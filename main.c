#include "include.h"

int main(void)
{
    system_init();

    //! write your name here
    while(!serial_out('S'));
    while(!serial_out('E'));
    while(!serial_out('N'));
    while(!serial_out('G'));
    while(!serial_out('\r'));
    while(!serial_out('\n'));

    while (1)	{
        uint8_t chByte;

        if (IS_KEY1_DOWN()) {
            LED1_ON();
        } else {
            LED1_OFF();
        }


        if (serial_in(&chByte)) {
            serial_out(chByte);
        }
        breath_led();
    }

}




