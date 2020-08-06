/***************************************************************************//**
 * @file
 * @brief This file contains the basic RTOS API layer. This API is used by
 * the Ember stack and HAL code and must be implemented for the specific RTOS
 * for things to work properly.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef __RTOS_SETUP_H__
#define __RTOS_SETUP_H__

#include PLATFORM_HEADER

// Pull in definitions of WakeEvents and WakeMask
#include "hal/micro/micro-common.h"

// Timeout in milliseconds that will cause us to block indefinitely
#define RTOS_MAX_DELAY (0xFFFFFFFF)

///////////////////////////////////////////////////////////////////////////////
// RTOS API Types
///////////////////////////////////////////////////////////////////////////////

typedef void * RtosQueue_t;
typedef void * RtosMutex_t;
typedef void * RtosSemaphore_t;
typedef void * RtosEventGroup_t;
typedef uint16_t RtosEventBits_t;
typedef void * RtosTask_t;
typedef void (*RtosTaskFunction_t)(void *);
typedef uint32_t RtosTick_t;

///////////////////////////////////////////////////////////////////////////////
// Basic RTOS API Layer (implemented in rtos-api-silabs.c)
///////////////////////////////////////////////////////////////////////////////

// -- Tasks --

/*
 * Create an RTOS task which will run when the scheduler is started.
 * @param taskFunction The main function to run for this task
 * @param name The user friendly name for this task
 * @param stackSize The number of words the stack should be able to hold
 * @param taskPriority The priority for this task to run at
 * @param taskHandle If provided, a handle for this task will be put in this
 * variable
 * @return Returns true if the task was created and false if it failed to be
 * created for some reason.
 */
bool rtosTaskCreate(RtosTaskFunction_t taskFunction,
                    const char * const name,
                    uint16_t stackSize,
                    void *taskParameters,
                    uint8_t taskPriority,
                    RtosTask_t *taskHandle);

/*
 * Suspend the specified task so that it is no longer scheduled.
 * @param task The task to suspend.
 */
void rtosTaskSuspend(RtosTask_t task);

/*
 * Resume the specified task.
 * @param task The task to resume.
 */
void rtosTaskResume(RtosTask_t task);

/*
 * Delay the currently running task by the specified number of milliseconds.
 * @param millisecs The number of milliseconds to delay for. Will only
 * delay after the rtosStartScheduler() call.
 */
void rtosTaskDelay(uint32_t millisecs);

/*
 * Get the ID of the currently running task.
 * @return The ID of the currently running task
 */
RtosTask_t rtosGetCurrentTask(void);

// -- Scheduler --

/*
 * This function starts the RTOS scheduler. It should never return and is
 * called once to start the RTOS.
 */
void rtosStartScheduler(void);

/*
 * This function suspends the RTOS scheduler. It is used by code that needs
 * to run without interruption.
 */
void rtosSuspendScheduler(void);

/*
 * This function resumes the RTOS scheduler. It is used to get things going
 * again after a suspend call.
 */
void rtosResumeScheduler(void);

/*
 * This function will enter an RTOS compatible critical section. It will
 * prevent other threads or interrupts from firing until a corresponding
 * call to rtosExitCritical(). Calls to these APIs are reference counted
 * and nestable.
 */
uint8_t rtosEnterCritical(void);

/*
 * This function will exit an RTOS critical section and re-enable other
 * threads and interrupts if all critical sections have been exited.
 */
uint8_t rtosExitCritical(void);

/*
 * Get the current system time in RTOS tick units.
 * @return The system time in RTOS tick units.
 */
RtosTick_t rtosGetTimeTicks(void);

/*
 * Convert the time from RTOS ticks to milliseconds.
 * @param ticks The time in RTOS ticks.
 * @return The nearest time in milliseconds.
 */
uint32_t rtosTicksToMilliseconds(RtosTick_t ticks);

/*
 * Convert the time from milliseconds to RTOS ticks.
 * @param millisecs The time in milliseconds.
 # @return The nearest time in RTOS ticks.
 */
RtosTick_t rtosMillisecondsToTicks(uint32_t millisecs);

/*
 * Convert the time from milliseconds to RTOS delay ticks.
 * @param millisecs The time in milliseconds.
 # @return The nearest time in RTOS ticks that can be used as a delay.
 */
RtosTick_t rtosMillisecondsToDelay(uint32_t millisecs);

// -- Queues --

