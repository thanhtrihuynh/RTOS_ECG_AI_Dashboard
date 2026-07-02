; ModuleID = 'T:/SoC/Project/RTOS/ecg_hls_vitis_clean_project_v6/ecg_fpga_top/ecg_fpga_top/hls/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: inaccessiblemem_or_argmemonly noinline willreturn
define void @apatb_ecg_fpga_top_ir(i16* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="320" "maxi" %beat_in_q12, i32* noalias nocapture nonnull "fpga.decayed.dim.hint"="1" "maxi" %pred_class, i16* noalias nocapture nonnull "fpga.decayed.dim.hint"="5" "maxi" %score5_q12) local_unnamed_addr #0 {
entry:
  %0 = bitcast i16* %beat_in_q12 to [320 x i16]*
  %beat_in_q12_copy = alloca [320 x i16], align 512
  %1 = bitcast i32* %pred_class to [1 x i32]*
  %pred_class_copy = alloca [1 x i32], align 512
  %2 = bitcast i16* %score5_q12 to [5 x i16]*
  %score5_q12_copy = alloca [5 x i16], align 512
  call fastcc void @copy_in([320 x i16]* nonnull %0, [320 x i16]* nonnull align 512 %beat_in_q12_copy, [1 x i32]* nonnull %1, [1 x i32]* nonnull align 512 %pred_class_copy, [5 x i16]* nonnull %2, [5 x i16]* nonnull align 512 %score5_q12_copy)
  call void @apatb_ecg_fpga_top_hw([320 x i16]* %beat_in_q12_copy, [1 x i32]* %pred_class_copy, [5 x i16]* %score5_q12_copy)
  call void @copy_back([320 x i16]* %0, [320 x i16]* %beat_in_q12_copy, [1 x i32]* %1, [1 x i32]* %pred_class_copy, [5 x i16]* %2, [5 x i16]* %score5_q12_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in([320 x i16]* noalias readonly, [320 x i16]* noalias align 512, [1 x i32]* noalias readonly, [1 x i32]* noalias align 512, [5 x i16]* noalias readonly, [5 x i16]* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a320i16([320 x i16]* align 512 %1, [320 x i16]* %0)
  call fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* align 512 %3, [1 x i32]* %2)
  call fastcc void @onebyonecpy_hls.p0a5i16([5 x i16]* align 512 %5, [5 x i16]* %4)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0a320i16([320 x i16]* noalias align 512 %dst, [320 x i16]* noalias readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq [320 x i16]* %dst, null
  %1 = icmp eq [320 x i16]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a320i16([320 x i16]* nonnull %dst, [320 x i16]* nonnull %src, i64 320)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a320i16([320 x i16]* %dst, [320 x i16]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [320 x i16]* %src, null
  %1 = icmp eq [320 x i16]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [320 x i16], [320 x i16]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [320 x i16], [320 x i16]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i16, i16* %src.addr, align 2
  store i16 %3, i16* %dst.addr, align 2
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* noalias align 512 %dst, [1 x i32]* noalias readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq [1 x i32]* %dst, null
  %1 = icmp eq [1 x i32]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a1i32([1 x i32]* nonnull %dst, [1 x i32]* nonnull %src, i64 1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a1i32([1 x i32]* %dst, [1 x i32]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [1 x i32]* %src, null
  %1 = icmp eq [1 x i32]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [1 x i32], [1 x i32]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [1 x i32], [1 x i32]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i32, i32* %src.addr, align 4
  store i32 %3, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0a5i16([5 x i16]* noalias align 512 %dst, [5 x i16]* noalias readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq [5 x i16]* %dst, null
  %1 = icmp eq [5 x i16]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a5i16([5 x i16]* nonnull %dst, [5 x i16]* nonnull %src, i64 5)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a5i16([5 x i16]* %dst, [5 x i16]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [5 x i16]* %src, null
  %1 = icmp eq [5 x i16]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [5 x i16], [5 x i16]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [5 x i16], [5 x i16]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i16, i16* %src.addr, align 2
  store i16 %3, i16* %dst.addr, align 2
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out([320 x i16]* noalias, [320 x i16]* noalias readonly align 512, [1 x i32]* noalias, [1 x i32]* noalias readonly align 512, [5 x i16]* noalias, [5 x i16]* noalias readonly align 512) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a320i16([320 x i16]* %0, [320 x i16]* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* %2, [1 x i32]* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0a5i16([5 x i16]* %4, [5 x i16]* align 512 %5)
  ret void
}

declare void @apatb_ecg_fpga_top_hw([320 x i16]*, [1 x i32]*, [5 x i16]*)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back([320 x i16]* noalias, [320 x i16]* noalias readonly align 512, [1 x i32]* noalias, [1 x i32]* noalias readonly align 512, [5 x i16]* noalias, [5 x i16]* noalias readonly align 512) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* %2, [1 x i32]* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0a5i16([5 x i16]* %4, [5 x i16]* align 512 %5)
  ret void
}

declare void @ecg_fpga_top_hw_stub(i16* noalias nocapture nonnull readonly, i32* noalias nocapture nonnull, i16* noalias nocapture nonnull)

define void @ecg_fpga_top_hw_stub_wrapper([320 x i16]*, [1 x i32]*, [5 x i16]*) #5 {
entry:
  call void @copy_out([320 x i16]* null, [320 x i16]* %0, [1 x i32]* null, [1 x i32]* %1, [5 x i16]* null, [5 x i16]* %2)
  %3 = bitcast [320 x i16]* %0 to i16*
  %4 = bitcast [1 x i32]* %1 to i32*
  %5 = bitcast [5 x i16]* %2 to i16*
  call void @ecg_fpga_top_hw_stub(i16* %3, i32* %4, i16* %5)
  call void @copy_in([320 x i16]* null, [320 x i16]* %0, [1 x i32]* null, [1 x i32]* %1, [5 x i16]* null, [5 x i16]* %2)
  ret void
}

attributes #0 = { inaccessiblemem_or_argmemonly noinline willreturn "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="arraycpy_hls" }
attributes #4 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1, !1}
!llvm.module.flags = !{!2, !3, !4}
!blackbox_cfg = !{!5}

!0 = !{!"AMD/Xilinx clang version 16.0.6"}
!1 = !{!"clang version 7.0.0 "}
!2 = !{i32 2, !"Dwarf Version", i32 4}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{}
