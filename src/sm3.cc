#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "sm3.h"

void handleErrors()
{
	printf("SM3 Error!\n");
}

void openssl_evp_sm3_digest(const unsigned char *message, size_t message_len, unsigned char *md_value, unsigned int *md_len)
{
	EVP_MD_CTX *mdctx;
	const EVP_MD *md;
	md_value = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sm3()));
	unsigned int i;
	md = EVP_sm3();
	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, message, message_len);
	EVP_DigestFinal_ex(mdctx, md_value, md_len);
	EVP_MD_CTX_free(mdctx);

	// printf("Digest is: ");
	// for (i = 0; i < *md_len; i++)
	// 	printf("%02x", md_value[i]);
	// printf("\n");

	// exit(0);
}