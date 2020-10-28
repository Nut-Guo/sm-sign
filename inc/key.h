#ifndef SIGN_KEY_H
#define SIGN_KEY_H
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
// extern EC_KEY *generate_sm2_key_files(const char *pub_keyfile, const char *pri_keyfile,
//    const unsigned char *passwd, int passwd_len);

extern EVP_PKEY *read_private_key(const char *file_name, const char *passwd);
extern EVP_PKEY *read_public_key(const char *file_name);
X509 *generate_x509(EVP_PKEY *pkey, EVP_PKEY *request, string x509_file);
// bool write_to_disk(EVP_PKEY *pkey, X509 *x509, string x509_file);
void write_pkcs8(const char *filename, EVP_PKEY *pkey, string passwd);
EVP_PKEY *read_pkcs8(const char *file_name);
#endif