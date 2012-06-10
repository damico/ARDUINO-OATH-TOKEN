#include "sha1.h"

void printHash(uint8_t* hash) {
  int i;
  for (i=0; i<20; i++) {
    //Serial.print("0123456789abcdef"[hash[i]>>4]);
    //Serial.print("0123456789abcdef"[hash[i]&0xf]);
    //Serial.println();
    Serial.println(hash[i]);
  }
  Serial.println();
}

//uint8_t hmacKey1[]={
  // 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
  // 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
  // 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
  // 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f
//};

uint8_t hmacKey1[]={   0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0xde, 0xad, 0xbe, 0xef, 0x6f, 0x21, 0xde, 0xad, 0xbe, 0xef };

long longInt = 1339301915;
long intern = 0;

void setup() {
  
  
  
 uint8_t byteArray[4];
              
 // convert from an unsigned long int to a 4-byte array
 byteArray[0] = 0x00;
 byteArray[1] = 0x00;
 byteArray[2] = 0x00;
 byteArray[3] = 0x00;
 byteArray[4] = (int)((longInt >> 24) & 0xFF) ;
 byteArray[5] = (int)((longInt >> 16) & 0xFF) ;
 byteArray[6] = (int)((longInt >> 8) & 0XFF);
 byteArray[7] = (int)((longInt & 0XFF));
  
  
  
  
  uint8_t* hash;
  uint32_t a;
  
  Serial.begin(9600);

 
  // HMAC tests
  //Serial.println("Test: FIPS 198a A.1");
  //Serial.println("Expect:4f4ca3d5d68ba7cc0a1208c9c61e9c5da0403c0a");
  //Serial.print("Result:");
  Sha1.initHmac(hmacKey1,16);
  //Sha1.print("DAMICAO");
  
  //uint8_t time[]={ 0x00, 0x00, 0x00, 0x00, 0x02, 0xa9, 0x25, 0xbd }; //06/08/2012 - 17:18:29
  Sha1.writebytes(byteArray, 8);

  hash = Sha1.resultHmac();
  printHash(hash);
  Serial.println();
  
  
  int hash2[20];
  
  int k;
  for(k=0; k<20; k++){
    
    hash2[k] = (int)hash[k];
//    Serial.println(hash2[k]);
    
  }

  
  int  offset = hash2[20 - 1] & 0xF; 
  Serial.print("OFFSET:");
  Serial.println(offset);
 
  long truncatedHash = 0;
  int j;
  for (j = 0; j < 4; ++j) {
    truncatedHash <<= 8;
    truncatedHash  |= hash2[offset + j];
    
    Serial.print(truncatedHash);
    Serial.print(" > ");
    Serial.print(hash[offset + j]);
    Serial.print("\n");
    Serial.println();
  }
    
  truncatedHash &= 0x7FFFFFFF;
  
  
  Serial.print("FINAL:");
  Serial.println(truncatedHash);
  Serial.println();
  
  truncatedHash %= 1000000;
  
  Serial.println(truncatedHash);


 

  //Serial.println(byteArray);

}
long oldOtp = 0;
void loop() {
  
  
  
  if(intern == 0) intern = longInt;
  else{
  
    uint8_t byteArray[8];
    
    long time = intern / 30;
              
 // convert from an unsigned long int to a 4-byte array
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
  for(k=0; k<20; k++){
    
    hash2[k] = (int)hash[k];

    
  }

  
  int  offset = hash2[20 - 1] & 0xF; 
  long truncatedHash = 0;
  int j;
  for (j = 0; j < 4; ++j) {
    truncatedHash <<= 8;
    truncatedHash  |= hash2[offset + j];
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
