lbl_80BDF818:
/* 80BDF818  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80BDF81C  7C 08 02 A6 */	mflr r0
/* 80BDF820  90 01 00 14 */	stw r0, 0x14(r1)
/* 80BDF824  81 83 05 9C */	lwz r12, 0x59c(r3)
/* 80BDF828  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 80BDF82C  7D 89 03 A6 */	mtctr r12
/* 80BDF830  4E 80 04 21 */	bctrl 
/* 80BDF834  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80BDF838  7C 08 03 A6 */	mtlr r0
/* 80BDF83C  38 21 00 10 */	addi r1, r1, 0x10
/* 80BDF840  4E 80 00 20 */	blr 
