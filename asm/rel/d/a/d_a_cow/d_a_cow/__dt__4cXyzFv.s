lbl_80658A68:
/* 80658A68  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80658A6C  7C 08 02 A6 */	mflr r0
/* 80658A70  90 01 00 14 */	stw r0, 0x14(r1)
/* 80658A74  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80658A78  7C 7F 1B 79 */	or. r31, r3, r3
/* 80658A7C  41 82 00 10 */	beq lbl_80658A8C
/* 80658A80  7C 80 07 35 */	extsh. r0, r4
/* 80658A84  40 81 00 08 */	ble lbl_80658A8C
/* 80658A88  4B C7 62 B5 */	bl __dl__FPv
lbl_80658A8C:
/* 80658A8C  7F E3 FB 78 */	mr r3, r31
/* 80658A90  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80658A94  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80658A98  7C 08 03 A6 */	mtlr r0
/* 80658A9C  38 21 00 10 */	addi r1, r1, 0x10
/* 80658AA0  4E 80 00 20 */	blr 
