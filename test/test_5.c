
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

ml_u32_t cnt1[50] = {0};
ml_u32_t cnt2[50] = {0};

ml_u32_t scanTime = 0;
ml_u32_t maxScan = 0;
void test5(void)
{
    MLPeriod.init();

    while (1) {
        static ml_u32_t store = 0;
			  ml_u32_t i;
			
        scanTime = ml_tick_get() - store;
        store = ml_tick_get();

        if (scanTime > maxScan) {
            maxScan = scanTime;
        }

        MLPeriod.run();
				
				
        for (i = 0; i < 50; i++) {
            if (MLPeriod.check(50 + i)) {
                cnt1[i]++;
            }
        }
        for (i = 0; i < 50; i++) {
            if (MLPeriod.check(60 + i)) {
                cnt2[i]++;
            }
        }

    }
}




/* keep an empty line */
