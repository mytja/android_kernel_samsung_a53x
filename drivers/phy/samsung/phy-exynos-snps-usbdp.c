// SPDX-License-Identifier: GPL-2.0
/**
 *
 * Copyright (c) 2021 Samsung Electronics Co., Ltd.
 *        http://www.samsung.com
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2  of
 * the License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

//#include <string.h>
//#include <sys/types.h>
//#include <lk/debug.h>
//#include <lk/reg.h>
//#include <lk/err.h>
//#include <platform.h>
//#include <platform/delay.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/io.h>

#include "phy-samsung-usb-cal.h"
#include "snps-usbdp-con-reg.h"
#include "snps-usbdp-tca-reg.h"

#define PHY_RAM_MODE

#ifdef PHY_RAM_MODE
#include "snps-usbdp-ram-code.h"
#endif

#define CRREG_LANE_TX(_reg)	(_reg + ((info->used_phy_port == 0) ? (0x0) : (0x0300)))
#define CRREG_LANE_RX(_reg)	(_reg + ((info->used_phy_port == 0) ? (0x0100) : (0x0200)))

static void cr_clk_high(struct exynos_usbphy_info *info)
{
	void __iomem *base = info->regs_base;
	u32 cr_para_con0 = 0;

	cr_para_con0 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&cr_para_con0))->b.phy0_cr_para_clk = 1;
	writel(cr_para_con0, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	udelay(1);
}

static void cr_clk_low(struct exynos_usbphy_info *info)
{
	void __iomem *base = info->regs_base;
	u32 cr_para_con0 = 0;

	cr_para_con0 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&cr_para_con0))->b.phy0_cr_para_clk = 0;
	writel(cr_para_con0, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	udelay(1);
}

static bool cr_clk_toggle(struct exynos_usbphy_info *info, int cycle_cnt, bool check_ack)
{
	int clk_toggle_cycle;
	u32 reg;

	for (clk_toggle_cycle = 0; clk_toggle_cycle < cycle_cnt; clk_toggle_cycle++) {
		cr_clk_high(info);
		cr_clk_low(info);
		if (check_ack) {
			reg = readl(info->regs_base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
			if (((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p) (&reg))->b.phy0_cr_para_ack) {
				return true;
			}
		}
	}
	if (check_ack)
		return false;
	else
		return true;
}

static void cr_port_clear(struct exynos_usbphy_info *info)
{
	u32 reg;
	void __iomem *base = info->regs_base;

	/*Clear cr_para_con1*/
	writel(0x0, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON1);
	/*Clear cr_para_con2*/
	writel(0x0, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2);
	/*Clear cr_para_con0*/
	reg = 0;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_clk = 0;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_ack = 0;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_addr = 0;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_sel = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);

	/* Check Ack to low */
	do {
		cr_clk_toggle(info, 1, false);
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
		if (((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_ack == 0)
			break;
	} while (1);

	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_clk = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
}

void phy_exynos_snps_usbdp_cr_write(struct exynos_usbphy_info *info, u16 addr, u16 data)
{
	void __iomem *base = info->regs_base;
	u32 cr_para_con0 = 0;
	u32 cr_para_con2 = 0;
	u32 clk_cycle = 0;

	cr_port_clear(info);

	/* write addr */
	cr_para_con0 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&cr_para_con0))->b.phy0_cr_para_addr = addr;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&cr_para_con0))->b.phy0_cr_para_clk = 1;
	writel(cr_para_con0, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	cr_clk_low(info);
	/* enable cr_para_wr_en  */
	// cr_para_con2 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2_p)(&cr_para_con2))->b.phy0_cr_para_wr_data = data;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2_p)(&cr_para_con2))->b.phy0_cr_para_wr_en = 1;
	writel(cr_para_con2, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2);
	/* toggle clock */
	cr_clk_high(info);
	cr_clk_low(info);
	/* enable cr_para_wr_en  */
	// cr_para_con2 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2_p)(&cr_para_con2))->b.phy0_cr_para_wr_en = 0;
	writel(cr_para_con2, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON2);

	/* check cr_para_ack*/
	do {
		cr_clk_high(info);
		cr_para_con0 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
		if ((cr_para_con0 & (0x1 << 4)))
			break;
		cr_clk_low(info);
		clk_cycle++;
	} while (clk_cycle < 10);

	if (clk_cycle == 10)
		pr_info("CR write failed to 0x%04x\n", addr);
	else
		cr_clk_low(info);
}

