#define ReadPins    PIND    // PIN 0-7 read register
#define IRPin       1 << 2  // Mask to read pin 2
#define Toggle      1 << 3  // Mask to read pin 3

#define RESOLUTION  20

// 2d array to save IR input
unsigned int cmd[100][2];

bool hasrun = false;
unsigned int highpulse = 0, lowpulse = 0;   // pulse length 

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop() {
    unsigned int index = 0;
    

    while (ReadPins & Toggle) {
        highpulse = 0, lowpulse = 0;
        hasrun=true;
        
        while (ReadPins & IRPin) {
            highpulse++;
            delayMicroseconds(RESOLUTION);

            if (!(ReadPins & Toggle)) {
                return;
            }
        }
        cmd[index][0] = highpulse * RESOLUTION;
        
        while (!(ReadPins & IRPin)) {
            lowpulse++;
            delayMicroseconds(RESOLUTION);

            if (!(ReadPins & Toggle)) {
                return;
            }
        }
        cmd[index][1] = lowpulse * RESOLUTION;
        index++;

    }
    if (hasrun) {
        for (int i = 0; i < 100; i ++) {
            Serial.print(cmd[i][0]);
            Serial.print(", ");
            Serial.println(cmd[i][1], DEC);
            if (cmd[i][0] == 0) {
                break;
            }
        }
        Serial.println("Done!");
        hasrun = false;
    }
    
}
