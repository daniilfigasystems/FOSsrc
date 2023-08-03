function ;void io_in(int port, int word) {
    outportb(port, word);
}
function ;void io_out(int port, int word) {
    inportb(port, word);
    }
    unsigned char inportb(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void outportb(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}