#include <stdio.h>
#include "soc/reg_base.h" // DR_REG_GPIO_BASE, DR_REG_IO_MUX_BASE
#include "driver/rtc_io.h" // rtc_gpio_*
#include "pin.h"

// TODO: GPIO Matrix Registers - GPIO_OUT_REG, GPIO_OUT_W1TS_REG, ...
// NOTE: Remember to enclose the macro values in parenthesis, as below
#define GPIO_BT_SELECT_REG          (DR_REG_GPIO_BASE + 0x0000)
#define GPIO_OUT_REG          (DR_REG_GPIO_BASE + 0x0004)
#define GPIO_OUT_W1TS_REG          (DR_REG_GPIO_BASE + 0x0008)
#define GPIO_OUT_W1TC_REG          (DR_REG_GPIO_BASE + 0x000c)
#define GPIO_OUT1_REG          (DR_REG_GPIO_BASE + 0x0010)
#define GPIO_OUT1_W1TS_REG          (DR_REG_GPIO_BASE + 0x0014)
#define GPIO_OUT1_W1TC_REG          (DR_REG_GPIO_BASE + 0x0018)
#define GPIO_SDIO_SELECT_REG          (DR_REG_GPIO_BASE + 0x001c)
#define GPIO_ENABLE_REG          (DR_REG_GPIO_BASE + 0x0020)
#define GPIO_ENABLE_W1TS_REG          (DR_REG_GPIO_BASE + 0x0024)
#define GPIO_ENABLE_W1TC_REG          (DR_REG_GPIO_BASE + 0x0028)
#define GPIO_ENABLE1_REG          (DR_REG_GPIO_BASE + 0x002c)
#define GPIO_ENABLE1_W1TS_REG          (DR_REG_GPIO_BASE + 0x0030)
#define GPIO_ENABLE1_W1TC_REG          (DR_REG_GPIO_BASE + 0x0034)
#define GPIO_STRAP_REG          (DR_REG_GPIO_BASE + 0x0038)
#define GPIO_IN_REG          (DR_REG_GPIO_BASE + 0x003c)
#define GPIO_IN1_REG          (DR_REG_GPIO_BASE + 0x0040)
#define GPIO_STATUS_REG          (DR_REG_GPIO_BASE + 0x0044)
#define GPIO_STATUS_W1TS_REG          (DR_REG_GPIO_BASE + 0x0048)
#define GPIO_STATUS_W1TC_REG          (DR_REG_GPIO_BASE + 0x004c)
#define GPIO_STATUS1_REG          (DR_REG_GPIO_BASE + 0x0050)
#define GPIO_STATUS1_W1TS_REG          (DR_REG_GPIO_BASE + 0x0054)
#define GPIO_STATUS1_W1TC_REG          (DR_REG_GPIO_BASE + 0x0058)
#define GPIO_ACPU_INT_REG          (DR_REG_GPIO_BASE + 0x0060)
#define GPIO_ACPU_NMI_INT_REG          (DR_REG_GPIO_BASE + 0x0064)
#define GPIO_PCPU_INT_REG          (DR_REG_GPIO_BASE + 0x0068)
#define GPIO_PCPU_NMI_INT_REG          (DR_REG_GPIO_BASE + 0x006c)
#define GPIO_CPUSDIO_INT_REG          (DR_REG_GPIO_BASE + 0x0070)
#define GPIO_ACPU_INT1_REG          (DR_REG_GPIO_BASE + 0x0074)
#define GPIO_ACPU_NMI_INT1_REG          (DR_REG_GPIO_BASE + 0x0078)
#define GPIO_PCPU_INT1_REG          (DR_REG_GPIO_BASE + 0x007c)
#define GPIO_PCPU_NMI_INT1_REG          (DR_REG_GPIO_BASE + 0x0080)
#define GPIO_CPUSDIO_INT1_REG          (DR_REG_GPIO_BASE + 0x0084)
#define GPIO_PIN0_REG          (DR_REG_GPIO_BASE + 0x0088)
#define GPIO_PIN1_REG          (DR_REG_GPIO_BASE + 0x008c)
#define GPIO_PIN2_REG          (DR_REG_GPIO_BASE + 0x0090)
#define GPIO_PIN3_REG          (DR_REG_GPIO_BASE + 0x0094)
#define GPIO_PIN4_REG          (DR_REG_GPIO_BASE + 0x0098)
#define GPIO_PIN5_REG          (DR_REG_GPIO_BASE + 0x009c)
#define GPIO_PIN6_REG          (DR_REG_GPIO_BASE + 0x00a0)
#define GPIO_PIN7_REG          (DR_REG_GPIO_BASE + 0x00a4)
#define GPIO_PIN8_REG          (DR_REG_GPIO_BASE + 0x00a8)
#define GPIO_PIN9_REG          (DR_REG_GPIO_BASE + 0x00ac)
#define GPIO_PIN10_REG          (DR_REG_GPIO_BASE + 0x00b0)
#define GPIO_PIN11_REG          (DR_REG_GPIO_BASE + 0x00b4)
#define GPIO_PIN12_REG          (DR_REG_GPIO_BASE + 0x00b8)
#define GPIO_PIN13_REG          (DR_REG_GPIO_BASE + 0x00bc)
#define GPIO_PIN14_REG          (DR_REG_GPIO_BASE + 0x00c0)
#define GPIO_PIN15_REG          (DR_REG_GPIO_BASE + 0x00c4)
#define GPIO_PIN16_REG          (DR_REG_GPIO_BASE + 0x00c8)
#define GPIO_PIN17_REG          (DR_REG_GPIO_BASE + 0x00cc)
#define GPIO_PIN18_REG          (DR_REG_GPIO_BASE + 0x00d0)
#define GPIO_PIN19_REG          (DR_REG_GPIO_BASE + 0x00d4)
#define GPIO_PIN20_REG          (DR_REG_GPIO_BASE + 0x00d8)
#define GPIO_PIN21_REG          (DR_REG_GPIO_BASE + 0x00dc)
#define GPIO_PIN22_REG          (DR_REG_GPIO_BASE + 0x00e0)
#define GPIO_PIN23_REG          (DR_REG_GPIO_BASE + 0x00e4)
#define GPIO_PIN24_REG          (DR_REG_GPIO_BASE + 0x00e8)
#define GPIO_PIN25_REG          (DR_REG_GPIO_BASE + 0x00ec)
#define GPIO_PIN26_REG          (DR_REG_GPIO_BASE + 0x00f0)
#define GPIO_PIN27_REG          (DR_REG_GPIO_BASE + 0x00f4)
#define GPIO_PIN28_REG          (DR_REG_GPIO_BASE + 0x00f8)
#define GPIO_PIN29_REG          (DR_REG_GPIO_BASE + 0x00fc)
#define GPIO_PIN30_REG          (DR_REG_GPIO_BASE + 0x0100)
#define GPIO_PIN31_REG          (DR_REG_GPIO_BASE + 0x0104)
#define GPIO_PIN32_REG          (DR_REG_GPIO_BASE + 0x0108)
#define GPIO_PIN33_REG          (DR_REG_GPIO_BASE + 0x010c)
#define GPIO_PIN34_REG          (DR_REG_GPIO_BASE + 0x0110)
#define GPIO_PIN35_REG          (DR_REG_GPIO_BASE + 0x0114)
#define GPIO_PIN36_REG          (DR_REG_GPIO_BASE + 0x0118)
#define GPIO_PIN37_REG          (DR_REG_GPIO_BASE + 0x011c)
#define GPIO_PIN38_REG          (DR_REG_GPIO_BASE + 0x0120)
#define GPIO_PIN39_REG          (DR_REG_GPIO_BASE + 0x0124)
#define GPIO_cali_conf_REG          (DR_REG_GPIO_BASE + 0x0128)
#define GPIO_cali_data_REG          (DR_REG_GPIO_BASE + 0x012c)
#define GPIO_FUNC0_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0130)
#define GPIO_FUNC1_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0134)
#define GPIO_FUNC2_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0138)
#define GPIO_FUNC3_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x013c)
#define GPIO_FUNC4_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0140)
#define GPIO_FUNC5_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0144)
#define GPIO_FUNC6_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0148)
#define GPIO_FUNC7_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x014c)
#define GPIO_FUNC8_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0150)
#define GPIO_FUNC9_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0154)
#define GPIO_FUNC10_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0158)
#define GPIO_FUNC11_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x015c)
#define GPIO_FUNC12_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0160)
#define GPIO_FUNC13_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0164)
#define GPIO_FUNC14_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0168)
#define GPIO_FUNC15_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x016c)
#define GPIO_FUNC16_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0170)
#define GPIO_FUNC17_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0174)
#define GPIO_FUNC18_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0178)
#define GPIO_FUNC19_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x017c)
#define GPIO_FUNC20_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0180)
#define GPIO_FUNC21_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0184)
#define GPIO_FUNC22_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0188)
#define GPIO_FUNC23_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x018c)
#define GPIO_FUNC24_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0190)
#define GPIO_FUNC25_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0194)
#define GPIO_FUNC26_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0198)
#define GPIO_FUNC27_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x019c)
#define GPIO_FUNC28_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01a0)
#define GPIO_FUNC29_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01a4)
#define GPIO_FUNC30_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01a8)
#define GPIO_FUNC31_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01ac)
#define GPIO_FUNC32_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01b0)
#define GPIO_FUNC33_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01b4)
#define GPIO_FUNC34_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01b8)
#define GPIO_FUNC35_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01bc)
#define GPIO_FUNC36_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01c0)
#define GPIO_FUNC37_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01c4)
#define GPIO_FUNC38_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01c8)
#define GPIO_FUNC39_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01cc)
#define GPIO_FUNC40_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01d0)
#define GPIO_FUNC41_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01d4)
#define GPIO_FUNC42_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01d8)
#define GPIO_FUNC43_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01dc)
#define GPIO_FUNC44_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01e0)
#define GPIO_FUNC45_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01e4)
#define GPIO_FUNC46_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01e8)
#define GPIO_FUNC47_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01ec)
#define GPIO_FUNC48_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01f0)
#define GPIO_FUNC49_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01f4)
#define GPIO_FUNC50_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01f8)
#define GPIO_FUNC51_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x01fc)
#define GPIO_FUNC52_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0200)
#define GPIO_FUNC53_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0204)
#define GPIO_FUNC54_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0208)
#define GPIO_FUNC55_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x020c)
#define GPIO_FUNC56_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0210)
#define GPIO_FUNC57_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0214)
#define GPIO_FUNC58_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0218)
#define GPIO_FUNC59_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x021c)
#define GPIO_FUNC60_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0220)
#define GPIO_FUNC61_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0224)
#define GPIO_FUNC62_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0228)
#define GPIO_FUNC63_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x022c)
#define GPIO_FUNC64_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0230)
#define GPIO_FUNC65_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0234)
#define GPIO_FUNC66_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0238)
#define GPIO_FUNC67_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x023c)
#define GPIO_FUNC68_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0240)
#define GPIO_FUNC69_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0244)
#define GPIO_FUNC70_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0248)
#define GPIO_FUNC71_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x024c)
#define GPIO_FUNC72_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0250)
#define GPIO_FUNC73_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0254)
#define GPIO_FUNC74_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0258)
#define GPIO_FUNC75_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x025c)
#define GPIO_FUNC76_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0260)
#define GPIO_FUNC77_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0264)
#define GPIO_FUNC78_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0268)
#define GPIO_FUNC79_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x026c)
#define GPIO_FUNC80_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0270)
#define GPIO_FUNC81_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0274)
#define GPIO_FUNC82_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0278)
#define GPIO_FUNC83_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x027c)
#define GPIO_FUNC84_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0280)
#define GPIO_FUNC85_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0284)
#define GPIO_FUNC86_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0288)
#define GPIO_FUNC87_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x028c)
#define GPIO_FUNC88_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0290)
#define GPIO_FUNC89_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0294)
#define GPIO_FUNC90_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0298)
#define GPIO_FUNC91_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x029c)
#define GPIO_FUNC92_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02a0)
#define GPIO_FUNC93_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02a4)
#define GPIO_FUNC94_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02a8)
#define GPIO_FUNC95_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02ac)
#define GPIO_FUNC96_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02b0)
#define GPIO_FUNC97_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02b4)
#define GPIO_FUNC98_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02b8)
#define GPIO_FUNC99_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02bc)
#define GPIO_FUNC100_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02c0)
#define GPIO_FUNC101_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02c4)
#define GPIO_FUNC102_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02c8)
#define GPIO_FUNC103_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02cc)
#define GPIO_FUNC104_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02d0)
#define GPIO_FUNC105_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02d4)
#define GPIO_FUNC106_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02d8)
#define GPIO_FUNC107_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02dc)
#define GPIO_FUNC108_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02e0)
#define GPIO_FUNC109_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02e4)
#define GPIO_FUNC110_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02e8)
#define GPIO_FUNC111_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02ec)
#define GPIO_FUNC112_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02f0)
#define GPIO_FUNC113_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02f4)
#define GPIO_FUNC114_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02f8)
#define GPIO_FUNC115_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x02fc)
#define GPIO_FUNC116_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0300)
#define GPIO_FUNC117_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0304)
#define GPIO_FUNC118_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0308)
#define GPIO_FUNC119_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x030c)
#define GPIO_FUNC120_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0310)
#define GPIO_FUNC121_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0314)
#define GPIO_FUNC122_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0318)
#define GPIO_FUNC123_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x031c)
#define GPIO_FUNC124_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0320)
#define GPIO_FUNC125_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0324)
#define GPIO_FUNC126_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0328)
#define GPIO_FUNC127_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x032c)
#define GPIO_FUNC128_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0330)
#define GPIO_FUNC129_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0334)
#define GPIO_FUNC130_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0338)
#define GPIO_FUNC131_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x033c)
#define GPIO_FUNC132_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0340)
#define GPIO_FUNC133_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0344)
#define GPIO_FUNC134_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0348)
#define GPIO_FUNC135_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x034c)
#define GPIO_FUNC136_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0350)
#define GPIO_FUNC137_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0354)
#define GPIO_FUNC138_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0358)
#define GPIO_FUNC139_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x035c)
#define GPIO_FUNC140_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0360)
#define GPIO_FUNC141_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0364)
#define GPIO_FUNC142_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0368)
#define GPIO_FUNC143_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x036c)
#define GPIO_FUNC144_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0370)
#define GPIO_FUNC145_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0374)
#define GPIO_FUNC146_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0378)
#define GPIO_FUNC147_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x037c)
#define GPIO_FUNC148_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0380)
#define GPIO_FUNC149_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0384)
#define GPIO_FUNC150_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0388)
#define GPIO_FUNC151_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x038c)
#define GPIO_FUNC152_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0390)
#define GPIO_FUNC153_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0394)
#define GPIO_FUNC154_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0398)
#define GPIO_FUNC155_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x039c)
#define GPIO_FUNC156_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03a0)
#define GPIO_FUNC157_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03a4)
#define GPIO_FUNC158_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03a8)
#define GPIO_FUNC159_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03ac)
#define GPIO_FUNC160_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03b0)
#define GPIO_FUNC161_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03b4)
#define GPIO_FUNC162_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03b8)
#define GPIO_FUNC163_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03bc)
#define GPIO_FUNC164_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03c0)
#define GPIO_FUNC165_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03c4)
#define GPIO_FUNC166_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03c8)
#define GPIO_FUNC167_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03cc)
#define GPIO_FUNC168_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03d0)
#define GPIO_FUNC169_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03d4)
#define GPIO_FUNC170_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03d8)
#define GPIO_FUNC171_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03dc)
#define GPIO_FUNC172_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03e0)
#define GPIO_FUNC173_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03e4)
#define GPIO_FUNC174_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03e8)
#define GPIO_FUNC175_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03ec)
#define GPIO_FUNC176_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03f0)
#define GPIO_FUNC177_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03f4)
#define GPIO_FUNC178_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03f8)
#define GPIO_FUNC179_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x03fc)
#define GPIO_FUNC180_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0400)
#define GPIO_FUNC181_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0404)
#define GPIO_FUNC182_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0408)
#define GPIO_FUNC183_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x040c)
#define GPIO_FUNC184_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0410)
#define GPIO_FUNC185_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0414)
#define GPIO_FUNC186_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0418)
#define GPIO_FUNC187_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x041c)
#define GPIO_FUNC188_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0420)
#define GPIO_FUNC189_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0424)
#define GPIO_FUNC190_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0428)
#define GPIO_FUNC191_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x042c)
#define GPIO_FUNC192_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0430)
#define GPIO_FUNC193_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0434)
#define GPIO_FUNC194_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0438)
#define GPIO_FUNC195_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x043c)
#define GPIO_FUNC196_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0440)
#define GPIO_FUNC197_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0444)
#define GPIO_FUNC198_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0448)
#define GPIO_FUNC199_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x044c)
#define GPIO_FUNC200_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0450)
#define GPIO_FUNC201_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0454)
#define GPIO_FUNC202_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0458)
#define GPIO_FUNC203_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x045c)
#define GPIO_FUNC204_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0460)
#define GPIO_FUNC205_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0464)
#define GPIO_FUNC206_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0468)
#define GPIO_FUNC207_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x046c)
#define GPIO_FUNC208_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0470)
#define GPIO_FUNC209_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0474)
#define GPIO_FUNC210_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0478)
#define GPIO_FUNC211_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x047c)
#define GPIO_FUNC212_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0480)
#define GPIO_FUNC213_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0484)
#define GPIO_FUNC214_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0488)
#define GPIO_FUNC215_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x048c)
#define GPIO_FUNC216_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0490)
#define GPIO_FUNC217_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0494)
#define GPIO_FUNC218_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0498)
#define GPIO_FUNC219_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x049c)
#define GPIO_FUNC220_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04a0)
#define GPIO_FUNC221_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04a4)
#define GPIO_FUNC222_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04a8)
#define GPIO_FUNC223_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04ac)
#define GPIO_FUNC224_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04b0)
#define GPIO_FUNC225_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04b4)
#define GPIO_FUNC226_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04b8)
#define GPIO_FUNC227_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04bc)
#define GPIO_FUNC228_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04c0)
#define GPIO_FUNC229_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04c4)
#define GPIO_FUNC230_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04c8)
#define GPIO_FUNC231_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04cc)
#define GPIO_FUNC232_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04d0)
#define GPIO_FUNC233_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04d4)
#define GPIO_FUNC234_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04d8)
#define GPIO_FUNC235_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04dc)
#define GPIO_FUNC236_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04e0)
#define GPIO_FUNC237_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04e4)
#define GPIO_FUNC238_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04e8)
#define GPIO_FUNC239_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04ec)
#define GPIO_FUNC240_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04f0)
#define GPIO_FUNC241_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04f4)
#define GPIO_FUNC242_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04f8)
#define GPIO_FUNC243_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x04fc)
#define GPIO_FUNC244_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0500)
#define GPIO_FUNC245_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0504)
#define GPIO_FUNC246_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0508)
#define GPIO_FUNC247_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x050c)
#define GPIO_FUNC248_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0510)
#define GPIO_FUNC249_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0514)
#define GPIO_FUNC250_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0518)
#define GPIO_FUNC251_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x051c)
#define GPIO_FUNC252_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0520)
#define GPIO_FUNC253_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0524)
#define GPIO_FUNC254_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0528)
#define GPIO_FUNC255_IN_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x052c)
#define GPIO_FUNC0_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0530)
#define GPIO_FUNC1_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0534)
#define GPIO_FUNC2_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0538)
#define GPIO_FUNC3_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x053c)
#define GPIO_FUNC4_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0540)
#define GPIO_FUNC5_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0544)
#define GPIO_FUNC6_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0548)
#define GPIO_FUNC7_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x054c)
#define GPIO_FUNC8_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0550)
#define GPIO_FUNC9_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0554)
#define GPIO_FUNC10_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0558)
#define GPIO_FUNC11_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x055c)
#define GPIO_FUNC12_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0560)
#define GPIO_FUNC13_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0564)
#define GPIO_FUNC14_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0568)
#define GPIO_FUNC15_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x056c)
#define GPIO_FUNC16_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0570)
#define GPIO_FUNC17_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0574)
#define GPIO_FUNC18_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0578)
#define GPIO_FUNC19_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x057c)
#define GPIO_FUNC20_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0580)
#define GPIO_FUNC21_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0584)
#define GPIO_FUNC22_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0588)
#define GPIO_FUNC23_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x058c)
#define GPIO_FUNC24_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0590)
#define GPIO_FUNC25_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0594)
#define GPIO_FUNC26_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x0598)
#define GPIO_FUNC27_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x059c)
#define GPIO_FUNC28_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05a0)
#define GPIO_FUNC29_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05a4)
#define GPIO_FUNC30_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05a8)
#define GPIO_FUNC31_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05ac)
#define GPIO_FUNC32_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05b0)
#define GPIO_FUNC33_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05b4)
#define GPIO_FUNC34_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05b8)
#define GPIO_FUNC35_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05bc)
#define GPIO_FUNC36_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05c0)
#define GPIO_FUNC37_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05c4)
#define GPIO_FUNC38_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05c8)
#define GPIO_FUNC39_OUT_SEL_CFG_REG          (DR_REG_GPIO_BASE + 0x05cc)

