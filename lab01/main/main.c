#include <stdio.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "lcd.h"
#include "pac.h"

static const char *TAG = "lab01";

#define delayMS(ms) \
	vTaskDelay(((ms)+(portTICK_PERIOD_MS-1))/portTICK_PERIOD_MS)

//----------------------------------------------------------------------------//
// Car Implementation - Begin
//----------------------------------------------------------------------------//

const uint8_t frame_mapping[] = {0,1,2,1};

// Car constants
#define CAR_CLR rgb565(220,30,0)
#define WINDOW_CLR rgb565(180,210,238)
#define TIRE_CLR BLACK
#define HUB_CLR GRAY
//these offsets define how far off the wheels are
#define WINDOW_DISTANCE_X_OFFSET 18
#define WHEEL_DISTANCE_X_OFFSET 37

#define UPPERRECTANGLE_X0 1
#define UPPERRECTANGLE_Y0 0
#define UPPERRECTANGLE_X1 40
#define UPPERRECTANGLE_Y1 11
#define HOOD_X0 40
#define HOOD_Y0 9
#define HOOD_X1 40
#define HOOD_Y1 11
#define HOOD_X2 60
#define HOOD_Y2 11
#define BASERECTANGLE_X0 0
#define BASERECTANGLE_Y0 12
#define BASERECTANGLE_X1 59
#define BASERECTANGLE_Y1 24
#define WINDOW_X0 3
#define WINDOW_Y0 1
#define WINDOW_X1 18
#define WINDOW_Y1 8
#define WINDOW_RADIUS 2
#define BASE_WHEEL_X0 11
#define BASE_WHEEL_Y0 24
#define SMALL_WHEEL_RAD 4
#define BIG_WHEEL_RAD 7
#define CAR_X_SIZE 60
#define CAR_Y_SIZE 32
#define PACMAN_FRAMES_LOOP 4
#define BOTTOM_TEXT_LOC LCD_H - LCD_CHAR_H * 2 

/**
 * @brief Draw a car at the specified location.
 * @param x      Top left corner X coordinate.
 * @param y      Top left corner Y coordinate.
 * @details Draw the car components relative to the anchor point (top, left).
 */
void drawCar(coord_t x, coord_t y)
{
	lcd_fillRect2(UPPERRECTANGLE_X0+x, UPPERRECTANGLE_Y0+y, UPPERRECTANGLE_X1+x, UPPERRECTANGLE_Y1+y, CAR_CLR);
	lcd_fillRect2(BASERECTANGLE_X0+x, BASERECTANGLE_Y0+y, BASERECTANGLE_X1+x, BASERECTANGLE_Y1+y, CAR_CLR);
	lcd_fillTriangle(HOOD_X0+x, HOOD_Y0+y, HOOD_X1+x, HOOD_Y1+y, HOOD_X2+x, HOOD_Y2+y, CAR_CLR);
	lcd_fillRoundRect2(WINDOW_X0+x, WINDOW_Y0+y, WINDOW_X1+x, WINDOW_Y1+y, WINDOW_RADIUS, WINDOW_CLR);
	lcd_fillRoundRect2(WINDOW_X0+WINDOW_DISTANCE_X_OFFSET+x, WINDOW_Y0+y, WINDOW_X1+WINDOW_DISTANCE_X_OFFSET+x, WINDOW_Y1+y, WINDOW_RADIUS, WINDOW_CLR);
	lcd_fillCircle(BASE_WHEEL_X0+x, BASE_WHEEL_Y0+y, BIG_WHEEL_RAD, TIRE_CLR);
	lcd_fillCircle(BASE_WHEEL_X0+WHEEL_DISTANCE_X_OFFSET+x, BASE_WHEEL_Y0+y, BIG_WHEEL_RAD, TIRE_CLR);
	lcd_fillCircle(BASE_WHEEL_X0+x, BASE_WHEEL_Y0+y, SMALL_WHEEL_RAD, HUB_CLR);
	lcd_fillCircle(BASE_WHEEL_X0+WHEEL_DISTANCE_X_OFFSET+x, BASE_WHEEL_Y0+y, SMALL_WHEEL_RAD, HUB_CLR);
}

//----------------------------------------------------------------------------//
// Car Implementation - End
//----------------------------------------------------------------------------//

// Main display constants
#define BACKGROUND_CLR rgb565(0,60,90)
#define TITLE_CLR GREEN
#define STATUS_CLR WHITE
#define STR_BUF_LEN 12 // string buffer length
#define FONT_SIZE 2
#define FONT_W (LCD_CHAR_W*FONT_SIZE)
#define FONT_H (LCD_CHAR_H*FONT_SIZE)
#define STATUS_W (FONT_W*3)

#define WAIT 2000 // milliseconds
#define DELAY_EX3 20 // milliseconds

// Object position and movement
#define OBJ_X 100
#define OBJ_Y 100
#define OBJ_MOVE 3 // pixels

#define STUPID_ARRAY_LENGTH 10

