lbl_80611EF8:
/* 80611EF8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80611EFC  7C 08 02 A6 */	mflr r0
/* 80611F00  90 01 00 14 */	stw r0, 0x14(r1)
/* 80611F04  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80611F08  7C 7F 1B 79 */	or. r31, r3, r3
/* 80611F0C  41 82 00 10 */	beq lbl_80611F1C
/* 80611F10  7C 80 07 35 */	extsh. r0, r4
/* 80611F14  40 81 00 08 */	ble lbl_80611F1C
/* 80611F18  4B CB CE 25 */	bl __dl__FPv
lbl_80611F1C:
/* 80611F1C  7F E3 FB 78 */	mr r3, r31
/* 80611F20  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80611F24  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80611F28  7C 08 03 A6 */	mtlr r0
/* 80611F2C  38 21 00 10 */	addi r1, r1, 0x10
/* 80611F30  4E 80 00 20 */	blr 