// TODO: IO MUX Registers
// HINT: Add DR_REG_IO_MUX_BASE with PIN_MUX_REG_OFFSET[n]
#define IO_MUX_REG(n) (DR_REG_IO_MUX_BASE + PIN_MUX_REG_OFFSET[n])

// TODO: IO MUX Register Fields - FUN_WPD, FUN_WPU, ...
#define FUN_WPD  7

#define REG(r) (*(volatile uint32_t *)(r))
#define REG_BITS 32
// TODO: Finish these macros. HINT: Use the REG() macro.
#define REG_SET_BIT(r,b) r = (r | (0x1 << b))
#define REG_CLR_BIT(r,b) r = (r & ~(0x1 << b))
#define REG_GET_BIT(r,b) ((r >> b) & 0x1)

#define GPIO_REG_OFFSET 4

#define IO_MUX_PIN(pin) (REG(DR_REG_GPIO_BASE + PIN_MUX_REG_OFFSET[pin]))
#define IO_FUNC_REG(pin) (REG(GPIO_FUNC0_OUT_SEL_CFG_REG + pin*GPIO_REG_OFFSET))

#define OUT_SEL_SETUP_VAL 0b100000000

#define MCU_SEL_TOP 14
#define MCU_SEL_BOT 12
#define FUN_DRV_TOP 11
#define FUN_DRV_BOT 10
#define FUN_IE 9
#define FUN_WPU 8
#define FUN_WPD 7

