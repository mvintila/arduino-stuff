/*
Measuring Current Using ACS712
*/
const int c[] = { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 };
const int v = A15;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2480; 
double Voltage = 0;
double Amps = 0;
/* 
 * Resistors used to measure supply voltage
*/
float R1 = 40100; // resistance of R1
float R2 = 14420; // resistance of R2

void setup(){ 
 Serial.begin(115200);
}

void loop(){
 

  for (int i = 1; i < 11; i++) {
    int values;
    for (int j = 0; j < 50; j++) {
      values += analogRead(c[i]);
    }
    RawValue = values / 50;
    values = 0;
    Voltage = (RawValue / 1024.0) * 4970; // Gets you mV
    Amps = ((Voltage - ACSoffset) / mVperAmp);
    Serial.print("raw{monitor=\"" ); // shows pre-scaled value 
    Serial.print(i);
    Serial.print("\"} ");
    Serial.print(float(RawValue),3); 
    Serial.print("\n");
    Serial.print("milivolts{monitor=\"" ); // shows pre-scaled value 
    Serial.print(i);
    Serial.print("\"} ");
    Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
    Serial.print("\n");
    Serial.print("amps{monitor=\"" ); // shows pre-scaled value 
    Serial.print(i);
    Serial.print("\"} ");
    Serial.print(fabs(Amps),3); // the '3' after voltage allows you to display 3 digits after decimal point
    Serial.print("\n");
  }
  float vin = 0;
  vin = (analogRead(v) * 4.97)/1024 / (R2/(R1+R2));
  Serial.print("volts{monitor=\"batt\"} " ); // shows pre-scaled value 
  Serial.print(vin,3); // the '3' after voltage allows you to display 3 digits after decimal point
  Serial.print("\n");
    
  delay(5000); 
}
