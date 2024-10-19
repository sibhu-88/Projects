#include <LPC21xx.H>
#include <string.h>

#include "4bit_lcd.h"
#include "typedef.h"

#define LED 1<<17
#define pclk 15000000

typedef struct rtc{
	U32 second;
	U32 minute;
	U32 hour;
	U32 date;
	U32 month;
	U32 year;
	char ampm[3];
}RTC;

void RTC_GetTime(RTC *get) {
    get->hour = HOUR;      
    get->minute = MIN;
    get->second = SEC;
    get->date = DOM;
    get->month = MONTH;
    get->year = YEAR;

    if (get->hour >= 12) {
        strcpy(get->ampm, "PM"); 
        if (get->hour > 12) {
            get->hour -= 12; 
        }
    } else {
        strcpy(get->ampm, "AM");
        if (get->hour == 0) {
            get->hour = 12;
        }
    }
}

void RTC_SetTime(RTC set) {
	HOUR = set.hour;
	MIN =  set.minute;
	SEC = set.second;
	DOM = set.date;
	MONTH = set.month;
	YEAR =	set.year;
}

void RTC_Init(void) {
	RTC set={40,59,11,19,10,2024};
    CCR = 0X00;
	RTC_SetTime(set);
	CCR |= 0X01;
	PREINT = (pclk / 32768) - 1;
	PREFRAC = pclk - ((PREINT +1) * 32768);
}

int main() {
    RTC get;

    RTC_Init();
	LCD_INIT();
	IODIR0 = LED;

    while (1) {
        RTC_GetTime(&get);

		LCD_CMD(0X80);
		LCD_STR("TIME:");
		LCD_INTEGER(get.hour);
		LCD_STR(":");
		LCD_INTEGER(get.minute);
		LCD_STR(":");
		LCD_INTEGER(get.second);
		LCD_STR(get.ampm);

		LCD_CMD(0XC0);
		LCD_STR("DATE::");
		LCD_INTEGER(get.date);
		LCD_STR("/");
		LCD_INTEGER(get.month);
		LCD_STR("/");
		LCD_INTEGER(get.year);

		delay_milisec(1000);
		LCD_CMD(0X01);
		IOPIN0 ^= LED;
    }
}