#define PAD_DRIVER 2

#define SECOND_REG_PIN_CUTOFF 31
// Gives byte offset of IO_MUX Configuration Register
// from base address DR_REG_IO_MUX_BASE
static const uint8_t PIN_MUX_REG_OFFSET[] = {
    0x44, 0x88, 0x40, 0x84, 0x48, 0x6c, 0x60, 0x64, // pin  0- 7
    0x68, 0x54, 0x58, 0x5c, 0x34, 0x38, 0x30, 0x3c, // pin  8-15
    0x4c, 0x50, 0x70, 0x74, 0x78, 0x7c, 0x80, 0x8c, // pin 16-23
    0x90, 0x24, 0x28, 0x2c, 0xFF, 0xFF, 0xFF, 0xFF, // pin 24-31
    0x1c, 0x20, 0x14, 0x18, 0x04, 0x08, 0x0c, 0x10, // pin 32-39
};


// Reset the configuration of a pin to not be an input or an output.
// Pull-up is enabled so the pin does not float.
int32_t pin_reset(pin_num_t pin)
{
	if (rtc_gpio_is_valid_gpio(pin)) { // hand-off work to RTC subsystem
		rtc_gpio_deinit(pin);
		rtc_gpio_pullup_en(pin);
		rtc_gpio_pulldown_dis(pin);
	}
	reg(IO_MUX_REG(n)) = 0x00;
	// TODO: Reset GPIO_FUNCn_OUT_SEL_CFG_REG: GPIO_FUNCn_OUT_SEL=0x100
	
	IO_FUNC_REG(pin) &= OUT_SEL_SETUP_VAL;
	// TODO: Reset IO_MUX_x_REG: MCU_SEL=2, FUN_DRV=2, FUN_WPU=1
	//MCU_SEL
	REG_CLR_BIT(IO_MUX_PIN(pin), MCU_SEL_TOP);
	REG_CLR_BIT(IO_MUX_PIN(pin), MCU_SEL_BOT);
	REG_SET_BIT(IO_MUX_PIN(pin), MCU_SEL_BOT + 1);
	//FUN_DRV
	REG_CLR_BIT(IO_MUX_PIN(pin), FUN_DRV_BOT);
	REG_SET_BIT(IO_MUX_PIN(pin), FUN_DRV_TOP);
	//FUN_WPU
	REG_SET_BIT(IO_MUX_PIN(pin), FUN_WPU);

	// Now that the pin is reset, set the output level to zero
	return pin_set_level(pin, 0);
}

