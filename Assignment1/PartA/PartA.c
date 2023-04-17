#include <xmc_common.h>

//counter
uint32_t volatile msTicks = 0;
void SysTick_Handler(void)
{
	msTicks++;
}

//turn on led
void On(uint32_t time)
{
	uint32_t curTicks = msTicks;
	while(msTicks - curTicks <= time)
	{
		PORT1->OMR = PORT1_OMR_PS1_Msk;
               	PORT1->OMR = ~PORT1_OMR_PR1_Msk;
	}
}

//turn off led
void Off(uint32_t time)
{
        uint32_t curTicks = msTicks;
        while(msTicks - curTicks <= time)
        {
                PORT1->OMR = PORT1_OMR_PS1_Msk;
                PORT1->OMR = PORT1_OMR_PR1_Msk;
        }
}

//alphabet morse
void AMorse(char x)
{
        switch(x)
        {
                case 'I':
                        On(100);
                        Off(100);
                        On(100);
                        break;
                case 'C':
                        On(300);
                        Off(100);
                        On(100);
                        Off(100);
                        On(300);
                        Off(100);
                        On(100);
                        break;
                case 'A':
                        On(100);
                        Off(100);
                        On(300);
                        break;
                case 'N':
                        On(300);
                        Off(100);
                        On(100);
                        break;
                case 'M':
                        On(300);
                        Off(100);
                        On(300);
                        break;
                case 'O':
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        break;
                case 'R':
                        On(100);
                        Off(100);
                        On(300);
                        Off(100);
                        On(100);
                        break;
                case 'S':
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        break;
                case 'E':
                        On(100);
                        break;
        }
}

int main(void)
{
	//setup SysTick
	SysTick_Config (SystemCoreClock / 1000);

	//configure led
	static const uint8_t PP_GPO = 0b10000;
	PORT1->IOCR0 = (PORT1->IOCR0 & ~PORT1_IOCR0_PC1_Msk) | (PP_GPO << PORT1_IOCR0_PC1_Pos);
	PORT1->PDR0 = PORT1_PDR0_PD1_Msk;

	while(1)
	{
        	AMorse('I');
        	Off(700);
               	AMorse('C');
                Off(300);
              	AMorse('A');
               	Off(300);
                AMorse('N');
               	Off(700);
                AMorse('M');
                Off(300);
                AMorse('O');
                Off(300);
                AMorse('R');
                Off(300);
                AMorse('S');
                Off(300);
                AMorse('E');
                Off(5000);
	}

	return 0;
}
