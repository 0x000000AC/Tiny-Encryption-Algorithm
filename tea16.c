#include <stdio.h>
#include <stdint.h>

uint16_t KEY[4];

void encrypt(uint16_t *v) {
  uint16_t v0=v[0], v1=v[1], sum=0, i;           // set up
  uint16_t delta=0x9e37;                         // a key schedule constant
  for (i=0; i < 32; i++) {                       // basic cycle start
    sum += delta;
    v0 += ((v1<<4) + KEY[0]) ^ (v1 + sum) ^ ((v1>>5) + KEY[1]);
    v1 += ((v0<<4) + KEY[2]) ^ (v0 + sum) ^ ((v0>>5) + KEY[3]);  
  }                                              // end cycle 
  v[0]=v0; v[1]=v1;
}       

void decrypt (uint16_t* v) {
    uint16_t v0=v[0], v1=v[1], sum=0xC6E0, i;  		// set up 
    uint16_t delta=0x9e37;                     		// a key schedule constant 
    for (i=0; i<32; i++) {                     		// basic cycle start 
        v1 -= ((v0<<4) + KEY[2]) ^ (v0 + sum) ^ ((v0>>5) + KEY[3]);
        v0 -= ((v1<<4) + KEY[0]) ^ (v1 + sum) ^ ((v1>>5) + KEY[1]);
        sum -= delta;
    }                                               // end cycle 
    v[0]=v0; v[1]=v1;
}

int main()
{
        // uint16_t is the same as an unsigned short
        // It's equal to 2 bytes or 16 bits
        // Each hex is a nibble so 0xFFFF or 65535 is max val
        uint16_t v[] = {0xFFFF, 0xFFFF};
		
		printf(" Original: ");
		printf(" [ %X %X ]", v[0], v[1]);
		
        encrypt(v);
        printf("\n Encrypted: ");
        printf("[ %X %X ]", v[0], v[1]);

        decrypt(v);
        printf("\n Decrypted: ");
        printf("[ %X %X ]", v[0], v[1]);
        printf("\n");

        return 0;
}
