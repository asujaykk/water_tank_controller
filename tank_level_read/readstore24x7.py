#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug  5 13:16:58 2021

@author: akhil_kk
"""
import time
from datetime import datetime
import os
#print(os.path.isdir("data"))
import device.serialport as serialport

dataFolderName="data"
timeLimit=5 #in hours
#totalTime=timeLimit*60*60
totalTime=True #for infinite data collecetion

def writeExtractedDataToFile(time,data,dataFolderPath):
    #print("yes")
    #print(os.path.isdir("data"))
    dir_name=dataFolderPath
    if not os.path.isdir(dir_name):
        os.mkdir(dir_name)
    
    #year folder added
    dir_name=dir_name+("/"+str(time[0]))
    if not os.path.isdir(dir_name):
        os.mkdir(dir_name)
    
    #month folder added
    dir_name=dir_name+("/"+str(time[1]))
    if not os.path.isdir(dir_name):
        os.mkdir(dir_name)
    
    #day folder added
    dir_name=dir_name+("/"+str(time[2]))
    if not os.path.isdir(dir_name):
        os.mkdir(dir_name)
    
    #hour folder added
    # dir_name=dir_name+("/"+str(time[3]))
    # if not os.path.isdir(dir_name):
    #     os.mkdir(dir_name)
    file_name=dir_name=dir_name+("/"+str(time[3])+".csv") #new file will be created under day folder for each hour
    file=open(file_name,"a")
    file.write(str(time[6])+','+data+"\n")
    file.close()
    

def getCurrentTime():
    today = datetime.now()
    year=int(today.strftime("%Y"))
    month=int(today.strftime("%m"))
    day=int(today.strftime("%d"))
    hour=int(today.strftime("%H"))
    minute=int(today.strftime("%M"))
    sec=int(today.strftime("%S"))
    ctimesec=time.time()
    # print(year)
    # print(month)
    # print(day)
    # print(hour)
    # print(minute)
    # print(sec)
    return (year,month,day,hour,minute,sec,ctimesec)

#writeExtractedDataToFile(getCurrentTime(),"1,2,3,4","data")

def validateAndExtractData(dataString):
    if dataString[:3]=="b'$" and dataString[len(dataString)-6:]=="#\\r\\n\'":
        #print("hi")
        #print(dataString[len(dataString)-6:])
        return dataString[3:-6]
    else:
        return ""

import serial


#ble_port = serialport.ble_serial("/dev/ttyACM1",baud=9600)

portStatus=False
portNames=("ttyACM0","ttyACM1")
currentPort=0
while totalTime:
    #ble_port=type(serialport)
    if portStatus==False:
       try:
          ble_port = serialport.ble_serial("/dev/"+portNames[currentPort],baud=9600)
          portStatus=True
       except OSError as err:
          portStatus=False
          if currentPort==0:
              currentPort=1
          else:
              currentPort=0
          print("oserror")
          #del ble_port
          #raise
       # else:
       #    print("unk err")
       #    portStatus=False
    
    if portStatus:
        #print("portactive")
        try:
            if ble_port.serial_available():
                serData = ble_port.read_line()
                extractedData=validateAndExtractData(serData)
                if extractedData !="":
                    cTime=getCurrentTime()
                    writeExtractedDataToFile(cTime,extractedData,dataFolderName)
                    #print(sens_value)
        except OSError as err:
          portStatus=False
    if type(totalTime)==bool:
        #do nothing
        print("infinite loop")
    else:
        totalTime -=1
        if (totalTime%10==9):
            print(totalTime)

del ble_port


#while True:
    