// Enable or disable a pull-up on the pin.
int32_t pin_pullup(pin_num_t pin, bool enable)
{
	if (rtc_gpio_is_valid_gpio(pin)) { // hand-off work to RTC subsystem
		if (enable) return rtc_gpio_pullup_en(pin);
		else return rtc_gpio_pullup_dis(pin);
	}
	// TODO: Set or clear the FUN_WPU bit in an IO_MUX register
	if (enable) {
		REG_SET_BIT(IO_MUX_PIN(pin), FUN_WPU);
	} else {
		REG_CLR_BIT(IO_MUX_PIN(pin), FUN_WPU);
	}
	IO_MUX_PIN(pin);
	return 0;
}

// Enable or disable a pull-down on the pin.
int32_t pin_pulldown(pin_num_t pin, bool enable)
{
	if (rtc_gpio_is_valid_gpio(pin)) { // hand-off work to RTC subsystem
		if (enable) return rtc_gpio_pulldown_en(pin);
		else return rtc_gpio_pulldown_dis(pin);
	}
	// TODO: Set or clear the FUN_WPD bit in an IO_MUX register
	if (enable) {
		REG_SET_BIT(IO_MUX_PIN(pin), FUN_WPD);
	} else {
		REG_CLR_BIT(IO_MUX_PIN(pin), FUN_WPD);
	}
	return 0;
}

