/* Copyright 2019 IBM Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NPU3_REGS_H
#define __NPU3_REGS_H

#define NPU3_FIR(n)				(0x2c00 + (n) * 0x40)
#define NPU3_FIR_MASK(n)			(0x2c03 + (n) * 0x40)
#define NPU3_FIR_ACTION0(n)			(0x2c06 + (n) * 0x40)
#define NPU3_FIR_ACTION1(n)			(0x2c07 + (n) * 0x40)
#define NPU3_FIR_MAX				3

/* NPU RING: Indirect address/data port */
#define NPU3_MISC_SCOM_IND_SCOM_ADDR		0x33e
#define   NPU3_MISC_DA_ADDR			PPC_BITMASK(0, 23)
#define   NPU3_MISC_DA_LEN			PPC_BITMASK(24, 25)
#define     NPU3_MISC_DA_LEN_4B			2
#define     NPU3_MISC_DA_LEN_8B			3
#define NPU3_MISC_SCOM_IND_SCOM_DATA		0x33f

/* NPU RING: Indirect register blocks */
#define NPU3_BLOCK(nib0, nib1)			((nib0) << 20 | (nib1) << 16)
#define NPU3_REG_BLOCK(reg)			((reg) & 0xff0000)
#define NPU3_REG_OFFSET(reg)			((reg) & 0xffff)

#define NPU3_BLOCK_NDL_U(brk)			NPU3_BLOCK(0 + (brk) / 2,\
							   8 + (brk) % 2 * 2)
#define NPU3_BLOCK_NTL_U(brk)			NPU3_BLOCK(0 + (brk) / 2,\
							   9 + (brk) % 2 * 2)
#define NPU3_BLOCK_CQ_SM(n)			NPU3_BLOCK(4, (n))
#define NPU3_BLOCK_CQ_CTL			NPU3_BLOCK(4, 4)
#define NPU3_BLOCK_CQ_DAT			NPU3_BLOCK(4, 5)
#define NPU3_BLOCK_NDL(brk)			NPU3_BLOCK(4 + (brk) / 2,\
							   8 + (brk) % 2 * 2)
#define NPU3_BLOCK_NTL(brk)			NPU3_BLOCK(4 + (brk) / 2,\
							   9 + (brk) % 2 * 2)
#define NPU3_BLOCK_NPU_ATS			NPU3_BLOCK(7, 0)
#define NPU3_BLOCK_NPU_XTS			NPU3_BLOCK(7, 1)
#define NPU3_BLOCK_NPU_MISC			NPU3_BLOCK(7, 2)
#define NPU3_BLOCK_NPU_XTS_ATSD(n)		NPU3_BLOCK(8, (n))

/* NDL_U block registers */
#define NPU3_DLPL_CTL(brk)			(NPU3_BLOCK_NDL_U(brk) + 0xfff4)
#define   NPU3_DLPL_CTL_RESET_RX		PPC_BIT32(0)
#define   NPU3_DLPL_CTL_RESET_MISC		PPC_BIT32(1)
#define NPU3_DLPL_CFG(brk)			(NPU3_BLOCK_NDL_U(brk) + 0xfff8)
#define   NPU3_DLPL_CFG_PRI_BYTESWAP		PPC_BIT32(0)

/* NTL_U block registers */
#define NPU3_NTL_MISC_CFG1(brk)			(NPU3_BLOCK_NTL_U(brk) + 0x0c0)
#define   NPU3_NTL_MISC_CFG1_NTL_RESET		PPC_BITMASK(8, 9)
#define NPU3_NTL_CREQ_HDR_CRED_SND(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x400)
#define NPU3_NTL_PRB_HDR_CRED_SND(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x410)
#define NPU3_NTL_ATR_HDR_CRED_SND(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x418)
#define NPU3_NTL_RSP_HDR_CRED_SND(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x428)
#define NPU3_NTL_CREQ_DAT_CRED_SND(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x430)
#define NPU3_NTL_RSP_DAT_CRED_SND(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x438)
#define NPU3_NTL_CREQ_HDR_CRED_RCV(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x440)
#define NPU3_NTL_DGD_HDR_CRED_RCV(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x448)
#define NPU3_NTL_ATSD_HDR_CRED_RCV(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x460)
#define NPU3_NTL_RSP_HDR_CRED_RCV(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x468)
#define NPU3_NTL_CREQ_DAT_CRED_RCV(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x470)
#define NPU3_NTL_RSP_DAT_CRED_RCV(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x478)
#define NPU3_NTL_CQ_FENCE_STATUS(brk)		(NPU3_BLOCK_NTL_U(brk) + 0x500)
#define   NPU3_NTL_CQ_FENCE_STATUS_FIELD	PPC_BITMASK(0, 1)
#define     NPU3_NTL_CQ_FENCE_STATUS_FULL	3
#define     NPU3_NTL_CQ_FENCE_STATUS_HALF	2
#define     NPU3_NTL_CQ_FENCE_STATUS_NONE	0

