//#include <Arduino.h>
#include <MedianFilter.h>

MedianFilter test(31, 0);

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
  test.in(i);
  j = test.out();
  
  Serial.print(i);
  Serial.print("\t");
  Serial.println(j);

  //i++;

  delay(500);
  
}
