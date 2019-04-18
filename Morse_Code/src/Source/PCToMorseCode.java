package assignment5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

import jssc.SerialPortException;

public class PCToMorseCode {
	public static void main(String[] args) throws SerialPortException, IOException {		
		// TODO:  Fix this: 
		//           a) Uncomment to create a SerialComm object
		//           b) Update the "the port" to refer to the serial port you're using
		//              (The port listed in the Arduino IDE Tools>Port menu.		
		//           c) Deal with the unresolved issue
		SerialComm port = new SerialComm("COM3");
		
		
		while(true) {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			String asd = in.readLine();
			for(int i = 0; i < asd.length(); i++) {
				port.writeByte((byte)(asd.charAt(i)));
			}
		}
		
			
			
			/*
			 * 
			 * It will read an entire line at a time.
			 * It will send send each character to serial port.
			 * The debug in SerialComm should be set to true 
			 * so that you can see the bytes as they go into 
			 * and out of the Java program (to/from the Arduino).
			 * 
			 */

		
		// TODO: Complete section 6 of the Studio (gather sanitized user input
		//       and send it to the Arduino)
	}

}
