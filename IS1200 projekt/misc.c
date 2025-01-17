#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Function to exit the game
void exitGame() {
  delay(1000);                     // Wait for 1 second before executing the exit operations
  PORTE = 0x0;                     // Reset all the pins on port E to low (possibly to turn off LEDs or similar)

  clearScreen();                   // Clear the screen to remove any remaining visuals
  convertToBitmap();               // Convert the current graphics state to a bitmap for display
  display_image(0, oled_display);  // Display the bitmap on the OLED display at starting position 0
}

// Function to restart the game
void restartGame() {
  // Initialize paddle 1 position at the left middle of the screen
  paddle1PositionX = 0;
  paddle1PositionY = 32 / 2 - 2;  // Center paddle vertically and adjust by half its height

  // Initialize paddle 2 position at the right middle of the screen
  paddle2PositionX = 128 - 4;     // Position paddle inside the right edge, accounting for width
  paddle2PositionY = 32 / 2 - 2;  // Center paddle vertically and adjust by half its height

  // Initialize the ball position at the center of the screen
  ballPositionX = 128 / 2 - 5;
  ballPositionY = 32 / 2;
  // Set the initial ball velocity to move right horizontally and stationary vertically
  ballVelocityX = 1;
  ballVelocityY = 0;

  clearScreen();  // Clear the screen for game restart
  // Draw the initial positions of paddles and ball
  drawPixels(paddle1PositionX, paddle1PositionY, paddleWidth, paddleHeight); 
  drawPixels(paddle2PositionX, paddle2PositionY, paddleWidth, paddleHeight); 
  drawPixels(ballPositionX, ballPositionY, ballDiameter, ballDiameter); 
  convertToBitmap();  // Prepare the frame for display by converting to bitmap
  display_image(0, oled_display);  // Display the frame on the OLED screen
  delay(1000);  // Delay briefly before starting gameplay, allowing the user to get ready
}

// Function to clear text from the screen
void clearText() {
  // Clear text on lines 0 through 4 of the display
  display_string(0, "");
  display_string(1, "");
  display_string(2, "");
  display_string(3, "");
  display_string(4, "");
  display_update();  // Update the display to show the cleared text lines
}




