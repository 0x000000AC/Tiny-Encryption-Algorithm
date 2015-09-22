#include <stdio.h>
#include <stdint.h>

uint32_t KEY[4];  // Key space for bit shifts

void encrypt(uint32_t* v) {
  uint32_t v0=v[0], v1=v[1], sum=0, i;             // set up
  uint32_t delta=0x9e3779b9;                       // a key schedule constant
  for (i=0; i < 32; i++) {                         // basic cycle start
    sum += delta;
    v0 += ((v1<<4) + KEY[0]) ^ (v1 + sum) ^ ((v1>>5) + KEY[1]);
    v1 += ((v0<<4) + KEY[2]) ^ (v0 + sum) ^ ((v0>>5) + KEY[3]);  
  }                                                // end cycle 
  v[0]=v0; v[1]=v1;
}       

void decrypt (uint32_t* v) {
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  // set up 
    uint32_t delta=0x9e3779b9;                     // a key schedule constant 
    for (i=0; i<32; i++) {                         // basic cycle start 
        v1 -= ((v0<<4) + KEY[2]) ^ (v0 + sum) ^ ((v0>>5) + KEY[3]);
        v0 -= ((v1<<4) + KEY[0]) ^ (v1 + sum) ^ ((v1>>5) + KEY[1]);
        sum -= delta;
    }                                              // end cycle 
    v[0]=v0; v[1]=v1;
}

int main()
{
		uint32_t v[] = {0xFFFFFFFF, 0xFFFFFFFF};
	
		// uint32_t v[] = {0xLJBLKECB, 0x0CELCIMF};
		// 64 bit ASCII->HEX translation of LJBLKECB: 4C4A424C4B454342  
		// 64 bit ASCII->HEX trnaslation of 0CELCIMF: 3043454C43494D46
		
		printf(" Original Values: ");
		printf("[ %X %X ]", v[0], v[1]);
		
        encrypt(v);

        printf("\n Encrypted:       ");
        printf("[ %X %X ]", v[0], v[1]);

        decrypt(v);
        printf("\n Decrypted:       ");
        printf("[ %X %X ]", v[0], v[1]);
        printf("\n");

        return 0;
}
