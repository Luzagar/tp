lbl_809D9C84:
/* 809D9C84  38 C3 FF FC */	addi r6, r3, -4
/* 809D9C88  38 85 FF FC */	addi r4, r5, -4
/* 809D9C8C  38 00 00 03 */	li r0, 3
/* 809D9C90  7C 09 03 A6 */	mtctr r0
lbl_809D9C94:
/* 809D9C94  80 64 00 04 */	lwz r3, 4(r4)
/* 809D9C98  84 04 00 08 */	lwzu r0, 8(r4)
/* 809D9C9C  90 66 00 04 */	stw r3, 4(r6)
/* 809D9CA0  94 06 00 08 */	stwu r0, 8(r6)
/* 809D9CA4  42 00 FF F0 */	bdnz lbl_809D9C94
/* 809D9CA8  80 04 00 04 */	lwz r0, 4(r4)
/* 809D9CAC  90 06 00 04 */	stw r0, 4(r6)
/* 809D9CB0  4E 80 00 20 */	blr 
