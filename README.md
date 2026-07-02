# Áp dụng HLS tutorial cho ECG dashboard

## 1. Copy file HLS sang PYNQ

Trên Windows PowerShell, vào thư mục dashboard:

```powershell
cd "D:\HCMUTE\HK II nam 3\RTOS\dashboard\ecg_ai_dashboard_pynq_z2"
scp .\fpga\hls\ecg_accel_hls.bit .\fpga\hls\ecg_accel_hls.hwh .\fpga\hls\pynq_ecg_hls_api_server.py xilinx@192.168.2.99:/home/xilinx/fpga/rtos/
```

Mật khẩu:

```text
xilinx
```

## 2. Trên PYNQ tạo thư mục nếu chưa có

```bash
mkdir -p /home/xilinx/fpga/rtos
cd /home/xilinx/fpga/rtos
ls -lh
```

Cần có:

```text
ecg_accel_hls.bit
ecg_accel_hls.hwh
pynq_ecg_hls_api_server.py
```

## 3. Đặt IP theo tutorial nếu ping chưa được

Trên PYNQ:

```bash
sudo ip link set eth0 up
sudo ip addr flush dev eth0
sudo ip addr add 192.168.2.99/24 dev eth0
ip a
```

Trên Windows, card Ethernet nên là:

```text
IPv4 Address: 192.168.2.1
Subnet Mask: 255.255.255.0
```

Test từ Windows:

```powershell
ping 192.168.2.99
```

## 4. Chạy PYNQ HLS API server

Trên PYNQ:

```bash
cd /home/xilinx/fpga/rtos
rm -rf __pycache__
sudo -E python3 pynq_ecg_hls_api_server.py
```

Để nguyên cửa sổ này, không tắt.

## 5. Test API từ Windows

Mở PowerShell khác:

```powershell
curl.exe http://192.168.2.99:8000/health
```

Nếu đúng sẽ có:

```json
{"ok": true, "overlay_loaded": true, "ip_name": "ecg_fpga_top_0"}
```

## 6. Chạy dashboard trên Windows

```powershell

Mở PowerShell và chạy:
cd "D:\HCMUTE\HK II nam 3\RTOS\dashboard\ecg_ai_dashboard_pynq_z2 "

Tạo virtual environment:
py -3.12 -m venv .venv

Kích hoạt .venv:
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\.venv\Scripts\Activate.ps1

Cài lại thư viện, ép NumPy bản ổn định:
python -m pip install --upgrade pip setuptools wheel
python -m pip cache purge
python -m pip install numpy==1.26.4
python -m pip install fastapi uvicorn pandas requests python-multipart wfdb

Cài thư viện dashboard:
python -m pip install --upgrade pip
python -m pip install -r requirements.txt
python -m pip install -r requirements-keras.txt

Trước khi chạy dashboard, set địa chỉ PYNQ API:
$env:PYNQ_HLS_URL="http://192.168.2.99:8000"

Chạy dashboard trên Windows:
python -m uvicorn backend.app:app --host 127.0.0.1 --port 8080

```

Mở trình duyệt:

```text
http://127.0.0.1:8080
```

Trong dashboard bấm `Check FPGA`. Nếu đúng sẽ hiện remote API sẵn sàng.

## 7. Chạy predict

Chọn backend:

```text
FPGA HLS Q4.12
```

Sau đó bấm:

```text
Predict beat
```

hoặc:

```text
Predict multi-backend
```

Kết quả FPGA HLS được PYNQ-Z2 suy luận và trả về dashboard Windows.
