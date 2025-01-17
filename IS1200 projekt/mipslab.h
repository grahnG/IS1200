/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson
   Latest update 2015-08-28 by F Lundevall
   This file modified 2024-02-26 by Gustav Grahn and Dennis Franzén
   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */ 
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep ); 

void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Written as part of asm lab: delay, time2string*/
void delay(int);
void time2string( char *, int );

extern uint8_t display[32][128]; // Declaration of a 2D array representing the pixel matrix for the display with 32 rows and 128 columns. Each element represents a pixel's state in the display.
extern uint8_t oled_display[512]; // Declaration of an array representing a buffer for the OLED display content

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

//NEW FUNCTIONS written by students

// Game Mode Functions
// Handles the logic for the two-player game mode
void twoPlayerMode(int);

// Player Movement Functions
// Controls the movement of players' paddles in two-player mode and the ball
void movePlayersTwo(int);
void moveBall(void);

// Display Rendering Functions
// Converts game data to bitmap format for display, draws pixels on the screen, and clears the screen
void convertToBitmap(void);
void drawPixels(int, int, int, int);
void clearScreen(void);

// Game Control Functions
// Handles scoring, quitting the game, resetting the game, and clearing text from the screen
void scoreGoal(int);
void exitGame(void);
void restartGame(void);
void clearText(void);

// External declarations for game state variables
extern int isGameActive;             // Indicates whether the game is currently active (1) or not (0)
extern int player1Score;             // Stores the current score of player 1
extern float player2Score;           // Stores the current score of player 2
extern float currentPlayer;          // Stores the number of the current player (e.g., player 1 or player 2)
extern int lightCount;               // Stores the number of lights (or similar game elements) currently active

// External declarations for paddle-related variables
extern float paddleHeight;           // Height of the paddle
extern float paddleWidth;            // Width of the paddle
extern float paddleMovementSpeed;    // Speed at which the paddle moves

extern float paddle1PositionX;       // X position of paddle 1
extern float paddle1PositionY;       // Y position of paddle 1

extern float paddle2PositionX;       // X position of paddle 2
extern float paddle2PositionY;       // Y position of paddle 2

extern float paddle2MoveUp;          // Indicates the movement direction of paddle 2 (up)
extern float paddle2MoveDown;        // Indicates the movement direction of paddle 2 (down)
extern float paddle1MoveUp;          // Indicates the movement direction of paddle 1 (up)
extern float paddle1MoveDown;        // Indicates the movement direction of paddle 1 (down)

// External declarations for ball-related variables
extern float ballDiameter;           // Diameter of the ball
extern float ballVelocityX;          // Horizontal velocity of the ball
extern float ballVelocityY;          // Vertical velocity of the ball

extern int ballPositionX;            // X position of the ball
extern int ballPositionY;            // Y position of the ball
extern int collisionCount;           // Counts the number of collisions (e.g., with paddles or walls)


