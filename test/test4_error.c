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

void test4(void)
{
    MLPeriod.init();
    printf("microLite - Bare metal system, 2021 Copyright by stevenLyan\r\n\r\n");
	
    printf("supported the max periodTimer num is %d \r\n", ML_PERIODTIMER_MAX);
    while (1) {
        ml_u32_t index;

        MLPeriod.run();

        for (index = 0; index < ML_PERIODTIMER_MAX; index++) {
            if (MLPeriod.check(index + 1)) {
                ;
            }
            printf("MLPeriod.check(%d) invoked \r\n", index + 1);
            printf("allocated periodTimer num is %d, error code is %d \r\n", MLPeriod.getUsedNum(), MLPeriod.getErrCode());
        }
        printf("\r\n");

        if (MLPeriod.check(1)) {
            ;
        }
        printf("MLPeriod.check(%d) invoked \r\n", 1);
        printf("allocated periodTimer num is %d, error code is %d \r\n", MLPeriod.getUsedNum(), MLPeriod.getErrCode());
        printf("\r\n");

        if (MLPeriod.check(1 + (ML_PERIODTIMER_MAX / 2))) {
            ;
        }
        printf("MLPeriod.check(%d) invoked \r\n", 1 + (ML_PERIODTIMER_MAX / 2));
        printf("allocated periodTimer num is %d, error code is %d \r\n", MLPeriod.getUsedNum(), MLPeriod.getErrCode());
        printf("\r\n");

        if (MLPeriod.check(ML_PERIODTIMER_MAX)) {
            ;
        }
        printf("MLPeriod.check(%d) invoked \r\n", ML_PERIODTIMER_MAX);
        printf("allocated periodTimer num is %d, error code is %d \r\n", MLPeriod.getUsedNum(), MLPeriod.getErrCode());
        printf("\r\n");


        if (MLPeriod.check(ML_PERIODTIMER_MAX + 1)) {
            ;
        }
        printf("MLPeriod.check(%d) invoked \r\n", ML_PERIODTIMER_MAX + 1);
        printf("allocated periodTimer num is %d, error code is %d \r\n", MLPeriod.getUsedNum(), MLPeriod.getErrCode());
        printf("\r\n");


        if (MLPeriod.check((ml_tick_t)0xFFFFFFFF)) {
            ;
        }
        printf("MLPeriod.check(%d) invoked \r\n", (ml_tick_t)0xFFFFFFFF);
        printf("no periodTimer is allocated, error code is %d \r\n", MLPeriod.getErrCode());
        printf("\r\n");

        /* end test */
        printf("end test \r\n");
        while (1);
    }
}


/* keep an empty line */

