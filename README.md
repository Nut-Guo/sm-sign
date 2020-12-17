# sm-sign

## Usage

```bash
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=<Install path> -DCMAKE_FIND_LIBRARY_SUFFIXES=.a ..
make install
```
Then go to install path
```bash
python setup.py install <--user>
```
Use the sm_sign command:
```
usage: sm_sign [-h] {genkey,sign,verify} ...

positional arguments:
  {genkey,sign,verify}  commands
    genkey              Generate Key Pair
    sign                Sign APK file
    verify              Verify APK

optional arguments:
  -h, --help            show this help message and exit
```

## Example
```bash
/mnt/.../lab/sslc >>> sm_sign genkey -k key.pk8 -p 12345678 --privkey priv.pem --pubkey pub.pem                ±[●●][main]
Create sm2 private key ok!
Create sm2 public key ok!
/mnt/.../lab/sslc >>> sm_sign sign -i test/valid/k-aapt-release.apk -o k-aapt-sm2.apk -k key.pk8 --pubkey pub.pem 
Enter PEM pass phrase:
/mnt/.../lab/sslc >>> sm_sign verify -i k-aapt-sm2.apk                                                         ±[●●][main]
AndroidManifest.xml:
CERT.SF  : b'uncuCow4mczAfY4QyrbA8++vP0FvKKjWocq1ZNq+RkU='
File hash: b'uncuCow4mczAfY4QyrbA8++vP0FvKKjWocq1ZNq+RkU='

classes.dex:
CERT.SF  : b'pV5Dww+OrfAX1r8BIdvLN+3GBTBfcZYhsg/keCDGcdQ='
File hash: b'pV5Dww+OrfAX1r8BIdvLN+3GBTBfcZYhsg/keCDGcdQ='

META-INF/MANIFEST.MF:
CERT.SF  : b'5a7zH22BUz29GW0oQBXHupggSTw7zF1kwU0G92M/+Bc='
File hash: b'5a7zH22BUz29GW0oQBXHupggSTw7zF1kwU0G92M/+Bc='

Verifying Signature...
Success
```