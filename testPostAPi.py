import urllib
import requests
import json
import time
import thread
# status = 0
# url = "https://api.openweathermap.org/data/2.5/weather?q=bangkok,th&appid=2100e87ca548704c2137ff03cd791158"
# response = urllib.urlopen(url)
# data = json.loads(response.read())
# data2 = json.dumps(data)
# print data['main']
# print data['weather']
# print type(data)
# print 'This converted'
# # print data2
# dataC = json.loads(data2)
# print dataC
def Thread():
    print("1")
    while True:
        print "running"
        time.sleep(3)
        url = "http://localhost:8081/start/get-start"
        response2 = urllib.urlopen(url)
        dataa = json.loads(response2.read())
        dataaa = json.dumps(dataa)
        print "dddd : "
        print dataaa
        if dataa['isTimeOut'] == False :
            time.sleep(20)
            print "false"
            # post-chemical
            # readSend = {"read law na i sas"} 
            print "go read and send"
            urlSend = "http://localhost:8081/chemicaltank/post-chemical"
            dataSend = {"date" : "070519", "specific_gravity" : 4,"residual_chemicals" : 3,"temp" : 4,"type_chemical" : "tc9"}
            headers = {'Content-type': 'application/json'}
            rsp = requests.post(urlSend, json=dataSend, headers=headers)
            print(rsp.text)
            print("done")
            # status = 1
            # if status == 1 :
            #     urlTimeout = "http://localhost:8081/start/post-start"
            #     dataTimeout = {"isTimeOut" : True}
            #     headersTimeOut = {'Content-type': 'application/json'}
            #     rqTimeOut = requests.post(urlTimeout, json=dataTimeout, headers=headersTimeOut)
            #     print(rqTimeOut.text)
            #     print("Set Timeout true")
            #     status = 0

            
thread.start_new_thread(Thread,())

while True:
    pass