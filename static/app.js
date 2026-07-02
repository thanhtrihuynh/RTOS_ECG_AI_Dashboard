let labels = [];
let labelInfo = {};
let uploadId = null;
let totalBeats = 0;
let currentSignal = [];
let currentTrueLabel = null;
let currentResultId = null;
let lastStatus = null;

const labelNamesVi = {
  N: "Nhịp bình thường",
  L: "Block nhánh trái",
  R: "Block nhánh phải",
  V: "Ngoại tâm thu thất",
  A: "Ngoại tâm thu nhĩ"
};

function $(id) { return document.getElementById(id); }
function setValueIfExists(id, value) { const el = $(id); if (el) el.value = value; }
function setMaxIfExists(id, value) { const el = $(id); if (el) el.max = value; }
function getCurrentBeatIndex() {
  const slider = $("beatSlider");
  const legacyInput = $("beatIndex");
  return Number((slider || legacyInput)?.value || 0);
}
function getBackend() { return document.querySelector("input[name='backend']:checked").value; }
function getFs() { return Number($("fsInput").value || 360); }
function fmtMs(v) { return `${Number(v).toFixed(4)} ms`; }
function fmtPct(v) { return v === null || v === undefined ? "-" : `${(Number(v) * 100).toFixed(2)}%`; }
function fmtSps(v) { return `${Number(v).toFixed(2)} beat/s`; }

function showWarnings(list) {
  const box = $("warningBox");
  if (!list || !list.length) {
    box.classList.add("hidden");
    box.innerHTML = "";
    return;
  }
  box.classList.remove("hidden");
  box.innerHTML = list.map(x => `<div>⚠ ${x}</div>`).join("");
}

function renderStatus(status) {
  lastStatus = status;
  const cpu = status.system_status.cpu || {};
  const na = cpu.combined || cpu.na_pair_overlap || {};
  const fpgaHls = status.system_status.fpga_hls || {};
  const fpgaRtl = status.system_status.fpga_rtl || {};

  const f32Received = Boolean(na.float32_received || cpu.float32?.received);
  const f32Loaded = Boolean(na.float32_loaded || cpu.float32?.loaded);
  const qReceived = Boolean(na.q4_12_received || cpu.q4_12?.received);
  const qLoaded = Boolean(na.q4_12_loaded || cpu.q4_12?.loaded);
  const anyOk = f32Loaded || qLoaded;
  const anyReceived = f32Received || qReceived;
  $("modelStatus").className = anyOk ? "statusLine statusOk" : (anyReceived ? "statusLine statusWarn" : "statusLine statusBad");
  const f32Text = f32Loaded ? 'đã load combined Keras' : (f32Received ? 'đã nhận file, chưa load TensorFlow/Keras' : 'chưa nhận package');
  const qText = qLoaded ? 'đã load engine .npz Q4.12' : (qReceived ? 'đã nhận .npz Q4.12, chưa có engine fixed-point đầy đủ' : 'chưa nhận package');
  $("modelStatus").innerHTML = `CPU Float32: ${f32Text}<br/>CPU Q4.12: ${qText}`;

  const hlsFiles = Boolean(fpgaHls.overlay_files_received);
  const rtlFiles = Boolean(fpgaRtl.overlay_files_received);
  const hlsLoaded = Boolean(fpgaHls.runtime_loaded);
  const rtlLoaded = Boolean(fpgaRtl.runtime_loaded);
  const hlsRemote = Boolean(fpgaHls.remote_available);
  const hlsRemoteUrl = fpgaHls.remote_url || "http://192.168.2.99:8000";
  $("fpgaStatus").className = (hlsLoaded || rtlLoaded || hlsRemote) ? "statusLine statusOk" : "statusLine statusBad";
  const hlsText = hlsRemote ? `remote API sẵn sàng (${hlsRemoteUrl})` : (hlsLoaded ? "đã load local" : (hlsFiles ? "đã nhận overlay nhưng chưa load" : "chưa nhận overlay"));
  $("fpgaStatus").innerHTML = `FPGA HLS overlay: ${hlsText}<br/>FPGA RTL overlay: ${rtlLoaded ? "đã load" : (rtlFiles ? "đã nhận overlay nhưng chưa load" : "chưa nhận overlay")}`;
}


function renderFpgaProbe(data) {
  const box = $("fpgaProbeStatus");
  if (!box) return;
  const ok = data.runtime_ready || data.environment_detected || data.remote_hls_ready;
  const cls = (data.runtime_ready || data.remote_hls_ready) ? "statusOk" : (data.environment_detected ? "statusWarn" : "statusBad");
  box.className = `datasetInfo ${cls}`;
  const pynqText = data.pynq_import_ok ? `có${data.pynq_version ? " (" + data.pynq_version + ")" : ""}` : "không";
  const deviceText = data.device_model || "không phát hiện";
  const nodesText = (data.device_nodes && data.device_nodes.length) ? data.device_nodes.join(", ") : "không có";
  box.innerHTML = `
    <b>${data.message}</b><br/>
    <b>PYNQ import:</b> ${pynqText}<br/>
    <b>Device model:</b> ${deviceText}<br/>
    <b>Device nodes:</b> ${nodesText}<br/>
    <b>HLS overlay:</b> ${data.hls_overlay_files ? "có .bit/.hwh" : "chưa có đủ .bit/.hwh"} | ${data.hls_runtime_loaded ? "đã load/local hoặc remote" : "chưa load"}<br/>
    <b>PYNQ remote API:</b> ${data.remote_hls_ready ? "sẵn sàng" : "chưa kết nối"} ${data.remote_hls_url ? "(" + data.remote_hls_url + ")" : ""}<br/>
    <b>RTL overlay:</b> ${data.rtl_overlay_files ? "có .bit/.hwh" : "chưa có đủ .bit/.hwh"} | ${data.rtl_runtime_loaded ? "đã load" : "chưa load"}
  `;
}

async function checkFpgaConnection() {
  const box = $("fpgaProbeStatus");
  if (box) {
    box.className = "datasetInfo";
    box.textContent = "Đang kiểm tra FPGA/PYNQ...";
  }
  const res = await fetch('/api/fpga_probe');
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderFpgaProbe(data);
}


async function loadModelFileStatus() {
  const res = await fetch('/api/model_files');
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderModelFileStatus(data);
}

function renderModelFileStatus(data) {
  const box = $("modelFileStatus");
  if (!box) return;
  const r = data.received || {};
  box.innerHTML = `
    <b>CPU Float32:</b> ${r.combined_cpu_float32 ? 'đã nhận combined Keras package' : 'chưa nhận'}<br/>
    <b>CPU Q4.12:</b> ${r.combined_cpu_q4_12 ? 'đã nhận combined Q4.12 package' : 'chưa nhận'}
  `;
}

async function importFpgaExport() {
  const res = await fetch('/api/import_fpga_export', { method: 'POST' });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderModelFileStatus(data.status);
  if (data.runtime_status) { renderStatus({system_status: data.runtime_status}); renderBackendDetails(getBackend()); }
  alert(`Đã import ${data.copied.length} file từ model_package_input/fpga_export vào đúng thư mục và reload model runtime.`);
}

