lbl_807480A4:
/* 807480A4  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 807480A8  7C 08 02 A6 */	mflr r0
/* 807480AC  90 01 00 C4 */	stw r0, 0xc4(r1)
/* 807480B0  39 61 00 C0 */	addi r11, r1, 0xc0
/* 807480B4  4B C1 A1 29 */	bl _savegpr_29
/* 807480B8  7C 7D 1B 78 */	mr r29, r3
/* 807480BC  3C 80 80 75 */	lis r4, lit_3910@ha /* 0x8074BF3C@ha */
/* 807480C0  3B E4 BF 3C */	addi r31, r4, lit_3910@l /* 0x8074BF3C@l */
/* 807480C4  3C 80 80 40 */	lis r4, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 807480C8  38 84 61 C0 */	addi r4, r4, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 807480CC  83 C4 5D AC */	lwz r30, 0x5dac(r4)
/* 807480D0  88 03 06 11 */	lbz r0, 0x611(r3)
/* 807480D4  2C 00 00 02 */	cmpwi r0, 2
/* 807480D8  41 82 05 9C */	beq lbl_80748674
/* 807480DC  40 80 00 14 */	bge lbl_807480F0
/* 807480E0  2C 00 00 00 */	cmpwi r0, 0
/* 807480E4  41 82 00 18 */	beq lbl_807480FC
/* 807480E8  40 80 03 A4 */	bge lbl_8074848C
/* 807480EC  48 00 08 60 */	b lbl_8074894C
lbl_807480F0:
/* 807480F0  2C 00 00 04 */	cmpwi r0, 4
/* 807480F4  40 80 08 58 */	bge lbl_8074894C
/* 807480F8  48 00 08 34 */	b lbl_8074892C
lbl_807480FC:
/* 807480FC  80 7D 07 04 */	lwz r3, 0x704(r29)
/* 80748100  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 80748104  C0 1F 01 D0 */	lfs f0, 0x1d0(r31)
/* 80748108  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8074810C  40 80 00 78 */	bge lbl_80748184
/* 80748110  80 1D 06 1C */	lwz r0, 0x61c(r29)
/* 80748114  2C 00 00 0B */	cmpwi r0, 0xb
/* 80748118  40 82 00 6C */	bne lbl_80748184
/* 8074811C  80 63 00 04 */	lwz r3, 4(r3)
/* 80748120  80 63 00 84 */	lwz r3, 0x84(r3)
/* 80748124  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80748128  38 63 00 30 */	addi r3, r3, 0x30
/* 8074812C  3C 80 80 45 */	lis r4, calc_mtx@ha /* 0x80450768@ha */
/* 80748130  38 84 07 68 */	addi r4, r4, calc_mtx@l /* 0x80450768@l */
/* 80748134  80 84 00 00 */	lwz r4, 0(r4)
/* 80748138  4B BF E3 79 */	bl PSMTXCopy
/* 8074813C  C0 3F 00 04 */	lfs f1, 4(r31)
/* 80748140  D0 21 00 8C */	stfs f1, 0x8c(r1)
/* 80748144  C0 1F 01 48 */	lfs f0, 0x148(r31)
/* 80748148  D0 01 00 90 */	stfs f0, 0x90(r1)
/* 8074814C  D0 21 00 94 */	stfs f1, 0x94(r1)
/* 80748150  38 61 00 8C */	addi r3, r1, 0x8c
/* 80748154  7C 64 1B 78 */	mr r4, r3
/* 80748158  4B B2 8D 95 */	bl MtxPosition__FP4cXyzP4cXyz
/* 8074815C  C0 3D 04 D0 */	lfs f1, 0x4d0(r29)
/* 80748160  D0 21 00 8C */	stfs f1, 0x8c(r1)
/* 80748164  C0 1D 04 D8 */	lfs f0, 0x4d8(r29)
/* 80748168  D0 01 00 94 */	stfs f0, 0x94(r1)
/* 8074816C  D0 3D 06 A4 */	stfs f1, 0x6a4(r29)
/* 80748170  C0 01 00 90 */	lfs f0, 0x90(r1)
/* 80748174  D0 1D 06 A8 */	stfs f0, 0x6a8(r29)
/* 80748178  C0 01 00 94 */	lfs f0, 0x94(r1)
/* 8074817C  D0 1D 06 AC */	stfs f0, 0x6ac(r29)
/* 80748180  48 00 01 7C */	b lbl_807482FC
lbl_80748184:
/* 80748184  C0 5D 06 AC */	lfs f2, 0x6ac(r29)
/* 80748188  C0 1D 06 A4 */	lfs f0, 0x6a4(r29)
/* 8074818C  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80748190  C0 3F 00 04 */	lfs f1, 4(r31)
/* 80748194  D0 21 00 60 */	stfs f1, 0x60(r1)
/* 80748198  D0 41 00 64 */	stfs f2, 0x64(r1)
/* 8074819C  C0 5D 06 A0 */	lfs f2, 0x6a0(r29)
/* 807481A0  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807481A4  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 807481A8  D0 21 00 6C */	stfs f1, 0x6c(r1)
/* 807481AC  D0 41 00 70 */	stfs f2, 0x70(r1)
/* 807481B0  38 61 00 5C */	addi r3, r1, 0x5c
/* 807481B4  38 81 00 68 */	addi r4, r1, 0x68
/* 807481B8  4B BF F1 E5 */	bl PSVECSquareDistance
/* 807481BC  C0 1F 00 04 */	lfs f0, 4(r31)
/* 807481C0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 807481C4  40 81 00 58 */	ble lbl_8074821C
/* 807481C8  FC 00 08 34 */	frsqrte f0, f1
/* 807481CC  C8 9F 00 10 */	lfd f4, 0x10(r31)
/* 807481D0  FC 44 00 32 */	fmul f2, f4, f0
/* 807481D4  C8 7F 00 18 */	lfd f3, 0x18(r31)
/* 807481D8  FC 00 00 32 */	fmul f0, f0, f0
/* 807481DC  FC 01 00 32 */	fmul f0, f1, f0
/* 807481E0  FC 03 00 28 */	fsub f0, f3, f0
/* 807481E4  FC 02 00 32 */	fmul f0, f2, f0
/* 807481E8  FC 44 00 32 */	fmul f2, f4, f0
/* 807481EC  FC 00 00 32 */	fmul f0, f0, f0
/* 807481F0  FC 01 00 32 */	fmul f0, f1, f0
/* 807481F4  FC 03 00 28 */	fsub f0, f3, f0
/* 807481F8  FC 02 00 32 */	fmul f0, f2, f0
/* 807481FC  FC 44 00 32 */	fmul f2, f4, f0
/* 80748200  FC 00 00 32 */	fmul f0, f0, f0
/* 80748204  FC 01 00 32 */	fmul f0, f1, f0
/* 80748208  FC 03 00 28 */	fsub f0, f3, f0
/* 8074820C  FC 02 00 32 */	fmul f0, f2, f0
/* 80748210  FC 21 00 32 */	fmul f1, f1, f0
/* 80748214  FC 20 08 18 */	frsp f1, f1
/* 80748218  48 00 00 88 */	b lbl_807482A0
lbl_8074821C:
/* 8074821C  C8 1F 00 20 */	lfd f0, 0x20(r31)
/* 80748220  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80748224  40 80 00 10 */	bge lbl_80748234
/* 80748228  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 8074822C  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
/* 80748230  48 00 00 70 */	b lbl_807482A0
lbl_80748234:
/* 80748234  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 80748238  80 81 00 28 */	lwz r4, 0x28(r1)
/* 8074823C  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 80748240  3C 00 7F 80 */	lis r0, 0x7f80
/* 80748244  7C 03 00 00 */	cmpw r3, r0
/* 80748248  41 82 00 14 */	beq lbl_8074825C
/* 8074824C  40 80 00 40 */	bge lbl_8074828C
/* 80748250  2C 03 00 00 */	cmpwi r3, 0
/* 80748254  41 82 00 20 */	beq lbl_80748274
/* 80748258  48 00 00 34 */	b lbl_8074828C
lbl_8074825C:
/* 8074825C  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80748260  41 82 00 0C */	beq lbl_8074826C
/* 80748264  38 00 00 01 */	li r0, 1
/* 80748268  48 00 00 28 */	b lbl_80748290
lbl_8074826C:
/* 8074826C  38 00 00 02 */	li r0, 2
/* 80748270  48 00 00 20 */	b lbl_80748290
lbl_80748274:
/* 80748274  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80748278  41 82 00 0C */	beq lbl_80748284
/* 8074827C  38 00 00 05 */	li r0, 5
/* 80748280  48 00 00 10 */	b lbl_80748290
lbl_80748284:
/* 80748284  38 00 00 03 */	li r0, 3
/* 80748288  48 00 00 08 */	b lbl_80748290
lbl_8074828C:
/* 8074828C  38 00 00 04 */	li r0, 4
lbl_80748290:
/* 80748290  2C 00 00 01 */	cmpwi r0, 1
/* 80748294  40 82 00 0C */	bne lbl_807482A0
/* 80748298  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 8074829C  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
lbl_807482A0:
/* 807482A0  C0 1F 00 04 */	lfs f0, 4(r31)
/* 807482A4  D0 01 00 8C */	stfs f0, 0x8c(r1)
/* 807482A8  D0 01 00 90 */	stfs f0, 0x90(r1)
/* 807482AC  C0 1F 00 34 */	lfs f0, 0x34(r31)
/* 807482B0  EC 00 08 2A */	fadds f0, f0, f1
/* 807482B4  D0 01 00 94 */	stfs f0, 0x94(r1)
/* 807482B8  C0 5D 06 A0 */	lfs f2, 0x6a0(r29)
/* 807482BC  C0 3D 04 D4 */	lfs f1, 0x4d4(r29)
/* 807482C0  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807482C4  D0 01 00 98 */	stfs f0, 0x98(r1)
/* 807482C8  D0 21 00 9C */	stfs f1, 0x9c(r1)
/* 807482CC  D0 41 00 A0 */	stfs f2, 0xa0(r1)
/* 807482D0  38 7D 06 A4 */	addi r3, r29, 0x6a4
/* 807482D4  38 81 00 98 */	addi r4, r1, 0x98
/* 807482D8  A8 BD 04 E6 */	lha r5, 0x4e6(r29)
/* 807482DC  3C A5 00 01 */	addis r5, r5, 1
/* 807482E0  38 05 80 00 */	addi r0, r5, -32768
/* 807482E4  7C 05 07 34 */	extsh r5, r0
/* 807482E8  38 C1 00 8C */	addi r6, r1, 0x8c
/* 807482EC  4B B2 8A D5 */	bl cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz
/* 807482F0  A8 7D 04 E6 */	lha r3, 0x4e6(r29)
/* 807482F4  38 03 00 40 */	addi r0, r3, 0x40
/* 807482F8  B0 1D 04 E6 */	sth r0, 0x4e6(r29)
lbl_807482FC:
/* 807482FC  A8 1D 04 E6 */	lha r0, 0x4e6(r29)
/* 80748300  B0 1D 06 02 */	sth r0, 0x602(r29)
/* 80748304  80 9D 07 04 */	lwz r4, 0x704(r29)
/* 80748308  C0 24 00 1C */	lfs f1, 0x1c(r4)
/* 8074830C  C0 1F 01 D4 */	lfs f0, 0x1d4(r31)
/* 80748310  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 80748314  40 82 00 5C */	bne lbl_80748370
/* 80748318  80 1D 06 1C */	lwz r0, 0x61c(r29)
/* 8074831C  2C 00 00 0B */	cmpwi r0, 0xb
/* 80748320  40 82 00 50 */	bne lbl_80748370
/* 80748324  C0 3D 04 D4 */	lfs f1, 0x4d4(r29)
/* 80748328  C0 1F 01 D8 */	lfs f0, 0x1d8(r31)
/* 8074832C  EC 01 00 2A */	fadds f0, f1, f0
/* 80748330  D0 1D 04 D4 */	stfs f0, 0x4d4(r29)
/* 80748334  C0 1D 04 D0 */	lfs f0, 0x4d0(r29)
/* 80748338  D0 1D 04 BC */	stfs f0, 0x4bc(r29)
/* 8074833C  C0 1D 04 D4 */	lfs f0, 0x4d4(r29)
/* 80748340  D0 1D 04 C0 */	stfs f0, 0x4c0(r29)
/* 80748344  C0 1D 04 D8 */	lfs f0, 0x4d8(r29)
/* 80748348  D0 1D 04 C4 */	stfs f0, 0x4c4(r29)
/* 8074834C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80748350  D0 1D 05 30 */	stfs f0, 0x530(r29)
/* 80748354  38 00 00 0A */	li r0, 0xa
/* 80748358  B0 1D 06 24 */	sth r0, 0x624(r29)
/* 8074835C  38 7D 06 A4 */	addi r3, r29, 0x6a4
/* 80748360  38 9D 06 B0 */	addi r4, r29, 0x6b0
/* 80748364  4B B2 88 A1 */	bl cLib_targetAngleY__FPC3VecPC3Vec
/* 80748368  B0 7D 04 E6 */	sth r3, 0x4e6(r29)
/* 8074836C  48 00 00 9C */	b lbl_80748408
lbl_80748370:
/* 80748370  38 60 00 01 */	li r3, 1
/* 80748374  88 04 00 11 */	lbz r0, 0x11(r4)
/* 80748378  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8074837C  40 82 00 18 */	bne lbl_80748394
/* 80748380  C0 3F 00 04 */	lfs f1, 4(r31)
/* 80748384  C0 04 00 18 */	lfs f0, 0x18(r4)
/* 80748388  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8074838C  41 82 00 08 */	beq lbl_80748394
/* 80748390  38 60 00 00 */	li r3, 0
lbl_80748394:
/* 80748394  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80748398  41 82 00 70 */	beq lbl_80748408
/* 8074839C  80 1D 06 1C */	lwz r0, 0x61c(r29)
/* 807483A0  2C 00 00 0B */	cmpwi r0, 0xb
/* 807483A4  40 82 00 64 */	bne lbl_80748408
/* 807483A8  A8 1D 06 24 */	lha r0, 0x624(r29)
/* 807483AC  2C 00 00 00 */	cmpwi r0, 0
/* 807483B0  40 82 00 58 */	bne lbl_80748408
/* 807483B4  38 00 00 64 */	li r0, 0x64
/* 807483B8  B0 1D 06 24 */	sth r0, 0x624(r29)
/* 807483BC  88 9D 06 1B */	lbz r4, 0x61b(r29)
/* 807483C0  28 04 00 FF */	cmplwi r4, 0xff
/* 807483C4  41 82 00 38 */	beq lbl_807483FC
/* 807483C8  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 807483CC  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 807483D0  88 1D 04 E2 */	lbz r0, 0x4e2(r29)
/* 807483D4  7C 05 07 74 */	extsb r5, r0
/* 807483D8  4B 8E CF 89 */	bl isSwitch__10dSv_info_cCFii
/* 807483DC  2C 03 00 00 */	cmpwi r3, 0
/* 807483E0  40 82 00 1C */	bne lbl_807483FC
/* 807483E4  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 807483E8  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 807483EC  88 9D 06 1B */	lbz r4, 0x61b(r29)
/* 807483F0  88 1D 04 E2 */	lbz r0, 0x4e2(r29)
/* 807483F4  7C 05 07 74 */	extsb r5, r0
/* 807483F8  4B 8E CE 09 */	bl onSwitch__10dSv_info_cFii
lbl_807483FC:
/* 807483FC  88 7D 06 11 */	lbz r3, 0x611(r29)
/* 80748400  38 03 00 01 */	addi r0, r3, 1
/* 80748404  98 1D 06 11 */	stb r0, 0x611(r29)
lbl_80748408:
/* 80748408  80 7D 07 04 */	lwz r3, 0x704(r29)
/* 8074840C  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 80748410  C0 1F 00 3C */	lfs f0, 0x3c(r31)
/* 80748414  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80748418  40 81 00 60 */	ble lbl_80748478
/* 8074841C  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 80748420  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 80748424  80 63 5D 3C */	lwz r3, 0x5d3c(r3)
/* 80748428  38 00 00 FF */	li r0, 0xff
/* 8074842C  90 01 00 08 */	stw r0, 8(r1)
/* 80748430  38 80 00 00 */	li r4, 0
/* 80748434  90 81 00 0C */	stw r4, 0xc(r1)
/* 80748438  38 00 FF FF */	li r0, -1
/* 8074843C  90 01 00 10 */	stw r0, 0x10(r1)
/* 80748440  90 81 00 14 */	stw r4, 0x14(r1)
/* 80748444  90 81 00 18 */	stw r4, 0x18(r1)
/* 80748448  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8074844C  80 9D 06 28 */	lwz r4, 0x628(r29)
/* 80748450  38 A0 00 00 */	li r5, 0
/* 80748454  3C C0 00 01 */	lis r6, 0x0001 /* 0x0000880C@ha */
/* 80748458  38 C6 88 0C */	addi r6, r6, 0x880C /* 0x0000880C@l */
/* 8074845C  38 E1 00 8C */	addi r7, r1, 0x8c
/* 80748460  39 1D 01 0C */	addi r8, r29, 0x10c
/* 80748464  39 3D 04 DC */	addi r9, r29, 0x4dc
/* 80748468  39 5D 04 EC */	addi r10, r29, 0x4ec
/* 8074846C  C0 3F 00 08 */	lfs f1, 8(r31)
/* 80748470  4B 90 50 5D */	bl set__13dPa_control_cFUlUcUsPC4cXyzPC12dKy_tevstr_cPC5csXyzPC4cXyzUcP18dPa_levelEcallBackScPC8_GXColorPC8_GXColorPC4cXyzf
/* 80748474  90 7D 06 28 */	stw r3, 0x628(r29)
lbl_80748478:
/* 80748478  7F A3 EB 78 */	mr r3, r29
/* 8074847C  C0 3F 01 CC */	lfs f1, 0x1cc(r31)
/* 80748480  C0 5F 01 DC */	lfs f2, 0x1dc(r31)
/* 80748484  4B FF B0 A1 */	bl SetMoveCam__8daE_PM_cFff
/* 80748488  48 00 04 C4 */	b lbl_8074894C
lbl_8074848C:
/* 8074848C  A8 7D 04 E6 */	lha r3, 0x4e6(r29)
/* 80748490  38 03 00 40 */	addi r0, r3, 0x40
/* 80748494  B0 1D 04 E6 */	sth r0, 0x4e6(r29)
/* 80748498  C0 5D 06 AC */	lfs f2, 0x6ac(r29)
/* 8074849C  C0 1D 06 A4 */	lfs f0, 0x6a4(r29)
/* 807484A0  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 807484A4  C0 3F 00 04 */	lfs f1, 4(r31)
/* 807484A8  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 807484AC  D0 41 00 4C */	stfs f2, 0x4c(r1)
/* 807484B0  C0 5D 06 A0 */	lfs f2, 0x6a0(r29)
/* 807484B4  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807484B8  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 807484BC  D0 21 00 54 */	stfs f1, 0x54(r1)
/* 807484C0  D0 41 00 58 */	stfs f2, 0x58(r1)
/* 807484C4  38 61 00 44 */	addi r3, r1, 0x44
/* 807484C8  38 81 00 50 */	addi r4, r1, 0x50
/* 807484CC  4B BF EE D1 */	bl PSVECSquareDistance
/* 807484D0  C0 1F 00 04 */	lfs f0, 4(r31)
/* 807484D4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 807484D8  40 81 00 58 */	ble lbl_80748530
/* 807484DC  FC 00 08 34 */	frsqrte f0, f1
/* 807484E0  C8 9F 00 10 */	lfd f4, 0x10(r31)
/* 807484E4  FC 44 00 32 */	fmul f2, f4, f0
/* 807484E8  C8 7F 00 18 */	lfd f3, 0x18(r31)
/* 807484EC  FC 00 00 32 */	fmul f0, f0, f0
/* 807484F0  FC 01 00 32 */	fmul f0, f1, f0
/* 807484F4  FC 03 00 28 */	fsub f0, f3, f0
/* 807484F8  FC 02 00 32 */	fmul f0, f2, f0
/* 807484FC  FC 44 00 32 */	fmul f2, f4, f0
/* 80748500  FC 00 00 32 */	fmul f0, f0, f0
/* 80748504  FC 01 00 32 */	fmul f0, f1, f0
/* 80748508  FC 03 00 28 */	fsub f0, f3, f0
/* 8074850C  FC 02 00 32 */	fmul f0, f2, f0
/* 80748510  FC 44 00 32 */	fmul f2, f4, f0
/* 80748514  FC 00 00 32 */	fmul f0, f0, f0
/* 80748518  FC 01 00 32 */	fmul f0, f1, f0
/* 8074851C  FC 03 00 28 */	fsub f0, f3, f0
/* 80748520  FC 02 00 32 */	fmul f0, f2, f0
/* 80748524  FC 21 00 32 */	fmul f1, f1, f0
/* 80748528  FC 20 08 18 */	frsp f1, f1
/* 8074852C  48 00 00 88 */	b lbl_807485B4
lbl_80748530:
/* 80748530  C8 1F 00 20 */	lfd f0, 0x20(r31)
/* 80748534  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80748538  40 80 00 10 */	bge lbl_80748548
/* 8074853C  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80748540  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
/* 80748544  48 00 00 70 */	b lbl_807485B4
lbl_80748548:
/* 80748548  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 8074854C  80 81 00 24 */	lwz r4, 0x24(r1)
/* 80748550  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 80748554  3C 00 7F 80 */	lis r0, 0x7f80
/* 80748558  7C 03 00 00 */	cmpw r3, r0
/* 8074855C  41 82 00 14 */	beq lbl_80748570
/* 80748560  40 80 00 40 */	bge lbl_807485A0
/* 80748564  2C 03 00 00 */	cmpwi r3, 0
/* 80748568  41 82 00 20 */	beq lbl_80748588
/* 8074856C  48 00 00 34 */	b lbl_807485A0
lbl_80748570:
/* 80748570  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80748574  41 82 00 0C */	beq lbl_80748580
/* 80748578  38 00 00 01 */	li r0, 1
/* 8074857C  48 00 00 28 */	b lbl_807485A4
lbl_80748580:
/* 80748580  38 00 00 02 */	li r0, 2
/* 80748584  48 00 00 20 */	b lbl_807485A4
lbl_80748588:
/* 80748588  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8074858C  41 82 00 0C */	beq lbl_80748598
/* 80748590  38 00 00 05 */	li r0, 5
/* 80748594  48 00 00 10 */	b lbl_807485A4
lbl_80748598:
/* 80748598  38 00 00 03 */	li r0, 3
/* 8074859C  48 00 00 08 */	b lbl_807485A4
lbl_807485A0:
/* 807485A0  38 00 00 04 */	li r0, 4
lbl_807485A4:
/* 807485A4  2C 00 00 01 */	cmpwi r0, 1
/* 807485A8  40 82 00 0C */	bne lbl_807485B4
/* 807485AC  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 807485B0  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
lbl_807485B4:
/* 807485B4  C0 1F 00 04 */	lfs f0, 4(r31)
/* 807485B8  D0 01 00 8C */	stfs f0, 0x8c(r1)
/* 807485BC  D0 01 00 90 */	stfs f0, 0x90(r1)
/* 807485C0  C0 1F 00 34 */	lfs f0, 0x34(r31)
/* 807485C4  EC 00 08 2A */	fadds f0, f0, f1
/* 807485C8  D0 01 00 94 */	stfs f0, 0x94(r1)
/* 807485CC  C0 5D 06 A0 */	lfs f2, 0x6a0(r29)
/* 807485D0  C0 3D 06 A8 */	lfs f1, 0x6a8(r29)
/* 807485D4  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807485D8  D0 01 00 98 */	stfs f0, 0x98(r1)
/* 807485DC  D0 21 00 9C */	stfs f1, 0x9c(r1)
/* 807485E0  D0 41 00 A0 */	stfs f2, 0xa0(r1)
/* 807485E4  38 7D 06 A4 */	addi r3, r29, 0x6a4
/* 807485E8  38 81 00 98 */	addi r4, r1, 0x98
/* 807485EC  A8 BD 04 E6 */	lha r5, 0x4e6(r29)
/* 807485F0  3C A5 00 01 */	addis r5, r5, 1
/* 807485F4  38 05 80 00 */	addi r0, r5, -32768
/* 807485F8  7C 05 07 34 */	extsh r5, r0
/* 807485FC  38 C1 00 8C */	addi r6, r1, 0x8c
/* 80748600  4B B2 87 C1 */	bl cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz
/* 80748604  A8 1D 06 24 */	lha r0, 0x624(r29)
/* 80748608  2C 00 00 00 */	cmpwi r0, 0
/* 8074860C  40 82 00 54 */	bne lbl_80748660
/* 80748610  38 60 00 00 */	li r3, 0
/* 80748614  4B 8E 43 69 */	bl getLayerNo__14dComIfG_play_cFi
/* 80748618  2C 03 00 02 */	cmpwi r3, 2
/* 8074861C  40 82 00 20 */	bne lbl_8074863C
/* 80748620  38 7D 06 3C */	addi r3, r29, 0x63c
/* 80748624  7F A4 EB 78 */	mr r4, r29
/* 80748628  38 A0 00 6E */	li r5, 0x6e
/* 8074862C  38 C0 00 00 */	li r6, 0
/* 80748630  38 E0 00 00 */	li r7, 0
/* 80748634  4B B0 19 5D */	bl init__10dMsgFlow_cFP10fopAc_ac_ciiPP10fopAc_ac_c
/* 80748638  48 00 00 1C */	b lbl_80748654
lbl_8074863C:
/* 8074863C  38 7D 06 3C */	addi r3, r29, 0x63c
/* 80748640  7F A4 EB 78 */	mr r4, r29
/* 80748644  38 A0 00 6F */	li r5, 0x6f
/* 80748648  38 C0 00 00 */	li r6, 0
/* 8074864C  38 E0 00 00 */	li r7, 0
/* 80748650  4B B0 19 41 */	bl init__10dMsgFlow_cFP10fopAc_ac_ciiPP10fopAc_ac_c
lbl_80748654:
/* 80748654  88 7D 06 11 */	lbz r3, 0x611(r29)
/* 80748658  38 03 00 01 */	addi r0, r3, 1
/* 8074865C  98 1D 06 11 */	stb r0, 0x611(r29)
lbl_80748660:
/* 80748660  7F A3 EB 78 */	mr r3, r29
/* 80748664  C0 3F 01 CC */	lfs f1, 0x1cc(r31)
/* 80748668  C0 5F 01 DC */	lfs f2, 0x1dc(r31)
/* 8074866C  4B FF AE B9 */	bl SetMoveCam__8daE_PM_cFff
/* 80748670  48 00 02 DC */	b lbl_8074894C
lbl_80748674:
/* 80748674  A8 7D 04 E6 */	lha r3, 0x4e6(r29)
/* 80748678  38 03 00 40 */	addi r0, r3, 0x40
/* 8074867C  B0 1D 04 E6 */	sth r0, 0x4e6(r29)
/* 80748680  C0 5D 06 AC */	lfs f2, 0x6ac(r29)
/* 80748684  C0 1D 06 A4 */	lfs f0, 0x6a4(r29)
/* 80748688  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8074868C  C0 3F 00 04 */	lfs f1, 4(r31)
/* 80748690  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 80748694  D0 41 00 34 */	stfs f2, 0x34(r1)
/* 80748698  C0 5D 06 A0 */	lfs f2, 0x6a0(r29)
/* 8074869C  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807486A0  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 807486A4  D0 21 00 3C */	stfs f1, 0x3c(r1)
/* 807486A8  D0 41 00 40 */	stfs f2, 0x40(r1)
/* 807486AC  38 61 00 2C */	addi r3, r1, 0x2c
/* 807486B0  38 81 00 38 */	addi r4, r1, 0x38
/* 807486B4  4B BF EC E9 */	bl PSVECSquareDistance
/* 807486B8  C0 1F 00 04 */	lfs f0, 4(r31)
/* 807486BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 807486C0  40 81 00 58 */	ble lbl_80748718
/* 807486C4  FC 00 08 34 */	frsqrte f0, f1
/* 807486C8  C8 9F 00 10 */	lfd f4, 0x10(r31)
/* 807486CC  FC 44 00 32 */	fmul f2, f4, f0
/* 807486D0  C8 7F 00 18 */	lfd f3, 0x18(r31)
/* 807486D4  FC 00 00 32 */	fmul f0, f0, f0
/* 807486D8  FC 01 00 32 */	fmul f0, f1, f0
/* 807486DC  FC 03 00 28 */	fsub f0, f3, f0
/* 807486E0  FC 02 00 32 */	fmul f0, f2, f0
/* 807486E4  FC 44 00 32 */	fmul f2, f4, f0
/* 807486E8  FC 00 00 32 */	fmul f0, f0, f0
/* 807486EC  FC 01 00 32 */	fmul f0, f1, f0
/* 807486F0  FC 03 00 28 */	fsub f0, f3, f0
/* 807486F4  FC 02 00 32 */	fmul f0, f2, f0
/* 807486F8  FC 44 00 32 */	fmul f2, f4, f0
/* 807486FC  FC 00 00 32 */	fmul f0, f0, f0
/* 80748700  FC 01 00 32 */	fmul f0, f1, f0
/* 80748704  FC 03 00 28 */	fsub f0, f3, f0
/* 80748708  FC 02 00 32 */	fmul f0, f2, f0
/* 8074870C  FC 21 00 32 */	fmul f1, f1, f0
/* 80748710  FC 20 08 18 */	frsp f1, f1
/* 80748714  48 00 00 88 */	b lbl_8074879C
lbl_80748718:
/* 80748718  C8 1F 00 20 */	lfd f0, 0x20(r31)
/* 8074871C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80748720  40 80 00 10 */	bge lbl_80748730
/* 80748724  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80748728  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
/* 8074872C  48 00 00 70 */	b lbl_8074879C
lbl_80748730:
/* 80748730  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80748734  80 81 00 20 */	lwz r4, 0x20(r1)
/* 80748738  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 8074873C  3C 00 7F 80 */	lis r0, 0x7f80
/* 80748740  7C 03 00 00 */	cmpw r3, r0
/* 80748744  41 82 00 14 */	beq lbl_80748758
/* 80748748  40 80 00 40 */	bge lbl_80748788
/* 8074874C  2C 03 00 00 */	cmpwi r3, 0
/* 80748750  41 82 00 20 */	beq lbl_80748770
/* 80748754  48 00 00 34 */	b lbl_80748788
lbl_80748758:
/* 80748758  54 80 02 7F */	clrlwi. r0, r4, 9
/* 8074875C  41 82 00 0C */	beq lbl_80748768
/* 80748760  38 00 00 01 */	li r0, 1
/* 80748764  48 00 00 28 */	b lbl_8074878C
lbl_80748768:
/* 80748768  38 00 00 02 */	li r0, 2
/* 8074876C  48 00 00 20 */	b lbl_8074878C
lbl_80748770:
/* 80748770  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80748774  41 82 00 0C */	beq lbl_80748780
/* 80748778  38 00 00 05 */	li r0, 5
/* 8074877C  48 00 00 10 */	b lbl_8074878C
lbl_80748780:
/* 80748780  38 00 00 03 */	li r0, 3
/* 80748784  48 00 00 08 */	b lbl_8074878C
lbl_80748788:
/* 80748788  38 00 00 04 */	li r0, 4
lbl_8074878C:
/* 8074878C  2C 00 00 01 */	cmpwi r0, 1
/* 80748790  40 82 00 0C */	bne lbl_8074879C
/* 80748794  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80748798  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
lbl_8074879C:
/* 8074879C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 807487A0  D0 01 00 8C */	stfs f0, 0x8c(r1)
/* 807487A4  D0 01 00 90 */	stfs f0, 0x90(r1)
/* 807487A8  C0 1F 00 34 */	lfs f0, 0x34(r31)
/* 807487AC  EC 00 08 2A */	fadds f0, f0, f1
/* 807487B0  D0 01 00 94 */	stfs f0, 0x94(r1)
/* 807487B4  C0 5D 06 A0 */	lfs f2, 0x6a0(r29)
/* 807487B8  C0 3D 06 A8 */	lfs f1, 0x6a8(r29)
/* 807487BC  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807487C0  D0 01 00 98 */	stfs f0, 0x98(r1)
/* 807487C4  D0 21 00 9C */	stfs f1, 0x9c(r1)
/* 807487C8  D0 41 00 A0 */	stfs f2, 0xa0(r1)
/* 807487CC  38 7D 06 A4 */	addi r3, r29, 0x6a4
/* 807487D0  38 81 00 98 */	addi r4, r1, 0x98
/* 807487D4  A8 BD 04 E6 */	lha r5, 0x4e6(r29)
/* 807487D8  3C A5 00 01 */	addis r5, r5, 1
/* 807487DC  38 05 80 00 */	addi r0, r5, -32768
/* 807487E0  7C 05 07 34 */	extsh r5, r0
/* 807487E4  38 C1 00 8C */	addi r6, r1, 0x8c
/* 807487E8  4B B2 85 D9 */	bl cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz
/* 807487EC  38 7D 06 3C */	addi r3, r29, 0x63c
/* 807487F0  7F A4 EB 78 */	mr r4, r29
/* 807487F4  38 A0 00 00 */	li r5, 0
/* 807487F8  38 C0 00 00 */	li r6, 0
/* 807487FC  4B B0 1A DD */	bl doFlow__10dMsgFlow_cFP10fopAc_ac_cPP10fopAc_ac_ci
/* 80748800  2C 03 00 00 */	cmpwi r3, 0
/* 80748804  41 82 01 14 */	beq lbl_80748918
/* 80748808  80 1E 05 70 */	lwz r0, 0x570(r30)
/* 8074880C  54 00 01 46 */	rlwinm r0, r0, 0, 5, 3
/* 80748810  90 1E 05 70 */	stw r0, 0x570(r30)
/* 80748814  80 1E 05 78 */	lwz r0, 0x578(r30)
/* 80748818  54 00 05 A8 */	rlwinm r0, r0, 0, 0x16, 0x14
/* 8074881C  90 1E 05 78 */	stw r0, 0x578(r30)
/* 80748820  3C 60 80 74 */	lis r3, s_boss_sub__FPvPv@ha /* 0x80747500@ha */
/* 80748824  38 63 75 00 */	addi r3, r3, s_boss_sub__FPvPv@l /* 0x80747500@l */
/* 80748828  7F A4 EB 78 */	mr r4, r29
/* 8074882C  4B 8D 8B 0D */	bl fpcEx_Search__FPFPvPv_PvPv
/* 80748830  7C 7E 1B 79 */	or. r30, r3, r3
/* 80748834  41 82 00 C8 */	beq lbl_807488FC
/* 80748838  C0 7E 04 D0 */	lfs f3, 0x4d0(r30)
/* 8074883C  D0 61 00 80 */	stfs f3, 0x80(r1)
/* 80748840  C0 5E 04 D4 */	lfs f2, 0x4d4(r30)
/* 80748844  D0 41 00 84 */	stfs f2, 0x84(r1)
/* 80748848  C0 3E 04 D8 */	lfs f1, 0x4d8(r30)
/* 8074884C  D0 21 00 88 */	stfs f1, 0x88(r1)
/* 80748850  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 80748854  EC 02 00 2A */	fadds f0, f2, f0
/* 80748858  D0 01 00 84 */	stfs f0, 0x84(r1)
/* 8074885C  D0 61 00 74 */	stfs f3, 0x74(r1)
/* 80748860  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 80748864  D0 21 00 7C */	stfs f1, 0x7c(r1)
/* 80748868  7F A3 EB 78 */	mr r3, r29
/* 8074886C  38 81 00 74 */	addi r4, r1, 0x74
/* 80748870  C0 3F 01 A4 */	lfs f1, 0x1a4(r31)
/* 80748874  C0 5F 01 E0 */	lfs f2, 0x1e0(r31)
/* 80748878  A8 BE 04 DE */	lha r5, 0x4de(r30)
/* 8074887C  4B FF AA 19 */	bl SetStopCam__8daE_PM_cF4cXyzffs
/* 80748880  C0 1F 01 00 */	lfs f0, 0x100(r31)
/* 80748884  D0 01 00 8C */	stfs f0, 0x8c(r1)
/* 80748888  C0 1F 01 E0 */	lfs f0, 0x1e0(r31)
/* 8074888C  D0 01 00 90 */	stfs f0, 0x90(r1)
/* 80748890  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80748894  D0 01 00 94 */	stfs f0, 0x94(r1)
/* 80748898  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 8074889C  D0 01 00 A4 */	stfs f0, 0xa4(r1)
/* 807488A0  C0 1D 06 9C */	lfs f0, 0x69c(r29)
/* 807488A4  D0 01 00 A8 */	stfs f0, 0xa8(r1)
/* 807488A8  C0 1D 06 A0 */	lfs f0, 0x6a0(r29)
/* 807488AC  D0 01 00 AC */	stfs f0, 0xac(r1)
/* 807488B0  38 7D 06 98 */	addi r3, r29, 0x698
/* 807488B4  38 81 00 A4 */	addi r4, r1, 0xa4
/* 807488B8  A8 BE 04 DE */	lha r5, 0x4de(r30)
/* 807488BC  38 C1 00 8C */	addi r6, r1, 0x8c
/* 807488C0  4B B2 85 01 */	bl cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz
/* 807488C4  C0 1D 06 98 */	lfs f0, 0x698(r29)
/* 807488C8  D0 1D 06 B0 */	stfs f0, 0x6b0(r29)
/* 807488CC  C0 1D 06 9C */	lfs f0, 0x69c(r29)
/* 807488D0  D0 1D 06 B4 */	stfs f0, 0x6b4(r29)
/* 807488D4  C0 1D 06 A0 */	lfs f0, 0x6a0(r29)
/* 807488D8  D0 1D 06 B8 */	stfs f0, 0x6b8(r29)
/* 807488DC  C0 01 00 80 */	lfs f0, 0x80(r1)
/* 807488E0  D0 1D 04 D0 */	stfs f0, 0x4d0(r29)
/* 807488E4  C0 3F 01 D8 */	lfs f1, 0x1d8(r31)
/* 807488E8  C0 1D 08 9C */	lfs f0, 0x89c(r29)
/* 807488EC  EC 01 00 2A */	fadds f0, f1, f0
/* 807488F0  D0 1D 04 D4 */	stfs f0, 0x4d4(r29)
/* 807488F4  C0 01 00 88 */	lfs f0, 0x88(r1)
/* 807488F8  D0 1D 04 D8 */	stfs f0, 0x4d8(r29)
lbl_807488FC:
/* 807488FC  88 7D 06 11 */	lbz r3, 0x611(r29)
/* 80748900  38 03 00 01 */	addi r0, r3, 1
/* 80748904  98 1D 06 11 */	stb r0, 0x611(r29)
/* 80748908  38 00 00 02 */	li r0, 2
/* 8074890C  98 1D 05 DC */	stb r0, 0x5dc(r29)
/* 80748910  38 00 00 64 */	li r0, 0x64
/* 80748914  B0 1D 06 22 */	sth r0, 0x622(r29)
lbl_80748918:
/* 80748918  7F A3 EB 78 */	mr r3, r29
/* 8074891C  C0 3F 01 CC */	lfs f1, 0x1cc(r31)
/* 80748920  C0 5F 01 DC */	lfs f2, 0x1dc(r31)
/* 80748924  4B FF AC 01 */	bl SetMoveCam__8daE_PM_cFff
/* 80748928  48 00 00 24 */	b lbl_8074894C
lbl_8074892C:
/* 8074892C  4B FF A8 E5 */	bl SetStopingCam__8daE_PM_cFv
/* 80748930  A8 1D 06 22 */	lha r0, 0x622(r29)
/* 80748934  2C 00 00 00 */	cmpwi r0, 0
/* 80748938  40 82 00 14 */	bne lbl_8074894C
/* 8074893C  7F A3 EB 78 */	mr r3, r29
/* 80748940  4B FF AC C1 */	bl SetReleaseCam__8daE_PM_cFv
/* 80748944  7F A3 EB 78 */	mr r3, r29
/* 80748948  4B 8D 13 35 */	bl fopAcM_delete__FP10fopAc_ac_c
lbl_8074894C:
/* 8074894C  39 61 00 C0 */	addi r11, r1, 0xc0
/* 80748950  4B C1 98 D9 */	bl _restgpr_29
/* 80748954  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 80748958  7C 08 03 A6 */	mtlr r0
/* 8074895C  38 21 00 C0 */	addi r1, r1, 0xc0
/* 80748960  4E 80 00 20 */	blr 
