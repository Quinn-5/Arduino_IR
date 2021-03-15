#define ReadPins    PIND    // PIN 0-7 read register
#define IRPin       1 << 2  // Mask to read pin 2
#define Toggle      1 << 3  // Mask to read pin 3

#define RESOLUTION  20

// 2d array to save IR input
unsigned int cmd[8][50][2];

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop() {

    if (ReadPins & Toggle) {
        unsigned int highpulse = 0, lowpulse = 0;   // pulse length timings
        unsigned int index = 0;
        bool hasrun = false;

        while (ReadPins & IRPin) {
            highpulse++;
            delayMicroseconds(RESOLUTION);

            if (!(ReadPins & Toggle)) {
                return;
            }
        }
        cmd[0][index][0] = highpulse * RESOLUTION;
        
        while (!(ReadPins & Toggle)) {
            lowpulse++;
            delayMicroseconds(RESOLUTION);

            if (!(ReadPins & Toggle)) {
                return;
            }
        }
        cmd[0][index][1] = lowpulse * RESOLUTION;
        index++;

    } else {
        for (int i = 0; i < 50; i ++) {
            Serial.print(cmd[0][i][0]);
            Serial.println(cmd[0][i][1]);
        }

    }
    
}