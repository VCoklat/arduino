package com.example.handy.led;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;


public class Help extends AppCompatActivity {
    TextView question;
    TextView help_menu;
    Intent intent = null;
    Intent chooser = null;
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_help);

            question = (TextView)findViewById(R.id.textQuestion);
            question.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    intent = new Intent(Intent.ACTION_SEND);
                    intent.setData(Uri.parse("mailto:"));
                    String[] to ={"handytantyo@gmail.com","dvanhauten@gmail.com","dikadhaneswara@gmail.com"};
                    intent.putExtra(Intent.EXTRA_EMAIL,to);
                    intent.setType("message/rfc822");
                    chooser = Intent.createChooser(intent,"Send Email");
                    startActivity(chooser);
                }
            });

            help_menu=(TextView) findViewById(R.id.textView7);
            help_menu.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View v){
                    Intent intentkamar1 = new Intent(Help.this,HelpMenu.class);
                    startActivity(intentkamar1);
                }
            });

        }
    }


