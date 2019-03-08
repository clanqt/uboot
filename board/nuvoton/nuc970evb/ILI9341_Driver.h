
#define DCx_ILI9341 DATA_CMD_ILI9341

//**************************************************************
//**************************************************************
//	Contents : ILI9341 Driver
//
//  Purpose  : TFT Control in 71xx
//
//  Date     : 10 March 2012
//  Status   : v1.00
//
//  Limitations and
//  errors   :  For proper functioning SPI should be configured in 6MHz.
//
//  Company  : Vaaraahi Embedded
//  Author   : AR Jithesh
//
//
//**************************************************************
//**************************************************************

void WriteSPIData(unsigned char dat);
void WriteSPICmd(unsigned char cmd);
void Init_ILI9341(void);
void SetDisplayRGBMode(void);
void TFT_exitsleep(void);
void TFT_reset(void);


	#define LCD_ILI9341_CMD WriteSPICmd
	#define LCD_ILI9341_Parameter WriteSPIData
	



//********************************************************************************
//**************************************************************
//**************************************************************
//  Designer    : AR JITHESH
//  Company     : Vaaraahi Embedded
//  Date        : 20March2012
//  Last Revised: -
//  Description	: Transfers the 8bit Data to the display MCU.
//**************************************************************
//**************************************************************
 void WriteSPIData(unsigned char dat)
 { 
	// Send data byte to LCD via SPI
	unsigned char dummy;
    dummy = SPI2BUF;  // force clearance of buffer full flag
    PIC_TFT_nChipSelect = 0;
    DCx_ILI9341 = 1;
    SPI2BUF = dat;  // make PIC H/W do the work (because it's much faster)
    while( !SPI2STATbits.SPIRBF); // wait for transfer to complete
    dummy = SPI2BUF; // force clearance of buffer full flag
    PIC_TFT_nChipSelect = 1;  // deselect chip the cLCD
 } // WriteSPIData
 
 

 
 
//********************************************************************************
//**************************************************************
//**************************************************************
//  Designer    : AR JITHESH
//  Company     : Vaaraahi Embedded
//  Date        : 20March2012
//  Last Revised: -
//  Description	: Transfers 8bit Command to the Display MCU.
//**************************************************************
//**************************************************************
 void WriteSPICmd(unsigned char cmd)
 { 
	// Send command byte to LCD via SPI
	unsigned char dummy;
	dummy = SPI2BUF;  // force clearance of buffer full flag
	PIC_TFT_nChipSelect = 0; //_LATA9 = 0;  // chip select the cLCD
	DCx_ILI9341 = 0;
	SPI2BUF = cmd;  // make PIC H/W do the work (because it's much faster)
	while( !SPI2STATbits.SPIRBF); // wait for transfer to complete
	dummy = SPI2BUF; // force clearance of buffer full flag
	PIC_TFT_nChipSelect = 1; //_LATA9 = 1;  // deselect chip the cLCD
 } // WriteSPICmd
 /////////////////////////////////////////////////////////////////////
 
 
 //********************************************************************************
//**************************************************************
//**************************************************************
//  Designer    : AR JITHESH
//  Company     : Vaaraahi Embedded
//  Date        : 20March2012
//  Last Revised: -
//  Description	: Transfers 16bitPixelData to the Display GRAM.
//**************************************************************
//**************************************************************
// void Write_Pixel_16bit(unsigned char msb, unsigned char lsb)
// { 
//	// Send data byte to LCD via SPI
//	unsigned char dummy;
//    dummy = SPI2BUF;  // force clearance of buffer full flag
//    PIC_TFT_nChipSelect = 0;
//    DCx_ILI9341 = 1;
//    SPI2BUF = msb;  // make PIC H/W do the work (because it's much faster)
//    while( !SPI2STATbits.SPIRBF); // wait for transfer to complete
//    dummy = SPI2BUF; // force clearance of buffer full flag
//    SPI2BUF = lsb;  // make PIC H/W do the work (because it's much faster)
//    while( !SPI2STATbits.SPIRBF); // wait for transfer to complete
//    dummy = SPI2BUF;
//    PIC_TFT_nChipSelect = 1;  // deselect chip the cLCD
// } // 