async function reloadModels() {
  const res = await fetch('/api/reload_models', { method: 'POST' });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderStatus({system_status: data.system_status});
  renderBackendDetails(getBackend());
  await loadModelFileStatus();
}

function renderLabelInfo() {
  const box = $("labelInfo");
  box.innerHTML = labels.map(label => {
    const info = labelInfo[label] || {};
    return `
      <div class="infoItem">
        <strong>${label} - ${info.vi_name || labelNamesVi[label] || ""}</strong>
        <p>${info.description || ""}</p>
      </div>
    `;
  }).join("");
}

function drawWaveform(signal) {
  const canvas = $("waveCanvas");
  const ctx = canvas.getContext("2d");
  const dpr = window.devicePixelRatio || 1;
  const rect = canvas.getBoundingClientRect();
  canvas.width = Math.max(1, rect.width) * dpr;
  canvas.height = 230 * dpr;
  ctx.scale(dpr, dpr);

  const w = rect.width;
  const h = 230;
  ctx.clearRect(0, 0, w, h);

  ctx.strokeStyle = "rgba(255,255,255,0.08)";
  for (let i = 0; i <= 5; i++) {
    const y = (h / 5) * i;
    ctx.beginPath();
    ctx.moveTo(0, y);
    ctx.lineTo(w, y);
    ctx.stroke();
  }

  if (!signal || signal.length === 0) return;

  const maxAbs = Math.max(...signal.map(v => Math.abs(v))) || 1;
  const pad = 18;
  const mid = h / 2;
  const scale = (h / 2 - pad) / maxAbs;

  ctx.strokeStyle = "#42d392";
  ctx.lineWidth = 2;
  ctx.beginPath();

  signal.forEach((v, i) => {
    const x = (i / Math.max(1, signal.length - 1)) * w;
    const y = mid - v * scale;
    if (i === 0) ctx.moveTo(x, y);
    else ctx.lineTo(x, y);
  });

  ctx.stroke();

  ctx.fillStyle = "rgba(159,176,208,0.85)";
  ctx.font = "12px Segoe UI";
  ctx.fillText(`${signal.length} samples / beat`, 12, 20);
}

function drawProbabilities(probabilities) {
  const canvas = $("probCanvas");
  const ctx = canvas.getContext("2d");
  const dpr = window.devicePixelRatio || 1;
  const rect = canvas.getBoundingClientRect();
  canvas.width = Math.max(1, rect.width) * dpr;
  canvas.height = 190 * dpr;
  ctx.scale(dpr, dpr);

  const w = rect.width;
  const h = 190;
  ctx.clearRect(0, 0, w, h);

  const probs = labels.map(l => probabilities?.[l] || 0);
  const maxP = Math.max(0.001, ...probs);

  const padL = 34;
  const padB = 28;
  const top = 16;
  const barGap = 14;
  const barW = (w - padL - 20 - barGap * (labels.length - 1)) / labels.length;
  const usableH = h - top - padB;

  ctx.strokeStyle = "rgba(255,255,255,0.08)";
  for (let i = 0; i <= 4; i++) {
    const y = top + (usableH / 4) * i;
    ctx.beginPath();
    ctx.moveTo(padL, y);
    ctx.lineTo(w - 10, y);
    ctx.stroke();
  }

  labels.forEach((label, i) => {
    const p = probs[i];
    const bh = (p / maxP) * usableH;
    const x = padL + i * (barW + barGap);
    const y = top + usableH - bh;

    const grad = ctx.createLinearGradient(0, y, 0, y + bh);
    grad.addColorStop(0, "#67b7ff");
    grad.addColorStop(1, "#42d392");
    ctx.fillStyle = grad;
    ctx.fillRect(x, y, barW, bh);

    ctx.fillStyle = "#e9efff";
    ctx.font = "bold 13px Segoe UI";
    ctx.textAlign = "center";
    ctx.fillText(label, x + barW / 2, h - 8);

    ctx.fillStyle = "#9fb0d0";
    ctx.font = "12px Segoe UI";
    ctx.fillText(`${(p * 100).toFixed(1)}%`, x + barW / 2, Math.max(14, y - 5));
  });

  ctx.textAlign = "left";
}

function drawCounts(predCounts) {
  const canvas = $("countCanvas");
  const ctx = canvas.getContext("2d");
  const dpr = window.devicePixelRatio || 1;
  const rect = canvas.getBoundingClientRect();
  canvas.width = Math.max(1, rect.width) * dpr;
  canvas.height = 210 * dpr;
  ctx.scale(dpr, dpr);

  const w = rect.width;
  const h = 210;
  ctx.clearRect(0, 0, w, h);

  const counts = labels.map(l => predCounts?.[l] || 0);
  const maxC = Math.max(1, ...counts);

  const padL = 36;
  const padB = 30;
  const top = 18;
  const gap = 18;
  const barW = (w - padL - 20 - gap * (labels.length - 1)) / labels.length;
  const usableH = h - top - padB;

  ctx.strokeStyle = "rgba(255,255,255,0.08)";
  for (let i = 0; i <= 4; i++) {
    const y = top + (usableH / 4) * i;
    ctx.beginPath();
    ctx.moveTo(padL, y);
    ctx.lineTo(w - 10, y);
    ctx.stroke();
  }

  labels.forEach((label, i) => {
    const c = counts[i];
    const bh = (c / maxC) * usableH;
    const x = padL + i * (barW + gap);
    const y = top + usableH - bh;

    ctx.fillStyle = "#42d392";
    ctx.fillRect(x, y, barW, bh);

    ctx.fillStyle = "#e9efff";
    ctx.font = "bold 13px Segoe UI";
    ctx.textAlign = "center";
    ctx.fillText(label, x + barW / 2, h - 8);

    ctx.fillStyle = "#9fb0d0";
    ctx.font = "12px Segoe UI";
    ctx.fillText(`${c}`, x + barW / 2, Math.max(14, y - 5));
  });

  ctx.textAlign = "left";
}


function backendLabel(backendId) {
  const map = {
    cpu_float32: "CPU Float32",
    cpu_q4_12: "CPU Q4.12",
    fpga_hls_q4_12: "FPGA HLS Q4.12",
    fpga_rtl_q4_12: "FPGA RTL Q4.12"
  };
  return map[backendId] || backendId || "-";
}

function shortPath(p) {
  if (!p) return "-";
  const parts = String(p).replaceAll("\\", "/").split("/");
  return parts.slice(-3).join("/");
}

function detailCard(value, label, cls="") {
  return `<div class="${cls}"><span>${value}</span><small>${label}</small></div>`;
}


function fmtResourceItem(item) {
  if (!item) return "-";
  if (typeof item !== "object") return String(item);
  const used = item.used ?? "-";
  const avail = item.available ?? null;
  const pct = item.percent ?? null;
  if (avail !== null && avail !== undefined) {
    const pctText = pct !== null && pct !== undefined ? ` (${Number(pct).toFixed(1)}%)` : "";
    return `${used}/${avail}${pctText}`;
  }
  if (pct !== null && pct !== undefined) return `${used} (${Number(pct).toFixed(1)}%)`;
  return `${used}`;
}

