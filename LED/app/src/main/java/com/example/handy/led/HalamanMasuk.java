package com.example.handy.led;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import static com.example.handy.led.DeviceList.EXTRA_ADDRESS;

public class HalamanMasuk extends AppCompatActivity {

    EditText textUsername,password;
    Button login;
    ImageView help;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.halaman_masuk);

        textUsername=(EditText) findViewById(R.id.editText);
        password=(EditText)findViewById(R.id.editText2);
        login = (Button)findViewById(R.id.button);

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(textUsername.getText().toString().equals("HCI2014")&&password.getText().toString().equals("kelompok4")){
                    Intent intentmain = new Intent(HalamanMasuk.this,MainActivity.class);
                    startActivity(intentmain);
                }else{
                    Toast.makeText(HalamanMasuk.this,"Wrong Username/Pass!",Toast.LENGTH_LONG).show();
                }
            }
        });

        help = (ImageView) findViewById(R.id.imageView3);
        help.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intenthelp = new Intent(HalamanMasuk.this,Help.class);
                startActivity(intenthelp);
            }
        });

    }
}
