//============================================================================
//============================================================================
//
// FILE:    ELEX7820-Lab5-CCSv4-DevInit.c
//
// TITLE:   Device initialization for F2802x series
// 
// Version: 1.0
//
// Date:    2017 11 27
//
// Modified by: Peter Li and Lulu Li for use with:
//
// - CCSV 7.2
// - XDC tools 100v2 ver 3.25.03.72
// - SysBios ver 6.35.04.50
// - TI compiler Ver 6.2.11
//
//============================================================================

#include "DSP2802x_Device.h"

void DeviceInit(void);
extern void DelayUs(Uint16);

//--------------------------------------------------------------------
//  Configure Device for target Application Here
//--------------------------------------------------------------------
void DeviceInit(void)
{
   EALLOW; // below registers are "protected", allow access.

// LOW SPEED CLOCKS prescale register settings
   SysCtrlRegs.LOSPCP.all = 0x0002;		// Sysclk / 4 (15 MHz)
   SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2;
      	
// PERIPHERAL CLOCK ENABLES 
//---------------------------------------------------
// If you are not using a peripheral you may want to switch
// the clock off to save power, i.e. set to =0 
// 
// Note: not all peripherals are available on all 280x derivates.
// Refer to the datasheet for your particular device. 

   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC -PL
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 0;	// COMP1
   SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;	// COMP2
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;	// SPI-A -LL
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 0;  	// SCI-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;	//eCAP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 0;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 0;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 0;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Enable TBCLK
   //------------------------------------------------
                  
                                     
//--------------------------------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//	rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//	1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//	2) If IN, can leave next to lines commented
//	3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//			   uncomment line with ..GPASET.. to force pin HIGH or
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-00 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;		// 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO0 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-01 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;		// 0=GPIO,  1=EPWM1B,  2=EMU0,  3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO1 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-02 - PIN FUNCTION = --Spare-- - DACEN pin x -LL
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;		// 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;		// 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO2 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-03 - PIN FUNCTION = --Spare-- - DACEN pin y -LL
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;		// 0=GPIO,  1=EPWM2B,  2=Resv,  3=COMP2OUT
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO3 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-04 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;		// 0=GPIO,  1=EPWM3A, 2=Resv, 	3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO4 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-05 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;		// 0=GPIO,  1=EPWM3B,  2=Resv,  3=ECAP1
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO5 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-06 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;		// 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO6 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-07 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;		// 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO7 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-08 - GPIO-11 Do Not Exist
//--------------------------------------------------------------------------------------
//  GPIO-12 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;	// 0=GPIO,  1=TZ1,  2=SCITX-A,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO12 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-13 - GPIO-15 Do Not Exist
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

//  GPIO-16 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;	// 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO16 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-17 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;	// 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO17 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-18 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;	// 0=GPIO,  1=SPICLK-A,  2=SCITX-A,  3=XCLKOUT
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO18 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-19 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;	// 0=GPIO,  1=SPISTE-A,  2=SCIRX-A,  3=ECAP1
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO19 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-20 - GPIO-27 Do Not Exist
//--------------------------------------------------------------------------------------
//  GPIO-28 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;	// 0=GPIO,  1=SCIRX-A,  2=I2C-SDA,  3=TZ2
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO28 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-29 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;	// 0=GPIO,  1=SCITXD-A,  2=I2C-SCL,  3=TZ3
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO29 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-30 - GPIO-31 Do Not Exist
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

//  GPIO-32 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;	// 0=GPIO,  1=I2C-SDA,  2=SYNCI,  3=ADCSOCA
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO32 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-33 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;	// 0=GPIO,  1=I2C-SCL,  2=SYNCO,  3=ADCSOCB
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO33 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-34 - PIN FUNCTION = LED for F28027 USB dongle
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// 0=GPIO,  1=COMP2OUT,  2=EMU1,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------

    /*
    * GPIO Pins that are configured here are
    * - GPIO0 and GPIO1 as yEncoder Channel A and B
    * - GPIO3 and GPIO4 as xEncoder Channel A and B
    * - GPIO2 and GPIO3 as x and y DAC chip select
    * */

    /*
    * Uses Encoder channel A as the trigger
    *
    * xEnc on xint1 and yEnc on xint2
    *
    * */

	// PL
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;
	XIntruptRegs.XINT2CR.bit.ENABLE = 1;
	XIntruptRegs.XINT1CR.bit.POLARITY = 3;
	XIntruptRegs.XINT2CR.bit.POLARITY = 3;

	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 5; // X motor encoder interrupt
	GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 0; // Y motor encoder interrupt

	// Sets initial conditions for chip select
    GpioDataRegs.GPASET.bit.GPIO3 = 1; // sets gpio to 1 synchronously
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; // sets gpio to 0 synchronously


    // Enable ADC conversions to read from ADCIN0 and ADCIN1
	AdcRegs.ADCCTL1.bit.ADCPWDN = 1;
	AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;
	AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;

    DelayUs(1000);
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 0x6;
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0x0;
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 0x6;
    AdcRegs.ADCSOC1CTL.bit.CHSEL = 0x1;

    AdcRegs.INTSEL1N2.bit.INT1SEL = 0;
    AdcRegs.INTSEL1N2.bit.INT2SEL = 1;

    AdcRegs.INTSEL1N2.bit.INT2E = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;


    // Enable the SPI bus - LL
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;

    SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
    SpiaRegs.SPICCR.bit.SPICHAR = 15;

    SpiaRegs.SPICTL.bit.CLK_PHASE = 1;
    SpiaRegs.SPICTL.bit.TALK = 1;
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
    SpiaRegs.SPIBRR = 0;

    SpiaRegs.SPICCR.bit.SPISWRESET = 1;

    // Enable PIE control registers
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // sets gpio to 0 synchronously
    GpioDataRegs.GPASET.bit.GPIO1 = 1; // sets gpio to 1 synchronously

    //PL
    // Change flash wait states to enable faster reading from flash
    FlashRegs.FOPT.bit.ENPIPE = 1;
    // CAUTION
    //Minimum waitstates required for the flash operating
    //at a given CPU rate must be characterized by TI.
    //Refer to the datasheet for the latest information.
    //Set the Paged Waitstate for the Flash
    FlashRegs.FBANKWAIT.bit.PAGEWAIT = 3;

    //Set the Random Waitstate for the Flash
    FlashRegs.FBANKWAIT.bit.RANDWAIT = 3;

    //Set the Waitstate for the OTP
    FlashRegs.FOTPWAIT.bit.OTPWAIT = 5;

    // CAUTION
    //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
    FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
    FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
    //Force a pipeline flush to ensure that the write to
    asm(" RPT #7 || NOP");
    //the last register configured occurs before returning.


	EDIS;	// Disable register access
}

//===========================================================================
// End of file.
//===========================================================================