/*
 * CQ_SM block registers
 *
 * Definitions here use NPU3_BLOCK_CQ_SM(0), but when npu3_write() is given
 * one of these, it will do corresponding writes to every CQ_SM block.
 */
#define NPU3_SM_MISC_CFG0			(NPU3_BLOCK_CQ_SM(0) + 0x000)
#define   NPU3_SM_MISC_CFG0_ENABLE_PBUS		PPC_BIT(26)
#define   NPU3_SM_MISC_CFG0_ENABLE_SNARF_CPM	PPC_BIT(27)
#define   NPU3_SM_MISC_CFG0_OCAPI_MODE		PPC_BITMASK(44, 48)
#define   NPU3_SM_MISC_CFG0_NVLINK_MODE		PPC_BITMASK(49, 53)
#define NPU3_SM_MISC_CFG1			(NPU3_BLOCK_CQ_SM(0) + 0x008)
#define NPU3_SM_MISC_CFG2			(NPU3_BLOCK_CQ_SM(0) + 0x0f0)
#define NPU3_GPU_MEM_BAR(brk)			(NPU3_BLOCK_CQ_SM(0) + 0x190 + (brk) * 8)
#define   NPU3_GPU_MEM_BAR_ENABLE		PPC_BIT(0)
#define   NPU3_GPU_MEM_BAR_ADDR_MASK		PPC_BITMASK(1, 35)
#define     NPU3_GPU_MEM_BAR_ADDR		PPC_BITMASK(1, 21)
#define     NPU3_GPU_MEM_BAR_SIZE		PPC_BITMASK(22, 35)
#define   NPU3_GPU_MEM_BAR_SL_MODE		PPC_BIT(36)
#define   NPU3_GPU_MEM_BAR_4T_LIMIT		PPC_BIT(37)
#define   NPU3_GPU_MEM_BAR_4T_SELECT		PPC_BITMASK(38, 39)
#define   NPU3_GPU_MEM_BAR_MODE			PPC_BITMASK(40, 43)
#define   NPU3_GPU_MEM_BAR_POISON		PPC_BIT(45)
#define   NPU3_GPU_MEM_BAR_CHIP_EQ_GROUP	PPC_BIT(49)
#define NPU3_NTL_BAR(brk)			(NPU3_BLOCK_CQ_SM(0) + 0x1b8 + (brk) * 8)
#define   NPU3_NTL_BAR_ENABLE			PPC_BIT(0)
#define   NPU3_NTL_BAR_ADDR			PPC_BITMASK(3, 35)
#define   NPU3_NTL_BAR_SIZE			PPC_BITMASK(39, 43)
#define     NPU3_NTL_BAR_SIZE_128K		1
#define NPU3_MMIO_BAR				(NPU3_BLOCK_CQ_SM(0) + 0x1e0)
#define   NPU3_MMIO_BAR_ENABLE			PPC_BIT(0)
#define   NPU3_MMIO_BAR_ADDR			PPC_BITMASK(3, 27)
#define NPU3_GENID_BAR				(NPU3_BLOCK_CQ_SM(0) + 0x1e8)
#define   NPU3_GENID_BAR_ENABLE			PPC_BIT(0)
#define   NPU3_GENID_BAR_ADDR			PPC_BITMASK(3, 32)
#define NPU3_RELAXED_SRC(n)			(NPU3_BLOCK_CQ_SM(0) + 0x1f0 + (n) * 8)
#define   NPU3_RELAXED_SRC_MAX			4
#define   NPU3_RELAXED_SRC_TAG			PPC_BITMASK(0, 13)
#define     NPU3_RELAXED_SRC_GRPCHP		PPC_BITMASK(0, 6)
#define     NPU3_RELAXED_SRC_PEC		PPC_BITMASK(12, 13)
#define   NPU3_RELAXED_SRC_TAGMASK		PPC_BITMASK(14, 27)
#define   NPU3_RELAXED_SRC_MASK_NPU		PPC_BIT(28)
#define   NPU3_RELAXED_SRC_MASK_PCIE		PPC_BIT(29)
#define   NPU3_RELAXED_SRC_MASK_L2L3		PPC_BIT(30)
#define   NPU3_RELAXED_SRC_RDSTART		PPC_BITMASK(32, 39)
#define   NPU3_RELAXED_SRC_RDEND		PPC_BITMASK(40, 47)
#define   NPU3_RELAXED_SRC_WRSTART		PPC_BITMASK(48, 55)
#define   NPU3_RELAXED_SRC_WREND		PPC_BITMASK(56, 63)
#define NPU3_RELAXED_CFG2(brk)			(NPU3_BLOCK_CQ_SM(0) + 0x230 + (brk) * 8)
#define   NPU3_RELAXED_CFG2_CMD_CL_DMA_W	PPC_BIT(0)
#define   NPU3_RELAXED_CFG2_CMD_CL_DMA_W_HP	PPC_BIT(1)
#define   NPU3_RELAXED_CFG2_CMD_CL_DMA_INJ	PPC_BIT(2)
#define   NPU3_RELAXED_CFG2_CMD_PR_DMA_INJ	PPC_BIT(3)
#define   NPU3_RELAXED_CFG2_CMD_DMA_PR_W	PPC_BIT(4)
#define   NPU3_RELAXED_CFG2_CMD_CL_RD_NC_F0	PPC_BIT(5)
#define   NPU3_RELAXED_CFG2_SRC_WRENA(src)	PPC_BIT(32 + (src) * 4)
#define   NPU3_RELAXED_CFG2_SRC_RDENA(src)	PPC_BIT(33 + (src) * 4)
#define   NPU3_RELAXED_CFG2_SRC_AWENA(src)	PPC_BIT(34 + (src) * 4)
#define   NPU3_RELAXED_CFG2_SRC_ARENA(src)	PPC_BIT(35 + (src) * 4)

