#include "sm.h"

string SM3(string data)
{
    string ret;
    char *dgst = (char *)malloc(32 * sizeof(unsigned char));
    sm3((unsigned char *)data.c_str(), data.size(), (unsigned char *)dgst);
    // for (int i = 0; i < 32; i++)
    //     printf("%02hhx", dgst[i]);
    // printf("\n");
    FILE *fp = fopen("/tmp/sm", "wb+");
    fwrite(dgst, sizeof(char), 32, fp);
    fclose(fp);
    ret.assign(dgst, 32);
    // for (int i = 0; i < 32; i++)
    // 	printf("%2x", dgst[i]);
    // cout <<data<<endl;
    // printf("\n");
    return ret;
}

EC_KEY *generate_SM2_key_files(string pub_keyfile, string pri_keyfile,
                               string passwd)
{
    int ret = 0;
    EC_KEY *ec_key = NULL;
    EC_GROUP *ec_group = NULL;
#ifdef MAKE_KEY_TO_RAM
    size_t prikey_len = 0;
    size_t pubkey_len = 0;
    unsigned char *prikey_buffer = NULL;
    unsigned char *pubkey_buffer = NULL;
#endif
    BIO *pri_bio = NULL;
    BIO *pub_bio = NULL;

    ec_key = EC_KEY_new();
    if (ec_key == NULL)
    {
        ret = -1;
        printf("EC_KEY_new() failed return NULL.\n");
        goto finish;
    }
    ec_group = EC_GROUP_new_by_curve_name(NID_sm2p256v1);
    if (ec_group == NULL)
    {
        ret = -1;
        printf("EC_GROUP_new_by_curve_name() failed, return NULL.\n");
        goto finish;
    }
    ret = EC_KEY_set_group(ec_key, ec_group);
    if (ret != 1)
    {
        printf("EC_KEY_set_group() failed, ret = %d\n", ret);
        ret = -1;
        goto finish;
    }
    ret = EC_KEY_generate_key(ec_key);
    if (!ret)
    {
        printf("EC_KEY_generate_key() failed, ret = %d\n", ret);
        ret = -1;
        goto finish;
    }
    printf("Create sm2 private key ok!\n");
#ifdef MAKE_KEY_TO_RAM
    pri_bio = BIO_new(BIO_s_mem());
#else
    pri_bio = BIO_new(BIO_s_file());
#endif
    if (pri_bio == NULL)
    {
        ret = -1;
        printf("pri_bio = BIO_new(BIO_s_file()) failed, return NULL. \n");
        goto finish;
    }
    ret = BIO_write_filename(pri_bio, (void *)pri_keyfile.c_str());
    if (ret <= 0)
    {
        printf("BIO_write_filename error!\n");
        goto finish;
    }
    ret = PEM_write_bio_ECPrivateKey(pri_bio, ec_key, EVP_sm4_cbc(), (unsigned char *)passwd.c_str(), passwd.size(), NULL, NULL);
    if (ret != 1)
    {
        printf("PEM_write_bio_ECPrivateKey error! ret = %d \n", ret);
        ret = -1;
        goto finish;
    }
#ifdef MAKE_KEY_TO_RAM
    pub_bio = BIO_new(BIO_s_mem());
#else
    pub_bio = BIO_new(BIO_s_file());
#endif
    if (pub_bio == NULL)
    {
        ret = -1;
        printf("pub_bio = BIO_new(BIO_s_file()) failed, return NULL. \n");
        goto finish;
    }
    ret = BIO_write_filename(pub_bio, (void *)pub_keyfile.c_str());
    if (ret <= 0)
    {
        printf("BIO_write_filename error!\n");
        goto finish;
    }
    ret = PEM_write_bio_EC_PUBKEY(pub_bio, ec_key);
    if (ret != 1)
    {
        ret = -1;
        printf("PEM_write_bio_EC_PUBKEY error!\n");
        goto finish;
    }
    printf("Create sm2 public key ok!\n");
#ifdef MAKE_KEY_TO_RAM
    PEM_write_bio_EC_PUBKEY(pub_bio, ec_key);
    prikey_len = BIO_pending(pri_bio);
    pubkey_len = BIO_Pending(pub_bio);
    prikey_buffer = (unsigned char *)OPENSSL_malloc((prikey_len + 1) * sizeof(unsigned char));
    if (prikey_buffer == NULL)
    {
        ret = -1;
        printf("prikey_buffer OPENSSL_malloc failed, return NULL. \n");
        goto finish;
    }
    pubkey_buffer = (unsigned char *)OPENSSL_malloc((pubkey_len + 1) * sizeof(unsigned char));
    if (pubkey_buffer == NULL)
    {
        ret = -1;
        printf("pubkey_buffer OPENSSL_malloc failed, return NULL. \n");
        goto finish;
    }
    BIO_read(pri_bio, prikey_buffer, prikey_len);
    BIO_read(pub_bio, pubkey_buffer, pubkey_len);
    prikey_buffer[prikey_len] = '\0';
    pubkey_buffer[pubkey_len] = '\0';
#endif
finish:
    if (ec_key != NULL)
        EC_KEY_free(ec_key);
    if (ec_group != NULL)
        EC_GROUP_free(ec_group);
#ifdef MAKE_KEY_TO_RAM
    if (prikey_buffer != NULL)
        OPENSSL_free(prikey_buffer);
    if (pubkey_buffer != NULL)
        OPENSSL_free(pubkey_buffer);
#endif
    if (pub_bio != NULL)
        BIO_free_all(pub_bio);
    if (pri_bio != NULL)
        BIO_free_all(pri_bio);
    return ec_key;
}

