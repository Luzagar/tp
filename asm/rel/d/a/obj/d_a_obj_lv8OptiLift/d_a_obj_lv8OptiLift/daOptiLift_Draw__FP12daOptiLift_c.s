lbl_80C8B874:
/* 80C8B874  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80C8B878  7C 08 02 A6 */	mflr r0
/* 80C8B87C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80C8B880  81 83 05 9C */	lwz r12, 0x59c(r3)
/* 80C8B884  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80C8B888  7D 89 03 A6 */	mtctr r12
/* 80C8B88C  4E 80 04 21 */	bctrl 
/* 80C8B890  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80C8B894  7C 08 03 A6 */	mtlr r0
/* 80C8B898  38 21 00 10 */	addi r1, r1, 0x10
/* 80C8B89C  4E 80 00 20 */	blr 