//********************************************************************************
//**************************************************************
//**************************************************************
//  Designer    : AR JITHESH
//  Company     : Vaaraahi Embedded
//  Date        : 20March2012
//  Last Revised: -
//  Description	: Initialises the display screen.
//**************************************************************
//**************************************************************

void TFT_exitsleep(void)
{
        LCD_ILI9341_CMD(0x13);//
		LCD_ILI9341_CMD(0x11); //Exit Sleep
		delay_msec(120);
		LCD_ILI9341_CMD(0x29); //Display on
		LCD_ILI9341_CMD(0x13);//
}
void TFT_reset(void)
{
        PWM_TFT_Backlight=0;
		/* Reset LCD Drivers */
		PIC_TFT_nRST=1;
	    delay_msec(10);
		PIC_TFT_nRST=0;
	    delay_msec(100);    	
		PIC_TFT_nRST = 1;
		delay_msec(200); //Delay l0ms I! This delay time is necessary
	//	PWM_TFT_Backlight=1;
}
void Init_ILI9341(void)
{
        unsigned char RD_DATA_TFT[5];
        unsigned char dummy;
		//******* Start Initial Sequence
		LCD_ILI9341_CMD(0xCB);
			LCD_ILI9341_Parameter (0x39);
			LCD_ILI9341_Parameter (0x2C);
			LCD_ILI9341_Parameter (0x00);
			LCD_ILI9341_Parameter (0x34);
			LCD_ILI9341_Parameter (0x02);
			
		LCD_ILI9341_CMD(0xCF);
			LCD_ILI9341_Parameter (0x00);
			LCD_ILI9341_Parameter (0xC1);
			LCD_ILI9341_Parameter (0X30);
			
		LCD_ILI9341_CMD(0xE8);
			LCD_ILI9341_Parameter (0x85);
			LCD_ILI9341_Parameter (0x00);
			LCD_ILI9341_Parameter (0x78);
			
		LCD_ILI9341_CMD(0xEA);
			LCD_ILI9341_Parameter (0x00);
			LCD_ILI9341_Parameter (0x00);
			
		LCD_ILI9341_CMD(0xED);
			LCD_ILI9341_Parameter (0x64);
			LCD_ILI9341_Parameter (0x03);
			LCD_ILI9341_Parameter (0X12);
			LCD_ILI9341_Parameter (0X81);
			
		LCD_ILI9341_CMD(0xF7); 
			LCD_ILI9341_Parameter (0x20);
			
		LCD_ILI9341_CMD(0xC0); //Power control
			LCD_ILI9341_Parameter (0x23); //VRH[5:0]
			
		LCD_ILI9341_CMD(0xCl); //Power control
			LCD_ILI9341_Parameter (0x10); //SAP[2:0];BT[3:0]
			
		LCD_ILI9341_CMD(0xC5); //VCM control
			LCD_ILI9341_Parameter (0x2B);
			LCD_ILI9341_Parameter (0x2B);
			
		LCD_ILI9341_CMD(0xC7); //VCM control2
			LCD_ILI9341_Parameter (0xC0);
		
		LCD_ILI9341_Parameter (0x02);
			
		
		//*************************************************
		LCD_ILI9341_CMD(0x36); // Memory Access Control
			LCD_ILI9341_Parameter (0x48);///48//28//24 working
		//*************************************************	
		LCD_ILI9341_CMD(0x21); //  //Inversion control
		//*************************************************
		
		LCD_ILI9341_CMD(0xBl);
			LCD_ILI9341_Parameter (0x1B);

		LCD_ILI9341_CMD(0xB6); //Display Function Control
			LCD_ILI9341_Parameter (0x12);//02
			LCD_ILI9341_Parameter (0x02);//02
			LCD_ILI9341_Parameter (0x27);

		LCD_ILI9341_CMD(0xF2); // 3Gamma Function Disable
			LCD_ILI9341_Parameter (0x00);
			
		 LCD_ILI9341_CMD(0x2a);  // column select
	
		LCD_ILI9341_CMD(0x26); //Gamma curve selected
			LCD_ILI9341_Parameter (0x0l);
			
		LCD_ILI9341_CMD(0xE0); //Set Gamma
			LCD_ILI9341_Parameter (0x0F);
			LCD_ILI9341_Parameter (0x30);
			LCD_ILI9341_Parameter (0x2B);
			LCD_ILI9341_Parameter (0x0C);
			LCD_ILI9341_Parameter (0x0E);
			LCD_ILI9341_Parameter (0x08);
			LCD_ILI9341_Parameter (0x4E);
			LCD_ILI9341_Parameter (0xFl);
			LCD_ILI9341_Parameter (0x37);
			LCD_ILI9341_Parameter (0x07);
			LCD_ILI9341_Parameter (0x10);
			LCD_ILI9341_Parameter (0x03);
			LCD_ILI9341_Parameter (0x0E);
			LCD_ILI9341_Parameter (0x09);
			LCD_ILI9341_Parameter (0x00);
			
		LCD_ILI9341_CMD(0xE1); //Set Gamma
			LCD_ILI9341_Parameter (0x00);
			LCD_ILI9341_Parameter (0x0E);
			LCD_ILI9341_Parameter (0x14);
			LCD_ILI9341_Parameter (0x03);
			LCD_ILI9341_Parameter (0x11);
			LCD_ILI9341_Parameter (0x07);
			LCD_ILI9341_Parameter (0x31);
			LCD_ILI9341_Parameter (0xC1);
			LCD_ILI9341_Parameter (0x48);
			LCD_ILI9341_Parameter (0x08);
			LCD_ILI9341_Parameter (0x0F);
			LCD_ILI9341_Parameter (0x0C);
			LCD_ILI9341_Parameter (0x31);
			LCD_ILI9341_Parameter (0x36);
			LCD_ILI9341_Parameter (0x0F);			

		
		SetDisplayRGBMode();	
		
		TFT_exitsleep();		
					
        /***Added to check if the display is properly initialised ***////
//		RD_WriteSPICmd(0x09);		
//		dummy=SPI2BUF; 
//		RD_WriteSPIData(0x00);
//		RD_DATA_TFT[0]=SPI2BUF;
//		RD_WriteSPIData(0x00);
//		RD_DATA_TFT[1]=SPI2BUF;
//		RD_WriteSPIData(0x61);
//		RD_DATA_TFT[2]=SPI2BUF;
//		RD_WriteSPIData(0x00);
//		RD_DATA_TFT[3]=SPI2BUF;
//		RD_WriteSPIData(0x00);
//		RD_DATA_TFT[4]=SPI2BUF;
//		
//		if(((RD_DATA_TFT[0]== 0xD2) && (RD_DATA_TFT[1]==0x31)))return;
//		else Init_ILI9341();
		

} 


