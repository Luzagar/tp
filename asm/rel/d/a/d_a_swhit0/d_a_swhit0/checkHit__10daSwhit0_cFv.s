lbl_8048668C:
/* 8048668C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80486690  7C 08 02 A6 */	mflr r0
/* 80486694  90 01 00 14 */	stw r0, 0x14(r1)
/* 80486698  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8048669C  7C 7F 1B 78 */	mr r31, r3
/* 804866A0  3C 60 80 40 */	lis r3, g_dComIfG_gameInfo@ha /* 0x804061C0@ha */
/* 804866A4  38 63 61 C0 */	addi r3, r3, g_dComIfG_gameInfo@l /* 0x804061C0@l */
/* 804866A8  88 03 4F AD */	lbz r0, 0x4fad(r3)
/* 804866AC  28 00 00 00 */	cmplwi r0, 0
/* 804866B0  41 82 00 0C */	beq lbl_804866BC
/* 804866B4  38 60 00 00 */	li r3, 0
/* 804866B8  48 00 00 38 */	b lbl_804866F0
lbl_804866BC:
/* 804866BC  38 7F 07 4C */	addi r3, r31, 0x74c
/* 804866C0  48 00 0C 8D */	bl func_8048734C
/* 804866C4  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 804866C8  40 82 00 24 */	bne lbl_804866EC
/* 804866CC  38 7F 06 14 */	addi r3, r31, 0x614
/* 804866D0  4B BF DD 91 */	bl ChkTgHit__12dCcD_GObjInfFv
/* 804866D4  28 03 00 00 */	cmplwi r3, 0
/* 804866D8  41 82 00 14 */	beq lbl_804866EC
/* 804866DC  38 00 00 08 */	li r0, 8
/* 804866E0  98 1F 07 4C */	stb r0, 0x74c(r31)
/* 804866E4  38 60 00 01 */	li r3, 1
/* 804866E8  48 00 00 08 */	b lbl_804866F0
lbl_804866EC:
/* 804866EC  38 60 00 00 */	li r3, 0
lbl_804866F0:
/* 804866F0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 804866F4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 804866F8  7C 08 03 A6 */	mtlr r0
/* 804866FC  38 21 00 10 */	addi r1, r1, 0x10
/* 80486700  4E 80 00 20 */	blr 
