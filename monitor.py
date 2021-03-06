import time
import matplotlib.pyplot as plt
from drawnow import *
import serial

REF_VOLTAGE = 5
MAX_ADC_VALUE = 255
FRAME_INTERVAL = 1000
MAX_DATA_LENGTH = 1000

myArduino = serial.Serial('COM3', 230400)
plt.ion()
data = [ ]
i = 0
start_time = time.time()
while (True):
    value = myArduino.read(1)  # read 1 byte
    #print(value)
    #skip some wrong value caused by communication    
    try:
        #convert ADC reading in byte string to voltage
        #value = value.strip()
        value = value.hex()
        value = int(value,16)
        #print(value)
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
            plt.ylim(-5,10)
            plt.title('Osciloscope')
            plt.grid(True)
            plt.ylabel('ADC outputs')
            plt.plot(data, 'ro-', label='Channel 0', marker=',')
            plt.legend(loc='lower right')
        drawnow(NewFrame)  #update plot to reflect new data input
        print('Frequency:',FRAME_INTERVAL/(time.time() - start_time))
        i = 0
        start_time = time.time()
        
    else:
        i += 1