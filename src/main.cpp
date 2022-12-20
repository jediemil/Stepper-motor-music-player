#include <Arduino.h>

#define NUM_SPEAKERS 8

uint32_t musicTable[][3] = {};
int musicLen = 0;

int ticksPerBeat = 480;
int usPerBeat = 500000;
uint32_t usPerTick = usPerBeat / ticksPerBeat;

void setup() {
    Serial.begin(115200);

    ledcSetup(0, 100, 8);
    ledcSetup(2, 100, 8);
    ledcSetup(4, 100, 8);
    ledcSetup(6, 100, 8);
    ledcSetup(8, 100, 8);
    ledcSetup(10, 100, 8);
    ledcSetup(12, 100, 8);
    ledcSetup(14, 100, 8);

    ledcAttachPin(13, 0);
    ledcAttachPin(27, 2);
    ledcAttachPin(26, 4);
    ledcAttachPin(25, 6);
    ledcAttachPin(33, 8);
    ledcAttachPin(32, 10);
    ledcAttachPin(4, 12);
    ledcAttachPin(16, 14);

    Serial.println("Boot successful");
}

void loop() {
    for (int i = 0; i < musicLen; i++) {
        uint32_t newFreq = musicTable[i][1];
        uint32_t channel = musicTable[i][0];

        if (channel == 9) {
            usPerBeat = newFreq;
            usPerTick = usPerBeat / ticksPerBeat;
        } else {
            ledcWriteTone(channel * 2, newFreq);
        }

        //Serial.printf("Waiting %u us\n", musicTable[i+1][2] * usPerTick);
        delayMicroseconds(musicTable[i + 1][2] * usPerTick); // TODO: Change to system based on micros().
    }

    delay(2000);

    for (int channel = 0; channel < NUM_SPEAKERS; channel++) {
        ledcWriteTone(channel * 2, 240);
    }

    delay(1000);

    for (int channel = 0; channel < NUM_SPEAKERS; channel++) {
        ledcWriteTone(channel * 2, 0);
    }

    delay(3000);
}