u16 phy_exynos_snps_usbdp_cr_read(struct exynos_usbphy_info *info, u16 addr)
{
	void __iomem *base = info->regs_base;
	u32 cr_para_con0 = 0;
	u32 cr_para_con1 = 0;
	u32 clk_cycle = 0;

	cr_port_clear(info);

	/* write addr */
	cr_para_con0 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&cr_para_con0))->b.phy0_cr_para_addr = addr;
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&cr_para_con0))->b.phy0_cr_para_clk = 1;
	/* enable cr_para_rd_en  */
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON1_p)(&cr_para_con1))->b.phy0_cr_para_rd_en = 1;
	writel(cr_para_con0, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	writel(cr_para_con1, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON1);

	cr_clk_low(info);

	/* toggle clock */
	cr_clk_high(info);

	/* disable cr_para_rd_en  */
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON1_p)(&cr_para_con1))->b.phy0_cr_para_rd_en = 0;
	writel(cr_para_con1, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON1);

	cr_clk_low(info);

	/* check cr_para_ack*/
	do {
		cr_clk_high(info);
		cr_para_con0 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
		if ((cr_para_con0 & (0x1 << 4)))
			break;
		cr_clk_low(info);
		clk_cycle++;
	} while (clk_cycle < 10);

	if (clk_cycle == 10) {
		pr_info("CR write failed to 0x%04x\n", addr);
		return -1;
	} else {
		cr_clk_low(info);
		cr_para_con1 = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON1);
	}

	return (u16)((cr_para_con1 & (0xffffU << 16)) >> 16);
}

static void phy_reset(struct exynos_usbphy_info *info, int val)
{
	u32 reg;
	void *base;

	base = info->regs_base;
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_RST_CTRL);
	((SNPS_USBDPPHY_REG_PHY_RST_CTRL_p)(&reg))->b.phy_reset = val;
	((SNPS_USBDPPHY_REG_PHY_RST_CTRL_p)(&reg))->b.phy_reset_ovrd_en = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_RST_CTRL);
}

static void lane0_reset(struct exynos_usbphy_info *info, int val)
{
	u32 reg;
	void *base;

	base = info->regs_base;
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_RST_CTRL);
	((SNPS_USBDPPHY_REG_PHY_RST_CTRL_p)(&reg))->b.pipe_lane0_reset_n = (val) ? 0x0 : 0x1;
	((SNPS_USBDPPHY_REG_PHY_RST_CTRL_p)(&reg))->b.pipe_lane0_reset_n_ovrd_en = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_RST_CTRL);
}

#define TCA_USB31 1
#define TCA_DPALT_4L 2
#define TCA_USB31_DPALT_2L 3
#define FLD_OP_MODE 1

