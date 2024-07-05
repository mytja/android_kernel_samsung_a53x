#ifndef __CMUCAL_VCLK_H__
#define __CMUCAL_VCLK_H__

#include "../../cmucal.h"

enum vclk_id {

/* DVFS VCLK*/
	VCLK_VDDI = DFS_VCLK_TYPE,
	VCLK_VDD_MIF,
	VCLK_VDD_G3D,
	VCLK_VDD_CAM,
	VCLK_VDD_CPUCL2,
	VCLK_VDD_CPUCL0,
	VCLK_VDD_CPUCL1,
	VCLK_VDD_ALIVE,
	VCLK_VDD_NPU,
	VCLK_VDD_INT_CMU,
	end_of_dfs_vclk,
	num_of_dfs_vclk = end_of_dfs_vclk - DFS_VCLK_TYPE,


/* SPECIAL VCLK*/
	VCLK_MUX_CHUB_TIMER = (MASK_OF_ID & end_of_dfs_vclk) | VCLK_TYPE,
	VCLK_MUX_CPUCL0_CMUREF,
	VCLK_MUX_CLKCMU_CMU_BOOST_CPU,
	VCLK_MUX_CPUCL1_CMUREF,
	VCLK_MUX_CPUCL2_CMUREF,
	VCLK_MUX_DSU_CMUREF,
	VCLK_MUX_CLK_DSU_POWERIP,
	VCLK_MUX_CLK_HSI0_USB32DRD,
	VCLK_CLKCMU_HSI0_USB32DRD,
	VCLK_MUX_MIF_CMUREF,
	VCLK_MUX_CLKCMU_CMU_BOOST_MIF,
	VCLK_MUX_NOCL0_CMUREF,
	VCLK_MUX_CLKCMU_CMU_BOOST,
	VCLK_MUX_NOCL1A_CMUREF,
	VCLK_MUX_NOCL1B_CMUREF,
	VCLK_MUX_NOCL2A_CMUREF,
	VCLK_MUX_CLKCMU_CMU_BOOST_CAM,
	VCLK_MUX_CLKCMU_DPUB_DSIM,
	VCLK_CLKCMU_HSI0_DPOSC,
	VCLK_DIV_CLK_ALIVE_SPMI,
	VCLK_DIV_CLK_ALIVE_DBGCORE_UART,
	VCLK_DIV_CLK_ALIVE_PMU_SUB,
	VCLK_DIV_CLK_AUD_DSIF,
	VCLK_CLKCMU_AUD_CPU,
	VCLK_CLKCMU_AUD_AUDIF0,
	VCLK_CLKCMU_AUD_AUDIF1,
	VCLK_DIV_CLK_AUD_SERIAL_LIF,
	VCLK_CLK_AUD_MCLK,
	VCLK_DIV_CLK_CHUB_DMAILBOX,
	VCLK_CLKALIVE_CHUB_PERI,
	VCLK_DIV_CLK_CHUB_USI0,
	VCLK_DIV_CLK_CHUB_USI1,
	VCLK_DIV_CLK_CHUB_USI3,
	VCLK_DIV_CLK_CHUB_USI2,
	VCLK_DIV_CLK_CHUB_SPI_MS_CTRL,
	VCLK_DIV_CLK_CHUB_SPI_I2C0,
	VCLK_DIV_CLK_CHUB_SPI_I2C1,
	VCLK_DIV_CLK_CMGP_USI4,
	VCLK_CLKALIVE_CMGP_PERI,
	VCLK_DIV_CLK_CMGP_USI1,
	VCLK_DIV_CLK_CMGP_USI0,
	VCLK_DIV_CLK_CMGP_USI2,
	VCLK_DIV_CLK_CMGP_USI3,
	VCLK_DIV_CLK_CMGP_USI5,
	VCLK_DIV_CLK_CMGP_USI6,
	VCLK_DIV_CLK_CMGP_I3C,
	VCLK_DIV_CLK_CMGP_SPI_MS_CTRL,
	VCLK_DIV_CLK_CMGP_SPI_I2C0,
	VCLK_DIV_CLK_CMGP_SPI_I2C1,
	VCLK_CLKCMU_HPM,
	VCLK_DIV_CLKCMU_CIS_CLK0,
	VCLK_DIV_CLKCMU_CIS_CLK1,
	VCLK_DIV_CLKCMU_CIS_CLK2,
	VCLK_DIV_CLKCMU_CIS_CLK3,
	VCLK_DIV_CLKCMU_CIS_CLK4,
	VCLK_DIV_CLKCMU_CIS_CLK5,
	VCLK_DIV_CLKCMU_CIS_CLK6,
	VCLK_MUX_CLKCMU_CIS_CLK7,
	VCLK_DIV_CLK_CPUCL1_CORE_1,
	VCLK_DIV_CLK_CPUCL2_HTU,
	VCLK_CLK_DNC_ADD_CH_CLK,
	VCLK_CLK_DSU_STR_DEM_CLK,
	VCLK_DIV_CLK_PERIC0_USI04,
	VCLK_MUX_CLK_PERIC0_I2C,
	VCLK_MUX_CLK_PERIC1_UART_BT,
	VCLK_DIV_CLK_PERIC1_USI07,
	VCLK_DIV_CLK_PERIC1_USI08,
	VCLK_DIV_CLK_PERIC1_USI09,
	VCLK_DIV_CLK_PERIC1_USI10,
	VCLK_MUX_CLK_PERIC1_SPI_MS_CTRL,
	VCLK_MUX_CLK_PERIC1_USI07_SPI_I2C,
	VCLK_MUX_CLK_PERIC1_USI08_SPI_I2C,
	VCLK_DIV_CLK_PERIC2_USI00,
	VCLK_DIV_CLK_PERIC2_USI01,
	VCLK_DIV_CLK_PERIC2_USI02,
	VCLK_DIV_CLK_PERIC2_USI03,
	VCLK_DIV_CLK_PERIC2_USI05,
	VCLK_DIV_CLK_PERIC2_USI06,
	VCLK_MUX_CLK_PERIC2_SPI_MS_CTRL,
	VCLK_DIV_CLK_PERIC2_USI11,
	VCLK_MUX_CLK_PERIC2_UART_DBG,
	VCLK_MUX_CLK_PERIC2_USI00_SPI_I2C,
	VCLK_MUX_CLK_PERIC2_USI01_SPI_I2C,
	VCLK_DIV_CLK_VTS_SERIAL_LIF,
	VCLK_CLKCMU_VTS_DMIC,
	VCLK_DIV_CLK_VTS_DMAILBOX_CCLK,
	VCLK_CLK_YUVP_ADD_CH_CLK,
	VCLK_MUX_CLKALIVE_GNSS_NOC,
	VCLK_CLKCMU_DNC_NOC,
	VCLK_CLKALIVE_DNC_NOC,
	VCLK_MUX_CLKCMU_MIF_SWITCH,
	end_of_vclk,
	num_of_vclk = end_of_vclk - ((MASK_OF_ID & end_of_dfs_vclk) | VCLK_TYPE),


/* COMMON VCLK*/
	VCLK_BLK_CMU = (MASK_OF_ID & end_of_vclk) | COMMON_VCLK_TYPE,
	VCLK_BLK_S2D,
	VCLK_BLK_ALIVE,
	VCLK_BLK_AUD,
	VCLK_BLK_CHUB,
	VCLK_BLK_CMGP,
	VCLK_BLK_CPUCL0,
	VCLK_BLK_CPUCL1,
	VCLK_BLK_CPUCL2,
	VCLK_BLK_DNC,
	VCLK_BLK_DSU,
	VCLK_BLK_G3DCORE,
	VCLK_BLK_GNPU,
	VCLK_BLK_GNPUP,
	VCLK_BLK_HSI0,
	VCLK_BLK_PERIC1,
	VCLK_BLK_PERIC2,
	VCLK_BLK_SDMA,
	VCLK_BLK_UFD,
	VCLK_BLK_VTS,
	VCLK_BLK_CPUCL0_GLB,
	VCLK_BLK_DSP,
	VCLK_BLK_M2M,
	VCLK_BLK_MFC0,
	VCLK_BLK_MFC1,
	VCLK_BLK_SSP,
	end_of_common_vclk,
	num_of_common_vclk = end_of_common_vclk - ((MASK_OF_ID & end_of_vclk) | COMMON_VCLK_TYPE),


/* GATE VCLK*/
	VCLK_IP_ALIVE_CMU_ALIVE = (MASK_OF_ID & end_of_common_vclk) | GATE_VCLK_TYPE,
	VCLK_IP_APBIF_PMU_ALIVE,
	VCLK_IP_RTC,
	VCLK_IP_APBIF_INTCOMB_VGPIO2AP,
	VCLK_IP_APBIF_INTCOMB_VGPIO2APM,
	VCLK_IP_APBIF_INTCOMB_VGPIO2PMU,
	VCLK_IP_TOP_RTC,
	VCLK_IP_CLKMON,
	VCLK_IP_DBGCORE_UART,
	VCLK_IP_DTZPC_ALIVE,
	VCLK_IP_GREBEINTEGRATION,
	VCLK_IP_HW_SCANDUMP_CLKSTOP_CTRL,
	VCLK_IP_SPMI_MASTER_PMIC,
	VCLK_IP_SLH_AXI_MI_C_MODEM,
	VCLK_IP_SLH_AXI_MI_C_VTS,
	VCLK_IP_SLH_AXI_MI_P_APM,
	VCLK_IP_SLH_AXI_SI_C_CMGP,
	VCLK_IP_LH_AXI_SI_D_APM,
	VCLK_IP_SLH_AXI_SI_LP_VTS,
	VCLK_IP_MAILBOX_APM_AP,
	VCLK_IP_MAILBOX_APM_CP,
	VCLK_IP_MAILBOX_AP_CP,
	VCLK_IP_MAILBOX_AP_CP_S,
	VCLK_IP_MAILBOX_AP_DBGCORE,
	VCLK_IP_PMU_INTR_GEN,
	VCLK_IP_ROM_CRC32_HOST,
	VCLK_IP_SWEEPER_P_ALIVE,
	VCLK_IP_SYSREG_ALIVE,
	VCLK_IP_VGEN_LITE_ALIVE,
	VCLK_IP_WDT_ALIVE,
	VCLK_IP_XIU_DP_ALIVE,
	VCLK_IP_CHUB_RTC,
	VCLK_IP_SLH_AXI_MI_C_CHUB,
	VCLK_IP_SLH_AXI_MI_C_GNSS,
	VCLK_IP_SLH_AXI_SI_LP_CHUB,
	VCLK_IP_MAILBOX_APM_CHUB,
	VCLK_IP_MAILBOX_APM_GNSS,
	VCLK_IP_MAILBOX_APM_VTS,
	VCLK_IP_MAILBOX_AP_CHUB,
	VCLK_IP_MAILBOX_AP_GNSS,
	VCLK_IP_MAILBOX_CP_CHUB,
	VCLK_IP_MAILBOX_CP_GNSS,
	VCLK_IP_MAILBOX_GNSS_CHUB,
	VCLK_IP_MAILBOX_SHARED_SRAM,
	VCLK_IP_MAILBOX_VTS_CHUB,
	VCLK_IP_SLH_AXI_SI_PPU_ALIVE_CPUCL0,
	VCLK_IP_INTMEM,
	VCLK_IP_PMU,
	VCLK_IP_SLH_AXI_SI_IP_APM,
	VCLK_IP_SLH_AXI_MI_ID_DBGCORE,
	VCLK_IP_SLH_AXI_SI_P_ALIVEDNC,
	VCLK_IP_SPC_ALIVE,
	VCLK_IP_APM_DMA,
	VCLK_IP_APBIF_GPIO_ALIVE,
	VCLK_IP_MCT_ALIVE,
	VCLK_IP_DFT_ALIVE,
	VCLK_IP_AUD_CMU_AUD,
	VCLK_IP_ABOX,
	VCLK_IP_AD_APB_SMMU_AUD,
	VCLK_IP_AD_APB_SMMU_AUD_NS1,
	VCLK_IP_AD_APB_SMMU_AUD_S,
	VCLK_IP_AXI_US_32TO128,
	VCLK_IP_BAAW_D_AUDVTS,
	VCLK_IP_D_TZPC_AUD,
	VCLK_IP_SLH_AXI_MI_LD_HSI0AUD,
	VCLK_IP_SLH_AXI_MI_P_AUD,
	VCLK_IP_LH_QDI_SI_D_AUD,
	VCLK_IP_SLH_AXI_SI_LD_AUDVTS,
	VCLK_IP_MAILBOX_AUD0,
	VCLK_IP_MAILBOX_AUD1,
	VCLK_IP_MAILBOX_AUD2,
	VCLK_IP_MAILBOX_AUD3,
	VCLK_IP_PERI_AXI_ASB,
	VCLK_IP_PPMU_AUD,
	VCLK_IP_SMMU_AUD,
	VCLK_IP_SYSREG_AUD,
	VCLK_IP_TREX_AUD,
	VCLK_IP_WDT_AUD,
	VCLK_IP_SLH_AXI_SI_LD_AUDHSI0,
	VCLK_IP_VGEN_LITE_AUD,
	VCLK_IP_AD_APB_VGEN_LITE,
	VCLK_IP_SERIAL_LIF,
	VCLK_IP_DFTMUX_AUD,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_AUD,
	VCLK_IP_DMIC_AUD0,
	VCLK_IP_DMIC_AUD1,
	VCLK_IP_DMIC_AUD2,
	VCLK_IP_BYRP_CMU_BYRP,
	VCLK_IP_AD_APB_BYRP,
	VCLK_IP_D_TZPC_BYRP,
	VCLK_IP_LH_AXI_SI_D_BYRP,
	VCLK_IP_PPMU_BYRP,
	VCLK_IP_SYSMMU_D_BYRP,
	VCLK_IP_SYSREG_BYRP,
	VCLK_IP_XIU_D_BYRP,
	VCLK_IP_SLH_AXI_MI_P_BYRP,
	VCLK_IP_LH_AST_SI_OTF_BYRPRGBP,
	VCLK_IP_SIPU_BYRP,
	VCLK_IP_VGEN_LITE_BYRP,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_BYRP,
	VCLK_IP_CHUB_CMU_CHUB,
	VCLK_IP_BPS_AXI_P_CHUB,
	VCLK_IP_CM4_CHUB,
	VCLK_IP_DMAILBOX_CHUB,
	VCLK_IP_SLH_AXI_MI_LP_CHUB,
	VCLK_IP_SLH_AXI_MI_P_CHUB,
	VCLK_IP_SLH_AXI_SI_C_CHUB,
	VCLK_IP_PWM_CHUB,
	VCLK_IP_SYSREG_CHUB,
	VCLK_IP_TIMER_CHUB,
	VCLK_IP_WDT_CHUB,
	VCLK_IP_XIU_DP_CHUB,
	VCLK_IP_I2C_CHUB,
	VCLK_IP_I3C_CHUB,
	VCLK_IP_USI_CHUB0,
	VCLK_IP_USI_CHUB1,
	VCLK_IP_USI_CHUB3,
	VCLK_IP_USI_CHUB2,
	VCLK_IP_BPS_AXI_LP_CHUB,
	VCLK_IP_APBIF_CHUB_COMBINE_WAKEUP_SRC,
	VCLK_IP_SWEEPER_C_CHUB,
	VCLK_IP_APBIF_GPIO_CHUB,
	VCLK_IP_SYSREG_COMBINE_CHUB2AP,
	VCLK_IP_SYSREG_COMBINE_CHUB2APM,
	VCLK_IP_ASYNCINTERRUPT,
	VCLK_IP_SLH_AXI_MI_LD_DNCCHUB,
	VCLK_IP_BPS_AXI_LD_DNCCHUB,
	VCLK_IP_MAILBOX_CHUB_DNC,
	VCLK_IP_SPI_I2C_CHUB0,
	VCLK_IP_SPI_I2C_CHUB1,
	VCLK_IP_SPI_MULTI_SLV_Q_CTRL_CHUB,
	VCLK_IP_CHUB_ALV,
	VCLK_IP_APBIF_UPMU_CHUB,
	VCLK_IP_CMGP_CMU_CMGP,
	VCLK_IP_APBIF_GPIO_CMGP,
	VCLK_IP_D_TZPC_CMGP,
	VCLK_IP_SPI_I2C_CMGP0,
	VCLK_IP_SPI_I2C_CMGP1,
	VCLK_IP_I2C_CMGP2,
	VCLK_IP_I2C_CMGP3,
	VCLK_IP_I3C_CMGP,
	VCLK_IP_SLH_AXI_MI_C_CMGP,
	VCLK_IP_SYSREG_CMGP,
	VCLK_IP_SYSREG_CMGP2APM,
	VCLK_IP_SYSREG_CMGP2CP,
	VCLK_IP_SYSREG_CMGP2PMU_AP,
	VCLK_IP_USI_CMGP0,
	VCLK_IP_USI_CMGP1,
	VCLK_IP_USI_CMGP2,
	VCLK_IP_USI_CMGP3,
	VCLK_IP_SYSREG_CMGP2CHUB,
	VCLK_IP_SYSREG_CMGP2GNSS,
	VCLK_IP_I2C_CMGP4,
	VCLK_IP_I2C_CMGP5,
	VCLK_IP_I2C_CMGP6,
	VCLK_IP_USI_CMGP4,
	VCLK_IP_USI_CMGP5,
	VCLK_IP_USI_CMGP6,
	VCLK_IP_SPI_MULTI_SLV_Q_CTRL_CMGP,
	VCLK_IP_SLH_AXI_SI_LP_CMGPUFD,
	VCLK_IP_CMGP_I2C,
	VCLK_IP_ADD_CPUCL0_0,
	VCLK_IP_BUSIF_ADD_CPUCL0_0,
	VCLK_IP_BUSIF_STR_CPUCL0_0,
	VCLK_IP_CPUCL0_CMU_CPUCL0,
	VCLK_IP_HTU_CPUCL0,
	VCLK_IP_CPUCL0,
	VCLK_IP_STR_CPUCL0_0,
	VCLK_IP_ADM_APB_G_CLUSTER0,
	VCLK_IP_CPUCL0_GLB_CMU_CPUCL0_GLB,
	VCLK_IP_HPM_CPUCL0_0,
	VCLK_IP_HPM_CPUCL0_1,
	VCLK_IP_HPM_CPUCL0_2,
	VCLK_IP_APB_ASYNC_P_CSSYS,
	VCLK_IP_BPS_CPUCL0,
	VCLK_IP_BUSIF_HPM_CPUCL0,
	VCLK_IP_CSSYS,
	VCLK_IP_D_TZPC_CPUCL0,
	VCLK_IP_LH_ATB_MI_IT_CLUSTER0,
	VCLK_IP_LH_ATB_MI_T_BDU,
	VCLK_IP_SLH_AXI_MI_G_DBGCORE,
	VCLK_IP_SLH_AXI_MI_IG_CSSYS,
	VCLK_IP_SLH_AXI_MI_IG_DBGCORE,
	VCLK_IP_SLH_AXI_MI_IG_ETR,
	VCLK_IP_SLH_AXI_MI_IG_STM,
	VCLK_IP_SLH_AXI_MI_P_CPUCL0,
	VCLK_IP_LH_AXI_SI_G_CSSYS,
	VCLK_IP_SLH_AXI_SI_IG_CSSYS,
	VCLK_IP_SLH_AXI_SI_IG_DBGCORE,
	VCLK_IP_SLH_AXI_SI_IG_ETR,
	VCLK_IP_SECJTAG,
	VCLK_IP_SYSREG_CPUCL0,
	VCLK_IP_TREX_CPUCL0,
	VCLK_IP_XIU_DP_CSSYS,
	VCLK_IP_XIU_P_CPUCL0,
	VCLK_IP_SLH_AXI_SI_IG_STM,
	VCLK_IP_PMU_PCSM_PM,
	VCLK_IP_BUSIF_DDC_CPUCL0_0,
	VCLK_IP_BUSIF_DDC_CPUCL0_1,
	VCLK_IP_LH_ATB_MI_IT_DDCDSU,
	VCLK_IP_LH_ATB_MI_T_DDCG3D,
	VCLK_IP_LH_ATB_MI_IT_DDCLIT,
	VCLK_IP_LH_ATB_MI_IT_DDCMID0,
	VCLK_IP_LH_ATB_MI_IT_DDCMID1,
	VCLK_IP_LH_ATB_MI_IT_DDCMID2,
	VCLK_IP_LH_ATB_MI_IT_DDCBIG,
	VCLK_IP_CFM_CPUCL0,
	VCLK_IP_ADD_CPUCL0_1,
	VCLK_IP_BUSIF_ADD_CPUCL0_1,
	VCLK_IP_BUSIF_STR_CPUCL0_1,
	VCLK_IP_HTU_CPUCL1_0,
	VCLK_IP_CPUCL1_CMU_CPUCL1,
	VCLK_IP_HTU_CPUCL1_1,
	VCLK_IP_HTU_CPUCL1_2,
	VCLK_IP_STR_CPUCL0_1,
	VCLK_IP_ADD_CPUCL0_2,
	VCLK_IP_BUSIF_ADD_CPUCL0_2,
	VCLK_IP_BUSIF_STR_CPUCL0_2,
	VCLK_IP_HTU_CPUCL2,
	VCLK_IP_CPUCL2_CMU_CPUCL2,
	VCLK_IP_STR_CPUCL0_2,
	VCLK_IP_MIPI_PHY_LINK_WRAP,
	VCLK_IP_SYSMMU_D1_CSIS,
	VCLK_IP_CSIS_CMU_CSIS,
	VCLK_IP_AD_APB_CSIS_WDMA,
	VCLK_IP_CSIS_PDP,
	VCLK_IP_D_TZPC_CSIS,
	VCLK_IP_AD_AXI_OIS_MCU_TOP,
	VCLK_IP_XIU_P_CSIS,
	VCLK_IP_LH_AXI_SI_D0_CSIS,
	VCLK_IP_LH_AXI_SI_D1_CSIS,
	VCLK_IP_LH_AXI_SI_D2_CSIS,
	VCLK_IP_OIS_MCU_TOP,
	VCLK_IP_PPMU_D0,
	VCLK_IP_PPMU_D1,
	VCLK_IP_PPMU_D2,
	VCLK_IP_QE_CSIS_WDMA0,
	VCLK_IP_QE_CSIS_WDMA1,
	VCLK_IP_QE_CSIS_WDMA2,
	VCLK_IP_QE_CSIS_WDMA3,
	VCLK_IP_QE_PDP_D0,
	VCLK_IP_QE_PDP_D1,
	VCLK_IP_QE_PDP_D2,
	VCLK_IP_QE_PDP_D3,
	VCLK_IP_SYSMMU_D0_CSIS,
	VCLK_IP_SYSMMU_D2_CSIS,
	VCLK_IP_SYSREG_CSIS,
	VCLK_IP_XIU_D3_CSIS,
	VCLK_IP_XIU_D4_CSIS,
	VCLK_IP_AD_APB_MIPI_PHY,
	VCLK_IP_LH_AST_SI_OTF0_CSISCSTAT,
	VCLK_IP_LH_AST_SI_OTF1_CSISCSTAT,
	VCLK_IP_LH_AST_SI_OTF2_CSISCSTAT,
	VCLK_IP_LH_AST_SI_OTF3_CSISCSTAT,
	VCLK_IP_PPMU_D3,
	VCLK_IP_QE_CSIS_WDMA4,
	VCLK_IP_LH_AXI_SI_D3_CSIS,
	VCLK_IP_SLH_AXI_SI_P_CSISPERIC1,
	VCLK_IP_SYSMMU_D3_CSIS,
	VCLK_IP_PPMU_D4,
	VCLK_IP_SYSMMU_D4_CSIS,
	VCLK_IP_VGEN_LITE_D0,
	VCLK_IP_VGEN_LITE_D1,
	VCLK_IP_LH_AXI_SI_D4_CSIS,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_CSIS,
	VCLK_IP_SIU_G_PPMU_CSIS,
	VCLK_IP_SLH_AST_SI_OTF_CSISDNC,
	VCLK_IP_SLH_AST_SI_OTF_CSISUFD,
	VCLK_IP_SLH_AXI_MI_LP_UFDCSIS,
	VCLK_IP_SLH_AXI_MI_P_CSIS,
	VCLK_IP_CSTAT_CMU_CSTAT,
	VCLK_IP_D_TZPC_CSTAT,
	VCLK_IP_AD_APB_CSTAT0,
	VCLK_IP_SLH_AXI_MI_P_CSTAT,
	VCLK_IP_PPMU_CSTAT,
	VCLK_IP_SYSMMU_D_CSTAT,
	VCLK_IP_LH_AXI_SI_D_CSTAT,
	VCLK_IP_SYSREG_CSTAT,
	VCLK_IP_XIU_D_CSTAT,
	VCLK_IP_LH_AST_MI_OTF0_CSISCSTAT,
	VCLK_IP_LH_AST_MI_OTF1_CSISCSTAT,
	VCLK_IP_LH_AST_MI_OTF2_CSISCSTAT,
	VCLK_IP_LH_AST_MI_OTF3_CSISCSTAT,
	VCLK_IP_SIPU_CSTAT,
	VCLK_IP_VGEN_LITE_CSTAT0,
	VCLK_IP_VGEN_LITE_CSTAT1,
	VCLK_IP_VGEN_LITE_CSTAT2,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_CSTAT,
	VCLK_IP_AHB_BUSMATRIX_DBGCORE,
	VCLK_IP_GREBEINTEGRATION_DBGCORE,
	VCLK_IP_SLH_AXI_MI_IP_APM,
	VCLK_IP_SLH_AXI_SI_G_DBGCORE,
	VCLK_IP_SLH_AXI_SI_G_SCAN2DRAM,
	VCLK_IP_SLH_AXI_SI_ID_DBGCORE,
	VCLK_IP_SYSREG_DBGCORE,
	VCLK_IP_WDT_DBGCORE,
	VCLK_IP_XHB_DBGCORE,
	VCLK_IP_DBGCORE_CMU_DBGCORE,
	VCLK_IP_MDIS_DBGCORE,
	VCLK_IP_SYSREG_DBGCORE_CORE,
	VCLK_IP_D_TZPC_DBGCORE,
	VCLK_IP_APBIF_S2D_DBGCORE,
	VCLK_IP_ASYNCAHBMASTER_DBGCORE,
	VCLK_IP_LH_AXI_MI_LD_DSP0DNC_SHMEM,
	VCLK_IP_LH_AXI_MI_LD_DSP1DNC_SHMEM,
	VCLK_IP_LH_AXI_MI_LD_GNPU0DNC_SHMEM,
	VCLK_IP_LH_AXI_MI_LD_GNPU1DNC_SHMEM,
	VCLK_IP_DNC_CMU_DNC,
	VCLK_IP_SLH_AXI_MI_D_CMDQ_GNPU0,
	VCLK_IP_LH_AXI_MI_LD_DSP0DNC_SFR,
	VCLK_IP_LH_AXI_MI_LD_DSP1DNC_SFR,
	VCLK_IP_SLH_AXI_MI_D_CMDQ_GNPU1,
	VCLK_IP_SLH_AXI_MI_P_DNC,
	VCLK_IP_SLH_AXI_MI_LD_DSP1DNC_CACHE,
	VCLK_IP_LH_AXI_SI_D1_GNPU0,
	VCLK_IP_LH_AXI_MI_LP_IPDNC,
	VCLK_IP_LH_AXI_SI_D1_GNPU1,
	VCLK_IP_LH_AXI_SI_LP_IPDNC,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_MMU3,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_MMU2,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_MMU1,
	VCLK_IP_ADM_DAP_DNC,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_MMU0,
	VCLK_IP_LH_AXI_MI_D_RQ_GNPU0,
	VCLK_IP_LH_AXI_MI_D_RQ_GNPU1,
	VCLK_IP_LH_AXI_SI_LD_DNCDSP1_DMA,
	VCLK_IP_SLH_AXI_MI_LD_DSP0DNC_CACHE,
	VCLK_IP_LH_AXI_SI_D0_GNPU0,
	VCLK_IP_LH_AXI_SI_LD_DNCDSP1_SFR,
	VCLK_IP_LH_AXI_SI_D0_GNPU1,
	VCLK_IP_IP_DNC,
	VCLK_IP_LH_AXI_SI_LD_DNCDSP0_DMA,
	VCLK_IP_SYSREG_DNC,
	VCLK_IP_LH_AXI_SI_LD_DNCDSP0_SFR,
	VCLK_IP_D_TZPC_DNC,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA3,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA2,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA1,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA0,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA7,
	VCLK_IP_LH_AXI_SI_D_CTRL_GNPU1,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA6,
	VCLK_IP_LH_AXI_SI_D_CTRL_GNPU0,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA5,
	VCLK_IP_LH_AXI_MI_LD_SDMADNC_DATA4,
	VCLK_IP_PPMU_IPDNC,
	VCLK_IP_PPMU_SDMA0,
	VCLK_IP_PPMU_SDMA1,
	VCLK_IP_PPMU_SDMA2,
	VCLK_IP_PPMU_SDMA3,
	VCLK_IP_SYSMMU_IPDNC,
	VCLK_IP_SYSMMU_SDMA0,
	VCLK_IP_SYSMMU_SDMA1,
	VCLK_IP_SYSMMU_SDMA2,
	VCLK_IP_SYSMMU_SDMA3,
	VCLK_IP_TREX_D_DNC,
	VCLK_IP_APBAS_S1_NS_SDMA0,
	VCLK_IP_BUSIF_HPM_DNC,
	VCLK_IP_HPM_DNC,
	VCLK_IP_HTU_DNC,
	VCLK_IP_BUSIF_DDD_DNC,
	VCLK_IP_BUSIF_ADD_DNC,
	VCLK_IP_ADD_DNC,
	VCLK_IP_SLH_AXI_SI_LD_DNCVTS,
	VCLK_IP_SLH_AXI_SI_LD_DNCCHUB,
	VCLK_IP_BAAW_DNCCHUB,
	VCLK_IP_BAAW_DNCVTS,
	VCLK_IP_DDD_DNC,
	VCLK_IP_LH_AXI_SI_LP_DNCSDMA,
	VCLK_IP_SIU_G_PPMU_DNC,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_DNC,
	VCLK_IP_SLH_AXI_SI_P_GNPU0,
	VCLK_IP_SLH_AXI_SI_P_GNPU1,
	VCLK_IP_SLH_AXI_MI_P_ALIVEDNC,
	VCLK_IP_VGEN_DNC,
	VCLK_IP_VGEN_LITE_DNC,
	VCLK_IP_SLH_AXI_SI_P_GNPUP0,
	VCLK_IP_SLH_AXI_SI_P_GNPUP1,
	VCLK_IP_SLH_AXI_MI_LD_UFDDNC,
	VCLK_IP_XIU_P_DNC,
	VCLK_IP_SLH_AST_MI_OTF_CSISDNC,
	VCLK_IP_SLH_AST_GLUE_OTF_CSISDNC,
	VCLK_IP_DPUB_CMU_DPUB,
	VCLK_IP_AD_APB_DECON_MAIN,
	VCLK_IP_DPUB,
	VCLK_IP_D_TZPC_DPUB,
	VCLK_IP_SLH_AXI_MI_P_DPUB,
	VCLK_IP_SYSREG_DPUB,
	VCLK_IP_UPI_M0,
	VCLK_IP_DPUF0_CMU_DPUF0,
	VCLK_IP_AD_APB_DPUF0_DMA,
	VCLK_IP_DPUF0,
	VCLK_IP_D_TZPC_DPUF0,
	VCLK_IP_SLH_AXI_MI_P_DPUF0,
	VCLK_IP_LH_AXI_SI_D1_DPUF0,
	VCLK_IP_PPMU_DPUF0D0,
	VCLK_IP_PPMU_DPUF0D1,
	VCLK_IP_SYSMMU_DPUF0D0,
	VCLK_IP_SYSMMU_DPUF0D1,
	VCLK_IP_SYSREG_DPUF0,
	VCLK_IP_XIU_D0_DPUF0,
	VCLK_IP_XIU_D1_DPUF0,
	VCLK_IP_SIU_DPUF0,
	VCLK_IP_LH_AXI_MI_D0_DPUF1DPUF0,
	VCLK_IP_LH_AXI_MI_D1_DPUF1DPUF0,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_DPUF0,
	VCLK_IP_SLH_AXI_SI_D0_DPUF0,
	VCLK_IP_DPUF1_CMU_DPUF1,
	VCLK_IP_AD_APB_DPUF1_DMA,
	VCLK_IP_DPUF1,
	VCLK_IP_D_TZPC_DPUF1,
	VCLK_IP_SLH_AXI_MI_P_DPUF1,
	VCLK_IP_PPMU_DPUF1D0,
	VCLK_IP_PPMU_DPUF1D1,
	VCLK_IP_SYSMMU_DPUF1D0,
	VCLK_IP_SYSMMU_DPUF1D1,
	VCLK_IP_SYSREG_DPUF1,
	VCLK_IP_SIU_DPUF1,
	VCLK_IP_LH_AXI_SI_D0_DPUF1DPUF0,
	VCLK_IP_LH_AXI_SI_D1_DPUF1DPUF0,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_DPUF1,
	VCLK_IP_DRCP_CMU_DRCP,
	VCLK_IP_AD_APB_DRCP,
	VCLK_IP_DRCP,
	VCLK_IP_PPMU_D_DRCP,
	VCLK_IP_SYSMMU_D_DRCP,
	VCLK_IP_D_TZPC_DRCP,
	VCLK_IP_XIU_D_DRCP,
	VCLK_IP_SYSREG_DRCP,
	VCLK_IP_SLH_AXI_MI_P_DRCP,
	VCLK_IP_LH_AST_MI_OTF_YUVPDRCP,
	VCLK_IP_LH_AST_SI_OTF_DRCPMCSC,
	VCLK_IP_LH_AXI_SI_D_DRCP,
	VCLK_IP_VGEN_LITE_D_DRCP,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_DRCP,
	VCLK_IP_LH_AXI_SI_LD_DSPDNC_SHMEM,
	VCLK_IP_DSP_CMU_DSP,
	VCLK_IP_SYSREG_DSP,
	VCLK_IP_D_TZPC_DSP,
	VCLK_IP_SLH_AXI_MI_P_DSP,
	VCLK_IP_LH_AXI_MI_LD_DNCDSP_DMA,
	VCLK_IP_LH_AXI_MI_LD_DNCDSP_SFR,
	VCLK_IP_SLH_AXI_SI_LD_DSPDNC_CACHE,
	VCLK_IP_LH_AXI_SI_LD_DSPDNC_SFR,
	VCLK_IP_IP_DSP,
	VCLK_IP_LH_AST_MI_LD_STRM_SDMADSP,
	VCLK_IP_CLUSTER0,
	VCLK_IP_BUSIF_STR_CPUCL0_3,
	VCLK_IP_LH_AST_MI_LD_IRI_GICCPU_CLUSTER0,
	VCLK_IP_LH_AST_SI_LD_ICC_CPUGIC_CLUSTER0,
	VCLK_IP_LH_ATB_SI_IT_CLUSTER0,
	VCLK_IP_PPC_INSTRRET_CLUSTER0_0,
	VCLK_IP_PPC_INSTRRET_CLUSTER0_1,
	VCLK_IP_PPC_INSTRRUN_CLUSTER0_0,
	VCLK_IP_PPC_INSTRRUN_CLUSTER0_1,
	VCLK_IP_SLH_AXI_MI_PPU_ALIVE_CPUCL0,
	VCLK_IP_DSU_CMU_DSU,
	VCLK_IP_HTU_DSU,
	VCLK_IP_LH_CHI_SI_D0_CLUSTER0,
	VCLK_IP_LH_CHI_SI_D1_CLUSTER0,
	VCLK_IP_GRAY2BIN_CNTVALUEB,
	VCLK_IP_U_SYNC_PPUWAKEUP_CLUSTER0,
	VCLK_IP_SLH_AXI_MI_IP_UTILITY,
	VCLK_IP_XIU_DP_UTILITY,
	VCLK_IP_SLH_AXI_SI_P_CLUSTER0_NOCL0,
	VCLK_IP_SLH_AXI_SI_IP_UTILITY,
	VCLK_IP_XIU_DP_PERIPHERAL,
	VCLK_IP_STR_CPUCL0_3,
	VCLK_IP_G3D_CMU_G3D,
	VCLK_IP_BUSIF_HPMG3D,
	VCLK_IP_SLH_AXI_SI_P_INT_G3D,
	VCLK_IP_HPM_G3D,
	VCLK_IP_SYSREG_G3D,
	VCLK_IP_D_TZPC_G3D,
	VCLK_IP_SLH_AXI_MI_P_G3D,
	VCLK_IP_CFM_G3D,
	VCLK_IP_BG3D_PWRCTL,
	VCLK_IP_ADD_G3D,
	VCLK_IP_ADD_APBIF_G3D,
	VCLK_IP_BUSIF_STR_G3D,
	VCLK_IP_HTU_G3D,
	VCLK_IP_G3DCORE_CMU_G3DCORE,
	VCLK_IP_GPU,
	VCLK_IP_ADM_DAP_G_G3D,
	VCLK_IP_BUSIF_DDC_G3D,
	VCLK_IP_STR_G3D,
	VCLK_IP_GNPU_CMU_GNPU,
	VCLK_IP_IP_NPUCORE,
	VCLK_IP_LH_AXI_MI_D_CTRL_GNPU,
	VCLK_IP_LH_AXI_SI_D_RQ_GNPU,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU0,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU31,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU30,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU4,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU3,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU2,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU1,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU8,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU7,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU6,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU5,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU9,
	VCLK_IP_LH_AXI_MI_D1_GNPU,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU20,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU22,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU21,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU24,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU23,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU26,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU25,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU28,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU27,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU29,
	VCLK_IP_D_TZPC_GNPU,
	VCLK_IP_LH_AST_MI_LD_GNPUP_BU3,
	VCLK_IP_LH_AST_MI_LD_GNPUP_BU2,
	VCLK_IP_LH_AST_SI_LD_GNPU_CU_RDATA,
	VCLK_IP_LH_AST_SI_LD_GNPU_AULOADER,
	VCLK_IP_LH_AST_MI_LD_GNPUP_RDREQ,
	VCLK_IP_LH_AST_MI_LD_GNPUP_CU_WCH,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU11,
	VCLK_IP_LH_AST_MI_LD_GNPUP_BU1,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU10,
	VCLK_IP_LH_AST_MI_LD_GNPUP_BU0,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU13,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU12,
	VCLK_IP_SLH_AXI_MI_P_GNPU,
	VCLK_IP_SLH_AXI_SI_D_CMDQ_GNPU,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU15,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU14,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU17,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU16,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU19,
	VCLK_IP_LH_AST_SI_LD_GNPU_AU18,
	VCLK_IP_SYSREG_GNPU,
	VCLK_IP_LH_AXI_MI_D0_GNPU,
	VCLK_IP_LH_AST_SI_LD_GNPU_NPUC_SETREG,
	VCLK_IP_LH_AST_MI_LD_GNPUP_NPUC_DONE,
	VCLK_IP_LH_AXI_SI_LD_GNPUDNC_SHMEM,
	VCLK_IP_XIU_D_GNPU_0,
	VCLK_IP_XIU_D_GNPU_1,
	VCLK_IP_LH_AST_SI_LD_GNPU_SRAM_WRRESP,
	VCLK_IP_GNPUP_CMU_GNPUP,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU3,
	VCLK_IP_LH_AST_MI_LD_GNPU_CU_RDATA,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU4,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU5,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU6,
	VCLK_IP_LH_AST_SI_LD_GNPUP_BU1,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU7,
	VCLK_IP_LH_AST_SI_LD_GNPUP_BU2,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU8,
	VCLK_IP_D_TZPC_GNPUP,
	VCLK_IP_LH_AST_SI_LD_GNPUP_BU3,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU9,
	VCLK_IP_SYSREG_GNPUP,
	VCLK_IP_LH_AST_SI_LD_GNPUP_BU0,
	VCLK_IP_LH_AST_SI_LD_GNPUP_RDREQ,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU17,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU16,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU19,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU18,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU13,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU12,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU15,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU14,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU31,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU0,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU30,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU1,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU11,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU2,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU10,
	VCLK_IP_LH_AST_MI_LD_GNPU_NPUC_SETREG,
	VCLK_IP_LH_AST_MI_LD_GNPU_AULOADER,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU28,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU27,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU29,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU24,
	VCLK_IP_LH_AST_SI_LD_GNPUP_NPUC_DONE,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU23,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU26,
	VCLK_IP_SLH_AXI_MI_P_GNPUP,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU25,
	VCLK_IP_IP_NPUPOST,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU20,
	VCLK_IP_LH_AST_SI_LD_GNPUP_CU_WCH,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU22,
	VCLK_IP_LH_AST_MI_LD_GNPU_AU21,
	VCLK_IP_LH_AST_MI_LD_GNPU_SRAM_WRRESP,
	VCLK_IP_GNSS_CMU_GNSS,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_HSI0,
	VCLK_IP_DP_LINK,
	VCLK_IP_HSI0_CMU_HSI0,
	VCLK_IP_D_TZPC_HSI0,
	VCLK_IP_SLH_AXI_MI_P_HSI0,
	VCLK_IP_SLH_ACEL_SI_D_HSI0,
	VCLK_IP_SLH_AXI_SI_LD_HSI0AUD,
	VCLK_IP_PPMU_HSI0_BUS1,
	VCLK_IP_SYSMMU_D_HSI0,
	VCLK_IP_SYSREG_HSI0,
	VCLK_IP_USB32DRD,
	VCLK_IP_VGEN_LITE_HSI0,
	VCLK_IP_XIU_D_HSI0,
	VCLK_IP_SLH_AXI_MI_LD_AUDHSI0,
	VCLK_IP_SPC_HSI0,
	VCLK_IP_URAM,
	VCLK_IP_XIU_P0_HSI0,
	VCLK_IP_AS_APB_EUSBPHY_HSI0,
	VCLK_IP_PCIE_GEN2,
	VCLK_IP_D_TZPC_HSI1,
	VCLK_IP_GPIO_HSI1,
	VCLK_IP_SLH_AXI_MI_P_HSI1,
	VCLK_IP_LH_ACEL_SI_D_HSI1,
	VCLK_IP_MMC_CARD,
	VCLK_IP_PCIE_GEN3,
	VCLK_IP_PCIE_IA_GEN3,
	VCLK_IP_PPMU_HSI1,
	VCLK_IP_SYSMMU_HSI1,
	VCLK_IP_SYSREG_HSI1,
	VCLK_IP_UFS_EMBD,
	VCLK_IP_VGEN_LITE_HSI1,
	VCLK_IP_XIU_D_HSI1,
	VCLK_IP_XIU_P_HSI1,
	VCLK_IP_HSI1_CMU_HSI1,
	VCLK_IP_PCIE_IA_GEN2,
	VCLK_IP_GPIO_HSI1UFS,
	VCLK_IP_SPC_HSI1,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_HSI1,
	VCLK_IP_LME_CMU_LME,
	VCLK_IP_LH_AXI_SI_D_LME,
	VCLK_IP_PPMU_D_LME,
	VCLK_IP_FRC_MC,
	VCLK_IP_AD_APB_LME,
	VCLK_IP_AD_AXI_FRC_MC,
	VCLK_IP_SLH_AXI_MI_P_LME,
	VCLK_IP_SYSREG_LME,
	VCLK_IP_D_TZPC_LME,
	VCLK_IP_LME,
	VCLK_IP_AD_APB_FRC_MC,
	VCLK_IP_SYSMMU_D_LME,
	VCLK_IP_XIU_D_LME,
	VCLK_IP_QE_D0_LME,
	VCLK_IP_QE_D1_LME,
	VCLK_IP_VGEN_LITE_D_LME,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_LME,
	VCLK_IP_M2M_CMU_M2M,
	VCLK_IP_AS_APB_M2M,
	VCLK_IP_D_TZPC_M2M,
	VCLK_IP_SLH_AXI_MI_P_M2M,
	VCLK_IP_LH_ACEL_SI_D_M2M,
	VCLK_IP_M2M,
	VCLK_IP_PPMU_D_M2M,
	VCLK_IP_QE_ASTC,
	VCLK_IP_QE_JPEG0,
	VCLK_IP_QE_JPEG1,
	VCLK_IP_QE_JSQZ,
	VCLK_IP_QE_M2M,
	VCLK_IP_SYSMMU_D_M2M_PM,
	VCLK_IP_SYSREG_M2M,
	VCLK_IP_XIU_D_M2M,
	VCLK_IP_ASTC,
	VCLK_IP_JPEG0,
	VCLK_IP_JPEG1,
	VCLK_IP_JSQZ,
	VCLK_IP_VGEN_LITE_M2M,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_M2M,
	VCLK_IP_MCFP_CMU_MCFP,
	VCLK_IP_MCFP,
	VCLK_IP_LH_AXI_SI_D2_MCFP,
	VCLK_IP_PPMU_D5_MCFP,
	VCLK_IP_PPMU_D2_MCFP,
	VCLK_IP_XIU_D1_MCFP,
	VCLK_IP_SLH_AXI_SI_D5_MCFP,
	VCLK_IP_LH_AXI_SI_D1_MCFP,
	VCLK_IP_SLH_AXI_SI_D4_MCFP,
	VCLK_IP_XIU_D0_MCFP,
	VCLK_IP_PPMU_D1_MCFP,
	VCLK_IP_SLH_AXI_SI_D3_MCFP,
	VCLK_IP_PPMU_D4_MCFP,
	VCLK_IP_LH_AXI_SI_D0_MCFP,
	VCLK_IP_SYSREG_MCFP,
	VCLK_IP_SYSMMU_D0_MCFP,
	VCLK_IP_SYSMMU_D2_MCFP,
	VCLK_IP_D_TZPC_MCFP,
	VCLK_IP_SYSMMU_D1_MCFP,
	VCLK_IP_SYSMMU_D4_MCFP,
	VCLK_IP_PPMU_D3_MCFP,
	VCLK_IP_SYSMMU_D3_MCFP,
	VCLK_IP_AD_APB_MCFP,
	VCLK_IP_PPMU_D0_MCFP,
	VCLK_IP_SYSMMU_D5_MCFP,
	VCLK_IP_SLH_AXI_MI_P_MCFP,
	VCLK_IP_LH_AST_MI_OTF_RGBPMCFP,
	VCLK_IP_LH_AST_SI_OTF0_MCFPYUVP,
	VCLK_IP_LH_AST_MI_OTF_YUVPMCFP,
	VCLK_IP_VGEN_LITE_D0_MCFP,
	VCLK_IP_VGEN_LITE_D1_MCFP,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_MCFP,
	VCLK_IP_SIU_G_PPMU_MCFP,
	VCLK_IP_MCSC_CMU_MCSC,
	VCLK_IP_AD_APB_GDC,
	VCLK_IP_AD_APB_MCSC,
	VCLK_IP_D_TZPC_MCSC,
	VCLK_IP_GDC,
	VCLK_IP_LH_AST_MI_OTF_DRCPMCSC,
	VCLK_IP_SLH_AXI_MI_P_MCSC,
	VCLK_IP_LH_ACEL_SI_D0_MCSC,
	VCLK_IP_LH_AXI_SI_D1_MCSC,
	VCLK_IP_LH_AXI_SI_D2_MCSC,
	VCLK_IP_MCSC,
	VCLK_IP_PPMU_D0_MCSC,
	VCLK_IP_PPMU_D1_MCSC,
	VCLK_IP_PPMU_D2_MCSC,
	VCLK_IP_SYSMMU_D1_MCSC,
	VCLK_IP_SYSMMU_D2_MCSC,
	VCLK_IP_SYSREG_MCSC,
	VCLK_IP_XIU_D0_MCSC,
	VCLK_IP_XIU_D1_MCSC,
	VCLK_IP_XIU_D2_MCSC,
	VCLK_IP_SYSMMU_D0_MCSC,
	VCLK_IP_VGEN_LITE_D0_MCSC,
	VCLK_IP_VGEN_LITE_D1_MCSC,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_MCSC,
	VCLK_IP_SIU_G_PPMU_MCSC,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_D0_MCSC,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_D0_MCSC,
	VCLK_IP_MFC0_CMU_MFC0,
	VCLK_IP_XIU_D_MFC0,
	VCLK_IP_WFD,
	VCLK_IP_SYSMMU_MFC0D0,
	VCLK_IP_PPMU_WFD,
	VCLK_IP_PPMU_MFC0D1,
	VCLK_IP_PPMU_MFC0D0,
	VCLK_IP_MFC0,
	VCLK_IP_LH_ATB_MFC0,
	VCLK_IP_LH_AXI_SI_D1_MFC0,
	VCLK_IP_LH_AXI_SI_D0_MFC0,
	VCLK_IP_LH_AST_SI_OTF2_MFC0MFC1,
	VCLK_IP_LH_AST_SI_OTF1_MFC0MFC1,
	VCLK_IP_LH_AST_SI_OTF0_MFC0MFC1,
	VCLK_IP_SLH_AXI_MI_P_MFC0,
	VCLK_IP_LH_AST_MI_OTF3_MFC1MFC0,
	VCLK_IP_LH_AST_MI_OTF2_MFC1MFC0,
	VCLK_IP_LH_AST_MI_OTF1_MFC1MFC0,
	VCLK_IP_LH_AST_MI_OTF0_MFC1MFC0,
	VCLK_IP_D_TZPC_MFC0,
	VCLK_IP_AS_AXI_WFD,
	VCLK_IP_ADS_APB_MFC0MFC1,
	VCLK_IP_AS_APB_MFC0,
	VCLK_IP_AS_APB_WFD_NS,
	VCLK_IP_SYSREG_MFC0,
	VCLK_IP_LH_AST_SI_OTF3_MFC0MFC1,
	VCLK_IP_SYSMMU_MFC0D1,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_MFC0,
	VCLK_IP_SIU_G_PPMU_MFC0,
	VCLK_IP_VGEN_LITE_MFC0,
	VCLK_IP_MFC1_CMU_MFC1,
	VCLK_IP_SYSREG_MFC1,
	VCLK_IP_SYSMMU_MFC1D0,
	VCLK_IP_LH_AST_MI_OTF0_MFC0MFC1,
	VCLK_IP_D_TZPC_MFC1,
	VCLK_IP_AS_APB_MFC1,
	VCLK_IP_ADM_APB_MFC0MFC1,
	VCLK_IP_LH_AST_MI_OTF1_MFC0MFC1,
	VCLK_IP_LH_AST_MI_OTF2_MFC0MFC1,
	VCLK_IP_LH_AST_MI_OTF3_MFC0MFC1,
	VCLK_IP_SLH_AXI_MI_P_MFC1,
	VCLK_IP_LH_AST_SI_OTF0_MFC1MFC0,
	VCLK_IP_LH_AST_SI_OTF1_MFC1MFC0,
	VCLK_IP_LH_AST_SI_OTF2_MFC1MFC0,
	VCLK_IP_LH_AST_SI_OTF3_MFC1MFC0,
	VCLK_IP_LH_AXI_SI_D0_MFC1,
	VCLK_IP_LH_AXI_SI_D1_MFC1,
	VCLK_IP_MFC1,
	VCLK_IP_PPMU_MFC1D0,
	VCLK_IP_PPMU_MFC1D1,
	VCLK_IP_SYSMMU_MFC1D1,
	VCLK_IP_VGEN_MFC1,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_MFC1,
	VCLK_IP_SIU_G_PPMU_MFC1,
	VCLK_IP_MIF_CMU_MIF,
	VCLK_IP_APBBR_DDRPHY,
	VCLK_IP_APBBR_DMC,
	VCLK_IP_DDRPHY,
	VCLK_IP_DMC,
	VCLK_IP_D_TZPC_MIF,
	VCLK_IP_SLH_AXI_MI_P_MIF,
	VCLK_IP_QCH_ADAPTER_PPC_DEBUG,
	VCLK_IP_SYSREG_MIF,
	VCLK_IP_LH_AST_SI_G_DMC,
	VCLK_IP_SPC_MIF,
	VCLK_IP_SYSREG_PRIVATE_MIF,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_MIF,
	VCLK_IP_BUSIF_DDD_MIF,
	VCLK_IP_DDD_MIF,
	VCLK_IP_PPC_DEBUG,
	VCLK_IP_NOCL0_CMU_NOCL0,
	VCLK_IP_CCI,
	VCLK_IP_SIU_G0_PPMU_NOCL0,
	VCLK_IP_SIU_G1_PPMU_NOCL0,
	VCLK_IP_APB_ASYNC_SYSMMU_S2_G3D,
	VCLK_IP_AXI_ASB_CSSYS,
	VCLK_IP_BAAW_CP,
	VCLK_IP_BDU,
	VCLK_IP_D_TZPC_NOCL0,
	VCLK_IP_SLH_AXI_MI_D2_MODEM,
	VCLK_IP_LH_CHI_MI_D0_CLUSTER0,
	VCLK_IP_LH_ACEL_MI_D0_G3D,
	VCLK_IP_LH_CHI_MI_D1_CLUSTER0,
	VCLK_IP_LH_ACEL_MI_D1_G3D,
	VCLK_IP_LH_ACEL_MI_D2_G3D,
	VCLK_IP_LH_ACEL_MI_D3_G3D,
	VCLK_IP_SLH_AXI_MI_D0_MODEM,
	VCLK_IP_SLH_AXI_MI_D1_MODEM,
	VCLK_IP_LH_QDI_MI_D_AUD,
	VCLK_IP_LH_AXI_MI_G_CSSYS,
	VCLK_IP_LH_ATB_SI_T_BDU,
	VCLK_IP_SLH_AXI_SI_P_APM,
	VCLK_IP_SLH_AXI_SI_P_AUD,
	VCLK_IP_SLH_AXI_SI_P_CPUCL0,
	VCLK_IP_SLH_AXI_SI_P_G3D,
	VCLK_IP_SLH_AXI_SI_P_MODEM,
	VCLK_IP_SLH_AXI_SI_P_PERISGIC,
	VCLK_IP_MPACE2AXI_0,
	VCLK_IP_MPACE2AXI_1,
	VCLK_IP_MPACE_ASB_D0_MIF,
	VCLK_IP_MPACE_ASB_D1_MIF,
	VCLK_IP_MPACE_ASB_D2_MIF,
	VCLK_IP_MPACE_ASB_D3_MIF,
	VCLK_IP_PPC_DEBUG_CCI,
	VCLK_IP_PPMU_CPUCL0_0,
	VCLK_IP_PPMU_CPUCL0_1,
	VCLK_IP_PPMU_G3D0,
	VCLK_IP_PPMU_G3D1,
	VCLK_IP_PPMU_G3D2,
	VCLK_IP_PPMU_G3D3,
	VCLK_IP_PPMU_MIF0,
	VCLK_IP_PPMU_MIF1,
	VCLK_IP_PPMU_MIF2,
	VCLK_IP_PPMU_MIF3,
	VCLK_IP_SYSMMU_S2_G3D,
	VCLK_IP_SYSMMU_MODEM,
	VCLK_IP_SYSREG_NOCL0,
	VCLK_IP_TREX_D_NOCL0,
	VCLK_IP_TREX_P_NOCL0,
	VCLK_IP_VGEN_LITE_MODEM,
	VCLK_IP_ASYNCSFR_WR_SMC,
	VCLK_IP_SLH_AXI_SI_P_MIF0,
	VCLK_IP_SLH_AXI_SI_P_MIF1,
	VCLK_IP_SLH_AXI_SI_P_MIF2,
	VCLK_IP_SLH_AXI_SI_P_MIF3,
	VCLK_IP_SYSMMU_S2_APM,
	VCLK_IP_LH_AXI_MI_D_APM,
	VCLK_IP_SLH_AXI_SI_P_MCW,
	VCLK_IP_SLH_AXI_MI_P_CLUSTER0_NOCL0,
	VCLK_IP_CACHEAID_NOCL0,
	VCLK_IP_PPMU_APM,
	VCLK_IP_LH_AST_MI_G0_DMC,
	VCLK_IP_LH_AST_MI_G1_DMC,
	VCLK_IP_LH_AST_MI_G2_DMC,
	VCLK_IP_LH_AST_MI_G3_DMC,
	VCLK_IP_LH_AST_MI_G_NOCL1A,
	VCLK_IP_LH_AST_MI_G_NOCL1B,
	VCLK_IP_LH_AST_MI_G_NOCL2A,
	VCLK_IP_WOW_DVFS_D0_MIF,
	VCLK_IP_WOW_DVFS_IRPS0,
	VCLK_IP_WOW_DVFS_IRPS1,
	VCLK_IP_WOW_DVFS_IRPS2,
	VCLK_IP_WOW_DVFS_IRPS3,
	VCLK_IP_WOW_DVFS_NOCL0,
	VCLK_IP_PPC_SCI,
	VCLK_IP_SPC_NOCL0,
	VCLK_IP_SYSREG_PRIVATE_NOCL0,
	VCLK_IP_WOW_DVFS_D0_CPUCL0,
	VCLK_IP_WOW_DVFS_D0_G3D,
	VCLK_IP_WOW_DVFS_D1_CPUCL0,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_AUD,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MODEM,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_NOCL1A,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_NOCL1B,
	VCLK_IP_SIU_G6_PPMU_NOCL0,
	VCLK_IP_SIU_G2_PPMU_NOCL0,
	VCLK_IP_SIU_G3_PPMU_NOCL0,
	VCLK_IP_SIU_G4_PPMU_NOCL0,
	VCLK_IP_SIU_G5_PPMU_NOCL0,
	VCLK_IP_APB_ASYNC_ETR,
	VCLK_IP_ETR_64_NOCL0,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MIF0,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MIF1,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MIF2,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MIF3,
	VCLK_IP_PPMU_SYNC_GEN,
	VCLK_IP_PBHA_GEN_D0_MODEM,
	VCLK_IP_PBHA_GEN_D1_MODEM,
	VCLK_IP_WOW_DVFS_D1_MIF,
	VCLK_IP_WOW_DVFS_D2_MIF,
	VCLK_IP_WOW_DVFS_D3_MIF,
	VCLK_IP_VGEN_D0_G3D,
	VCLK_IP_VGEN_D1_G3D,
	VCLK_IP_VGEN_D2_G3D,
	VCLK_IP_VGEN_D3_G3D,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_P_CLUSTER0,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_P_CLUSTER0,
	VCLK_IP_APB_ASYNC_VGEN_D0_G3D,
	VCLK_IP_APB_ASYNC_VGEN_D1_G3D,
	VCLK_IP_APB_ASYNC_VGEN_D2_G3D,
	VCLK_IP_APB_ASYNC_VGEN_D3_G3D,
	VCLK_IP_SLH_AST_SI_IG_DEBUG_MUX_NOCL0,
	VCLK_IP_SLH_AST_MI_IG_DEBUG_MUX_NOCL0,
	VCLK_IP_NOCL1A_CMU_NOCL1A,
	VCLK_IP_SLH_AXI_SI_P_SSP,
	VCLK_IP_SYSREG_NOCL1A,
	VCLK_IP_TREX_D_NOCL1A,
	VCLK_IP_SLH_AXI_SI_P_HSI1,
	VCLK_IP_SLH_AXI_SI_P_MFC1,
	VCLK_IP_LH_AXI_MI_D1_MFC1,
	VCLK_IP_LH_AST_SI_G_NOCL1A,
	VCLK_IP_LH_AXI_MI_D1_MFC0,
	VCLK_IP_SLH_AXI_SI_P_MFC0,
	VCLK_IP_NOCIF_CMUTOPC,
	VCLK_IP_LH_ACEL_MI_D_M2M,
	VCLK_IP_D_TZPC_NOCL1A,
	VCLK_IP_LH_AXI_MI_D_LME,
	VCLK_IP_SLH_AXI_SI_P_M2M,
	VCLK_IP_TREX_P_NOCL1A,
	VCLK_IP_LH_AXI_MI_D0_MFC1,
	VCLK_IP_SLH_AXI_SI_P_LME,
	VCLK_IP_LH_AXI_MI_D0_MFC0,
	VCLK_IP_LH_ACEL_MI_D_HSI1,
	VCLK_IP_SLH_ACEL_MI_D_SSP,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_HSI1,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_LME,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_M2M,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MFC0,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MFC1,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_NOCL1A,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_NOCL2A,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_SSP,
	VCLK_IP_SIU_2X1_P0_NOCL1A,
	VCLK_IP_SIU_4X1_P0_NOCL1A,
	VCLK_IP_SIU_8X1_P0_NOCL1A,
	VCLK_IP_SLH_AXI_SI_P_PERIC0,
	VCLK_IP_SLH_AXI_SI_P_PERIC2,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_NOCL1A,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_NOCL1A,
	VCLK_IP_SLH_AST_MI_IG_DEBUG_MUX_NOCL1A,
	VCLK_IP_SLH_AST_SI_IG_DEBUG_MUX_NOCL1A,
	VCLK_IP_NOCL1B_CMU_NOCL1B,
	VCLK_IP_BAAW_P_VTS,
	VCLK_IP_D_TZPC_NOCL1B,
	VCLK_IP_SLH_ACEL_MI_D_HSI0,
	VCLK_IP_SLH_AXI_MI_D0_DPUF0,
	VCLK_IP_LH_AXI_MI_D1_DPUF0,
	VCLK_IP_SLH_AXI_SI_P_DPUB,
	VCLK_IP_SLH_AXI_SI_P_DPUF0,
	VCLK_IP_SLH_AXI_SI_P_DPUF1,
	VCLK_IP_SLH_AXI_SI_P_HSI0,
	VCLK_IP_SLH_AXI_SI_P_VTS,
	VCLK_IP_LH_AST_SI_G_NOCL1B,
	VCLK_IP_QE_PDMA,
	VCLK_IP_QE_SPDMA,
	VCLK_IP_SYSREG_NOCL1B,
	VCLK_IP_TREX_D_NOCL1B,
	VCLK_IP_TREX_P_NOCL1B,
	VCLK_IP_TREX_RB_NOCL1B,
	VCLK_IP_SLH_AXI_SI_P_CHUB,
	VCLK_IP_SLH_AXI_SI_P_GNSS,
	VCLK_IP_BAAW_P_CHUB,
	VCLK_IP_BAAW_P_GNSS,
	VCLK_IP_SLH_AXI_SI_P_UFD,
	VCLK_IP_SLH_AXI_SI_P_DNC,
	VCLK_IP_SLH_AXI_SI_P_DSP0,
	VCLK_IP_SLH_AXI_SI_P_DSP1,
	VCLK_IP_SLH_AXI_SI_P_PERIS,
	VCLK_IP_SLH_AXI_SI_P_SDMA,
	VCLK_IP_PPMU_D_TT,
	VCLK_IP_PPMU_DIT,
	VCLK_IP_BAAW_P_DNC,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_HSI0,
	VCLK_IP_SIU_P0_TREX_XIU_DIT,
	VCLK_IP_SIU_P1_HSI_DPUF_DNC_GNSS,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_DPUF0,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_DPUF1,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_DNC,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_NOCL1B,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_GNSS,
	VCLK_IP_SLH_AXI_SI_P_PERIC1,
	VCLK_IP_AD_APB_DIT,
	VCLK_IP_AD_APB_PDMA,
	VCLK_IP_AD_APB_SPDMA,
	VCLK_IP_AD_APB_SYSMMU_DIT,
	VCLK_IP_AD_APB_SYSMMU_TT,
	VCLK_IP_AD_APB_SYSMMU_TT_NS,
	VCLK_IP_AD_APB_SYSMMU_TT_S,
	VCLK_IP_SLH_AXI_MI_D_UFD,
	VCLK_IP_PDMA,
	VCLK_IP_SPDMA,
	VCLK_IP_DIT,
	VCLK_IP_XIU_D_TT,
	VCLK_IP_SYSMMU_TT,
	VCLK_IP_SYSMMU_S2_DIT,
	VCLK_IP_VGEN_LITE_NOCL1B,
	VCLK_IP_VGEN_SPDMA,
	VCLK_IP_VGEN_PDMA,
	VCLK_IP_AD_AXI_TT,
	VCLK_IP_LH_ACEL_MI_ID_DIT,
	VCLK_IP_LH_ACEL_SI_ID_DIT,
	VCLK_IP_AD_APB_VGEN_LITE_NOCL1B,
	VCLK_IP_AD_APB_VGEN_PDMA,
	VCLK_IP_AD_APB_VGEN_SPDMA,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_TREXP,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_XIU_D_TT,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_DIT,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_TREXP,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_XIU_D_TT,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_DIT,
	VCLK_IP_SLH_AST_MI_IG_DEBUG_MUX_NOCL1B,
	VCLK_IP_SLH_AST_SI_IG_DEBUG_MUX_NOCL1B,
	VCLK_IP_NOCL2A_CMU_NOCL2A,
	VCLK_IP_LH_AXI_MI_D2_MCSC,
	VCLK_IP_SYSREG_NOCL2A,
	VCLK_IP_TREX_D_NOCL2A,
	VCLK_IP_SLH_AXI_SI_P_CSTAT,
	VCLK_IP_LH_AXI_MI_D_CSTAT,
	VCLK_IP_LH_AXI_MI_D1_MCFP,
	VCLK_IP_SLH_AXI_SI_P_CSIS,
	VCLK_IP_SLH_AXI_SI_P_MCFP,
	VCLK_IP_LH_AXI_MI_D1_CSIS,
	VCLK_IP_SLH_AXI_MI_D4_MCFP,
	VCLK_IP_LH_AXI_MI_D0_RGBP,
	VCLK_IP_SLH_AXI_SI_P_BYRP,
	VCLK_IP_LH_ACEL_MI_D0_MCSC,
	VCLK_IP_TREX_P_NOCL2A,
	VCLK_IP_LH_AXI_MI_D0_MCFP,
	VCLK_IP_LH_AXI_MI_D_BYRP,
	VCLK_IP_SLH_AXI_SI_P_YUVP,
	VCLK_IP_LH_AXI_MI_D3_CSIS,
	VCLK_IP_SLH_AXI_MI_D3_MCFP,
	VCLK_IP_LH_AST_SI_G_NOCL2A,
	VCLK_IP_LH_AXI_MI_D1_MCSC,
	VCLK_IP_SLH_AXI_SI_P_MCSC,
	VCLK_IP_LH_AXI_MI_D0_CSIS,
	VCLK_IP_SLH_AXI_MI_D_YUVP,
	VCLK_IP_D_TZPC_NOCL2A,
	VCLK_IP_SLH_AXI_SI_P_DRCP,
	VCLK_IP_SLH_AXI_SI_P_RGBP,
	VCLK_IP_LH_AXI_MI_D_DRCP,
	VCLK_IP_LH_AXI_MI_D2_CSIS,
	VCLK_IP_SLH_AXI_MI_D5_MCFP,
	VCLK_IP_LH_AXI_MI_D2_MCFP,
	VCLK_IP_LH_AXI_MI_D4_CSIS,
	VCLK_IP_LH_AXI_MI_D1_RGBP,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_BYRP,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_CSIS,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_CSTAT,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_DRCP,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MCFP,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_MCSC,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_RGBP,
	VCLK_IP_SLH_ASTL_MI_G_PPMU_YUVP,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_NOCL2A,
	VCLK_IP_SIU_2X1_P0_NOCL2A,
	VCLK_IP_SIU_4X1_P0_NOCL2A,
	VCLK_IP_SIU_8X1_P1_NOCL2A,
	VCLK_IP_SLH_ASTL_MI_IG_PPMU_NOCL2A,
	VCLK_IP_SLH_ASTL_SI_IG_PPMU_NOCL2A,
	VCLK_IP_SLH_AST_MI_IG_DEBUG_MUX_NOCL2A,
	VCLK_IP_SLH_AST_SI_IG_DEBUG_MUX_NOCL2A,
	VCLK_IP_PERIC0_CMU_PERIC0,
	VCLK_IP_SYSREG_PERIC0,
	VCLK_IP_GPIO_PERIC0,
	VCLK_IP_SLH_AXI_MI_P_PERIC0,
	VCLK_IP_D_TZPC_PERIC0,
	VCLK_IP_USI04_USI,
	VCLK_IP_USI04_I2C,
	VCLK_IP_PERIC1_CMU_PERIC1,
	VCLK_IP_GPIO_PERIC1,
	VCLK_IP_D_TZPC_PERIC1,
	VCLK_IP_SLH_AXI_MI_P_CSISPERIC1,
	VCLK_IP_SLH_AXI_MI_P_PERIC1,
	VCLK_IP_SYSREG_PERIC1,
	VCLK_IP_XIU_P_PERIC1,
	VCLK_IP_I3C00,
	VCLK_IP_I3C01,
	VCLK_IP_I3C02,
	VCLK_IP_BT_UART,
	VCLK_IP_USI07_USI,
	VCLK_IP_USI07_SPI_I2C,
	VCLK_IP_USI08_USI,
	VCLK_IP_USI08_SPI_I2C,
	VCLK_IP_USI09_I2C,
	VCLK_IP_USI10_I2C,
	VCLK_IP_USI09_USI,
	VCLK_IP_USI10_USI,
	VCLK_IP_SPI_MULTI_SLV_Q_CTRL_PERIC1,
	VCLK_IP_PERIC2_CMU_PERIC2,
	VCLK_IP_D_TZPC_PERIC2,
	VCLK_IP_GPIO_PERIC2,
	VCLK_IP_SLH_AXI_MI_P_PERIC2,
	VCLK_IP_SYSREG_PERIC2,
	VCLK_IP_USI00_SPI_I2C,
	VCLK_IP_USI01_SPI_I2C,
	VCLK_IP_USI02_I2C,
	VCLK_IP_USI03_I2C,
	VCLK_IP_USI05_I2C,
	VCLK_IP_USI06_I2C,
	VCLK_IP_USI00_USI,
	VCLK_IP_USI01_USI,
	VCLK_IP_USI02_USI,
	VCLK_IP_USI03_USI,
	VCLK_IP_USI05_USI,
	VCLK_IP_USI06_USI,
	VCLK_IP_I3C06,
	VCLK_IP_I3C07,
	VCLK_IP_I3C08,
	VCLK_IP_I3C09,
	VCLK_IP_I3C10,
	VCLK_IP_I3C11,
	VCLK_IP_SPI_MULTI_SLV_Q_CTRL_PERIC2,
	VCLK_IP_USI11_I2C,
	VCLK_IP_USI11_USI,
	VCLK_IP_I3C03,
	VCLK_IP_I3C04,
	VCLK_IP_I3C05,
	VCLK_IP_DBG_UART,
	VCLK_IP_PWM,
	VCLK_IP_PERIS_CMU_PERIS,
	VCLK_IP_D_TZPC_PERIS,
	VCLK_IP_GIC,
	VCLK_IP_LH_AST_MI_LD_ICC_CPUGIC_CLUSTER0,
	VCLK_IP_SLH_AXI_MI_P_PERIS,
	VCLK_IP_SLH_AXI_MI_P_PERISGIC,
	VCLK_IP_LH_AST_SI_LD_IRI_GICCPU_CLUSTER0,
	VCLK_IP_MCT,
	VCLK_IP_OTP_CON_TOP,
	VCLK_IP_SYSREG_PERIS,
	VCLK_IP_TMU_SUB,
	VCLK_IP_TMU_TOP,
	VCLK_IP_WDT0,
	VCLK_IP_WDT1,
	VCLK_IP_OTP_CON_BIRA,
	VCLK_IP_BUSIF_DDD_PERIS,
	VCLK_IP_DDD_PERIS,
	VCLK_IP_RGBP_CMU_RGBP,
	VCLK_IP_AD_APB_RGBP,
	VCLK_IP_D_TZPC_RGBP,
	VCLK_IP_SLH_AXI_MI_P_RGBP,
	VCLK_IP_LH_AXI_SI_D0_RGBP,
	VCLK_IP_PPMU_D0_RGBP,
	VCLK_IP_SYSMMU_D0_RGBP,
	VCLK_IP_SYSREG_RGBP,
	VCLK_IP_XIU_D0_RGBP,
	VCLK_IP_RGBP,
	VCLK_IP_LH_AST_MI_OTF_BYRPRGBP,
	VCLK_IP_LH_AST_SI_OTF_RGBPMCFP,
	VCLK_IP_VGEN_LITE_RGBP,
	VCLK_IP_PPMU_D1_RGBP,
	VCLK_IP_LH_AXI_SI_D1_RGBP,
	VCLK_IP_XIU_D1_RGBP,
	VCLK_IP_SYSMMU_D1_RGBP,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_RGBP,
	VCLK_IP_SIU_G_PPMU_RGBP,
	VCLK_IP_S2D_CMU_S2D,
	VCLK_IP_BIS_S2D,
	VCLK_IP_SLH_AXI_MI_G_SCAN2DRAM,
	VCLK_IP_SDMA_CMU_SDMA,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA5,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA4,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA7,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA6,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA1,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA0,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA3,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_DATA2,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_MMU1,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_MMU2,
	VCLK_IP_SLH_AXI_MI_P_SDMA,
	VCLK_IP_SYSREG_SDMA,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_MMU0,
	VCLK_IP_LH_AXI_SI_LD_SDMADNC_MMU3,
	VCLK_IP_D_TZPC_SDMA,
	VCLK_IP_LH_AST_SI_LD_STRM_SDMADSP0,
	VCLK_IP_LH_AST_SI_LD_STRM_SDMADSP1,
	VCLK_IP_IP_SDMA,
	VCLK_IP_LH_AXI_MI_LP_DNCSDMA,
	VCLK_IP_SSP_CMU_SSP,
	VCLK_IP_BAAW_SSS,
	VCLK_IP_BPS_AXI_P_SSP,
	VCLK_IP_D_TZPC_SSP,
	VCLK_IP_LH_AXI_MI_L_STRONG,
	VCLK_IP_SLH_AXI_MI_P_SSP,
	VCLK_IP_SLH_ACEL_SI_D_SSP,
	VCLK_IP_PPMU_SSP,
	VCLK_IP_QE_RTIC,
	VCLK_IP_QE_STRONG,
	VCLK_IP_QE_SSS,
	VCLK_IP_RTIC,
	VCLK_IP_SSS,
	VCLK_IP_SWEEPER_D_SSP,
	VCLK_IP_SYSREG_SSP,
	VCLK_IP_VGEN_LITE_SSP,
	VCLK_IP_XIU_D_SSP,
	VCLK_IP_AD_APB_SYSMMU_SSP,
	VCLK_IP_SYSMMU_SSP,
	VCLK_IP_US_32TO128_SSSCORE,
	VCLK_IP_ADM_DAP_G_SSS,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_SSP,
	VCLK_IP_STRONG_CMU_STRONG,
	VCLK_IP_UFD_CMU_UFD,
	VCLK_IP_D_TZPC_UFD,
	VCLK_IP_SLH_AXI_MI_LP_CMGPUFD,
	VCLK_IP_SLH_AXI_MI_P_UFD,
	VCLK_IP_PDMA_UFD,
	VCLK_IP_SYSREG_UFD,
	VCLK_IP_UFD,
	VCLK_IP_XIU_DP_UFD,
	VCLK_IP_SPI_UFD,
	VCLK_IP_VGEN_LITE_D_UFD,
	VCLK_IP_SLH_AXI_SI_D_UFD,
	VCLK_IP_XIU_D_UFD,
	VCLK_IP_SLH_AXI_SI_LD_UFDDNC,
	VCLK_IP_SRAM_MIU_UFD,
	VCLK_IP_I3C_UFD,
	VCLK_IP_BAAW_D_UFDDNC,
	VCLK_IP_SYSREG_UFD_SECURE,
	VCLK_IP_ID_COMP_UFD,
	VCLK_IP_SLH_AXI_SI_LP_UFDCSIS,
	VCLK_IP_SLH_AST_MI_OTF_CSISUFD,
	VCLK_IP_AHB2AXI_AHB0,
	VCLK_IP_AHB2AXI_AHB4,
	VCLK_IP_ASYNCAXI0,
	VCLK_IP_ASYNCAXI2,
	VCLK_IP_ASYNCAXI4,
	VCLK_IP_BAAW_C_VTS,
	VCLK_IP_BPS_LP_VTS,
	VCLK_IP_BPS_P_VTS,
	VCLK_IP_DMAILBOX_TEST,
	VCLK_IP_DMIC_AHB0,
	VCLK_IP_DMIC_AHB2,
	VCLK_IP_DMIC_AHB4,
	VCLK_IP_DMIC_IF0,
	VCLK_IP_DMIC_IF1,
	VCLK_IP_DMIC_IF2,
	VCLK_IP_D_TZPC_VTS,
	VCLK_IP_GPIO_VTS,
	VCLK_IP_HWACG_SYS_DMIC0,
	VCLK_IP_HWACG_SYS_DMIC2,
	VCLK_IP_HWACG_SYS_DMIC4,
	VCLK_IP_INTMEM_CODE,
	VCLK_IP_INTMEM_DATA0,
	VCLK_IP_INTMEM_DATA1,
	VCLK_IP_INTMEM_PCM,
	VCLK_IP_SLH_AXI_MI_LD_AUDVTS,
	VCLK_IP_SLH_AXI_MI_LP_VTS,
	VCLK_IP_SLH_AXI_MI_P_VTS,
	VCLK_IP_SLH_AXI_SI_C_VTS,
	VCLK_IP_MAILBOX_ABOX_VTS,
	VCLK_IP_MAILBOX_AP_VTS,
	VCLK_IP_PDMA_VTS,
	VCLK_IP_SERIAL_LIF_VT,
	VCLK_IP_SS_VTS_GLUE,
	VCLK_IP_SWEEPER_C_VTS,
	VCLK_IP_SYSREG_VTS,
	VCLK_IP_VGEN_LITE,
	VCLK_IP_WDT_VTS,
	VCLK_IP_AHB2AXI_AHB2,
	VCLK_IP_XIU_DP1_VTS,
	VCLK_IP_VTS_CMU_VTS,
	VCLK_IP_SLH_AXI_MI_LD_DNCVTS,
	VCLK_IP_TIMER,
	VCLK_IP_TIMER1,
	VCLK_IP_TIMER2,
	VCLK_IP_YAMIN_MCU_VTS,
	VCLK_IP_MAILBOX_DNC_VTS,
	VCLK_IP_ASYNCAXI_SERIAL_LIF_VT,
	VCLK_IP_ASYNCINTERRUPT_VTS,
	VCLK_IP_YUVP_CMU_YUVP,
	VCLK_IP_AD_APB_YUVP,
	VCLK_IP_SLH_AXI_MI_P_YUVP,
	VCLK_IP_SYSREG_YUVP,
	VCLK_IP_SLH_AXI_SI_D_YUVP,
	VCLK_IP_PPMU_YUVP,
	VCLK_IP_SYSMMU_D_YUVP,
	VCLK_IP_XIU_D_YUVP,
	VCLK_IP_YUVP,
	VCLK_IP_LH_AST_MI_OTF0_MCFPYUVP,
	VCLK_IP_LH_AST_SI_OTF_YUVPDRCP,
	VCLK_IP_D_TZPC_YUVP,
	VCLK_IP_LH_AST_SI_OTF_YUVPMCFP,
	VCLK_IP_HPM_YUVP,
	VCLK_IP_BUSIF_HPM_YUVP,
	VCLK_IP_BUSIF_DDD_YUVP,
	VCLK_IP_BUSIF_ADD_YUVP,
	VCLK_IP_ADD_YUVP,
	VCLK_IP_DDD_YUVP,
	VCLK_IP_VGEN_LITE_YUVP,
	VCLK_IP_SLH_ASTL_SI_G_PPMU_YUVP,
	end_of_gate_vclk,
	num_of_gate_vclk = end_of_gate_vclk - ((MASK_OF_ID & end_of_common_vclk) | GATE_VCLK_TYPE),

};
#endif
