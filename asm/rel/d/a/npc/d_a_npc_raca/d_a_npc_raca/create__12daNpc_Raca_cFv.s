lbl_80AB5DFC:
/* 80AB5DFC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80AB5E00  7C 08 02 A6 */	mflr r0
/* 80AB5E04  90 01 00 34 */	stw r0, 0x34(r1)
/* 80AB5E08  39 61 00 30 */	addi r11, r1, 0x30
/* 80AB5E0C  4B 8A C3 D1 */	bl _savegpr_29
/* 80AB5E10  7C 7D 1B 78 */	mr r29, r3
/* 80AB5E14  3C 80 80 AC */	lis r4, m__18daNpc_Raca_Param_c@ha /* 0x80AB8EC8@ha */
/* 80AB5E18  3B E4 8E C8 */	addi r31, r4, m__18daNpc_Raca_Param_c@l /* 0x80AB8EC8@l */
/* 80AB5E1C  3C 80 80 AC */	lis r4, cNullVec__6Z2Calc@ha /* 0x80AB8FBC@ha */
/* 80AB5E20  3B C4 8F BC */	addi r30, r4, cNullVec__6Z2Calc@l /* 0x80AB8FBC@l */
/* 80AB5E24  80 03 04 A0 */	lwz r0, 0x4a0(r3)
/* 80AB5E28  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80AB5E2C  40 82 00 40 */	bne lbl_80AB5E6C
/* 80AB5E30  28 1D 00 00 */	cmplwi r29, 0
/* 80AB5E34  41 82 00 2C */	beq lbl_80AB5E60
/* 80AB5E38  38 1E 00 38 */	addi r0, r30, 0x38
/* 80AB5E3C  90 01 00 08 */	stw r0, 8(r1)
/* 80AB5E40  38 9E 00 4C */	addi r4, r30, 0x4c
/* 80AB5E44  38 BE 01 2C */	addi r5, r30, 0x12c
/* 80AB5E48  38 DE 02 44 */	addi r6, r30, 0x244
/* 80AB5E4C  38 E0 00 04 */	li r7, 4
/* 80AB5E50  39 1E 02 C4 */	addi r8, r30, 0x2c4
/* 80AB5E54  39 20 00 04 */	li r9, 4
/* 80AB5E58  39 5E 00 28 */	addi r10, r30, 0x28
/* 80AB5E5C  48 00 2E 71 */	bl __ct__12daNpc_Raca_cFPC26daNpcT_faceMotionAnmData_cPC22daNpcT_motionAnmData_cPCQ222daNpcT_MotionSeqMngr_c18sequenceStepData_ciPCQ222daNpcT_MotionSeqMngr_c18sequenceStepData_ciPC16daNpcT_evtData_cPPc
lbl_80AB5E60:
/* 80AB5E60  80 1D 04 A0 */	lwz r0, 0x4a0(r29)
/* 80AB5E64  60 00 00 08 */	ori r0, r0, 8
/* 80AB5E68  90 1D 04 A0 */	stw r0, 0x4a0(r29)
lbl_80AB5E6C:
/* 80AB5E6C  7F A3 EB 78 */	mr r3, r29
/* 80AB5E70  48 00 09 5D */	bl getType__12daNpc_Raca_cFv
/* 80AB5E74  98 7D 0F 80 */	stb r3, 0xf80(r29)
/* 80AB5E78  A8 1D 04 B4 */	lha r0, 0x4b4(r29)
/* 80AB5E7C  54 03 04 3E */	clrlwi r3, r0, 0x10
/* 80AB5E80  28 03 FF FF */	cmplwi r3, 0xffff
/* 80AB5E84  38 00 FF FF */	li r0, -1
/* 80AB5E88  41 82 00 08 */	beq lbl_80AB5E90
/* 80AB5E8C  7C 60 1B 78 */	mr r0, r3
lbl_80AB5E90:
/* 80AB5E90  90 1D 0A 7C */	stw r0, 0xa7c(r29)
/* 80AB5E94  4B 6F 66 E9 */	bl dKy_darkworld_check__Fv
/* 80AB5E98  98 7D 0A 89 */	stb r3, 0xa89(r29)
/* 80AB5E9C  7F A3 EB 78 */	mr r3, r29
/* 80AB5EA0  88 1D 0F 80 */	lbz r0, 0xf80(r29)
/* 80AB5EA4  54 00 10 3A */	slwi r0, r0, 2
/* 80AB5EA8  38 9E 00 44 */	addi r4, r30, 0x44
/* 80AB5EAC  7C 84 00 2E */	lwzx r4, r4, r0
/* 80AB5EB0  38 BE 00 38 */	addi r5, r30, 0x38
/* 80AB5EB4  4B 69 25 45 */	bl loadRes__8daNpcT_cFPCScPPCc
/* 80AB5EB8  7C 7E 1B 78 */	mr r30, r3
/* 80AB5EBC  2C 1E 00 04 */	cmpwi r30, 4
/* 80AB5EC0  40 82 01 DC */	bne lbl_80AB609C
/* 80AB5EC4  7F A3 EB 78 */	mr r3, r29
/* 80AB5EC8  3C 80 80 AB */	lis r4, createHeapCallBack__12daNpc_Raca_cFP10fopAc_ac_c@ha /* 0x80AB65FC@ha */
/* 80AB5ECC  38 84 65 FC */	addi r4, r4, createHeapCallBack__12daNpc_Raca_cFP10fopAc_ac_c@l /* 0x80AB65FC@l */
/* 80AB5ED0  38 A0 3A 10 */	li r5, 0x3a10
/* 80AB5ED4  4B 56 45 DD */	bl fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl
/* 80AB5ED8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80AB5EDC  40 82 00 0C */	bne lbl_80AB5EE8
/* 80AB5EE0  38 60 00 05 */	li r3, 5
/* 80AB5EE4  48 00 01 BC */	b lbl_80AB60A0
lbl_80AB5EE8:
/* 80AB5EE8  7F A3 EB 78 */	mr r3, r29
/* 80AB5EEC  48 00 09 01 */	bl isDelete__12daNpc_Raca_cFv
/* 80AB5EF0  2C 03 00 00 */	cmpwi r3, 0
/* 80AB5EF4  41 82 00 0C */	beq lbl_80AB5F00
/* 80AB5EF8  38 60 00 05 */	li r3, 5
/* 80AB5EFC  48 00 01 A4 */	b lbl_80AB60A0
lbl_80AB5F00:
/* 80AB5F00  80 7D 05 78 */	lwz r3, 0x578(r29)
/* 80AB5F04  80 63 00 04 */	lwz r3, 4(r3)
/* 80AB5F08  38 03 00 24 */	addi r0, r3, 0x24
/* 80AB5F0C  90 1D 05 04 */	stw r0, 0x504(r29)
/* 80AB5F10  7F A3 EB 78 */	mr r3, r29
/* 80AB5F14  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 80AB5F18  C0 5F 00 90 */	lfs f2, 0x90(r31)
/* 80AB5F1C  FC 60 08 90 */	fmr f3, f1
/* 80AB5F20  C0 9F 00 94 */	lfs f4, 0x94(r31)
/* 80AB5F24  C0 BF 00 98 */	lfs f5, 0x98(r31)
/* 80AB5F28  FC C0 20 90 */	fmr f6, f4
/* 80AB5F2C  4B 56 46 1D */	bl fopAcM_setCullSizeBox__FP10fopAc_ac_cffffff
/* 80AB5F30  38 7D 05 80 */	addi r3, r29, 0x580
/* 80AB5F34  38 9D 04 D0 */	addi r4, r29, 0x4d0
/* 80AB5F38  38 BD 05 38 */	addi r5, r29, 0x538
/* 80AB5F3C  38 C0 00 03 */	li r6, 3
/* 80AB5F40  38 E0 00 01 */	li r7, 1
/* 80AB5F44  4B 80 A5 ED */	bl init__10Z2CreatureFP3VecP3VecUcUc
/* 80AB5F48  38 7D 09 C0 */	addi r3, r29, 0x9c0
/* 80AB5F4C  38 9D 06 8C */	addi r4, r29, 0x68c
/* 80AB5F50  C0 3F 00 9C */	lfs f1, 0x9c(r31)
/* 80AB5F54  FC 40 08 90 */	fmr f2, f1
/* 80AB5F58  4B 59 AD 45 */	bl init__7dPaPo_cFP9dBgS_Acchff
/* 80AB5F5C  38 1D 04 E4 */	addi r0, r29, 0x4e4
/* 80AB5F60  90 01 00 08 */	stw r0, 8(r1)
/* 80AB5F64  38 7D 06 8C */	addi r3, r29, 0x68c
/* 80AB5F68  38 9D 04 D0 */	addi r4, r29, 0x4d0
/* 80AB5F6C  38 BD 04 BC */	addi r5, r29, 0x4bc
/* 80AB5F70  7F A6 EB 78 */	mr r6, r29
/* 80AB5F74  38 E0 00 01 */	li r7, 1
/* 80AB5F78  39 1D 08 A0 */	addi r8, r29, 0x8a0
/* 80AB5F7C  39 3D 04 F8 */	addi r9, r29, 0x4f8
/* 80AB5F80  39 5D 04 DC */	addi r10, r29, 0x4dc
/* 80AB5F84  4B 5C 02 C5 */	bl Set__9dBgS_AcchFP4cXyzP4cXyzP10fopAc_ac_ciP12dBgS_AcchCirP4cXyzP5csXyzP5csXyz
/* 80AB5F88  38 7D 08 64 */	addi r3, r29, 0x864
/* 80AB5F8C  38 9F 00 00 */	addi r4, r31, 0
/* 80AB5F90  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 80AB5F94  FC 00 00 1E */	fctiwz f0, f0
/* 80AB5F98  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 80AB5F9C  80 81 00 14 */	lwz r4, 0x14(r1)
/* 80AB5FA0  38 A0 00 00 */	li r5, 0
/* 80AB5FA4  7F A6 EB 78 */	mr r6, r29
/* 80AB5FA8  4B 5C D8 B9 */	bl Init__9dCcD_SttsFiiP10fopAc_ac_c
/* 80AB5FAC  38 7D 0E 44 */	addi r3, r29, 0xe44
/* 80AB5FB0  3C 80 80 3B */	lis r4, mCcDCyl__8daNpcT_c@ha /* 0x803B36D8@ha */
/* 80AB5FB4  38 84 36 D8 */	addi r4, r4, mCcDCyl__8daNpcT_c@l /* 0x803B36D8@l */
/* 80AB5FB8  4B 5C E8 FD */	bl Set__8dCcD_CylFRC11dCcD_SrcCyl
/* 80AB5FBC  38 1D 08 64 */	addi r0, r29, 0x864
/* 80AB5FC0  90 1D 0E 88 */	stw r0, 0xe88(r29)
/* 80AB5FC4  3C 60 80 14 */	lis r3, tgHitCallBack__8daNpcT_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf@ha /* 0x80147FA4@ha */
/* 80AB5FC8  38 03 7F A4 */	addi r0, r3, tgHitCallBack__8daNpcT_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf@l /* 0x80147FA4@l */
/* 80AB5FCC  90 1D 0E E8 */	stw r0, 0xee8(r29)
/* 80AB5FD0  38 7D 06 8C */	addi r3, r29, 0x68c
/* 80AB5FD4  3C 80 80 40 */	lis r4, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 80AB5FD8  38 84 61 C0 */	addi r4, r4, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 80AB5FDC  38 84 0F 38 */	addi r4, r4, 0xf38
/* 80AB5FE0  4B 5C 0A CD */	bl CrrPos__9dBgS_AcchFR4dBgS
/* 80AB5FE4  80 1D 07 68 */	lwz r0, 0x768(r29)
/* 80AB5FE8  90 1D 09 30 */	stw r0, 0x930(r29)
/* 80AB5FEC  80 1D 07 6C */	lwz r0, 0x76c(r29)
/* 80AB5FF0  90 1D 09 34 */	stw r0, 0x934(r29)
/* 80AB5FF4  80 1D 07 70 */	lwz r0, 0x770(r29)
/* 80AB5FF8  90 1D 09 38 */	stw r0, 0x938(r29)
/* 80AB5FFC  88 1D 07 74 */	lbz r0, 0x774(r29)
/* 80AB6000  98 1D 09 3C */	stb r0, 0x93c(r29)
/* 80AB6004  A0 1D 07 7C */	lhz r0, 0x77c(r29)
/* 80AB6008  B0 1D 09 44 */	sth r0, 0x944(r29)
/* 80AB600C  A0 1D 07 7E */	lhz r0, 0x77e(r29)
/* 80AB6010  B0 1D 09 46 */	sth r0, 0x946(r29)
/* 80AB6014  80 1D 07 80 */	lwz r0, 0x780(r29)
/* 80AB6018  90 1D 09 48 */	stw r0, 0x948(r29)
/* 80AB601C  80 1D 07 84 */	lwz r0, 0x784(r29)
/* 80AB6020  90 1D 09 4C */	stw r0, 0x94c(r29)
/* 80AB6024  C0 1D 07 8C */	lfs f0, 0x78c(r29)
/* 80AB6028  D0 1D 09 54 */	stfs f0, 0x954(r29)
/* 80AB602C  C0 1D 07 90 */	lfs f0, 0x790(r29)
/* 80AB6030  D0 1D 09 58 */	stfs f0, 0x958(r29)
/* 80AB6034  C0 1D 07 94 */	lfs f0, 0x794(r29)
/* 80AB6038  D0 1D 09 5C */	stfs f0, 0x95c(r29)
/* 80AB603C  80 1D 07 98 */	lwz r0, 0x798(r29)
/* 80AB6040  90 1D 09 60 */	stw r0, 0x960(r29)
/* 80AB6044  C0 1D 07 9C */	lfs f0, 0x79c(r29)
/* 80AB6048  D0 1D 09 64 */	stfs f0, 0x964(r29)
/* 80AB604C  80 1D 07 A0 */	lwz r0, 0x7a0(r29)
/* 80AB6050  90 1D 09 68 */	stw r0, 0x968(r29)
/* 80AB6054  C0 1D 07 24 */	lfs f0, 0x724(r29)
/* 80AB6058  D0 1D 0D F4 */	stfs f0, 0xdf4(r29)
/* 80AB605C  C0 3F 00 A0 */	lfs f1, 0xa0(r31)
/* 80AB6060  C0 1D 0D F4 */	lfs f0, 0xdf4(r29)
/* 80AB6064  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80AB6068  41 82 00 14 */	beq lbl_80AB607C
/* 80AB606C  7F A3 EB 78 */	mr r3, r29
/* 80AB6070  4B 69 2C 01 */	bl setEnvTevColor__8daNpcT_cFv
/* 80AB6074  7F A3 EB 78 */	mr r3, r29
/* 80AB6078  4B 69 2C 55 */	bl setRoomNo__8daNpcT_cFv
lbl_80AB607C:
/* 80AB607C  7F A3 EB 78 */	mr r3, r29
/* 80AB6080  48 00 07 9D */	bl reset__12daNpc_Raca_cFv
/* 80AB6084  38 00 00 01 */	li r0, 1
/* 80AB6088  98 1D 0A 88 */	stb r0, 0xa88(r29)
/* 80AB608C  7F A3 EB 78 */	mr r3, r29
/* 80AB6090  48 00 04 B9 */	bl Execute__12daNpc_Raca_cFv
/* 80AB6094  38 00 00 00 */	li r0, 0
/* 80AB6098  98 1D 0A 88 */	stb r0, 0xa88(r29)
lbl_80AB609C:
/* 80AB609C  7F C3 F3 78 */	mr r3, r30
lbl_80AB60A0:
/* 80AB60A0  39 61 00 30 */	addi r11, r1, 0x30
/* 80AB60A4  4B 8A C1 85 */	bl _restgpr_29
/* 80AB60A8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80AB60AC  7C 08 03 A6 */	mtlr r0
/* 80AB60B0  38 21 00 30 */	addi r1, r1, 0x30
/* 80AB60B4  4E 80 00 20 */	blr 
