import time
import matplotlib.pyplot as plt
from drawnow import *
import serial

REF_VOLTAGE = 5
MAX_ADC_VALUE = 1023
FRAME_INTERVAL = 400
MAX_DATA_LENGTH = 800

myArduino = serial.Serial('COM3', 115200)
plt.ion()
data = [ ]
i = 0
#start_time = time.time()
while (True):
    value = myArduino.readline()  # read the reply
    #print(value)
    #skip some wrong value caused by communication    
    try:
        #convert ADC reading in byte string to voltage
        value = value.strip()
        value = int(value)
        value = value * REF_VOLTAGE / MAX_ADC_VALUE
        #print('Voltage:',value)
        
        data.append(value)
    except:
        data.append('')
    #control data length to make it in real time
    if (len(data) > MAX_DATA_LENGTH):
        data.pop(0)
    #control frame rate to make it in real time
    if i > FRAME_INTERVAL:
        def NewFrame():
            plt.ylim(0,5)
            plt.title('Osciloscope')
            plt.grid(True)
            plt.ylabel('ADC outputs')
            plt.plot(data, 'ro-', label='Channel 0')
            plt.legend(loc='lower right')
        drawnow(NewFrame)  #update plot to reflect new data input
        #print('Sample Frequency:',FRAME_INTERVAL/(time.time() - start_time))
        i = 0
        #start_time = time.time()
        
    else:
        i += 1