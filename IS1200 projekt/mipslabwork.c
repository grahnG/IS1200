/* mipslabwork.c
   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):
   This file modified 2017-04-31 by Ture Teknolog 
   This file modified 2024-02-26 by Gustav Grahn and Dennis Franzén
   For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t display[32][128];
uint8_t oled_display[512]; 
int initial_active = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int *trise = (volatile int *)0xbf886100;
  TRISECLR = 0xff;  // Output (LED:S)
  TRISDSET = 0xfe0; // Input (BTN 2-4, SW 1-4)
  TRISFSET = 0x2;   // Input (BTN 1)
  PORTE = 0x0;      // Led
}

/* This function is called repetitively from the main program */
void labwork(void) {
  int btns = getbtns();
  int sw = getsw();

  if(sw & 0x1) {
    exitGame();
  }
    
    twoPlayerMode(btns);
  
}
