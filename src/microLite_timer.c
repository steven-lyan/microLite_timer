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


/* Includes ------------------------------------------------------------------*/
#include "microLite_timer.h"


/** @defgroup periodTimer
  * @brief period timer modules
  * @{
  */

/** @defgroup periodTimer_Private_TypesDefinitions
  * @{
  */
	
typedef struct {
    ml_tick_t      initTick;
    ml_tick_t      timeoutTick;
    ml_tickStatus  timeoutFlag;
} ml_periodTimer_TypeDef;

/**
  * @}
  */

/** @defgroup periodTimer_Private_Defines
  * @{
  */

/** Limits and boundaries */
#if (!((0 < ML_PERIODTIMER_MAX) && (ML_PERIODTIMER_MAX < 500)))
#error Wrong defined micro "ML_PERIODTIMER_MAX" (microLite_timer.h).
#endif

/**
  * @}
  */

/** periodTimer error code */
#define ML_TIMER_ERRCODE_PARM_INVALID            ((ml_u32_t)1)
#define ML_TIMER_ERRCODE_TC_OVERFLOW1            ((ml_u32_t)2)

/** @defgroup periodTimer_Private_FunctionPrototypes
  * @{
  */

static ml_u16_t ml_periodTimer_usedNum_get(void);
static ml_u32_t ml_periodTimer_errCode_get(void);
static void ml_periodTimer_init(void);
static void ml_periodTimer_run(void);
static ml_tickStatus ml_periodTimer_check(ml_tick_t init_tick);

/**
  * @}
  */


/** @defgroup periodTimer_Private_Variables
  * @{
  */
static ml_periodTimer_TypeDef  ml_pedTimer[ML_PERIODTIMER_MAX + 1] = {0}; /* " + 1" for debug */
static ml_u16_t   ml_pedTimer_num = 0;
static ml_u32_t   ml_pedTimer_errorCode = 0;

static const ml_periodTimer_Object_Struct  MLpedTimer_Object  = {
    ml_periodTimer_init,
    ml_periodTimer_run,
    ml_periodTimer_check,
    ml_periodTimer_usedNum_get,
    ml_periodTimer_errCode_get
};

/**
  * @}
  */

/** @defgroup periodTimer_Private_Functions
  * @{
  */

/**
 *  this function init periodTimer.
 */
static void ml_periodTimer_init(void)
{
    ml_u16_t i = 0;

    for (i = 0; i < ML_PERIODTIMER_MAX; i++) {
        ml_pedTimer[i].initTick = 0;
        ml_pedTimer[i].timeoutTick = 0;
        ml_pedTimer[i].timeoutFlag = ML_TICK_RESET;
    }
}

/**
 * Attention!!! this function can only be invoked in one place.
 */
static void ml_periodTimer_run(void)
{
    ml_tick_t current_tick;
    ml_u16_t j = 0;

    for (j = 0; j < ML_PERIODTIMER_MAX; j++) {
        if (ml_pedTimer[j].initTick) {
            /* re-get current tick */
            current_tick = ml_tick_get();
            if (((ml_tick_t)(current_tick - ml_pedTimer[j].timeoutTick)) >= (ml_tick_t)ml_pedTimer[j].initTick) {
                ml_pedTimer[j].timeoutTick = current_tick;
                ml_pedTimer[j].timeoutFlag = ML_TICK_SET;
            } else {
                ml_pedTimer[j].timeoutFlag = ML_TICK_RESET;
            }
        } else {
            break;
        }
    }

}

/**
 * This function will check periodTimer structure
 * @param[in]  init_tick 
 * @return the operation status, ML_TICK_SUCCESS on OK, ML_TICK_ERROR on error
 */
static ml_tickStatus ml_periodTimer_check(ml_tick_t init_tick)
{
    ml_tickStatus status = ML_TICK_RESET;

    if ((0 < init_tick) && ((ml_tick_t)init_tick < (ml_tick_t)0xFFFFFFFFUL)) {

        do {
            ml_u16_t k = 0;
            ml_u16_t unfound_cnt = 0;

            for (k = 0; k < ML_PERIODTIMER_MAX; k++) {
                if ((ml_pedTimer[k].initTick == init_tick) || (ml_pedTimer[k].initTick == 0)) {
                    /* check the initTick is new */
                    if (ml_pedTimer[k].initTick == 0) {
                        ml_pedTimer[k].initTick = init_tick;
                        ml_pedTimer[k].timeoutTick = ml_tick_get();
                        ml_pedTimer[k].timeoutFlag = ML_TICK_RESET;
                        ml_pedTimer_num++;
                    }
                    break;
                } else {
                    unfound_cnt++;
                }
            }

            if (unfound_cnt >= ML_PERIODTIMER_MAX) {
                /* assert: error!!! */
                ml_pedTimer_errorCode |= ML_TIMER_ERRCODE_TC_OVERFLOW1;
            } else {
                /* do nothing */
            }

        } while (0);

        do {
            ml_u16_t n = 0;

            for (n = 0; n < ml_pedTimer_num; n++) {
                if ((ml_pedTimer[n].initTick == init_tick) && (ml_pedTimer[n].timeoutFlag == ML_TICK_SET)) {
                    status = ML_TICK_SET;
                    break;
                } else {
                    /* do nothing */
                }
            }
        } while (0);
    } else {
        /* invalid param, assert: error. */
        ml_pedTimer_errorCode |= ML_TIMER_ERRCODE_PARM_INVALID;
    }

    return status;
}

/**
 * this function get periodTimer used number.
 */
