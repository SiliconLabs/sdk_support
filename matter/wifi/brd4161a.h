#ifndef _BRD4161A_H_
#define _BRD4161A_H_
#ifndef LOGGING_STATS
#define WAKE_INDICATOR_PIN PIN(D, 3)
#endif

#ifdef LOGGING_STATS
#define LOGGING_WAKE_INDICATOR_PIN PIN(D, 3)
#define LOGGING_STATS_PORT gpioPortD
#define LOGGING_STATS_PIN 03
#endif

#define MY_USART USART2
#define MY_USART_TX_SIGNAL dmadrvPeripheralSignal_USART2_TXBL
#define MY_USART_RX_SIGNAL dmadrvPeripheralSignal_USART2_RXDATAV


#ifdef RS911X_WIFI
#define WFX_RESET_PIN PIN(D, 12)
#define WFX_INTERRUPT_PIN PIN(C, 9)
#define WFX_SLEEP_CONFIRM_PIN PIN(D, 13)
#define SL_WFX_HOST_PINOUT_SPI_IRQ 9
#else /* WF200 */
#define SL_WFX_HOST_PINOUT_RESET_PORT gpioPortD
#define SL_WFX_HOST_PINOUT_RESET_PIN 10
#define SL_WFX_HOST_PINOUT_SPI_WIRQ_PORT gpioPortB /* SPI IRQ port*/
#define SL_WFX_HOST_PINOUT_SPI_WIRQ_PIN 6          /* SPI IRQ pin */
#define SL_WFX_HOST_PINOUT_WUP_PORT gpioPortD
#define SL_WFX_HOST_PINOUT_WUP_PIN 8
#define SL_WFX_HOST_PINOUT_SPI_IRQ 5
#endif /* WF200/9116 */

#endif /* _BRD4161A_H_ */
