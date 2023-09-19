void bugcheck(int code, int line) {
if (code == 0x40) {
halt();
}
else if (code == 0x1234) {
halt();  
}
}
