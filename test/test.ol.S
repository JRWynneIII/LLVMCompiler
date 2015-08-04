	.text
	.abiversion 2
	.file	"mandelbrot.ol.ll"
	.section	.rodata.cst4,"aM",@progbits,4
	.align	2
.LCPI0_0:
	.long	3259498496              # float -50
.LCPI0_1:
	.long	1101004800              # float 20
.LCPI0_2:
	.long	3246391296              # float -16
.LCPI0_3:
	.long	1092616192              # float 10
.LCPI0_4:
	.long	1082130432              # float 4
	.text
	.globl	main
	.align	4
	.type	main,@function
main:                                   # @main
.Lfunc_begin0:
	.cfi_startproc
.Ltmp0:
	addis 2, 12, .TOC.-.Ltmp0@ha
	addi 2, 2, .TOC.-.Ltmp0@l
.Ltmp1:
	.localentry	main, .Ltmp1-.Ltmp0
# BB#0:                                 # %entry
	mfcr 12
	mflr 0
	std 0, 16(1)
	stw 12, 8(1)
	stdu 1, -320(1)
.Ltmp2:
	.cfi_def_cfa_offset 320
.Ltmp3:
	.cfi_offset lr, 16
.Ltmp4:
	.cfi_offset r19, -144
.Ltmp5:
	.cfi_offset r20, -136
.Ltmp6:
	.cfi_offset r21, -128
.Ltmp7:
	.cfi_offset r22, -120
.Ltmp8:
	.cfi_offset r23, -112
.Ltmp9:
	.cfi_offset r24, -104
.Ltmp10:
	.cfi_offset r25, -96
.Ltmp11:
	.cfi_offset r26, -88
.Ltmp12:
	.cfi_offset r27, -80
.Ltmp13:
	.cfi_offset r28, -72
.Ltmp14:
	.cfi_offset r29, -64
.Ltmp15:
	.cfi_offset r30, -56
.Ltmp16:
	.cfi_offset f27, -40
.Ltmp17:
	.cfi_offset f28, -32
.Ltmp18:
	.cfi_offset f29, -24
.Ltmp19:
	.cfi_offset f30, -16
.Ltmp20:
	.cfi_offset f31, -8
.Ltmp21:
	.cfi_offset cr2, 8
.Ltmp22:
	.cfi_offset cr3, 8
	addis 4, 2, .LCPI0_1@toc@ha
	addis 5, 2, .LCPI0_2@toc@ha
	addis 6, 2, .LCPI0_3@toc@ha
	li 3, 31
	addis 7, 2, .LCPI0_4@toc@ha
	addis 11, 2, .LCPI0_0@toc@ha
	stfd 27, 280(1)                 # 8-byte Folded Spill
	stfd 28, 288(1)                 # 8-byte Folded Spill
	stw 3, 116(1)
	addi 6, 6, .LCPI0_3@toc@l
	addi 12, 7, .LCPI0_4@toc@l
	addi 3, 11, .LCPI0_0@toc@l
	addi 4, 4, .LCPI0_1@toc@l
	addi 5, 5, .LCPI0_2@toc@l
	stfd 29, 296(1)                 # 8-byte Folded Spill
	std 21, 192(1)                  # 8-byte Folded Spill
	stfd 30, 304(1)                 # 8-byte Folded Spill
	lxsspx 30, 0, 4
	addi 21, 1, 96
	stfd 31, 312(1)                 # 8-byte Folded Spill
	lxsspx 31, 0, 3
	lxsspx 29, 0, 5
	lxsspx 28, 0, 6
	lxsspx 27, 0, 12
	std 22, 200(1)                  # 8-byte Folded Spill
	std 23, 208(1)                  # 8-byte Folded Spill
	addi 23, 1, 128
	addi 22, 1, 120
	std 24, 216(1)                  # 8-byte Folded Spill
	std 25, 224(1)                  # 8-byte Folded Spill
	addi 25, 1, 144
	addi 24, 1, 136
	std 26, 232(1)                  # 8-byte Folded Spill
	std 27, 240(1)                  # 8-byte Folded Spill
	addi 27, 1, 160
	addi 26, 1, 152
	std 28, 248(1)                  # 8-byte Folded Spill
	std 29, 256(1)                  # 8-byte Folded Spill
	li 29, 0
	li 28, 1
	std 30, 264(1)                  # 8-byte Folded Spill
	li 30, 0
	std 19, 176(1)                  # 8-byte Folded Spill
	std 20, 184(1)                  # 8-byte Folded Spill
	std 30, 96(1)
	std 30, 160(1)
	std 30, 152(1)
	std 30, 144(1)
	std 30, 136(1)
	std 30, 128(1)
	std 30, 120(1)
	stw 29, 108(1)
	stw 29, 168(1)
	stw 29, 112(1)
	.align	4
.LBB0_1:                                # %loop
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
                                        #       Child Loop BB0_3 Depth 3
	lwz 3, 168(1)
	stw 29, 172(1)
	addi 20, 3, 1
	cmpwi 2, 3, 32
	.align	4
