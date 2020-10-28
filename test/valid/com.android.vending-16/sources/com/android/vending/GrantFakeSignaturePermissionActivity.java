package com.android.vending;

import android.annotation.TargetApi;
import android.app.Activity;
import android.os.Bundle;

@TargetApi(23)
public class GrantFakeSignaturePermissionActivity extends Activity {
    /* access modifiers changed from: protected */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (checkSelfPermission("android.permission.FAKE_PACKAGE_SIGNATURE") != 0) {
            requestPermissions(new String[]{"android.permission.FAKE_PACKAGE_SIGNATURE"}, 1);
            return;
        }
        setResult(-1);
        finish();
    }

    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        int i = 0;
        if (requestCode == 1 && grantResults.length == 1) {
            if (grantResults[0] == 0) {
                i = -1;
            }
            setResult(i);
            finish();
        }
    }
}