// Enable or disable the pin as an input signal.
int32_t pin_input(pin_num_t pin, bool enable)
{
	// TODO: Set or clear the FUN_IE bit in an IO_MUX register
	if (enable) {
		REG_SET_BIT(IO_MUX_PIN(pin), FUN_IE);
	} else {
		REG_CLR_BIT(IO_MUX_PIN(pin), FUN_IE);
	}
	return 0;
}

// Enable or disable the pin as an output signal.
int32_t pin_output(pin_num_t pin, bool enable)
{
	// TODO: Set or clear the I/O pin bit in the ENABLE or ENABLE1 register
	if (pin > SECOND_REGISTER_PIN_CUTOFF) {
		pin -= (SECOND_REGISTER_PIN_CUTOFF+1);
		if (enable) {
			REG_SET_BIT(REG(GPIO_ENABLE1_W1TS_REG), pin)
		} else {
			REG_SET_BIT(REG(GPIO_ENABLE1_W1TC_REG), pin)
		}
		//we use ENABLE1 regs
	} else {
		//we use ENABLE regs
		if (enable) {
			REG_SET_BIT(REG(GPIO_ENABLE_W1TS_REG), pin)
		} else {
			REG_SET_BIT(REG(GPIO_ENABLE_W1TC_REG), pin)
		}
	}
	return 0;
}

