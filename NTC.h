// Request commands 

#define R_ABORT                 0x00
#define R_SET_CHANNEL_THRESHOLD 0x01
#define R_GET_CHANNEL_THRESHOLD 0x02
#define R_SET_AND_CONDITION     0x03
#define R_GET_AND_CONDITION     0x04
#define R_GET_CHANNELS_OUTSIDE_THRESHOLD_VALUES 0x05
#define R_SET_CAN_ADDR_UNPROTECT 0x06
#define R_ERASE_AND_CONDITION    0x07
#define R_SET_ADC_PARAM          0x08
#define R_GET_PARAM              0x09
#define R_GET_STATUS             0x1E


// Answer commands 

#define A_SET_CHANNEL_THRESHOLD   0x01
#define A_GET_CHANNEL_THRESHOLD   0x02
#define A_SET_AND_CONDITION       0x03
#define A_GET_AND_CONDITION       0x04
#define A_GET_CHANNELS_OUTSIDE_THRESHOLD_VALUES 0x05
#define A_SET_CAN_ADDR            0x06
#define A_ERASE_AND_CONDITION     0x07
#define A_SET_ADC_PARAM           0x08
#define A_GET_PARAM               0x09
#define A_GET_STATUS_EEPROM       0x1E
#define A_GET_STATUS_WARNING      0x1E

#define PAYLOADMASK               0xFFFFFFFFFFFFFF
#define CANIDMASK                 0xFFFF
#define REQIDMASK                 0xFF
#define REQIDSHIFT                56
