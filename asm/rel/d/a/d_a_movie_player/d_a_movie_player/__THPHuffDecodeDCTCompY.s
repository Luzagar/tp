lbl_80874D8C:
/* 80874D8C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80874D90  7C 08 02 A6 */	mflr r0
/* 80874D94  90 01 00 14 */	stw r0, 0x14(r1)
/* 80874D98  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80874D9C  93 C1 00 08 */	stw r30, 8(r1)
/* 80874DA0  7C 7E 1B 78 */	mr r30, r3
/* 80874DA4  7C 9F 23 78 */	mr r31, r4
/* 80874DA8  7C 00 FF EC */	dcbz 0, r31
/* 80874DAC  3C 80 80 88 */	lis r4, Ydchuff@ha /* 0x80879A40@ha */
/* 80874DB0  38 84 9A 40 */	addi r4, r4, Ydchuff@l /* 0x80879A40@l */
/* 80874DB4  80 84 00 00 */	lwz r4, 0(r4)
/* 80874DB8  48 00 03 E1 */	bl __THPHuffDecodeTab
/* 80874DBC  38 00 00 20 */	li r0, 0x20
/* 80874DC0  7C 1F 07 EC */	dcbz r31, r0
/* 80874DC4  38 A0 00 00 */	li r5, 0
/* 80874DC8  38 00 00 40 */	li r0, 0x40
/* 80874DCC  7C 1F 07 EC */	dcbz r31, r0
/* 80874DD0  2C 03 00 00 */	cmpwi r3, 0
/* 80874DD4  41 82 00 88 */	beq lbl_80874E5C
/* 80874DD8  80 BE 06 A4 */	lwz r5, 0x6a4(r30)
/* 80874DDC  20 C5 00 21 */	subfic r6, r5, 0x21
/* 80874DE0  80 9E 06 A0 */	lwz r4, 0x6a0(r30)
/* 80874DE4  7C E6 18 11 */	subfc. r7, r6, r3
/* 80874DE8  39 05 FF FF */	addi r8, r5, -1
/* 80874DEC  41 81 00 1C */	bgt lbl_80874E08
/* 80874DF0  7C 05 1A 14 */	add r0, r5, r3
/* 80874DF4  7C 85 40 30 */	slw r5, r4, r8
/* 80874DF8  90 1E 06 A4 */	stw r0, 0x6a4(r30)
/* 80874DFC  20 03 00 20 */	subfic r0, r3, 0x20
/* 80874E00  7C A5 04 30 */	srw r5, r5, r0
/* 80874E04  48 00 00 30 */	b lbl_80874E34
lbl_80874E08:
/* 80874E08  80 BE 06 9C */	lwz r5, 0x69c(r30)
/* 80874E0C  7C 80 40 30 */	slw r0, r4, r8
/* 80874E10  84 85 00 04 */	lwzu r4, 4(r5)
/* 80874E14  38 E7 00 01 */	addi r7, r7, 1
/* 80874E18  90 9E 06 A0 */	stw r4, 0x6a0(r30)
/* 80874E1C  7C 84 34 30 */	srw r4, r4, r6
/* 80874E20  90 BE 06 9C */	stw r5, 0x69c(r30)
/* 80874E24  7C 04 02 14 */	add r0, r4, r0
/* 80874E28  90 FE 06 A4 */	stw r7, 0x6a4(r30)
/* 80874E2C  20 E3 00 20 */	subfic r7, r3, 0x20
/* 80874E30  7C 05 3C 30 */	srw r5, r0, r7
lbl_80874E34:
/* 80874E34  7C A0 07 34 */	extsh r0, r5
/* 80874E38  7C 04 00 34 */	cntlzw r4, r0
/* 80874E3C  20 03 00 20 */	subfic r0, r3, 0x20
/* 80874E40  7C 04 00 00 */	cmpw r4, r0
/* 80874E44  40 81 00 18 */	ble lbl_80874E5C
/* 80874E48  38 00 FF FF */	li r0, -1
/* 80874E4C  7C 00 18 30 */	slw r0, r0, r3
/* 80874E50  7C 60 2A 14 */	add r3, r0, r5
/* 80874E54  38 03 00 01 */	addi r0, r3, 1
/* 80874E58  7C 05 07 34 */	extsh r5, r0
lbl_80874E5C:
/* 80874E5C  38 00 00 60 */	li r0, 0x60
/* 80874E60  7C 1F 07 EC */	dcbz r31, r0
/* 80874E64  A8 1E 06 84 */	lha r0, 0x684(r30)
/* 80874E68  7C 00 2A 14 */	add r0, r0, r5
/* 80874E6C  B0 1E 06 84 */	sth r0, 0x684(r30)
/* 80874E70  B0 1F 00 00 */	sth r0, 0(r31)
/* 80874E74  3C 60 80 88 */	lis r3, Yachuff@ha /* 0x80879A4C@ha */
/* 80874E78  80 C3 9A 4C */	lwz r6, Yachuff@l(r3)  /* 0x80879A4C@l */
/* 80874E7C  80 9E 06 A4 */	lwz r4, 0x6a4(r30)
/* 80874E80  38 A6 00 20 */	addi r5, r6, 0x20
/* 80874E84  80 1E 06 A0 */	lwz r0, 0x6a0(r30)
/* 80874E88  38 60 00 01 */	li r3, 1
/* 80874E8C  48 00 02 E4 */	b lbl_80875170
lbl_80874E90:
/* 80874E90  39 24 00 04 */	addi r9, r4, 4
/* 80874E94  2C 04 00 1C */	cmpwi r4, 0x1c
/* 80874E98  5C 0A 4E FE */	rlwnm r10, r0, r9, 0x1b, 0x1f
/* 80874E9C  41 81 00 B0 */	bgt lbl_80874F4C
/* 80874EA0  7D 66 50 AE */	lbzx r11, r6, r10
/* 80874EA4  7D 25 50 AE */	lbzx r9, r5, r10
/* 80874EA8  2C 0B 00 FF */	cmpwi r11, 0xff
/* 80874EAC  41 82 00 0C */	beq lbl_80874EB8
/* 80874EB0  7C 84 4A 14 */	add r4, r4, r9
/* 80874EB4  48 00 02 1C */	b lbl_808750D0
lbl_80874EB8:
/* 80874EB8  39 20 00 05 */	li r9, 5
/* 80874EBC  38 E6 00 58 */	addi r7, r6, 0x58
/* 80874EC0  38 84 00 05 */	addi r4, r4, 5
lbl_80874EC4:
/* 80874EC4  2C 04 00 21 */	cmpwi r4, 0x21
/* 80874EC8  55 4A 08 3C */	slwi r10, r10, 1
/* 80874ECC  41 82 00 18 */	beq lbl_80874EE4
/* 80874ED0  5C 0B 27 FE */	rlwnm r11, r0, r4, 0x1f, 0x1f
/* 80874ED4  85 07 00 04 */	lwzu r8, 4(r7)
/* 80874ED8  7D 4A 5B 78 */	or r10, r10, r11
/* 80874EDC  38 84 00 01 */	addi r4, r4, 1
/* 80874EE0  48 00 00 44 */	b lbl_80874F24
lbl_80874EE4:
/* 80874EE4  81 7E 06 9C */	lwz r11, 0x69c(r30)
/* 80874EE8  38 80 00 01 */	li r4, 1
/* 80874EEC  84 0B 00 04 */	lwzu r0, 4(r11)
/* 80874EF0  85 07 00 04 */	lwzu r8, 4(r7)
/* 80874EF4  91 7E 06 9C */	stw r11, 0x69c(r30)
/* 80874EF8  50 0A 0F FE */	rlwimi r10, r0, 1, 0x1f, 0x1f
/* 80874EFC  48 00 00 14 */	b lbl_80874F10
lbl_80874F00:
/* 80874F00  55 4A 08 3C */	slwi r10, r10, 1
/* 80874F04  5C 0B 27 FE */	rlwnm r11, r0, r4, 0x1f, 0x1f
/* 80874F08  85 07 00 04 */	lwzu r8, 4(r7)
/* 80874F0C  7D 4A 5B 78 */	or r10, r10, r11
lbl_80874F10:
/* 80874F10  7C 0A 40 00 */	cmpw r10, r8
/* 80874F14  38 84 00 01 */	addi r4, r4, 1
/* 80874F18  39 29 00 01 */	addi r9, r9, 1
/* 80874F1C  41 81 FF E4 */	bgt lbl_80874F00
/* 80874F20  48 00 00 10 */	b lbl_80874F30
lbl_80874F24:
/* 80874F24  7C 0A 40 00 */	cmpw r10, r8
/* 80874F28  39 29 00 01 */	addi r9, r9, 1
/* 80874F2C  41 81 FF 98 */	bgt lbl_80874EC4
lbl_80874F30:
/* 80874F30  81 06 00 40 */	lwz r8, 0x40(r6)
/* 80874F34  55 27 10 3A */	slwi r7, r9, 2
/* 80874F38  7C E6 3A 14 */	add r7, r6, r7
/* 80874F3C  80 E7 00 8C */	lwz r7, 0x8c(r7)
/* 80874F40  7C E7 42 14 */	add r7, r7, r8
/* 80874F44  7D 6A 38 AE */	lbzx r11, r10, r7
/* 80874F48  48 00 01 88 */	b lbl_808750D0
lbl_80874F4C:
/* 80874F4C  2C 04 00 21 */	cmpwi r4, 0x21
/* 80874F50  81 5E 06 9C */	lwz r10, 0x69c(r30)
/* 80874F54  41 82 00 34 */	beq lbl_80874F88
/* 80874F58  2C 04 00 20 */	cmpwi r4, 0x20
/* 80874F5C  5C 09 4E FE */	rlwnm r9, r0, r9, 0x1b, 0x1f
/* 80874F60  41 82 00 90 */	beq lbl_80874FF0
/* 80874F64  7D 66 48 AE */	lbzx r11, r6, r9
/* 80874F68  7D 85 48 AE */	lbzx r12, r5, r9
/* 80874F6C  2C 0B 00 FF */	cmpwi r11, 0xff
/* 80874F70  7D 24 62 14 */	add r9, r4, r12
/* 80874F74  41 82 00 E0 */	beq lbl_80875054
/* 80874F78  2C 09 00 21 */	cmpwi r9, 0x21
/* 80874F7C  41 81 00 D8 */	bgt lbl_80875054
/* 80874F80  7D 24 4B 78 */	mr r4, r9
/* 80874F84  48 00 01 4C */	b lbl_808750D0
lbl_80874F88:
/* 80874F88  84 0A 00 04 */	lwzu r0, 4(r10)
/* 80874F8C  54 09 2E FE */	srwi r9, r0, 0x1b
/* 80874F90  91 5E 06 9C */	stw r10, 0x69c(r30)
/* 80874F94  7D 66 48 AE */	lbzx r11, r6, r9
/* 80874F98  7D 45 48 AE */	lbzx r10, r5, r9
/* 80874F9C  2C 0B 00 FF */	cmpwi r11, 0xff
/* 80874FA0  38 8A 00 01 */	addi r4, r10, 1
/* 80874FA4  41 82 00 08 */	beq lbl_80874FAC
/* 80874FA8  48 00 01 28 */	b lbl_808750D0
lbl_80874FAC:
/* 80874FAC  39 60 00 05 */	li r11, 5
/* 80874FB0  38 E0 00 14 */	li r7, 0x14
lbl_80874FB4:
/* 80874FB4  21 4B 00 1F */	subfic r10, r11, 0x1f
/* 80874FB8  7C 09 54 30 */	srw r9, r0, r10
/* 80874FBC  38 87 00 48 */	addi r4, r7, 0x48
/* 80874FC0  7C 86 20 2E */	lwzx r4, r6, r4
/* 80874FC4  7C 09 20 00 */	cmpw r9, r4
/* 80874FC8  39 6B 00 01 */	addi r11, r11, 1
/* 80874FCC  38 E7 00 04 */	addi r7, r7, 4
/* 80874FD0  41 81 FF E4 */	bgt lbl_80874FB4
/* 80874FD4  38 8B 00 01 */	addi r4, r11, 1
/* 80874FD8  81 06 00 40 */	lwz r8, 0x40(r6)
/* 80874FDC  7C E6 3A 14 */	add r7, r6, r7
/* 80874FE0  80 E7 00 8C */	lwz r7, 0x8c(r7)
/* 80874FE4  7C E7 42 14 */	add r7, r7, r8
/* 80874FE8  7D 69 38 AE */	lbzx r11, r9, r7
/* 80874FEC  48 00 00 E4 */	b lbl_808750D0
lbl_80874FF0:
/* 80874FF0  84 0A 00 04 */	lwzu r0, 4(r10)
/* 80874FF4  91 5E 06 9C */	stw r10, 0x69c(r30)
/* 80874FF8  50 09 27 3E */	rlwimi r9, r0, 4, 0x1c, 0x1f
/* 80874FFC  7D 66 48 AE */	lbzx r11, r6, r9
/* 80875000  7C 85 48 AE */	lbzx r4, r5, r9
/* 80875004  2C 0B 00 FF */	cmpwi r11, 0xff
/* 80875008  41 82 00 08 */	beq lbl_80875010
/* 8087500C  48 00 00 C4 */	b lbl_808750D0
lbl_80875010:
/* 80875010  38 E6 00 58 */	addi r7, r6, 0x58
/* 80875014  55 2A D8 08 */	slwi r10, r9, 0x1b
/* 80875018  38 80 00 05 */	li r4, 5
/* 8087501C  50 0A F8 7E */	rlwimi r10, r0, 0x1f, 1, 0x1f
lbl_80875020:
/* 80875020  21 64 00 1F */	subfic r11, r4, 0x1f
/* 80875024  85 07 00 04 */	lwzu r8, 4(r7)
/* 80875028  7D 49 5C 30 */	srw r9, r10, r11
/* 8087502C  7C 09 40 00 */	cmpw r9, r8
/* 80875030  38 84 00 01 */	addi r4, r4, 1
/* 80875034  41 81 FF EC */	bgt lbl_80875020
/* 80875038  81 06 00 40 */	lwz r8, 0x40(r6)
/* 8087503C  54 87 10 3A */	slwi r7, r4, 2
/* 80875040  7C E6 3A 14 */	add r7, r6, r7
/* 80875044  80 E7 00 8C */	lwz r7, 0x8c(r7)
/* 80875048  7C E7 42 14 */	add r7, r7, r8
/* 8087504C  7D 69 38 AE */	lbzx r11, r9, r7
/* 80875050  48 00 00 80 */	b lbl_808750D0
lbl_80875054:
/* 80875054  39 00 FF FF */	li r8, -1
/* 80875058  20 E4 00 21 */	subfic r7, r4, 0x21
/* 8087505C  7D 07 38 30 */	slw r7, r8, r7
/* 80875060  7C 09 38 78 */	andc r9, r0, r7
/* 80875064  38 E6 00 44 */	addi r7, r6, 0x44
/* 80875068  81 5E 06 9C */	lwz r10, 0x69c(r30)
/* 8087506C  21 04 00 21 */	subfic r8, r4, 0x21
/* 80875070  39 68 00 01 */	addi r11, r8, 1
/* 80875074  55 08 10 3A */	slwi r8, r8, 2
/* 80875078  84 0A 00 04 */	lwzu r0, 4(r10)
/* 8087507C  7C E7 42 14 */	add r7, r7, r8
/* 80875080  91 5E 06 9C */	stw r10, 0x69c(r30)
/* 80875084  55 29 08 3C */	slwi r9, r9, 1
/* 80875088  50 09 0F FE */	rlwimi r9, r0, 1, 0x1f, 0x1f
/* 8087508C  85 07 00 04 */	lwzu r8, 4(r7)
/* 80875090  38 80 00 02 */	li r4, 2
/* 80875094  48 00 00 18 */	b lbl_808750AC
lbl_80875098:
/* 80875098  55 29 08 3C */	slwi r9, r9, 1
/* 8087509C  85 07 00 04 */	lwzu r8, 4(r7)
/* 808750A0  7D 29 62 14 */	add r9, r9, r12
/* 808750A4  38 84 00 01 */	addi r4, r4, 1
/* 808750A8  39 6B 00 01 */	addi r11, r11, 1
lbl_808750AC:
/* 808750AC  7C 09 40 00 */	cmpw r9, r8
/* 808750B0  5C 0C 27 FE */	rlwnm r12, r0, r4, 0x1f, 0x1f
/* 808750B4  41 81 FF E4 */	bgt lbl_80875098
/* 808750B8  81 06 00 40 */	lwz r8, 0x40(r6)
/* 808750BC  55 67 10 3A */	slwi r7, r11, 2
/* 808750C0  7C E6 3A 14 */	add r7, r6, r7
/* 808750C4  80 E7 00 8C */	lwz r7, 0x8c(r7)
/* 808750C8  7C E7 42 14 */	add r7, r7, r8
/* 808750CC  7D 69 38 AE */	lbzx r11, r9, r7
lbl_808750D0:
/* 808750D0  71 6C 00 0F */	andi. r12, r11, 0xf
/* 808750D4  7D 6B 26 70 */	srawi r11, r11, 4
/* 808750D8  41 82 00 88 */	beq lbl_80875160
/* 808750DC  7C 63 5A 14 */	add r3, r3, r11
/* 808750E0  21 24 00 21 */	subfic r9, r4, 0x21
/* 808750E4  7D 49 60 11 */	subfc. r10, r9, r12
/* 808750E8  38 E4 FF FF */	addi r7, r4, -1
/* 808750EC  41 81 00 18 */	bgt lbl_80875104
/* 808750F0  7C 84 62 14 */	add r4, r4, r12
/* 808750F4  7C 08 38 30 */	slw r8, r0, r7
/* 808750F8  20 EC 00 20 */	subfic r7, r12, 0x20
/* 808750FC  7D 0B 3C 30 */	srw r11, r8, r7
/* 80875100  48 00 00 28 */	b lbl_80875128
lbl_80875104:
/* 80875104  81 1E 06 9C */	lwz r8, 0x69c(r30)
/* 80875108  7C 07 38 30 */	slw r7, r0, r7
/* 8087510C  84 08 00 04 */	lwzu r0, 4(r8)
/* 80875110  38 8A 00 01 */	addi r4, r10, 1
/* 80875114  91 1E 06 9C */	stw r8, 0x69c(r30)
/* 80875118  7C 08 4C 30 */	srw r8, r0, r9
/* 8087511C  7C E8 3A 14 */	add r7, r8, r7
/* 80875120  21 4C 00 20 */	subfic r10, r12, 0x20
/* 80875124  7C EB 54 30 */	srw r11, r7, r10
lbl_80875128:
/* 80875128  7D 68 00 34 */	cntlzw r8, r11
/* 8087512C  20 EC 00 20 */	subfic r7, r12, 0x20
/* 80875130  7C 08 38 00 */	cmpw r8, r7
/* 80875134  40 81 00 14 */	ble lbl_80875148
/* 80875138  38 E0 FF FF */	li r7, -1
/* 8087513C  7C E7 60 30 */	slw r7, r7, r12
/* 80875140  7D 67 5A 14 */	add r11, r7, r11
/* 80875144  39 6B 00 01 */	addi r11, r11, 1
lbl_80875148:
/* 80875148  3C E0 80 88 */	lis r7, __THPJpegNaturalOrder@ha /* 0x80879034@ha */
/* 8087514C  38 E7 90 34 */	addi r7, r7, __THPJpegNaturalOrder@l /* 0x80879034@l */
/* 80875150  7C E7 18 AE */	lbzx r7, r7, r3
/* 80875154  54 E7 08 3C */	slwi r7, r7, 1
/* 80875158  7D 7F 3B 2E */	sthx r11, r31, r7
/* 8087515C  48 00 00 10 */	b lbl_8087516C
lbl_80875160:
/* 80875160  2C 0B 00 0F */	cmpwi r11, 0xf
/* 80875164  40 82 00 14 */	bne lbl_80875178
/* 80875168  38 63 00 0F */	addi r3, r3, 0xf
lbl_8087516C:
/* 8087516C  38 63 00 01 */	addi r3, r3, 1
lbl_80875170:
/* 80875170  2C 03 00 40 */	cmpwi r3, 0x40
/* 80875174  41 80 FD 1C */	blt lbl_80874E90
lbl_80875178:
/* 80875178  90 9E 06 A4 */	stw r4, 0x6a4(r30)
/* 8087517C  90 1E 06 A0 */	stw r0, 0x6a0(r30)
/* 80875180  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80875184  83 C1 00 08 */	lwz r30, 8(r1)
/* 80875188  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8087518C  7C 08 03 A6 */	mtlr r0
/* 80875190  38 21 00 10 */	addi r1, r1, 0x10
/* 80875194  4E 80 00 20 */	blr 
