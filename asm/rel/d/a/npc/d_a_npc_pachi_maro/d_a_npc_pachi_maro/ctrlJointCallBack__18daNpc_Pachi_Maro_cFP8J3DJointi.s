lbl_80A985E4:
/* 80A985E4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80A985E8  7C 08 02 A6 */	mflr r0
/* 80A985EC  90 01 00 14 */	stw r0, 0x14(r1)
/* 80A985F0  7C 60 1B 78 */	mr r0, r3
/* 80A985F4  2C 04 00 00 */	cmpwi r4, 0
/* 80A985F8  40 82 00 30 */	bne lbl_80A98628
/* 80A985FC  3C 60 80 43 */	lis r3, j3dSys@ha /* 0x80434AC8@ha */
/* 80A98600  38 63 4A C8 */	addi r3, r3, j3dSys@l /* 0x80434AC8@l */
/* 80A98604  80 A3 00 38 */	lwz r5, 0x38(r3)
/* 80A98608  80 65 00 14 */	lwz r3, 0x14(r5)
/* 80A9860C  28 03 00 00 */	cmplwi r3, 0
/* 80A98610  41 82 00 18 */	beq lbl_80A98628
/* 80A98614  7C 04 03 78 */	mr r4, r0
/* 80A98618  81 83 0E 3C */	lwz r12, 0xe3c(r3)
/* 80A9861C  81 8C 00 3C */	lwz r12, 0x3c(r12)
/* 80A98620  7D 89 03 A6 */	mtctr r12
/* 80A98624  4E 80 04 21 */	bctrl 
lbl_80A98628:
/* 80A98628  38 60 00 01 */	li r3, 1
/* 80A9862C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80A98630  7C 08 03 A6 */	mtlr r0
/* 80A98634  38 21 00 10 */	addi r1, r1, 0x10
/* 80A98638  4E 80 00 20 */	blr 
