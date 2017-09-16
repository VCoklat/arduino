package com.example.handy.led;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

public class Dapur extends AppCompatActivity {
    Switch switchButton1,switchButton2;
    ImageView off1,off2;
	String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    //SPP UUID. Look for it
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

  		//Intent newint = getIntent();
        address = "20:16:03:08:13:39"; //newint.getStringExtra(MainActivity.EXTRA_ADDRESS); //receive the address of the bluetooth device

        setContentView(R.layout.dapur);
		new ConnectBT().execute(); //Call the class to connect

        switchButton1 = (Switch)findViewById(R.id.switchButton1);
        switchButton1.setChecked(false);
        off1=(ImageView)findViewById(R.id.imageView10);

        switchButton1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener(){
            @Override

            public void onCheckedChanged(CompoundButton compoundButton,boolean bChecked){
                if(bChecked){
                    off1.setImageResource(R.drawable.on);
                    if (btSocket!=null)
                    {
                        try
                        {
                            btSocket.getOutputStream().write("LN".toString().getBytes());
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }else{
                    off1.setImageResource(R.drawable.off);
                    if (btSocket!=null)
                    {
                        try
                        {
                            btSocket.getOutputStream().write("LM".toString().getBytes());
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        switchButton2 = (Switch)findViewById(R.id.switchButton2);
        switchButton2.setChecked(false);
        off2=(ImageView)findViewById(R.id.imageView11);

        switchButton2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener(){
            @Override

            public void onCheckedChanged(CompoundButton compoundButton,boolean bChecked){
                if(bChecked){
                    off2.setImageResource(R.drawable.on);
                    if (btSocket!=null) {
                        try {
                            btSocket.getOutputStream().write("AN".toString().getBytes());
                        } catch (IOException e) {
                            msg("Error");
                        }
                    }
                }else{
                    off2.setImageResource(R.drawable.off);
                    if (btSocket!=null) {
                        try {
                            btSocket.getOutputStream().write("AM".toString().getBytes());
                        } catch (IOException e) {
                            msg("Error");
                        }
                    }
                }
            }
        });
    }
    @Override
    public void onBackPressed() {
        if (btSocket!=null) //If the btSocket is busy
        {
            try
            {
                btSocket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        Intent intentkamar2 = new Intent(Dapur.this,MainActivity.class);
        // intentkamar2.putExtra(EXTRA_ADDRESS, address); //this will be received at ledControl (class) Activity
        startActivity(intentkamar2);
    }

    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s, Toast.LENGTH_LONG).show();
    }

	private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(Dapur.this, "Connecting...", "Please wait");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                 btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                 BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                 btSocket.connect();//start connection
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("There are a error in bluettooth connection. Please Restart Your Application.");
                finish();
            }
            else
            {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}
