lbl_804865FC:
/* 804865FC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80486600  7C 08 02 A6 */	mflr r0
/* 80486604  90 01 00 14 */	stw r0, 0x14(r1)
/* 80486608  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8048660C  7C 7F 1B 79 */	or. r31, r3, r3
/* 80486610  41 82 00 1C */	beq lbl_8048662C
/* 80486614  3C A0 80 48 */	lis r5, __vt__8cM3dGAab@ha /* 0x80487498@ha */
/* 80486618  38 05 74 98 */	addi r0, r5, __vt__8cM3dGAab@l /* 0x80487498@l */
/* 8048661C  90 1F 00 18 */	stw r0, 0x18(r31)
/* 80486620  7C 80 07 35 */	extsh. r0, r4
/* 80486624  40 81 00 08 */	ble lbl_8048662C
/* 80486628  4B E4 87 15 */	bl __dl__FPv
lbl_8048662C:
/* 8048662C  7F E3 FB 78 */	mr r3, r31
/* 80486630  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80486634  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80486638  7C 08 03 A6 */	mtlr r0
/* 8048663C  38 21 00 10 */	addi r1, r1, 0x10
/* 80486640  4E 80 00 20 */	blr 
