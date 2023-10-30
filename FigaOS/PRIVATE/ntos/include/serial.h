#define COM1 0x3f8
#define COM2 0x2f8
void int_com2();
void int_com1();
int com_receive(int com);
char read_com(int com);
int ite(int com);
void write_com(int com, char *data);