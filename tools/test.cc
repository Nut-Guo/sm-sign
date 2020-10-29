#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sm2.h>
#include <fstream>
#include "key.h"
#include "sm.h"
// #include "test.h"
// int test_evp_sm2_signature_verify()
// {
//     int ret = 0, i = 0;
//     unsigned char sign_out[1024];
//     unsigned char plain_in[] = "hello carlos.";
//     unsigned int out_len = 256;
//     unsigned char dgst[32];
//     unsigned int dgst_len = 32;
//     size_t in_len = strlen((char *)plain_in);
//     sm3(plain_in, in_len, dgst);
//     printf("hash:");
//     for (i = 0; i < dgst_len; i++)
//     {
//         printf("%02X", dgst[i]);
//     }
//     printf("\n");
//     EVP_PKEY *privkey = read_private_key(PRIVATE_SM2_KEY_FILE, "12345678");
//     EC_KEY *priv_eckey = NULL;
//     priv_eckey = EVP_PKEY_get1_EC_KEY(privkey);
//     ret = SM2_sign(NID_undef, dgst, dgst_len, sign_out, &out_len, priv_eckey);
//     if (ret == 0) {
//         printf("sm2 signature failed!\n");
//         return ret;
//     }
//     printf("sm2 openssl sign len = %d, signature result: \n", out_len);
//     for(i = 0; i < out_len; i++) {
//         printf("%02X", sign_out[i]);
//     }
//     printf("\n");
//     EVP_PKEY *pubkey = read_public_key(PUBLIC_SM2_KEY_FILE);
//     EC_KEY *pub_eckey = NULL;
//     pub_eckey = EVP_PKEY_get1_EC_KEY(pubkey);
//     ret = SM2_verify(NID_undef, dgst, dgst_len, sign_out, out_len, pub_eckey);
//     if (ret == -1) {
//         ret = -1;
//         printf("sm2 verify failed!\n");
//     } else {
//         ret = 0;
//         printf("sm2 verify succeed!\n");
//     }
//     return ret;
// }

// int test_evp_sm2_encrypt_decrypt()
// {
//     int ret = 0, i = 0;
//     unsigned char cipher_out[1024];
//     unsigned char plain_in[] = "hello carlos sm2...";
//     size_t out_len = 1024;
//     size_t in_len = strlen((char*)plain_in);
//     EVP_PKEY *pubkey = read_public_key(PUBLIC_SM2_KEY_FILE);
//     EC_KEY *pub_eckey = NULL;
//     pub_eckey = EVP_PKEY_get1_EC_KEY(pubkey);
//     if(pub_eckey == NULL) {
//         printf("error in get_key\n");
//         return ret;
//     }
//     SM2_encrypt_with_recommended(plain_in, strlen((char *)plain_in), cipher_out, &out_len, pub_eckey);
//     printf("sm2 plain text is : %s \n", plain_in);
//     printf("sm2 cipher len = %d text is :\n", out_len);
//     for (i = 0; i < out_len; i ++) {
//         printf("%02X", cipher_out[i]);
//     }
//     printf("\n");
//     memset(plain_in, '\0', in_len);
//     in_len = 1;
//     EVP_PKEY *privkey = read_private_key(PRIVATE_SM2_KEY_FILE, "12345678");
//     EC_KEY *priv_eckey = NULL;
//     priv_eckey = EVP_PKEY_get1_EC_KEY(privkey);
//     if(priv_eckey == NULL) {
//         printf("error in get_key\n");
//         return ret;
//     }
//     SM2_decrypt_with_recommended(cipher_out, out_len, plain_in, &in_len, priv_eckey);
//     printf("sm2 decrypt len = %d  and text is : %s \n", in_len, plain_in);
//     return ret;
// }

// void test_sign_cert(const char * x509, const char *priv_pem, const char* passwd, const char* cert_sf, const char* cert_sm2_file) {
//     sign_cert_sm2(x509 , priv_pem, passwd, cert_sf, cert_sm2_file);
// }

#define PUB_KEY_FILE "pub.pem"
#define PRI_KEY_FILE "pri.pem"
#define PRI_PKCS8 "pri.pk8"
#define PASSWD "12345678"
// void test_pkcs8() {
//     generate_SM2_key_files(PUB_KEY_FILE, PRI_KEY_FILE, string(PASSWD));
//     EVP_PKEY* priv_key = read_private_key(PRI_KEY_FILE, PASSWD);
//     write_pkcs8(PRI_PKCS8, priv_key);
//     EVP_PKEY *priv_res = read_pkcs8(PRI_PKCS8);
// }

bool pkcs7_verify_file(string p7s, string data)
{
    BIO *p7p = BIO_new(BIO_s_file());
    BIO_write(p7p, (void *)p7s.c_str(), p7s.size());
    PKCS7 *p7 = NULL;
    ERR_load_PKCS7_strings();
    if (p7p == NULL)
    {
        BIO_printf(p7p, "load error!\n");
    }
    // const unsigned char *pcs = (unsigned char *)p7s.c_str();
    // unsigned char* pcs = new unsigned char[p7s.size()];
    // memcpy(pcs, p7s.c_str(), p7s.size());
    /* cout << p7s; */
    p7 = d2i_PKCS7(&p7, (const unsigned char **)&p7s[0], (int)p7s.size());
    if (p7 == NULL)
    {
        printf("PKCS7 Wrong\n");
        return false;
    }
    cout << "Success!\n"
         << endl;
    BIO *bdata = BIO_new(BIO_s_mem());
    BIO *out = BIO_new(BIO_s_mem());
    //
    BIO_write(bdata, (void *)data.c_str(), data.size());
    // printf("%s", out);
    int flags = PKCS7_NOVERIFY;
    bool ret = PKCS7_verify(p7, NULL, NULL, bdata, out, flags);
    // bool ret = true;
    BIO_free_all(bdata);
    BIO_free_all(out);
    BIO_free_all(p7p);
    return ret;
}
int main(int argc, char *argv[])
{
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_digests();
    EVP_add_digest(EVP_sm3());
    generate_SM2_key_files(PUB_KEY_FILE, PRI_KEY_FILE, PASSWD);
    // test_evp_sm2_signature_verify();
    // test_evp_sm2_encrypt_decrypt();
    // test_sign_cert(argv[1], argv[2], argv[3], argv[4], argv[5]);
    // test_pkcs8();
    EVP_PKEY *priv_key = read_private_key(PRI_KEY_FILE, PASSWD);
    EVP_PKEY *pub_key = read_public_key(PUB_KEY_FILE);
    X509 *x509 = generate_x509(priv_key, pub_key, "test.x509");
    string test_data = "Hello1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 2\0 qwer";
    ifstream inf("/mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/README.md");
    inf >> test_data;
    cout << test_data;
    inf.close();
    string pkcs7 = pkcs7_sign(x509, priv_key, test_data);
    // cout << pkcs7 << endl;
    // ofstream p("test.pk7");
    // p << pkcs7;
    // p.close();
    // cout << "OK";
    if (pkcs7_verify(pkcs7, test_data))
    {
        printf("Verify success!\n");
    }
    else
    {
        printf("Verify failed!\n");
    }
}