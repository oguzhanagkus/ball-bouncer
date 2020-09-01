package com.example.ballbouncermobilapp;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.TextView;

import com.google.gson.Gson;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.PointsGraphSeries;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {


    public static DatagramSocket c;
    public static String serverIp;
    DataFromServer dfs;
    //public static CustomDialog customDialog;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
       /* customDialog = new CustomDialog();
        customDialog.show(getSupportFragmentManager(),"connection custom"); */

    //    new UdpUnicastClient();

        new myTask().execute(5555);
    }

    private class myTask extends AsyncTask<Integer, DataFromServer, Boolean> {


        //add point graph series of datapoint type
        PointsGraphSeries<DataPoint> xyCurrentSeries;
        PointsGraphSeries<DataPoint> xyPreviousSeries;
        PointsGraphSeries<DataPoint> xhCurrentSeries;


        TextView positionText;
        TextView heightText;
        GraphView xyPlotView;
        GraphView xhPlotView;
        ///////////////////////////////////////////7777

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            try {
                c= new DatagramSocket(5555);
            } catch (SocketException e) {
                e.printStackTrace();
            }
            try {
                c.setBroadcast(true);
            } catch (SocketException e) {
                e.printStackTrace();
            }

            dfs = new DataFromServer();
            positionText= findViewById(R.id.positionText);
            heightText = findViewById(R.id.heightText);


            xyCurrentSeries = new PointsGraphSeries<>();
            xyPreviousSeries = new PointsGraphSeries<>();
            xhCurrentSeries = new PointsGraphSeries<>();

            xyPlotView = (GraphView) findViewById(R.id.xyPlot);
            xhPlotView = (GraphView) findViewById(R.id.xhPlot);

            setXYProperties();
            setXHProperties();
        }

        @Override
        protected Boolean doInBackground(Integer... integers) {
           //data oku....
            while (true) {
                System.out.println("Starting T2");

                try {
                    byte[] recvBufx = new byte[15000];
                    DatagramPacket receivePacketx = new DatagramPacket(recvBufx, recvBufx.length);
                    c.receive(receivePacketx);

                    String x = new String(receivePacketx.getData());
                    System.out.println("x = " + x);
                    String position[] = x.split("-");
                    if(position.length < 4 )
                        continue;

                    dfs.generalSetter(Double.parseDouble(position[0]), Double.parseDouble(position[1]), Double.parseDouble(position[2]));
                    System.out.println("dfs = " + dfs.getX());

                    publishProgress(dfs);
                    Thread.sleep(100);
                } catch (IOException | InterruptedException e) {
                    System.out.println("e.getMessage() = " + e.getMessage());
                }
                xyPlotView.removeAllSeries();
                xyPlotView.refreshDrawableState();

                xhPlotView.removeAllSeries();
                xhPlotView.refreshDrawableState();
            }

        }

        @Override
        protected void onProgressUpdate(final DataFromServer... values) {
            super.onProgressUpdate(values);


            xyCurrentSeries = new PointsGraphSeries<>();
            xyPreviousSeries = new PointsGraphSeries<>();
            xhCurrentSeries = new PointsGraphSeries<>();

            System.out.println("v0 "+values[0]);
            setXYProperties();
            setXHProperties();

            String x = String.valueOf( (int)values[0].getX() );
            String y = String.valueOf( (int)values[0].getY() );
            String h = String.valueOf( (int)values[0].getZ() );

            heightText.setText("Height: " + h);
            positionText.setText("Coordinates: (" + x + ", " + y + " )");

            System.out.println("---------------");
            xyPreviousSeries.appendData(new DataPoint(values[0].get_x(),values[0].get_y()),true,1000);

            xyCurrentSeries.appendData(new DataPoint(values[0].getX(),values[0].getY()),true,1000);

            xhCurrentSeries.appendData(new DataPoint(values[0].getX(),values[0].getZ()),true,1000);


            xyPlotView.addSeries(xyCurrentSeries);
            xyPlotView.addSeries(xyPreviousSeries);
            xhPlotView.addSeries(xhCurrentSeries);

        }

        @Override
        protected void onPostExecute(Boolean aBoolean) {
            super.onPostExecute(aBoolean);
            c.close();
        }

        ////////////////////+ //////////////////////////////////
        public void setXHProperties() {

            GraphView xhPlotView = (GraphView) findViewById(R.id.xhPlot);
            xhPlotView.setTitle("X-Z Coordinates");
            xhPlotView.setTitleColor(Color.WHITE);
            //set color
            xhPlotView.getGridLabelRenderer().setGridColor(Color.WHITE);
            xhPlotView.getGridLabelRenderer().setHorizontalLabelsColor(Color.WHITE);
            xhPlotView.getGridLabelRenderer().setVerticalLabelsColor(Color.WHITE);

            //set current  properties
            xhCurrentSeries.setShape(PointsGraphSeries.Shape.POINT);
            xhCurrentSeries.setColor(Color.GREEN);
            xhCurrentSeries.setSize(15f);

            //set Scrollable and Scalable
            xhPlotView.getViewport().setScalable(true);
            xhPlotView.getViewport().setScalableY(true);
            xhPlotView.getViewport().setScrollable(true);
            xhPlotView.getViewport().setScrollableY(true);

            //set manuel x bounds
            xhPlotView.getViewport().setXAxisBoundsManual(true);
            xhPlotView.getViewport().setMaxX(500);
            xhPlotView.getViewport().setMinX(0);

            //set manuel y bounds
            xhPlotView.getViewport().setYAxisBoundsManual(true);
            xhPlotView.getViewport().setMaxY(100);
            xhPlotView.getViewport().setMinY(0);
        }

        public void setXYProperties() {

            xyPlotView.setTitle("X-Y Coordinates");
            xyPlotView.setTitleColor(Color.WHITE);
            GraphView xyPlotView = (GraphView) findViewById(R.id.xyPlot) ;
            //set color
            xyPlotView.getGridLabelRenderer().setGridColor(Color.WHITE);
            xyPlotView.getGridLabelRenderer().setHorizontalLabelsColor(Color.WHITE);
            xyPlotView.getGridLabelRenderer().setVerticalLabelsColor(Color.WHITE);

            //set current  properties
            xyCurrentSeries.setShape(PointsGraphSeries.Shape.POINT);
            xyCurrentSeries.setColor(Color.GREEN);
            xyCurrentSeries.setSize(15f);

            //set previous properties
            xyPreviousSeries.setShape(PointsGraphSeries.Shape.POINT);
            xyPreviousSeries.setColor(Color.YELLOW);
            xyPreviousSeries.setSize(15f);

            //set Scrollable and Scalable
            xyPlotView.getViewport().setScalable(true);
            xyPlotView.getViewport().setScalableY(true);
            xyPlotView.getViewport().setScrollable(true);
            xyPlotView.getViewport().setScrollableY(true);

            //set manuel x bounds
            xyPlotView.getViewport().setXAxisBoundsManual(true);
            xyPlotView.getViewport().setMaxX(500);
            xyPlotView.getViewport().setMinX(0);

            //set manuel y bounds
            xyPlotView.getViewport().setYAxisBoundsManual(true);
            xyPlotView.getViewport().setMaxY(700);
            xyPlotView.getViewport().setMinY(0);
        }
    }



}