#ifndef OPENSSL_SM3_H
#define OPENSSL_SM3_H

#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/x509.h>
void openssl_evp_sm3_digest(const unsigned char *message, size_t message_len, unsigned char *md, unsigned int *md_len);

#endif