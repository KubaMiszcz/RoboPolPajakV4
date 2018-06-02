#pragma once
//MCU Constants
static const uint16_t ADC_RESOLUTION = 4095;
//Robot Constants
static const uint8_t NUM_LEGS = 4;
static const uint8_t NUM_HINGES_IN_LEG = 3;

//Construktion Constants [mm]
static const int16_t LEG_OFFSET_FROM_ORIGIN_IN_X = 35;
static const int16_t LEG_OFFSET_FROM_ORIGIN_IN_Y = 35;
static const int16_t LEG_OFFSET_FROM_ORIGIN_IN_Z = -22;
static const uint16_t LEG_SEGMENT_LENGTHS[NUM_HINGES_IN_LEG] = { 32, 64, 123 };

//servo characteristics for FrontLeftLeg 
static const uint16_t SERVO_5135_CHARACTERISTIC_CCRS[5] = { 7121, 5325, 3975, 2825, 1678 };
static const uint16_t SERVO_5181_CHARACTERISTIC_CCRS[5] = { 6977, 5325, 3975, 2725, 1530 };
static const uint16_t SERVO_5132_CHARACTERISTIC_CCRS[5] = { 1860, 3300, 4575, 5850, 7365 }; //Reversed

//servo characteristics for FrontRightLeg 
static const uint16_t SERVO_5186_CHARACTERISTIC_CCRS[5] = { 6911, 5350, 4025, 2825, 1612 };
static const uint16_t SERVO_5185_CHARACTERISTIC_CCRS[5] = { 7164, 5650, 4205, 2850, 1767 };
static const uint16_t SERVO_5184_CHARACTERISTIC_CCRS[5] = { 1921, 3275, 4650, 5975, 7579 }; //Reversed

//servo characteristics for RearRightLeg 
static const uint16_t SERVO_5134_CHARACTERISTIC_CCRS[5] = { 6600, 5125, 3850, 2750, 1650 };
static const uint16_t SERVO_5133_CHARACTERISTIC_CCRS[5] = { 7894, 5930, 4550, 3340, 2094 };
static const uint16_t SERVO_5183_CHARACTERISTIC_CCRS[5] = { 1880, 3175, 4475, 5800, 7498 }; //Reversed

//servo characteristics for RearLeftLeg 
static const uint16_t SERVO_5131_CHARACTERISTIC_CCRS[5] = { 7391, 5650, 4210, 2900, 1753 };
static const uint16_t SERVO_5187_CHARACTERISTIC_CCRS[5] = { 7442, 5650, 4325, 3025, 1838 };
static const uint16_t SERVO_5182_CHARACTERISTIC_CCRS[5] = { 1640, 2900, 4100, 5375, 6928 }; //Reversed

//Other Constants
static const float_t TO_DEGREES = 180 / M_PI;
uint32_t tick = 0;
uint32_t tick2 = 0;


//+debug only for keep vertical scale in live varables in vgdb
static const uint8_t sc0 = 0;
static const uint8_t scPos100 = 100;
static const uint8_t scPos200 = 200;
static const uint8_t scPos300 = 300;
static const uint8_t scPos400 = 400;
static const uint8_t scPos500 = 500;
static const uint8_t scPos600 = 600;
static const uint8_t scPos700 = 700;
static const uint8_t scPos800 = 800;
static const uint8_t scPos900 = 900;
static const uint16_t scPos1000 = 1000;
static const uint16_t scPos2000 = 2000;
static const uint16_t scPos3000 = 3000;
static const uint16_t scPos4000 = 4000;
static const uint16_t scPos5000 = 5000;
static const uint16_t scPos6000 = 6000;
static const uint16_t scPos7000 = 7000;
static const uint16_t scPos8000 = 8000;
static const uint16_t scPos9000 = 9000;
static const uint16_t scPos10000 = 10000;

//negative values
static const uint8_t scNeg100 = -100;
static const uint8_t scNeg200 = -200;
static const uint8_t scNeg300 = -300;
static const uint8_t scNeg400 = -400;
static const uint8_t scNeg500 = -500;
static const uint8_t scNeg600 = -600;
static const uint8_t scNeg700 = -700;
static const uint8_t scNeg800 = -800;
static const uint8_t scNeg900 = -900;
static const uint16_t scNeg1000 = -1000;
static const uint16_t scNeg2000 = -2000;
static const uint16_t scNeg3000 = -3000;
static const uint16_t scNeg4000 = -4000;
static const uint16_t scNeg5000 = -5000;
static const uint16_t scNeg6000 = -6000;
static const uint16_t scNeg7000 = -7000;
static const uint16_t scNeg8000 = -8000;
static const uint16_t scNeg9000 = -9000;
static const uint16_t scNeg10000 = -10000;

//static const uint16_t LEG_SEGMENT_0_LENGTH = 32;
//static const uint16_t LEG_SEGMENT_1_LENGTH = 64;
//static const uint16_t LEG_SEGMENT_2_LENGTH = 123;
