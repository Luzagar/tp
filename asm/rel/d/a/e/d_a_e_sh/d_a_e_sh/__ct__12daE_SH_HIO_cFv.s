lbl_8078E34C:
/* 8078E34C  3C 80 80 79 */	lis r4, lit_3902@ha /* 0x80791D70@ha */
/* 8078E350  38 A4 1D 70 */	addi r5, r4, lit_3902@l /* 0x80791D70@l */
/* 8078E354  3C 80 80 79 */	lis r4, __vt__12daE_SH_HIO_c@ha /* 0x807920E0@ha */
/* 8078E358  38 04 20 E0 */	addi r0, r4, __vt__12daE_SH_HIO_c@l /* 0x807920E0@l */
/* 8078E35C  90 03 00 00 */	stw r0, 0(r3)
/* 8078E360  38 00 FF FF */	li r0, -1
/* 8078E364  98 03 00 04 */	stb r0, 4(r3)
/* 8078E368  C0 05 00 2C */	lfs f0, 0x2c(r5)
/* 8078E36C  D0 03 00 08 */	stfs f0, 8(r3)
/* 8078E370  C0 05 00 30 */	lfs f0, 0x30(r5)
/* 8078E374  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 8078E378  C0 05 00 34 */	lfs f0, 0x34(r5)
/* 8078E37C  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 8078E380  C0 05 00 38 */	lfs f0, 0x38(r5)
/* 8078E384  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 8078E388  C0 05 00 3C */	lfs f0, 0x3c(r5)
/* 8078E38C  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 8078E390  C0 05 00 40 */	lfs f0, 0x40(r5)
/* 8078E394  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 8078E398  C0 05 00 44 */	lfs f0, 0x44(r5)
/* 8078E39C  D0 03 00 20 */	stfs f0, 0x20(r3)
/* 8078E3A0  C0 05 00 48 */	lfs f0, 0x48(r5)
/* 8078E3A4  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8078E3A8  38 00 00 00 */	li r0, 0
/* 8078E3AC  98 03 00 28 */	stb r0, 0x28(r3)
/* 8078E3B0  4E 80 00 20 */	blr 
