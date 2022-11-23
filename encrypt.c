#include <stdio.h>
#include <stdlib.h>
#include "Hacl_Chacha20Poly1305_32.h"
        
static const int key[8] = {1, 2, 3, 4, 5, 6, 7, 8};
static const int nonce[3] = {9, 10, 11};
static const char tag[] = {};
static char mac[16] = {};
const int page_size = 4096;

int main(int argc, char *argv[]) {
	if (argc != 3)
		printf("%s [decrypt] [encrypt]\n", argv[0]);
	
	FILE *file_read = fopen(argv[1], "r");
	fseek(file_read, 0, SEEK_END);
	long size = ftell(file_read);
	fseek(file_read, 0, SEEK_SET);
	FILE *file_write = fopen(argv[2], "w");
	void *buffer = malloc(page_size);
	void *encry_buf = malloc(page_size);
	while (size >= page_size) {
		fread(buffer, 1, page_size, file_read);
        	Hacl_Chacha20Poly1305_32_aead_encrypt(
                	(uint8_t *)key,
                	(uint8_t *)nonce,
                	0,
                	(uint8_t *)tag,
                	page_size,
                	(uint8_t *)buffer,
                	(uint8_t *)encry_buf,
                	(uint8_t *)mac
        	);
		//memcpy(encry_buf, buffer, page_size);
		fwrite(encry_buf, 1, page_size, file_write);
		size -= page_size;
	}
	if (size > 0) {
		fread(buffer, 1, size, file_read);
        	Hacl_Chacha20Poly1305_32_aead_encrypt(
                	(uint8_t *)key,
                	(uint8_t *)nonce,
                	0,
                	(uint8_t *)tag,
                	size,
                	(uint8_t *)buffer,
                	(uint8_t *)encry_buf,
                	(uint8_t *)mac
        	);
		//memcpy(encry_buf, buffer, size);
		fwrite(encry_buf, 1, size, file_write);
	}
	fclose(file_read);
	fclose(file_write);
	return 0;
}
