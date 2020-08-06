/***************************************************************************//**
 * @file
 * @brief SLEEPTIMER API definition.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup platform_service
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SLEEPTIMER
 * @{
 * @brief Low frequency timer utilities.
 * Utilities (timer, delays and time keeping).
 ******************************************************************************/

#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sl_sleeptimer_config.h"
#include "em_device.h"
#include "sl_status.h"

#define SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG 0x01

#define SLEEPTIMER_ENUM(name) typedef uint8_t name; enum name##_enum

/// Timestamp, wall clock time in seconds.
typedef uint32_t sl_sleeptimer_timestamp_t;

/// Time zone offset from UTC(second).
typedef int32_t sl_sleeptimer_time_zone_offset_t;

// Forward declaration
typedef struct sl_sleeptimer_timer_handle sl_sleeptimer_timer_handle_t;

/***************************************************************************//**
 * Typedef for the user supplied callback function which is called when
 * a timer expires.
 *
 * @param handle The timer handle.
 *
 * @param data An extra parameter for the user application.
 ******************************************************************************/
typedef void (*sl_sleeptimer_timer_callback_t)(sl_sleeptimer_timer_handle_t *handle, void *data);

struct sl_sleeptimer_timer_handle {
  void *callback_data;                     ///< User data to pass to callback function.
  uint8_t priority;                        ///< Priority of timer.
  uint16_t option_flags;                   ///< Option flags.
  sl_sleeptimer_timer_handle_t *next;      ///< Pointer to next element in list.
  sl_sleeptimer_timer_callback_t callback; ///< Function to call when timer expires.
  uint32_t timeout_periodic;               ///< Periodic timeout.
  uint32_t delta;                          ///< Delay relative to previous element in list.
};

/// @brief Month enum.
SLEEPTIMER_ENUM(sl_sleeptimer_month_t) {
  MONTH_JANUARY = 0,
  MONTH_FEBRUARY = 1,
  MONTH_MARCH   = 2,
  MONTH_APRIL = 3,
  MONTH_MAY = 4,
  MONTH_JUNE = 5,
  MONTH_JULY = 6,
  MONTH_AUGUST = 7,
  MONTH_SEPTEMBER = 8,
  MONTH_OCTOBER = 9,
  MONTH_NOVEMBER = 10,
  MONTH_DECEMBER = 11,
};

/// @brief Week Day enum.
SLEEPTIMER_ENUM(sl_sleeptimer_weekDay_t) {
  DAY_SUNDAY = 0,
  DAY_MONDAY = 1,
  DAY_TUESDAY = 2,
  DAY_WEDNESDAY = 3,
  DAY_THURSDAY = 4,
  DAY_FRIDAY = 5,
  DAY_SATURDAY = 6,
};

/// @brief Time and Date structure.
typedef  struct  time_date {
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t month_day;
  sl_sleeptimer_month_t month;
  uint16_t year;                              ///< Current year, based on a 1900 Epoch.
  sl_sleeptimer_weekDay_t day_of_week;
  uint16_t day_of_year;
  sl_sleeptimer_time_zone_offset_t time_zone; ///< Offset, in seconds, from UTC
} sl_sleeptimer_date_t;

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * Initializes the Sleeptimer.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_init(void);

/***************************************************************************//**
 * Starts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_start_timer(sl_sleeptimer_timer_handle_t *handle,
                                      uint32_t timeout,
                                      sl_sleeptimer_timer_callback_t callback,
                                      void *callback_data,
                                      uint8_t priority,
                                      uint16_t option_flags);

/***************************************************************************//**
 * Restarts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_restart_timer(sl_sleeptimer_timer_handle_t *handle,
                                        uint32_t timeout,
                                        sl_sleeptimer_timer_callback_t callback,
                                        void *callback_data,
                                        uint8_t priority,
                                        uint16_t option_flags);

/***************************************************************************//**
 * Starts a 32 bits periodic timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer periodic timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_start_periodic_timer(sl_sleeptimer_timer_handle_t *handle,
                                               uint32_t timeout,
                                               sl_sleeptimer_timer_callback_t callback,
                                               void *callback_data,
                                               uint8_t priority,
                                               uint16_t option_flags);

/***************************************************************************//**
 * Restarts a 32 bits periodic timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer periodic timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_restart_periodic_timer(sl_sleeptimer_timer_handle_t *handle,
                                                 uint32_t timeout,
                                                 sl_sleeptimer_timer_callback_t callback,
                                                 void *callback_data,
                                                 uint8_t priority,
                                                 uint16_t option_flags);

/***************************************************************************//**
 * Stops a timer.
 *
 * @param handle Pointer to handle to timer.
 *
 * @return
 ******************************************************************************/