function resourceCard(resourceUsage, key, label) {
  const available = Boolean(resourceUsage?.available);
  const item = resourceUsage?.resources?.[key];
  return detailCard(available && item ? fmtResourceItem(item) : "chưa có", label, available && item ? "ok" : "warn");
}

function fpgaResourceCards(resourceUsage) {
  const available = Boolean(resourceUsage?.available);
  return [
    detailCard(available ? "đã có" : "chưa có", "Resource report", available ? "ok" : "warn"),
    resourceCard(resourceUsage, "LUT", "LUT dùng / tổng"),
    resourceCard(resourceUsage, "FF", "FF dùng / tổng"),
    resourceCard(resourceUsage, "BRAM", "BRAM dùng / tổng"),
    resourceCard(resourceUsage, "DSP", "DSP dùng / tổng"),
    resourceCard(resourceUsage, "URAM", "URAM dùng / tổng"),
    detailCard(resourceUsage?.clock_mhz ?? resourceUsage?.clock_period_ns ?? "-", resourceUsage?.clock_mhz ? "Clock MHz" : "Clock period ns"),
    detailCard(resourceUsage?.latency_cycles ?? "-", "Latency cycles"),
    detailCard(resourceUsage?.ii ?? "-", "Initiation interval"),
    detailCard(shortPath(resourceUsage?.source_path || resourceUsage?.source), "Nguồn report")
  ];
}


function importantFpgaResourceCards(resourceUsage) {
  const available = Boolean(resourceUsage?.available);
  return [
    detailCard(available ? "Có" : "Chưa có", "Resource report", available ? "ok" : "warn"),
    resourceCard(resourceUsage, "LUT", "LUT"),
    resourceCard(resourceUsage, "FF", "FF"),
    resourceCard(resourceUsage, "BRAM", "BRAM"),
    resourceCard(resourceUsage, "DSP", "DSP"),
    detailCard(resourceUsage?.clock_mhz ?? resourceUsage?.clock_period_ns ?? "-", resourceUsage?.clock_mhz ? "Clock MHz" : "Clock ns"),
    detailCard(resourceUsage?.latency_cycles ?? "-", "Latency cycles"),
    detailCard(resourceUsage?.ii ?? "-", "II")
  ];
}


function renderBackendDetails(backendId = getBackend(), resultData = null) {
  const panel = $("backendDetailPanel");
  if (!panel) return;
  const sys = lastStatus?.system_status || {};
  const cpu = sys.cpu || {};
  const hls = sys.fpga_hls || {};
  const rtl = sys.fpga_rtl || {};

  let title = "Thông số backend đang chọn";
  let cards = [];

  if (backendId === "cpu_float32") {
    const loaded = Boolean(cpu.float32?.loaded || cpu.keras_loaded);
    title = "CPU Float32";
    cards = [
      detailCard(loaded ? "Loaded" : "Missing", "Combined models", loaded ? "ok" : "bad"),
      detailCard("5-class + N/A", "Pipeline")
    ];
  } else if (backendId === "cpu_q4_12") {
    title = "CPU Q4.12";
    cards = [
      detailCard(cpu.q4_12?.loaded ? "Loaded" : (cpu.q4_12?.received ? "Received" : "Missing"), "Q4.12 .npz weights", cpu.q4_12?.loaded ? "ok" : (cpu.q4_12?.received ? "warn" : "bad")),
      detailCard(cpu.q4_12?.mode || "Q4.12 package", "Mode")
    ];
  } else if (backendId === "fpga_hls_q4_12") {
    const files = Boolean(hls.overlay_files_received);
    const loaded = Boolean(hls.runtime_loaded);
    title = "Tài nguyên FPGA HLS Q4.12";
    cards = [
      detailCard(files ? "Có" : "Thiếu", ".bit/.hwh", files ? "ok" : "bad"),
      detailCard(loaded ? "Loaded" : "Chưa load", "PYNQ runtime", loaded ? "ok" : (files ? "warn" : "bad")),
      ...importantFpgaResourceCards(hls.resource_usage || {})
    ];
  } else if (backendId === "fpga_rtl_q4_12") {
    const files = Boolean(rtl.overlay_files_received);
    const loaded = Boolean(rtl.runtime_loaded);
    title = "Tài nguyên FPGA RTL Q4.12";
    cards = [
      detailCard(files ? "Có" : "Thiếu", ".bit/.hwh", files ? "ok" : "bad"),
      detailCard(loaded ? "Loaded" : "Chưa load", "PYNQ runtime", loaded ? "ok" : (files ? "warn" : "bad")),
      ...importantFpgaResourceCards(rtl.resource_usage || {})
    ];
  }

  panel.innerHTML = `
    <div class="detailTitle">${title}</div>
    <div class="detailGrid compactBackendGrid">${cards.join("")}</div>
  `;
}

function clearPrediction() {
  $("predLabel").textContent = "-";
  $("predName").textContent = "Chưa suy luận";
  $("confidenceText").textContent = "0.00%";
  $("latencyText").textContent = "-";
  $("throughputText").textContent = "-";
  $("backendText").textContent = backendLabel(getBackend());
  $("engineNote").textContent = "";
  renderBackendDetails(getBackend());
  drawProbabilities({});
  const cards = $("beatMultiCards");
  if (cards) cards.innerHTML = `<div class="backendRunCard empty">Bấm Predict multi-backend để xem latency từng backend.</div>`;
}


function updateBeatPositionText(index, total) {
  const text = total > 0 ? `${index} / ${total - 1}` : '0 / 0';
  if ($("beatPositionText")) $("beatPositionText").textContent = text;
}

function renderRecordTracking(meta, beatIndex, totalBeats, stats = null) {
  const box = $("recordTrackingInfo");
  if (!box) return;
  if (!meta) {
    box.innerHTML = `Beat ${beatIndex} / ${Math.max(0, totalBeats - 1)}`;
    return;
  }
  const record = meta.record_id || '-';
  const channel = meta.channel || meta.selected_channel || '-';
  const start = meta.start ?? '-';
  const end = meta.end ?? '-';
  const startTime = meta.start_time || '-';
  const endTime = meta.end_time || '-';
  const label = meta.label || '-';
  const chIndex = meta.selected_channel_index ?? '-';
  const available = Array.isArray(meta.available_channels) ? meta.available_channels.join(', ') : '-';
  const statsText = stats ? `<br/><b>Beat stats:</b> shape=${stats.shape} | mean=${Number(stats.mean).toFixed(3)} | std=${Number(stats.std).toFixed(3)} | min=${Number(stats.min).toFixed(3)} | max=${Number(stats.max).toFixed(3)}` : '';
  box.innerHTML = `
    <b>Record:</b> ${record} | <b>Beat:</b> ${beatIndex} / ${Math.max(0, totalBeats - 1)} | <b>Label:</b> ${label}<br/>
    <b>Selected channel:</b> ${channel} | <b>Index:</b> ${chIndex} | <b>Available:</b> ${available}<br/>
    <b>Range:</b> ${start} - ${end} | <b>Time:</b> ${startTime} - ${endTime}${statsText}
  `;
}

