#include "sha1.h"

void printHash(uint8_t* hash) {
  int i;
  for (i=0; i<20; i++) Serial.println(hash[i]);
  Serial.println();
}

uint8_t hmacKey1[]={   0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0xde, 0xad, 0xbe, 0xef, 0x6f, 0x21, 0xde, 0xad, 0xbe, 0xef };

long birthTime = 1339345870;
long intern = 0;
long oldOtp = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  if(intern == 0) intern = birthTime;
  else{
  
   uint8_t byteArray[8];   
   long time = intern / 30;
              
   byteArray[0] = 0x00;
   byteArray[1] = 0x00;
   byteArray[2] = 0x00;
   byteArray[3] = 0x00;
   byteArray[4] = (int)((time >> 24) & 0xFF) ;
   byteArray[5] = (int)((time >> 16) & 0xFF) ;
   byteArray[6] = (int)((time >> 8) & 0XFF);
   byteArray[7] = (int)((time & 0XFF));
  
   uint8_t* hash;
   uint32_t a; 
   Sha1.initHmac(hmacKey1,16);
   Sha1.writebytes(byteArray, 8);
   hash = Sha1.resultHmac();
  
   int hash2[20];
   int k;
  
  //for(k=0; k<20; k++){
    
   // hash2[k] = (int)hash[k];

    
  //}
  
   int  offset = hash[20 - 1] & 0xF; 
   long truncatedHash = 0;
   int j;
   for (j = 0; j < 4; ++j) {
    truncatedHash <<= 8;
    truncatedHash  |= hash[offset + j];
   }
    
   truncatedHash &= 0x7FFFFFFF;
   truncatedHash %= 1000000;
  
   if(truncatedHash != oldOtp){
    oldOtp = truncatedHash;
    Serial.println(truncatedHash);
   }
   
   delay(1000);
   intern++;     
  }
  
  
}