/*
 * Create a queue and return the reference to it.
 * @param queueLength The number of items that can be held in the queue
 * @param queueItemSize The maximum size of each item in the queue
 * @param queueName An optional pointer to the name of the queue. This can be
 * used for debugging purposes, but if it is left as NULL it will be ignored.
 * @return A reference to the queue or 0 if the queue could not be created.
 */
RtosQueue_t rtosQueueCreate(uint32_t queueLength, uint32_t queueItemSize, const char* queueName);

/*
 * Return the number of items available to be read from the queue.
 * @param queue The ID of the queue to check.
 * @return The number of items waiting to be read from the queue.
 */
uint32_t rtosQueueCount(RtosQueue_t queue);

/*
 * Read one message out of the queue and into the data buffer pointed to by
 * data. You must make sure that this buffer has enough space for a full
 * queue item as specified at creation time.
 * @param queue The ID of the queue to check.
 * @param data A pointer to the data buffer to copy the item into.
 * @param millisecs The time to wait for an item to be available in milliseconds.
 * If this is 0 the function will not wait at all and if it is RTOS_MAX_DELAY
 * it will wait indefinitely.
 * @return Returns true if a message was found in time and false otherwise.
 */
bool rtosQueueReceive(RtosQueue_t queue, void *data, uint32_t millisecs);

/*
 * The same as rtosQueueReceive except the message is left in the queue
 * after we return.
 * @param queue The ID of the queue to check.
 * @param data A pointer to the data buffer to copy the item into.
 * @param millisecs The time to wait for an item to be available in milliseconds.
 * If this is 0 the function will not wait at all and if it is RTOS_MAX_DELAY
 * it will wait indefinitely.
 * @return Returns true if a message was found in time and false otherwise.
 */
bool rtosQueuePeek(RtosQueue_t queue, void *data, uint32_t millisecs);

/*
 * Place a new data item into the queue to be sent.
 * @param queue The ID of the queue.
 * @param data A pointer to the data buffer to copy into the queue.
 * @param millisecs The time to wait for space to become available in
 * milliseconds. If this is 0 the function will not wait at all and if it is
 * RTOS_MAX_DELAY it will wait indefinitely.
 * @return Returns true if the item was placed in the queue and false otherwise.
 */
bool rtosQueueSend(RtosQueue_t queue, const void* data, uint32_t millisecs);

/*
 * Delete the queue object and return any memory allocated to it.
 * @param queue The queue to be deleted.
 */
void rtosQueueDelete(RtosQueue_t queue);

// -- Mutex/Semaphore --

/*
 * Create a mutex.
 * @return The handle to an initialized mutex.
 */
RtosMutex_t rtosMutexCreate(void);

/*
 * Attempt to take this mutex if it becomes available within the timeout.
 * @param mutex The ID of the mutex.
 * @param millisecs The time to wait for space to become available in
 * milliseconds. If this is 0 the function will not wait at all and if it is
 * RTOS_MAX_DELAY it will wait indefinitely.
 * @return Returns true if the mutex is successfully taken and false if the
 * timeout occurred.
 */
bool rtosMutexTake(RtosMutex_t mutex, uint32_t millisecs);

/*
 * Return the mutex.
 * @param mutex The ID of the mutex.
 * @return Returns true if the mutex was returned successfully and false if
 * an error occurred. A return value of false indicates that you probably
 * did not successfully take the mutex.
 */
bool rtosMutexGive(RtosMutex_t mutex);

/*
 * Delete the mutex object and return any memory used by it.
 * @param mutex The mutex to delete.
 */
void rtosMutexDelete(RtosMutex_t semaphore);

/*
 * Create a binary semaphore. The semaphore returned is in a state where
 * it can be taken one time.
 * @return The handle to an initialized semaphore or NULL if it could not
 * be created.
 */
RtosSemaphore_t rtosSemaphoreCreateBinary(void);

/*
 * Create a counting semaphore.
 * @return The handle to an initialized semaphore or NULL if it could not
 * be created.
 */
RtosSemaphore_t rtosSemaphoreCreateCounting(uint32_t maxCount, uint32_t initialCount);

/*
 * Attempt to take this semaphore if it becomes available within the timeout.
 * @param semaphore The ID of the semaphore.
 * @param millisecs The time to wait for space to become available in
 * milliseconds. If this is 0 the function will not wait at all and if it is
 * RTOS_MAX_DELAY it will wait indefinitely.
 * @return Returns true if the semaphore is successfully taken and false if the
 * timeout occurred.
 */
bool rtosSemaphoreTake(RtosSemaphore_t semaphore, uint32_t millisecs);