int phy_exynos_snps_usbdp_nc2usb_mode(struct exynos_usbphy_info *info, int val)
{
	u32 reg;
	void *tca_base = info->regs_base_2nd;
	int time_out;

	if (val == FLD_OP_MODE) {
		/* Controller Synced Mode */
		/* Clear any pending status */
		writel(0xFFFF, tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_STS);
		/* Ack and Timeout interrupts enabled */
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_EN);
		((SNPS_USBDPPHY_TCA_TCA_INTR_EN_p)(&reg))->b.xa_ack_evt_en = 1;
		((SNPS_USBDPPHY_TCA_TCA_INTR_EN_p)(&reg))->b.xa_timeout_evt_en = 1;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_EN);

		/* Enable USB mode */
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_TCPC);
		/* tcpc_mux_ctrl = NC(0), USB(1), DPalt-4lane(2), USB31+DP=lane0/1(3) */
		((SNPS_USBDPPHY_TCA_TCA_TCPC_p)(&reg))->b.tcpc_mux_control = TCA_USB31;
		((SNPS_USBDPPHY_TCA_TCA_TCPC_p)(&reg))->b.tcpc_connector_orientation = 0;
		((SNPS_USBDPPHY_TCA_TCA_TCPC_p)(&reg))->b.tcpc_low_power_en = 0;
		((SNPS_USBDPPHY_TCA_TCA_TCPC_p)(&reg))->b.tcpc_valid = 1;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_TCPC);

		/* check xa_act_evt */
		for (time_out = 1000; time_out > 0; --time_out) {
			reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_STS);
			if (reg & (0x1 << 0))
				break;
			udelay(1);
		}
		if (time_out <= 0) {
			pr_info("Timeout on the TCA!!\n");
			return -1;
		}
		/* Clear any pending status */
		writel(0xffff, tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_STS);

		/* Ack and Timeout interrupts enabled */
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_EN);
		((SNPS_USBDPPHY_TCA_TCA_INTR_EN_p)(&reg))->b.xa_ack_evt_en = 0;
		((SNPS_USBDPPHY_TCA_TCA_INTR_EN_p)(&reg))->b.xa_timeout_evt_en = 0;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_INTR_EN);
	} else {
		/* System Configuration Mode */
		/* Read current xbar configuration */
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_GEN_STATUS);
		/* Write current xbar configuration to sysmode reg */
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
		/* Enable system config mode : Sync(default) */
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_GCFG);
		((SNPS_USBDPPHY_TCA_TCA_GCFG_p)(&reg))->b.op_mode = 0;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_GCFG);
		/* assert typec_disable, change conn_mode, de-assert typec-dis */
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
		((SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG_p)(&reg))->b.typec_disable = 1;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
		/* waite for a couple of APB clocks */
		udelay(1);
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
		((SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG_p)(&reg))->b.typec_conn_mode = 0;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
		/* waite for a couple of APB clocks */
		udelay(1);
		reg = readl(tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
		((SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG_p)(&reg))->b.typec_disable = 0;
		writel(reg, tca_base + SNPS_USBDPPHY_TCA_TCA_SYSMODE_CFG);
	}

	return 0;
}

void phy_exynos_snps_dptx_reset(struct exynos_usbphy_info *info, int val)
{
	u32 reg;
	void *base = info->regs_base;

	/* disable DP txX & reset */
	reg = readl(base + SNPS_USBDPPHY_REG_DP_CONFIG13);
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx0_disable = 1;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx1_disable = 1;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx2_disable = 1;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx3_disable = 1;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx0_reset = val;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx1_reset = val;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx2_reset = val;
	((SNPS_USBDPPHY_REG_DP_CONFIG13_p)(&reg))->b.dp_tx3_reset = val;
	writel(reg, base + SNPS_USBDPPHY_REG_DP_CONFIG13);
}

void phy_exynos_snps_usbdp_phy_initiate(struct exynos_usbphy_info *info)
{
	u32 reg;
	void *base = info->regs_base;

	/* enable phy power */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CONFIG0);
	((SNPS_USBDPPHY_REG_PHY_CONFIG0_p)(&reg))->b.phy0_ana_pwr_en = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CONFIG0);

	/* phy test power down */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CONFIG2);
	((SNPS_USBDPPHY_REG_PHY_CONFIG2_p)(&reg))->b.phy_test_powerdown = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CONFIG2);


	/* cr_para_sel = cr_para_clk (0 = cr_jtag_clk) */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);
	((SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0_p)(&reg))->b.phy0_cr_para_sel = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CR_PARA_CON0);

	/* Select phy boot up mode */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_SRAM_CON);
	((SNPS_USBDPPHY_REG_PHY_SRAM_CON_p)(&reg))->b.phy0_sram_ext_ld_done = 0;
#ifdef PHY_RAM_MODE
	/* PHY boot up mode : RAM mode
	 * the internal algorithms are first loaded by Raw PCS into the SRAM at which
	 * point user can change the contents of the SRAM.
	 * The updated SRAM contents are used for the adaptation and calibration routines.
	 */
	((SNPS_USBDPPHY_REG_PHY_SRAM_CON_p)(&reg))->b.phy0_sram_bypass = 0;
#else
	/* PHY boot up mode  : ROM mode (sram_bypass)
	 * In this case, the adaptation and calibration algorithms are executed
	 * from the hard wired values within the Raw PCS.
	 */
	((SNPS_USBDPPHY_REG_PHY_SRAM_CON_p)(&reg))->b.phy0_sram_bypass = 1;
