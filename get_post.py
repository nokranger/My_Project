import RPi.GPIO as GPIO
import serial
import time
import thread
from unidecode import unidecode
import json
data = {}
data['AD1'] = []

#from time import sleep
ser = serial.Serial('/dev/ttyAMA0',9600);
def thread_1():
    while True:
        if ser.inWaiting:
            time.sleep(2)
            print("thread 1")
            read = ser.readline().decode().strip('\r\n');
            print("READ : " + read)
            readlist = read
            readlist = list(readlist)
            print(readlist[6])
        if(read == "AD1 + S1"):
            status = read
            print("S : " + status)
        elif(readlist[6] == "D"):
            processes = read
            print("p : " + processes)
        elif(read == "AD1 + S1OFF + S2ON"):
            endprocess = read
            print("ee : " + endprocess)
        elif(read == "AD1 + S1OFF + S2OFF"):
            endprocess_2 = read
            print("ee2 : " + endprocess_2)
        elif(read == "AD1 + END"):
            end = read
            print("e : " + end)
            data['AD1'].append({
                'status' : status,
                'process' : processes,
                'process_2' : endprocess_2,
                'endprocess' : endprocess,
                'end' : end
            })
            with open('data.json','w+') as outfile:
                json.dump(data,outfile)
                print("writefile")
        #thread.start_new_thread(thread_2())
            
def thread_2():
    while True:
            print("thread 2")
            ser.write("AD1 + ST" + "\r\n")
            time.sleep(3)
            #thread.start_new_thread(thread_1())
            
def thread_3():
    while True:
            print("thread 3")
            ser.write("AD2 + ST" + "\r\n")
            time.sleep(3)

def thread_4():
    while True:
            print("thread 4")
            ser.write("AD1 + R" + "\r\n")
            time.sleep(3)
def thread_5():
    while True:
            print("thread 5")
            ser.write("AD2 + R" + "\r\n")
            time.sleep(3)

thread.start_new_thread(thread_1,())
thread.start_new_thread(thread_2,())

while True:
    pass
