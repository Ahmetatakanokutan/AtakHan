package com.example.demo.business.abstracts;

import com.example.demo.enums.PlaneEnum;

import java.io.IOException;

public interface PlaneService {
    void planeCommand(PlaneEnum destination) ;
    public void thrustCommand(String thrustPercentage);
}
