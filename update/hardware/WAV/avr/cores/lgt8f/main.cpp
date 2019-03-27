#include <stdint.h>
#include <avr/wdt.h>
#include <Arduino.h>

#if defined(__LGT8FX8E__) || defined(__LGT8FX8P__)
void __patch_wdt(void) \
	     __attribute__((naked)) \
	     __attribute__((section(".init3")));
void __patch_wdt(void)
{
	MCUSR = 0;
	wdt_disable();
}
#endif

void sysClock(uint8_t mode)
{
	if(mode == EXT_OSC) {
		// enable external crystal
		GPIOR0 = PMCR | 0x04;
		PMCR = 0x80;
		PMCR = GPIOR0;
		
		// waiting for crystal stable
		delay(20);

		// switch to external crystal
		GPIOR0 = (PMCR & 0x9f) | 0x20;
		PMCR = 0x80;
		PMCR = GPIOR0;

		// set to right prescale
		CLKPR = 0x80;
		CLKPR = 0x00;	
	} else if(mode == INT_OSC) {
		// prescaler settings
		CLKPR = 0x80;
		CLKPR = 0x01;	

		// switch to internal crystal
		GPIOR0 = PMCR & 0x9f;
		PMCR = 0x80;
		PMCR = GPIOR0;

		// disable external crystal
		GPIOR0 = PMCR & 0xfb;
		PMCR = 0x80;
		PMCR = GPIOR0;
	}
}	

void lgt8fx8x_init()
{
#if defined(__LGT8FX8E__)
// store ivref calibration 
	GPIOR1 = VCAL1;
	GPIOR2 = VCAL2;

#if defined(__LGT8F_SSOP20__)
	GPIOR0 = PMXCR | 0x07;
	PMXCR = 0x80;
	PMXCR = GPIOR0;
#endif

// enable 1KB E2PROM 
	ECCR = 0x80;
	ECCR = 0x40;

// clock source settings
	if((VDTCR & 0x0C) == 0x0C) {
		// switch to external crystal
		sysClock(EXT_OSC);
	} else {
		CLKPR = 0x80;
		CLKPR = 0x01;
	}
#else
	// enable 32KRC for WDT
	GPIOR0 = PMCR | 0x10;
	PMCR = 0x80;
	PMCR = GPIOR0;

	// clock scalar to 16MHz
	CLKPR = 0x80;
	CLKPR = 0x01;
#endif
}

int main(void)
{

#if defined(__LGT8F__)
	lgt8fx8x_init();
#endif	

	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}