//void Display_MachineID(void)
//{
//	unsigned char MachineID_BUF[20];
//	unsigned int MachineID,LIu_IDData;
//	unsigned short DATA;
//	register unsigned char Lcu_LoopCnt=0,Lcu_BuffCnt=0,datacnt=0,linecnt=0,k=0;
//	unsigned char* MACHINEID_PTR, * MACHINEID;
//	unsigned char* Src_Add;	
//
//	unsigned short PixelData=0,i,j,x,y,PixelSelect=0;
//	unsigned char PixelBit,ExtraPixels,PixelWidth,ShiftByte;
//	
//	unsigned short x_start=50,y_start=150;
//	unsigned char width=13;	
//	
//	unsigned short TEMP=0,CHAR=0;
//
//	MACHINEID_PTR= Machine_Id_Address;
//
//	
//	for(Lcu_LoopCnt=0;Lcu_LoopCnt<5;Lcu_LoopCnt++)
//	{
//		MachineID=*(MACHINEID_PTR+Lcu_LoopCnt);
//		MachineID_BUF[Lcu_BuffCnt++]=MachineID>>24;
//		MachineID_BUF[Lcu_BuffCnt++]=MachineID>>16;
//		MachineID_BUF[Lcu_BuffCnt++]=MachineID>>8;
//		MachineID_BUF[Lcu_BuffCnt++]=MachineID;
//	}
//
//	
//	for (datacnt=0; datacnt<20; datacnt++)
//	{
//		//MACHINEID = & MachineID_BUF[datacnt];
//		y_start=150;
//		x_start+=70;
//		for(linecnt=0;linecnt<13;linecnt++)
//		{
//			TEMP='A';//MachineID_BUF[datacnt]
//			CHAR=((TEMP-0x20)*13)+linecnt;
//			
//			DATA=ter_114n9[CHAR];
//			
//			LCD_ILI9341_CMD(0x2a);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(x_start);
//				LCD_ILI9341_Parameter(0x01);
//				LCD_ILI9341_Parameter(0x40);
//			LCD_ILI9341_CMD(0x2b);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(y_start);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(0xf0);
//			LCD_ILI9341_CMD(0x2c);
//			
//			y_start++;
//			
//			ShiftByte = 0x80;
//			
//						
//			for(k=0;k<8;k++)
//			{
//						
//						PixelBit = DATA & ShiftByte;
//						ShiftByte = ShiftByte >> 1;
//						if(PixelBit>0) 
//						{
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							//LCD_ILI9341_Parameter(0xFF);
//						}
//						else 
//						{
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							//LCD_ILI9341_Parameter(0x00);
//						}
//			
//			}
//		}
//		
//	}
//	}
//		
//		
//	

