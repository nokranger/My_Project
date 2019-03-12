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
            print(read)
            readlist = read
            readlist = list(readlist)
            print(readlist[0])
        if(read == "Sta1"):
            status = read
            print(status)
        elif(readlist[0] == "A"):
            processes = read
            print(processes)
        elif(read == "S1OFF + S2ON"):
            endprocess = read
            print(endprocess)
        elif(read == "END"):
            end = read
            print(end)
            data['AD1'].append({
                'status' : status,
                'process' : processes,
                'end' : end,
                'endprocess' : endprocess
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
        print('1')

def thread_4():
    while True:
        print('2')

thread.start_new_thread(thread_1,())
thread.start_new_thread(thread_2,())

while True:
    pass
