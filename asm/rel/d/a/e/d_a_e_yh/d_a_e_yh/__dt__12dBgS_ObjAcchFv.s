lbl_808039DC:
/* 808039DC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 808039E0  7C 08 02 A6 */	mflr r0
/* 808039E4  90 01 00 14 */	stw r0, 0x14(r1)
/* 808039E8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 808039EC  93 C1 00 08 */	stw r30, 8(r1)
/* 808039F0  7C 7E 1B 79 */	or. r30, r3, r3
/* 808039F4  7C 9F 23 78 */	mr r31, r4
/* 808039F8  41 82 00 38 */	beq lbl_80803A30
/* 808039FC  3C 80 80 80 */	lis r4, __vt__12dBgS_ObjAcch@ha /* 0x808046A8@ha */
/* 80803A00  38 84 46 A8 */	addi r4, r4, __vt__12dBgS_ObjAcch@l /* 0x808046A8@l */
/* 80803A04  90 9E 00 10 */	stw r4, 0x10(r30)
/* 80803A08  38 04 00 0C */	addi r0, r4, 0xc
/* 80803A0C  90 1E 00 14 */	stw r0, 0x14(r30)
/* 80803A10  38 04 00 18 */	addi r0, r4, 0x18
/* 80803A14  90 1E 00 24 */	stw r0, 0x24(r30)
/* 80803A18  38 80 00 00 */	li r4, 0
/* 80803A1C  4B 87 25 79 */	bl __dt__9dBgS_AcchFv
/* 80803A20  7F E0 07 35 */	extsh. r0, r31
/* 80803A24  40 81 00 0C */	ble lbl_80803A30
/* 80803A28  7F C3 F3 78 */	mr r3, r30
/* 80803A2C  4B AC B3 11 */	bl __dl__FPv
lbl_80803A30:
/* 80803A30  7F C3 F3 78 */	mr r3, r30
/* 80803A34  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80803A38  83 C1 00 08 */	lwz r30, 8(r1)
/* 80803A3C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80803A40  7C 08 03 A6 */	mtlr r0
/* 80803A44  38 21 00 10 */	addi r1, r1, 0x10
/* 80803A48  4E 80 00 20 */	blr 
