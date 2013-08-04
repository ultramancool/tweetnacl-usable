#ifdef WIN32
#include "Windows.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>

void randombytes(unsigned char * ptr,unsigned int length) 
{
	char failed = 0;
#ifdef WIN32
	static HCRYPTPROV prov = 0;
	if (prov == 0) {
		CryptAcquireContext( &prov,NULL,NULL,PROV_RSA_FULL,0);
	}
	CryptGenRandom(prov, length, ptr);
#else
	FILE* fh = fopen("/dev/urandom", "rb");
	if (fh != NULL) {
		if (fread(ptr, length, 1, fh) == 0) {
			failed = 1;
		}
		fclose(fh);
	} else {
		failed = 1;
	}	
#endif
	/* 
         * yes, this is horrible error handling but we don't have better 
         * options from here and I don't want to start changing the design 
         * of the library 
         */
	if (failed) {
		fprintf(stderr, "Generating random data failed. Please report "
                                "this to https://github.com/ultramancool\n");
		exit(1);
	}
}
