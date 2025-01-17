#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Paddle-specific variables
float paddleHeight = 8;           // Height of each paddle
float paddleWidth = 3;            // Width of each paddle
float paddleMovementSpeed = 1;    // The speed at which paddles can move

// Position variables for paddle 1 (Player 1's paddle)
float paddle1PositionX = 0;       // Initial X position of paddle 1 (left edge of the screen)
float paddle1PositionY = 32 / 2 - 2; // Initial Y position of paddle 1 (centered vertically)

// Position variables for paddle 2 (Player 2's paddle)
float paddle2PositionX = 128 - 4; // Initial X position of paddle 2 (near the right edge of the screen)
float paddle2PositionY = 32 / 2 - 2; // Initial Y position of paddle 2 (centered vertically)

// Movement state variables for paddles, indicating if they are moving up or down
float paddle2MoveUp = 0;          // Movement flag for paddle 2 moving up
float paddle2MoveDown = 0;        // Movement flag for paddle 2 moving down
float paddle1MoveUp = 0;          // Movement flag for paddle 1 moving up
float paddle1MoveDown = 0;        // Movement flag for paddle 1 moving down

// Ball-specific variables
float ballDiameter = 2;           // Diameter of the ball
float ballVelocityX = 1;          // Initial horizontal velocity of the ball
float ballVelocityY = 0;          // Initial vertical velocity of the ball

// Initial position for the ball
int ballPositionX = 128 / 2 - 5;  // Initial X position of the ball (centered horizontally)
int ballPositionY = 32 / 2;       // Initial Y position of the ball (centered vertically)
int collisionCount = 0;           // Counter for the number of collisions

// Function to update the positions of the paddles based on player input
void movePlayersTwo(int btns) {
  // Reset movement indicators for both paddles
  paddle2MoveUp = paddle2MoveDown = paddle1MoveUp = paddle1MoveDown = 0;

  // Update paddle 2's vertical position based on input
  if ((btns & 0x1) && paddle2PositionY < (32 - paddleHeight)) {
    paddle2PositionY += paddleMovementSpeed;
    paddle2MoveUp = 1;
  }
  if ((btns & 0x2) && paddle2PositionY > 0) {
    paddle2PositionY -= paddleMovementSpeed;
    paddle2MoveDown = 1;
  }

  // Update paddle 1's vertical position based on input
  if ((btns & 0x4) && paddle1PositionY < (32 - paddleHeight)) {
    paddle1PositionY += paddleMovementSpeed;
    paddle1MoveUp = 1;
  }
  if ((btns & 0x8) && paddle1PositionY > 0) {
    paddle1PositionY -= paddleMovementSpeed;
    paddle1MoveDown = 1;
  }
}

// Function to update the ball's position and handle collisions
void moveBall() {
  // Update ball position based on its velocity
  ballPositionX += ballVelocityX;
  ballPositionY += ballVelocityY;

  // Cap the ball's vertical velocity to prevent excessive speed
  if (ballVelocityY > 1.7) ballVelocityY = 1.7;
  if (ballVelocityY < -1.7) ballVelocityY = -1.7;

  // Invert ball's vertical direction if it hits the top or bottom edge
  if (ballPositionY < 1 || ballPositionY > (31 - ballDiameter)) {
    ballVelocityY = -ballVelocityY;
  }

  // Special condition to change ball's vertical direction after certain collisions
  if (ballVelocityY < 0.3 && ballPositionY <= 10) {
    collisionCount++;
    if (collisionCount >= 10) {
      ballVelocityY = 1;
      collisionCount = 0;
    }
  } else {
    collisionCount = 0;
  }
}



