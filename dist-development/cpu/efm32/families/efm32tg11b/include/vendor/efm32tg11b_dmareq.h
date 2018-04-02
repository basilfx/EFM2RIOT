/**************************************************************************//**
 * @file efm32tg11b_dmareq.h
 * @brief EFM32TG11B_DMAREQ register and bit field definitions
 * @version 5.4.0
 ******************************************************************************
 * # License
 * <b>Copyright 2017 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.@n
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.@n
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Laboratories, Inc.
 * has no obligation to support this Software. Silicon Laboratories, Inc. is
 * providing the Software "AS IS", with no express or implied warranties of any
 * kind, including, but not limited to, any implied warranties of
 * merchantability or fitness for any particular purpose or warranties against
 * infringement of any proprietary rights of a third party.
 *
 * Silicon Laboratories, Inc. will not be liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this Software.
 *
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#if defined(__ICCARM__)
#pragma system_include       /* Treat file as system include file. */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang system_header  /* Treat file as system include file. */
#endif

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/

/**************************************************************************//**
 * @addtogroup EFM32TG11B_DMAREQ DMAREQ
 * @{
 * @defgroup EFM32TG11B_DMAREQ_BitFields DMAREQ Bit Fields
 * @{
 *****************************************************************************/
#define DMAREQ_PRS_REQ0               ((1 << 16) + 0)  /**< DMA channel select for PRS_REQ0 */
#define DMAREQ_PRS_REQ1               ((1 << 16) + 1)  /**< DMA channel select for PRS_REQ1 */
#define DMAREQ_ADC0_SINGLE            ((8 << 16) + 0)  /**< DMA channel select for ADC0_SINGLE */
#define DMAREQ_ADC0_SCAN              ((8 << 16) + 1)  /**< DMA channel select for ADC0_SCAN */
#define DMAREQ_VDAC0_CH0              ((10 << 16) + 0) /**< DMA channel select for VDAC0_CH0 */
#define DMAREQ_VDAC0_CH1              ((10 << 16) + 1) /**< DMA channel select for VDAC0_CH1 */
#define DMAREQ_USART0_RXDATAV         ((12 << 16) + 0) /**< DMA channel select for USART0_RXDATAV */
#define DMAREQ_USART0_TXBL            ((12 << 16) + 1) /**< DMA channel select for USART0_TXBL */
#define DMAREQ_USART0_TXEMPTY         ((12 << 16) + 2) /**< DMA channel select for USART0_TXEMPTY */
#define DMAREQ_USART1_RXDATAV         ((13 << 16) + 0) /**< DMA channel select for USART1_RXDATAV */
#define DMAREQ_USART1_TXBL            ((13 << 16) + 1) /**< DMA channel select for USART1_TXBL */
#define DMAREQ_USART1_TXEMPTY         ((13 << 16) + 2) /**< DMA channel select for USART1_TXEMPTY */
#define DMAREQ_USART1_RXDATAVRIGHT    ((13 << 16) + 3) /**< DMA channel select for USART1_RXDATAVRIGHT */
#define DMAREQ_USART1_TXBLRIGHT       ((13 << 16) + 4) /**< DMA channel select for USART1_TXBLRIGHT */
#define DMAREQ_USART2_RXDATAV         ((14 << 16) + 0) /**< DMA channel select for USART2_RXDATAV */
#define DMAREQ_USART2_TXBL            ((14 << 16) + 1) /**< DMA channel select for USART2_TXBL */
#define DMAREQ_USART2_TXEMPTY         ((14 << 16) + 2) /**< DMA channel select for USART2_TXEMPTY */
#define DMAREQ_USART3_RXDATAV         ((15 << 16) + 0) /**< DMA channel select for USART3_RXDATAV */
#define DMAREQ_USART3_TXBL            ((15 << 16) + 1) /**< DMA channel select for USART3_TXBL */
#define DMAREQ_USART3_TXEMPTY         ((15 << 16) + 2) /**< DMA channel select for USART3_TXEMPTY */
#define DMAREQ_USART3_RXDATAVRIGHT    ((15 << 16) + 3) /**< DMA channel select for USART3_RXDATAVRIGHT */
#define DMAREQ_USART3_TXBLRIGHT       ((15 << 16) + 4) /**< DMA channel select for USART3_TXBLRIGHT */
#define DMAREQ_UART0_RXDATAV          ((18 << 16) + 0) /**< DMA channel select for UART0_RXDATAV */
#define DMAREQ_UART0_TXBL             ((18 << 16) + 1) /**< DMA channel select for UART0_TXBL */
#define DMAREQ_UART0_TXEMPTY          ((18 << 16) + 2) /**< DMA channel select for UART0_TXEMPTY */
#define DMAREQ_LEUART0_RXDATAV        ((20 << 16) + 0) /**< DMA channel select for LEUART0_RXDATAV */
#define DMAREQ_LEUART0_TXBL           ((20 << 16) + 1) /**< DMA channel select for LEUART0_TXBL */
#define DMAREQ_LEUART0_TXEMPTY        ((20 << 16) + 2) /**< DMA channel select for LEUART0_TXEMPTY */
#define DMAREQ_I2C0_RXDATAV           ((22 << 16) + 0) /**< DMA channel select for I2C0_RXDATAV */
#define DMAREQ_I2C0_TXBL              ((22 << 16) + 1) /**< DMA channel select for I2C0_TXBL */
#define DMAREQ_I2C1_RXDATAV           ((23 << 16) + 0) /**< DMA channel select for I2C1_RXDATAV */
#define DMAREQ_I2C1_TXBL              ((23 << 16) + 1) /**< DMA channel select for I2C1_TXBL */
#define DMAREQ_TIMER0_UFOF            ((25 << 16) + 0) /**< DMA channel select for TIMER0_UFOF */
#define DMAREQ_TIMER0_CC0             ((25 << 16) + 1) /**< DMA channel select for TIMER0_CC0 */
#define DMAREQ_TIMER0_CC1             ((25 << 16) + 2) /**< DMA channel select for TIMER0_CC1 */
#define DMAREQ_TIMER0_CC2             ((25 << 16) + 3) /**< DMA channel select for TIMER0_CC2 */
#define DMAREQ_TIMER1_UFOF            ((26 << 16) + 0) /**< DMA channel select for TIMER1_UFOF */
#define DMAREQ_TIMER1_CC0             ((26 << 16) + 1) /**< DMA channel select for TIMER1_CC0 */
#define DMAREQ_TIMER1_CC1             ((26 << 16) + 2) /**< DMA channel select for TIMER1_CC1 */
#define DMAREQ_TIMER1_CC2             ((26 << 16) + 3) /**< DMA channel select for TIMER1_CC2 */
#define DMAREQ_TIMER1_CC3             ((26 << 16) + 4) /**< DMA channel select for TIMER1_CC3 */
#define DMAREQ_WTIMER0_UFOF           ((32 << 16) + 0) /**< DMA channel select for WTIMER0_UFOF */
#define DMAREQ_WTIMER0_CC0            ((32 << 16) + 1) /**< DMA channel select for WTIMER0_CC0 */
#define DMAREQ_WTIMER0_CC1            ((32 << 16) + 2) /**< DMA channel select for WTIMER0_CC1 */
#define DMAREQ_WTIMER0_CC2            ((32 << 16) + 3) /**< DMA channel select for WTIMER0_CC2 */
#define DMAREQ_WTIMER1_UFOF           ((33 << 16) + 0) /**< DMA channel select for WTIMER1_UFOF */
#define DMAREQ_WTIMER1_CC0            ((33 << 16) + 1) /**< DMA channel select for WTIMER1_CC0 */
#define DMAREQ_WTIMER1_CC1            ((33 << 16) + 2) /**< DMA channel select for WTIMER1_CC1 */
#define DMAREQ_WTIMER1_CC2            ((33 << 16) + 3) /**< DMA channel select for WTIMER1_CC2 */
#define DMAREQ_WTIMER1_CC3            ((33 << 16) + 4) /**< DMA channel select for WTIMER1_CC3 */
#define DMAREQ_MSC_WDATA              ((48 << 16) + 0) /**< DMA channel select for MSC_WDATA */
#define DMAREQ_CRYPTO0_DATA0WR        ((49 << 16) + 0) /**< DMA channel select for CRYPTO0_DATA0WR */
#define DMAREQ_CRYPTO0_DATA0XWR       ((49 << 16) + 1) /**< DMA channel select for CRYPTO0_DATA0XWR */
#define DMAREQ_CRYPTO0_DATA0RD        ((49 << 16) + 2) /**< DMA channel select for CRYPTO0_DATA0RD */
#define DMAREQ_CRYPTO0_DATA1WR        ((49 << 16) + 3) /**< DMA channel select for CRYPTO0_DATA1WR */
#define DMAREQ_CRYPTO0_DATA1RD        ((49 << 16) + 4) /**< DMA channel select for CRYPTO0_DATA1RD */
#define DMAREQ_CSEN_DATA              ((61 << 16) + 0) /**< DMA channel select for CSEN_DATA */
#define DMAREQ_CSEN_BSLN              ((61 << 16) + 1) /**< DMA channel select for CSEN_BSLN */
#define DMAREQ_LESENSE_BUFDATAV       ((62 << 16) + 0) /**< DMA channel select for LESENSE_BUFDATAV */

/** @} */
/** @} End of group EFM32TG11B_DMAREQ */
/** @} End of group Parts */
#ifdef __cplusplus
}
#endif