/* CQ_CTL block registers */
#define NPU3_CTL_MISC_CFG0			(NPU3_BLOCK_CQ_CTL + 0x000)
#define NPU3_CTL_MISC_CFG1			(NPU3_BLOCK_CQ_CTL + 0x008)
#define NPU3_CTL_MISC_CFG2			(NPU3_BLOCK_CQ_CTL + 0x010)
#define   NPU3_CTL_MISC_CFG2_OCAPI_MODE		PPC_BITMASK(0, 4)
#define   NPU3_CTL_MISC_CFG2_NVLINK_MODE	PPC_BITMASK(5, 9)
#define NPU3_CTL_MISC_CFG3			(NPU3_BLOCK_CQ_CTL + 0x018)
#define NPU3_CTL_BDF2PE_CFG(n)			(NPU3_BLOCK_CQ_CTL + 0x180 + (n) * 8)
#define   NPU3_CTL_BDF2PE_CFG_ENABLE		PPC_BIT(0)
#define   NPU3_CTL_BDF2PE_CFG_PE		PPC_BITMASK(4, 7)
#define   NPU3_CTL_BDF2PE_CFG_BDF		PPC_BITMASK(8, 23)

/* CQ_DAT block registers */
#define NPU3_DAT_MISC_CFG1			(NPU3_BLOCK_CQ_DAT + 0x008)
#define   NPU3_DAT_MISC_CFG1_OCAPI_MODE		PPC_BITMASK(40, 44)
#define   NPU3_DAT_MISC_CFG1_NVLINK_MODE	PPC_BITMASK(45, 49)

