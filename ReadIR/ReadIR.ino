#define ReadPins    PIND    // PIN 0-7 read register
#define IRPin       1 << 2  // Mask to read pin 2
#define record      1 << 3  // Mask to read pin 3
#define play        4       // play button pin
#define ledPin      5       // IR LED pin

#define RESOLUTION  20
#define MAX_BYTE    255
#define CMD_SIZE    64

// 2d array to save IR input
unsigned int cmd[CMD_SIZE][2];
// 3d array to store multiple commands
unsigned int storage[1][CMD_SIZE][2];

bool hasrun = false;
unsigned int highpulse = 0, lowpulse = 0;   // pulse length 

void setup() {
    Serial.begin(9600);
    Serial.println("Ready to decode IR!");
    pinMode(ledPin, OUTPUT);
}

void loop() {
    if (ReadPins & record) {
        readIR();
    } else if (digitalRead(play)) {
        replay();
    }
}


void readIR() {
    while (true) {
        unsigned int index = 0;
    

        while (ReadPins & record) {
            highpulse = 0, lowpulse = 0;
            hasrun=true;

            while (ReadPins & IRPin) {
                highpulse++;
                delayMicroseconds(RESOLUTION);

                if (!(ReadPins & record)) {
                    break;
                }
            }
            cmd[index][0] = highpulse;

            while (!(ReadPins & IRPin)) {
                lowpulse++;
                delayMicroseconds(RESOLUTION);

                if (!(ReadPins & record)) {
                    break;
                }
            }   
            cmd[index][1] = lowpulse;
            index++;
        }
        if (hasrun) {
            for (int i = 0; i < CMD_SIZE; i ++) {
                storage[0][i][0] = cmd[i][0];
                storage[0][i][1] = cmd[i][1];
                if (cmd[i][0] == 0) {
                    break;
                }            
                Serial.print(storage[0][i-1][0] * RESOLUTION);
                Serial.print(", ");
                Serial.println(storage[0][i-1][1] * RESOLUTION);
                
                cmd[i][0] = 0;
                cmd[i][1] = 0;
            }
            Serial.println("Done!");
            return;
        }
    }
}

void replay() {
    cli();
    long microsecs;
    //unsigned long a, b;
    for (int i = 0; i < CMD_SIZE; i++) {
        delayMicroseconds(storage[0][i][0] * RESOLUTION);
        //Serial.print("expected: ");
        //Serial.println(storage[0][i][1] * RESOLUTION + storage[0][i][0] * RESOLUTION);
        //a = micros();
        microsecs = storage[0][i][1] * RESOLUTION;
        while (microsecs > 0) {
            digitalWrite(ledPin, HIGH);
            delayMicroseconds(9);
            digitalWrite(ledPin, LOW);
            delayMicroseconds(8);
            //number of microseconds in 38KHz pulse
            microsecs -= 26;
        }
        //b = micros();
        
        //Serial.print("actual: ");
        //Serial.println(b-a);
        
    }
    sei();
    delay(100);
}
    