// Enable or disable the pin as an open-drain signal.
int32_t pin_odrain(pin_num_t pin, bool enable)
{
	// TODO: Set or clear the PAD_DRIVER bit in a PIN register
	if (enable) {
		REG_SET_BIT(REG(GPIO_PIN0_REG + GPIO_REG_OFFSET*pin), PAD_DRIVER);
	} else {
		REG_CLR_BIT(REG(GPIO_PIN0_REG + GPIO_REG_OFFSET*pin), PAD_DRIVER);
	}
	return 0;
}

// Sets the output signal level if the pin is configured as an output.
int32_t pin_set_level(pin_num_t pin, int32_t level)
{
		if (pin > SECOND_REG_PIN_CUTOFF) {
		pin -= SECOND_REG_PIN_CUTOFF;
		if (enable) {
			REG_SET_BIT(REG(GPIO_OUT1_W1TS_REG), pin)
		} else {
			REG_SET_BIT(REG(GPIO_OUT1_W1TC_REG), pin)
		}
		//we use ENABLE1 regs
	} else {
		//we use ENABLE regs
		if (enable) {
			REG_SET_BIT(REG(GPIO_OUT_W1TS_REG), pin)
		} else {
			REG_SET_BIT(REG(GPIO_OUT_W1TC_REG), pin)
		}
	}
	return 0;
	return 0SECOND_REGISTER_PIN_CUTOFF
}

