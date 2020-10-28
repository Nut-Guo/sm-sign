from zipfile import ZipFile
import io
# dir = "/mnt/d/Documents/Chores/homework/NSS/main/lab/sslc/test/valid/"
# file_name = "com.android.vending-16.apk"
import sm
import os.path
import base64
def sign(file_name, key):
    sign_apk = ZipFile(os.path.join(dir, file_name) + ".signed", mode='w')
    with ZipFile(file_name, 'r') as zfile:
        mf = b'Manifest-Version: 1.0\nBuilt-By: Sign tool\nCreated-By: Siliang Qin\n'
        dgst = b''
        for finfo in zfile.infolist():
            if('META-INF' in finfo.filename):
                continue
            content = zfile.read(finfo.filename)
            sign_apk.writestr(finfo.filename, content)
            s = sm.SM3(content)
            dgst += b'\nNAME: %s\nSM3-Digest: %s\n' % (
                finfo.filename.encode('utf-8'), base64.b64encode(s))
        mf += dgst
        sign_apk.writestr('META-INF/MANIFEST.MF', mf)
        sf = b"Signature-Version: 1.0\nX-Android-APK-Signed: 2\n"
        sf += b"SM3-Digest-Manifest: "
        sf += base64.b64encode(sm.SM3(mf))
        sf += b'\nCreated-By: 1.0 (Android)\n'
        sf += dgst
        sign_apk.writestr('META-INF/CERT.SF', sf)
        key = sm.read_private_key(b'pri_key.ec', b'12345678')
        # sign = sm.SM2_SIGN(sf, key)
        x509 = sm.generate_x509(key, key, b'cert.x509')
        p7 = sm.pkcs7_sign(x509, key, sf)
        print(p7)
        sign_apk.writestr('META-INF/CERT.SM2', p7)
        # print(sign)
    sign_apk.close()
