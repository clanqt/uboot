static void ili9341_init (void);

void SPI_WriteComm(unsigned char y) // (uchar y,uchar x)
{
    unsigned char i;
    gpio_direction_output(GPIO_PB6,0); 		//Chip Select 0
    gpio_direction_output(GPIO_PB4,0);          //DataCommand 0
    for(i=0;i<8;i++)
    {
        gpio_direction_output(GPIO_PB7,0);           //Clock Pin 0
        if (y&0x80)
        {
            gpio_direction_output(GPIO_PB8,1);	//SDA Data Output Pin
        }
        else
        {
            gpio_direction_output(GPIO_PB8,0);	//sdi=0; MOSI=D0
        }
        gpio_direction_output(GPIO_PB7,1);	//Clock Pin 1
        y=y<<1;
    }
    gpio_direction_output(GPIO_PB6,1);		//Chip Select 1
}

void SPI_WriteData(unsigned char y) // (uchar w, uchar v)
{
    unsigned char i;
    gpio_direction_output(GPIO_PB6,0); 		//Chip Select 0
    gpio_direction_output(GPIO_PB4,1);          //DataCommand 0
    for(i=0;i<8;i++)
    {
        gpio_direction_output(GPIO_PB7,0);           //Clock Pin 0
        if (y&0x80)
        {
            gpio_direction_output(GPIO_PB8,1);	//SDA Data Output Pin
        }
        else
        {
            gpio_direction_output(GPIO_PB8,0);	//sdi=0; MOSI=D0
        }
        gpio_direction_output(GPIO_PB7,1);	//Clock Pin 1
        y=y<<1;
    }
    gpio_direction_output(GPIO_PB6,1);		//Chip Select 1
}

static void ili9341_init(void)
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

    //************* Start Initial Sequence **********//
    SPI_WriteComm(0x01); //Software reset
    mdelay(5);

    SPI_WriteData(0x11);
    mdelay(120);

    SPI_WriteComm(0xCF);
    SPI_WriteData(0x00);
    SPI_WriteData(0xCB);
    SPI_WriteData(0X30);

    SPI_WriteComm(0xED);
    SPI_WriteData(0x64);
    SPI_WriteData(0x03);
    SPI_WriteData(0X12);
    SPI_WriteData(0X81);

    SPI_WriteComm(0xE8);
    SPI_WriteData(0x85);
    SPI_WriteData(0x10);
    SPI_WriteData(0x7A);

    SPI_WriteComm(0xCB);
    SPI_WriteData(0x39);
    SPI_WriteData(0x2C);
    SPI_WriteData(0x00);
    SPI_WriteData(0x34);
    SPI_WriteData(0x02);

    SPI_WriteComm(0xF7);
    SPI_WriteData(0x20);

    SPI_WriteComm(0xEA);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);

    SPI_WriteComm(0xC0);    //Power control
    SPI_WriteData(0x21);   //VRH[5:0]

    SPI_WriteComm(0xC1);    //Power control
    SPI_WriteData(0x11);   //SAP[2:0];BT[3:0]

    SPI_WriteComm(0xC5);    //VCM control
    SPI_WriteData(0x3F);
    SPI_WriteData(0x3C);

    SPI_WriteComm(0xC7);    //VCM control2
    SPI_WriteData(0XAF);

    SPI_WriteComm(0x36);    // Memory Access Control
    SPI_WriteData(0x08);

    SPI_WriteComm(0x3A);
    SPI_WriteData(0x66);

    SPI_WriteComm(0xB1);
    SPI_WriteData(0x00);
    SPI_WriteData(0x1B);

    SPI_WriteComm(0xB6);    // Display Function Control
    SPI_WriteData(0x0A);
    SPI_WriteData(0xA2);

    /////////////////RGB REGIST////////
    SPI_WriteComm(0xB0);
    SPI_WriteData(0xE0);

    SPI_WriteComm(0xF6);
    SPI_WriteData(0x01);
    SPI_WriteData(0x00);
    SPI_WriteData(0x07);
    ///////////////////////////////////

    SPI_WriteComm(0xF2);    // 3Gamma Function Disable
    SPI_WriteData(0x00);

    SPI_WriteComm(0x26);    //Gamma curve selected
    SPI_WriteData(0x01);

    SPI_WriteComm(0xE0);    //Set Gamma
    SPI_WriteData(0x0F);
    SPI_WriteData(0x23);
    SPI_WriteData(0x20);
    SPI_WriteData(0x0C);
    SPI_WriteData(0x0F);
    SPI_WriteData(0x09);
    SPI_WriteData(0x4E);
    SPI_WriteData(0XA8);
    SPI_WriteData(0x3D);
    SPI_WriteData(0x0B);
    SPI_WriteData(0x15);
    SPI_WriteData(0x06);
    SPI_WriteData(0x0E);
    SPI_WriteData(0x08);
    SPI_WriteData(0x00);

    SPI_WriteComm(0XE1);    //Set Gamma
    SPI_WriteData(0x00);
    SPI_WriteData(0x1C);
    SPI_WriteData(0x1F);
    SPI_WriteData(0x03);
    SPI_WriteData(0x10);
    SPI_WriteData(0x06);
    SPI_WriteData(0x31);
    SPI_WriteData(0x57);
    SPI_WriteData(0x42);
    SPI_WriteData(0x04);
    SPI_WriteData(0x0A);
    SPI_WriteData(0x09);
    SPI_WriteData(0x31);
    SPI_WriteData(0x37);
    SPI_WriteData(0x0F);

    SPI_WriteComm(0x36);
    SPI_WriteData(0x08);

    SPI_WriteComm(0x11);    //Exit Sleep
    mdelay(120);
    SPI_WriteComm(0x29);

    SPI_WriteComm(0xb0);
    SPI_WriteData(0x80);

    SPI_WriteComm(0xf6);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SPI_WriteData(0x06);

    SPI_WriteComm(0xB5);
    SPI_WriteData(0x02);
    SPI_WriteData(0x02);
    SPI_WriteData(0x0A);
    SPI_WriteData(0x14);
}
