#include "aes.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t * in;
uint8_t * out;
uint8_t * key;
int keysize;
int main(int argc, char ** argv){
  char mode = argv[1][0];
  int ksize = atoi(argv[2]);
  hexToraw(argv[5], ksize / 4, &key, &keysize);
  

  FILE * file = fopen(argv[3], "r");
  FILE * ofile = fopen(argv[4], "w");
  fseek(file, 0L, SEEK_END);
  long bufsize = ftell(file);
  fseek(file, 0L, SEEK_SET);

  in = malloc(sizeof(char) * bufsize + 1);
  int pad = (!(bufsize % 16)) ? 0 : 16 - (bufsize % 16);
  out = malloc(sizeof(char) * bufsize + pad);
  long length = fread(in, sizeof(char), bufsize, file);
  in[length + 1] = '\0';

  long encoded = 0;

  while(length > encoded){
    uint8_t * tout;
    if(length - encoded > 16){
      tout = out + encoded;
    } else {
      tout = malloc(16 * sizeof(uint8_t));
      memcpy(tout, in + encoded, length - encoded);
    }

    switch(mode){
    case 'd':
      switch(ksize){
      case 128:
	aes_128_decrypt(in + encoded, &tout, key);
	break;
      case 192:
	aes_192_decrypt(in + encoded, &tout, key);
	break;
      case 256:
	aes_256_decrypt(in + encoded, &tout, key);
	break;
      }
      break;
    case 'e':
      switch(ksize){
      case 128:
	aes_128_encrypt(in + encoded, &tout, key);
	break;
      case 192:
	aes_192_encrypt(in + encoded, &tout, key);
	break;
      case 256:
	aes_256_encrypt(in + encoded, &tout, key);
	break;
      }
    }
    memcpy(out + encoded, tout, 16);
    encoded += 16;
  }
  fwrite(out, sizeof(char), bufsize + pad, ofile);

  fclose(file);
  fclose(ofile);
  free(out);
  free(in);
}
