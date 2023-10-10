/* 
 * File:   mcal_std_types.h
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 6:02 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include "compiler.h"
#include "std_libraries.h"

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long      sint32;

typedef uint8 Std_ReturnType;

/* Section : Macro Declarations */
#define STD_HIGH            0X01
#define STD_LOW             0X00

#define STD_ON              0X01
#define STD_OFF             0X00

#define STD_ACTIVE          0X01
#define STD_IDLE            0X00

#define E_OK                (Std_ReturnType)0x01
#define E_OK                (Std_ReturnType)0x00

/* Section : Macro Declarations */

/* Section : Functions Declarations */





#endif	/* MCAL_STD_TYPES_H */

