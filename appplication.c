/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"


SPI_Config spi_ob = {
    .spi_mode = SPI_MASTER_FOSC_DIV4,
    .ClockPolarity = SPI_IDLE_STATE_HIGH_LEVEL,
    .SampleSelect = SPI_DATA_SAMPLE_MIDDLE,
    .ClockSelect = SPI_TRANSMIT_ACTIVE_TO_IDLE
};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    ret = SPI_Init(&spi_ob);
    
    uint8 str[]="yous";
    
    while(1)
    {
        for(int i=0;i<4;i++){
            ret = SPI_Send_Byte(&spi_ob, str[i]);
            __delay_ms(100);
        }
        
        
    }
    return (EXIT_SUCCESS);
}



