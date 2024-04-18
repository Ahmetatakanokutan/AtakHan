package com.example.demo.api;

import com.example.demo.business.abstracts.PlaneService;
import com.example.demo.enums.PlaneEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("api/plane")
public class PlaneApi {
    PlaneService iPlaneControl;

    @Autowired
    public PlaneApi(PlaneService iPlaneControl) {
        super();
        this.iPlaneControl = iPlaneControl;
    }

    @CrossOrigin(origins = "http://localhost:63342")
    @GetMapping("{destination}")
    void planeControl(@PathVariable("destination") PlaneEnum destination) {
        iPlaneControl.planeCommand(destination);
    }

    @CrossOrigin(origins = "http://localhost:63342")
    @GetMapping("/thrust/{thrust}")
    void thrustControl(@PathVariable("thrust") String thrustPercentage) {
        iPlaneControl.thrustCommand(thrustPercentage);
    }
}
