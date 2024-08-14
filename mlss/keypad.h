#include "typedef.h"

// Macros for column and row pins
#define COL0 (IOPIN0 & (1 << 16))
#define COL1 (IOPIN0 & (1 << 17))
#define COL2 (IOPIN0 & (1 << 18))
#define COL3 (IOPIN0 & (1 << 19))

#define ROW0 (1 << 20)
#define ROW1 (1 << 21)
#define ROW2 (1 << 22)
#define ROW3 (1 << 23)

// Key lookup table
U8 KEY_LUT[4][4] = {
    {1, 2, 3, 'A'},
    {4, 5, 6, 'B'},
    {7, 8, 9, 'C'},
    {'*', 0, '#', 'D'}
};

U8 KEYSCAN(void) {
    U8 ROW_VAL, COL_VAL;

    // Set row pins as output and column pins as input
    IODIR0 |= ROW0 | ROW1 | ROW2 | ROW3;
    IODIR0 &= ~(COL0 | COL1 | COL2 | COL3);

    while (1) {
        // Scan each row and check for pressed key
        IOCLR0 |= ROW0 | ROW1 | ROW2 | ROW3;
        IOSET0 |= COL0 | COL1 | COL2 | COL3;

        // Check if any column is low (key pressed in that row)
        if (!(COL0 && COL1 && COL2 && COL3)) {
            ROW_VAL = 0;
            break;
        }

        IOCLR0 |= ROW0;
        IOSET0 |= ROW1 | ROW2 | ROW3;
        if (!(COL0 && COL1 && COL2 && COL3)) {
            ROW_VAL = 1;
            break;
        }

        IOCLR0 |= ROW1;
        IOSET0 |= ROW0 | ROW2 | ROW3;
        if (!(COL0 && COL1 && COL2 && COL3)) {
            ROW_VAL = 2;
            break;
        }

        IOCLR0 |= ROW2;
        IOSET0 |= ROW0 | ROW1 | ROW3;
        if (!(COL0 && COL1 && COL2 && COL3)) {
            ROW_VAL = 3;
            break;
        }

        // Wait for a short duration before retrying (debouncing)
        delay_milisec(10);
    }

    // Determine the column where key is pressed
    if (!COL0) COL_VAL = 0;
    else if (!COL1) COL_VAL = 1;
    else if (!COL2) COL_VAL = 2;
    else if (!COL3) COL_VAL = 3;

    // Wait until key is released (debouncing)
    delay_milisec(100);
    while (!(COL0 && COL1 && COL2 && COL3));

    // Return the pressed key value from the lookup table
    return KEY_LUT[ROW_VAL][COL_VAL] ;
}
