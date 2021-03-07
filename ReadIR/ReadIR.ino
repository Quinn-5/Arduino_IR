#define IRpin_PIN   PIND
#define IRPin       2

// arrays to record IR input
unsigned int cmd0[50];
unsigned int cmd1[50];
unsigned int cmd2[50];
unsigned int cmd3[50];
unsigned int cmd4[50];
unsigned int cmd5[50];
unsigned int cmd6[50];
unsigned int cmd7[50];

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop() {
  
}