// Gets the input signal level if the pin is configured as an input.
int32_t pin_get_level(pin_num_t pin)
{
	int32_t retval = 0;
	// TODO: Get the I/O pin bit from the IN or IN1 register
	if (pin > SECOND_REG_PIN_CUTOFF) {
		pin -= SECOND_REG_PIN_CUTOFF;
		ret_val = REG_GET_BIT(REG(GPIO_IN1_REG), pin);
		//we use ENABLE1 regs
	} else {
		ret_val = REG_GET_BIT(REG(GPIO_IN_REG), pin);
	}
	return ret_val;
}

// Get the value of the input registers, one pin per bit.
// The two 32-bit input registers are concatenated into a uint64_t.
uint64_t pin_get_in_reg(void)
{
	uint64_t ret_val = (REG(GPIO_IN1_REG) << (SECOND_REG_PIN_CUTOFF+1)) + REG(GPIO_IN_REG);
	return ret_val;
}

// Get the value of the output registers, one pin per bit.
// The two 32-bit output registers are concatenated into a uint64_t.
uint64_t pin_get_out_reg(void)
{
	uint64_t ret_val = (REG(GPIO_OUT1_REG) << (SECOND_REG_PIN_CUTOFF+1)) + REG(GPIO_IN_REG);
	return ret_val;
}