let beatLoadTimer = null;
function scheduleLoadBeat() {
  const idx = getCurrentBeatIndex();
  updateBeatPositionText(idx, totalBeats);
  const meta = null;
  if ($("beatHint")) $("beatHint").textContent = `Đang load beat ${idx} / ${Math.max(0, totalBeats - 1)}...`;

  clearTimeout(beatLoadTimer);
  beatLoadTimer = setTimeout(() => {
    loadBeat().catch(err => alert(`Load beat error: ${err.message}`));
  }, 60);
}

function getBeatStep() {
  const raw = Number($("beatStepInput")?.value || 1);
  return Math.max(1, Math.floor(Math.abs(raw)) || 1);
}

async function stepBeat(delta = 1) {
  if (!uploadId || totalBeats <= 0) return alert("Chưa load dataset.");
  const slider = $("beatSlider");
  const current = getCurrentBeatIndex();
  const next = Math.max(0, Math.min(totalBeats - 1, current + delta));
  if (slider) slider.value = next;
  updateBeatPositionText(next, totalBeats);
  await loadBeat();
}


function renderDatasetContext(recordContext) {
  const box = $("predictDatasetContext");
  if (!box) return;
  if (!recordContext) {
    box.innerHTML = "Record/Dataset: chưa có dữ liệu.";
    return;
  }
  box.innerHTML = `
    <b>Record/Dataset:</b> ${recordContext.record_text || '-'} |
    <b>Format:</b> ${recordContext.format_type || '-'} |
    <b>Total beats:</b> ${recordContext.total_beats ?? '-'}
  `;
}

async function uploadVerilogFiles() {
  const files = $("verilogFiles").files;
  if (!files || files.length === 0) {
    alert('Chọn file .v/.sv/.vh trước.');
    return;
  }
  const fd = new FormData();
  for (const file of files) fd.append('files', file);
  const res = await fetch('/api/upload_verilog_registers', { method: 'POST', body: fd });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  $("verilogStatus").innerHTML = `Đã lưu ${data.count} file RTL/Verilog vào ${data.target_dir}`;
}

function renderDatasetInfo(data) {
  uploadId = data.upload_id;
  totalBeats = data.total_beats;
  currentSignal = data.first_signal;
  currentTrueLabel = data.first_true_label;

  setValueIfExists("beatSlider", 0);
  setMaxIfExists("beatSlider", Math.max(0, totalBeats - 1));
  setValueIfExists("beatIndex", 0);
  setMaxIfExists("beatIndex", Math.max(0, totalBeats - 1));
  updateBeatPositionText(0, totalBeats);
  $("trueLabelBadge").textContent = `True: ${currentTrueLabel || "unknown"}`;

  $("datasetInfo").innerHTML = `
    <b>File:</b> ${data.filename}<br/>
    <b>Format:</b> ${data.format_type}<br/>
    <b>Total heartbeat:</b> ${data.total_beats}<br/>
    <b>Raw rows:</b> ${data.raw_rows}<br/>
    <b>Raw cols:</b> ${data.raw_cols}<br/>
    <b>Raw samples/beat:</b> ${data.raw_samples_per_beat}<br/>
    <b>Normalized:</b> ${data.normalized_length} mẫu/beat<br/>
    <b>Has label:</b> ${data.has_labels ? "yes" : "no"}
  `;

  $("beatHint").textContent = `Đã load beat 0 / ${Math.max(0, totalBeats - 1)}.`;
  const firstMeta = data.info && data.info.segments ? data.info.segments[0] : null;
  renderRecordTracking(firstMeta, 0, totalBeats);
  drawWaveform(currentSignal);
  clearPrediction();
  renderDatasetContext(data.record_context);
  showWarnings(data.warnings || []);
}


async function loadRecords() {
  const q = $("recordSearchInput") ? $("recordSearchInput").value.trim() : "";
  const url = q ? `/api/records?q=${encodeURIComponent(q)}` : "/api/records";
  const res = await fetch(url);
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderRecordList(data.records || []);
}

function renderRecordList(records) {
  const box = $("recordList");
  if (!box) return;
  if (!records.length) {
    box.innerHTML = "Chưa có record đã lưu.";
    return;
  }
  box.innerHTML = records.map(r => {
    const files = Object.keys(r.files || {}).join(", ");
    return `
      <div class="recordItem">
        <strong>Record ${r.record_id}</strong>
        <small>Files: ${files || "-"}</small>
        <small>Updated: ${r.updated_at || "-"}</small>
        <div class="recordActions">
          <button onclick="loadSavedRecord('${r.record_id}')">Load</button>
          <button class="secondary" onclick="downloadSavedRecord('${r.record_id}')">ZIP</button>
          <button class="secondary dangerBtn" onclick="deleteSavedRecord('${r.record_id}')">Delete</button>
        </div>
      </div>
    `;
  }).join("");
}

async function loadSavedRecord(recordId) {
  const res = await fetch(`/api/records/${encodeURIComponent(recordId)}/load`, { method: "POST" });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderDatasetInfo(data);
  await loadRecords();
  await loadModelFileStatus();
  await loadBulkStatus();
  await loadLabelRecordMap();
}

function downloadSavedRecord(recordId) {
  window.location.href = `/api/records/${encodeURIComponent(recordId)}/download`;
}

async function deleteSavedRecord(recordId) {
  if (!confirm(`Xóa record ${recordId} khỏi Record Library?`)) return;
  const res = await fetch(`/api/records/${encodeURIComponent(recordId)}`, { method: 'DELETE' });
  if (!res.ok) throw new Error(await res.text());
  await loadRecords();
}

async function init() {
  const labelBox = $("labelRecordMap");
  if (labelBox) labelBox.innerHTML = "Đã nạp app.js V40. Bấm Refresh label map hoặc Index Dataset Folder.";
  const res = await fetch("/api/status");
  const data = await res.json();

  labels = data.labels;
  labelInfo = data.label_info;

  renderStatus(data);
  renderBackendDetails(getBackend());
  renderLabelInfo();
  drawWaveform([]);
  drawProbabilities({});
  drawCounts({});
  await loadRecords();
  await loadModelFileStatus();
  await loadBulkStatus();
}

function activateMode(mode) {
  document.querySelectorAll(".modeBtn").forEach(btn => {
    btn.classList.toggle("active", btn.dataset.mode === mode);
  });
  document.querySelectorAll(".modePanel").forEach(panel => {
    panel.classList.toggle("active", panel.id === `panel-${mode}`);
  });
}

async function uploadCsvTable() {
  const file = $("csvTableFile").files?.[0];
  if (!file) return alert("Chọn file CSV heartbeat trước.");
  const fd = new FormData();
  fd.append("file", file);

  const res = await fetch(`/api/upload_csv_mode?mode=heartbeat_table&fs=${getFs()}`, {
    method: "POST",
    body: fd
  });
  if (!res.ok) throw new Error(await res.text());
  renderDatasetInfo(await res.json());
  await loadRecords();
  await loadModelFileStatus();
  await loadBulkStatus();
}

