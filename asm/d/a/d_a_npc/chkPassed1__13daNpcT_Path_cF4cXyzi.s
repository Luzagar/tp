lbl_80146188:
/* 80146188  94 21 FF 60 */	stwu r1, -0xa0(r1)
/* 8014618C  7C 08 02 A6 */	mflr r0
/* 80146190  90 01 00 A4 */	stw r0, 0xa4(r1)
/* 80146194  39 61 00 A0 */	addi r11, r1, 0xa0
/* 80146198  48 21 C0 41 */	bl _savegpr_28
/* 8014619C  7C 7D 1B 78 */	mr r29, r3
/* 801461A0  7C 9E 23 78 */	mr r30, r4
/* 801461A4  7C BC 2B 78 */	mr r28, r5
/* 801461A8  A3 E3 00 1C */	lhz r31, 0x1c(r3)
/* 801461AC  B3 E1 00 08 */	sth r31, 8(r1)
/* 801461B0  B3 E1 00 0A */	sth r31, 0xa(r1)
/* 801461B4  80 63 00 00 */	lwz r3, 0(r3)
/* 801461B8  88 03 00 05 */	lbz r0, 5(r3)
/* 801461BC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 801461C0  41 82 00 54 */	beq lbl_80146214
/* 801461C4  A0 63 00 00 */	lhz r3, 0(r3)
/* 801461C8  7C 1C 18 00 */	cmpw r28, r3
/* 801461CC  40 82 00 48 */	bne lbl_80146214
/* 801461D0  38 81 00 0A */	addi r4, r1, 0xa
/* 801461D4  38 A0 00 01 */	li r5, 1
/* 801461D8  88 1D 00 20 */	lbz r0, 0x20(r29)
/* 801461DC  20 00 00 01 */	subfic r0, r0, 1
/* 801461E0  7C 00 00 34 */	cntlzw r0, r0
/* 801461E4  54 06 DE 3E */	rlwinm r6, r0, 0x1b, 0x18, 0x1f
/* 801461E8  4B FF F9 39 */	bl daNpcT_decIdx__FiRUsii
/* 801461EC  80 7D 00 00 */	lwz r3, 0(r29)
/* 801461F0  A0 63 00 00 */	lhz r3, 0(r3)
/* 801461F4  38 81 00 08 */	addi r4, r1, 8
/* 801461F8  38 A0 00 01 */	li r5, 1
/* 801461FC  88 1D 00 20 */	lbz r0, 0x20(r29)
/* 80146200  20 00 00 01 */	subfic r0, r0, 1
/* 80146204  7C 00 00 34 */	cntlzw r0, r0
/* 80146208  54 06 DE 3E */	rlwinm r6, r0, 0x1b, 0x18, 0x1f
/* 8014620C  4B FF F8 B9 */	bl daNpcT_incIdx__FiRUsii
/* 80146210  48 00 00 44 */	b lbl_80146254
lbl_80146214:
/* 80146214  7F 83 E3 78 */	mr r3, r28
/* 80146218  38 81 00 0A */	addi r4, r1, 0xa
/* 8014621C  38 A0 00 00 */	li r5, 0
/* 80146220  88 1D 00 20 */	lbz r0, 0x20(r29)
/* 80146224  20 00 00 01 */	subfic r0, r0, 1
/* 80146228  7C 00 00 34 */	cntlzw r0, r0
/* 8014622C  54 06 DE 3E */	rlwinm r6, r0, 0x1b, 0x18, 0x1f
/* 80146230  4B FF F8 F1 */	bl daNpcT_decIdx__FiRUsii
/* 80146234  7F 83 E3 78 */	mr r3, r28
/* 80146238  38 81 00 08 */	addi r4, r1, 8
/* 8014623C  38 A0 00 00 */	li r5, 0
/* 80146240  88 1D 00 20 */	lbz r0, 0x20(r29)
/* 80146244  20 00 00 01 */	subfic r0, r0, 1
/* 80146248  7C 00 00 34 */	cntlzw r0, r0
/* 8014624C  54 06 DE 3E */	rlwinm r6, r0, 0x1b, 0x18, 0x1f
/* 80146250  4B FF F8 75 */	bl daNpcT_incIdx__FiRUsii
lbl_80146254:
/* 80146254  80 7D 00 00 */	lwz r3, 0(r29)
/* 80146258  A0 E1 00 0A */	lhz r7, 0xa(r1)
/* 8014625C  80 C3 00 08 */	lwz r6, 8(r3)
/* 80146260  54 E0 23 36 */	rlwinm r0, r7, 4, 0xc, 0x1b
/* 80146264  7C 86 02 14 */	add r4, r6, r0
/* 80146268  80 64 00 04 */	lwz r3, 4(r4)
/* 8014626C  80 04 00 08 */	lwz r0, 8(r4)
/* 80146270  90 61 00 50 */	stw r3, 0x50(r1)
/* 80146274  90 01 00 54 */	stw r0, 0x54(r1)
/* 80146278  80 04 00 0C */	lwz r0, 0xc(r4)
/* 8014627C  90 01 00 58 */	stw r0, 0x58(r1)
/* 80146280  C0 01 00 50 */	lfs f0, 0x50(r1)
/* 80146284  D0 01 00 80 */	stfs f0, 0x80(r1)
/* 80146288  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 8014628C  D0 01 00 84 */	stfs f0, 0x84(r1)
/* 80146290  C0 01 00 58 */	lfs f0, 0x58(r1)
/* 80146294  D0 01 00 88 */	stfs f0, 0x88(r1)
/* 80146298  57 E5 04 3E */	clrlwi r5, r31, 0x10
/* 8014629C  57 E0 23 36 */	rlwinm r0, r31, 4, 0xc, 0x1b
/* 801462A0  7C 86 02 14 */	add r4, r6, r0
/* 801462A4  80 64 00 04 */	lwz r3, 4(r4)
/* 801462A8  80 04 00 08 */	lwz r0, 8(r4)
/* 801462AC  90 61 00 44 */	stw r3, 0x44(r1)
/* 801462B0  90 01 00 48 */	stw r0, 0x48(r1)
/* 801462B4  80 04 00 0C */	lwz r0, 0xc(r4)
/* 801462B8  90 01 00 4C */	stw r0, 0x4c(r1)
/* 801462BC  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 801462C0  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 801462C4  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 801462C8  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 801462CC  C0 01 00 4C */	lfs f0, 0x4c(r1)
/* 801462D0  D0 01 00 7C */	stfs f0, 0x7c(r1)
/* 801462D4  A0 01 00 08 */	lhz r0, 8(r1)
/* 801462D8  54 00 20 36 */	slwi r0, r0, 4
/* 801462DC  7C 86 02 14 */	add r4, r6, r0
/* 801462E0  80 64 00 04 */	lwz r3, 4(r4)
/* 801462E4  80 04 00 08 */	lwz r0, 8(r4)
/* 801462E8  90 61 00 38 */	stw r3, 0x38(r1)
/* 801462EC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 801462F0  80 04 00 0C */	lwz r0, 0xc(r4)
/* 801462F4  90 01 00 40 */	stw r0, 0x40(r1)
/* 801462F8  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 801462FC  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 80146300  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 80146304  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 80146308  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 8014630C  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 80146310  7C 07 28 40 */	cmplw r7, r5
/* 80146314  40 82 00 70 */	bne lbl_80146384
/* 80146318  C0 02 99 D8 */	lfs f0, lit_4116(r2)
/* 8014631C  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80146320  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 80146324  C0 02 99 EC */	lfs f0, lit_4513(r2)
/* 80146328  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 8014632C  38 61 00 68 */	addi r3, r1, 0x68
/* 80146330  38 81 00 74 */	addi r4, r1, 0x74
/* 80146334  48 12 A8 D1 */	bl cLib_targetAngleY__FPC3VecPC3Vec
/* 80146338  7C 64 1B 78 */	mr r4, r3
/* 8014633C  3C 60 80 3E */	lis r3, now__14mDoMtx_stack_c@ha /* 0x803DD470@ha */
/* 80146340  38 63 D4 70 */	addi r3, r3, now__14mDoMtx_stack_c@l /* 0x803DD470@l */
/* 80146344  4B EC 60 99 */	bl mDoMtx_YrotS__FPA4_fs
/* 80146348  3C 60 80 3E */	lis r3, now__14mDoMtx_stack_c@ha /* 0x803DD470@ha */
/* 8014634C  38 63 D4 70 */	addi r3, r3, now__14mDoMtx_stack_c@l /* 0x803DD470@l */
/* 80146350  38 81 00 5C */	addi r4, r1, 0x5c
/* 80146354  7C 85 23 78 */	mr r5, r4
/* 80146358  48 20 0A 15 */	bl PSMTXMultVec
/* 8014635C  38 61 00 2C */	addi r3, r1, 0x2c
/* 80146360  38 81 00 5C */	addi r4, r1, 0x5c
/* 80146364  38 A1 00 74 */	addi r5, r1, 0x74
/* 80146368  48 12 07 7D */	bl __pl__4cXyzCFRC3Vec
/* 8014636C  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80146370  D0 01 00 80 */	stfs f0, 0x80(r1)
/* 80146374  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80146378  D0 01 00 84 */	stfs f0, 0x84(r1)
/* 8014637C  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80146380  D0 01 00 88 */	stfs f0, 0x88(r1)
lbl_80146384:
/* 80146384  57 E3 04 3E */	clrlwi r3, r31, 0x10
/* 80146388  A0 01 00 08 */	lhz r0, 8(r1)
/* 8014638C  7C 03 00 40 */	cmplw r3, r0
/* 80146390  40 82 00 70 */	bne lbl_80146400
/* 80146394  C0 02 99 D8 */	lfs f0, lit_4116(r2)
/* 80146398  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 8014639C  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 801463A0  C0 02 99 EC */	lfs f0, lit_4513(r2)
/* 801463A4  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 801463A8  38 61 00 80 */	addi r3, r1, 0x80
/* 801463AC  38 81 00 74 */	addi r4, r1, 0x74
/* 801463B0  48 12 A8 55 */	bl cLib_targetAngleY__FPC3VecPC3Vec
/* 801463B4  7C 64 1B 78 */	mr r4, r3
/* 801463B8  3C 60 80 3E */	lis r3, now__14mDoMtx_stack_c@ha /* 0x803DD470@ha */
/* 801463BC  38 63 D4 70 */	addi r3, r3, now__14mDoMtx_stack_c@l /* 0x803DD470@l */
/* 801463C0  4B EC 60 1D */	bl mDoMtx_YrotS__FPA4_fs
/* 801463C4  3C 60 80 3E */	lis r3, now__14mDoMtx_stack_c@ha /* 0x803DD470@ha */
/* 801463C8  38 63 D4 70 */	addi r3, r3, now__14mDoMtx_stack_c@l /* 0x803DD470@l */
/* 801463CC  38 81 00 5C */	addi r4, r1, 0x5c
/* 801463D0  7C 85 23 78 */	mr r5, r4
/* 801463D4  48 20 09 99 */	bl PSMTXMultVec
/* 801463D8  38 61 00 20 */	addi r3, r1, 0x20
/* 801463DC  38 81 00 5C */	addi r4, r1, 0x5c
/* 801463E0  38 A1 00 74 */	addi r5, r1, 0x74
/* 801463E4  48 12 07 01 */	bl __pl__4cXyzCFRC3Vec
/* 801463E8  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 801463EC  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 801463F0  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 801463F4  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 801463F8  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 801463FC  D0 01 00 70 */	stfs f0, 0x70(r1)
lbl_80146400:
/* 80146400  C0 3E 00 00 */	lfs f1, 0(r30)
/* 80146404  C0 5E 00 08 */	lfs f2, 8(r30)
/* 80146408  C0 61 00 80 */	lfs f3, 0x80(r1)
/* 8014640C  C0 81 00 88 */	lfs f4, 0x88(r1)
/* 80146410  C0 A1 00 68 */	lfs f5, 0x68(r1)
/* 80146414  C0 C1 00 70 */	lfs f6, 0x70(r1)
/* 80146418  38 61 00 1C */	addi r3, r1, 0x1c
/* 8014641C  38 81 00 14 */	addi r4, r1, 0x14
/* 80146420  38 A1 00 0C */	addi r5, r1, 0xc
/* 80146424  48 12 22 09 */	bl cM3d_Len2dSqPntAndSegLine__FffffffPfPfPf
/* 80146428  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8014642C  41 82 00 90 */	beq lbl_801464BC
/* 80146430  C0 21 00 74 */	lfs f1, 0x74(r1)
/* 80146434  C0 41 00 7C */	lfs f2, 0x7c(r1)
/* 80146438  C0 61 00 80 */	lfs f3, 0x80(r1)
/* 8014643C  C0 81 00 88 */	lfs f4, 0x88(r1)
/* 80146440  C0 A1 00 68 */	lfs f5, 0x68(r1)
/* 80146444  C0 C1 00 70 */	lfs f6, 0x70(r1)
/* 80146448  38 61 00 18 */	addi r3, r1, 0x18
/* 8014644C  38 81 00 10 */	addi r4, r1, 0x10
/* 80146450  38 A1 00 0C */	addi r5, r1, 0xc
/* 80146454  48 12 21 D9 */	bl cM3d_Len2dSqPntAndSegLine__FffffffPfPfPf
/* 80146458  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8014645C  41 82 00 60 */	beq lbl_801464BC
/* 80146460  C0 21 00 68 */	lfs f1, 0x68(r1)
/* 80146464  C0 01 00 80 */	lfs f0, 0x80(r1)
/* 80146468  EC 21 00 28 */	fsubs f1, f1, f0
/* 8014646C  C0 41 00 70 */	lfs f2, 0x70(r1)
/* 80146470  C0 01 00 88 */	lfs f0, 0x88(r1)
/* 80146474  EC 42 00 28 */	fsubs f2, f2, f0
/* 80146478  48 12 11 FD */	bl cM_atan2s__Fff
/* 8014647C  7C 7D 1B 78 */	mr r29, r3
/* 80146480  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 80146484  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80146488  EC 21 00 28 */	fsubs f1, f1, f0
/* 8014648C  C0 41 00 10 */	lfs f2, 0x10(r1)
/* 80146490  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 80146494  EC 42 00 28 */	fsubs f2, f2, f0
/* 80146498  48 12 11 DD */	bl cM_atan2s__Fff
/* 8014649C  7C 03 E8 50 */	subf r0, r3, r29
/* 801464A0  7C 03 07 34 */	extsh r3, r0
/* 801464A4  48 21 EC 2D */	bl abs
/* 801464A8  54 60 04 3E */	clrlwi r0, r3, 0x10
/* 801464AC  28 00 40 00 */	cmplwi r0, 0x4000
/* 801464B0  40 81 00 0C */	ble lbl_801464BC
/* 801464B4  38 60 00 01 */	li r3, 1
/* 801464B8  48 00 00 08 */	b lbl_801464C0
lbl_801464BC:
/* 801464BC  38 60 00 00 */	li r3, 0
lbl_801464C0:
/* 801464C0  39 61 00 A0 */	addi r11, r1, 0xa0
/* 801464C4  48 21 BD 61 */	bl _restgpr_28
/* 801464C8  80 01 00 A4 */	lwz r0, 0xa4(r1)
/* 801464CC  7C 08 03 A6 */	mtlr r0
/* 801464D0  38 21 00 A0 */	addi r1, r1, 0xa0
/* 801464D4  4E 80 00 20 */	blr 
