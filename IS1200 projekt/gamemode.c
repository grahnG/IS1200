#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Game-specific variables to track the state and mode of the game
int isGameActive = 0; // Flag indicating whether the game is active (1) or not (0)
float currentGameMode = 0; // Variable to store the current game mode, with 0 representing a default or uninitialized state

// Function to execute the two-player game mode logic
void twoPlayerMode(int btns) {
  movePlayersTwo(btns); // Function call to handle player movements based on button inputs for two players
  moveBall();           // Function call to update the ball's position based on its current velocity
  paddle_hit();         // Function call to check and handle collisions between the ball and paddles

  clearScreen(); // Clear the display in preparation for drawing the updated game state
  // Draw paddles and ball at their current positions
  drawPixels(paddle1PositionX, paddle1PositionY, paddleWidth, paddleHeight); // Draw player 1's paddle
  drawPixels(paddle2PositionX, paddle2PositionY, paddleWidth, paddleHeight); // Draw player 2's paddle
  drawPixels(ballPositionX, ballPositionY, ballDiameter, ballDiameter);     // Draw the ball
  convertToBitmap(); // Convert the drawn elements into a bitmap format suitable for the OLED display
  display_image(0, oled_display); // Display the updated game state on the OLED screen
}