async function uploadCsvLong() {
  const file = $("csvLongFile").files?.[0];
  if (!file) return alert("Chọn file CSV ECG dài trước.");
  const fd = new FormData();
  fd.append("file", file);

  const res = await fetch(`/api/upload_csv_mode?mode=long_ecg&fs=${getFs()}`, {
    method: "POST",
    body: fd
  });
  if (!res.ok) throw new Error(await res.text());
  renderDatasetInfo(await res.json());
  await loadRecords();
  await loadModelFileStatus();
  await loadBulkStatus();
}


function fileStem(file) {
  if (!file) return null;
  const name = file.name;
  const idx = name.lastIndexOf('.');
  return idx >= 0 ? name.substring(0, idx) : name;
}

function validateWfdbSelection(hea, dat, atr, xws) {
  if (!hea || !dat) {
    alert('WFDB cần tối thiểu file .hea và .dat.');
    return false;
  }
  const base = fileStem(hea);
  const selected = {'.hea': hea, '.dat': dat, '.atr': atr, '.xws': xws};
  const mismatches = [];
  for (const [ext, file] of Object.entries(selected)) {
    if (!file) continue;
    const stem = fileStem(file);
    if (stem !== base) mismatches.push(`${ext}=${stem}`);
  }
  if (mismatches.length) {
    alert(`Các file WFDB phải cùng record ID. Bạn đang chọn lệch: ${mismatches.join(', ')}. Ví dụ đúng: ${base}.hea, ${base}.dat, ${base}.atr, ${base}.xws.`);
    return false;
  }
  return true;
}

async function uploadWfdb(saveRecord = false) {
  const hea = $("wfdbHeaFile").files?.[0];
  const dat = $("wfdbDatFile").files?.[0];
  const atr = $("wfdbAtrFile").files?.[0];
  const xws = $("wfdbXwsFile").files?.[0];

  if (!validateWfdbSelection(hea, dat, atr, xws)) return;

  const fd = new FormData();
  fd.append("hea_file", hea);
  fd.append("dat_file", dat);
  if (atr) fd.append("atr_file", atr);
  if (xws) fd.append("xws_file", xws);

  const res = await fetch(`/api/upload_wfdb_guided?fs=${getFs()}&save=${saveRecord ? 'true' : 'false'}`, {
    method: "POST",
    body: fd
  });
  if (!res.ok) throw new Error(await res.text());
  renderDatasetInfo(await res.json());
  await loadRecords();
  await loadModelFileStatus();
  await loadBulkStatus();
}

async function loadBulkStatus() {
  const res = await fetch('/api/bulk/status');
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderBulkStatus(data);
}

function renderBulkStatus(data) {
  const box = $("bulkStatusBox");
  if (!box) return;
  box.innerHTML = `
    <b>Metadata dir:</b> ${data.metadata_dir}<br/>
    <b>WFDB dir:</b> ${data.wfdb_records_dir}<br/>
    <b>CSV files:</b> ${(data.csv_files || []).join(', ') || '-'}<br/>
    <b>WFDB files:</b> ${data.wfdb_file_count}<br/>
    <b>Records:</b> ${data.record_count}<br/>
    <b>Segments:</b> ${data.segment_count}<br/>
    <b>Labels:</b> ${JSON.stringify(data.labels_count || {})}
  `;
}

window.loadLabelRecordMap = async function loadLabelRecordMap() {
  const box = $("labelRecordMap");
  if (box) box.innerHTML = "Đang đọc Bulk Dataset Index...";
  try {
    const res = await fetch('/api/bulk/label_records');
    if (!res.ok) throw new Error(await res.text());
    const data = await res.json();
    renderLabelRecordMap(data.summary || {}, data);
  } catch (err) {
    if (box) box.innerHTML = `Không đọc được label map: ${err.message}`;
    throw err;
  }
};

function renderLabelRecordMap(summary, meta = {}) {
  const box = $("labelRecordMap");
  if (!box) return;
  const segmentCount = Number(meta.segment_count || 0);
  const recordCount = Number(meta.record_count || 0);
  if (segmentCount === 0) {
    box.innerHTML = `
      <div class="recordItem">
        <strong>Chưa có dữ liệu trong Bulk Dataset Index</strong>
        <small>Hãy bấm Index Dataset Folder trước, sau đó bấm Refresh label map.</small>
        <small>Nếu đã index rồi mà vẫn thấy dòng này, bấm Ctrl + F5 để xóa cache JavaScript cũ.</small>
      </div>
    `;
    return;
  }
  const order = ['N', 'L', 'R', 'V', 'A'];
  const rows = [`
    <div class="recordItem">
      <strong>Bulk Index: ${recordCount} record | ${segmentCount} segment</strong>
      <small>Nguồn: ${meta.db_path || 'record_library/metadata/dataset_index.sqlite'}</small>
    </div>
  `];
  rows.push(...order.map(label => {
    const item = summary[label] || {record_count: 0, beat_count: 0, records: []};
    const records = item.records || [];
    const recordText = records.length
      ? records.map(r => `${r.record_id} (${r.beat_count})`).join(', ')
      : 'Không có record';
    return `
      <div class="recordItem">
        <strong>${label} - ${labelNamesVi[label] || label}</strong>
        <small>${item.record_count || 0} record | ${item.beat_count || 0} beat</small>
        <small>${recordText}</small>
      </div>
    `;
  }));
  box.innerHTML = rows.join('');
}


async function indexBulkDataset() {
  const res = await fetch('/api/bulk/import_folder', { method: 'POST' });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  alert(`Đã index ${data.inserted_segments} segments từ ${data.saved_records} records. Missing records: ${data.missing_records_count}`);
  await loadBulkStatus();
  await loadLabelRecordMap();
  await loadRecords();
}

async function searchBulkSegments() {
  const recordId = $("bulkRecordSearchInput").value.trim();
  const label = $("bulkLabelSearchInput").value.trim();
  const params = new URLSearchParams();
  if (recordId) params.set('record_id', recordId);
  if (label) params.set('label', label);
  params.set('limit', '100');
  const res = await fetch(`/api/bulk/search?${params.toString()}`);
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderBulkSegments(data.segments || []);
}

function renderBulkSegments(segments) {
  const box = $("bulkSegmentList");
  if (!box) return;
  if (!segments.length) {
    box.innerHTML = "Không tìm thấy segment.";
    return;
  }
  box.innerHTML = segments.map(s => `
    <div class="recordItem">
      <strong>${s.record_id} | ${s.label || '-'} | #${s.segment_id}</strong>
      <small>Channel: ${s.channel || '-'}</small>
      <small>Range: ${s.start} - ${s.end}</small>
      <div class="recordActions">
        <button onclick="loadBulkSegment(${s.segment_id})">Load beat</button>
        <button class="secondary" onclick="loadBulkRecord('${s.record_id}')">Load record</button>
      </div>
    </div>
  `).join('');
}

