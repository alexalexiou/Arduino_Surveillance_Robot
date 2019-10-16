package com.example.arduino2;

import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.TextView;


/**
 * The Activity2 class is responsible for controlling the robot  . 
 * @author  Alexis Alexiou
 * @version 2.0, March 2014
 */
public class Activity2 extends Activity {

	private Socket s;
	private OutputStream out = null;
	private PrintWriter w = null;
	private Handler handler;
	private TextView textView1;
	private String tag = "DEBUGGING";
	private static String IP;
	private static int port;

	
	
	/**
	 *This method is responsible for receiving the two Extra parameters 
	 *from MAinActivity and open a socket connection. In order to succeed this,
	 * it make use of thread implementation.  
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity2);
		handler = new Handler();
		setContentView(R.layout.activity2);
		textView1 = (TextView) findViewById(R.id.textView1);
		Bundle extras = getIntent().getExtras(); 
		if (extras != null) {
			IP = extras.getString("IP");
			String port2 = extras.getString("PORT");
			port = Integer.parseInt(port2);
			// Log.v("ip",ip);
			// Log.v("port",port);
		}

		Runnable runnable = new Runnable() {        
			public void run() {              // this runnable object is where the connection takes place

				synchronized (this) {
					try {
						s = new Socket(IP, port);
						out = s.getOutputStream();
						w = new PrintWriter(out);
					} catch (Exception e) {
						Log.v("error socket", "Alex soc");
						e.printStackTrace();
					}
				}

				handler.post(new Runnable() {   // with handler post we manage to saw into the 
					@Override                   // main thread UI, a success message if the connection 
					public void run() {         // have been established or not.
						synchronized (this) {
							try {
								Thread.sleep(1000);
								if (s != null)
									textView1.setText("connected...");

							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								Log.v("error handler", "handler Alex");
								e.printStackTrace();
							}

						}
					}
				});

			}
		};
		Thread mythread = new Thread(runnable);  
		mythread.start();
		/*
		 *  if (s.isConnected()) {  Toast.makeText(this, "connected..",
		 * Toast.LENGTH_LONG).show();
		 * 
		 *  } else { // Toast.makeText(this, "disconnected",
		 * Toast.LENGTH_LONG).show(); // }
		 */
		hornButton();

	}
	
	

	public void moveLeft(View v) {

		Runnable runnable = new Runnable() {
			public void run() {

				synchronized (this) {
					try {
						w.print("left");
						w.print('\n');
						w.flush();

					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		};
		Thread mythread = new Thread(runnable);
		mythread.start();
	}

	/**
	 * motion routine method for turning right
	 * Sends a string message through the socket 
	 * All the operation, in order to more than one buttons
	 *  may be pressed at the same moment
	 * @param v
	 */
	public void moveRight(View v) {

		Runnable runnable = new Runnable() {
			public void run() {

				synchronized (this) {
					try {
						w.print("right");
						w.print('\n');
						w.flush();

					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		};
		Thread mythread = new Thread(runnable);
		mythread.start();
		// Toast.makeText(getApplicationContext(),"toast",
		// Toast.LENGTH_SHORT).show();
	}
	
	
	/**
	 * motion routine method for moving forward
	 * Sends a string message through the socket 
	 * All the operation, in order to more than one buttons
	 *  may be pressed at the same moment
	 * @param v
	 */
	public void moveForward(View v) {

		Runnable runnable = new Runnable() {
			public void run() {

				synchronized (this) {
					try {
						w.print("forw");
						w.print('\n');
						w.flush();

					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		};
		Thread mythread = new Thread(runnable);
		mythread.start();
	}
	
	
	/**
	 * motion routine method for reverse moving
	 * Sends a string message through the socket 
	 * All the operation, in order to more than one buttons
	 *  may be pressed at the same moment
	 * @param v
	 */
	public void moveBack(View v) {

		Runnable runnable = new Runnable() {
			public void run() {

				synchronized (this) {
					try {
						w.print("back");
						w.print('\n');
						w.flush();

					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		};
		Thread mythread = new Thread(runnable);
		mythread.start();
	}

	
	/**
	 * motion routine method for stopping
	 * Sends a string message through the socket 
	 * All the operation, in order to more than one buttons
	 *  may be pressed at the same moment
	 * @param v
	 */
	public void stop(View v) {

		Runnable runnable = new Runnable() {
			public void run() {

				synchronized (this) {
					try {
						w.print("stop");
						w.print('\n');
						w.flush();

					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		};
		Thread mythread = new Thread(runnable);
		mythread.start();

	}

	
	/**
	 * motion routine method for turning the buzzer of the robot on
	 * Sends a string message through the socket 	
	 * buttons send message while is pressed
	 * when it's not it doesn't send anything	 
	 */
	public void hornButton() {

		Button b = (Button) findViewById(R.id.button1);

		b.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN:
					// Do something
					w.println("horn");
					w.println('\n');
					w.flush();

					return true;
				case MotionEvent.ACTION_UP:
					// No longer down
					w.println("nohorn");
					w.println('\n');
					w.flush();

					return true;
				}

				return false;
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity2, menu);
		return true;
	}

}
