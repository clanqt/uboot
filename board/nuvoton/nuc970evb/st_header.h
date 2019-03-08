//BOE 3.5 Initial Code 
static void init_st_display(void); 

void write_command (unsigned char y) // (uchar y,uchar x)
{
unsigned char i;
gpio_direction_output(GPIO_PB6,0); 		//cs=0;
gpio_direction_output(GPIO_PB8,0); 		
gpio_direction_output(GPIO_PB7,0);		
udelay(1);
gpio_direction_output(GPIO_PB7,1);
  for(i=0;i<8;i++)
    {
      if (y&0x80)
{
    gpio_direction_output(GPIO_PB7,0);	//sd0=0 for command
    gpio_direction_output(GPIO_PB8,1);	//sdi=1; MOSI-D0
}
          else 
{	
     gpio_direction_output(GPIO_PB7,0);	//scl=0;
     gpio_direction_output(GPIO_PB8,0);	//sdi=0; MOSI=D0
}

gpio_direction_output(GPIO_PB7,1);		//scl=0
      y=y<<1;
    }
gpio_direction_output(GPIO_PB6,1);		//cs=1;
}


void write_data(unsigned char w) // (uchar w, uchar v)
{
  unsigned char i;
gpio_direction_output(GPIO_PB6,0); 		//cs=0;
gpio_direction_output(GPIO_PB8,1);		//sd0=1 for data 
gpio_direction_output(GPIO_PB7,0);		//scl=0
udelay(2);
gpio_direction_output(GPIO_PB7,1);		//scl=1

for(i=0;i<8;i++)
 {
      
     if (w&0x80)
{
gpio_direction_output(GPIO_PB7,0); 		
gpio_direction_output(GPIO_PB8,1); 

}
        else
{
gpio_direction_output(GPIO_PB7,0);	        //scl=1;
gpio_direction_output(GPIO_PB8,0);        	// sdi=0;
}
      
gpio_direction_output(GPIO_PB7,1);	        //scl=1;
w=w<<1;
    }
gpio_direction_output(GPIO_PB6,1); 		//cs=1;
}


static void init_st_display(void)
{ 
gpio_request(GPIO_PB8,"ili9488");   /* D0 */
gpio_direction_output(GPIO_PB8,0);

gpio_request(GPIO_PB9,"ili9488");  /* D1 */
gpio_direction_input(GPIO_PB9);

gpio_request(GPIO_PB6,"ili9488");  /* CS0 */
gpio_direction_output(GPIO_PB6,1);

gpio_request(GPIO_PB7,"ili9844");   /* CLK */
gpio_direction_output(GPIO_PB7,0);

gpio_request(GPIO_PB5,"ili9844");    /*  RESET */
gpio_direction_output(GPIO_PB5,0);

gpio_request(GPIO_PB4,"ili9488");    /* DATA/COMMAND */
gpio_direction_output(GPIO_PB4,0);


gpio_direction_output(GPIO_PB5,1);
mdelay(1);

gpio_direction_output(GPIO_PB5,0);
mdelay(10);

gpio_direction_output(GPIO_PB5,1);
mdelay(120);
 
//*************LCD Driver Initial **********// 
mdelay(120);      // Delay 120ms

write_command(0x11);     // Sleep Out
mdelay(120);      // Delay 120ms

write_command(0x3a) ; //55 16-BIT//66 18-BIT//77:24-BIT
write_data(0x55);

write_command(0xf0) ; 
write_data(0xc3) ; 

write_command(0xf0); 
write_data(0x96) ; 

write_command(0x36); 
write_data(0x48) ; 

write_command(0xB4); 
write_data(0x01) ; 

/////MIPI接口VIDEO，RGB打开B6寄存器////
write_command(0xB6); 
write_data(0xe0); 
write_data(0x02); 
write_data(0x3b); 
/////////////// 

write_command(0xB7) ; 
write_data(0xC6) ; 

write_command(0xc2) ; 
write_data(0xA7) ; 

write_command(0xc5) ; 
write_data(0x15) ; 

write_command(0xe0) ;     //Positive Voltage Gamma Control
write_data(0xf0); 
write_data(0x07); 
write_data(0x11); 
write_data(0x14); 
write_data(0x16); 
write_data(0x0c); 
write_data(0x42); 
write_data(0x55); 
write_data(0x50); 
write_data(0x0b); 
write_data(0x16); 
write_data(0x16); 
write_data(0x20); 
write_data(0x23); 

write_command(0xe1) ;      //Negative Voltage Gamma Control
write_data(0xf0); 
write_data(0x06); 
write_data(0x11); 
write_data(0x13); 
write_data(0x14); 
write_data(0x1c); 
write_data(0x42); 
write_data(0x54); 
write_data(0x51); 
write_data(0x0b); 
write_data(0x16); 
write_data(0x15); 
write_data(0x20); 
write_data(0x22); 

write_command(0xf0) ; 
write_data(0x3c) ; 

write_command(0xf0) ; 
write_data(0x69) ; 
mdelay(120);      // Delay 120ms

write_command(0x29) ;     // Display ON
}