sl_status_t sl_sleeptimer_stop_timer(sl_sleeptimer_timer_handle_t *handle);

/***************************************************************************//**
 * Gets the status of a timer.
 *
 * @param handle Pointer to handle to timer.
 * @param running Pointer to the status of the timer.
 *
 * @note A non periodic timer is considered not running during its callback.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_is_timer_running(sl_sleeptimer_timer_handle_t *handle,
                                           bool *running);

/***************************************************************************//**
 * Gets remaining time until timer expires.
 *
 * @param handle Pointer to handle to timer.
 * @param time Time left in timer ticks.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_get_timer_time_remaining(sl_sleeptimer_timer_handle_t *handle,
                                                   uint32_t *time);

/**************************************************************************//**
 * Gets the time remaining until the first timer with the matching set of flags
 * expires.
 *
 * @param option_flags Set of flags to match.
 *
 * @param time_remaining Time left in timer ticks.
 *
 * @return 0 if successful. Error code otherwise.
 *****************************************************************************/
sl_status_t sl_sleeptimer_get_remaining_time_of_first_timer(uint16_t option_flags,
                                                            uint32_t *time_remaining);

/***************************************************************************//**
 * Gets current 32 bits global tick count.
 *
 * @return Current tick count.
 ******************************************************************************/
uint32_t sl_sleeptimer_get_tick_count(void);

/***************************************************************************//**
 * Gets current 64 bits global tick count.
 *
 * @return Current tick count.
 ******************************************************************************/
uint64_t sl_sleeptimer_get_tick_count64(void);

/***************************************************************************//**
 * Get timer frequency.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
uint32_t sl_sleeptimer_get_timer_frequency(void);

#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
/***************************************************************************//**
 * Converts a Unix timestamp into a date.
 *
 * @param time Unix timestamp to convert.
 * @param time_zone Offset from UTC in second.
 * @param date Pointer to converted date.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_time_to_date(sl_sleeptimer_timestamp_t time,
                                               sl_sleeptimer_time_zone_offset_t time_zone,
                                               sl_sleeptimer_date_t *date);

/***************************************************************************//**
 * Converts a date into a Unix timestamp.
 *
 * @param date Pointer to date to convert.
 * @param time Pointer to converted Unix timestamp.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note Dates are based on the Unix time representation.
 *       Range of dates supported :
 *          - January 1, 1970, 00:00:00 to January 19, 2038, 03:14:00
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_date_to_time(sl_sleeptimer_date_t *date,
                                               sl_sleeptimer_timestamp_t *time);

/***************************************************************************//**
 * Convert date to string.
 *
 * @param str Output string.
 * @param size Size of the input array.
 * @param format The format specification character.
 * @param date Pointer to date structure.
 *
 * @return 0 if error. Number of character in the output string.
 *
 * @note Refer strftime() from UNIX.
 *       http://man7.org/linux/man-pages/man3/strftime.3.html
 ******************************************************************************/
uint32_t sl_sleeptimer_convert_date_to_str(char *str,
                                           size_t size,
                                           const uint8_t *format,
                                           sl_sleeptimer_date_t *date);

/***************************************************************************//**
 * Sets time zone offset.
 *
 * @param  offset  Time zone offset, in seconds.
 ******************************************************************************/
void sl_sleeptimer_set_tz(sl_sleeptimer_time_zone_offset_t offset);

/***************************************************************************//**
 * Gets time zone offset.
 *
 * @return Time zone offset, in seconds.
 ******************************************************************************/
sl_sleeptimer_time_zone_offset_t sl_sleeptimer_get_tz(void);

/***************************************************************************//**
 * Retrieves current time.
 *
 * @return Current timestamps in Unix format.
 ******************************************************************************/
