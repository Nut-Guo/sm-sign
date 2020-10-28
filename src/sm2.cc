#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <openssl/sm2.h>
#include "sm2.h"

// int generate_sm2_key_files(const char *pub_keyfile, const char *pri_keyfile,
//                            const unsigned char *passwd, int passwd_len)
// {
//     int ret = 0;
//     EC_KEY *ec_key = NULL;
//     EC_GROUP *ec_group = NULL;
// #ifdef MAKE_KEY_TO_RAM
//     size_t prikey_len = 0;
//     size_t pubkey_len = 0;
//     unsigned char *prikey_buffer = NULL;
//     unsigned char *pubkey_buffer = NULL;
// #endif
//     BIO *pri_bio = NULL;
//     BIO *pub_bio = NULL;

//     ec_key = EC_KEY_new();
//     if (ec_key == NULL)
//     {
//         ret = -1;
//         printf("EC_KEY_new() failed return NULL.\n");
//         goto finish;
//     }
//     ec_group = EC_GROUP_new_by_curve_name(NID_sm2p256v1);
//     if (ec_group == NULL)
//     {
//         ret = -1;
//         printf("EC_GROUP_new_by_curve_name() failed, return NULL.\n");
//         goto finish;
//     }
//     ret = EC_KEY_set_group(ec_key, ec_group);
//     if (ret != 1)
//     {
//         printf("EC_KEY_set_group() failed, ret = %d\n", ret);
//         ret = -1;
//         goto finish;
//     }
//     ret = EC_KEY_generate_key(ec_key);
//     if (!ret)
//     {
//         printf("EC_KEY_generate_key() failed, ret = %d\n", ret);
//         ret = -1;
//         goto finish;
//     }
//     printf("Create sm2 private key ok!\n");
// #ifdef MAKE_KEY_TO_RAM
//     pri_bio = BIO_new(BIO_s_mem());
// #else
//     pri_bio = BIO_new(BIO_s_file());
// #endif
//     if (pri_bio == NULL)
//     {
//         ret = -1;
//         printf("pri_bio = BIO_new(BIO_s_file()) failed, return NULL. \n");
//         goto finish;
//     }
//     ret = BIO_write_filename(pri_bio, (void *)pri_keyfile);
//     if (ret <= 0)
//     {
//         printf("BIO_write_filename error!\n");
//         goto finish;
//     }
//     ret = PEM_write_bio_ECPrivateKey(pri_bio, ec_key, EVP_sm4_cbc(), (unsigned char *)passwd, passwd_len, NULL, NULL);
//     if (ret != 1)
//     {
//         printf("PEM_write_bio_ECPrivateKey error! ret = %d \n", ret);
//         ret = -1;
//         goto finish;
//     }
// #ifdef MAKE_KEY_TO_RAM
//     pub_bio = BIO_new(BIO_s_mem());
// #else
//     pub_bio = BIO_new(BIO_s_file());
// #endif
//     if (pub_bio == NULL)
//     {
//         ret = -1;
//         printf("pub_bio = BIO_new(BIO_s_file()) failed, return NULL. \n");
//         goto finish;
//     }
//     ret = BIO_write_filename(pub_bio, (void *)pub_keyfile);
//     if (ret <= 0)
//     {
//         printf("BIO_write_filename error!\n");
//         goto finish;
//     }
//     ret = PEM_write_bio_EC_PUBKEY(pub_bio, ec_key);
//     if (ret != 1)
//     {
//         ret = -1;
//         printf("PEM_write_bio_EC_PUBKEY error!\n");
//         goto finish;
//     }
//     printf("Create sm2 public key ok!\n");
// #ifdef MAKE_KEY_TO_RAM
//     PEM_write_bio_EC_PUBKEY(pub_bio, ec_key);
//     prikey_len = BIO_pending(pri_bio);
//     pubkey_len = BIO_Pending(pub_bio);
//     prikey_buffer = (unsigned char *)OPENSSL_malloc((prikey_len + 1) * sizeof(unsigned char));
//     if (prikey_buffer == NULL)
//     {
//         ret = -1;
//         printf("prikey_buffer OPENSSL_malloc failed, return NULL. \n");
//         goto finish;
//     }
//     pubkey_buffer = (unsigned char *)OPENSSL_malloc((pubkey_len + 1) * sizeof(unsigned char));
//     if (pubkey_buffer == NULL)
//     {
//         ret = -1;
//         printf("pubkey_buffer OPENSSL_malloc failed, return NULL. \n");
//         goto finish;
//     }
//     BIO_read(pri_bio, prikey_buffer, prikey_len);
//     BIO_read(pub_bio, pubkey_buffer, pubkey_len);
//     prikey_buffer[prikey_len] = '\0';
//     pubkey_buffer[pubkey_len] = '\0';
// #endif
// finish:
//     if (ec_key != NULL)
//         EC_KEY_free(ec_key);
//     if (ec_group != NULL)
//         EC_GROUP_free(ec_group);
// #ifdef MAKE_KEY_TO_RAM
//     if (prikey_buffer != NULL)
//         OPENSSL_free(prikey_buffer);
//     if (pubkey_buffer != NULL)
//         OPENSSL_free(pubkey_buffer);
// #endif
//     if (pub_bio != NULL)
//         BIO_free_all(pub_bio);
//     if (pri_bio != NULL)
//         BIO_free_all(pri_bio);
//     return ret;
// }