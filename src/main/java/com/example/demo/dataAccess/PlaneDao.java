package com.example.demo.dataAccess;

import com.example.demo.Entites.Plane;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PlaneDao extends JpaRepository<Plane, Integer> {
}
