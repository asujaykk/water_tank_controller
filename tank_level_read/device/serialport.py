# -*- coding: utf-8 -*-
"""
Created on Sun May 31 21:05:45 2020

@author: AKHIL_KK
"""
import serial
class ble_serial():
    end_chr=b'\x29'
    strt_chr = b'\x0A\x28'
    choma = b'\x2C'
    def __init__(self,com,baud=9600):
        self.com=com
        self.baud=baud
        #self.serialport=None
        try:
            self.serialport=serial.Serial(port = self.com, baudrate=self.baud,
                           bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
        except serial.SerialException:
            #print("expt",serial.SerialException) 
            raise OSError

    def read_snesdata(self):
        self.serialport.read_until(self.strt_chr)
        return str(self.serialport.read_until(self.end_chr))[2:-2]
    
    def read_line(self):
        return str(self.serialport.readline())
    
    def serial_available(self):
        if self.serialport.in_waiting >0:
            return True
        else:
            return False
    
    def __del__(self):
        self.serialport.close()
               