sl_sleeptimer_timestamp_t sl_sleeptimer_get_time(void);

/***************************************************************************//**
 * Sets current time.
 *
 * @param time Time to set.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_set_time(sl_sleeptimer_timestamp_t time);

/***************************************************************************//**
 * Gets current date.
 *
 * @param date Pointer to a sl_sleeptimer_date_t structure.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_get_datetime(sl_sleeptimer_date_t *date);

/***************************************************************************//**
 * Sets current time, in date format.
 *
 * @param date Pointer to current date.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_set_datetime(sl_sleeptimer_date_t *date);

/***************************************************************************//**
 * Builds a date time structure based on the provided parameters.
 *
 * @param date Pointer to the structure to be populated.
 * @param year Current year. May be provided based on a 0 Epoch or a 1900 Epoch.
 * @param month Months since January. Expected value: 0-11.
 * @param month_day Day of the month. Expected value: 1-31.
 * @param hour Hours since midnight. Expected value: 0-23.
 * @param min Minutes after the hour. Expected value: 0-59.
 * @param sec Seconds after the minute. Expected value: 0-59.
 * @param tzOffset Offset, in seconds, from UTC.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_build_datetime(sl_sleeptimer_date_t *date,
                                         uint16_t year,
                                         sl_sleeptimer_month_t month,
                                         uint8_t month_day,
                                         uint8_t hour,
                                         uint8_t min,
                                         uint8_t sec,
                                         sl_sleeptimer_time_zone_offset_t tzOffset);

/***************************************************************************//**
 * Converts Unix timestamp into NTP timestamp.
 *
 * @param time Unix timestamp.
 * @param ntp_time Pointer to NTP Timestamp.
 *
 * @note Unix timestamp range supported : 0x0 to 0x7C55 817F
 *       ie. January 1, 1970, 00:00:00 to February 07, 2036, 06:28:15
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_unix_time_to_ntp(sl_sleeptimer_timestamp_t time,
                                                   uint32_t *ntp_time);

/***************************************************************************//**
 * Converts NTP timestamp into Unix timestamp.
 *
 * @param ntp_time NTP Timestamp.
 * @param time Pointer to Unix timestamp.
 *
 * @note NTP timestamp range supported : 0x83AA 7E80 to 0xFFFF FFFF
 *       ie. January 1, 1970, 00:00:00 to February 07, 2036, 06:28:15
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_ntp_time_to_unix(uint32_t ntp_time,
                                                   sl_sleeptimer_timestamp_t *time);

/***************************************************************************//**
 * Converts Unix timestamp into Zigbee timestamp.
 *
 * @param time Unix timestamp.
 *
 * @param zigbee_time Pointer to NTP Timestamp.
 *
 * @note Unix timestamp range supported : 0x386D 4380 to 0x7FFF FFFF
 *       ie. January 1, 2000, 00:00:0 to January 19, 2038, 03:14:00
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_unix_time_to_zigbee(sl_sleeptimer_timestamp_t time,
                                                      uint32_t *zigbee_time);

/***************************************************************************//**
 * Converts Zigbee timestamp into Unix timestamp.
 *
 * @param zigbee_time NTP Timestamp.
 * @param time Pointer to Unix timestamp.
 *
 * @note ZIGBEE timestamp range supported : 0x0 to 0x4792 BC7F
 *        ie. January 1, 2000, 00:00:00 to January 19, 2038, 03:14:00
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_zigbee_time_to_unix(uint32_t zigbee_time,
                                                      sl_sleeptimer_timestamp_t *time);

/***************************************************************************//**
 * Calculates offset for time zone after UTC-0.
 *
 * @param hours Number of hours from UTC-0.
 * @param minutes Number of minutes from UTC-0.
 *
 * @return The time zone offset in seconds.
 ******************************************************************************/
__STATIC_INLINE sl_sleeptimer_time_zone_offset_t sl_sleeptimer_set_tz_ahead_utc(uint8_t hours,
                                                                                uint8_t minutes)
{
  return ((hours * 3600u) + (minutes * 60u));
}