async function loadBulkSegment(segmentId) {
  const res = await fetch(`/api/bulk/segments/${segmentId}/load`, { method: 'POST' });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderDatasetInfo(data);
}

async function loadBulkRecord(recordId) {
  const res = await fetch(`/api/bulk/records/${encodeURIComponent(recordId)}/load`, { method: 'POST' });
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();
  renderDatasetInfo(data);
}

async function loadBeat() {
  if (!uploadId) return alert("Chưa upload dataset.");
  const idx = getCurrentBeatIndex();
  const res = await fetch(`/api/dataset/${uploadId}/beat/${idx}`);
  if (!res.ok) throw new Error(await res.text());
  const data = await res.json();

  currentSignal = data.signal;
  currentTrueLabel = data.true_label;
  $("trueLabelBadge").textContent = `True: ${currentTrueLabel || "unknown"}`;
  $("beatHint").textContent = `Đã load beat ${idx} / ${data.total_beats - 1}.`;
  setValueIfExists("beatSlider", idx);
  updateBeatPositionText(idx, data.total_beats);
  renderRecordTracking(data.beat_meta, idx, data.total_beats, data.beat_stats);
  drawWaveform(currentSignal);
  clearPrediction();
}


async function predictBeat() {
  if (!uploadId) return alert("Chưa upload dataset.");
  const idx = getCurrentBeatIndex();

  $("predictBeatBtn").disabled = true;
  $("predictBeatBtn").textContent = "Running...";
  try {
    const res = await fetch("/api/predict_beat", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify({
        upload_id: uploadId,
        beat_index: idx,
        backend: getBackend()
      })
    });

    if (!res.ok) throw new Error(await res.text());
    const data = await res.json();

    $("predLabel").textContent = data.predicted_label;
    $("predName").textContent = labelInfo[data.predicted_label]?.vi_name || "";
    $("confidenceText").textContent = fmtPct(data.confidence);
    $("latencyText").textContent = fmtMs(data.latency_ms);
    $("throughputText").textContent = fmtSps(data.throughput_sps);
    $("backendText").textContent = backendLabel(data.backend);
    $("engineNote").textContent = data.note;
    renderBackendDetails(data.backend, data);
    $("trueLabelBadge").textContent = `True: ${data.true_label || "unknown"}`;

    currentSignal = data.signal;
    drawWaveform(currentSignal);
    drawProbabilities(data.probabilities);

    const warnings = [];
    if (data.note && data.note.includes("WARNING")) warnings.push(data.note);
    showWarnings(warnings);
  } catch (err) {
    alert(`Predict beat error: ${err.message}`);
  } finally {
    $("predictBeatBtn").disabled = false;
    $("predictBeatBtn").textContent = "Predict beat";
  }
}


async function predictBeatMultiBackend() {
  if (!uploadId) return alert("Chưa upload dataset.");
  const idx = getCurrentBeatIndex();
  const btns = [$("predictBeatMultiBtn"), $("predictBeatMultiBtnWide")].filter(Boolean);
  const box = $("beatMultiCards");
  if (box) box.innerHTML = `<div class="backendRunCard empty">Đang chạy nhiều backend...</div>`;

  for (const btn of btns) {
    btn.disabled = true;
    btn.textContent = "Running multi...";
  }
  try {
    const res = await fetch("/api/predict_beat_multi", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify({
        upload_id: uploadId,
        beat_index: idx,
        backends: getSelectedBeatBackends()
      })
    });
    if (!res.ok) throw new Error(await res.text());
    const data = await res.json();
    renderBeatMultiResults(data);
    $("trueLabelBadge").textContent = `True: ${data.true_label || "unknown"}`;

    const selectedBackend = getBackend();
    const selectedResult = (data.results || []).find(r => r.backend === selectedBackend) || (data.results || [])[0];
    if (selectedResult) {
      $("predLabel").textContent = selectedResult.predicted_label;
      $("predName").textContent = labelInfo[selectedResult.predicted_label]?.vi_name || "";
      $("confidenceText").textContent = fmtPct(selectedResult.confidence);
      $("latencyText").textContent = fmtMs(selectedResult.latency_ms);
      $("throughputText").textContent = fmtSps(selectedResult.throughput_sps);
      $("backendText").textContent = backendLabel(selectedResult.backend);
      $("engineNote").textContent = selectedResult.note || "";
      renderBackendDetails(selectedResult.backend, selectedResult);
      drawProbabilities(selectedResult.probabilities || {});
    }

    const warnings = [];
    for (const e of (data.errors || [])) warnings.push(`${backendLabel(e.backend)}: ${e.error}`);
    showWarnings(warnings);
  } catch (err) {
    alert(`Predict multi-backend beat error: ${err.message}`);
  } finally {
    for (const btn of btns) {
      btn.disabled = false;
      btn.textContent = "Predict multi-backend";
    }
  }
}

function renderTable(rows) {
  const tbody = $("resultTable").querySelector("tbody");
  if (!rows.length) {
    tbody.innerHTML = `<tr><td colspan="7">Chưa có kết quả.</td></tr>`;
    return;
  }

  tbody.innerHTML = rows.map(r => {
    const correctText = r.correct === null || r.correct === undefined ? "-" : (r.correct ? "yes" : "no");
    return `
      <tr>
        <td>${r.beat_index}</td>
        <td>${r.true_label || "-"}</td>
        <td>${r.predicted_label}</td>
        <td>${correctText}</td>
        <td>${fmtPct(r.confidence)}</td>
        <td>${fmtMs(r.latency_ms)}</td>
        <td>${r.note}</td>
      </tr>
    `;
  }).join("");
}

function renderPerClassStats(rows) {
  const table = $("perClassTable");
  if (!table) return;
  const tbody = table.querySelector("tbody");
  if (!rows || !rows.length) {
    tbody.innerHTML = `<tr><td colspan="4">Chưa có thống kê theo lớp.</td></tr>`;
    return;
  }
  tbody.innerHTML = rows.map(r => {
    const trueTotal = Number(r.true_total || 0);
    const correct = Number(r.correct || 0);
    const predTotal = Number(r.pred_total || 0);
    const acc = r.accuracy === null || r.accuracy === undefined ? "-" : fmtPct(r.accuracy);
    return `
      <tr>
        <td><b>${r.label}</b> - ${labelNamesVi[r.label] || ""}</td>
        <td><b>${correct} / ${trueTotal}</b></td>
        <td>${acc}</td>
        <td>${predTotal}</td>
      </tr>
    `;
  }).join("");
}

function getSelectedMultiBackends() {
  const checked = Array.from(document.querySelectorAll(".multiBackendCheck:checked")).map(x => x.value);
  return checked.length ? checked : [getBackend()];
}

function getSelectedBeatBackends() {
  const checked = Array.from(document.querySelectorAll(".beatBackendCheck:checked")).map(x => x.value);
  return checked.length ? checked : [getBackend()];
}

function backendCardClass(backendId, ok=true) {
  if (!ok) return "backendRunCard error";
  if (backendId === "cpu_float32") return "backendRunCard cpuFloat";
  if (backendId === "cpu_q4_12") return "backendRunCard cpuQ12";
  if (backendId === "fpga_hls_q4_12") return "backendRunCard fpgaHls";
  if (backendId === "fpga_rtl_q4_12") return "backendRunCard fpgaRtl";
  return "backendRunCard";
}

