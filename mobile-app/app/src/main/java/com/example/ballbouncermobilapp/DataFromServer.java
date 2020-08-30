package com.example.ballbouncermobilapp;

import java.io.Serializable;

public class DataFromServer implements Serializable {
    private double x;
    private double y;
    private double z;
    private double _x;
    private double _y;
    private double _z;

    public DataFromServer() {
    }

    public void generalSetter(double px, double py, double pz){
        this._x = this.x;
        this._y = this.y;
        this._z = this.z;
        this.x = px;
        this.y = py;
        this.z = pz;
    }

    public double get_x() {
        return _x;
    }

    public double get_y() {
        return _y;
    }

    public double get_z() {
        return _z;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getZ() {
        return z;
    }

    public void setZ(double z) {
        this.z = z;
    }

    @Override
    public String toString() {
        return "DataFromServer{" +
                "x=" + x +
                ", y=" + y +
                ", z=" + z +
                ", _x=" + _x +
                ", _y=" + _y +
                ", _z=" + _z +
                '}';
    }
}
