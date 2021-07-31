#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define CLR_HIGH 14
#define CLR_LOW 15

void print_char(char character, int col, int row, char attribute_byte);
void clrscr();

int get_screen_offset();
int get_cursor();
int get_screen_offset(int cols, int rows);
int handle_scrolling(int offset);
void set_cursor(int offset);