string SM2_SIGN(string data, EVP_PKEY *privkey)
{
    unsigned char *sign = (unsigned char *)malloc(1024 * sizeof(unsigned char));
    unsigned int sign_len;
    // EVP_PKEY *privkey = read_private_key(priv_pem.c_str(), passwd.c_str());
    EC_KEY *priv_eckey = NULL;
    priv_eckey = EVP_PKEY_get1_EC_KEY(privkey);
    SM2_sign(NID_undef, (unsigned char *)data.c_str(), data.size(), sign, &sign_len, priv_eckey);
    // *sign_ret = {sign, sign_len};
    return string((char *)sign, sign_len);
}

bool SM2_VERIFY(string data, string sign, EVP_PKEY *pubkey)
{
    EC_KEY *pub_eckey = NULL;
    pub_eckey = EVP_PKEY_get1_EC_KEY(pubkey);
    return (bool)SM2_verify(NID_undef, (unsigned char *)data.c_str(), data.size(), (unsigned char *)sign.c_str(), sign.size(), pub_eckey);
}

string pkcs7_sign(X509 *x509, EVP_PKEY *privkey, string cert_sf)
{
    // BIO *bp = BIO_new(BIO_s_file());
    // X509 *x509 = NULL;
    // EVP_PKEY *privkey = read_private_key(priv_pem.c_str(), passwd.c_str());
    // EC_KEY *priv_eckey = NULL;
    // priv_eckey = EVP_PKEY_get1_EC_KEY(privkey);
    // /*read public key from pem file.*/
    // BIO_read_filename(bp, x509_pem.c_str());
    // BIO *data = BIO_new(BIO_s_mem());
    // BIO_read_filename(data, cert_sf.c_str());
    // x509 = PEM_read_bio_X509(bp, NULL, NULL, NULL);
    // BIO_write(data, (void *)cert_sf.c_str(), cert_sf.size());
    BIO *data = BIO_new_mem_buf(cert_sf.c_str(), cert_sf.size());
    int flags = 0;
    // flags |= PKCS7_DETACHED;
    // flags |=
    PKCS7 *p7 = PKCS7_sign(x509, privkey, NULL, data, flags);
    // BIO *cert_sm2 = BIO_new_file(cert_sm2_file.c_str(), "wb+");

    unsigned char buffer[4096];
    unsigned char *p = buffer;
    int len = i2d_PKCS7(p7, &p);
    if (len <= 0)
    {
        printf("sign failed\n");
    }
    else
    {
        // printf("Sign ok.\n");
    }
    string p7_out((char *)buffer, len);
    
    // PEM_write_bio_PKCS7(cert_sm2, p7);
    // BIO_free_all(cert_sm2);
    // BIO_free_all(bp);
    // ofstream p("test.pk7");
    // p << p7_out;
    BIO_free_all(data);
    // cout<<p7_out<<endl;
    return p7_out;
}

bool pkcs7_verify(string p7s, string data)
{
    ofstream p("test.pk7");
    p << p7s;
    BIO *p7p = BIO_new_mem_buf(p7s.c_str(), p7s.size());
    // BIO *p7p = BIO_new(BIO_s_mem());
    // BIO_write(p7p, (void *)p7s.c_str(), p7s.size());
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
    BIO *dp = BIO_new_mem_buf(data.c_str(), data.size());
    // const unsigned char *ps = (const unsigned char *)&p7s[0];
    p7 = d2i_PKCS7_bio(p7p, &p7);
    if (p7 == NULL)
    {
        printf("PKCS7 Wrong\n");
        return false;
    } else {
        // printf("PKCS7 OK\n");
    }
    BIO *bdata = BIO_new(BIO_s_mem());
    BIO *out = BIO_new(BIO_s_mem());
    //
    BIO_write(bdata, (void *)&data[0], data.size());
    // printf("%s", out);
    // BIO_printf(bdata, )
    int flags = PKCS7_NOVERIFY | PKCS7_NOCHAIN;
    // bool ret = PKCS7_verify(p7, NULL, NULL, bdata, out, flags);
    bool ret = PKCS7_verify(p7, NULL, NULL, bdata, out, flags);
    // bool ret = true;
    // cout <<endl;
    BIO_free_all(bdata);
    BIO_free_all(out);
    BIO_free_all(p7p);
    BIO_free_all(dp);
    return ret;
}

void init()
{
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_digests();
}