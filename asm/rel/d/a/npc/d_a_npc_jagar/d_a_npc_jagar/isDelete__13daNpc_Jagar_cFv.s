lbl_80A150F8:
/* 80A150F8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80A150FC  7C 08 02 A6 */	mflr r0
/* 80A15100  90 01 00 14 */	stw r0, 0x14(r1)
/* 80A15104  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80A15108  88 03 0F 80 */	lbz r0, 0xf80(r3)
/* 80A1510C  2C 00 00 01 */	cmpwi r0, 1
/* 80A15110  41 82 00 28 */	beq lbl_80A15138
/* 80A15114  40 80 00 10 */	bge lbl_80A15124
/* 80A15118  2C 00 00 00 */	cmpwi r0, 0
/* 80A1511C  40 80 00 14 */	bge lbl_80A15130
/* 80A15120  48 00 00 60 */	b lbl_80A15180
lbl_80A15124:
/* 80A15124  2C 00 00 03 */	cmpwi r0, 3
/* 80A15128  40 80 00 58 */	bge lbl_80A15180
/* 80A1512C  48 00 00 4C */	b lbl_80A15178
lbl_80A15130:
/* 80A15130  38 60 00 00 */	li r3, 0
/* 80A15134  48 00 00 50 */	b lbl_80A15184
lbl_80A15138:
/* 80A15138  3B E0 00 01 */	li r31, 1
/* 80A1513C  38 60 00 D3 */	li r3, 0xd3
/* 80A15140  4B 73 79 6D */	bl daNpcT_chkEvtBit__FUl
/* 80A15144  2C 03 00 00 */	cmpwi r3, 0
/* 80A15148  40 82 00 28 */	bne lbl_80A15170
/* 80A1514C  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 80A15150  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 80A15154  38 63 01 00 */	addi r3, r3, 0x100
/* 80A15158  38 80 00 02 */	li r4, 2
/* 80A1515C  38 A0 00 00 */	li r5, 0
/* 80A15160  4B 61 F0 A9 */	bl isCollect__20dSv_player_collect_cCFiUc
/* 80A15164  2C 03 00 00 */	cmpwi r3, 0
/* 80A15168  40 82 00 08 */	bne lbl_80A15170
/* 80A1516C  3B E0 00 00 */	li r31, 0
lbl_80A15170:
/* 80A15170  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 80A15174  48 00 00 10 */	b lbl_80A15184
lbl_80A15178:
/* 80A15178  38 60 00 00 */	li r3, 0
/* 80A1517C  48 00 00 08 */	b lbl_80A15184
lbl_80A15180:
/* 80A15180  38 60 00 00 */	li r3, 0
lbl_80A15184:
/* 80A15184  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80A15188  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80A1518C  7C 08 03 A6 */	mtlr r0
/* 80A15190  38 21 00 10 */	addi r1, r1, 0x10
/* 80A15194  4E 80 00 20 */	blr 
