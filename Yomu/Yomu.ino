#include <dummy.h> //esp32 library
#include "Arduino.h"
#include "Audio.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"
#include "boootloader_random.h"


// Digital I/O used
#define SD_CS          2
#define SPI_MOSI      17
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      5
#define I2S_BCLK      7
#define I2S_LRC       6


// Pushbutton
#define BTN_A   9
#define BTN_B   10

// Debounce Handling
const int kDebounceTime = 100; // 100 ms
int cLastDebounce = 0;

bool checkDebounce() {
    if(cLastDebounce >= kDebounceTime) {
        cLastDebounce = 0;
        return true;
    }
    else return false;
}

Audio audio;

void my_audio_info(Audio::msg_t m) {
    Serial.printf("%s: %s\n", m.s, m.msg);
}

void setup() {

    // Button Setup
    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);

    // Audio info
    Audio::audio_info_callback = my_audio_info;

    // Initialize SD Card via SPI
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    SPI.setFrequency(1000000);
    Serial.begin(115200);
    SD.begin(SD_CS);

    // Initialize I2S module
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(21); // 0...21
    audio.connecttoFS(SD, "001.mp3");
}

void loop(){
    vTaskDelay(1);
    cLastDebounce++;

    audio.loop();

    if( digitalRead(BTN_A) == 0 && checkDebounce()) {
        audio.connecttoFS(SD, "002.mp3");
        vTaskDelay(1);
        audio.loop();
    }

    if( digitalRead(BTN_B) == 0 && checkDebounce()) {
        audio.connecttoFS(SD, "003.mp3");
        vTaskDelay(1);
        audio.loop();
    }
    

}