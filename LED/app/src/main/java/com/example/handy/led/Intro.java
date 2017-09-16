package com.example.handy.led;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import java.util.Timer;
import java.util.TimerTask;

public class Intro extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.intro);

        TimerTask task =new TimerTask() {
            @Override
            public void run() {
                Intent intenthalaman = new Intent(Intro.this,HalamanMasuk.class);
                startActivity(intenthalaman);
                finishscreen();
            }
        };
        Timer t = new Timer();
        t.schedule(task,3000);
    }

    private void finishscreen(){
        this.finish();
    }
}
