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