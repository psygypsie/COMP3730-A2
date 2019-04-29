#include "Ass-02.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int characterPositionsX[10] = {15,47,79,111,143,175,207,239,271,303};	//X-Places in textbox. Maybe even these out (minus all by 5 or something).
static int characterSpots[10] = {0};
/*
 * Just writes over the entire text box with background color.
 * Also Resets the flags for the free position on the screen.
 *
 * */
static void ClearTextBox(){


	BSP_LCD_SetTextColor (0xFFFF);		//Text Color: White.
	BSP_LCD_FillRect (0, 0, 320, 46);	//Write over screen.
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.

	//Reset Flags.
	for(int i = 0; i<10; i++){
		characterSpots[i] = 0;
	}
}

/*
 *  Manages where characters may be written to in the TextBox.
 */
static int characterManager(){


	//Loop through and mark next available position.
	for(int i = 0; i < 10; i++){

		if(characterSpots[i] == 0){
			return i;
		}
	}

	//If we got to here then the screen is full. Put some sort of user feedback in here.
	//For now just clear textbox.
	//ClearTextBox();
	return 0;


}

void CalculatorInit (void)
{

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init ();
  BSP_LCD_DisplayOn ();
  BSP_TP_Init ();


  BSP_LCD_Clear (LCD_COLOR_WHITE);


  /*** Drawing Display: Consult Spreadsheet ***/


  /** DRAWING BOXES **/

  /* Numbers [0-9] */
  BSP_LCD_SetTextColor(0x00FF);
  BSP_LCD_FillRect (0, 49, 240, 192);

  /* Operations */
  BSP_LCD_SetTextColor(0xFF00);
  BSP_LCD_FillRect (241, 49, 79, 192);	// [+, -, x, %]
  BSP_LCD_SetTextColor(0x1685);
  BSP_LCD_FillRect (161, 193, 80, 48);	// [=]

  /* Clear Button  */
  BSP_LCD_SetTextColor(0xE0A2);
  BSP_LCD_FillRect (81, 193, 80, 48);	// [C]

  /* Draw Grid (Borders) */
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DrawHLine (0,47, 320);		//0a
  BSP_LCD_DrawHLine (0,48, 320);		//0b
  BSP_LCD_DrawHLine (0,95, 320);		//1a
  BSP_LCD_DrawHLine (0,96, 320);		//1b
  BSP_LCD_DrawHLine (0,143, 320);		//2a
  BSP_LCD_DrawHLine (0,144, 320);		//2c
  BSP_LCD_DrawHLine (0,191, 320);		//3a
  BSP_LCD_DrawHLine (0,192, 320);		//3b
  BSP_LCD_DrawHLine (0,239, 320);		//4a
  BSP_LCD_DrawHLine (0,240, 320);		//4b

  BSP_LCD_DrawVLine (79, 49, 192);		//0a
  BSP_LCD_DrawVLine (80, 49, 192);		//0b
  BSP_LCD_DrawVLine (159, 49, 192);		//1a
  BSP_LCD_DrawVLine (160, 49, 192);		//1b
  BSP_LCD_DrawVLine (239, 49, 192);		//2a
  BSP_LCD_DrawVLine (240, 49, 192);		//2b
  BSP_LCD_DrawVLine (319, 49, 192);		//3a
  BSP_LCD_DrawVLine (320, 49, 192);		//3b

  /** DRAWING CHARACTERS **/

  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);	//Text Color: Black
  BSP_LCD_SetFont (&Font24);				//Font Size: 24

  /* Col 0 */
  BSP_LCD_SetBackColor(0x00FF);				//Background Color: Blue
  BSP_LCD_DisplayChar (32, 61, '7');
  BSP_LCD_DisplayChar (32, 109, '4');
  BSP_LCD_DisplayChar (32, 157, '1');
  BSP_LCD_DisplayChar (32, 205, '0');

  /* Col 1 */
  BSP_LCD_SetBackColor(0x00FF);				//Background Color: Blue
  BSP_LCD_DisplayChar (114, 61, '8');
  BSP_LCD_DisplayChar (114, 109, '5');
  BSP_LCD_DisplayChar (114, 157, '2');
  BSP_LCD_SetBackColor(0xE0A2);				//Background Color: Red
  BSP_LCD_DisplayChar (114, 205, 'C');

  /* Col 2 */
  BSP_LCD_SetBackColor(0x00FF);				//Background Color: Blue
  BSP_LCD_DisplayChar (194, 61, '9');
  BSP_LCD_DisplayChar (194, 109, '6');
  BSP_LCD_DisplayChar (194, 157, '3');
  BSP_LCD_SetBackColor(0x1685);				//Background Color: Green
  BSP_LCD_DisplayChar (194, 205, '=');

  /* Col 3 */
  BSP_LCD_SetBackColor(0xFF00);				//Background Color: Yellow
  BSP_LCD_DisplayChar (274, 61, '+');
  BSP_LCD_DisplayChar (274, 109, '-');
  BSP_LCD_DisplayChar (274, 157, 'x');
  BSP_LCD_DisplayChar (274, 205, '%');





}

