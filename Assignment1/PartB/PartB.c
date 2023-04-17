#include <xmc_common.h>
#include <stdlib.h>


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

//digit morse
void DMorse(uint32_t x)
{
	switch(x)
	{
		case 0:
			On(300);
			Off(100);
			On(300);
			Off(100);
			On(300);
			Off(100);
			On(300);
			Off(100);
			On(300);
			break;
		case 1:
			On(100);
			Off(100);
			On(300);
			Off(100);
	               	On(300);
                        Off(100);
			On(300);
                        Off(100);
			On(300);
                        break;
                case 2:
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        break;
                case 3:
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        break;
                case 4:
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(300);
                        break;
                case 5:
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        break;
                case 6:
                        On(300);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        break;
                case 7:
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        break;
                case 8:
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(100);
                        Off(100);
                        On(100);
                        break;
                case 9:
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(300);
                        Off(100);
                        On(100);
                        break;	
	}
}

//save press-down time
uint32_t pdTimes[2] = {0};
uint32_t* point = pdTimes + 1;
void PressDownTimer(void)
{
        if(point == pdTimes)
        {
                point = pdTimes + 1;
                *point = msTicks;
        }
	else
        {
                point = pdTimes;
                *point = msTicks;
        }
}

//send digital morse code
void DCMorse(uint32_t x)
{
	uint32_t digit[8] = {0};
	digit[7] = (x / 1) % 10;
	digit[6] = (x / 10) % 10;
	digit[5] = (x / 100) % 10;
	digit[4] = (x / 1000) % 10;
	digit[3] = (x / 10000) % 10;
	digit[2] = (x / 100000) % 10;
	digit[1] = (x / 1000000) % 10;
	digit[0] = (x / 10000000) % 10;

	if(digit[0] != 0)
	{
		DMorse(digit[0]);
		Off(300);
		DMorse(digit[1]);
		Off(300);
		DMorse(digit[2]);
		Off(300);
		DMorse(digit[3]);
		Off(300);
		DMorse(digit[4]);
		Off(300);
		DMorse(digit[5]);
		Off(300);
		DMorse(digit[6]);
		Off(300);
		DMorse(digit[7]);
		Off(1);
	}
	else if(digit[1] != 0)
	{
               	DMorse(digit[1]);
                Off(300);
                DMorse(digit[2]);
                Off(300);
                DMorse(digit[3]);
                Off(300);
                DMorse(digit[4]);
                Off(300);
                DMorse(digit[5]);
                Off(300);
                DMorse(digit[6]);
                Off(300);
                DMorse(digit[7]);
                Off(1);
	}
	else if(digit[2] != 0)
        {
                DMorse(digit[2]);
                Off(300);
                DMorse(digit[3]);
                Off(300);
                DMorse(digit[4]);
                Off(300);
                DMorse(digit[5]);
                Off(300);
                DMorse(digit[6]);
                Off(300);
                DMorse(digit[7]);
                Off(1);
        }
	else if(digit[3] != 0)
        {
                DMorse(digit[3]);
                Off(300);
                DMorse(digit[4]);
                Off(300);
                DMorse(digit[5]);
                Off(300);
                DMorse(digit[6]);
                Off(300);
                DMorse(digit[7]);
                Off(1);
        }
	else if(digit[4] != 0)
        {
                DMorse(digit[4]);
                Off(300);
                DMorse(digit[5]);
                Off(300);
                DMorse(digit[6]);
                Off(300);
                DMorse(digit[7]);
                Off(1);
        }
	else if(digit[5] != 0)
        {
                DMorse(digit[5]);
                Off(300);
                DMorse(digit[6]);
                Off(300);
                DMorse(digit[7]);
                Off(1);
        }
	else if(digit[6] != 0)
        {
                DMorse(digit[6]);
                Off(300);
                DMorse(digit[7]);
                Off(1);
        }
	else
	{	
		DMorse(digit[7]);
		Off(1);
	}
}

int main(void)
{	
	uint32_t timedistance = 0;

	//setup SysTick
        SysTick_Config (SystemCoreClock / 1000);

	//configure led
        static const uint8_t PP_GPO = 0b10000;
        PORT1->IOCR0 = (PORT1->IOCR0 & ~PORT1_IOCR0_PC1_Msk) | (PP_GPO << PORT1_IOCR0_PC1_Pos);
        PORT1->PDR0 = PORT1_PDR0_PD1_Msk;
	
	//configure button
        static const uint8_t PP_GPI = 0b000;
        PORT1->IOCR12 = (PORT1->IOCR12 & ~PORT1_IOCR12_PC14_Msk) | (PP_GPI << PORT1_IOCR12_PC14_Pos);
        PORT1->IOCR12 = (PORT1->IOCR12 & ~PORT1_IOCR12_PC15_Msk) | (PP_GPI << PORT1_IOCR12_PC15_Pos);


        while(1)
        {
           	if(((PORT1->IN >> 14) & 0x1U) == 0)
                {
               		PressDownTimer();

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
                        Off(700);
		}

		if(((PORT1->IN >> 15) & 0x1U) == 0)
		{
			if(pdTimes[0] == 0 && pdTimes[1] == 0)
			{
				DMorse(0);
				Off(1);
			}
			else if(pdTimes[0] != 0 && pdTimes[1] == 0)
			{
				DCMorse(pdTimes[0]);
			}
			else
			{	
				timedistance = abs(pdTimes[1] - pdTimes[0]);
				DCMorse(timedistance);
			}	

		}
        }

        return 0;
}