static ml_u16_t ml_periodTimer_usedNum_get(void)
{
    return ml_pedTimer_num;
}
/**
 * this function get periodTimer error code.
 */
static ml_u32_t ml_periodTimer_errCode_get(void)
{
    return ml_pedTimer_errorCode;
}
/**
  * @brief Get the periodTimer object
  * @retval MLpedTimer_Object
  */
ml_periodTimer_Object_Struct ML_periodTimer_Object_Get(void)
{
    return MLpedTimer_Object;
}

/**
  * @}
  */

/**
  * @}
  */



/** @defgroup shotTimer
  * @brief shot timer modules
  * @{
  */

/** @defgroup shotTimer_Private_FunctionPrototypes
  * @{
  */


static ml_errorStatus ml_shotTimer_start(ml_shotTimer_TypeDef *shot_ptr, ml_tick_t initTick);
static ml_errorStatus ml_shotTimer_stop(ml_shotTimer_TypeDef *shot_ptr);
static ml_tickStatus ml_shotTimer_check(ml_shotTimer_TypeDef *shot_ptr);
static ml_tick_t ml_shotTimer_offsetTick_get(const ml_shotTimer_TypeDef *shot_ptr);
static ml_tickStatus ml_shotTimer_state_get(const ml_shotTimer_TypeDef *shot_ptr);


/**
  * @}
  */
	
/** @defgroup shotTimer_Private_Variables
  * @{
  */
static const ml_shotTimer_Object_Struct  MLshotTimer_Object  = {
    ml_shotTimer_start,
    ml_shotTimer_stop,
    ml_shotTimer_check,
    ml_shotTimer_offsetTick_get,
    ml_shotTimer_state_get
};

/**
  * @}
  */
/** @defgroup shotTimer_Private_Functions
  * @{
  */

/**
 * This function will start the shotTimer
 * @param[in]  shot_ptr
 * @param[in]  initTick      Initial time value
 * @return the operation status, ML_TICK_SUCCESS on OK, ML_TICK_ERROR on error
 */
static ml_errorStatus ml_shotTimer_start(ml_shotTimer_TypeDef *shot_ptr, ml_tick_t initTick)
{
    if ((0 < initTick) && ((ml_tick_t)initTick < (ml_tick_t)0xFFFFFFFFUL)) {
        /* deactive state */
        if (shot_ptr->activeStatus == ML_TICK_RESET) {
            shot_ptr->activeStatus = ML_TICK_SET;

            shot_ptr->initTick = initTick;
            shot_ptr->timeoutTick = ml_tick_get();
            shot_ptr->offsetTick = 0;

            return ML_TICK_SUCCESS;
        }
    }
    return ML_TICK_ERROR;
}

/**
 * This function will stop the shotTimer
 * @return the operation status, ML_TICK_SUCCESS on OK, ML_TICK_ERROR on error
 */
static ml_errorStatus ml_shotTimer_stop(ml_shotTimer_TypeDef *shot_ptr)
{
    /* deactived state */
    if (shot_ptr->activeStatus == ML_TICK_SET) {
        shot_ptr->activeStatus = ML_TICK_RESET;

        return ML_TICK_SUCCESS;
    }
    return ML_TICK_ERROR;
}

/**
 * This function will check shotTimer structure, if a timeout event happens,
 * the shotTimer stop automaticly.
 */
static ml_tickStatus ml_shotTimer_check(ml_shotTimer_TypeDef *shot_ptr)
{
    ml_tickStatus timeoutFlag = ML_TICK_RESET;
    /* actived state */
    if (shot_ptr->activeStatus) {

        shot_ptr->offsetTick = (ml_tick_t)((ml_tick_get() - shot_ptr->timeoutTick));

        if ((ml_tick_t)(shot_ptr->offsetTick) >= (ml_tick_t)shot_ptr->initTick) {
            shot_ptr->activeStatus = ML_TICK_RESET;
            timeoutFlag = ML_TICK_SET;
        } else {
            /* do nothing */
        }
    } else {
        /* do nothing */
    }

    return timeoutFlag;
}

/**
 * this function get shotTimer offset tick.
 */
static ml_tick_t ml_shotTimer_offsetTick_get(const ml_shotTimer_TypeDef *shot_ptr)
{
    return (ml_tick_t)(shot_ptr->offsetTick);
}
/**
 * this function get shotTimer operation state.
 */
static ml_tickStatus ml_shotTimer_state_get(const ml_shotTimer_TypeDef *shot_ptr)
{
    return (ml_tickStatus)(shot_ptr->activeStatus);
}


/**
  * @brief Get the shotTimer object
  * @retval MLshotTimer_Object
  */
ml_shotTimer_Object_Struct ML_shotTimer_Object_Get(void)
{
    return MLshotTimer_Object;
}


/**
  * @}
  */

/**
  * @}
  */


/** @defgroup tick
  * @brief tick modules
  * @{
  */

/** @defgroup tick_Private_Variables
  * @{
  */
static volatile ml_tick_t ml_tick = 0;
/**
  * @}
  */


/** @defgroup tick_Private_Functions
  * @{
  */

/**
  * @brief Normally, this function is invoked by clock ISR.
  * @retval : None
  */
void ml_tick_increase(void)
{
    ml_tick++;
}

/**
  * @brief This function will return current tick
  * @retval : current tick
  */
ml_tick_t ml_tick_get(void)
{
    ml_tick_t t = 0;

    t = ml_tick;
    while (t != ml_tick) {
        t = ml_tick;
    }

    return t;
}


/**
  * @}
  */

/**
  * @}
  */


/* keep an empty line */
