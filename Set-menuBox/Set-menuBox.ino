void setup() {
  Serial.begin(9600);
  
  // draw the menu box
  DashedLine(24);
  Serial.println("| Program Options Menu |");
  DashedLine(24);
}

void loop() {
}

void DashedLine(int len)
{
  int i;
  
  // draw the line
  for (i = 0; i < len; i++) {
    Serial.print("-");
  }
  // move the cursor to the next line
  Serial.println("");
}