void CalculatorProcess (void)
{

  uint16_t linenum = 0;
  int charPos = characterManager();

  if (BSP_TP_GetDisplayPoint (&display) == 0)	//Reading in the touched points.
  {
	/*** If statements describe a box around touch zone corresponding to buttons. ***/
	BSP_LCD_SetBackColor(0xFFFF);				//Background Color: White
	BSP_LCD_SetTextColor (LCD_COLOR_BLACK);		//Text Color: Black.

	/** Column 1 [7,4,1,0] **/
    if (((display.x >= 0) && (display.x <= 80)))
    {
      /* 7 */
      if ((display.y >= 49) && (display.y < 96))
      {
    	 BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '7');	//Get X pos from array.
    	 characterSpots[charPos] = 1;									//Update available locations in textbox.
    	 HAL_Delay(500);												//Stops it from wigging out.
      }
      /* 4 */
      else if ((display.y >= 97) && (display.y <= 144))
      {
    	  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '4');	//Get X pos from array.
		  characterSpots[charPos] = 1;									//Update available locations in textbox.
		  HAL_Delay(500);	//Stops it from wigging out.
      }
      /* 1 */
      else if ((display.y >= 145) && (display.y <= 192))
      {
    	  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '1');	//Get X pos from array.
		  characterSpots[charPos] = 1;									//Update available locations in textbox.
		  HAL_Delay(500);	//Stops it from wigging out.
      }
      /* 0 */
      else if ((display.y >= 193) && (display.y <= 240))
      {
    	  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '0');	//Get X pos from array.
		  characterSpots[charPos] = 1;									//Update available locations in textbox.
		  HAL_Delay(500);	//Stops it from wigging out.
      }


    }
    /** Column 2 [8,5,2,C] **/
    else if (((display.x >= 81) && (display.x <= 160))){
          /* 8 */
		   if ((display.y >= 49) && (display.y < 96))
		   {
			 BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '8');	//Get X pos from array.
			 characterSpots[charPos] = 1;									//Update available locations in textbox.
			 HAL_Delay(500);												//Stops it from wigging out.
		   }
		   /* 5 */
		   else if ((display.y >= 97) && (display.y <= 144))
		   {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '5');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		   }
		   /* 2 */
		   else if ((display.y >= 145) && (display.y <= 192))
		   {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '2');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		   }
		   /* C */
		   else if ((display.y >= 193) && (display.y <= 240))
		  {
			 ClearTextBox();
			 HAL_Delay(500);
		  }


    }
    /** Column 2 [9,6,3,=] **/
    else if (((display.x >= 161) && (display.x <= 240))){
          /* 8 */
		   if ((display.y >= 49) && (display.y < 96))
		   {
			 BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '9');	//Get X pos from array.
			 characterSpots[charPos] = 1;									//Update available locations in textbox.
			 HAL_Delay(500);												//Stops it from wigging out.
		   }
		   /* 5 */
		   else if ((display.y >= 97) && (display.y <= 144))
		   {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '6');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		   }
		   /* 2 */
		   else if ((display.y >= 145) && (display.y <= 192))
		   {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '3');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		   }
		   /* C */
		   else if ((display.y >= 193) && (display.y <= 240))
		  {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '=');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		  }


    }
    /** Column 2 [+,-,x,%] **/
	else if (((display.x >= 241) && (display.x <= 320))){
		  /* 8 */
		   if ((display.y >= 49) && (display.y < 96))
		   {
			 BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '+');	//Get X pos from array.
			 characterSpots[charPos] = 1;									//Update available locations in textbox.
			 HAL_Delay(500);												//Stops it from wigging out.
		   }
		   /* 5 */
		   else if ((display.y >= 97) && (display.y <= 144))
		   {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '-');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		   }
		   /* 2 */
		   else if ((display.y >= 145) && (display.y <= 192))
		   {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, 'x');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		   }
		   /* C */
		   else if ((display.y >= 193) && (display.y <= 240))
		  {
			  BSP_LCD_DisplayChar (characterPositionsX[charPos], 13, '%');	//Get X pos from array.
			  characterSpots[charPos] = 1;									//Update available locations in textbox.
			  HAL_Delay(500);	//Stops it from wigging out.
		  }


	}


  }



}//End CalculatorProcess

















