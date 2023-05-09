package com.example.demo.api;

import com.example.demo.business.abstracts.PlaneService;
import com.example.demo.enums.PlaneEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;

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
    void thrustUp(@PathVariable("destination") PlaneEnum destination) {
        iPlaneControl.planeCommand(destination);
    }

}