#endif
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_SRAM_CON);
	/* When sharing a reference resistor amongst several PHYs,
	 * it may take up to 240 μs per PHY to sequentially calibrate each PHY.
	 * additional delay for REXT calibration */
	udelay(10);

	/* Lane flip */
	if (info->used_phy_port == 1)
		writel(0x4, base + SNPS_USBDPPHY_REG_TCA_CONFIG);
	else
		writel(0x0, base + SNPS_USBDPPHY_REG_TCA_CONFIG);
}

void phy_exynos_snps_usbdp_tune_each(struct exynos_usbphy_info *info, char *name, int val)
{
	void __iomem *base = info->regs_base;
	u32 reg = 0;

	if (!name)
		return;

	if (val == -1)
		return;

	/*
		TX Equalization and Adaptation
		txX_eq_pre[5:0] = |C-1| = 0(g1), 5(g2)
		txX_eq_post[5:0] = |C1| = 10(g1), 8(g2)
		txX_eq_main[5:0] = C0 = 51(g1), 49(g2)
	*/
	if (!strcmp(name, "tx_eq_pre_g1")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20_p)(&reg))->b.ss_tx_eq_pre_g1 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
	} else if (!strcmp(name, "tx_eq_pre_g2")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20_p)(&reg))->b.ss_tx_eq_pre_g2 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
	} else if (!strcmp(name, "tx_eq_post_g1")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19_p)(&reg))->b.ss_tx_eq_post_g1 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
	} else if (!strcmp(name, "tx_eq_post_g2")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19_p)(&reg))->b.ss_tx_eq_post_g2 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
	} else if (!strcmp(name, "tx_eq_main_g1")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18_p)(&reg))->b.ss_tx_eq_main_g1 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
	} else if (!strcmp(name, "tx_eq_main_g2")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18_p)(&reg))->b.ss_tx_eq_main_g2 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
		/*
			RX Equalization
			rxX_eq_att_lvl[2:0] = 0(g1), 0(g2)
			rxX_eq_ctle_boost[4:0] = 7(g1), 7(g2)
			rxX_ana_afe_gain[3:0] = 6(g1), 6(g2)
			rxX_eq_dfe_tap1[7:0] = 0(g1), 0(g2)
		*/
	} else if (!strcmp(name, "rx_eq_att_lvl_g1")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_att_lvl_g1 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	} else if (!strcmp(name, "rx_eq_att_lvl_g2")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_att_lvl_g2 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	} else if (!strcmp(name, "rx_eq_afe_gain_g1")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_afe_gain_g1 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	} else if (!strcmp(name, "rx_eq_afe_gain_g2")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_afe_gain_g2 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	} else if (!strcmp(name, "rx_eq_ctle_boost_g1")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10_p)(&reg))->b.ss_rx_eq_ctle_boost_g1 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);
	} else if (!strcmp(name, "rx_eq_ctle_boost_g2")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10_p)(&reg))->b.ss_rx_eq_ctle_boost_g2 = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);

		/*
			RX term ctrl[2:0]
			TX tern ctrl[2:0]
			*/
	} else if (!strcmp(name, "rx_term_ctrl")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15_p)(&reg))->b.ss_rx_term_ctrl = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15);
	} else if (!strcmp(name, "tx_term_ctrl")) {
		reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG21);
		((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG21_p)(&reg))->b.ss_tx_term_ctrl = val;
		writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG21);
	}
}