//********************************************************************************

void SetDisplayRGBMode(void){
	
	  LCD_ILI9341_CMD(0x3a);//  rgb & cpu 18 0x66 /16 0x55 bit select
		            LCD_ILI9341_Parameter(0x66);
	  LCD_ILI9341_CMD(0xf6); //interface control
	                LCD_ILI9341_Parameter(0x01);
	                LCD_ILI9341_Parameter(0x01);
	                LCD_ILI9341_Parameter(0x06); //06-RGB  02-Internal  0A-vsyc
	
//	  LCD_ILI9341_CMD(0x2A);
//				LCD_ILI9341_Parameter (0x00);
//				LCD_ILI9341_Parameter (0x14);
//				LCD_ILI9341_Parameter (0x01);
//				LCD_ILI9341_Parameter (0x53);
//			LCD_ILI9341_CMD(0x2B);
//				LCD_ILI9341_Parameter (0x00);
//				LCD_ILI9341_Parameter (0x00);
//				LCD_ILI9341_Parameter (0x00);
//				LCD_ILI9341_Parameter (0xEF);
				
	  LCD_ILI9341_CMD(0xb0); //         
	                LCD_ILI9341_Parameter(0xCC); //C0-DE Mode,  E0-Sync Mode  B1-Direct/Mem
	                
	  delay_msec(10);   
}	 

//********************************************************************************    


//********************************************************************************
//**************************************************************
//**************************************************************
//  Designer    : AR JITHESH
//  Company     : Vaaraahi Embedded
//  Date        : 20March2012
//  Last Revised: -
//  Description	: Fills the Entire Screen.
//**************************************************************
//**************************************************************
//void Fill_ILI9341Screen(unsigned char blue, unsigned char red, unsigned char green ){
//	unsigned int i;
//	blue&=0b11111100; red&=0b11111100; green&=0b11111100;
//	LCD_ILI9341_CMD(0x2a);
//		LCD_ILI9341_Parameter(0x00);
//		LCD_ILI9341_Parameter(0x00);
//		LCD_ILI9341_Parameter(0x01);
//		LCD_ILI9341_Parameter(0x40);
//	LCD_ILI9341_CMD(0x2b);
//		LCD_ILI9341_Parameter(0x00);
//		LCD_ILI9341_Parameter(0x00);
//		LCD_ILI9341_Parameter(0x00);
//		LCD_ILI9341_Parameter(0xf0);
//	LCD_ILI9341_CMD(0x2c);
//	for(i=0;i<76800;i++){
//		LCD_ILI9341_Parameter(blue);
//		LCD_ILI9341_Parameter(red);
//		LCD_ILI9341_Parameter(green);
//	}	
//}	

//********************************************************************************

