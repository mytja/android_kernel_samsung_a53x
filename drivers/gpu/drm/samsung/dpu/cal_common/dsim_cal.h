/* SPDX-License-Identifier: GPL-2.0-only
 *
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Header file for SAMSUNG DSIM CAL
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SAMSUNG_DSIM_CAL_H__
#define __SAMSUNG_DSIM_CAL_H__

#include <exynos_panel.h>
#include <regs-dsim.h>

#define DSIM_PIXEL_FORMAT_RGB24			0x3E
#define MAX_DSIM_DATALANE_CNT			4

/* EVT1 feature */
#define DPHY_PLL_CLK_GATE_EN	0

#define DSIM_LANE_CLOCK		(1 << 0)
#define DSIM_LANE_DATA0		(1 << 1)
#define DSIM_LANE_DATA1		(1 << 2)
#define DSIM_LANE_DATA2		(1 << 3)
#define DSIM_LANE_DATA3		(1 << 4)

#define MIPI_DSI_ERR_SOT			(1 << 0)
#define MIPI_DSI_ERR_SOT_SYNC			(1 << 1)
#define MIPI_DSI_ERR_EOT_SYNC			(1 << 2)
#define MIPI_DSI_ERR_ESCAPE_MODE_ENTRY_CMD	(1 << 3)
#define MIPI_DSI_ERR_LOW_POWER_TRANSMIT_SYNC	(1 << 4)
#define MIPI_DSI_ERR_HS_RECEIVE_TIMEOUT		(1 << 5)
#define MIPI_DSI_ERR_FALSE_CONTROL		(1 << 6)
#define MIPI_DSI_ERR_ECC_SINGLE_BIT		(1 << 8)
#define MIPI_DSI_ERR_ECC_MULTI_BIT		(1 << 9)
#define MIPI_DSI_ERR_CHECKSUM			(1 << 10)
#define MIPI_DSI_ERR_DATA_TYPE_NOT_RECOGNIZED	(1 << 11)
#define MIPI_DSI_ERR_VCHANNEL_ID_INVALID	(1 << 12)
#define MIPI_DSI_ERR_INVALID_TRANSMIT_LENGTH	(1 << 13)

/*
 * DSI_PROTOCAL_VIOLATION[15] is for protocol violation that is caused
 * EoTp missing So this bit is ignored because of not supporting
 * @S.LSI AP
 */
#define MIPI_DSI_ERR_PROTOCAL_VIOLATION		(1 << 15)
#define MIPI_DSI_ERR_BIT_MASK			(0x3f3f)

#define DSIM_VBP	0
#define DSIM_VSYNC	1
#define DSIM_V_ACTIVE	2
#define DSIM_VFP	3

enum {
	DSIM_COLOR_BAR = 0,
	DSIM_GRAY_GRADATION,
	DSIM_USER_DEFINED,
	DSIM_PRB7_RANDOM,
	DSIM_BIST_MODE_MAX,
};

struct dsim_clks {
	u32 hs_clk;
	u32 esc_clk;
	u32 byte_clk;
	u32 word_clk;

};

struct dsim_regs {
	void __iomem *regs;
	void __iomem *ss_regs;
	void __iomem *phy_regs;
	void __iomem *phy_regs_ex;
};

struct dsim_pll_param {
	char *name;
	unsigned int p;
	unsigned int m;
	unsigned int s;
	unsigned int k;
	unsigned int mfr;
	unsigned int mrr;
	unsigned int sel_pf;
	unsigned int icp;
	unsigned int afc_enb;
	unsigned int extafc;
	unsigned int feed_en;
	unsigned int fsel;
	unsigned int fout_mask;
	unsigned int rsel;
	bool dither_en;

	unsigned int pll_freq; /* in/out parameter: Mhz */
	unsigned int esc_freq; /* Mhz */
	unsigned int cmd_underrun_cnt;
};

enum dsim_panel_mode {
	DSIM_VIDEO_MODE = 0,
	DSIM_COMMAND_MODE,
};

struct stdphy_pms {
	unsigned int p;
	unsigned int m;
	unsigned int s;
	unsigned int k;
	unsigned int mfr;
	unsigned int mrr;
	unsigned int sel_pf;
	unsigned int icp;
	unsigned int afc_enb;
	unsigned int extafc;
	unsigned int feed_en;
	unsigned int fsel;
	unsigned int fout_mask;
	unsigned int rsel;
	bool dither_en;
#if IS_ENABLED(CONFIG_DRM_MCD_COMMON)
/* Save m and k values required for freq_hop */
	unsigned int freq_hop_m;
	unsigned int freq_hop_k;
#endif
};

