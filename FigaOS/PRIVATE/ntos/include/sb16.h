#define module_name "SB16"
#define SBMODE8_1CH_SINGLE "0x80"
#define SBMODE8_1CH_AUTO "0x81"
#define SBMODE16_5CH_SINGLE "0x82"
#define SBMODE16_5CH_AUTO "0x83"
#define RIGHT_SB16 "0xF1"
#define LEFT_SB16 "0xF2"
#define TURN_ON_SPK_SB16 "0xD1"
#define TURN_OFF_SPK_SB16 "0xD3"
typedef struct SB16_DEVICE {
    int LEFT_VOLUME;
    int RIGHT_VOLUME;
    int SPK_STATE;
    char SND_ADDRESS;
    int SBMODE;
    int LENGTH;
    int CHANNEL;
};
void reset_DSP();