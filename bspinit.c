#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"
#include "uart.h"
#include "sysinit.h"
#include "bspinit.h"

#define  UART_BITRATE_9600     9600
#define  MAX_WITH              1000

typedef struct
{
    uint32_t wTick;
    uint32_t wPeriod;
    uint32_t wDuty;
    int32_t  nOffset;
    uint8_t  chTimeflag;

} timer_t;

static timer_t  *s_timer;

void GpioInit(void);
void uart_init(void);
void timer_init(void);

void
system_init(void)
{
    sysinit();
    GpioInit();
    uart_init();
    timer_init();
}

void
GpioInit(void)
{
    GPIO_PinInit(GPIO_LED1,GPIO_PinOutput);
    GPIO_PinInit(GPIO_LED2,GPIO_PinOutput);
    LED1_OFF();
    LED2_OFF();
    GPIO_PinInit(GPIO_KEY1,GPIO_PinInput_InternalPullup);
    GPIO_PinInit(GPIO_KEY2,GPIO_PinInput_InternalPullup);
}


void
uart_init(void)
{
    UART_ConfigType sConfig;
    sConfig.u32SysClkHz = BUS_CLK_HZ;
    sConfig.u32Baudrate = UART_BITRATE_9600;
    UART_Init(UART1,&sConfig);
}

bool
serial_out(uint8_t chByte)
{
    if((UART1->S1 & UART_S1_TDRE_MASK)) {
        UART1->D=chByte;
        return true;
    }
    return false;
}

bool
serial_in(uint8_t *pchByte)
{
    if(pchByte!=NULL) {
        if((UART1->S1 & UART_S1_RDRF_MASK)) {
            *pchByte=UART1->D;
            return true;
        }
    }
    return false;
}


void
timer_init(void)
{
	s_timer->wTick=0;
	s_timer->wPeriod=650;
	s_timer->wDuty=400;
	s_timer->nOffset=1;
	s_timer->chTimeflag=0;
}


void
breath_led(void)
{
    s_timer->wTick++;
    if(s_timer->wTick>=s_timer->wPeriod) {
        s_timer->wTick=0;
        s_timer->chTimeflag=1;
    }
    if(s_timer->wTick<s_timer->wDuty) {
        LED2_ON();
    } else {
        LED2_OFF();
    }
    if(s_timer->chTimeflag) {
        s_timer->chTimeflag=0;
        s_timer->wDuty=s_timer->wDuty+s_timer->nOffset;
        if(s_timer->wDuty>=s_timer->wPeriod||s_timer->wDuty<=0) {
            s_timer->nOffset=-s_timer->nOffset;
        }
    }
}