void phy_exynos_snps_usbdp_tune_each_cr(struct exynos_usbphy_info *info, char *name, int val)
{
	void __iomem *link_base = info->link_base;
	u32 cr_reg = 0;

	if (!name)
		return;

	if (val == -1)
		return;

	/*
	    TX Equalization and Adaptation
	    txX_eq_pre[5:0] = |C-1| = 0(g1), 5(g2)
	    txX_eq_post[5:0] = |C1| = 10(g1), 8(g2)
	    txX_eq_main[5:0] = C0 = 51(g1), 49(g2)
	*/
	if (!strcmp(name, "tx_eq_pre_g1")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_TX(0x1003));
		cr_reg &= ~(0x3f << 0);
		cr_reg |= (1 << 6) | (val << 0);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_TX(0x1003), cr_reg);
	} else if (!strcmp(name, "tx_eq_pre_g2")) {
		cr_reg = readl(link_base + USB31DRD_LINK_LCSR_TX_DEEMPH);
		cr_reg &= ~(0x3f << 0);
		cr_reg |= (val << 0);
		writel(cr_reg, link_base + USB31DRD_LINK_LCSR_TX_DEEMPH);
	} else if (!strcmp(name, "tx_eq_post_g1")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_TX(0x1003));
		cr_reg &= ~(0x3f << 7);
		cr_reg |= (1 << 13) | (val << 7);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_TX(0x1003), cr_reg);
	} else if (!strcmp(name, "tx_eq_post_g2")) {
		cr_reg = readl(link_base + USB31DRD_LINK_LCSR_TX_DEEMPH);
		cr_reg &= ~(0x3f << 12);
		cr_reg |= (val << 12);
		writel(cr_reg, link_base + USB31DRD_LINK_LCSR_TX_DEEMPH);
	} else if (!strcmp(name, "tx_eq_main_g1")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_TX(0x1002));
		cr_reg &= ~(0x3f << 4);
		cr_reg |= (1 << 10) | (val << 4);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_TX(0x1002), cr_reg);
	} else if (!strcmp(name, "tx_eq_main_g2")) {
		cr_reg = readl(link_base + USB31DRD_LINK_LCSR_TX_DEEMPH);
		cr_reg &= ~(0x3f << 6);
		cr_reg |= (val << 6);
		writel(cr_reg, link_base + USB31DRD_LINK_LCSR_TX_DEEMPH);
	} else if (!strcmp(name, "tx_vswing_lvl")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, 0x22);
		cr_reg &= ~(0x7 << 4);
		cr_reg |= (1 << 7) | (val << 4);
		phy_exynos_snps_usbdp_cr_write(info, 0x22, cr_reg);

		/*
		    RX Equalization
		    rxX_eq_att_lvl[2:0] = 0(g1), 0(g2)
		    rxX_eq_ctle_boost[4:0] = 7(g1), 7(g2)
		    rxX_ana_afe_gain[3:0] = 6(g1), 6(g2)
		    rxX_eq_dfe_tap1[7:0] = 0(g1), 0(g2)
		*/
	} else if (!strcmp(name, "rx_eq_att_lvl")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x301d));
		cr_reg &= ~(0x7 << 4);
		cr_reg |= (1 << 7) | (val << 4);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x301d), cr_reg);
	} else if (!strcmp(name, "rx_eq_afe_gain")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x301d));
		cr_reg &= ~(0xf << 0);
		cr_reg |= (1 << 7) | (val << 4);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x301d), cr_reg);
	} else if (!strcmp(name, "rx_eq_ctle_boost")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x301d));
		cr_reg |= (1 << 7); /* RX_EQ overide enable */
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x301d), cr_reg);
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x301e));
		cr_reg &= ~(0x1f << 8);
		cr_reg |= (val << 8);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x301e), cr_reg);

		/*
		    RX term ctrl[2:0]
		    TX tern ctrl[2:0]
	    */
	} else if (!strcmp(name, "rx_term_ctrl")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x301a));
		cr_reg &= ~(0x7 << 0);
		cr_reg |= (1 << 3) | (val << 8);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x301a), cr_reg);

	} else if (!strcmp(name, "tx_term_ctrl")) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_TX(0x301a));
		cr_reg &= ~(0x7 << 4);
		cr_reg |= (1 << 7) | (val << 4);
		phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_TX(0x301a), cr_reg);

	}
}

