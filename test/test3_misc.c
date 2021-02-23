
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

static ml_shotTimer_TypeDef test3_timer1 = {0};


void test3(void)
{
    MLPeriod.init();
	
    printf("microLite - Bare metal system, 2021 Copyright by stevenLyan\r\n\r\n");
	
    printf("microLite timer sample, current tick is %d \r\n", ml_tick_get());
    MLShot.start(&test3_timer1, 800);

    while (1) {
        MLPeriod.run();
        /*----------------------------------------------------------------------------*/
        if (MLPeriod.check(1000)) {
            printf("periodTimer is timeout, current tick is %d\r\n", ml_tick_get());
        }
        /*----------------------------------------------------------------------------*/
        if (MLShot.check(&test3_timer1)) {
            printf("timer1 stop(auto), current tick is %d!!!\r\n", ml_tick_get());
        } else {
            /* stop timer1 ahead of time manually */
            if (MLShot.getState(&test3_timer1) == ML_TICK_SET) {
                if (MLShot.getOffsetTick(&test3_timer1) > 500) {
                    MLShot.stop(&test3_timer1);
                    printf("timer1 stop(manual), current tick is %d!!!\r\n", ml_tick_get());
                }
            }
        }
    }
}

/* keep an empty line */
