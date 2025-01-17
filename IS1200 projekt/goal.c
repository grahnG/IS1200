#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

int strobeW = 0;         // Counter for strobe effect iterations
int p1Score = 0;         // Player 1's score
int p2Score = 0;         // Player 2's score
int p1ledscore = 0;      // Binary representation of Player 1's score for LEDs
int p2ledscore = 0;      // Binary representation of Player 2's score for LEDs

// Function to handle scoring a goal and updating the game state accordingly
void scoreGoal(int player) {
    // Check which player scored and update the display and score
    if (player == 1) {
        display_string(2, "Player 1 scored!"); // Update display for Player 1 scoring
        display_update(); 
        // Create a strobe light effect to signal the goal
        while (strobeW < 7) {
            delay(100);    
            PORTE = 0xf0; // Light up LEDs for Player 1
            delay(100);
            PORTE = 0x0;  // Turn off LEDs
            strobeW++;
        }
        strobeW = 0;
        p1Score++; // Increment Player 1's score
    } else if (player == 2) {
        display_string(2, "Player 2 scored!"); // Update display for Player 2 scoring
        display_update();
        // Create a strobe light effect for Player 2
        while (strobeW < 7) {
            delay(100);
            PORTE = 0xf;  // Light up LEDs for Player 2
            delay(100);
            PORTE = 0x0;
            strobeW++;
        }
        strobeW = 0;
        p2Score++; // Increment Player 2's score
    }

    // Update the LED score display based on the current score
    // Binary encoding is used to represent the score on LEDs
    if (p2Score == 1) { p2ledscore = 0x01;}
    if (p2Score == 2) { p2ledscore = 0x03;}
    if (p2Score == 3) { p2ledscore = 0x07;}
    if (p2Score == 4) { p2ledscore = 0x0f;}
    if (p2Score == 5) {
        // Declare Player 2 as the winner, reset the scores, and restart the game
        display_string(2, "Player 2 HAS WON");
        display_string(4, "THE GAME!!!");
        display_update(); 
        delay(5000); // Display the winning message for 5 seconds
        p1Score = 0;
        p2Score = 0;
        p2ledscore = 0x00;
        p1ledscore = 0x00;
    }

    if (p1Score == 1) {p1ledscore = 0x80;}
    if (p1Score == 2) {p1ledscore = 0xc0;}
    if (p1Score == 3) {p1ledscore = 0xe0;}
    if (p1Score == 4) {p1ledscore = 0xf0;}
    if (p1Score == 5) {
        // Declare Player 1 as the winner, reset the scores, and restart the game
        display_string(2, "Player 1 HAS WON");
        display_string(4, "THE GAME!!!");
        display_update();
        delay(5000); // Display the winning message for 5 seconds
        p1Score = 0;
        p2Score = 0;
        p1ledscore = 0x00;
        p2ledscore = 0x00;
    }

    // After scoring, display the updated scores using LEDs and restart the game
    restartGame(); // Restart the game after declaring the winner
    PORTE = p1ledscore + p2ledscore; // Combine and display scores for both players
}

