lbl_80725218:
/* 80725218  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8072521C  7C 08 02 A6 */	mflr r0
/* 80725220  90 01 00 14 */	stw r0, 0x14(r1)
/* 80725224  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80725228  7C 7F 1B 79 */	or. r31, r3, r3
/* 8072522C  41 82 00 1C */	beq lbl_80725248
/* 80725230  3C A0 80 72 */	lis r5, __vt__8cM3dGSph@ha /* 0x80725A60@ha */
/* 80725234  38 05 5A 60 */	addi r0, r5, __vt__8cM3dGSph@l /* 0x80725A60@l */
/* 80725238  90 1F 00 10 */	stw r0, 0x10(r31)
/* 8072523C  7C 80 07 35 */	extsh. r0, r4
/* 80725240  40 81 00 08 */	ble lbl_80725248
/* 80725244  4B BA 9A F9 */	bl __dl__FPv
lbl_80725248:
/* 80725248  7F E3 FB 78 */	mr r3, r31
/* 8072524C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80725250  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80725254  7C 08 03 A6 */	mtlr r0
/* 80725258  38 21 00 10 */	addi r1, r1, 0x10
/* 8072525C  4E 80 00 20 */	blr 
