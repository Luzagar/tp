lbl_80323264:
/* 80323264  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80323268  7C 08 02 A6 */	mflr r0
/* 8032326C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80323270  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80323274  7C 7F 1B 79 */	or. r31, r3, r3
/* 80323278  41 82 00 30 */	beq lbl_803232A8
/* 8032327C  3C 60 80 3D */	lis r3, __vt__13J3DPEBlockXlu@ha /* 0x803CE798@ha */
/* 80323280  38 03 E7 98 */	addi r0, r3, __vt__13J3DPEBlockXlu@l /* 0x803CE798@l */
/* 80323284  90 1F 00 00 */	stw r0, 0(r31)
/* 80323288  41 82 00 10 */	beq lbl_80323298
/* 8032328C  3C 60 80 3D */	lis r3, __vt__10J3DPEBlock@ha /* 0x803CDD20@ha */
/* 80323290  38 03 DD 20 */	addi r0, r3, __vt__10J3DPEBlock@l /* 0x803CDD20@l */
/* 80323294  90 1F 00 00 */	stw r0, 0(r31)
lbl_80323298:
/* 80323298  7C 80 07 35 */	extsh. r0, r4
/* 8032329C  40 81 00 0C */	ble lbl_803232A8
/* 803232A0  7F E3 FB 78 */	mr r3, r31
/* 803232A4  4B FA BA 99 */	bl __dl__FPv
lbl_803232A8:
/* 803232A8  7F E3 FB 78 */	mr r3, r31
/* 803232AC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803232B0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803232B4  7C 08 03 A6 */	mtlr r0
/* 803232B8  38 21 00 10 */	addi r1, r1, 0x10
/* 803232BC  4E 80 00 20 */	blr 
