lbl_800B1FD8:
/* 800B1FD8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800B1FDC  7C 08 02 A6 */	mflr r0
/* 800B1FE0  90 01 00 24 */	stw r0, 0x24(r1)
/* 800B1FE4  39 61 00 20 */	addi r11, r1, 0x20
/* 800B1FE8  48 2B 01 F1 */	bl _savegpr_28
/* 800B1FEC  7C 7D 1B 78 */	mr r29, r3
/* 800B1FF0  7C 9E 23 78 */	mr r30, r4
/* 800B1FF4  80 03 05 70 */	lwz r0, 0x570(r3)
/* 800B1FF8  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
/* 800B1FFC  40 82 01 D4 */	bne lbl_800B21D0
/* 800B2000  80 1D 19 9C */	lwz r0, 0x199c(r29)
/* 800B2004  54 00 06 B5 */	rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 800B2008  41 82 01 C8 */	beq lbl_800B21D0
/* 800B200C  80 1D 31 A0 */	lwz r0, 0x31a0(r29)
/* 800B2010  54 00 03 5B */	rlwinm. r0, r0, 0, 0xd, 0xd
/* 800B2014  40 82 01 BC */	bne lbl_800B21D0
/* 800B2018  88 1D 2F A8 */	lbz r0, 0x2fa8(r29)
/* 800B201C  28 00 00 06 */	cmplwi r0, 6
/* 800B2020  41 82 01 B0 */	beq lbl_800B21D0
/* 800B2024  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 800B2028  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 800B202C  3B 83 0F 38 */	addi r28, r3, 0xf38
/* 800B2030  7F 83 E3 78 */	mr r3, r28
/* 800B2034  38 9D 1A 60 */	addi r4, r29, 0x1a60
/* 800B2038  4B FC 26 29 */	bl ChkPolySafe__4cBgSFRC13cBgS_PolyInfo
/* 800B203C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800B2040  41 82 01 90 */	beq lbl_800B21D0
/* 800B2044  80 1D 05 70 */	lwz r0, 0x570(r29)
/* 800B2048  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800B204C  41 82 00 14 */	beq lbl_800B2060
/* 800B2050  38 7D 1A 60 */	addi r3, r29, 0x1a60
/* 800B2054  4B F7 FA FD */	bl checkMagnetCode__12daTagMagne_cFR13cBgS_PolyInfo
/* 800B2058  2C 03 00 00 */	cmpwi r3, 0
/* 800B205C  40 82 00 10 */	bne lbl_800B206C
lbl_800B2060:
/* 800B2060  A0 1D 2F E8 */	lhz r0, 0x2fe8(r29)
/* 800B2064  28 00 00 C2 */	cmplwi r0, 0xc2
/* 800B2068  40 82 00 0C */	bne lbl_800B2074
lbl_800B206C:
/* 800B206C  38 60 00 00 */	li r3, 0
/* 800B2070  48 00 01 64 */	b lbl_800B21D4
lbl_800B2074:
/* 800B2074  38 7D 1A 60 */	addi r3, r29, 0x1a60
/* 800B2078  38 80 00 01 */	li r4, 1
/* 800B207C  4B FF 01 65 */	bl getMoveBGActorName__9daAlink_cFR13cBgS_PolyInfoi
/* 800B2080  7C 7F 1B 78 */	mr r31, r3
/* 800B2084  7F 83 E3 78 */	mr r3, r28
/* 800B2088  38 9D 1A 60 */	addi r4, r29, 0x1a60
/* 800B208C  7F C5 F3 78 */	mr r5, r30
/* 800B2090  4B FC 26 B5 */	bl GetTriPla__4cBgSCFRC13cBgS_PolyInfoP8cM3dGPla
/* 800B2094  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800B2098  41 82 01 38 */	beq lbl_800B21D0
/* 800B209C  7F A3 EB 78 */	mr r3, r29
/* 800B20A0  81 9D 06 28 */	lwz r12, 0x628(r29)
/* 800B20A4  81 8C 02 80 */	lwz r12, 0x280(r12)
/* 800B20A8  7D 89 03 A6 */	mtctr r12
/* 800B20AC  4E 80 04 21 */	bctrl 
/* 800B20B0  2C 03 00 00 */	cmpwi r3, 0
/* 800B20B4  41 82 00 18 */	beq lbl_800B20CC
/* 800B20B8  7F E0 07 34 */	extsh r0, r31
/* 800B20BC  2C 00 00 C5 */	cmpwi r0, 0xc5
/* 800B20C0  41 82 01 10 */	beq lbl_800B21D0
/* 800B20C4  2C 00 00 D4 */	cmpwi r0, 0xd4
/* 800B20C8  41 82 01 08 */	beq lbl_800B21D0
lbl_800B20CC:
/* 800B20CC  80 1D 31 74 */	lwz r0, 0x3174(r29)
/* 800B20D0  2C 00 00 08 */	cmpwi r0, 8
/* 800B20D4  41 82 00 28 */	beq lbl_800B20FC
/* 800B20D8  88 1D 2F A8 */	lbz r0, 0x2fa8(r29)
/* 800B20DC  28 00 00 01 */	cmplwi r0, 1
/* 800B20E0  41 82 00 E8 */	beq lbl_800B21C8
/* 800B20E4  C0 3E 00 04 */	lfs f1, 4(r30)
/* 800B20E8  C0 1D 34 70 */	lfs f0, 0x3470(r29)
/* 800B20EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800B20F0  40 80 00 0C */	bge lbl_800B20FC
/* 800B20F4  28 00 00 02 */	cmplwi r0, 2
/* 800B20F8  40 82 00 D0 */	bne lbl_800B21C8
lbl_800B20FC:
/* 800B20FC  88 1D 2F A8 */	lbz r0, 0x2fa8(r29)
/* 800B2100  28 00 00 05 */	cmplwi r0, 5
/* 800B2104  40 82 00 50 */	bne lbl_800B2154
/* 800B2108  80 1D 05 74 */	lwz r0, 0x574(r29)
/* 800B210C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800B2110  40 82 00 44 */	bne lbl_800B2154
/* 800B2114  C0 3D 33 AC */	lfs f1, 0x33ac(r29)
/* 800B2118  C0 02 92 A4 */	lfs f0, lit_6021(r2)
/* 800B211C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800B2120  40 81 00 10 */	ble lbl_800B2130
/* 800B2124  A0 1D 2F E8 */	lhz r0, 0x2fe8(r29)
/* 800B2128  28 00 00 0C */	cmplwi r0, 0xc
/* 800B212C  40 82 00 28 */	bne lbl_800B2154
lbl_800B2130:
/* 800B2130  3C 60 80 44 */	lis r3, sincosTable___5JMath@ha /* 0x80439A20@ha */
/* 800B2134  38 63 9A 20 */	addi r3, r3, sincosTable___5JMath@l /* 0x80439A20@l */
/* 800B2138  A8 1D 31 22 */	lha r0, 0x3122(r29)
/* 800B213C  54 00 04 38 */	rlwinm r0, r0, 0, 0x10, 0x1c
/* 800B2140  7C 63 02 14 */	add r3, r3, r0
/* 800B2144  C0 23 00 04 */	lfs f1, 4(r3)
/* 800B2148  C0 1E 00 04 */	lfs f0, 4(r30)
/* 800B214C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800B2150  41 80 00 78 */	blt lbl_800B21C8
lbl_800B2154:
/* 800B2154  80 1D 05 70 */	lwz r0, 0x570(r29)
/* 800B2158  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800B215C  40 82 00 74 */	bne lbl_800B21D0
/* 800B2160  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 800B2164  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 800B2168  80 03 5F 18 */	lwz r0, 0x5f18(r3)
/* 800B216C  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 800B2170  40 82 00 60 */	bne lbl_800B21D0
/* 800B2174  7F A3 EB 78 */	mr r3, r29
/* 800B2178  7F E4 FB 78 */	mr r4, r31
/* 800B217C  4B FF FE 3D */	bl checkLv2MiddleBossBgRide__9daAlink_cFs
/* 800B2180  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800B2184  41 82 00 4C */	beq lbl_800B21D0
/* 800B2188  C0 22 94 D4 */	lfs f1, lit_18929(r2)
/* 800B218C  3C 60 80 39 */	lis r3, m__19daAlinkHIO_slide_c0@ha /* 0x8038D8CC@ha */
/* 800B2190  38 63 D8 CC */	addi r3, r3, m__19daAlinkHIO_slide_c0@l /* 0x8038D8CC@l */
/* 800B2194  C0 03 00 68 */	lfs f0, 0x68(r3)
/* 800B2198  EC 01 00 32 */	fmuls f0, f1, f0
/* 800B219C  FC 00 00 1E */	fctiwz f0, f0
/* 800B21A0  D8 01 00 08 */	stfd f0, 8(r1)
/* 800B21A4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800B21A8  3C 60 80 44 */	lis r3, sincosTable___5JMath@ha /* 0x80439A20@ha */
/* 800B21AC  38 63 9A 20 */	addi r3, r3, sincosTable___5JMath@l /* 0x80439A20@l */
/* 800B21B0  54 00 04 38 */	rlwinm r0, r0, 0, 0x10, 0x1c
/* 800B21B4  7C 63 02 14 */	add r3, r3, r0
/* 800B21B8  C0 23 00 04 */	lfs f1, 4(r3)
/* 800B21BC  C0 1E 00 04 */	lfs f0, 4(r30)
/* 800B21C0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800B21C4  40 80 00 0C */	bge lbl_800B21D0
lbl_800B21C8:
/* 800B21C8  38 60 00 01 */	li r3, 1
/* 800B21CC  48 00 00 08 */	b lbl_800B21D4
lbl_800B21D0:
/* 800B21D0  38 60 00 00 */	li r3, 0
lbl_800B21D4:
/* 800B21D4  39 61 00 20 */	addi r11, r1, 0x20
/* 800B21D8  48 2B 00 4D */	bl _restgpr_28
/* 800B21DC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800B21E0  7C 08 03 A6 */	mtlr r0
/* 800B21E4  38 21 00 20 */	addi r1, r1, 0x20
/* 800B21E8  4E 80 00 20 */	blr 
