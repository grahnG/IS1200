#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


// Function to adjust ball's vertical velocity based on paddle 1's movement
void paddle1_physics() {
  // If paddle 1 moves up, decrease the ball's vertical velocity
  if(paddle1MoveUp == 1) {
    ballVelocityY -= 0.5;  
  }

  // If paddle 1 moves down, increase the ball's vertical velocity
  if(paddle1MoveDown == 1) {
    ballVelocityY += 0.5; 
  }
  
  // Check if the ball hits the top or bottom third of paddle 1 and reverse its vertical velocity
  if((ballPositionY + ballDiameter > paddle1PositionY) && 
     (ballPositionY < paddle1PositionY + paddleHeight)) {
    if(ballPositionY < paddle1PositionY + paddleHeight / 3 || 
       ballPositionY > paddle1PositionY + 2 * paddleHeight / 3) {
      ballVelocityY = -ballVelocityY; 
    }
  }
}

// Function to adjust ball's vertical velocity based on paddle 2's movement
void paddle2_physics() {
  // Adjust the ball's vertical velocity based on paddle 2's movement direction
  if(paddle2MoveUp == 1) {
    ballVelocityY -= 0.5;  // Decrease if moving up
  } else if(paddle2MoveDown == 1) {
    ballVelocityY += 0.5;  // Increase if moving down
  }

  // Check if the ball hits the top or bottom third of paddle 2 and reverse its vertical velocity
  if((ballPositionY + ballDiameter > paddle2PositionY) && 
     (ballPositionY < paddle2PositionY + paddleHeight)) {
    if(ballPositionY < paddle2PositionY + paddleHeight / 3 || 
       ballPositionY > paddle2PositionY + 2 * paddleHeight / 3) {
      ballVelocityY = -ballVelocityY;
    }
  }
}

// Function to implement ball and paddle collision logic
void paddle_hit() {
  // Check collision with paddle 1
  if (ballPositionX == paddleWidth && 
      (ballPositionY + ballDiameter > paddle1PositionY) && 
      (ballPositionY < paddle1PositionY + paddleHeight)) {
    ballVelocityX = -ballVelocityX;  // Reverse horizontal velocity on hit
    paddle1_physics();               // Apply additional physics effects based on paddle 1's movement
  } else if (ballPositionX < -21) {  // Check for ball out of bounds on the left side
    scoreGoal(2);                    // Award a point to player 2
  }

  // Check collision with paddle 2
  if (ballPositionX == (128 - paddleWidth - 4) && 
      (ballPositionY + ballDiameter > paddle2PositionY) && 
      (ballPositionY < paddle2PositionY + paddleHeight)) {
    ballVelocityX = -ballVelocityX;  // Reverse horizontal velocity on hit
    paddle2_physics();               // Apply additional physics effects based on paddle 2's movement
  } else if (ballPositionX > 138) {  // Check for ball out of bounds on the right side
    scoreGoal(1);                    // Award a point to player 1
  }
}




