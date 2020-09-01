package com.example.ballbouncermobilapp;

import java.io.Serializable;

public class DataFromServer implements Serializable {
    private int x;
    private int y;
    private int z;
    private int _x;
    private int _y;
    private int _z;

    public DataFromServer() {
    }


    public void generalSetter(int px, int py, int pz){

        this.x = px;
        this.y = py;
        this.z = pz;
        if(this.z == 0.0) {
            this._x = this.x;
            this._y = this.y;
            this._z = this.z;
        }
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getZ() {
        return z;
    }

    public void setZ(int z) {
        this.z = z;
    }

    public int get_x() {
        return _x;
    }

    public void set_x(int _x) {
        this._x = _x;
    }

    public int get_y() {
        return _y;
    }

    public void set_y(int _y) {
        this._y = _y;
    }

    public int get_z() {
        return _z;
    }

    public void set_z(int _z) {
        this._z = _z;
    }
}