#if 0
static void phy_exynos_snps_usbdp_lane_config(struct exynos_usbphy_info *info)
{
	u32 reg;
	void *base = info->regs_base;

	/*
		TX Equalization and Adaptation
		txX_eq_pre[5:0] = |C-1| = 0(g1), 5(g2)
		txX_eq_post[5:0] = |C1| = 10(g1), 8(g2)
		txX_eq_main[5:0] = C0 = 51(g1), 49(g2)
		*/
	/* tx_eq_pre_g1 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20_p)(&reg))->b.ss_tx_eq_pre_g1 = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
	/* tx_eq_pre_g2 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20_p)(&reg))->b.ss_tx_eq_pre_g2 = 5;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG20);
	/* tx_eq_post_g1 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19_p)(&reg))->b.ss_tx_eq_post_g1 = 10;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
	/*tx_eq_post_g2 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19_p)(&reg))->b.ss_tx_eq_post_g2 = 8;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG19);
	/* tx_eq_main_g1 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18_p)(&reg))->b.ss_tx_eq_main_g1 = 52;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
	/* tx_eq_main_g2 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18_p)(&reg))->b.ss_tx_eq_main_g2 = 49;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG18);
	/* txX ana iboost enable / rboost enable : reset(0), databook(3) */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG17);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG17_p)(&reg))->b.ss_tx_ana_iboost_en = 1;
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG17_p)(&reg))->b.ss_tx_ana_rboost_en = 3;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG17);
	/*
		RX Equalization
		rxX_eq_att_lvl[2:0] = 0(g1), 0(g2)
		rxX_eq_ctle_boost[4:0] = 7(g1), 7(g2)
		rxX_ana_afe_gain[3:0] = 6(g1), 6(g2)
		rxX_eq_dfe_tap1[7:0] = 0(g1), 0(g2)
		*/
	/* rx_eq_att_lvl_g1 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_att_lvl_g1 = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	/* rx_eq_att_lvl_g2 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_att_lvl_g2 = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	/* rxX adapt afe/dfe enable */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG8);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG8_p)(&reg))->b.ss_rx_adapt_afe_en_g1 = 3;
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG8_p)(&reg))->b.ss_rx_adapt_afe_en_g2 = 3;
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG8_p)(&reg))->b.ss_rx_adapt_dfe_en_g1 = 3;
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG8_p)(&reg))->b.ss_rx_adapt_dfe_en_g2 = 3;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG8);
	/*rx_eq_afe_gain_g1*/
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_afe_gain_g1 = 6;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	/*rx_eq_afe_gain_g2 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9_p)(&reg))->b.ss_rx_eq_afe_gain_g2 = 6;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG9);
	/*rx_eq_ctle_boost_g1 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10_p)(&reg))->b.ss_rx_eq_ctle_boost_g1 = 7;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);
	/* rx_eq_ctle_boost_g1 */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10_p)(&reg))->b.ss_rx_eq_ctle_boost_g2 = 7;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG10);

	/*
	RX term ctrl[2:0]
	TX tern ctrl[2:0]
	*/
	/*rx_term_ctrl */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15_p)(&reg))->b.ss_rx_term_ctrl = 2;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15);
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CONFIG0);
	((SNPS_USBDPPHY_REG_PHY_CONFIG0_p)(&reg))->b.phy_ss_rx0_term_acdc = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CONFIG0);
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_LANE1_CTRL);
	((SNPS_USBDPPHY_REG_PHY_LANE1_CTRL_p)(&reg))->b.phy_ss_rx1_term_acdc = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_LANE1_CTRL);

	/*tx_term_ctrl */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG21);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG21_p)(&reg))->b.ss_tx_term_ctrl = 2;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG21);

	/*
	rxX sigdet hf threshold[2:0]
	rxX sigdet lf threshold[2:0]
	rxX_sq_ctrl_resp[1:0] = 1 (NA in register map)
	xX_sq_ctrl_thresh[2:0] = 2 (NA in register map)
	*/
	/*rxX sigdet lf threshold : reset(0x36), databook(6)*/
#define SET_SIGDET_VALUE(_x) ((_x << 3) | _x)
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15_p)(&reg))->b.ss_rx_sigdet_lf_filter_en = 1;
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15_p)(&reg))->b.ss_rx_sigdet_lf_threshold_g1 = SET_SIGDET_VALUE(0x6);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15_p)(&reg))->b.ss_rx_sigdet_lf_threshold_g2 = SET_SIGDET_VALUE(0x6);
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG15);

	/*rxX sigdet hf threshold : reset(0x9), databook(1)*/
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG14);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG14_p)(&reg))->b.ss_rx_sigdet_hf_filt_dis = 0;
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG14_p)(&reg))->b.ss_rx_sigdet_hf_threshold_g1 = SET_SIGDET_VALUE(0x1);
	((SNPS_USBDPPHY_REG_PHY_EXT_CONFIG14_p)(&reg))->b.ss_rx_sigdet_hf_threshold_g2 = SET_SIGDET_VALUE(0x1);
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_EXT_CONFIG14);
}
#endif
void phy_exynos_snps_usbdp_config_mplla(struct exynos_usbphy_info *info)
{
	u32 reg;
	void *base = info->regs_base;

	/* Common mplla set */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CONFIG0);
	((SNPS_USBDPPHY_REG_PHY_CONFIG0_p)(&reg))->b.phy0_ss_mplla_ssc_en = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CONFIG0);

	reg = readl(base + SNPS_USBDPPHY_REG_DP_CONFIG12);
	((SNPS_USBDPPHY_REG_DP_CONFIG12_p)(&reg))->b.dp_tx0_mpll_en = 0;
	((SNPS_USBDPPHY_REG_DP_CONFIG12_p)(&reg))->b.dp_tx1_mpll_en = 0;
	((SNPS_USBDPPHY_REG_DP_CONFIG12_p)(&reg))->b.dp_tx2_mpll_en = 0;
	((SNPS_USBDPPHY_REG_DP_CONFIG12_p)(&reg))->b.dp_tx3_mpll_en = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_DP_CONFIG12);
}

