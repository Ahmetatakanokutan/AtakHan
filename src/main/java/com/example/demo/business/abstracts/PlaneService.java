package com.example.demo.business.abstracts;

import com.example.demo.entites.PlaneEntity;
import com.example.demo.enums.PlaneEnum;

import java.io.IOException;

public interface PlaneService {
    void planeCommand(PlaneEnum destination) ;
    void thrustCommand(String thrustPercentage);
    void planeCommand(PlaneEntity plane);
}
