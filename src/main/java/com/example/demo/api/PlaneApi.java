package com.example.demo.api;

import com.example.demo.business.abstracts.PlaneService;
import com.example.demo.enums.PlaneEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.math.BigInteger;

@RestController
@RequestMapping("api/plane")
public class PlaneApi {
    PlaneService iPlaneControl;

    @Autowired
    public PlaneApi( PlaneService iPlaneControl){
        super();
        this.iPlaneControl = iPlaneControl;
    }

    @GetMapping ("{destination}")
    void planeControl(@PathVariable("destination") PlaneEnum destination) {
        iPlaneControl.planeCommand(destination);
    }

    @GetMapping("/thrust/{thrust}")
    void thrustControl(@PathVariable("thrust") String thrustPercentage){
        iPlaneControl.thrustCommand(thrustPercentage);
    }


}
