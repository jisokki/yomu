#include "Arduino.h"
#include "Audio.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"

// Digital I/O used
#define SD_CS          16
#define SPI_MOSI      15
#define SPI_MISO      6
#define SPI_SCK       7
#define I2S_DOUT      38
#define I2S_BCLK      39
#define I2S_LRC       40

Audio audio;

void setup() {
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    SPI.setFrequency(1000000);
    Serial.begin(115200);
    SD.begin(SD_CS);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(12); // 0...21
    audio.connecttoFS(SD, "001.mp3");
}

void loop(){
    vTaskDelay(1);
    audio.loop();
}