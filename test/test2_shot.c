
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

#include "microLite_timer.h"
#include "stdio.h"

static ml_shotTimer_TypeDef test2_timer1 = {0};
static ml_shotTimer_TypeDef test2_timer2 = {0};
static ml_shotTimer_TypeDef test2_timer3 = {0};

void test2(void)
{	
    printf("microLite - Bare metal system, 2021 Copyright by stevenLyan\r\n\r\n");
	
    printf("microLite timer sample, current tick is %d \r\n", ml_tick_get());
    MLShot.start(&test2_timer1, 800);
    MLShot.start(&test2_timer2, 500);

    while (1) {
        /*----------------------------------------------------------------------------*/
        /* Schedules the specified task for execution after the specified delay.
              [the specified delay]:  [timer1]800 ticks */
        if (MLShot.check(&test2_timer1)) {
            printf("timer1 stop(auto), current tick is %d!!!\r\n", ml_tick_get());
        }
        /*----------------------------------------------------------------------------*/
        /* Schedules the specified task for repeated fixed-delay execution, beginning
        		     after the specified delay.
        		        [the specified delay]:  [timer2]500 ticks
        				[repeated fixed-delay]: [timer3]1000 ticks
        		*/
        if (MLShot.check(&test2_timer2)) {
            MLShot.start(&test2_timer3, 1000);
            printf("timer2 stop(auto) and timer3 start, current tick is %d!!!\r\n", ml_tick_get());
        }
        if (MLShot.check(&test2_timer3)) {
            MLShot.start(&test2_timer3, 1000);
            printf("timer3 timeout, current tick is %d\r\n", ml_tick_get());
        }

    }
}

/* keep an empty line */
