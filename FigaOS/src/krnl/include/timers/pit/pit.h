#define CHANNEL_0_DATA_RW 0x40
#define CHANNEL_1_DATA_RW 0x41
#define CHANNEL_2_DATA_RW 0x42
#define MODE_COMMAND_REGISTER_W 0x43

void PITInit(
    unsigned int frequency
);

void wait(
    int wait_ticks
);

unsigned int PITGetTimer(
	void
);