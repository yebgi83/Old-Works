package com.yebgi.calender;

import android.app.Activity;
import android.os.Bundle;
import android.graphics.*;

public class androidCalenderActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // setContentView(R.layout.main);
        setContentView(new androidCalenderView(this));
    }
}
