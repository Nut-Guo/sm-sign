#include <openssl/crypto.h>
#include <cstdio>
#include <cstring>
#include <openssl/sm2.h>
#include <openssl/sm3.h>
#include "key.h"

int main(int argc, char *argv[])
{
	// printf("%s \n", SSLeay_version(SSLEAY_VERSION));
	// generate_sm2_key_files(PUBLIC_SM2_KEY_FILE, PRIVATE_SM2_KEY_FILE, (const unsigned char *)"12345", 5);
	// test_evp_sm2_signature_verify();
	// test_evp_sm2_encrypt_decrypt();
	// char msg[] = "Hello World\n";
	// unsigned int dgst_len;
	// unsigned char *dgst_buf;
	// // openssl_evp_sm3_digest((unsigned char *)msg, (size_t)(strlen(msg)), dgst_buf, &dgst_len);

	// if (dgst_buf != NULL)
	// {
	// 	for (int i = 0; i < dgst_len; i++)
	// 	{
	// 		printf("%02x", (dgst_buf)[i]);
	// 	}
	// 	puts("\n");
	// }
		

	// unsigned char sm3_digest[SM3_DIGEST_LENGTH];
	// sm3((unsigned char *)msg, strlen(msg), sm3_digest);
	// for (int i = 0; i < SM3_DIGEST_LENGTH; i++)
	// {
	// 	printf("%02x", sm3_digest[i]);
	// }
	// printf("\n");
}