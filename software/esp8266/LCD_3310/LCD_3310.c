/*************************************************************************
 *
 *    Driver for the Nokia 3310 LCD
 *
 **************************************************************************/
#include <Arduino.h>
#include "LCD_3310.h"
#include "font5x8.h"

// simple delays
static void Delay(volatile unsigned long a)
{
    while (a != 0) a--;
}

static void Delayc(volatile unsigned char a)
{
    while (a != 0) a--;
}

/* TO IMPLEMENT YOUR VERSION OF THE DRIVER YOU'LL HAVE TO EDIT THIS SECTION ONLY */


        #define LCD_MOSI_MAKE_OUT()     pinMode (13, OUTPUT)       // MOSI pin #13
	#define LCD_MOSI_HIGH()         digitalWrite (13, 1)
	#define LCD_MOSI_LOW()          digitalWrite (13, 0)

        #define LCD_SCK_MAKE_OUT()      pinMode (14, OUTPUT)       // CLK  pin #14
	#define LCD_SCK_HIGH()          digitalWrite (14, 1)
	#define LCD_SCK_LOW()           digitalWrite (14, 0)

        #define LCD_CS_MAKE_OUT()       pinMode (15, OUTPUT)       // CS   pin #15
	#define LCD_CS_HIGH()           digitalWrite (15, 1)
	#define LCD_CS_LOW()            digitalWrite (15, 0)

        #define LCD_RES_MAKE_OUT()      pinMode (5, OUTPUT)      // SCL  pin #5
	#define LCD_RES_HIGH()          digitalWrite (5, 1)	
	#define LCD_RES_LOW()           digitalWrite (5, 0)   

        #define LCD_CD_MAKE_OUT()       pinMode (0, OUTPUT)        // SDA  pin #0
	#define LCD_CD_HIGH()           digitalWrite (0, 1)
	#define LCD_CD_LOW()            digitalWrite (0, 0)

#define SEND_BYTE_SPI()                     \
        {                                   \
                for(i = 0; i < 8; i++)      \
                {                           \
                    if(data & 0x80)         \
                    {                       \
                        LCD_MOSI_HIGH();    \
                    }                       \
                    else                    \
                    {                       \
                        LCD_MOSI_LOW();     \
                    }                       \
                    Delay(1);               \
                    LCD_SCK_LOW();          \
                    Delay(1);               \
                    LCD_SCK_HIGH();         \
                                            \
                    data <<= 1;             \
                }                           \
        }

static void Initialize_SPI(void)
{
    // Initialize SPI Interface pins as GPIOs
    LCD_MOSI_MAKE_OUT();
    LCD_SCK_MAKE_OUT();

    LCD_SCK_HIGH();
    LCD_MOSI_HIGH();
}

/* END OF SECTION */


#define LCD_START_LINE_ADDR	(66-2)

#if LCD_START_LINE_ADDR	> 66
#error "Invalid LCD starting line address"
#endif

// LCD memory index
unsigned int LcdMemIdx;

// represent LCD matrix
char LcdMemory[LCD_CACHE_SIZE];

/****************************************************************************/
/*  Initialize LCD Controller                                               */
/*  Function : LCDInit                                                      */
/*      Parameters                                                          */
/*          Input   :  Nothing                                              */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDInit(void)
{
    // Initialize SPI Interface
    Initialize_SPI();

    // set pin directions
    LCD_CS_MAKE_OUT();
    LCD_CS_HIGH();
    LCD_CD_MAKE_OUT();
    LCD_RES_MAKE_OUT();

    // Toggle reset pin
    LCD_RES_LOW();
    Delay(1000);
    LCD_RES_HIGH();
    Delay(1000);

    // Send sequence of command
    LCDSend(0x21, SEND_CMD); // LCD Extended Commands.
    LCDSend(0xC8, SEND_CMD); // Set LCD Vop (Contrast). 0xC8
    LCDSend(0x04 | !!(LCD_START_LINE_ADDR & (1u << 6)), SEND_CMD); // Set Temp S6 for start line
    LCDSend(0x40 | (LCD_START_LINE_ADDR & ((1u << 6) - 1)), SEND_CMD); // Set Temp S[5:0] for start line
    //LCDSend( 0x13, SEND_CMD );  // LCD bias mode 1:48.
    LCDSend(0x12, SEND_CMD); // LCD bias mode 1:68.
    LCDSend(0x20, SEND_CMD); // LCD Standard Commands, Horizontal addressing mode.
    //LCDSend( 0x22, SEND_CMD );  // LCD Standard Commands, Vertical addressing mode.
    LCDSend(0x08, SEND_CMD); // LCD blank
    LCDSend(0x0C, SEND_CMD); // LCD in normal mode.

    // Clear and Update
    LCDClear();
    LCDUpdate();
}

