lbl_80662C40:
/* 80662C40  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80662C44  7C 08 02 A6 */	mflr r0
/* 80662C48  90 01 00 14 */	stw r0, 0x14(r1)
/* 80662C4C  4B FF FF 99 */	bl Delete__7daCow_cFv
/* 80662C50  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80662C54  7C 08 03 A6 */	mtlr r0
/* 80662C58  38 21 00 10 */	addi r1, r1, 0x10
/* 80662C5C  4E 80 00 20 */	blr 
