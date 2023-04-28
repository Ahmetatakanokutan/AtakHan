package com.example.demo.business.concretes;

import com.example.demo.business.abstracts.PlaneService;
import com.example.demo.dataAccess.PlaneDao;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.fazecast.jSerialComm.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

@Service
public class planeControl implements PlaneService {

    PlaneDao planeDao;

    SerialPort []comnPort = SerialPort.getCommPorts();


    @Autowired
    public planeControl(PlaneDao planeDao){
        this.planeDao = planeDao;
        this.comnPort = SerialPort.getCommPorts();
        comnPort[0].setBaudRate(2000000);
        comnPort[0].setNumDataBits(8);
        comnPort[0].setNumStopBits(1);
        comnPort[0].setParity(SerialPort.NO_PARITY);
        comnPort[0].addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
            }

            @Override
            public void serialEvent(SerialPortEvent serialPortEvent) {
                byte[] readBuffer = new byte[comnPort[0].bytesAvailable()];
                int numRead = comnPort[0].readBytes(readBuffer, readBuffer.length);
                for (int i = 0; i < readBuffer.length; i++) {
                    System.out.print((char) readBuffer[i]);
                }
            }
        });
        comnPort[0].openPort();
    }

    @SneakyThrows
    public void planeCommand(String destination) {
        comnPort[0].writeBytes(destination.getBytes(), destination.length());
    }
}
