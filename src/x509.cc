#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/x509.h>

X509* get_x509_from_file(const char* filename, X509 **x509) {
    FILE *fp = fopen(filename, "r");
    PEM_read_X509(fp, x509, NULL, NULL);
    return *x509;
}