/****************************************************************************/
/*  Reset LCD 	                                                            */
/*  Function : LCDReset                                                     */
/*      Parameters                                                          */
/*          Input   :  Resets the LCD module                                */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDReset(void)
{

    // Close SPI module - optional
    // NOT DONE

    LCD_RES_LOW();
}

/****************************************************************************/
/*  Update LCD                                                              */
/*  Function : LCDUpdate                                                    */
/*      Parameters                                                          */
/*          Input   :  sends buffer data to the LCD                         */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDUpdate(void)
{
    int x, y;

    for (y = 0; y < 48 / 8; y++)
    {
        LCDSend(0x80, SEND_CMD);
        LCDSend(0x40 | y, SEND_CMD);
        for (x = 0; x < 84; x++)
        {
            LCDSend(LcdMemory[y * 84 + x], SEND_CHR);
        }
    }
}
/****************************************************************************/
/*  Send to LCD                                                             */
/*  Function : LCDSend                                                      */
/*      Parameters                                                          */
/*          Input   :  data and  SEND_CHR or SEND_CMD                       */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDSend(char data, unsigned char cd)
{
    int i;
    LCD_CS_LOW();

    if (cd == SEND_CHR)
    {
        LCD_CD_HIGH();
    }
    else
    {
        LCD_CD_LOW();
    }

    // send data over SPI
    SEND_BYTE_SPI();

    LCD_CS_HIGH();
}


/****************************************************************************/
/*  Clear LCD                                                               */
/*  Function : LCDClear                                                     */
/*      Parameters                                                          */
/*          Input   :  Nothing                                              */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDClear(void)
{
    int i;

    // loop all cache array
    for (i = 0; i < LCD_CACHE_SIZE; i++)
    {
        LcdMemory[i] = 0x00;
    }
}

/****************************************************************************/
/*  Write char at x position on y row                                       */
/*  Function : LCDChrXY                                                     */
/*      Parameters                                                          */
/*          Input   :  position, row, char                                  */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDChrXY(unsigned char x, unsigned char y, char ch, unsigned char inv)
{
    unsigned int index = 0;
    unsigned int i = 0;
    const unsigned char *font = get_font5x8(ch);

    // check for out off range
    if (x > LCD_X_RES) return;
    if (y > LCD_Y_RES) return;

    index = (unsigned int) x + (unsigned int) y * 84;

    for (i = 0; i < 5; i++)
    {
	if (inv)
		LcdMemory[index++] = ~font[i];
	else 
		LcdMemory[index++] = font[i];
    }
    if (inv)
	LcdMemory[index] = 0xff;
    else
	LcdMemory[index] = 0x00;
}

/****************************************************************************/
/*  Write 10x16 char at x position on y row                                       */
/*  Function : LCDChrXY                                                     */
/*      Parameters                                                          */
/*          Input   :  position, row, char                                  */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDMediumChrXY(unsigned char x, unsigned char y, char ch, unsigned char inv)
{
    unsigned int index = 0;
    unsigned int i = 0;
    const unsigned char *font = get_font10x16(ch);

    // check for out off range
    if (x > LCD_X_RES) return;
    if (y > LCD_Y_RES) return;

    index = (unsigned int) x + (unsigned int) y * 84;

    for (i = 0; i < 20; i += 2)
    {
	if (inv)
		LcdMemory[index++] = ~(font[i]);
	else
		LcdMemory[index++] = font[i];
    }

    index = (unsigned int) x + (unsigned int) (y + 1) * 84;

    for (i = 1; i < 20; i += 2)
    {
	if (inv)
		LcdMemory[index++] = ~(font[i]);
	else
		LcdMemory[index++] = font[i];
    }

}

void LCDPixelXY(unsigned char x, unsigned char y)
{
    unsigned int index = 0;
    unsigned int i = 0;
    
    // check for out off range
    if ((x > LCD_X_RES)||(x < 0)) return;
    if ((y > LCD_Y_RES)||(y < 0)) return;

    index = (unsigned int) x + ((unsigned int) (y/8))*84 ;

    LcdMemory[index] |= 1<<(y%8);
}

void LCDLine (int x1, int y1, int x2, int y2) {      //draw a line
   int dx, dy, sx, sy, err, e2;
   dx = abs (x2-x1);
   dy = abs (y2-y1);
   if (x1<x2) sx = 1;
      else sx = -1;
   if (y1<y2) sy = 1;
      else sy = -1;
   err = dx-dy;
   do {
      LCDPixelXY (x1, y1);
      if ((x1 == x2) && (y1 == y2))
         break;
      e2 = 2*err;
      if (e2 > -dy) {
         err = err - dy;
    x1 = x1+sx;
      }
      if (e2 < dx) {
         err = err + dx;
     y1 = y1 + sy;
      }
   } while (1);
  return;
}

