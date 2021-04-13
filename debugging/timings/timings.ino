int ray[5] = {1, 2, 3, 4, 5};


void setup() {
    Serial.begin(9600);

    Serial.println("For loop: ");
    int a = micros();
    for(int i = 1; i<10; i++) {
        int b = micros();

        int micro = 3;
        while (micro!=9) {
            micro = 9;
        }
        
        Serial.println(b - a);
        a = micros();
    }

    Serial.println();
    Serial.println("array access");
    a = micros();

    int b = micros();
    Serial.println(b - a);
}

void loop() {
    // put your main code here, to run repeatedly:

}
