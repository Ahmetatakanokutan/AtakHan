package com.example.demo.Entites;

import com.example.demo.enums.Angle;
import com.example.demo.enums.PlaneEnum;
import jakarta.persistence.*;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.lang.Nullable;

@Entity
@Data
@NoArgsConstructor
public class Plane {
    public Plane(int id){
        this.id = id;
    }

    @GeneratedValue(strategy = GenerationType.IDENTITY)

    @Id
    @Column(name = "id")
    private int id;

    @Nullable
    @Column(name = "Name")
    private String name;

    @Nullable
    @Column(name = "moveAngle")
    private Angle moveAngle;

    @Nullable
    @Column(name = "thrust")
    private PlaneEnum thrust;

}
