lbl_809F99D0:
/* 809F99D0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 809F99D4  7C 08 02 A6 */	mflr r0
/* 809F99D8  90 01 00 14 */	stw r0, 0x14(r1)
/* 809F99DC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 809F99E0  7C 7F 1B 79 */	or. r31, r3, r3
/* 809F99E4  41 82 00 10 */	beq lbl_809F99F4
/* 809F99E8  7C 80 07 35 */	extsh. r0, r4
/* 809F99EC  40 81 00 08 */	ble lbl_809F99F4
/* 809F99F0  4B 8D 53 4D */	bl __dl__FPv
lbl_809F99F4:
/* 809F99F4  7F E3 FB 78 */	mr r3, r31
/* 809F99F8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 809F99FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 809F9A00  7C 08 03 A6 */	mtlr r0
/* 809F9A04  38 21 00 10 */	addi r1, r1, 0x10
/* 809F9A08  4E 80 00 20 */	blr 
