/* hx8357_init.h 
*
*Clancor display information header 
*
*Copyright (C) 2015, Clancor Technovates
*
*Initialisation code for ili9341 display board 
*
***************************************************************************************
* Note: Need to change gpio(spi - mosi and miso) pins in future for 2nd revision board *
***************************************************************************************
*/
// Modified for ili9341 - capacitive touch


static void ili9341_init (void);

void write_command(unsigned char y) // (uchar y,uchar x)
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
/*
void read_data(void) // (uchar w, uchar v)
{
    unsigned char i;
    gpio_direction_output(GPIO_PB6,0); 		//cs=0;
    gpio_direction_output(GPIO_PB8,1);		//sd0=1 for data
    gpio_direction_output(GPIO_PB7,0);		//scl=0
    udelay(2);
    gpio_direction_output(GPIO_PB7,1);		//scl=1

    for(i=0;i<8;i++)
    {
    if(gpio_direction_input(GPIO_PB9)==1)
        {
                printk("%d",1);
        }
        else
        {
                printk("%d",0);
        }
     gpio_direction_output(GPIO_PB7,1);		//scl=0
}
*/

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


static void ili9341_init (void)
{

    gpio_request(GPIO_PB8,"ili9341");   /* D0 */
    gpio_direction_output(GPIO_PB8,0);

    gpio_request(GPIO_PB9,"ili9341");   /* D1 */
    gpio_direction_input(GPIO_PB9);

    gpio_request(GPIO_PB6,"ili9341");   /* CS0 */
    gpio_direction_output(GPIO_PB6,1);

    gpio_request(GPIO_PB7," ili9341");   /* CLK */
    gpio_direction_output(GPIO_PB7,0);

    gpio_request(GPIO_PB5," ili9341");   /*  RESET */
    gpio_direction_output(GPIO_PB5,0);

    gpio_request(GPIO_PB4,"ili9341");   /* DATA/COMMAND */
    gpio_direction_output(GPIO_PB4,0);


    //Hardware reset Sequance
    gpio_direction_output(GPIO_PB5,1);
    mdelay(10);
    gpio_direction_output(GPIO_PB5,0);
    mdelay(100);
    gpio_direction_output(GPIO_PB5,1);
    mdelay(200);
    //Hardware reset Sequance

    //******* Start Initial Sequence
    write_command(0x01); //software reset
    mdelay(5);
    write_command(0x11);
    mdelay(120);

    write_command(0xCF);
    write_data(0x00);
    write_data(0xc3);
    write_data(0X30);

    write_command(0xED);
    write_data(0x64);
    write_data(0x03);
    write_data(0X12);
    write_data(0X81);

    write_command(0xE8);
    write_data(0x85);
    write_data(0x10);
    write_data(0x79);

    write_command(0xCB);
    write_data(0x39);
    write_data(0x2C);
    write_data(0x00);
    write_data(0x34);
    write_data(0x02);

    write_command(0xF7);
    write_data(0x20);

    write_command(0xEA);
    write_data(0x00);
    write_data(0x00);

    write_command(0xC0); //Power control
    write_data (0x22); //VRH[5:0]

    write_command(0xC1); //Power control
    write_data (0x11); //SAP[2:0];BT[3:0]

    write_command(0xC5); //VCM control
    write_data (0x3D);//2B
    write_data (0x20);//2B

    write_command(0xC7); //VCM control2
    write_data (0xC0);

    write_command(0xB1);
    write_data(0x00);
    write_data(0x13);

    write_command(0xB5);//Blanking Porch Control
    write_data(0x09);
    write_data(0x09);
    write_data(0x02);
    write_data(0x02);

    write_command(0xB6); //Display Function Control
    write_data(0x12);//12
    write_data(0x02);//02
    write_data(0x27);

    write_command(0x30);
    write_data(0x00);
    write_data(0x00);
    write_data(0x01);
    write_data(0x3F);

    write_command(0xF2); // 3Gamma Function Disable
    write_data (0x00);

    //write_command(0x2A);  // column select
    write_command(0x2C);

    write_command(0x26); //Gamma curve selected
    write_data (0x01);

    write_command(0x3A);//  rgb & cpu 18 0x66 /16 0x55 bit select
    write_data(0x55);
    //*************************************************
    write_command(0x36); // Memory Access Control
    write_data (0x48);// 0 degree=0x48, 90 degree=0xE8, 180 degree=0x88, 270 degree=0x38,
    //*************************************************
    write_command(0x21);  //Inversion control
    //*************************************************

    write_command(0xF6); //interface control
    //	                write_data(0x01);
    //	                write_data(0x01);
    //	                write_data(0x06); //06-RGB  02-Internal  0A-vsyc
    write_data(0x00);
    write_data(0x01);
    write_data(0x06);

    write_command(0xB0); //
    write_data(0xC0); //C0-DE Mode,  E0-Sync Mode  B1-Direct Mem

    write_command(0xE0); //Set Gamma
    write_data(0x0F);
    write_data(0x3F);
    write_data(0x2F);
    write_data(0x0C);
    write_data(0x10);
    write_data(0x0A);
    write_data(0x53);
    write_data(0XD5);
    write_data(0x40);
    write_data(0x0A);
    write_data(0x13);
    write_data(0x03);
    write_data(0x08);
    write_data(0x03);
    write_data(0x00);

    write_command(0xE1); //Set Gamma
    write_data(0x00);
    write_data(0x00);
    write_data(0x10);
    write_data(0x03);
    write_data(0x0F);
    write_data(0x05);
    write_data(0x2C);
    write_data(0xA2);
    write_data(0x3F);
    write_data(0x05);
    write_data(0x0E);
    write_data(0x0C);
    write_data(0x37);
    write_data(0x3C);
    write_data(0x0F);

    write_command(0x11);    //Exit Sleep
    mdelay(120);
    write_command(0x29);    //Display on
    mdelay(50);

}