void LCDRectangle (int x1, int y1, int x2, int y2) {  //draw a rectangle
   LCDLine (x1, y1, x1, y2);
   LCDLine (x1, y1, x2, y1);
   LCDLine (x2, y1, x2, y2);
   LCDLine (x1, y2, x2, y2);

   return;
}

void LCDSolidRectangle (int x1, int y1, int x2, int y2) {  //draw a solid rectangle
  int i = 0;
   if (x2>x1)
      for (i=x1; i<=x2;i++)
         LCDLine (i, y1, i, y2);
   else for (i=x2; i<=x1;i++)
         LCDLine (i, y1, i, y2);
   return;
}

void LCD4EllipsePoints (int CX, int CY, int X, int Y) {  //function needed for drawing an ellipse
   LCDPixelXY (CX+X, CY+Y);
   LCDPixelXY (CX-X, CY+Y);
   LCDPixelXY (CX-X, CY-Y);
   LCDPixelXY (CX+X, CY-Y);
   return;
}

void LCDEllipse (int CX, int CY, int XRadius, int YRadius) {   //draw an ellipse & fix radius if negative
   int X, Y, XChange, YChange, EllipseError, TwoASquare, TwoBSquare, StoppingX, StoppingY;
   if (XRadius<0) XRadius=-XRadius;
   if (YRadius<0) YRadius=-YRadius;

   TwoASquare = 2 * XRadius*XRadius;
   TwoBSquare = 2 * YRadius*YRadius;
   X = XRadius;
   Y = 0;
   XChange = YRadius*YRadius * (1-2*XRadius);
   YChange = XRadius*XRadius;
   EllipseError = 0;
   StoppingX = TwoBSquare*XRadius;
   StoppingY = 0;

   while (StoppingX >= StoppingY) {          // 1st set of points, y'> -1
      LCD4EllipsePoints (CX, CY, X, Y);
      Y++;
      StoppingY = StoppingY + TwoASquare;
      EllipseError = EllipseError + YChange;
      YChange = YChange + TwoASquare;
      if ((2*EllipseError + XChange) > 0) {
     X--;
     StoppingX = StoppingX - TwoBSquare;
     EllipseError = EllipseError + XChange;
     XChange = XChange + TwoBSquare;
   }}

   X = 0;
   Y = YRadius;
   XChange = YRadius*YRadius;
   YChange = XRadius*XRadius * (1-2*YRadius);
   EllipseError = 0;
   StoppingX = 0;
   StoppingY = TwoASquare * YRadius;

   while (StoppingX <= StoppingY) {        // 2nd set of points, y'< -1
      LCD4EllipsePoints (CX, CY, X, Y);
      X++;
      StoppingX = StoppingX + TwoBSquare;
      EllipseError = EllipseError + XChange;
      XChange = XChange + TwoBSquare;
      if ((2*EllipseError + YChange) > 0) {
         Y--;
     StoppingY = StoppingY - TwoASquare;
     EllipseError = EllipseError + YChange;
     YChange = YChange + TwoASquare;
   }}

   return;
}

void LCDCircle (int x, int y, int r) {   //draw a circle
   LCDEllipse (x, y, r, r);
   return;
}

void LCDTriangle (int x1, int y1, int x2, int y2, int x3, int y3) {   //draw a triangle
   LCDLine (x1, y1, x2, y2);
   LCDLine (x2, y2, x3, y3);
   LCDLine (x3, y3, x1, y1);
   return;
}

/****************************************************************************/
/*  Set LCD Contrast                                                        */
/*  Function : LcdContrast                                                  */
/*      Parameters                                                          */
/*          Input   :  contrast                                             */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDContrast(unsigned char contrast)
{

    //  LCD Extended Commands.
    LCDSend(0x21, SEND_CMD);

    // Set LCD Vop (Contrast).
    LCDSend(0x80 | contrast, SEND_CMD);

    //  LCD Standard Commands, horizontal addressing mode.
    LCDSend(0x20, SEND_CMD);
}


/****************************************************************************/
/*  Send string to LCD                                                      */
/*  Function : LCDStr                                                       */
/*      Parameters                                                          */
/*          Input   :  row, text, inversion                                 */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDStr(unsigned char x, unsigned char row, const char *dataPtr, unsigned char inv, unsigned char size)
{

    // loop to the and of string
    while (*dataPtr)
    {
	if (size == 5) {
            LCDChrXY(x, row, *dataPtr, inv);
	    x += 6;
	} else if (size == 10) {
            LCDMediumChrXY(x, row, *dataPtr, inv);
	    x += 10;
	}
        dataPtr++;
    }

    LCDUpdate();
}