//void Display_SPI_Booting(unsigned char* Image,unsigned short width ,unsigned short height,unsigned short y_start,unsigned short x_start)
//{	
//	unsigned short PixelData=0,i,j,k,x,y,PixelSelect=0;
//	unsigned char PixelBit,ExtraPixels,PixelWidth,ShiftByte;
////	unsigned short x_start,y_start;
////		width = 187;
////		height =18;
//		PixelWidth = 8;
//		ExtraPixels = width%8;
//		
////		y_start = 125;
////		x_start = 70;
//		
//		for(i=0;i<height;i++){
//			
//			LCD_ILI9341_CMD(0x2a);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(x_start);
//				LCD_ILI9341_Parameter(0x01);
//				LCD_ILI9341_Parameter(0x40);
//			LCD_ILI9341_CMD(0x2b);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(y_start);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(0xf0);
//			LCD_ILI9341_CMD(0x2c);
//			
//			y_start++;
//			
//			for(j=0;j<((width%8!=0)?((width/8)+1):(width/8));j++){
//				PixelData =*(Image+PixelSelect);
//				ShiftByte = 0x80;
//				if( j<((width%8!=0)?(width/8):((width/8)-1)) ){
//					for(k=0;k<PixelWidth;k++){
//						PixelBit = PixelData & ShiftByte;
//						ShiftByte = ShiftByte >> 1;
//						if(PixelBit>0) {
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							//LCD_ILI9341_Parameter(0xFF);
//						}
//						else {
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							//LCD_ILI9341_Parameter(0x00);
//						}
//					}	
//				}
//				else{
//					for(k=0;k<ExtraPixels;k++){
//						
//						PixelBit = PixelData & ShiftByte;
//						ShiftByte = ShiftByte >> 1;
//						if(PixelBit>0) {
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							//LCD_ILI9341_Parameter(0xFF);
//						}
//						else {
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							//LCD_ILI9341_Parameter(0x00);
//						}	
//					}	
//				}
//				PixelSelect+=1;
//			}
//				
//		//	LCD_ILI9341_CMD(0x00);
//		}
//}						


//********************************************************************************

//void Display_SPI_Shutting(void){
//	unsigned short width,height,PixelData=0,i,j,k,x,y,PixelSelect=0;
//	unsigned char PixelBit,ExtraPixels,PixelWidth,ShiftByte;
//	unsigned short x_start,y_start;
//		width = 140;
//		height =30;
//		PixelWidth = 8;
//		ExtraPixels = width%8;
//		
//		y_start = 100;
//		x_start = 75;
//		
//		for(i=0;i<height;i++){
//			
//			LCD_ILI9341_CMD(0x2a);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(x_start);
//				LCD_ILI9341_Parameter(0x01);
//				LCD_ILI9341_Parameter(0x40);
//			LCD_ILI9341_CMD(0x2b);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(y_start);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(0xf0);
//			LCD_ILI9341_CMD(0x2c);
//			
//			y_start++;
//			
//			for(j=0;j<((width%8!=0)?((width/8)+1):(width/8));j++){
//				PixelData = (shutting_down_img[PixelSelect]);
//				ShiftByte = 0x80;
//				if( j<((width%8!=0)?(width/8):((width/8)-1)) ){
//					for(k=0;k<PixelWidth;k++){
//						PixelBit = PixelData & ShiftByte;
//						ShiftByte = ShiftByte >> 1;
//						if(PixelBit>0) {
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							//LCD_ILI9341_Parameter(0xFF);
//						}
//						else {
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							//LCD_ILI9341_Parameter(0x00);
//						}
//					}	
//				}
//				else{
//					for(k=0;k<ExtraPixels;k++){
//						
//						PixelBit = PixelData & ShiftByte;
//						ShiftByte = ShiftByte >> 1;
//						if(PixelBit>0) {
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							LCD_ILI9341_Parameter(0xFF);
//							//LCD_ILI9341_Parameter(0xFF);
//						}
//						else {
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							LCD_ILI9341_Parameter(0x00);
//							//LCD_ILI9341_Parameter(0x00);
//						}	
//					}	
//				}
//				PixelSelect+=1;
//			}
//			LCD_ILI9341_CMD(0x00);
//		}
//}						


