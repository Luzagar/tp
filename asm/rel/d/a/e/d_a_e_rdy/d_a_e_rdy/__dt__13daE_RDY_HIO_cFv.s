lbl_80779880:
/* 80779880  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80779884  7C 08 02 A6 */	mflr r0
/* 80779888  90 01 00 14 */	stw r0, 0x14(r1)
/* 8077988C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80779890  7C 7F 1B 79 */	or. r31, r3, r3
/* 80779894  41 82 00 1C */	beq lbl_807798B0
/* 80779898  3C A0 80 78 */	lis r5, __vt__13daE_RDY_HIO_c@ha /* 0x8077A81C@ha */
/* 8077989C  38 05 A8 1C */	addi r0, r5, __vt__13daE_RDY_HIO_c@l /* 0x8077A81C@l */
/* 807798A0  90 1F 00 00 */	stw r0, 0(r31)
/* 807798A4  7C 80 07 35 */	extsh. r0, r4
/* 807798A8  40 81 00 08 */	ble lbl_807798B0
/* 807798AC  4B B5 54 91 */	bl __dl__FPv
lbl_807798B0:
/* 807798B0  7F E3 FB 78 */	mr r3, r31
/* 807798B4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 807798B8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 807798BC  7C 08 03 A6 */	mtlr r0
/* 807798C0  38 21 00 10 */	addi r1, r1, 0x10
/* 807798C4  4E 80 00 20 */	blr 
