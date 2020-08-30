package com.example.ballbouncermobilapp;

import androidx.lifecycle.MutableLiveData;

public class XYValue extends MutableLiveData<XYValue> {

    private double x;
    private double y;
    private double h;

    public XYValue(double x, double y, double h) {
        this.x = x;
        this.y = y;
        this.h = h;
        if (listener != null) listener.onChange();

    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getH() {
        return h;
    }

    public void setH(double h) {
        this.h = h;
    }

    /////////////////////////////
    private ChangeListener listener;

    public void setListener(ChangeListener listener) {
        this.listener = listener;
    }

    public interface ChangeListener {
        void onChange();
    }

}
