#define usint_t unsigned int

#define VIDEO_BUFFER_LOCATION 0xb8000
#define ROW_SIZE 25
#define COLUMN_SIZE 80
#define VGA_CELL_SIZE 2

#define COLOR_BLACK 0x00
#define COLOR_BLUE 0x01
#define COLOR_GREEN 0x02
#define COLOR_CYAN 0x03
#define COLOR_RED 0x04
#define COLOR_MAGENTA 0x05
#define COLOR_BROWN 0x06
#define COLOR_LIGHT_GREY 0x07
#define COLOR_DARK_GREY 0x08
#define COLOR_LIGHT_BLUE 0x9
#define COLOR_LIGHT_GREEN 0xa 
#define COLOR_LIGHT_CYAN 0xb
#define COLOR_LIGHT_RED 0xc
#define COLOR_LIGHT_MAGENTA 0xd
#define COLOR_LIGHT_BROWN 0xe
#define COLOR_WHITE 0xf

void printString(const char *displayString, usint_t vgaIndex, usint_t colorCode) {
  char *vga = (char*) VIDEO_BUFFER_LOCATION;
  usint_t stringIndex = 0;

  while (displayString[stringIndex] != '\0') {
    vga[vgaIndex] = displayString[stringIndex];
    vga[vgaIndex + 1] = colorCode;

    stringIndex++;
    vgaIndex += VGA_CELL_SIZE;
  }
}

void clearScreen() {
  char *vga = (char*) VIDEO_BUFFER_LOCATION;
  usint_t vgaIndex = 0;
  usint_t screenSize = ROW_SIZE * COLUMN_SIZE;

  while (vgaIndex < screenSize) {
    vga[vgaIndex] = ' ';
    vga[vgaIndex + 1] = COLOR_BLACK; // Not needed though. Since, the space is already a character with black colour.
    
    vgaIndex += VGA_CELL_SIZE;
  }
}

void kernelMain(void) {
  const char *displayString = "#";
  
  clearScreen();
  printString(displayString, 0, COLOR_LIGHT_GREEN);

  return;
}
