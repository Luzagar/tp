lbl_8060729C:
/* 8060729C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 806072A0  7C 08 02 A6 */	mflr r0
/* 806072A4  90 01 00 44 */	stw r0, 0x44(r1)
/* 806072A8  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 806072AC  F3 E1 00 38 */	psq_st f31, 56(r1), 0, 0 /* qr0 */
/* 806072B0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 806072B4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 806072B8  7C 7F 1B 78 */	mr r31, r3
/* 806072BC  3C 60 80 61 */	lis r3, lit_3928@ha /* 0x8060FDE0@ha */
/* 806072C0  3B C3 FD E0 */	addi r30, r3, lit_3928@l /* 0x8060FDE0@l */
/* 806072C4  80 1F 0A A4 */	lwz r0, 0xaa4(r31)
/* 806072C8  2C 00 00 00 */	cmpwi r0, 0
/* 806072CC  40 82 01 AC */	bne lbl_80607478
/* 806072D0  38 60 00 00 */	li r3, 0
/* 806072D4  38 00 00 14 */	li r0, 0x14
/* 806072D8  7C 09 03 A6 */	mtctr r0
lbl_806072DC:
/* 806072DC  38 03 09 90 */	addi r0, r3, 0x990
/* 806072E0  7C 1F 00 2E */	lwzx r0, r31, r0
/* 806072E4  2C 00 00 00 */	cmpwi r0, 0
/* 806072E8  40 82 00 14 */	bne lbl_806072FC
/* 806072EC  38 00 00 01 */	li r0, 1
/* 806072F0  7C 7F 1A 14 */	add r3, r31, r3
/* 806072F4  90 03 09 90 */	stw r0, 0x990(r3)
/* 806072F8  48 00 00 0C */	b lbl_80607304
lbl_806072FC:
/* 806072FC  38 63 00 04 */	addi r3, r3, 4
/* 80607300  42 00 FF DC */	bdnz lbl_806072DC
lbl_80607304:
/* 80607304  C3 FE 00 70 */	lfs f31, 0x70(r30)
/* 80607308  C0 3F 05 00 */	lfs f1, 0x500(r31)
/* 8060730C  C0 1F 04 F8 */	lfs f0, 0x4f8(r31)
/* 80607310  D0 01 00 0C */	stfs f0, 0xc(r1)
/* 80607314  C0 1E 00 04 */	lfs f0, 4(r30)
/* 80607318  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8060731C  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 80607320  38 61 00 0C */	addi r3, r1, 0xc
/* 80607324  4B D3 FE 15 */	bl PSVECSquareMag
/* 80607328  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8060732C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80607330  40 81 00 58 */	ble lbl_80607388
/* 80607334  FC 00 08 34 */	frsqrte f0, f1
/* 80607338  C8 9E 00 10 */	lfd f4, 0x10(r30)
/* 8060733C  FC 44 00 32 */	fmul f2, f4, f0
/* 80607340  C8 7E 00 18 */	lfd f3, 0x18(r30)
/* 80607344  FC 00 00 32 */	fmul f0, f0, f0
/* 80607348  FC 01 00 32 */	fmul f0, f1, f0
/* 8060734C  FC 03 00 28 */	fsub f0, f3, f0
/* 80607350  FC 02 00 32 */	fmul f0, f2, f0
/* 80607354  FC 44 00 32 */	fmul f2, f4, f0
/* 80607358  FC 00 00 32 */	fmul f0, f0, f0
/* 8060735C  FC 01 00 32 */	fmul f0, f1, f0
/* 80607360  FC 03 00 28 */	fsub f0, f3, f0
/* 80607364  FC 02 00 32 */	fmul f0, f2, f0
/* 80607368  FC 44 00 32 */	fmul f2, f4, f0
/* 8060736C  FC 00 00 32 */	fmul f0, f0, f0
/* 80607370  FC 01 00 32 */	fmul f0, f1, f0
/* 80607374  FC 03 00 28 */	fsub f0, f3, f0
/* 80607378  FC 02 00 32 */	fmul f0, f2, f0
/* 8060737C  FC 21 00 32 */	fmul f1, f1, f0
/* 80607380  FC 20 08 18 */	frsp f1, f1
/* 80607384  48 00 00 88 */	b lbl_8060740C
lbl_80607388:
/* 80607388  C8 1E 00 20 */	lfd f0, 0x20(r30)
/* 8060738C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80607390  40 80 00 10 */	bge lbl_806073A0
/* 80607394  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80607398  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
/* 8060739C  48 00 00 70 */	b lbl_8060740C
lbl_806073A0:
/* 806073A0  D0 21 00 08 */	stfs f1, 8(r1)
/* 806073A4  80 81 00 08 */	lwz r4, 8(r1)
/* 806073A8  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 806073AC  3C 00 7F 80 */	lis r0, 0x7f80
/* 806073B0  7C 03 00 00 */	cmpw r3, r0
/* 806073B4  41 82 00 14 */	beq lbl_806073C8
/* 806073B8  40 80 00 40 */	bge lbl_806073F8
/* 806073BC  2C 03 00 00 */	cmpwi r3, 0
/* 806073C0  41 82 00 20 */	beq lbl_806073E0
/* 806073C4  48 00 00 34 */	b lbl_806073F8
lbl_806073C8:
/* 806073C8  54 80 02 7F */	clrlwi. r0, r4, 9
/* 806073CC  41 82 00 0C */	beq lbl_806073D8
/* 806073D0  38 00 00 01 */	li r0, 1
/* 806073D4  48 00 00 28 */	b lbl_806073FC
lbl_806073D8:
/* 806073D8  38 00 00 02 */	li r0, 2
/* 806073DC  48 00 00 20 */	b lbl_806073FC
lbl_806073E0:
/* 806073E0  54 80 02 7F */	clrlwi. r0, r4, 9
/* 806073E4  41 82 00 0C */	beq lbl_806073F0
/* 806073E8  38 00 00 05 */	li r0, 5
/* 806073EC  48 00 00 10 */	b lbl_806073FC
lbl_806073F0:
/* 806073F0  38 00 00 03 */	li r0, 3
/* 806073F4  48 00 00 08 */	b lbl_806073FC
lbl_806073F8:
/* 806073F8  38 00 00 04 */	li r0, 4
lbl_806073FC:
/* 806073FC  2C 00 00 01 */	cmpwi r0, 1
/* 80607400  40 82 00 0C */	bne lbl_8060740C
/* 80607404  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80607408  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
lbl_8060740C:
/* 8060740C  C0 1E 00 60 */	lfs f0, 0x60(r30)
/* 80607410  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80607414  40 81 00 08 */	ble lbl_8060741C
/* 80607418  C3 FE 00 08 */	lfs f31, 8(r30)
lbl_8060741C:
/* 8060741C  4B C6 04 51 */	bl cM_rnd__Fv
/* 80607420  C0 1E 00 78 */	lfs f0, 0x78(r30)
/* 80607424  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80607428  40 80 00 2C */	bge lbl_80607454
/* 8060742C  C0 3E 00 48 */	lfs f1, 0x48(r30)
/* 80607430  4B C6 05 25 */	bl cM_rndF__Ff
/* 80607434  C0 1E 00 48 */	lfs f0, 0x48(r30)
/* 80607438  EC 00 08 2A */	fadds f0, f0, f1
/* 8060743C  EC 1F 00 32 */	fmuls f0, f31, f0
/* 80607440  FC 00 00 1E */	fctiwz f0, f0
/* 80607444  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80607448  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8060744C  90 1F 0A A4 */	stw r0, 0xaa4(r31)
/* 80607450  48 00 00 28 */	b lbl_80607478
lbl_80607454:
/* 80607454  C0 3E 00 60 */	lfs f1, 0x60(r30)
/* 80607458  4B C6 05 35 */	bl cM_rndFX__Ff
/* 8060745C  C0 1E 00 64 */	lfs f0, 0x64(r30)
/* 80607460  EC 00 08 2A */	fadds f0, f0, f1
/* 80607464  EC 1F 00 32 */	fmuls f0, f31, f0
/* 80607468  FC 00 00 1E */	fctiwz f0, f0
/* 8060746C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80607470  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80607474  90 1F 0A A4 */	stw r0, 0xaa4(r31)
lbl_80607478:
/* 80607478  E3 E1 00 38 */	psq_l f31, 56(r1), 0, 0 /* qr0 */
/* 8060747C  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 80607480  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80607484  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80607488  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8060748C  7C 08 03 A6 */	mtlr r0
/* 80607490  38 21 00 40 */	addi r1, r1, 0x40
/* 80607494  4E 80 00 20 */	blr 