.LBB0_2:                                # %loop17
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_3 Depth 3
	lwz 3, 172(1)
	lwz 4, 168(1)
	lwz 12, 172(1)
	std 30, 144(1)
	std 30, 136(1)
	std 30, 128(1)
	std 30, 120(1)
	mtvsrwa 0, 3
	addi 19, 12, 1
	cmpwi 3, 12, 85
	mtvsrwa 1, 4
	xscvsxddp 0, 0
	stw 28, 112(1)
	stw 29, 108(1)
	xscvsxddp 1, 1
	xsadddp 0, 0, 31
	xsadddp 1, 1, 29
	xsdivdp 0, 0, 30
	xsdivdp 1, 1, 28
	stxsdx 0, 0, 27
	stxsdx 1, 0, 26
	.align	4
.LBB0_3:                                # %loop35
                                        #   Parent Loop BB0_1 Depth=1
                                        #     Parent Loop BB0_2 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	lxsdx 0, 0, 25
	lxsdx 1, 0, 27
	lwz 4, 112(1)
	lxsdx 2, 0, 24
	lxsdx 3, 0, 26
	lxsdx 11, 0, 24
	lxsdx 12, 0, 25
	addi 3, 4, 1
	cmpwi	 4, 31
	xsadddp 1, 0, 1
	xsadddp 10, 2, 3
	xsmuldp 0, 0, 1
	xsmuldp 1, 12, 10
	xssubdp 0, 11, 0
	xsadddp 1, 1, 1
	xsmuldp 0, 11, 0
	stxsdx 1, 0, 23
	ori 2, 2, 0
	lxsdx 1, 0, 23
	stxsdx 0, 0, 22
	stxsdx 1, 0, 25
	ori 2, 2, 0
	lxsdx 0, 0, 22
	lxsdx 1, 0, 25
	xsmuldp 13, 0, 0
	stxsdx 0, 0, 24
	xsadddp 2, 1, 13
	xsmuldp 1, 1, 2
	fcmpu 1, 1, 27
	stxsdx 1, 0, 21
	crnor 20, 7, 4
	bc 12, 20, .LBB0_5
# BB#4:                                 # %then
                                        #   in Loop: Header=BB0_3 Depth=3
	stw 28, 108(1)
.LBB0_5:                                # %ifcont
                                        #   in Loop: Header=BB0_3 Depth=3
	stw 3, 112(1)
	bc 12, 0, .LBB0_3
# BB#6:                                 # %afterloop
                                        #   in Loop: Header=BB0_2 Depth=2
	lwz 3, 108(1)
	cmplwi	 3, 1
	bne	 0, .LBB0_8
# BB#7:                                 # %then73
                                        #   in Loop: Header=BB0_2 Depth=2
	li 3, 42
	bl putchar
	nop
.LBB0_8:                                # %ifcont74
                                        #   in Loop: Header=BB0_2 Depth=2
	lwz 3, 108(1)
	cmplwi	 3, 1
	beq	 0, .LBB0_10
# BB#9:                                 # %then79
                                        #   in Loop: Header=BB0_2 Depth=2
	li 3, 32
	bl putchar
	nop
.LBB0_10:                               # %ifcont81
                                        #   in Loop: Header=BB0_2 Depth=2
	stw 29, 108(1)
	stw 19, 172(1)
	bc 12, 12, .LBB0_2
# BB#11:                                # %afterloop83
                                        #   in Loop: Header=BB0_1 Depth=1
	li 3, 10
	bl putchar
	nop
	stw 20, 168(1)
	bc 12, 8, .LBB0_1
# BB#12:                                # %afterloop85
	li 3, 1
	lfd 31, 312(1)                  # 8-byte Folded Reload
	lfd 30, 304(1)                  # 8-byte Folded Reload
	ld 30, 264(1)                   # 8-byte Folded Reload
	ld 29, 256(1)                   # 8-byte Folded Reload
	lfd 29, 296(1)                  # 8-byte Folded Reload
	lfd 28, 288(1)                  # 8-byte Folded Reload
	ld 28, 248(1)                   # 8-byte Folded Reload
	ld 27, 240(1)                   # 8-byte Folded Reload
	lfd 27, 280(1)                  # 8-byte Folded Reload
	ld 26, 232(1)                   # 8-byte Folded Reload
	ld 25, 224(1)                   # 8-byte Folded Reload
	ld 24, 216(1)                   # 8-byte Folded Reload
	ld 23, 208(1)                   # 8-byte Folded Reload
	ld 22, 200(1)                   # 8-byte Folded Reload
	ld 21, 192(1)                   # 8-byte Folded Reload
	ld 20, 184(1)                   # 8-byte Folded Reload
	ld 19, 176(1)                   # 8-byte Folded Reload
	addi 1, 1, 320
	ld 0, 16(1)
	lwz 12, 8(1)
	mtocrf 32, 12
	mtlr 0
	mtocrf 16, 12
	blr
	.long	0
	.quad	0
.Lfunc_end0:
	.size	main, .Lfunc_end0-.Lfunc_begin0
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
