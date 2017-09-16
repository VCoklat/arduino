package com.example.handy.led;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import static com.example.handy.led.DeviceList.EXTRA_ADDRESS;


public class MainActivity extends AppCompatActivity {

    ImageView kamar2;
    ImageView kamar1,dapur,kamar_mandi,ruang_tamu,help;
    String address = null;
    public static String EXTRA_ADDRESS = "device_address";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent newint = getIntent();
        address = newint.getStringExtra(EXTRA_ADDRESS); //receive the address of the bluetooth device

        setContentView(R.layout.activity_main);

        kamar2 = (ImageView) findViewById(R.id.imageView14);
        kamar2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
             /*   String info = ((TextView) v).getText().toString();
                String address = info.substring(info.length() - 17);
*/
                Intent intentkamar2 = new Intent(MainActivity.this,Kamar2.class);
               // intentkamar2.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity
                startActivity(intentkamar2);
            }
        });

        kamar1=(ImageView)findViewById(R.id.imageView17);
        kamar1.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                /*String info = ((TextView) v).getText().toString();
                String address = info.substring(info.length() - 17);
*/
                Intent intentkamar1 = new Intent(MainActivity.this,Kamar1.class);

                startActivity(intentkamar1);
            }
        });

        dapur = (ImageView) findViewById(R.id.imageView15);
        dapur.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
              /*  String info = ((TextView) v).getText().toString();
                String address = info.substring(info.length() - 17);

                Intent intentdapur = new Intent(MainActivity.this,Dapur.class);
                intentdapur.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity*/
                Intent intentdapur = new Intent(MainActivity.this,Dapur.class);
                startActivity(intentdapur);
            }
        });

        kamar_mandi = (ImageView) findViewById(R.id.imageView19);
        kamar_mandi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
  /*              String info = ((TextView) v).getText().toString();
                String address = info.substring(info.length() - 17);
*/
                Intent intentmandi = new Intent(MainActivity.this,Kamarmandi.class);
  //              intentmandi.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity
                startActivity(intentmandi);
            }
        });

        ruang_tamu = (ImageView) findViewById(R.id.imageView2);
        ruang_tamu.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
    /*            String info = ((TextView) v).getText().toString();
                String address = info.substring(info.length() - 17);
*/
                Intent intentruangtamu = new Intent(MainActivity.this,Ruangtamu.class);
  //              intentruangtamu.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity
                startActivity(intentruangtamu);
            }
        });

        help = (ImageView) findViewById(R.id.imageView3);
        help.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intenthelp = new Intent(MainActivity.this,Help.class);
                startActivity(intenthelp);
            }
        });
    }
}
