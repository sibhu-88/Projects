
#define leds 7<<17
#define led1(i) 1<<(17+i)
#define led2(i) 1<<(19-i)
#define M1 1<<17
#define M2 1<<18

//right
void right(void){
	char cnt=0,i;
	IODIR0 = leds;
	IOSET0 = leds;
		while(cnt<10){
			for( i=0 ; i<3 ; i++ ){
				IOCLR0 = led1(i);
				DELAY_MS(150);
				IOSET0 = led1(i);
				DELAY_MS(150);
			}
			cnt++;
		}	
}
	
//left
void left(void){
	char cnt=0,i;
	IODIR0 = leds;
	IOSET0 = leds;
	while(cnt<10){
		for( i=0 ; i<3 ; i++ ){
			IOCLR0 = led2(i);
			DELAY_MS(150);
			IOSET0 = led2(i);
			DELAY_MS(150);
		}
		cnt++;
	}
}
	
	//wiper
void wiper(void){
	IODIR0 = M1| M2;
	IOSET0 = M1;
	IOCLR0 = M2;
	DELAY_SEC(2);
	IOCLR0 = M1| M2;
}	