/*
 * Return the semaphore.
 * @param semaphore The ID of the semaphore.
 * @return Returns true if the semaphore was returned successfully and false if
 * an error occurred. A return value of false indicates that you probably
 * did not successfully take the semaphore.
 */
bool rtosSemaphoreGive(RtosSemaphore_t semaphore);

/*
 * Delete the semaphore object and return any memory used by it.
 * @param semaphore The semaphore to delete.
 */
void rtosSemaphoreDelete(RtosSemaphore_t semaphore);

// -- Event Groups --

/*
 * Create an event group. This is a collection of signals that can be set,
 * cleared, and waited on. It's useful for task synchronization.
 * @return The ID of the event group created.
 */
RtosEventGroup_t rtosEventGroupCreate(void);

/*
 * Clear the specified bits in the event group.
 * @param event The ID of the event group.
 * @param bits A mask of the bits to clear.
 * @return The value of the event group bits at the time this function returns.
 */
RtosEventBits_t rtosEventGroupClearBits(RtosEventGroup_t event, RtosEventBits_t bits);

/*
 * Set the event group bits high to signal anyone waiting on this event that it
 * has occurred. This function is safe to call from within an ISR context.
 * @param event The ID of the event group.
 * @param bits The bit or bits to set high in this event group.
 * @return The state of the event bits after this function returns. Note that
 * this doesn't mean the bits you just set will be high since they may be
 * processed immediately.
 */
RtosEventBits_t rtosEventGroupSetBits(RtosEventGroup_t event, RtosEventBits_t bits);

/*
 * Wait for any of the specified event bits to be set or the timeout. When one
 * or more of the bits are set this function will clear them and return.
 * @param event The ID of the event group.
 * @param bits The set of bits to wait on. This function will wait for any one
 * bit to be set and not all bits to be set.
 * @param millisecs The time to wait for space to become available in
 * milliseconds. If this is 0 the function will not wait at all and if it is
 * RTOS_MAX_DELAY it will wait indefinitely.
 */
RtosEventBits_t rtosEventGroupWaitBits(RtosEventGroup_t event, RtosEventBits_t bits, uint32_t millisecs);

///////////////////////////////////////////////////////////////////////////////
// SiLabs RTOS API Layer (implemented in rtos-integration.c)
///////////////////////////////////////////////////////////////////////////////

/*
 * Initialization function for the RTOS API layer. This is used to initialize
 * globals used by the API layer and must be called before starting the RTOS.
 */
void rtosApiInit(void);

/*
 * This function will register the address of a global to be with the RTOS.
 * The value stored in this address will be cached by the RTOS and swapped on
 * every task switch. This is like a simple version of thread local storage.
 * @param address The address to register in the global cache
 * @return Returns 0 on success and 1 on failure.
 */
int rtosRegisterSharedGlobal(void** address);

/*
 * This function must prevent the RTOS from entering deep sleep. It should
 * be paired with a corresponding rtosUnblockDeepSleep() call to allow deep
 * sleep again. This should also be able to track nested requests to block
 * deep sleep and not unblock until every unblock routine has been called.
 */
void rtosBlockDeepSleep(void);

/*
 * This function must be paired with rtosBlockDeepSleep() to allow deep sleep
 * to work again. This routine is thread safe, but you should not call it more
 * times than rtosBlockDeepSleep() was called since that will have an undefined
 * behavior.
 */
void rtosUnblockDeepSleep(void);

/*
 * This function gets the state of the RTOS deep sleep count.
 */
uint32_t rtosGetDeepSleepBlockCount(void);

/*
 * This function registers a callback function with the RTOS sleep manager to
 * be called when we wakeup from any deep sleep event. NOTE: Any callbacks here
 * may be called within the context of the RTOS scheduler so they cannot block.
 * @param callback The function to call which takes a WakeEvents type which
 * matches the value that halGetWakeInfo() would return.
 * @return Returns true if the callback was added and false if there was not
 * enough space for it.
 */
bool rtosAddDeepSleepWakeCallback(void (*callback)(WakeEvents));

/*
 * Configure the GPIO wake sources when coming out of deep sleep. By default
 * these will come from the board header file, but this function can be used
 * to reconfigure the wake sources at runtime.
 * @param gpioWakeBitMask A bit mask for GPIOs that should cause a wake from
 * deepsleep. This is the same as the second parameter to halSleepWithOptions()
 */
void rtosSetSleepWakeSource(WakeMask gpioWakeBitMask);

#endif // __RTOS_SETUP_H__
