package com.example.demo.entites;

import com.example.demo.enums.PlaneEnum;

public class PlaneEntity {
    private String throttle;
    private float rudder;
    private float elevator;
    private float ailerionRight;
    private float ailerionLeft;
    public String getThrottle() {
        return throttle;
    }

    public void setThrottle(String throttle) {
        this.throttle = throttle;
    }

    public double getRudder() {
        return rudder;
    }

    public String getStringRudder() {
        return String.valueOf(rudder);
    }
    public void setRudder(float rudder) {
        this.rudder = rudder;
    }


    public double getElevator() {
        return elevator;
    }
    public String getStringElevator() {
        return String.valueOf(elevator);
    }
    public void setElevator(float elevator) {
        this.elevator = elevator;
    }

    public double getAilerionRight() {
        return ailerionRight;
    }

    public String getStringAilerionRight() {
        return String.valueOf(ailerionRight);
    }
    public void setAilerionRight(float ailerionRight) {
        this.ailerionRight = ailerionRight;
    }

    public double getAilerionLeft() {
        return ailerionLeft;
    }
    public String getStringAilerionLeft() {
        return String.valueOf(ailerionLeft);
    }
    public void setAilerionLeft(float ailerionLeft) {
        this.ailerionLeft = ailerionLeft;
    }



}
