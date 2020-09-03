package com.example.ballbouncermobilapp;

import android.os.AsyncTask;
import android.os.Build;

import androidx.annotation.RequiresApi;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.util.Enumeration;
import java.util.Map;


public class UdpUnicastClient {

    public UdpUnicastClient() {
        new myTaskMal().execute(5555);
    }

    private class myTaskMal extends AsyncTask<Integer, Integer , Boolean> {

        @Override
        protected void onPreExecute() {
            super.onPreExecute();

        }

        @Override
        protected Boolean doInBackground(Integer... integers) {

            int port = integers[0];

            // Find the server using UDP broadcast
            try {
                //Open a random port to send the package
                MainActivity.c = new DatagramSocket();
                MainActivity.c.setBroadcast(true);

                byte[] sendData = "6Unz2hcxQVTs2dq".getBytes();

                //Try the 255.255.255.255 first
                try {
                    DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("255.255.255.255"), port);
                    MainActivity.c.send(sendPacket);
                    System.out.println(getClass().getName() + ">>> Request packet sent to: 255.255.255.255 (DEFAULT)");
                } catch (Exception e) {
                }

                // Broadcast the message over all the network interfaces
                Enumeration interfaces = NetworkInterface.getNetworkInterfaces();
                while (interfaces.hasMoreElements()) {
                    NetworkInterface networkInterface = (NetworkInterface) interfaces.nextElement();

                    if (networkInterface.isLoopback() || !networkInterface.isUp()) {
                        continue; // Don't want to broadcast to the loopback interface
                    }

                    for (InterfaceAddress interfaceAddress : networkInterface.getInterfaceAddresses()) {
                        InetAddress broadcast = interfaceAddress.getBroadcast();
                        if (broadcast == null) {
                            continue;
                        }

                        // Send the broadcast package!
                        try {
                            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, broadcast, port);
                            MainActivity.c.send(sendPacket);
                        } catch (Exception e) {
                        }
                        System.out.println(getClass().getName() + ">>> Request packet sent to: " + broadcast.getHostAddress() + "; Interface: " + networkInterface.getDisplayName());
                    }
                }

                System.out.println(getClass().getName() + ">>> Done looping over all network interfaces. Now waiting for a reply!");

                //Wait for a response
                byte[] recvBuf = new byte[15000];
                final DatagramPacket receivePacket = new DatagramPacket(recvBuf, recvBuf.length);
                MainActivity.c.receive(receivePacket);
                //We have a response
                System.out.println(getClass().getName() + ">>> Broadcast response from server: " + receivePacket.getAddress().getHostAddress());

                //Check if the message is correct
                String message = new String(receivePacket.getData()).trim();
              /*  if (message.equals("R8Jb2f55EZDAmJ7")) {
                    MainActivity.serverIp = receivePacket.getAddress().getHostAddress();
                    //System.out.println("EŞLEŞTİ >>>>");

                    return true;
                } */

                //Close the port!
            } catch (IOException  ex) {
                System.out.println("\"HATA\" = " + ex.getMessage());
            }

            return true;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            super.onProgressUpdate(values);
        }

    }


}
