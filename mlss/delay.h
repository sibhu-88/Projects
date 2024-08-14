#include "typedef.h"

/**
 * @brief Delays execution for the specified number of seconds.
 * @param sec Number of seconds to delay.
 */
void delay_sec(U32 sec)
{
    // Calculate timer reload value for 1 second delay
    T0PR = (CCLK / 1000000) - 1; // Assuming CCLK is in MHz
    T0TCR = 0x01; // Start timer
    while (T0TC < sec * 1000000); // Wait until timer reaches desired duration
    T0TCR = 0x02; // Reset timer
    T0TCR = 0x00; // Stop timer
}

/**
 * @brief Delays execution for the specified number of milliseconds.
 * @param ms Number of milliseconds to delay.
 */
void delay_milisec(U32 ms)
{
    // Calculate timer reload value for 1 millisecond delay
    T0PR = (CCLK / 1000) - 1; // Assuming CCLK is in kHz
    T0TCR = 0x01; // Start timer
    while (T0TC < ms); // Wait until timer reaches desired duration
    T0TCR = 0x02; // Reset timer
    T0TCR = 0x00; // Stop timer
}

/**
 * @brief Delays execution for the specified number of microseconds.
 * @param mis Number of microseconds to delay.
 */
void delay_microsec(U32 mis)
{
    // Calculate timer reload value for 1 microsecond delay
    T0PR = (CCLK / 1000000) - 1; // Assuming CCLK is in MHz
    T0TCR = 0x01; // Start timer
    while (T0TC < mis); // Wait until timer reaches desired duration
    T0TCR = 0x02; // Reset timer
    T0TCR = 0x00; // Stop timer
}
