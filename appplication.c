/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;


int main() {
    
    app_init();

    while(1)
    {
        
    }
    return (EXIT_SUCCESS);
}


void app_init(void)
{
    ecu_layer_initialize();
}