#include <cstdio>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/sm3.h>
int main(int argc, char *argv[])
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char mess2[] = "Hello World\n";
    //  unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned char *md_value = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sm3()));
    unsigned int md_len, i;

    if (argv[1] == NULL)
    {
        printf("Usage: mdtest digestname\n");
        exit(1);
    }

    //  md = EVP_get_digestbyname(argv[1]);
    md = EVP_sm3();
    if (md == NULL)
    {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    //  EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
    EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    printf("Digest is: ");
    for (i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");
    sm3((unsigned char *)mess2, strlen(mess2), md_value);
    for (i = 0; i < 32; i++)
        printf("%02x", md_value[i]);
    printf("\n");
    // printf("%d", strlen(mess2));
    exit(0);
}