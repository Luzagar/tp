lbl_8099BBE8:
/* 8099BBE8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8099BBEC  7C 08 02 A6 */	mflr r0
/* 8099BBF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 8099BBF4  4B FF E6 99 */	bl create__13daNpcClerkT_cFv
/* 8099BBF8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8099BBFC  7C 08 03 A6 */	mtlr r0
/* 8099BC00  38 21 00 10 */	addi r1, r1, 0x10
/* 8099BC04  4E 80 00 20 */	blr 
