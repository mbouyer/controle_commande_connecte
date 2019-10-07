/**********************************************************************************/
/*                                                                                */
/*    Copyright (C) 2005 OLIMEX  LTD.                                             */
/*                                                                                */
/*    Module Name    :  LCD module                                                */
/*    File   Name    :  lcd.h                                                     */
/*    Revision       :  02.00                                                     */
/*    Date           :  2011/06/27 code clean-up                                  */
/*    Revision       :  01.00                                                     */
/*    Date           :  2006/01/26 initial version                                */
/*                                                                                */
/**********************************************************************************/
#ifndef _LCD_3310_H
#define _LCD_3310_H

#ifdef __cplusplus
 extern "C" {
#endif

/* definitions */
#define SEND_CMD                   0
#define SEND_CHR                   1

#define LCD_X_RES                  84
#define LCD_Y_RES                  48

#define PIXEL_OFF                  0
#define PIXEL_ON                   1
#define PIXEL_XOR                  2

#define FONT_1X                    1
#define FONT_2X                    2

// this is the buffer size
#define LCD_CACHE_SIZE             ((LCD_X_RES * LCD_Y_RES) / 8)



/****************************************************************************/
/*  Initialize LCD Controller                                               */
/*  Function : LCDInit                                                      */
/*      Parameters                                                          */
/*          Input   :  Nothing                                              */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDInit(void);

/****************************************************************************/
/*  Send to LCD                                                             */
/*  Function : LCDSend                                                      */
/*      Parameters                                                          */
/*          Input   :  data and  SEND_CHR or SEND_CMD                       */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDSend(char data, unsigned char cd);

/****************************************************************************/
/*  Update LCD memory                                                       */
/*  Function : LCDUpdate                                                    */
/*      Parameters                                                          */
/*          Input   :  Nothing                                              */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDUpdate ( void );

/****************************************************************************/
/*  Clear LCD                                                               */
/*  Function : LCDClear                                                     */
/*      Parameters                                                          */
/*          Input   :  Nothing                                              */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDClear(void);

/****************************************************************************/
/*  Write char at x position on y row                                       */
/*  Function : LCDChrXY                                                     */
/*      Parameters                                                          */
/*          Input   :  position, row, char, inv                             */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDChrXY (unsigned char x, unsigned char y, char ch, unsigned char inv );
void LCDMediumChrXY (unsigned char x, unsigned char y, char ch, unsigned char inv );

/****************************************************************************/
/*  Write char at x position on y row                                       */
/*  Function : LCDPixelXY                                                   */
/*      Parameters                                                          */
/*          Input   :  position, row                                        */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDPixelXY (unsigned char x, unsigned char y);

void LCDLine (int x1, int y1, int x2, int y2);
void LCDRectangle (int x1, int y1, int x2, int y2);
void LCDSolidRectangle (int x1, int y1, int x2, int y2);
void LCD4EllipsePoints (int CX, int CY, int X, int Y);
void LCDEllipse (int CX, int CY, int XRadius, int YRadius);
void LCDCircle (int x, int y, int r);
void LCDTriangle (int x1, int y1, int x2, int y2, int x3, int y3);

/****************************************************************************/
/*  Set LCD Contrast                                                        */
/*  Function : LcdContrast                                                  */
/*      Parameters                                                          */
/*          Input   :  contrast                                             */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDContrast(unsigned char contrast);

/****************************************************************************/
/*  Send string to LCD                                                      */
/*  Function : LCDStr                                                       */
/*      Parameters                                                          */
/*          Input   :  x, row, text, inversion, size                           */
/*          Output  :  Nothing                                              */
/****************************************************************************/
void LCDStr(unsigned char x, unsigned char row, const char *dataPtr, unsigned char inv, unsigned char size);

#ifdef __cplusplus
}
#endif

#endif // _LCD_3310_H
