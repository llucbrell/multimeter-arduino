/*
       dP                dP       dP                                                          dP          
       88                88       88                                                          88          
       88d888b. .d8888b. 88d888b. 88d888b. .d8888b. .d8888b. .d8888b. .d8888b. .d8888b. .d888b88 .d8888b. 
       88'  `88 88'  `88 88'  `88 88'  `88 88ooood8 Y8ooooo. 88'  `"" 88'  `"" 88'  `88 88'  `88 88ooood8 
       88    88 88.  .88 88.  .88 88.  .88 88.  ...       88 88.  ... 88.  ... 88.  .88 88.  .88 88.  ... 
       dP    dP `88888P' 88Y8888' 88Y8888' `88888P' `88888P' `88888P' `88888P' `88888P' `88888P8 `88888P' 
                                                                                                    

                                                                                             
                                   i8@@8Li.                t@8000                                   
                                 .GitL:::GGGC;             G8ifGt80LtL11,.                          
                                  C,Li;i8i;Ci:ti  i11i:;i::i00ii;;ifffi;;f@8                        
                                  ,L;0L88iCf;L01f.   ,;  ifG0101f0t:;:;;;1GC                        
                                    t@80CL0LfC,    ,1i :;ii CGti1;G8fi::fCiL:                       
                                      L0C11tGf;      ,1;   L .;:.         Lii                       
                                      ,i0fLGt;f1.    t:                    1.                       
                                    ;0C8Li;t88L;:,,i  :t,          :1 .,  .t                        
                                  18i;i;1fC8tL,      .             ,  1. :L                         
                                1C:;G8Gf;f;             ::::      ;LG0t. iLG0CCi                    
            ..t0fC0tGt,       iC:ifCGCt:             ;,    ;L  i G1G0C11CLCL1C88CGti                
          ,Li;G01f01C::GC.   C8G1;:;:;              t           ii8@@@@@C  ;G81iGfitCtt1tf:         
        .CiGtL,      :0:;8: Gi:i08@8.           ..                .ifft,       iL:.       .1        
       .0CLfi          Ct;;08Cffti1.          .,                                f.  i   it:         
       t1i:L            0GLf:::;;;i          ;.                                 i  :.  ;   ::       
       0@@@;            ,iGt:::;:1          f                                    ;; ,i  i1ti        
       C@@@.             18888@@8C         .f     :t11:                               t. i          
       .8@0               G;:::;C8f      :;.L   ,i   , f                                            
                          ff:C8L;;;: t81,:8::f..f    @1 1                                           
                          G0i:::i8L10@8,,ff,f0L0. t@,.f.1                                           
                           C1:18L:i8;88,:Lf8t:f:   : Lt:.                                           
                           ,80C:::8t:L8f:G@G,:L   ,@8  i   ;i.                                      
                            ,8:::t8i::C8C1@8CfG   f@G i ;;    ;1                                    
                              tC:t8f::,;C8C1L0f     .G1f..1 G@,1                                    
                                i0t01::::::f01,f1,iG0;1  Gf    1                                    
                                   :tC00Lt:.      ;G,       8L1.           
                          .LG:;                    f.  f@@1  t.            
                      ,;.0ttC::::                   L   :t: ,:             
                 i;ftttttttt8:::;                    .L.  :1.              
             .:Gtttttfttttttttf;::;                                        
         i8tttttft::Cttttttttt;::::                                        
         tttC,.;;:::::fttttttttt::::;                                      
       ,::1Lt8;:::::::tttttttttt;:::f                                      
     8:0tttttttG;::::::;tttttttttt:::;                                     
   CtfttttttttttG::::::::tttttttttt:::i                                    
   ttttttttttttttt:::::::;tttttttttC:::                                    
    Gtttttttttttttt:::::::Gtttttttttf::t                                   
    .ttttttttttttttt:L.Cii;tttttttttL;f1                                   
     Lttttttttttttttfift,8ttttttttff            
      Gttttttttttttt0fttttttttt,                
       tttttttt1GGttCtLtG8G                     
        .1ft.i,.  t18i           GGGf;;;:::::;::i;:;C  
                t          .ifi:::;:;1fft11if;L11LLf1itC8fi   
                   ;  C8LttttCCLttttttttG1ft1f        
                   :         t                             
                  ;         ;                 Project-->        Multimeter   
                 L        t                 
               C       t                      Author---> Lucas_C/llucbrell/hobbescode         
                 8    C                       
                 ;Ct                          License-->      GNU-license        
  

  
*/



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
