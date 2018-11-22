#ifndef __bspinit_h__
#define __bspinit_h__
#include <stdbool.h>
#include <stdint.h>

extern void system_init(void);
extern void uart_init(void);
extern bool serial_out(uint8_t chByte);
extern bool serial_in(uint8_t *pchByte);
extern void breath_led(void);

#define  GPIO_LED1             GPIO_PTH1
#define  GPIO_LED2             GPIO_PTH2
#define  GPIO_KEY1             GPIO_PTA0
#define  GPIO_KEY2             GPIO_PTD0


#define LED1_ON()              do{GPIOB->PCOR|=GPIO_PTH1_MASK;}while(0)
#define LED1_OFF()             do{GPIOB->PSOR|=GPIO_PTH1_MASK;}while(0)
#define LED2_ON()              do{GPIOB->PCOR|=GPIO_PTH2_MASK;}while(0)
#define LED2_OFF()             do{GPIOB->PSOR|=GPIO_PTH2_MASK;}while(0)

#define IS_KEY1_DOWN()          ((GPIOA->PDIR&GPIO_PTA0_MASK)==0)

#define IS_KEY1_UP()            ((GPIOA->PDIR&GPIO_PTA0_MASK)==1)

#define IS_KEY2_DOWN()          ((GPIOA->PDIR&GPIO_PTD0_MASK)==0)

#define IS_KEY2_UP()            ((GPIOA->PDIR&GPIO_PTD0_MASK)==1)


#endif