/* NTL block registers */
#define NPU3_NTL_MISC_CFG2(brk)			(NPU3_BLOCK_NTL(brk) + 0x000)
#define   NPU3_NTL_MISC_CFG2_BRICK_ENABLE	PPC_BIT(0)
#define   NPU3_NTL_MISC_CFG2_NDL_RX_PARITY_ENA	PPC_BIT(16)
#define   NPU3_NTL_MISC_CFG2_NDL_TX_PARITY_ENA	PPC_BIT(17)
#define   NPU3_NTL_MISC_CFG2_NDL_PRI_PARITY_ENA	PPC_BIT(18)
#define   NPU3_NTL_MISC_CFG2_RCV_CREDIT_OVERFLOW_ENA PPC_BIT(19)
#define NPU3_NTL_PRI_CFG(brk)			(NPU3_BLOCK_NTL(brk) + 0x0b0)
#define   NPU3_NTL_PRI_CFG_NDL			PPC_BITMASK(1, 2)

/* NPU_ATS block registers */
#define NPU3_ATS_IODA_ADDR			(NPU3_BLOCK_NPU_ATS + 0x108)
#define   NPU3_ATS_IODA_ADDR_AUTO_INC		PPC_BIT(0)
#define   NPU3_ATS_IODA_ADDR_TBL_SEL		PPC_BITMASK(11, 15)
#define     NPU3_ATS_IODA_ADDR_TBL_TVT		9
#define   NPU3_ATS_IODA_ADDR_TBL_ADDR		PPC_BITMASK(54, 63)
#define NPU3_ATS_IODA_DATA			(NPU3_BLOCK_NPU_ATS + 0x110)
#define   NPU3_ATS_IODA_TVT_XLAT_ADDR		PPC_BITMASK(0, 47)
#define   NPU3_ATS_IODA_TVT_TABLE_LEVEL		PPC_BITMASK(48, 50)
#define   NPU3_ATS_IODA_TVT_TABLE_SIZE		PPC_BITMASK(51, 55)
#define   NPU3_ATS_IODA_TVT_PAGE_SIZE		PPC_BITMASK(59, 63)
#define NPU3_ATS_TCE_KILL			(NPU3_BLOCK_NPU_ATS + 0x120)
#define   NPU3_ATS_TCE_KILL_ALL			PPC_BIT(0)
#define   NPU3_ATS_TCE_KILL_ONE			PPC_BIT(2)
#define   NPU3_ATS_TCE_KILL_PE_NUMBER		PPC_BITMASK(4, 7)
#define   NPU3_ATS_TCE_KILL_ADDRESS		PPC_BITMASK(15, 51)

