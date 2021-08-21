/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   2.1.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/


#include "../include/adc0.h"

adc_irq_cb_t ADC0_window_cb = NULL;

/**
 * \brief Initialize ADC interface
 */
int8_t ADC0_Initialize()
{
     
    //PRESC DIV20; 
	ADC0.CTRLB = 0x08;

    //FREERUN disabled; LEFTADJ disabled; SAMPNUM ACC1024; 
	ADC0.CTRLF = 0x0A;

    //TIMEBASE 10; REFSEL 1024MV; 
	ADC0.CTRLC = 0x54;

    //WINSRC RESULT; WINCM NONE; 
	ADC0.CTRLD = 0x00;

    //SAMPDUR 12; 
	ADC0.CTRLE = 0x0C;

    //GAIN 16X; PGABIASSEL 1X; ADCPGASAMPDUR 6CLK; PGAEN enabled; 
	ADC0.PGACTRL = 0x81;

    //DBGRUN disabled; 
	ADC0.DBGCTRL = 0x00;

    //DIFF enabled; MODE BURST_SCALING; START MUXPOS_WRITE; 
	ADC0.COMMAND = 0xD2;

    //TRIGOVR disabled; SAMPOVR disabled; RESOVR disabled; WCMP disabled; SAMPRDY disabled; RESRDY disabled; 
	ADC0.INTCTRL = 0x00;

    //VIA PGA; MUXPOS AIN4; 
	ADC0.MUXPOS = 0x44;

    //VIA PGA; MUXNEG AIN6; 
	ADC0.MUXNEG = 0x46;

    // Window comparator high threshold 
	ADC0.WINHT = 0x00;

    // Window comparator low threshold 
	ADC0.WINLT = 0x00;

    //RUNSTDBY disabled; LOWLAT enabled; ENABLE enabled; 
	ADC0.CTRLA = 0x21;


	return 0;
}

void ADC0_Enable()
{
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

void ADC0_Disable()
{
	ADC0.CTRLA &= ~ADC_ENABLE_bm;
}

void ADC0_SetWindowHigh(adc_result_t high)
{
	ADC0.WINHT = high;
}

void ADC0_SetWindowLow(adc_result_t low)
{
	ADC0.WINLT = low;
}

void ADC0_SetWindowMode(adc0_window_mode_t mode)
{
	ADC0.CTRLD = mode;
}

void ADC0_StartConversion(adc_0_channel_t channel)
{
	ADC0.MUXPOS  = channel;
	ADC0.COMMAND |= ADC_START_IMMEDIATE_gc;
}

void ADC0_StartDiffConversion(adc_0_channel_t channel, adc_0_muxneg_channel_t channel1)
{
	ADC0.MUXPOS  = channel;
	ADC0.MUXNEG  = channel1;
        ADC0.COMMAND |=  ADC_START_IMMEDIATE_gc | ADC_DIFF_bm;
}

void ADC0_StopConversion()
{
	ADC0.COMMAND &= ~ADC_START_gm;
}

bool ADC0_IsConversionDone()
{
	return (ADC0.INTFLAGS & ADC_RESRDY_bm);
}

adc_result_t ADC0_GetConversionResult(void)
{
	return (ADC0.RESULT);
}

uint16_t ADC0_GetConversionSample(void)
{
	return (ADC0.SAMPLE);
}

bool ADC0_GetWindowResult(void)
{
	bool temp     = (ADC0.INTFLAGS & ADC_WCMP_bm);
	ADC0.INTFLAGS = ADC_WCMP_bm; // Clear intflag if set
	return temp;
}

adc_result_t ADC0_GetConversion(bool viaPGA, adc_0_channel_t channel)
{
	adc_result_t res;

        ADC0_StartConversion(channel|(viaPGA<<6));
	while (!ADC0_IsConversionDone());
	res = ADC0_GetConversionResult();
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	return res;
}

diff_adc_result_t ADC0_GetDiffConversion(bool viaPGA, adc_0_channel_t channel, adc_0_muxneg_channel_t channel1)
{
	diff_adc_result_t res;
        ADC0.COMMAND |=  ADC_START_IMMEDIATE_gc | ADC_DIFF_bm;
        ADC0_StartDiffConversion(channel, channel1|(viaPGA<<6));
	while (!ADC0_IsConversionDone());
	res = ADC0_GetConversionResult();
	ADC0.INTFLAGS |= ADC_RESRDY_bm;
	return res;
}

uint8_t ADC0_GetResolution()
{
	return (ADC0.COMMAND & ADC_MODE_SINGLE_8BIT_gc) ? 8 : 12;
}

void ADC0_RegisterWindowCallback(adc_irq_cb_t f)
{
	ADC0_window_cb = f;
}

ISR(ADC0_SAMPRDY_vect)
{
        /* Insert your ADC Sample ready interrupt handling code here */

	// Clear the interrupt flag
	ADC0.INTFLAGS = ADC_SAMPRDY_bm;
}

ISR(ADC0_RESRDY_vect)
{
    /* Insert your ADC result ready interrupt handling code here */

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_RESRDY_bm;
}

ISR(ADC0_ERROR_vect)
{
    /* Insert your ADC Error interrupt handling code here */

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_TRIGOVR_bm;

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_SAMPOVR_bm;

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_RESOVR_bm;


}

/* PGA API's */
void ADC0_PGA_enable()
{
	ADC0.PGACTRL |= ADC_PGAEN_bm;
}

void ADC0_PGA_disable()
{
	ADC0.PGACTRL &= ~ADC_PGAEN_bm;
}

void ADC0_PGA_Gain_Setting(ADC_GAIN_t value)
{
	ADC0.PGACTRL = (ADC0.PGACTRL & ~ADC_GAIN_gm) | value;
}

void ADC0_PGA_Bias_Select(ADC_PGABIASSEL_t value)
{
	ADC0.PGACTRL = (ADC0.PGACTRL & ~ADC_PGABIASSEL_gm) | value;
}

void ADC0_PGA_Sample_Duration(ADC_ADCPGASAMPDUR_t value)
{
	ADC0.PGACTRL = (ADC0.PGACTRL & ~ADC_ADCPGASAMPDUR_gm) | value;
}

