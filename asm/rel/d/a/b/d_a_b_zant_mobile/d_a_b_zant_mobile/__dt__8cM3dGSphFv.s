lbl_80652624:
/* 80652624  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80652628  7C 08 02 A6 */	mflr r0
/* 8065262C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80652630  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80652634  7C 7F 1B 79 */	or. r31, r3, r3
/* 80652638  41 82 00 1C */	beq lbl_80652654
/* 8065263C  3C A0 80 65 */	lis r5, __vt__8cM3dGSph@ha /* 0x806528B0@ha */
/* 80652640  38 05 28 B0 */	addi r0, r5, __vt__8cM3dGSph@l /* 0x806528B0@l */
/* 80652644  90 1F 00 10 */	stw r0, 0x10(r31)
/* 80652648  7C 80 07 35 */	extsh. r0, r4
/* 8065264C  40 81 00 08 */	ble lbl_80652654
/* 80652650  4B C7 C6 ED */	bl __dl__FPv
lbl_80652654:
/* 80652654  7F E3 FB 78 */	mr r3, r31
/* 80652658  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8065265C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80652660  7C 08 03 A6 */	mtlr r0
/* 80652664  38 21 00 10 */	addi r1, r1, 0x10
/* 80652668  4E 80 00 20 */	blr 
