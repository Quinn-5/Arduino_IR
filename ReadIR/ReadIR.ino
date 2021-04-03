#define ReadPins    PIND    // PIN 0-7 read register
#define IRPin       1 << 2  // Mask to read pin 2
#define record      1 << 3  // Mask to read pin 3
#define play        4       // play button pin

#define RESOLUTION  20
#define MAX_BYTE    255

// 2d array to save IR input
unsigned int cmd[64][2];
// 3d array to store multiple commands
byte storage[5][64][2];

bool hasrun = false;
unsigned int highpulse = 0, lowpulse = 0;   // pulse length 

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop() {
    if (ReadPins & PIND) {
        readIR();
    }
    if (digitalRead(play)) {
        replay();
    }
}


void readIR() {
    unsigned int index = 0;
    

    while (ReadPins & record) {
        highpulse = 0, lowpulse = 0;
        hasrun=true;
        
        while (ReadPins & IRPin) {
            highpulse++;
            delayMicroseconds(RESOLUTION);

            if (!(ReadPins & record)) {
                return;
            }
        }
        cmd[index][0] = highpulse;
        
        while (!(ReadPins & IRPin)) {
            lowpulse++;
            delayMicroseconds(RESOLUTION);

            if (!(ReadPins & record)) {
                return;
            }
        }
        cmd[index][1] = lowpulse;
        index++;

    }
    if (hasrun) {
        for (int i = 0; i < 100; i ++) {
            if (cmd[i][0] < MAX_BYTE && cmd[i][1] < MAX_BYTE) {
                storage[1][i][0] = (byte)cmd[i][0];
                storage[1][i][1] = (byte)cmd[i][1];
                Serial.print(cmd[i][0]);
                Serial.print(", ");
                Serial.println(cmd[i][1]);
            }
            if (cmd[i][0] == 0) {
                break;
            }
        }
        Serial.println("Done!");
        hasrun = false;
    }
}

void replay() {
    Serial.println("Play button pressed.");
}
