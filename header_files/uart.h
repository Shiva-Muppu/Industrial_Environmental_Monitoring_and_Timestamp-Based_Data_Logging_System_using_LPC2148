#include "types.h"

/* UART0 initialization */
void UART0_Init(void);

/* Transmit and receive single character */
void UART0_Tx(u8 sDat);
u8 UART0_Rx(void);

/* Transmit string */
void U0_TxStr(s8 *s);

/* Transmit unsigned and signed integers */
void U0_TxU32(u32 n);
void U0_TxS32(s32 n);

/* Transmit floating-point value */
void U0_TxF32(f32 fn, u8 nDP);

/* Receive string */
s8 *U0_RxStr(void);
