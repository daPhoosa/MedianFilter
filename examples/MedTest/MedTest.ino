//#include <Arduino.h>
#include <MedianFilter.h>

MedianFilter test(31);

int i=0;
int j;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Serial.println("*** Program Start ***");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly: 
  i = int(random(-9, 9));
  test.write(i);
  j = test.read();
  
  Serial.println(i);
  test.printData();

  //i++;

  delay(500);
  
}