/***************************************************************************//**
 * Calculates offset for time zone before UTC-0.
 *
 * @param hours Number of hours to UTC-0.
 * @param minutes Number of minutes to UTC-0.
 *
 * @return The time zone offset in seconds.
 ******************************************************************************/
__STATIC_INLINE sl_sleeptimer_time_zone_offset_t sl_sleeptimer_set_tz_behind_utc(uint8_t hours,
                                                                                 uint8_t minutes)
{
  return -((hours * 3600u) + (minutes * 60u));
}
#endif

/***************************************************************************//**
 * Active delay.
 *
 * @param time_ms Delay duration in milliseconds.
 ******************************************************************************/
void sl_sleeptimer_delay_millisecond(uint16_t time_ms);

/***************************************************************************//**
 * Converts milliseconds in ticks.
 *
 * @param time_ms Number of milliseconds.
 *
 * @return Corresponding ticks number.
 *
 * @note The result is "rounded" to the superior tick number.
 *       This function is light and cannot fail so it should be privilegied to
 *       perform a millisecond to tick conversion.
 ******************************************************************************/
uint32_t sl_sleeptimer_ms_to_tick(uint16_t time_ms);

/***************************************************************************//**
 * Converts 32-bits milliseconds in ticks.
 *
 * @param time_ms Number of milliseconds.
 * @param tick Pointer to the converted tick number.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note  The result is "rounded" to the superior tick number.
 *        If possible the sl_sleeptimer_ms_to_tick() function should be used.
 *
 * @note  This function converts the delay expressed in milliseconds to timer
 *        ticks (represented on 32 bits). This means that the value that can
 *        be passed to the argument 'time_ms' is limited. The maximum
 *        timeout value that can be passed to this function can be retrieved
 *        by calling sl_sleeptimer_get_max_ms32_conversion().
 *        If the value passed to 'time_ms' is too large,
 *        SL_STATUS_INVALID_PARAMETER will be returned.
 ******************************************************************************/
sl_status_t sl_sleeptimer_ms32_to_tick(uint32_t time_ms,
                                       uint32_t *tick);

/***************************************************************************//**
 * Gets the maximum value that can be passed to the functions that have a
 * 32-bits time or timeout argument expressed in milliseconds.
 *
 * @return Maximum time or timeout value in milliseconds.
 ******************************************************************************/
uint32_t sl_sleeptimer_get_max_ms32_conversion(void);

/***************************************************************************//**
 * Converts ticks in milliseconds.
 *
 * @param tick Number of tick.
 *
 * @return Corresponding milliseconds number.
 *
 * @note The result is rounded to the inferior millisecond.
 ******************************************************************************/
uint32_t sl_sleeptimer_tick_to_ms(uint32_t tick);

/***************************************************************************//**
 * Converts 64-bit ticks in milliseconds.
 *
 * @param tick Number of tick.
 * @param ms Pointer to the converted milliseconds number.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note The result is rounded to the inferior millisecond.
 ******************************************************************************/
sl_status_t sl_sleeptimer_tick64_to_ms(uint64_t tick,
                                       uint64_t *ms);

/**************************************************************************//**
 * Starts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_ms Timer timeout, in milliseconds.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note  This function converts the delay expressed in milliseconds to timer
 *        ticks (represented on 32 bits). This means that the value that can
 *        be passed to the argument 'timeout_ms' is limited. The maximum
 *        timeout value that can be passed to this function can be retrieved
 *        by calling sl_sleeptimer_get_max_ms32_conversion().
 *        If the value passed to 'timeout_ms' is too large,
 *        SL_STATUS_INVALID_PARAMETER will be returned.
 *****************************************************************************/
__STATIC_INLINE sl_status_t sl_sleeptimer_start_timer_ms(sl_sleeptimer_timer_handle_t *handle,
                                                         uint32_t timeout_ms,
                                                         sl_sleeptimer_timer_callback_t callback,
                                                         void *callback_data,
                                                         uint8_t priority,
                                                         uint16_t option_flags)
{
  sl_status_t status;
  uint32_t timeout_tick;

  status = sl_sleeptimer_ms32_to_tick(timeout_ms, &timeout_tick);
  if (status != SL_STATUS_OK) {
    return status;
  }

  return sl_sleeptimer_start_timer(handle, timeout_tick, callback, callback_data, priority, option_flags);
}