function escapeHtml(text) {
  return String(text ?? "")
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;")
    .replaceAll("'", "&#039;");
}

function correctnessPill(correct) {
  if (correct === null || correct === undefined) return `<span class="truthPill neutral">-</span>`;
  return correct ? `<span class="truthPill true">True</span>` : `<span class="truthPill false">False</span>`;
}

function compactBackendError(errText, backendId) {
  const raw = String(errText || "");
  const lower = raw.toLowerCase();
  if (backendId === "fpga_hls_q4_12" && (lower.includes("overlay") || lower.includes(".bit") || lower.includes(".hwh"))) {
    return "Chưa có overlay HLS (.bit/.hwh).";
  }
  if (backendId === "fpga_rtl_q4_12" && (lower.includes("overlay") || lower.includes(".bit") || lower.includes(".hwh"))) {
    return "Chưa có overlay RTL (.bit/.hwh).";
  }
  if (lower.includes("pynq") || lower.includes("zynq")) {
    return "Chưa phát hiện runtime PYNQ/Zynq.";
  }
  if (lower.includes("tensorflow") || lower.includes("keras")) {
    return "Chưa load được TensorFlow/Keras.";
  }
  if (lower.includes("không chạy được backend")) {
    return "Backend chưa sẵn sàng.";
  }
  return raw.length > 120 ? raw.slice(0, 117) + "..." : raw;
}

function renderBeatMultiResults(data) {
  const box = $("beatMultiCards");
  if (!box) return;
  const rows = [];
  for (const r of (data.results || [])) {
    const predName = labelNamesVi[r.predicted_label] || "";
    rows.push(`
      <div class="${backendCardClass(r.backend, true)}">
        <div class="backendRunTop">
          <b>${backendLabel(r.backend)}</b>
          <span class="runDot ok"></span>
        </div>
        <div class="runPred">${escapeHtml(r.predicted_label || "-")}</div>
        <div class="runSub">${escapeHtml(predName)}</div>
        <div class="runMetrics">
          <div><span>${fmtMs(r.latency_ms)}</span><small>Latency</small></div>
          <div><span>${fmtPct(r.confidence)}</span><small>Confidence</small></div>
          <div><span>${correctnessPill(r.correct)}</span><small>Kết quả</small></div>
        </div>
        <div class="runNote" title="${escapeHtml(r.note || "")}">${escapeHtml(r.note || "-")}</div>
      </div>
    `);
  }
  for (const e of (data.errors || [])) {
    const fullErr = String(e.error || "");
    const compactErr = compactBackendError(fullErr, e.backend);
    rows.push(`
      <div class="${backendCardClass(e.backend, false)}">
        <div class="backendRunTop">
          <b>${backendLabel(e.backend)}</b>
          <span class="runDot bad"></span>
        </div>
        <div class="runPred errorTitle">Lỗi</div>
        <div class="runSub">Backend chưa sẵn sàng</div>
        <div class="errorPill">Không chạy</div>
        <div class="runError" title="${escapeHtml(fullErr)}">${escapeHtml(compactErr)}</div>
      </div>
    `);
  }
  box.innerHTML = rows.length ? rows.join("") : `<div class="backendRunCard empty">Không có backend nào được chọn.</div>`;
}

function renderMultiBackendResults(data) {
  const table = $("multiBackendTable");
  if (!table) return;
  const tbody = table.querySelector("tbody");
  const rows = [];
  for (const r of (data.results || [])) {
    const labeled = Number(r.labeled_count || 0);
    const correct = Number(r.correct_count || 0);
    rows.push(`
      <tr>
        <td><b>${backendLabel(r.backend)}</b></td>
        <td>${labeled > 0 ? `${correct} / ${labeled}` : "No labels"}</td>
        <td>${r.accuracy === null || r.accuracy === undefined ? "-" : fmtPct(r.accuracy)}</td>
        <td>${fmtMs(r.avg_latency_ms)}</td>
        <td>${fmtSps(r.throughput_sps)}</td>
        <td>OK</td>
      </tr>
    `);
  }
  for (const e of (data.errors || [])) {
    rows.push(`
      <tr class="errorRow">
        <td><b>${backendLabel(e.backend)}</b></td>
        <td>-</td>
        <td>-</td>
        <td>-</td>
        <td>-</td>
        <td>${e.error}</td>
      </tr>
    `);
  }
  tbody.innerHTML = rows.length ? rows.join("") : `<tr><td colspan="6">Không có kết quả backend.</td></tr>`;
}


async function predictDataset() {
  if (!uploadId) return alert("Chưa upload dataset.");

  $("predictDatasetBtn").disabled = true;
  $("predictDatasetBtn").textContent = "Running dataset...";
  try {
    const maxRaw = $("maxBeatsInput").value.trim();
    const payload = {
      upload_id: uploadId,
      backend: getBackend()
    };
    if (maxRaw !== "") payload.max_beats = Number(maxRaw);

    const res = await fetch("/api/predict_dataset", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify(payload)
    });

    if (!res.ok) throw new Error(await res.text());
    const data = await res.json();

    currentResultId = data.result_id;
    renderDatasetContext(data.record_context);
    $("totalRunText").textContent = `${data.total_run}`;
    const labeled = data.labeled_count || 0;
    const correct = data.correct_count || 0;
    $("correctCountText").textContent = labeled > 0 ? `${correct} / ${labeled}` : "No labels";
    $("accuracyText").textContent = data.accuracy === null ? "No labels" : fmtPct(data.accuracy);
    $("avgLatencyText").textContent = fmtMs(data.avg_latency_ms);
    $("datasetThroughputText").textContent = fmtSps(data.throughput_sps);

    drawCounts(data.pred_counts);
    renderPerClassStats(data.per_class_stats || []);
    renderTable(data.preview_rows || []);

    $("exportCsvBtn").disabled = false;
    $("exportJsonBtn").disabled = false;

    const warnings = [...(data.warnings || [])];
    const sys = data.system_status || {};
    const f32Warning = sys.cpu?.float32?.warning;
    const qWarning = sys.cpu?.q4_12?.warning;
    const fpgaHlsWarning = sys.fpga_hls?.warning;
    const fpgaRtlWarning = sys.fpga_rtl?.warning;
    if (getBackend() === "cpu_float32" && f32Warning) warnings.push(f32Warning);
    if (getBackend() === "cpu_q4_12" && qWarning) warnings.push(qWarning);
    if (getBackend() === "fpga_hls_q4_12" && fpgaHlsWarning) warnings.push(fpgaHlsWarning);
    if (getBackend() === "fpga_rtl_q4_12" && fpgaRtlWarning) warnings.push(fpgaRtlWarning);
    showWarnings(warnings);
  } catch (err) {
    alert(`Predict dataset error: ${err.message}`);
  } finally {
    $("predictDatasetBtn").disabled = false;
    $("predictDatasetBtn").textContent = "Predict dataset";
  }
}

