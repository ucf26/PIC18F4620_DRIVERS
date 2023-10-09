/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"


#define HW8_WR(_x) (*((volatile uint8 *)(_x)))

#define HW_LATC (HW8_WR(0xF8B))
#define HW_TRIC (HW8_WR(0xF94))



typedef union{
    struct{
        uint8 SELF_LATC0 : 1;
        uint8 SELF_LATC1 : 1;
        uint8 SELF_LATC2 : 1;
        uint8 SELF_LATC3 : 1;
        uint8 SELF_LATC4 : 1;
        uint8 SELF_LATC5 : 1;
        uint8 SELF_LATC6 : 1;
        uint8 SELF_LATC7 : 1;
    };
    uint8 SELF_LATC_REG;
}SELF_LATC;

#define LAT_REG_AC ((volatile SELF_LATC *)(0xF8B)) 

int main() {
    HW_TRIC = 0x00; // all is output 
    HW_LATC = 0x0F;
    
    LAT_REG_AC->SELF_LATC7 = 1;
    
    
    
    while(1)
    {
        
    }
    return (EXIT_SUCCESS);
}

