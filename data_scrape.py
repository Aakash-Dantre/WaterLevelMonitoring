import requests
import json
import matplotlib.pyplot as plt
import numpy as np
from onem2m import *
from selenium import webdriver
from time import sleep
from selenium.webdriver.firefox.options import Options
#from selenuim.webdriver.chrome.options import Options

data4=[]
data17=[]
data22=[]

# CREATE FILES team4f,team22f,team17f.
def get_data_group(group_name):
    headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
    }

    group_uri = server+str(group_name)
    print(group_uri)
    response = requests.get(group_uri, headers=headers)
    # print('Return code : {}'.format(response.status_code))
    #print('Return Content : {}'.format(response.text))
    try:_resp = json.loads(response.text)
    except:print("lol:error")
    val=[]
    val.append(_resp['m2m:cin']['lt'])
    val.append(_resp['m2m:cin']['con'])
    val.append(group_name)
    if(team==4):data4.append(val)
    if(team==17):data17.append(val)
    if(team==22):data22.append(val)
    return response.status_code, _resp

if __name__ == "__main__":

    server="http://onem2m.iiit.ac.in:443/~/in-cse/in-name/Team4_Water_Level_Monitoring_in_Overhead_Tanks/node_1/"
    team=4
    lst1=discovery("http://onem2m.iiit.ac.in:443/~/in-cse/cnt-637307938")[1]
    for i in range(len(lst1)):
        lst1[i]=lst1[i][8:]
    for i in lst1:
        get_data_group(i)

    server="http://onem2m.iiit.ac.in:443/~/in-cse/in-name/Team17_Water_Level_Monitoring_in_Overhead_Tanks/node_1/"
    team=17
    lst2=discovery("http://onem2m.iiit.ac.in:443/~/in-cse/cnt-883266330")[1]
    for i in range(len(lst2)):
        lst2[i]=lst2[i][8:]
    for i in lst2:
        get_data_group(i)

    server="http://onem2m.iiit.ac.in:443/~/in-cse/in-name/Team22_Water_Level_Monitoring_in_Overhead_Tanks/node_1/"
    team=22
    lst3=discovery("http://onem2m.iiit.ac.in:443/~/in-cse/cnt-662282378")[1]
    for i in range(len(lst3)):
        lst3[i]=lst3[i][8:]
    for i in lst3:
        get_data_group(i)

    server="http://onem2m.iiit.ac.in:443/~/in-cse/in-name/Team4_Water_Level_Monitoring_in_Overhead_Tanks/node_1/"
    
    with open('team4f', 'a') as f:
        for item in data4:
            f.write("%s,\n" % item)
    with open('team17f', 'a') as f:
        for item in data17:
            f.write("%s,\n" % item)
    with open('team22f', 'a') as f:
        for item in data22:
            f.write("%s,\n" % item)        

