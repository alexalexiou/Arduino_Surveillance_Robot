package com.example.arduino2;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.View;
import android.view.View.OnKeyListener;
import android.widget.EditText;

/**
 * The MainActivity class is responsible for user inputof data . 
 * It's the class where user's input have to be made and passing them to Activity2 class
 * @author  Alexis Alexiou
 * @version 2.0, March 2014
 * 
 */

public class MainActivity extends Activity {

	private EditText et1;
	private EditText et2;

	// public final static String IP = "com.example.arduino2_IP";
	// public final static String PORT = "com.example.arduino2_PORT";

	
	/**
	 * in this method the two textviews from layout resource are beeing connected,
	 * with the java class. The user have to give two values as input, the ip address of the
     *wifi shield and the server's port.
	 * 
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		// bt1 =(Button)findViewById(R.id.button1);
		et1 = (EditText) findViewById(R.id.editText1);
		et2 = (EditText) findViewById(R.id.editText2);

		et2.setOnKeyListener(new OnKeyListener() {
			@Override
			public boolean onKey(View v, int keyCode, KeyEvent event) {
				{

					if (keyCode == KeyEvent.KEYCODE_ENTER
							/*
					 * without .ACTION_UP or .ACTION_DOWN it types two times
					 */
							&& event.getAction() == KeyEvent.ACTION_UP) { 
						clickToConnect(v);

						return true;
					}
				}
				return false;
			}
		});

	}
	
	/**
	 * this method is responsible to send data to Activity2 and show to
	 *  the user, the UI of activity_main layout
	 * @param v from View class, every component in the layout file has a view instant
	 */

	public void clickToConnect(View v) {
		String ipValue = et1.getText().toString();   // takes the value from the IP textfield and convert it to a string
		String port = et2.getText().toString();      // takes the value from the port textfield and convert it to a string

		// Log.v("IP", ipValue);
		// Log.v("Port", port);
		Intent i = new Intent(this, Activity2.class);  //intent object is created in order to start a new Activity and pass data to it
		i.putExtra("IP", ipValue);                     // putExtra method keeps the data that we want to pass them to next activity
		i.putExtra("PORT", port);
		startActivity(i);                             // starts the activity Activity2
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
