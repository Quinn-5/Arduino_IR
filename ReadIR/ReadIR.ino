#define ReadPins    PIND    // PIN 0-7 read register
#define IRPin       1 << 2  // Mask to read pin 2
#define record      1 << 3  // Mask to read pin 3
#define play1       4       // play button pin 1
#define play2       5       // play button pin 2
#define ledPin      6       // IR LED pin

#define RESOLUTION  20
#define MAX_BYTE    255
#define CMD_SIZE    64

// 2d array to save IR input
unsigned int cmd[CMD_SIZE][2];
// 3d array to store multiple commands
unsigned int storage[2][CMD_SIZE][2];

bool hasrun = false;
unsigned int highpulse, lowpulse;   // pulse length 

void setup() {
    Serial.begin(9600);
    Serial.println("Ready.");
    pinMode(ledPin, OUTPUT);
}

void loop() {
    int index = -1;
    if(digitalRead(play1))
        index = 0;
    else if (digitalRead(play2))
        index = 1;
    
        
    
    if ((ReadPins & record) && index+1) {
        readIR(index);
    } else if ((digitalRead(play1) || digitalRead(play2)) && index+1) {
        replay(index);
    }
}

//  Code to record IR
void readIR(int saveSlot) {
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
                storage[saveSlot][i][0] = cmd[i][0];
                storage[saveSlot][i][1] = cmd[i][1];
                if (cmd[i][0] == 0) {
                    break;
                }            
                Serial.print(storage[saveSlot][i][0] * RESOLUTION);
                Serial.print(", ");
                Serial.println(storage[saveSlot][i][1] * RESOLUTION);
                
                cmd[i][0] = 0;
                cmd[i][1] = 0;
            }
            Serial.println("Done!");
            return;
        }
    }
}

void replay(int saveSlot) {
    noInterrupts();
    long microsecs;
    for (int i = 0; i < CMD_SIZE; i++) {
        delayMicroseconds(storage[saveSlot][i][0] * RESOLUTION);
        microsecs = storage[saveSlot][i][1] * RESOLUTION;
        while (microsecs > 0) {
            //  Measured this to be closest to 38kHz via oscilloscope
            digitalWrite(ledPin, HIGH);
            delayMicroseconds(9);
            digitalWrite(ledPin, LOW);
            delayMicroseconds(8);
            
            //number of microseconds in 38kHz pulse
            microsecs -= 26;
        }
    }
    interrupts();
    //  typical delay between signals measured from remote
    delay(100);
}
    
