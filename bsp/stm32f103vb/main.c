/*
 *  stevenLyan is pleased to support the open source community.
 *
 *  Copyright 2021 stevenLyan (Email:stevenlyan@qq.com)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-18     stevenLyan   first version
 *
 */
#include "misc.c"
#include "stm32f10x_gpio.c"
#include "stm32f10x_it.c"
#include "stm32f10x_rcc.c"
#include "stm32f10x_tim.c"
#include "stm32f10x_usart.c"
#include "system_stm32f10x.c"
#include "periph_init.c"

static uint32_t hal_systick_config(uint32_t tick_rate)
{
    if ((tick_rate == 1000) || (tick_rate == 100)) {
        if (SysTick_Config(72000000 / (tick_rate))) {
            /* assert: Failed!!! Initialize systime failure!!! */
            return 1;
        }
    } else {
        /* assert: Failed!!! only 1000 or 100 is supported!!! */
        return 1;
    }
    return 0;
}


extern void test1(void);
int main(void)
{
    int xxx = 0xffff;
    periph_init();
    hal_systick_config(1000);
    while (xxx--) {
        ;
    }
    test1();
}

/* irq */
#include "microLite_timer.h"
void SysTick_Handler(void)
{
    ml_tick_increase();
}


#include "stdio.h"
/* printf, use MicroLib */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (unsigned char) ch);
    while (!(USART1->SR & USART_FLAG_TXE));
    return (ch);
}

/* keep an empty line */


