lbl_80492408:
/* 80492408  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8049240C  7C 08 02 A6 */	mflr r0
/* 80492410  90 01 00 14 */	stw r0, 0x14(r1)
/* 80492414  A0 03 09 80 */	lhz r0, 0x980(r3)
/* 80492418  54 00 07 3E */	clrlwi r0, r0, 0x1c
/* 8049241C  2C 00 00 0F */	cmpwi r0, 0xf
/* 80492420  41 82 00 1C */	beq lbl_8049243C
/* 80492424  40 80 00 1C */	bge lbl_80492440
/* 80492428  2C 00 00 00 */	cmpwi r0, 0
/* 8049242C  41 82 00 08 */	beq lbl_80492434
/* 80492430  48 00 00 10 */	b lbl_80492440
lbl_80492434:
/* 80492434  48 00 08 D5 */	bl dropProcInit2__8daTbox_cFv
/* 80492438  48 00 00 08 */	b lbl_80492440
lbl_8049243C:
/* 8049243C  48 00 00 15 */	bl dropProcInit__8daTbox_cFv
lbl_80492440:
/* 80492440  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80492444  7C 08 03 A6 */	mtlr r0
/* 80492448  38 21 00 10 */	addi r1, r1, 0x10
/* 8049244C  4E 80 00 20 */	blr 
