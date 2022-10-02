void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);  // LED on pin 13 of UNO
}

short rx_byte = 0;

void loop() {
  if (Serial.available() > 0) {    // is a character available?
    //rx_byte = Serial.read();
      rx_byte = Serial.parseInt();
  
    switch (rx_byte) {
      case 1:
        digitalWrite(13, HIGH);
        Serial.println("LED is ON");
      break;
      
      case 2:
        digitalWrite(13, LOW);
        Serial.println("LED is OFF");
      break;
      
      case 3:
        Serial.println("------- MENU -------");
        Serial.println("1. Switch LED on.");
        Serial.println("2. Switch LED off.");
        Serial.println("3. This menu.");
        Serial.println("--------------------");
      break;
      
      default:
        Serial.println("Invalid option");
      break;
    } // end: switch (rx_byte)
  } // end: if (Serial.available() > 0)
}