#include "Windows.h"

void randombytes(unsigned char * ptr,unsigned int length) 
{
	static HCRYPTPROV prov = 0;
	if (prov == 0) {
		CryptAcquireContext( &prov,NULL,NULL,PROV_RSA_FULL,0);
	}
	CryptGenRandom(prov, length, ptr);
}