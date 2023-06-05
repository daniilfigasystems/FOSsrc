void vga_init();
void vga_clear();
void print_char();
int main(void) {
    vga_init();
    vga_clear();
 print_char("hello");
    return 0;
}