static int check_fw_update_done(struct exynos_usbphy_info *info)
{
	void __iomem *base = info->regs_base;

	do {
		cr_clk_toggle(info, 10, false);
		/* check sram_init_done_flag */
		if (((readl(base + SNPS_USBDPPHY_REG_PHY_SRAM_CON)) >> 2))
			break;
		udelay(1); // 2us delay
	} while (1);
	return 0;
}

#ifdef PHY_RAM_MODE
static int update_fw_to_sram(struct exynos_usbphy_info *info)
{
	int cnt, code_size;

	code_size = sizeof(phy_fw_code) / sizeof(struct ram_code);
	for (cnt = 0; cnt < code_size; cnt++) {
		phy_exynos_snps_usbdp_cr_write(info, phy_fw_code[cnt].addr, phy_fw_code[cnt].data);
	}
	return 0;
}

void phy_exynos_snps_usbdp_phy_sram_ext_ld_done(struct exynos_usbphy_info *info, int val)
{
	u32 reg;
	void *base = info->regs_base;

	cr_clk_high(info);
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_SRAM_CON);
	((SNPS_USBDPPHY_REG_PHY_SRAM_CON_p)(&reg))->b.phy0_sram_ext_ld_done = val;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_SRAM_CON);
	cr_clk_low(info);

/* Check init done signal is high */
	do {
		/* need to toggle cr clk to update register value */
		cr_clk_toggle(info, 8, false);

		reg = readl(base + SNPS_USBDPPHY_REG_PHY_SRAM_CON);
	} while (((SNPS_USBDPPHY_REG_PHY_SRAM_CON_p)(&reg))->b.phy0_sram_init_done == 0);
}
#endif

void phy_exynos_snps_usbdp_tune(struct exynos_usbphy_info *info)
{
	u32 cnt = 0;

	if (!info) {
		return;
	}

	if (!info->tune_param) {
		return;
	}

	for (; info->tune_param[cnt].value != EXYNOS_USB_TUNE_LAST; cnt++) {
		char *para_name;
		int val;

		val = info->tune_param[cnt].value;

		if (val == -1) {
			continue;
		}

		para_name = info->tune_param[cnt].name;
		if (!para_name) {
			break;
		}
		/* TODO */
		phy_exynos_snps_usbdp_tune_each_cr(info, para_name, val);
	}
}


static int additional_cr_reg_update(struct exynos_usbphy_info *info)
{
	u16 cr_reg;
	int time_out;
	u16 fw_id;

	/* Wait for RX calibration done */
	for (time_out = 100; time_out > 0; time_out--) {
		cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x303e));
		if (cr_reg & 0x2)
			break;
		mdelay(1);
	}
	if (time_out <= 0) {
		pr_info("Fail usbdp phy init(Not check cal done)\n");
		return -1;
	}

	cr_reg = phy_exynos_snps_usbdp_cr_read(info, 0x003D);
	pr_info("PMA version:0x%04x\n", cr_reg);

	cr_reg = phy_exynos_snps_usbdp_cr_read(info, 0x2010);
	pr_info( "PCS ID:0x%04x\n", cr_reg);

	fw_id = phy_exynos_snps_usbdp_cr_read(info, 0x2011);
	cr_reg = phy_exynos_snps_usbdp_cr_read(info, 0x2012);
	pr_info("Firmware ID:0x%04x, 0x%04x\n", fw_id, cr_reg);

	/* TX VSWING_LVL(Max 7) */
	cr_reg = phy_exynos_snps_usbdp_cr_read(info, 0x22);
	cr_reg &= ~(0x7 << 4);
	cr_reg |= (1 << 7) | (0x7 << 4);
	phy_exynos_snps_usbdp_cr_write(info, 0x22, cr_reg);

	/* TX tune : Enable iBoost / rBoost */
	cr_reg = phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_TX(0x10eb));
	/* iBoost */
	cr_reg |= (1 << 3) | (0x3 << 1);
	phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_TX(0x10eb), cr_reg);

