lbl_806302B4:
/* 806302B4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 806302B8  7C 08 02 A6 */	mflr r0
/* 806302BC  90 01 00 24 */	stw r0, 0x24(r1)
/* 806302C0  39 61 00 20 */	addi r11, r1, 0x20
/* 806302C4  4B D3 1F 15 */	bl _savegpr_28
/* 806302C8  7C 7C 1B 78 */	mr r28, r3
/* 806302CC  3B C0 00 00 */	li r30, 0
/* 806302D0  3B A0 00 00 */	li r29, 0
/* 806302D4  3B E0 00 00 */	li r31, 0
lbl_806302D8:
/* 806302D8  38 1F 06 08 */	addi r0, r31, 0x608
/* 806302DC  7C 7C 00 2E */	lwzx r3, r28, r0
/* 806302E0  3C 03 00 01 */	addis r0, r3, 1
/* 806302E4  28 00 FF FF */	cmplwi r0, 0xffff
/* 806302E8  41 82 00 20 */	beq lbl_80630308
/* 806302EC  38 81 00 08 */	addi r4, r1, 8
/* 806302F0  4B 9E 96 CD */	bl fopAcM_SearchByID__FUiPP10fopAc_ac_c
/* 806302F4  80 61 00 08 */	lwz r3, 8(r1)
/* 806302F8  28 03 00 00 */	cmplwi r3, 0
/* 806302FC  41 82 00 0C */	beq lbl_80630308
/* 80630300  93 C3 06 90 */	stw r30, 0x690(r3)
/* 80630304  3B DE 00 01 */	addi r30, r30, 1
lbl_80630308:
/* 80630308  3B BD 00 01 */	addi r29, r29, 1
/* 8063030C  2C 1D 00 0A */	cmpwi r29, 0xa
/* 80630310  3B FF 00 04 */	addi r31, r31, 4
/* 80630314  41 80 FF C4 */	blt lbl_806302D8
/* 80630318  39 61 00 20 */	addi r11, r1, 0x20
/* 8063031C  4B D3 1F 09 */	bl _restgpr_28
/* 80630320  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80630324  7C 08 03 A6 */	mtlr r0
/* 80630328  38 21 00 20 */	addi r1, r1, 0x20
/* 8063032C  4E 80 00 20 */	blr 
