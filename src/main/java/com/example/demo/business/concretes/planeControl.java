package com.example.demo.business.concretes;

import com.example.demo.business.abstracts.PlaneService;
import com.example.demo.enums.PlaneEnum;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;
import com.fazecast.jSerialComm.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;

@Service
@EnableScheduling
public class planeControl implements PlaneService {



    SerialPort []comnPort;
    int port;


    @Autowired
    public planeControl(){
        Scanner scanner = new Scanner(System.in);
        this.comnPort = SerialPort.getCommPorts();
        System.out.println("\nPort secimi yapin");
        for (int i = 0; i < comnPort.length; i++)
            System.out.println("\n" + (i + 1) + ") " + comnPort[i].getDescriptivePortName());
        port = scanner.nextInt() - 1;
        comnPort[port].setBaudRate(2000000);
        comnPort[port].setNumDataBits(8);
        comnPort[port].setNumStopBits(1);
        comnPort[port].setParity(SerialPort.NO_PARITY);
        comnPort[port].addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
            }

            @Override
            public void serialEvent(SerialPortEvent serialPortEvent) {
                byte[] readBuffer = new byte[comnPort[port].bytesAvailable()];
                int numRead = comnPort[port].readBytes(readBuffer, readBuffer.length);
                for (int i = 0; i < readBuffer.length; i++) {
                    System.out.print((char) readBuffer[i]);
                }
            }
        });
        comnPort[port].openPort();
        System.out.println(comnPort[port].getDescriptivePortName());

    }

    //@Scheduled(fixedDelay = 1)
    @SneakyThrows
    public void planeCommand(PlaneEnum destination) {
        String destinationCopy = destination.toString() + '\n';
        comnPort[port].writeBytes(destinationCopy.getBytes(), destinationCopy.length());

    }
    public void thrustCommand(String thrustPercentage){
        thrustPercentage = "motor:"+thrustPercentage+'\n';
        comnPort[port].writeBytes(thrustPercentage.getBytes(),thrustPercentage.length());
    }
}
