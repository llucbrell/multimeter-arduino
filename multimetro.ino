// customizable variables
float R1 = 98600.0; // resistance R1 (100K)
float R2 = 9980.0; // resistance R2 (10K)
int refresh = 1000;
int sampleRatio = 1000;

// reference variables
byte maxVoltSuport = 5;
int atmegaBits = 1024;

//counters
long totalTime = 0;
unsigned long samples = 0;
long timeRuning = 0;
unsigned long count=0;

//values
float vMax = 0.0;
float vMin = 10000.0;
float vTotal = 0.0;
float vAveragePerSample = 0.0;
float myResolution = 0.0;
float power=0.0;
float maxPower=0.0;
float minPower=10000.0;
float aPower = 0.0;
float pTotal =0.0;
float vout = 0.0;
float vin = 0.0;
float ain = 0.0;
float value = 0.0;

//pin numbers
byte analogInput = 0;

//START
void setup() {
  myResolution= ((float) maxVoltSuport/ (float) atmegaBits)*1000;
  pinMode(analogInput, INPUT);
  Serial.begin(9600);
  Serial.print("           MULTIMETER -- ");
  Serial.print(myResolution);
  Serial.println(" mV step-resolution");
  Serial.println("                      llucbrell@gmail.com");
  Serial.println();
  Serial.println();
}
void loop() {
  
  //number of samples and time to make an average
  samples = samples + 1;
  count = samples/sampleRatio;
  totalTime = totalTime + 1;
  
  // read the value at analog input
  value = analogRead(analogInput);

  //voltage calculations
  vout = (value * 5.0) / 1024.0;
  timeRuning = totalTime/sampleRatio;
  vin = vout / (R2 / (R1 + R2));
  vTotal = vin + vTotal;
  vAveragePerSample = vTotal / samples;
  
  // calculate the current in miliamps
  ain = vin / ((R1 + R2) / 1000); 
  
  // power calculations in miliwatts
  power= ((vin*vin)/(R1+R2))*1000;
  pTotal = power+ pTotal;
  aPower= pTotal /samples;
  maxPower= ((vMax*vMax)/(R1+R2))*1000;
  minPower= ((vMin*vMin)/(R1+R2))*1000;
  
  // set the max and min values
  if (vin > vMax) {
    vMax = vin;
  }
  if (vin < vMin && vin != 0) {
    vMin = vin;
  }
   if (power > maxPower) {
    maxPower = power;
  }
  if (power < minPower && minPower != 0) {
    minPower = power;
  }

  // print values on the screen using the refresh value and serial
  if(samples%refresh==0){
    
  Serial.print(" VOLTAGE");
  Serial.print(" Last=");
  Serial.print(vin );
  Serial.print("v " );
  Serial.print("Max=");
  Serial.print(vMax );
  Serial.print("v " );
  if (vMin == 10000.0) {
    Serial.print("Min=");
    Serial.print( 0.00);
    Serial.print("v " );
  }
  else{
  Serial.print("Min=");
  Serial.print(vMin );
  Serial.print("v " );
  }
  Serial.print("Total=");
  Serial.print(vTotal/sampleRatio );
  Serial.print(" Average/Sample=");
  Serial.print(vAveragePerSample );
  Serial.println();

  Serial.print(" POWER Last=");
  Serial.print(power);
  Serial.print("mW ");
  Serial.print(" Max=");
  Serial.print(maxPower);
  Serial.print("mW ");
  Serial.print(" Min=");
  Serial.print(minPower);
  Serial.print("mW ");
  Serial.print(" Average=");
  Serial.print(aPower);
  Serial.println("mW ");
  Serial.print( " ENERGY Last=");
  Serial.print(power*3600);
  Serial.print("kJ/h ");
  Serial.print(power/1000);
  Serial.println("w/h ");

  Serial.print(" REFS TimeOn=");
  Serial.print(timeRuning);
  Serial.print("s " );
  Serial.print(" Sample-count=");
  Serial.print(count );
  Serial.print("e^10 ");
  Serial.print(" Sample-ratio=");
  Serial.print((long)sampleRatio*60);
  Serial.print("smp/min");
  Serial.print(" Screen-refresh=");
  Serial.print(refresh);
  Serial.println("smp/sec");


  //end and separation
  Serial.println();
  delay(refresh);
  }
}