void app_main(void)
{
	ESP_LOGI(TAG, "Start up");
	lcd_init();
	lcd_fillScreen(BACKGROUND_CLR);
	lcd_setFontSize(FONT_SIZE);
	lcd_drawString(0, 0, "Hello World! (lcd)", TITLE_CLR);
	printf("Hello World! (terminal)\n");
	delayMS(WAIT);

	// TODO: Exercise 1 - Draw car in one location.
	// * Fill screen with background color
	// * Draw string "Exercise 1" at top left of screen with title color
	// * Draw car at OBJ_X, OBJ_Y
	// * Wait 2 seconds

	lcd_fillScreen(BACKGROUND_CLR);
	lcd_drawString(0, 0, "Exercise 1", TITLE_CLR);
	drawCar(OBJ_X, OBJ_Y);
	delayMS(WAIT);
	// TODO: Exercise 2 - Draw moving car (Method 1), one pass across display.
	// Clear the entire display and redraw all objects each iteration.
	// Use a loop and increment x by OBJ_MOVE each iteration.
	// Start x off screen (negative coordinate).
	// Move loop:
	// * Fill screen with background color
	// * Draw string "Exercise 2" at top left of screen with title color
	// * Draw car at x, OBJ_Y
	// * Display the x position of the car at bottom left of screen
	//   with status color
	char x_string[STUPID_ARRAY_LENGTH]; 
	for (int16_t i=-CAR_X_SIZE; i<LCD_W; i++) {
		lcd_fillScreen(BACKGROUND_CLR);
		lcd_drawString(0, 0, "Exercise 2", TITLE_CLR);
		snprintf(x_string, STUPID_ARRAY_LENGTH, "%d", i);
		drawCar(i, OBJ_Y);
		lcd_drawString(0, BOTTOM_TEXT_LOC, x_string, STATUS_CLR);
	}

	// TODO: Exercise 3 - Draw moving car (Method 2), one pass across display.
	// Move by erasing car at old position, then redrawing at new position.
	// Objects that don't change or move are drawn once.
	// Before loop:
	// * Fill screen once with background color
	// * Draw string "Exercise 3" at top left of screen with title color
	// Move loop:
	// * Erase car at old position by drawing a rectangle with background color
	// * Draw car at new position
	// * Erase status at bottom by drawing a rectangle with background color
	// * Display new position status of car at bottom left of screen
	// After running the above first, add a 20ms delay within the loop
	// at the end to see the effect.
	lcd_fillScreen(BACKGROUND_CLR);
	for (int16_t i=-CAR_X_SIZE; i<LCD_W; i++) {
		lcd_fillRect2(i-1, OBJ_Y, i-1+CAR_X_SIZE, OBJ_Y+CAR_Y_SIZE, BACKGROUND_CLR);
		lcd_fillRect2(0, BOTTOM_TEXT_LOC, STUPID_ARRAY_LENGTH * LCD_CHAR_W, LCD_H, BACKGROUND_CLR);
		lcd_drawString(0, 0, "Exercise 3", TITLE_CLR);
		snprintf(x_string, STUPID_ARRAY_LENGTH, "%d", i);
		drawCar(i, OBJ_Y);
		lcd_drawString(0, BOTTOM_TEXT_LOC, x_string, STATUS_CLR);
		delayMS(DELAY_EX3);
	}
	// TODO: Exercise 4 - Draw moving car (Method 3), one pass across display.
	// First, draw all objects into a cleared, off-screen frame buffer.
	// Then, transfer the entire frame buffer to the screen.
	// Before loop:
	// * Enable the frame buffer
	// Move loop:
	// * Fill screen (frame buffer) with background color
	// * Draw string "Exercise 4" at top left with title color
	// * Draw car at x, OBJ_Y
	// * Display position of the car at bottom left with status color
	// * Write the frame buffer to the LCD
	lcd_frameEnable();
	lcd_fillScreen(BACKGROUND_CLR);
	for (int16_t i=-CAR_X_SIZE; i<LCD_W; i++) {
		lcd_drawString(0, 0, "Exercise 4", TITLE_CLR); //title
		snprintf(x_string, STUPID_ARRAY_LENGTH, "%d", i); //xcord
		drawCar(i, OBJ_Y);
		lcd_drawString(0, BOTTOM_TEXT_LOC, x_string, STATUS_CLR);
		lcd_writeFrame();
		lcd_fillRect2(i, OBJ_Y, i+CAR_X_SIZE, OBJ_Y+CAR_Y_SIZE, BACKGROUND_CLR); //we've written the frame, so might as well clear old stuff
		lcd_fillRect2(0, BOTTOM_TEXT_LOC, STUPID_ARRAY_LENGTH * LCD_CHAR_W, LCD_H, BACKGROUND_CLR);
	}


	// TODO: Exercise 5 - Draw an animated Pac-Man moving across the display.
	// Use Pac-Man sprites instead of the car object.
	// Cycle through each sprite when moving the Pac-Man character.
	// Before loop:
	// * Enable the frame buffer
	// Nest the move loop inside a forever loop:
	// Move loop:
	// * Fill screen (frame buffer) with background color
	// * Draw string "Exercise 5" at top left with title color
	// * Draw Pac-Man at x, OBJ_Y with yellow color;
	//   Cycle through sprites to animate chomp
	// * Display position at bottom left with status color
	// * Write the frame buffer to the LCD
	lcd_frameEnable();
	lcd_fillScreen(BACKGROUND_CLR);



	for (;;) {
		uint8_t frame_num = 0;
		for (int16_t i=-PAC_W; i<LCD_W; i++) {
			frame_num = frame_num % PACMAN_FRAMES_LOOP;
			lcd_drawString(0, 0, "Exercise 5", TITLE_CLR); //title
			snprintf(x_string, STUPID_ARRAY_LENGTH, "%d", i); //xcord
			lcd_drawBitmap(i, OBJ_Y, pac[frame_mapping[frame_num]], PAC_W, PAC_H, YELLOW);
			lcd_drawString(0, BOTTOM_TEXT_LOC, x_string, STATUS_CLR);
			lcd_writeFrame();
			lcd_fillRect2(i, OBJ_Y, i+PAC_W, OBJ_Y+PAC_H, BACKGROUND_CLR); //we've written the frame, so might as well clear old stuff
			lcd_fillRect2(0, BOTTOM_TEXT_LOC, STUPID_ARRAY_LENGTH * LCD_CHAR_W, LCD_H, BACKGROUND_CLR);
			frame_num++;
		}
	}


}
