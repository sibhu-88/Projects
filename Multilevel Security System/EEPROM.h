#include <LPC21xx.h>
#include <stdlib.h>
#include "typedef.h"

// Define pin functions for I2C communication
#define SCL_EN (1 << 4)  // P0.4 for SCL
#define SDA_EN (1 << 6)  // P0.6 for SDA

// Define I2C speed and related constants
#define CCLK 60000000    // CPU Clock Frequency in Hz
#define PCLK CCLK / 4    // Peripheral Clock Frequency in Hz (assuming PCLK is CCLK divided by 4)
#define I2C_SPEED 100000 // I2C Speed in Hz
#define LOADVAL ((PCLK / I2C_SPEED) / 2)

// Bit defines for I2CONSET register
#define AA_BIT 2
#define SI_BIT 3
#define STO_BIT 4
#define STA_BIT 5
#define I2EN_BIT 6

// EEPROM Slave Address
#define I2C_EEPROM_SA 0x50

void init_i2c(void)
{
    // Configure I/O pins for SCL & SDA functions using PINSEL0
    PINSEL0 |= SCL_EN | SDA_EN;

    // Configure Speed for I2C Serial Communication
    I2SCLL = LOADVAL; // Low period of SCL clock
    I2SCLH = LOADVAL; // High period of SCL clock

    // Enable I2C Peripheral for Communication
    I2CONSET = 1 << I2EN_BIT;
}

void i2c_start(void)
{
    // Start condition
    I2CONSET = 1 << STA_BIT;
    while (!((I2CONSET >> SI_BIT) & 1)); // Wait for start bit status
    I2CONCLR = 1 << STA_BIT; // Clear start condition
}

void i2c_restart(void)
{
    // Start condition
    I2CONSET = 1 << STA_BIT;
    I2CONCLR = 1 << SI_BIT; // Clear SI bit
    while (!((I2CONSET >> SI_BIT) & 1)); // Wait for SI bit status
    I2CONCLR = 1 << STA_BIT; // Clear start condition
}

void i2c_write(U8 dat)
{
    // Put data into I2DAT
    I2DAT = dat;
    I2CONCLR = 1 << SI_BIT; // Clear SI bit
    while (!((I2CONSET >> SI_BIT) & 1)); // Wait for SI bit status
}

void i2c_stop(void)
{
    I2CONSET = 1 << STO_BIT; // Issue stop condition
    I2CONCLR = 1 << SI_BIT; // Clear SI bit status
    while ((I2CONSET >> STO_BIT) & 1); // Wait for stop bit to clear automatically
}

U8 i2c_nack(void)
{
    I2CONSET = 0x00; // Assert Not Acknowledge
    I2CONCLR = 1 << SI_BIT; // Clear SI bit
    while (!((I2CONSET >> SI_BIT) & 1)); // Wait for SI bit status
    return I2DAT;
}

U8 i2c_masterack(void)
{
    I2CONSET = 0x04; // Assert Acknowledge
    I2CONCLR = 1 << SI_BIT; // Clear SI bit
    while (!((I2CONSET >> SI_BIT) & 1)); // Wait for SI bit status
    I2CONCLR = 0x04; // Clear Assert Acknowledge
    return I2DAT;
}

void i2c_eeprom_page_write(U8 slaveAddr, U8 wBuffStartAddr, U8 *p, U8 nBytes)
{
    U8 i;
    i2c_start();
    i2c_write(slaveAddr << 1); // SlaveAddr + write
    i2c_write(wBuffStartAddr); // Write buffer start address
    for (i = 0; i < nBytes; i++)
    {
        i2c_write(p[i]); // Write buffer data
    }
    i2c_stop();
    delay_milisec(10); // Delay after write operation
}

void i2c_eeprom_seq_read(U8 slaveAddr, U8 rBuffStartAddr, U8 *p, U8 nBytes)
{
    U8 i;
    i2c_start();
    i2c_write(slaveAddr << 1); // SlaveAddr + write
    i2c_write(rBuffStartAddr); // Read buffer start address
    i2c_restart();
    i2c_write((slaveAddr << 1) | 1); // SlaveAddr + read
    for (i = 0; i < nBytes - 1; i++)
    {
        p[i] = i2c_masterack(); // Read data with ACK
    }
    p[i] = i2c_nack(); // Read final byte with NACK
    i2c_stop();
}
