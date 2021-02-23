/**
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
 * 2021-02-18     stevenLyan   first version(v0.0.1)
 *
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MICROLITE_TIMER_H
#define __MICROLITE_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

    /**
     *  typedef
     */

    typedef unsigned short     int ml_u16_t;
    typedef unsigned           int ml_u32_t;

    typedef enum {
        ML_TICK_RESET = 0,
        ML_TICK_SET   = !ML_TICK_RESET
    } ml_tickStatus;

    typedef enum {
        ML_TICK_ERROR = 0,
        ML_TICK_SUCCESS = !ML_TICK_ERROR
    } ml_errorStatus;

    typedef ml_u32_t           ml_tick_t;

    /**
     *  periodTimer
     */


#ifndef ML_PERIODTIMER_MAX
#define ML_PERIODTIMER_MAX                       (50)   /*  Maxium number of periodTimer */
#endif

    typedef struct {
        void (*init)(void);
        void (*run)(void);
        ml_tickStatus  (*check)(ml_tick_t period);
        ml_u16_t (*getUsedNum)(void);
        ml_u32_t (*getErrCode)(void);
    } ml_periodTimer_Object_Struct;

    ml_periodTimer_Object_Struct ML_periodTimer_Object_Get(void);

#define MLPeriod (ML_periodTimer_Object_Get())

    /**
     *  shotTimer
     */

    typedef struct {
        ml_tick_t      initTick;
        ml_tick_t      timeoutTick;
        ml_tick_t      offsetTick;
        ml_tickStatus  activeStatus;
    } ml_shotTimer_TypeDef;

    typedef struct {
        ml_errorStatus (*start)(ml_shotTimer_TypeDef *shot_ptr, ml_tick_t initTick);
        ml_errorStatus (*stop)(ml_shotTimer_TypeDef *shot_ptr);
        ml_tickStatus  (*check)(ml_shotTimer_TypeDef *shot_ptr);
        ml_tick_t (*getOffsetTick)(const ml_shotTimer_TypeDef *shot_ptr);
        ml_tickStatus  (*getState)(const ml_shotTimer_TypeDef *shot_ptr);
    } ml_shotTimer_Object_Struct;

    ml_shotTimer_Object_Struct ML_shotTimer_Object_Get(void);

#define MLShot   (ML_shotTimer_Object_Get())

    /**
     *  tick
     */
    ml_tick_t ml_tick_get(void);
    void ml_tick_increase(void);

#ifdef __cplusplus
}
#endif


#endif

/* keep an empty line */