/**************************************************************************//**
 * Restarts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_ms Timer timeout, in milliseconds.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note  This function converts the delay expressed in milliseconds to timer
 *        ticks (represented on 32 bits). This means that the value that can
 *        be passed to the argument 'timeout_ms' is limited. The maximum
 *        timeout value that can be passed to this function can be retrieved
 *        by calling sl_sleeptimer_get_max_ms32_conversion().
 *        If the value passed to 'timeout_ms' is too large,
 *        SL_STATUS_INVALID_PARAMETER will be returned.
 *****************************************************************************/
__STATIC_INLINE sl_status_t sl_sleeptimer_restart_timer_ms(sl_sleeptimer_timer_handle_t *handle,
                                                           uint32_t timeout_ms,
                                                           sl_sleeptimer_timer_callback_t callback,
                                                           void *callback_data,
                                                           uint8_t priority,
                                                           uint16_t option_flags)
{
  sl_status_t status;
  uint32_t timeout_tick;

  status = sl_sleeptimer_ms32_to_tick(timeout_ms, &timeout_tick);
  if (status != SL_STATUS_OK) {
    return status;
  }

  return sl_sleeptimer_restart_timer(handle, timeout_tick, callback, callback_data, priority, option_flags);
}

/***************************************************************************//**
 * Starts a 32 bits periodic timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_ms Timer periodic timeout, in milliseconds.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note  This function converts the delay expressed in milliseconds to timer
 *        ticks (represented on 32 bits). This means that the value that can
 *        be passed to the argument 'timeout_ms' is limited. The maximum
 *        timeout value that can be passed to this function can be retrieved
 *        by calling sl_sleeptimer_get_max_ms32_conversion().
 *        If the value passed to 'timeout_ms' is too large,
 *        SL_STATUS_INVALID_PARAMETER will be returned.
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_sleeptimer_start_periodic_timer_ms(sl_sleeptimer_timer_handle_t *handle,
                                                                  uint32_t timeout_ms,
                                                                  sl_sleeptimer_timer_callback_t callback,
                                                                  void *callback_data,
                                                                  uint8_t priority,
                                                                  uint16_t option_flags)
{
  sl_status_t status;
  uint32_t timeout_tick;

  status = sl_sleeptimer_ms32_to_tick(timeout_ms, &timeout_tick);
  if (status != SL_STATUS_OK) {
    return status;
  }

  return sl_sleeptimer_start_periodic_timer(handle, timeout_tick, callback, callback_data, priority, option_flags);
}

/***************************************************************************//**
 * Restarts a 32 bits periodic timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_ms Timer periodic timeout, in milliseconds.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 * @param option_flags Bit array of option flags for the timer.
 *        Valid bit-wise OR of one or more of the following:
 *          - SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG
 *        or 0 for not flags.
 *
 * @return 0 if successful. Error code otherwise.
 *
 * @note  This function converts the delay expressed in milliseconds to timer
 *        ticks (represented on 32 bits). This means that the value that can
 *        be passed to the argument 'timeout_ms' is limited. The maximum
 *        timeout value that can be passed to this function can be retrieved
 *        by calling sl_sleeptimer_get_max_ms32_conversion().
 *        If the value passed to 'timeout_ms' is too large,
 *        SL_STATUS_INVALID_PARAMETER will be returned.
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_sleeptimer_restart_periodic_timer_ms(sl_sleeptimer_timer_handle_t *handle,
                                                                    uint32_t timeout_ms,
                                                                    sl_sleeptimer_timer_callback_t callback,
                                                                    void *callback_data,
                                                                    uint8_t priority,
                                                                    uint16_t option_flags)
{
  sl_status_t status;
  uint32_t timeout_tick;

  status = sl_sleeptimer_ms32_to_tick(timeout_ms, &timeout_tick);
  if (status != SL_STATUS_OK) {
    return status;
  }

  return sl_sleeptimer_restart_periodic_timer(handle, timeout_tick, callback, callback_data, priority, option_flags);
}

/** @} (end addtogroup SLEEPTIMER) */
/** @} (end addtogroup platform_service) */

#ifdef __cplusplus
}
#endif

#endif /* SLEEPTIMER_H */
