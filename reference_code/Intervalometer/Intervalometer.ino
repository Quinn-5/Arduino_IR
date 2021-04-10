    // This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
    // See the full tutorial at https://learn.adafruit.com/ir-sensor/making-an-intervalometer
    // MIT License, attribution appreciated    Limor Fried, Adafruit Industries
     
    int IRledPin =  5;    // LED connected to digital pin 13
     
    // The setup() method runs once, when the sketch starts
     
    void setup()   {                
      // initialize the IR digital pin as an output:
      pinMode(IRledPin, OUTPUT);      
     
      // Serial.begin(9600);
    }
     
    void loop()                     
    {
      // Serial.println("Sending IR signal");
     
      SendPowerCode();
     
      delay(5*1000);  // wait one minute (60 seconds * 1000 milliseconds)
    }
     
    // This procedure sends a 38KHz pulse to the IRledPin 
    // for a certain # of microseconds. We'll use this whenever we need to send codes
    void pulseIR(long microsecs) {
      // we'll count down from the number of microseconds we are told to wait
     
      cli();  // this turns off any background interrupts
     
      while (microsecs > 0) {
        // 38 kHz is about 13 microseconds high and 13 microseconds low
       digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
       delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
       digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
       delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
     
       // so 26 microseconds altogether
       microsecs -= 26;
      }
     
      sei();  // this turns them back on
    }
     
    void SendPowerCode() {
      // This is the code for my particular Nikon, for others use the tutorial
      // to 'grab' the proper code from the remote
     
pulseIR(9300);
delayMicroseconds(4500);
pulseIR(600);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(560);
pulseIR(600);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(540);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(1680);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(560);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(600);
delayMicroseconds(540);
pulseIR(580);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(560);
pulseIR(580);
delayMicroseconds(560);
pulseIR(620);
delayMicroseconds(560);
pulseIR(600);
delayMicroseconds(520);
pulseIR(580);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(560);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(580);
delayMicroseconds(1680);
pulseIR(580);
delayMicroseconds(1680);
pulseIR(600);
delayMicroseconds(1660);
pulseIR(620);
delayMicroseconds(1640);
pulseIR(580);
delayMicroseconds(1660);
pulseIR(9120);
delayMicroseconds(41200);
pulseIR(580);
delayMicroseconds(2240);
pulseIR(9120);
delayMicroseconds(31244);
pulseIR(580);
delayMicroseconds(2260);
pulseIR(9100);
delayMicroseconds(31264);
pulseIR(600);
delayMicroseconds(2240);
      
      delay(65); // wait 65 milliseconds before sending it again
}
