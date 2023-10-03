extern unsigned int testfpu();
void checkfpu() {
    int testval = testfpu();
    if (testval == 0) {
        write_com(0x3f8, " NO FPU!");
        halt();
    }
    else {
        write_com(0x3f8, " FPU Present!");
    }
}
                                                                    