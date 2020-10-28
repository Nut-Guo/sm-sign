#ifndef OPENSSL_KEYGEN_H
#define OPENSSL_KEYGEN_H
#include <openssl/x509.h>
#include <openssl/pem.h>
extern EVP_PKEY *generate_key();
extern X509 *generate_x509(EVP_PKEY *pkey);
extern bool write_to_disk(EVP_PKEY *pkey, X509 *x509);
#endif