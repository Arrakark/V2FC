import serial
import matplotlib.pyplot as plt
ser = serial.Serial('COM4')  # open serial port
ser.readline()
ser.readline()
plt.ion()
plt.show()
while ser.isOpen():
    line = ser.readline()
    line = line.strip()
    valuearray = line.split(',')
    valuearray.pop()
    plt.clf()
    for idx, val in enumerate(valuearray):
        val = float(val)
        plt.bar(idx,val);
    print valuearray
    plt.draw()
    plt.pause(0.00001)