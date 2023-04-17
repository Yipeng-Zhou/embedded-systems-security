#include <xmc_common.h>

void initCCU4(void);
void connectLED(void);

int main(void)
{
	initCCU4();

	while(1);
	return 0;
}

void initCCU4()
{
	SCU_RESET -> PRCLR0 = SCU_RESET_PRCLR0_CCU40RS_Msk;
	SCU_CLK -> CLKSET = SCU_CLK_CLKSET_CCUCEN_Msk;
	CCU40 -> GIDLC = CCU4_GIDLC_SPRB_Msk;
	CCU40_CC42 -> PRS = 0XFFFF;
	CCU40_CC42 -> CRS = (1 - 0.1) * 0XFFFF;
	CCU40 -> GCSS = CCU4_GCSS_S2SE_Msk;
	connectLED();
	CCU40 -> GIDLC = CCU4_GIDLC_CS2I_Msk;
	CCU40_CC42 -> TCSET = CCU4_CC4_TCSET_TRBS_Msk;
}

void connectLED()
{
	static const uint8_t PP_ALT3 = 0b10011;
	PORT1 -> IOCR0 = (PORT1 -> IOCR0 & ~PORT1_IOCR0_PC1_Msk) | (PP_ALT3 << PORT1_IOCR0_PC1_Pos);
}