struct dphy_timing_value {
	unsigned int bps;
	unsigned int clk_prepare;
	unsigned int clk_zero;
	unsigned int clk_post;
	unsigned int clk_trail;
	unsigned int hs_prepare;
	unsigned int hs_zero;
	unsigned int hs_trail;
	unsigned int lpx;
	unsigned int hs_exit;
	unsigned int b_dphyctl;
};

struct dsim_reg_config {
	struct dpu_panel_timing	p_timing;
	enum dsim_panel_mode	mode;
	struct stdphy_pms	dphy_pms;
	enum type_of_ddi	ddi_type;
	unsigned int		bpc;
	unsigned int		data_lane_cnt;
	unsigned int		vt_compensation;
	struct exynos_dsc	dsc;
	unsigned int		cmd_underrun_cnt;
	unsigned int		line_cmd_allow;
	unsigned int		line_stable_vfp;
	u32			burst_cmd_en;
};

void dsim_regs_desc_init(void __iomem *reg_base, const char *name,
		enum dsim_regs_type type, unsigned int id);

/*************** DSIM CAL APIs exposed to DSIM driver ***************/
int dsim_reg_get_link_clock(u32 id);

/* DSIM control */
void dsim_reg_init(u32 id, struct dsim_reg_config *config,
		struct dsim_clks *clks, bool panel_ctrl);
void dsim_reg_start(u32 id);
int dsim_reg_stop(u32 id, u32 lanes);
void dsim_reg_recovery_process(u32 id);

void dsim_reg_enable_packetgo(u32 id, u32 en);

/* ULPS control */
int dsim_reg_exit_ulps_and_start(u32 id, u32 ddi_type, u32 lanes);
int dsim_reg_stop_and_enter_ulps(u32 id, u32 ddi_type, u32 lanes);

/* DSIM interrupt control */
int dsim_reg_get_int_and_clear(u32 id);
void dsim_reg_clear_int(u32 id, u32 int_src);
int dsim_reg_get_int(u32 id);
void dsim_reg_wait_clear_int(u32 id, u32 int_num);

/* DSIM read/write command control */
void dsim_reg_wr_tx_header(u32 id, u32 d_id, unsigned long d0, u32 d1, u32 bta);
void dsim_reg_wr_tx_payload(u32 id, u32 payload);
u32 dsim_reg_header_fifo_is_empty(u32 id);
bool dsim_reg_is_writable_fifo_state(u32 id);
u32 dsim_reg_payload_fifo_is_empty(u32 id);
bool dsim_reg_is_writable_ph_fifo_state(u32 id, u32 cmd_cnt);
u32 dsim_reg_get_rx_fifo(u32 id);
u32 dsim_reg_rx_fifo_is_empty(u32 id);
int dsim_reg_rx_err_handler(u32 id, u32 rx_fifo);
int dsim_reg_wait_pl_fifo_is_empty_timeout(u32 id, unsigned long timeout_us);

void dsim_reg_set_burst_cmd(u32 id, enum dsim_panel_mode mode);
void dsim_reg_enable_packetgo(u32 id, u32 en);
void dsim_reg_set_packetgo_ready(u32 id);

/* For reading DSIM shadow SFR */
void dsim_reg_enable_shadow_read(u32 id, u32 en);

/* For window update and multi resolution feature */
void dsim_reg_function_reset(u32 id);
void dsim_reg_set_partial_update(u32 id, struct dsim_reg_config *config);
void dsim_reg_set_mres(u32 id, struct dsim_reg_config *config);
void dsim_reg_set_cm_underrun_lp_ref(u32 id, u32 lp_ref);
void dsim_reg_set_cmd_ctrl(u32 id, struct dsim_reg_config *config,
						struct dsim_clks *clks);
void dsim_reg_set_porch(u32 id, struct dsim_reg_config *config);

/* DSIM BIST for test */
void dsim_reg_set_bist(u32 id, bool en, u32 mode);

void dsim_reg_set_cmd_transfer_mode(u32 id, u32 lp);
u32 dsim_reg_get_cmd_tansfer_mode(u32 id);

#if defined(CONFIG_EXYNOS_DMA_DSIMFC)
void dsim_reg_set_cmd_access_mode(u32 id, u32 dma_en);
u32  dsim_reg_get_cmd_access_mode(u32 id);
#endif

/* Frequency Hopping feature for EVT1 */
void dsim_reg_set_dphy_freq_hopping(u32 id, u32 p, u32 m, u32 k, u32 en);

/* For reading DSIM STATUS */
u32 dsim_reg_get_link_status2(u32 id);
u32 dsim_reg_get_dphy_status(u32 id);
void dsim_reg_set_datalane_state(u32 id);

/* DSIM SFR dump */
void __dsim_dump(u32 id, struct dsim_regs *regs);
#endif /* __SAMSUNG_DSIM_CAL_H__ */