#if IS_ENABLED(CONFIG_SOC_S5E9925) && IS_ENABLED(CONFIG_SOC_S5E9925_EVT0)
	/* P1 mode block power table update: Enable AFE */
	phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x1042), 0x0203);

	/* P2 mode block power table update: Enable AFE */
	phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x1043), 0x181);
#endif

	return 0;
}

int phy_exynos_snps_usbdp_phy_enable(struct exynos_usbphy_info *info)
{

	/* 1. Assert reset (phy_reset = 1) */
	lane0_reset(info, 1);
	phy_reset(info, 1);

	/* 2. use default mplla set valule and configuring the PHY */
	phy_exynos_snps_usbdp_config_mplla(info);
	/* rx/tx lane tune parameter */

	/* 3. Reset DP TX Lane and initated phy */
	phy_exynos_snps_dptx_reset(info, 1);
	phy_exynos_snps_usbdp_phy_initiate(info);

	/* 4. De-assert reset (phy_reset = 0) */
	udelay(20);

	phy_reset(info, 0);
	lane0_reset(info, 0);

#ifdef PHY_RAM_MODE
	/* 3.boot up phy : RAM Mode -> SRAM f/w update
	 * After external access to the SRAM (or any other PHY register) is complete,
	 * input sram_ext_ld_done should be set high, allowing the FSMs in the
	 * Raw PCS to start executing the code from SRAM */
	check_fw_update_done(info);

	/* Override vco_lowfreq_val to 0 all rx lanes */
	phy_exynos_snps_usbdp_cr_write(info, 0x31c5, 0x8000);
	phy_exynos_snps_usbdp_cr_write(info, 0x32c5, 0x8000);

	/* f/w update */
	update_fw_to_sram(info);

	/* sram_ext_ld_done = 1 */
	phy_exynos_snps_usbdp_phy_sram_ext_ld_done(info, 1);
#else
	/* 3.boot up phy : ROM Mode -> Bypass SRAM and skip f/w update */
	pr_info(" PHY Boo mode :ROM(SRAM Bypass) mode\n");

	check_fw_update_done(info);

	phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x30c5), 0x8000);

	phy_exynos_snps_usbdp_cr_write(info, CRREG_LANE_RX(0x3018), 0x0f00);
	phy_exynos_snps_usbdp_cr_read(info, CRREG_LANE_RX(0x3018));

	phy_exynos_snps_usbdp_cr_read(info, 0x63);
	phy_exynos_snps_usbdp_cr_write(info, 0x63, 0x021f);
	phy_exynos_snps_usbdp_cr_read(info, 0x63);
#endif

	/* CR Register update */
	if (additional_cr_reg_update(info) != 0)
		return -1;

	/* Switch from NC to USB : Sync mode */
	if (phy_exynos_snps_usbdp_nc2usb_mode(info, 1) != 0)
		return -1;

	return 0;
}

void phy_exynos_snps_usbdp_phy_disable(struct exynos_usbphy_info *info)
{
	u32 reg;
	void *base = info->regs_base;

	/* phy test power down */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CONFIG2);
	((SNPS_USBDPPHY_REG_PHY_CONFIG2_p)(&reg))->b.phy_test_powerdown = 1;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CONFIG2);

	/* Disable Analog phy power */
	reg = readl(base + SNPS_USBDPPHY_REG_PHY_CONFIG0);
	((SNPS_USBDPPHY_REG_PHY_CONFIG0_p)(&reg))->b.phy0_ana_pwr_en = 0;
	writel(reg, base + SNPS_USBDPPHY_REG_PHY_CONFIG0);
}
