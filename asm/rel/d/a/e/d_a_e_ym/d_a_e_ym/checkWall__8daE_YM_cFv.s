lbl_80814758:
/* 80814758  94 21 FF 20 */	stwu r1, -0xe0(r1)
/* 8081475C  7C 08 02 A6 */	mflr r0
/* 80814760  90 01 00 E4 */	stw r0, 0xe4(r1)
/* 80814764  39 61 00 E0 */	addi r11, r1, 0xe0
/* 80814768  4B B4 DA 75 */	bl _savegpr_29
/* 8081476C  7C 7E 1B 78 */	mr r30, r3
/* 80814770  3C 60 80 81 */	lis r3, lit_3925@ha /* 0x80815994@ha */
/* 80814774  3B E3 59 94 */	addi r31, r3, lit_3925@l /* 0x80815994@l */
/* 80814778  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8081477C  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80814780  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80814784  C0 1F 00 00 */	lfs f0, 0(r31)
/* 80814788  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8081478C  38 61 00 60 */	addi r3, r1, 0x60
/* 80814790  4B 86 34 D9 */	bl __ct__11dBgS_LinChkFv
/* 80814794  88 1E 06 A0 */	lbz r0, 0x6a0(r30)
/* 80814798  28 00 00 01 */	cmplwi r0, 1
/* 8081479C  41 82 00 18 */	beq lbl_808147B4
/* 808147A0  38 61 00 60 */	addi r3, r1, 0x60
/* 808147A4  38 80 FF FF */	li r4, -1
/* 808147A8  4B 86 35 35 */	bl __dt__11dBgS_LinChkFv
/* 808147AC  38 60 00 00 */	li r3, 0
/* 808147B0  48 00 03 28 */	b lbl_80814AD8
lbl_808147B4:
/* 808147B4  38 61 00 34 */	addi r3, r1, 0x34
/* 808147B8  38 9E 04 D0 */	addi r4, r30, 0x4d0
/* 808147BC  A8 BE 06 6C */	lha r5, 0x66c(r30)
/* 808147C0  38 C1 00 28 */	addi r6, r1, 0x28
/* 808147C4  4B A5 C5 FD */	bl cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz
/* 808147C8  C0 1F 01 4C */	lfs f0, 0x14c(r31)
/* 808147CC  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 808147D0  38 61 00 40 */	addi r3, r1, 0x40
/* 808147D4  38 9E 04 D0 */	addi r4, r30, 0x4d0
/* 808147D8  A8 BE 06 6C */	lha r5, 0x66c(r30)
/* 808147DC  38 C1 00 28 */	addi r6, r1, 0x28
/* 808147E0  4B A5 C5 E1 */	bl cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz
/* 808147E4  38 61 00 60 */	addi r3, r1, 0x60
/* 808147E8  38 81 00 40 */	addi r4, r1, 0x40
/* 808147EC  38 A1 00 34 */	addi r5, r1, 0x34
/* 808147F0  38 C0 00 00 */	li r6, 0
/* 808147F4  4B 86 35 71 */	bl Set__11dBgS_LinChkFPC4cXyzPC4cXyzPC10fopAc_ac_c
/* 808147F8  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 808147FC  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 80814800  3B A3 0F 38 */	addi r29, r3, 0xf38
/* 80814804  7F A3 EB 78 */	mr r3, r29
/* 80814808  38 81 00 60 */	addi r4, r1, 0x60
/* 8081480C  4B 85 FB A9 */	bl LineCross__4cBgSFP11cBgS_LinChk
/* 80814810  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80814814  41 82 02 B4 */	beq lbl_80814AC8
/* 80814818  3C 60 80 81 */	lis r3, __vt__8cM3dGPla@ha /* 0x80815D04@ha */
/* 8081481C  38 03 5D 04 */	addi r0, r3, __vt__8cM3dGPla@l /* 0x80815D04@l */
/* 80814820  90 01 00 5C */	stw r0, 0x5c(r1)
/* 80814824  7F A3 EB 78 */	mr r3, r29
/* 80814828  38 81 00 74 */	addi r4, r1, 0x74
/* 8081482C  38 A1 00 4C */	addi r5, r1, 0x4c
/* 80814830  4B 85 FF 15 */	bl GetTriPla__4cBgSCFRC13cBgS_PolyInfoP8cM3dGPla
/* 80814834  C0 01 00 4C */	lfs f0, 0x4c(r1)
/* 80814838  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8081483C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80814840  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80814844  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 80814848  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8081484C  38 61 00 1C */	addi r3, r1, 0x1c
/* 80814850  4B B3 28 E9 */	bl PSVECSquareMag
/* 80814854  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80814858  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8081485C  40 81 00 58 */	ble lbl_808148B4
/* 80814860  FC 00 08 34 */	frsqrte f0, f1
/* 80814864  C8 9F 00 10 */	lfd f4, 0x10(r31)
/* 80814868  FC 44 00 32 */	fmul f2, f4, f0
/* 8081486C  C8 7F 00 18 */	lfd f3, 0x18(r31)
/* 80814870  FC 00 00 32 */	fmul f0, f0, f0
/* 80814874  FC 01 00 32 */	fmul f0, f1, f0
/* 80814878  FC 03 00 28 */	fsub f0, f3, f0
/* 8081487C  FC 02 00 32 */	fmul f0, f2, f0
/* 80814880  FC 44 00 32 */	fmul f2, f4, f0
/* 80814884  FC 00 00 32 */	fmul f0, f0, f0
/* 80814888  FC 01 00 32 */	fmul f0, f1, f0
/* 8081488C  FC 03 00 28 */	fsub f0, f3, f0
/* 80814890  FC 02 00 32 */	fmul f0, f2, f0
/* 80814894  FC 44 00 32 */	fmul f2, f4, f0
/* 80814898  FC 00 00 32 */	fmul f0, f0, f0
/* 8081489C  FC 01 00 32 */	fmul f0, f1, f0
/* 808148A0  FC 03 00 28 */	fsub f0, f3, f0
/* 808148A4  FC 02 00 32 */	fmul f0, f2, f0
/* 808148A8  FC 21 00 32 */	fmul f1, f1, f0
/* 808148AC  FC 20 08 18 */	frsp f1, f1
/* 808148B0  48 00 00 88 */	b lbl_80814938
lbl_808148B4:
/* 808148B4  C8 1F 00 20 */	lfd f0, 0x20(r31)
/* 808148B8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 808148BC  40 80 00 10 */	bge lbl_808148CC
/* 808148C0  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 808148C4  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
/* 808148C8  48 00 00 70 */	b lbl_80814938
lbl_808148CC:
/* 808148CC  D0 21 00 0C */	stfs f1, 0xc(r1)
/* 808148D0  80 81 00 0C */	lwz r4, 0xc(r1)
/* 808148D4  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 808148D8  3C 00 7F 80 */	lis r0, 0x7f80
/* 808148DC  7C 03 00 00 */	cmpw r3, r0
/* 808148E0  41 82 00 14 */	beq lbl_808148F4
/* 808148E4  40 80 00 40 */	bge lbl_80814924
/* 808148E8  2C 03 00 00 */	cmpwi r3, 0
/* 808148EC  41 82 00 20 */	beq lbl_8081490C
/* 808148F0  48 00 00 34 */	b lbl_80814924
lbl_808148F4:
/* 808148F4  54 80 02 7F */	clrlwi. r0, r4, 9
/* 808148F8  41 82 00 0C */	beq lbl_80814904
/* 808148FC  38 00 00 01 */	li r0, 1
/* 80814900  48 00 00 28 */	b lbl_80814928
lbl_80814904:
/* 80814904  38 00 00 02 */	li r0, 2
/* 80814908  48 00 00 20 */	b lbl_80814928
lbl_8081490C:
/* 8081490C  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80814910  41 82 00 0C */	beq lbl_8081491C
/* 80814914  38 00 00 05 */	li r0, 5
/* 80814918  48 00 00 10 */	b lbl_80814928
lbl_8081491C:
/* 8081491C  38 00 00 03 */	li r0, 3
/* 80814920  48 00 00 08 */	b lbl_80814928
lbl_80814924:
/* 80814924  38 00 00 04 */	li r0, 4
lbl_80814928:
/* 80814928  2C 00 00 01 */	cmpwi r0, 1
/* 8081492C  40 82 00 0C */	bne lbl_80814938
/* 80814930  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80814934  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
lbl_80814938:
/* 80814938  C0 41 00 50 */	lfs f2, 0x50(r1)
/* 8081493C  4B A5 2D 39 */	bl cM_atan2s__Fff
/* 80814940  38 03 80 00 */	addi r0, r3, -32768
/* 80814944  7C 03 07 34 */	extsh r3, r0
/* 80814948  38 63 40 00 */	addi r3, r3, 0x4000
/* 8081494C  4B B5 07 85 */	bl abs
/* 80814950  2C 03 15 55 */	cmpwi r3, 0x1555
/* 80814954  41 81 01 68 */	bgt lbl_80814ABC
/* 80814958  C0 01 00 90 */	lfs f0, 0x90(r1)
/* 8081495C  D0 1E 04 D0 */	stfs f0, 0x4d0(r30)
/* 80814960  C0 01 00 94 */	lfs f0, 0x94(r1)
/* 80814964  D0 1E 04 D4 */	stfs f0, 0x4d4(r30)
/* 80814968  C0 01 00 98 */	lfs f0, 0x98(r1)
/* 8081496C  D0 1E 04 D8 */	stfs f0, 0x4d8(r30)
/* 80814970  C0 21 00 4C */	lfs f1, 0x4c(r1)
/* 80814974  C0 41 00 54 */	lfs f2, 0x54(r1)
/* 80814978  4B A5 2C FD */	bl cM_atan2s__Fff
/* 8081497C  3C 63 00 01 */	addis r3, r3, 1
/* 80814980  38 03 80 00 */	addi r0, r3, -32768
/* 80814984  B0 1E 06 6C */	sth r0, 0x66c(r30)
/* 80814988  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 8081498C  C0 01 00 4C */	lfs f0, 0x4c(r1)
/* 80814990  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 80814994  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80814998  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8081499C  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 808149A0  38 61 00 10 */	addi r3, r1, 0x10
/* 808149A4  4B B3 27 95 */	bl PSVECSquareMag
/* 808149A8  C0 1F 00 04 */	lfs f0, 4(r31)
/* 808149AC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 808149B0  40 81 00 58 */	ble lbl_80814A08
/* 808149B4  FC 00 08 34 */	frsqrte f0, f1
/* 808149B8  C8 9F 00 10 */	lfd f4, 0x10(r31)
/* 808149BC  FC 44 00 32 */	fmul f2, f4, f0
/* 808149C0  C8 7F 00 18 */	lfd f3, 0x18(r31)
/* 808149C4  FC 00 00 32 */	fmul f0, f0, f0
/* 808149C8  FC 01 00 32 */	fmul f0, f1, f0
/* 808149CC  FC 03 00 28 */	fsub f0, f3, f0
/* 808149D0  FC 02 00 32 */	fmul f0, f2, f0
/* 808149D4  FC 44 00 32 */	fmul f2, f4, f0
/* 808149D8  FC 00 00 32 */	fmul f0, f0, f0
/* 808149DC  FC 01 00 32 */	fmul f0, f1, f0
/* 808149E0  FC 03 00 28 */	fsub f0, f3, f0
/* 808149E4  FC 02 00 32 */	fmul f0, f2, f0
/* 808149E8  FC 44 00 32 */	fmul f2, f4, f0
/* 808149EC  FC 00 00 32 */	fmul f0, f0, f0
/* 808149F0  FC 01 00 32 */	fmul f0, f1, f0
/* 808149F4  FC 03 00 28 */	fsub f0, f3, f0
/* 808149F8  FC 02 00 32 */	fmul f0, f2, f0
/* 808149FC  FC 21 00 32 */	fmul f1, f1, f0
/* 80814A00  FC 20 08 18 */	frsp f1, f1
/* 80814A04  48 00 00 88 */	b lbl_80814A8C
lbl_80814A08:
/* 80814A08  C8 1F 00 20 */	lfd f0, 0x20(r31)
/* 80814A0C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80814A10  40 80 00 10 */	bge lbl_80814A20
/* 80814A14  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80814A18  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
/* 80814A1C  48 00 00 70 */	b lbl_80814A8C
lbl_80814A20:
/* 80814A20  D0 21 00 08 */	stfs f1, 8(r1)
/* 80814A24  80 81 00 08 */	lwz r4, 8(r1)
/* 80814A28  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 80814A2C  3C 00 7F 80 */	lis r0, 0x7f80
/* 80814A30  7C 03 00 00 */	cmpw r3, r0
/* 80814A34  41 82 00 14 */	beq lbl_80814A48
/* 80814A38  40 80 00 40 */	bge lbl_80814A78
/* 80814A3C  2C 03 00 00 */	cmpwi r3, 0
/* 80814A40  41 82 00 20 */	beq lbl_80814A60
/* 80814A44  48 00 00 34 */	b lbl_80814A78
lbl_80814A48:
/* 80814A48  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80814A4C  41 82 00 0C */	beq lbl_80814A58
/* 80814A50  38 00 00 01 */	li r0, 1
/* 80814A54  48 00 00 28 */	b lbl_80814A7C
lbl_80814A58:
/* 80814A58  38 00 00 02 */	li r0, 2
/* 80814A5C  48 00 00 20 */	b lbl_80814A7C
lbl_80814A60:
/* 80814A60  54 80 02 7F */	clrlwi. r0, r4, 9
/* 80814A64  41 82 00 0C */	beq lbl_80814A70
/* 80814A68  38 00 00 05 */	li r0, 5
/* 80814A6C  48 00 00 10 */	b lbl_80814A7C
lbl_80814A70:
/* 80814A70  38 00 00 03 */	li r0, 3
/* 80814A74  48 00 00 08 */	b lbl_80814A7C
lbl_80814A78:
/* 80814A78  38 00 00 04 */	li r0, 4
lbl_80814A7C:
/* 80814A7C  2C 00 00 01 */	cmpwi r0, 1
/* 80814A80  40 82 00 0C */	bne lbl_80814A8C
/* 80814A84  3C 60 80 45 */	lis r3, __float_nan@ha /* 0x80450AE0@ha */
/* 80814A88  C0 23 0A E0 */	lfs f1, __float_nan@l(r3)  /* 0x80450AE0@l */
lbl_80814A8C:
/* 80814A8C  C0 41 00 50 */	lfs f2, 0x50(r1)
/* 80814A90  4B A5 2B E5 */	bl cM_atan2s__Fff
/* 80814A94  38 03 80 00 */	addi r0, r3, -32768
/* 80814A98  B0 1E 06 68 */	sth r0, 0x668(r30)
/* 80814A9C  3C 60 80 81 */	lis r3, __vt__8cM3dGPla@ha /* 0x80815D04@ha */
/* 80814AA0  38 03 5D 04 */	addi r0, r3, __vt__8cM3dGPla@l /* 0x80815D04@l */
/* 80814AA4  90 01 00 5C */	stw r0, 0x5c(r1)
/* 80814AA8  38 61 00 60 */	addi r3, r1, 0x60
/* 80814AAC  38 80 FF FF */	li r4, -1
/* 80814AB0  4B 86 32 2D */	bl __dt__11dBgS_LinChkFv
/* 80814AB4  38 60 00 01 */	li r3, 1
/* 80814AB8  48 00 00 20 */	b lbl_80814AD8
lbl_80814ABC:
/* 80814ABC  3C 60 80 81 */	lis r3, __vt__8cM3dGPla@ha /* 0x80815D04@ha */
/* 80814AC0  38 03 5D 04 */	addi r0, r3, __vt__8cM3dGPla@l /* 0x80815D04@l */
/* 80814AC4  90 01 00 5C */	stw r0, 0x5c(r1)
lbl_80814AC8:
/* 80814AC8  38 61 00 60 */	addi r3, r1, 0x60
/* 80814ACC  38 80 FF FF */	li r4, -1
/* 80814AD0  4B 86 32 0D */	bl __dt__11dBgS_LinChkFv
/* 80814AD4  38 60 00 00 */	li r3, 0
lbl_80814AD8:
/* 80814AD8  39 61 00 E0 */	addi r11, r1, 0xe0
/* 80814ADC  4B B4 D7 4D */	bl _restgpr_29
/* 80814AE0  80 01 00 E4 */	lwz r0, 0xe4(r1)
/* 80814AE4  7C 08 03 A6 */	mtlr r0
/* 80814AE8  38 21 00 E0 */	addi r1, r1, 0xe0
/* 80814AEC  4E 80 00 20 */	blr 
