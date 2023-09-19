#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C
//Numerals
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_0 0x0B
//Mathmatical Operators
#define KEY_MINUS 0x0C
#define KEY_EQUAL 0x0D
#define KEY_KEYPAD_PLUS 0x4E
#define KEY_KEYPAD_DIV 0x35
//AhnTriKernel System SHIFT alternative(ATDRIVER)
#define KEY_SQUARE_OPENED_BRACKET 0x1A
#define KEY_SQUARE_CLOSED_BRACKET 0x1B
#define KEY_SEMICOLON 0x27
#define KEY_BACKSLASH 0x2B
#define KEY_FORESLHASH 0x35
#define KEY_AT 0x3B
#define KEY_SHARP 0x3C
#define KEY_DOLLAR 0x3D
#define KEY_PERCENT 0x3E
#define KEY_POWER 0x3F
#define KEY_AND 0x40
#define KEY_STAR 0x41
//Computer Deafults
#define KEY_BACKSPACE 0x0E
#define KEY_DELETE 0x53
#define KEY_DOWN 0x50
#define KEY_END 0x4F
#define KEY_ENTER 0x1C
#define KEY_ESC 0x01
#define KEY_KEYPAD_PLUS 0x4E
#define KEY_COMMA 0x33
#define KEY_DOT 0x34
#define KEY_SP 0x39
#define KEY_LEFT 0x4B
#define KEY_PAGE_DOWN 0x51
#define KEY_PAGE_UP 0x49
#define KEY_PRINT_SCREEN 0x37
#define KEY_RIGHT 0x4D
#define KEY_TAB 0x0F
#define KEY_UP 0x48
#define KEY_HOME 0xE0
char get_ascii_char(unsigned char key_code)
{
  switch(key_code){
    case KEY_A : return 'a';
    case KEY_B : return 'b';
    case KEY_C : return 'c';
    case KEY_D : return 'd';
    case KEY_E : return 'e';
    case KEY_F : return 'f';
    case KEY_G : return 'g';
    case KEY_H : return 'h';
    case KEY_I : return 'i';
    case KEY_J : return 'j';
    case KEY_K : return 'k';
    case KEY_L : return 'l';
    case KEY_M : return 'm';
    case KEY_N : return 'n';
    case KEY_O : return 'o';
    case KEY_P : return 'p';
    case KEY_Q : return 'q';
    case KEY_R : return 'r';
    case KEY_S : return 's';
    case KEY_T : return 't';
    case KEY_U : return 'u';
    case KEY_V : return 'v';
    case KEY_W : return 'w';
    case KEY_X : return 'x';
    case KEY_Y : return 'y';
    case KEY_Z : return 'z';
    case KEY_1 : return '1';
    case KEY_2 : return '2';
    case KEY_3 : return '3';
    case KEY_4 : return '4';
    case KEY_5 : return '5';
    case KEY_6 : return '6';
    case KEY_7 : return '7';
    case KEY_8 : return '8';
    case KEY_9 : return '9';
    case KEY_0 : return '0';
    case KEY_MINUS : return '-';
    case KEY_EQUAL : return '=';
    case KEY_SQUARE_OPENED_BRACKET : return '[';
    case KEY_SQUARE_CLOSED_BRACKET : return ']';
    case KEY_SEMICOLON : return ';';
    case KEY_BACKSLASH : return '\\';
    case KEY_COMMA : return ',';
    case KEY_DOT : return '.';
    case KEY_FORESLHASH : return '/';
    case KEY_SP : return ' ';
    case KEY_AT : return '@';
    case KEY_SHARP : return '#';
    case KEY_DOLLAR : return '$';
    case KEY_PERCENT : return '%';
    case KEY_POWER : return '^';
    case KEY_AND : return '&';
    case KEY_STAR : return '*';
    case KEY_TAB : return '       ';
    case KEY_BACKSPACE : return '\b';
    default : return 0;
  }
}
int read_char()
{

}