//********************************************************************************


//void Display_Vaaraahi_Logo(void){
//	
//	unsigned short width, height, x_start, y_start, PixelSelect = 0, PixelData;
//	unsigned char Blue, Red, Green;
//	unsigned int i,j;
//	
//	width =109;//58; 
//	height =36;//68;
//	x_start =120; y_start =70;
//	
//	for(i=0;i<height;i++){
//			
//			LCD_ILI9341_CMD(0x2a);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(x_start);
//				LCD_ILI9341_Parameter(0x01);
//				LCD_ILI9341_Parameter(0x40);
//			LCD_ILI9341_CMD(0x2b);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(y_start);
//				LCD_ILI9341_Parameter(0x00);
//				LCD_ILI9341_Parameter(0xf0);
//			LCD_ILI9341_CMD(0x2c);
//			
//			for(j=0;j<width;j++){
//				PixelData = (logonew[PixelSelect]);
//				Blue = (PixelData & 0xF800)>>8;
//				Red = (PixelData & 0x07E0)>>3;
//				Green = PixelData & 0x001F;
//
//				LCD_ILI9341_Parameter(Blue);
//				LCD_ILI9341_Parameter(Red);
//				LCD_ILI9341_Parameter(Green);
//				PixelSelect+=1;
//			}
//			y_start++;
//			LCD_ILI9341_CMD(0x00);
//		}
//	
//	
//}	

//********************************************************************************

          


/******************************************************************************
 * Function:        void TFT_Display_String(unsigned short St_Add_Xaxis,unsigned char St_Add_Yaxis,unsigned char *Display_Data,
 					unsigned char No_Of_Bytes,unsigned short Font_Colour,unsigned short Background_Colour)
 *
 * PreCondition:    SPI and TFT should be initialized
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        To Display a string in the TFT
 *
 * Note:            None
 *****************************************************************************/
//void TFT_Display_String(unsigned short St_Add_Xaxis,unsigned char St_Add_Yaxis,unsigned char *Display_Data,unsigned char No_Of_Bytes,unsigned short Font_Colour,unsigned short Background_Colour)
//{
//	unsigned int pixel_count,No_Of_Pixels=0;
//	unsigned short En_Add_Xaxis=0,Character_Data=0;
//	unsigned char En_Add_Yaxis=0,Font_Count,Font_height,Character_Pixel_Count=0,Pixel_Data=0;
//
//	En_Add_Xaxis=St_Add_Xaxis+(No_Of_Bytes*10)-1;
//	No_Of_Pixels=((En_Add_Xaxis-St_Add_Xaxis)+1)*(13);
//
//	WriteSPICmd(0x0052);WriteSPIData(St_Add_Xaxis);
//	WriteSPICmd(0x0053);WriteSPIData(En_Add_Xaxis);
//	
//	
//	St_Add_Yaxis=239-St_Add_Yaxis;
//	En_Add_Yaxis=St_Add_Yaxis-12;		/**height of the font minus 1*/
//
//	WriteSPICmd(0x0050);WriteSPIData(En_Add_Yaxis);
//	WriteSPICmd(0x0051);WriteSPIData(St_Add_Yaxis);
//
//	WriteSPICmd(0x0022);
//	for(Font_height=0;Font_height<13;Font_height++)
//	{
//		for(Font_Count=0;Font_Count<No_Of_Bytes;Font_Count++)
//		{
//			Character_Data=((Display_Data[Font_Count]-0x20)*13)+Font_height;
//		//	Character_Data=ter_114n9[Character_Data];
//			Character_Pixel_Count=15;
//			for(;Character_Pixel_Count>6;Character_Pixel_Count--)
//			{
//				Pixel_Data=	(Character_Data>>(Character_Pixel_Count-1))&0x01;
//				if(Pixel_Data==1)
//					WriteSPIData(Font_Colour);		
//				else
//					WriteSPIData(Background_Colour);		
//			}
//			WriteSPIData(Background_Colour);		
//		}	
//	}
//}