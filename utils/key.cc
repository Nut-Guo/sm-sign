#include "key.h"


EVP_PKEY *read_public_key(const char *file_name)
{
    BIO *bp = NULL;
    EC_KEY *ec_key = NULL;
    EVP_PKEY *public_evp_key = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    //OpenSSL_add_all_algorithms();
    bp = BIO_new( BIO_s_file() );
    /*read public key from pem file.*/
    BIO_read_filename( bp, file_name );
    ec_key = PEM_read_bio_EC_PUBKEY(bp, NULL, NULL, NULL);
    public_evp_key = EVP_PKEY_new();
    EVP_PKEY_set1_EC_KEY(public_evp_key, ec_key);
    ctx = EVP_PKEY_CTX_new(public_evp_key, NULL);
    EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_sm2p256v1);
    // EVP_PKEY_encrypt_init(ctx);
    return public_evp_key;
}

EVP_PKEY *read_private_key(const char *file_name, const char *passwd)
{
    BIO *bp = NULL;
    EC_KEY *ec_key = NULL;
    EVP_PKEY *private_evp_key = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    //OpenSSL_add_all_algorithms();
    bp = BIO_new(BIO_s_file());
    /*read public key from pem file.*/
    BIO_read_filename(bp, file_name);
    if (bp == NULL)
    {
        printf("Error open file\n");
    }
    ec_key = PEM_read_bio_ECPrivateKey(bp, &ec_key, NULL, (void *)passwd);
    if (ec_key == NULL)
    {
        printf("Error reading private key from file\n");
    }
    private_evp_key = EVP_PKEY_new();
    EVP_PKEY_set1_EC_KEY(private_evp_key, ec_key);
    ctx = EVP_PKEY_CTX_new(private_evp_key, NULL);
    EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_sm2p256v1);
    // EVP_PKEY_decrypt_init(ctx);
    return private_evp_key;
}

X509 *generate_x509(EVP_PKEY *pkey, EVP_PKEY *request, string x509_file)
{
    /* Allocate memory for the X509 structure. */
    X509 *x509 = X509_new();
    if (!x509)
    {
        std::cerr << "Unable to create X509 structure." << std::endl;
        return NULL;
    }

    /* Set the serial number. */
    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    /* This certificate is valid from now until exactly one year from now. */
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);

    /* Set the public key for our certificate. */
    X509_set_pubkey(x509, request);

    /* We want to copy the subject name to the issuer name. */
    X509_NAME *name = X509_get_subject_name(x509);

    /* Set the country code and common name. */
    X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC, (unsigned char *)"CN", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (unsigned char *)"UCAS", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)"localhost", -1, -1, 0);

    /* Now set the issuer name. */
    X509_set_issuer_name(x509, name);

    /* Actually sign the certificate with our key. */
    if (!X509_sign(x509, pkey, EVP_sm3()))
    {
        std::cerr << "Error signing certificate." << std::endl;
        X509_free(x509);
        return NULL;
    }
    FILE *x509_fp = fopen(x509_file.c_str(), "wb");
    if (!x509_fp)
    {
        std::cerr << "Unable to open x509 for writing." << std::endl;
        return NULL;
    }

    /* Write the certificate to disk. */
    bool ret = PEM_write_X509(x509_fp, x509);
    fclose(x509_fp);

    if (!ret)
    {
        std::cerr << "Unable to write certificate to disk." << std::endl;
        return NULL;
    }

    return x509;
}

// bool write_to_disk(X509 *x509, string x509_file)
// {
//     /* Open the PEM file for writing the key to disk. */
//     // FILE *pkey_file = fopen(key_file, "wb");
//     // if (!pkey_file)
//     // {
//     //     std::cerr << "Unable to open \"key.pem\" for writing." << std::endl;
//     //     return false;
//     // }

//     // /* Write the key to disk. */
//     // bool ret = PEM_write_PrivateKey(pkey_file, pkey, EVP_sm4_cbc(), (unsigned char *)passwd, strlen(passwd), NULL, NULL);
//     // fclose(pkey_file);

//     // if (!ret)
//     // {
//     //     std::cerr << "Unable to write private key to disk." << std::endl;
//     //     return false;
//     // }

//     /* Open the PEM file for writing the certificate to disk. */
//     FILE *x509_fp = fopen(x509_file.c_str(), "wb");
//     if (!x509_fp)
//     {
//         std::cerr << "Unable to open x509 for writing." << std::endl;
//         return false;
//     }

//     /* Write the certificate to disk. */
//     bool ret = PEM_write_X509(x509_fp, x509);
//     fclose(x509_fp);

//     if (!ret)
//     {
//         std::cerr << "Unable to write certificate to disk." << std::endl;
//         return false;
//     }

//     return true;
// }

void write_pkcs8(const char *filename, EVP_PKEY *pkey, string passwd)
{
    PKCS8_PRIV_KEY_INFO *p8 = EVP_PKEY2PKCS8(pkey);
    // BIO *bp = BIO_new_file(filename, "wb+");
    FILE *fp = fopen(filename, "wb+");
    i2d_PKCS8PrivateKey_fp(fp, pkey, EVP_sm4_cbc(), (char *)passwd.c_str(), passwd.size(), NULL, NULL);
    // BIO_free_all(bp);
    fclose(fp);
}

EVP_PKEY *read_pkcs8(const char *file_name)
{
    // BIO *bp = NULL;
    EVP_PKEY *private_evp_key = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    //OpenSSL_add_all_algorithms();
    FILE *fp = fopen(file_name, "rb");
    /*read public key from pem file.*/
    // BIO_read_filename(bp, file_name);
    // if (bp == NULL)
    // {
    //     printf("Error open file\n");
    // }
    private_evp_key = d2i_PKCS8PrivateKey_fp(fp, &private_evp_key, NULL, NULL);
    // PKCS8_PRIV_KEY_INFO *p8;
    // p8 = d2i_PKCS8_PRIV_KEY_INFO_bio(bp, &p8);
    // private_evp_key = PKCS8_pkey_get0()
    // EVP_PKEY_set1_EC_KEY(private_evp_key, ec_key);
    ctx = EVP_PKEY_CTX_new(private_evp_key, NULL);
    EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_sm2p256v1);
    return private_evp_key;
}