
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

void test1(void)
{
    MLPeriod.init();

    printf("microLite - Bare metal system, 2021 Copyright by stevenLyan\r\n\r\n");
		
    printf("microLite timer sample, current tick is %d \r\n", ml_tick_get());
    while (1) {
        MLPeriod.run();

        if (MLPeriod.check(1000)) {
            printf("task1, current tick is %d\r\n", ml_tick_get());
        }
        if (MLPeriod.check(500)) {
            printf("task2, current tick is %d\r\n", ml_tick_get());
        }
        if (MLPeriod.check(500)) {
            printf("task3, current tick is %d\r\n", ml_tick_get());
        }
        if (MLPeriod.check(800)) {
            printf("task4, current tick is %d\r\n", ml_tick_get());
        }
    }
}

/* keep an empty line */
