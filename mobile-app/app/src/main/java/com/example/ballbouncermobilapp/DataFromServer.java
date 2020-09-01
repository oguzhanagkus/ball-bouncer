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

        this.x = px;
        this.y = py;
        this.z = pz;

        if(this.z == 0.0) {
            this._x = this.x;
            this._y = this.y;
            this._z = this.z;
        }
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

    public double get_x() {
        return _x;
    }

    public void set_x(double _x) {
        this._x = _x;
    }

    public double get_y() {
        return _y;
    }

    public void set_y(double _y) {
        this._y = _y;
    }

    public double get_z() {
        return _z;
    }

    public void set_z(double _z) {
        this._z = _z;
    }
}
