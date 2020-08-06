/***************************************************************************//**
 * @file
 * @brief This file defines the basic information needed to go from reset up to
 * the main() found in C code.
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
// Forward declaration for the debugging ISR shim
void halInternalIntDebuggingIsr(void);

// Determines reset cause
void halInternalClassifyReset(void);

//=============================================================================
// Provide a prototype for the real C code main() in the application.
//=============================================================================
extern int main(void);

// The startup files for IAR and GCC use different names for the vector table.
// We declare both here, but only actually use the one that's appropriate.

#ifdef __ICCARM__
  #define VECTOR_TABLE  __vector_table
#elif defined(__GNUC__)
  #define VECTOR_TABLE  __Vectors
#else
  #error Do not know how to get the vector table for this compiler.
#endif

extern const HalVectorTableType VECTOR_TABLE[];
