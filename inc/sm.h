#ifndef SIGN_SM_H
#define SIGN_SM_H
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/sm3.h>
#include <openssl/sm2.h>
#include <openssl/pkcs7.h>
#include <openssl/bio.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "key.h"
using namespace std;

extern string SM3(string data);
extern EC_KEY *generate_SM2_key_files(string pub_keyfile, string pri_keyfile, string passwd);
extern string SM2_SIGN(string data, EVP_PKEY *privkey);
extern bool SM2_VERIFY(string data, string sig, EVP_PKEY *pubkey);
extern string pkcs7_sign(X509 *x509, EVP_PKEY *privkey, string cert_sf);
#endif