async function predictMultiBackendDataset() {
  if (!uploadId) return alert("Chưa upload dataset.");

  const btn = $("predictMultiBackendBtn");
  if (btn) {
    btn.disabled = true;
    btn.textContent = "Running multi...";
  }
  try {
    const maxRaw = $("maxBeatsInput").value.trim();
    const payload = {
      upload_id: uploadId,
      backends: getSelectedMultiBackends()
    };
    if (maxRaw !== "") payload.max_beats = Number(maxRaw);

    const res = await fetch("/api/predict_dataset_multi", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify(payload)
    });
    if (!res.ok) throw new Error(await res.text());
    const data = await res.json();
    renderDatasetContext(data.record_context);
    renderMultiBackendResults(data);

    const firstOk = (data.results || [])[0];
    if (firstOk) {
      $("totalRunText").textContent = `${firstOk.total_run}`;
      const labeled = firstOk.labeled_count || 0;
      const correct = firstOk.correct_count || 0;
      $("correctCountText").textContent = labeled > 0 ? `${correct} / ${labeled}` : "No labels";
      $("accuracyText").textContent = firstOk.accuracy === null ? "No labels" : fmtPct(firstOk.accuracy);
      $("avgLatencyText").textContent = fmtMs(firstOk.avg_latency_ms);
      $("datasetThroughputText").textContent = fmtSps(firstOk.throughput_sps);
      drawCounts(firstOk.pred_counts || {});
      renderPerClassStats(firstOk.per_class_stats || []);
    }

    const warnings = [];
    for (const e of (data.errors || [])) warnings.push(`${backendLabel(e.backend)}: ${e.error}`);
    showWarnings(warnings);
  } catch (err) {
    alert(`Predict multi-backend error: ${err.message}`);
  } finally {
    for (const btn of btns) {
      btn.disabled = false;
      btn.textContent = "Predict multi-backend";
    }
  }
}

function exportCsv() {
  if (!currentResultId) return;
  window.location.href = `/api/export/${currentResultId}/csv`;
}

function exportJson() {
  if (!currentResultId) return;
  window.location.href = `/api/export/${currentResultId}/json`;
}

document.querySelectorAll(".modeBtn").forEach(btn => {
  btn.addEventListener("click", () => activateMode(btn.dataset.mode));
});

$("uploadCsvTableBtn").addEventListener("click", async () => {
  try { await uploadCsvTable(); } catch (err) { alert(`Upload error: ${err.message}`); }
});
$("uploadCsvLongBtn").addEventListener("click", async () => {
  try { await uploadCsvLong(); } catch (err) { alert(`Upload error: ${err.message}`); }
});
$("uploadWfdbBtn").addEventListener("click", async () => {
  try { await uploadWfdb(false); } catch (err) { alert(`Upload error: ${err.message}`); }
});
$("saveWfdbBtn").addEventListener("click", async () => {
  try { await uploadWfdb(true); } catch (err) { alert(`Save error: ${err.message}`); }
});

if ($("beatSlider")) {
  $("beatSlider").addEventListener("input", scheduleLoadBeat);
  $("beatSlider").addEventListener("change", scheduleLoadBeat);
}
if ($("prevBeatStepBtn")) {
  $("prevBeatStepBtn").addEventListener("click", async () => {
    try { await stepBeat(-getBeatStep()); } catch (err) { alert(`Prev beat error: ${err.message}`); }
  });
}
if ($("nextBeatStepBtn")) {
  $("nextBeatStepBtn").addEventListener("click", async () => {
    try { await stepBeat(getBeatStep()); } catch (err) { alert(`Next beat error: ${err.message}`); }
  });
}

document.querySelectorAll("input[name='backend']").forEach(radio => {
  radio.addEventListener("change", () => {
    clearPrediction();
    const selected = getBackend();
    if (selected.startsWith("fpga_")) {
      showWarnings(["Bạn đang chọn backend FPGA. Kết quả beat sẽ phụ thuộc vào overlay .bit/.hwh, PYNQ runtime và register_map tương ứng. Nếu chưa có overlay hoặc chưa nối AXI thật, backend sẽ báo lỗi thay vì dùng kết quả CPU."]);
    } else {
      showWarnings([]);
    }
  });
});

$("predictBeatBtn").addEventListener("click", predictBeat);
if ($("predictBeatMultiBtn")) $("predictBeatMultiBtn").addEventListener("click", predictBeatMultiBackend);
if ($("predictBeatMultiBtnWide")) $("predictBeatMultiBtnWide").addEventListener("click", predictBeatMultiBackend);
$("predictDatasetBtn").addEventListener("click", predictDataset);
$("predictMultiBackendBtn").addEventListener("click", predictMultiBackendDataset);
$("exportCsvBtn").addEventListener("click", exportCsv);
$("exportJsonBtn").addEventListener("click", exportJson);
$("importExportBtn").addEventListener("click", async () => {
  try { await importFpgaExport(); } catch (err) { alert(`Import error: ${err.message}`); }
});
$("uploadVerilogBtn").addEventListener("click", async () => {
  try { await uploadVerilogFiles(); } catch (err) { alert(`RTL/Verilog upload error: ${err.message}`); }
});
$("reloadModelsBtn").addEventListener("click", async () => {
  try { await reloadModels(); } catch (err) { alert(`Reload model error: ${err.message}`); }
});
$("refreshModelFilesBtn").addEventListener("click", async () => {
  try { await loadModelFileStatus(); } catch (err) { alert(`Refresh model status error: ${err.message}`); }
});

if ($("checkFpgaBtn")) {
  $("checkFpgaBtn").addEventListener("click", async () => {
    try { await checkFpgaConnection(); } catch (err) { alert(`Check FPGA error: ${err.message}`); }
  });
}
$("searchRecordsBtn").addEventListener("click", async () => {
  try { await loadRecords(); } catch (err) { alert(`Search error: ${err.message}`); }
});
$("refreshRecordsBtn").addEventListener("click", async () => {
  setValueIfExists("recordSearchInput", "");
  try { await loadRecords(); } catch (err) { alert(`Refresh error: ${err.message}`); }
});
$("indexBulkDatasetBtn").addEventListener("click", async () => {
  try { await indexBulkDataset(); } catch (err) { alert(`Index dataset error: ${err.message}`); }
});
$("refreshBulkStatusBtn").addEventListener("click", async () => {
  try { await loadBulkStatus(); await loadLabelRecordMap(); } catch (err) { alert(`Bulk status error: ${err.message}`); }
});
$("searchBulkSegmentsBtn").addEventListener("click", async () => {
  try { await searchBulkSegments(); } catch (err) { alert(`Search segments error: ${err.message}`); }
});
if ($("refreshLabelRecordsBtn")) {
  $("refreshLabelRecordsBtn").addEventListener("click", async () => {
    try { await loadLabelRecordMap(); } catch (err) { console.error(err); }
  });
}
window.addEventListener("resize", () => drawWaveform(currentSignal));

init().catch(err => {
  $("serverStatus").textContent = "server error";
  console.error(err);
});
