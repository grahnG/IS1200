#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// This function sets pixels within a specified rectangle to be "on" in the display buffer.
void drawPixels(int xPos, int yPos, int width, int height) {
  int rowIndex, columnIndex;

  // Iterate over all pixels in the display array
  for (rowIndex = 0; rowIndex < 32; rowIndex++) {
    for (columnIndex = 0; columnIndex < 128; columnIndex++) {
      // Check if the current pixel is within the specified rectangle bounds
      if (rowIndex >= yPos && rowIndex < (yPos + height) &&
          columnIndex >= xPos && columnIndex < (xPos + width)) {
        display[rowIndex][columnIndex] = 1; // Set the pixel to "on"
      }
    }
  }
}

// Converts the current state of the 2D display array into a 1D array format that the OLED can use.
void convertToBitmap() {
  int pageIndex, columnIndex, rowIndex;
  uint8_t bitMask;      
  uint8_t oledPixelValue; 

  // Iterate over each page (8 pixel rows) of the OLED display
  for (pageIndex = 0; pageIndex < 4; pageIndex++) {
    for (columnIndex = 0; columnIndex < 128; columnIndex++) {
      bitMask = 1;
      oledPixelValue = 0;

      // Combine 8 vertical bits into a single byte for each column
      for (rowIndex = 0; rowIndex < 8; rowIndex++) {
        if (display[8 * pageIndex + rowIndex][columnIndex]) {
          oledPixelValue |= bitMask; // Set the corresponding bit if the pixel should be "on"
        }
        bitMask <<= 1; // Move to the next bit in the byte
      }
      oled_display[columnIndex + pageIndex * 128] = oledPixelValue; // Update the OLED buffer
    }
  }
}

// Clears all pixels in the display buffer, effectively resetting the display.
void clearScreen() {
  int rowIndex, columnIndex, i;

  // Iterate over all pixels in the display array and set them to "off"
  for (rowIndex = 0; rowIndex < 32; rowIndex++) {
    for (columnIndex = 0; columnIndex < 128; columnIndex++) {
      display[rowIndex][columnIndex] = 0;
    }
  }

  // Also clear the OLED display buffer
  for (i = 0; i < 512; i++) {
    oled_display[i] = 0;
  }
}