/* NPU_XTS block registers */
#define NPU3_XTS_CFG				(NPU3_BLOCK_NPU_XTS + 0x020)
#define   NPU3_XTS_CFG_MMIOSD			PPC_BIT(1)
#define   NPU3_XTS_CFG_TRY_ATR_RO		PPC_BIT(6)
#define   NPU3_XTS_CFG_OPENCAPI			PPC_BIT(15)
#define NPU3_XTS_CFG2				(NPU3_BLOCK_NPU_XTS + 0x028)
#define   NPU3_XTS_CFG2_NO_FLUSH_ENA		PPC_BIT(49)
#define   NPU3_XTS_CFG2_XSL2_ENA		PPC_BIT(55)
#define NPU3_XTS_CFG3				(NPU3_BLOCK_NPU_XTS + 0x068)
#define NPU3_XTS_ATSD_HYP(n)			(NPU3_BLOCK_NPU_XTS + 0x100 + (n) * 8)
#define   NPU3_XTS_ATSD_HYP_MSR_HV		PPC_BIT(51)
#define   NPU3_XTS_ATSD_HYP_LPARID		PPC_BITMASK(52, 63)
#define NPU3_XTS_BDF_MAP(n)			(NPU3_BLOCK_NPU_XTS + 0x4000 + (n) * 8)
#define   NPU3_XTS_BDF_MAP_MAX			16
#define   NPU3_XTS_BDF_MAP_VALID		PPC_BIT(0)
#define   NPU3_XTS_BDF_MAP_UNFILT		PPC_BIT(1)
#define   NPU3_XTS_BDF_MAP_STACK		PPC_BITMASK(4, 6)
#define   NPU3_XTS_BDF_MAP_BRICK		PPC_BITMASK(7, 9)
#define   NPU3_XTS_BDF_MAP_BDF			PPC_BITMASK(16, 31)
#define   NPU3_XTS_BDF_MAP_XLAT			PPC_BITMASK(39, 40)
#define   NPU3_XTS_BDF_MAP_LPCR_PS		PPC_BITMASK(41, 43)
#define   NPU3_XTS_BDF_MAP_LPCR_ISL		PPC_BIT(44)
#define   NPU3_XTS_BDF_MAP_LPCR_TC		PPC_BIT(45)
#define   NPU3_XTS_BDF_MAP_LPCR_SC		PPC_BIT(46)
#define   NPU3_XTS_BDF_MAP_LPCR_BOT		PPC_BIT(47)
#define   NPU3_XTS_BDF_MAP_LPARSHORT		PPC_BITMASK(48, 51)
#define   NPU3_XTS_BDF_MAP_LPARID		PPC_BITMASK(52, 63)
#define NPU3_XTS_PID_MAP(n)			(NPU3_BLOCK_NPU_XTS + 0x8000 + (n) * 32)
#define   NPU3_XTS_PID_MAP_VALID_ATRGPA0	PPC_BIT(0)
#define   NPU3_XTS_PID_MAP_VALID_ATRGPA1	PPC_BIT(1)
#define   NPU3_XTS_PID_MAP_VALID_ATSD		PPC_BIT(2)
#define   NPU3_XTS_PID_MAP_MSR			PPC_BITMASK(25, 31)
#define     NPU3_XTS_PID_MAP_MSR_DR		PPC_BIT(25)
#define     NPU3_XTS_PID_MAP_MSR_TA		PPC_BIT(26)
#define     NPU3_XTS_PID_MAP_MSR_HV		PPC_BIT(27)
#define     NPU3_XTS_PID_MAP_MSR_PR		PPC_BIT(28)
#define     NPU3_XTS_PID_MAP_MSR_US		PPC_BIT(29)
#define     NPU3_XTS_PID_MAP_MSR_SF		PPC_BIT(30)
#define     NPU3_XTS_PID_MAP_MSR_UV		PPC_BIT(31)
#define   NPU3_XTS_PID_MAP_LPARSHORT		PPC_BITMASK(40, 43)
#define   NPU3_XTS_PID_MAP_PID       		PPC_BITMASK(44, 63)

/* NPU_MISC block registers */
#define NPU3_MISC_CFG				(NPU3_BLOCK_NPU_MISC + 0x030)
#define   NPU3_MISC_CFG_IPI_PS			PPC_BIT(11)
#define     NPU3_MISC_CFG_IPI_PS_64K		1
#define   NPU3_MISC_CFG_IPI_OS			PPC_BIT(12)
#define     NPU3_MISC_CFG_IPI_OS_AIX		0
#define     NPU3_MISC_CFG_IPI_OS_LINUX		1
#define NPU3_MISC_INT_BAR			(NPU3_BLOCK_NPU_MISC + 0x098)
#define   NPU3_MISC_INT_BAR_ADDR		PPC_BITMASK(0, 39)
#define NPU3_MISC_BDF2PE_CFG(n)			(NPU3_BLOCK_NPU_MISC + 0x100 + (n) * 8)
#define   NPU3_MISC_BDF2PE_CFG_ENABLE		PPC_BIT(0)
#define   NPU3_MISC_BDF2PE_CFG_PE		PPC_BITMASK(4, 7)
#define   NPU3_MISC_BDF2PE_CFG_BDF		PPC_BITMASK(8, 23)
#define NPU3_MISC_PESTB_DATA(pe)		(NPU3_BLOCK_NPU_MISC + 0x200 + (pe) * 8)
#define   NPU3_MISC_PESTB_DATA_DMA_STOPPED_STATE PPC_BIT(0)

/* NPU_XTS_ATSD block registers */
#define NPU3_XTS_ATSD_LAUNCH(n)			(NPU3_BLOCK_NPU_XTS_ATSD(n) + 0x000)

#endif /* __NPU3_REGS_H */
