'''
File: client.py
Project: client
Created Date: Friday August 27th 2021
Author: Ronan (ronan.lashermes@inria.fr)
-----
Last Modified: Tuesday, 31st August 2021 9:20:24 am
Modified By: Ronan (ronan.lashermes@inria.fr>)
-----
Copyright (c) 2021 INRIA
'''

import serial
import numpy as np
from termcolor import colored, cprint
import sys
import os

def timing_to_proba_min(tm):
    pm = np.zeros(tm.shape)
    mins = np.min(tm,0)

    (nrows, ncols) = tm.shape

    for c in range(ncols):
        for r in range(nrows):
            if tm[r,c] <= mins[c]:
                pm[r,c] = 1.0
            else:
                pm[r,c] = 0.0


    #normalize by column

    # (rows, cols) = pm.shape
    s = np.sum(pm)

    if s != 0.0:
        pm /= s


    return pm

class RPi:
    BAUD_RATE = 115200

    def __init__(self, serial_port, debug=False):
        self.serial_handle = serial.Serial(serial_port, self.BAUD_RATE, timeout=3)
        self.debug = debug

    # RAW SERIAL

    def send_bytes(self, bytes):
        self.serial_handle.write(bytes)

    def send_str(self, str):
        self.serial_handle.write(str.encode('utf-8'))

    def read_bytes(self, count):
        return self.serial_handle.read(count)

    def read_until(self, end_bytes):
        buffer = bytearray()
        
        while buffer.endswith(end_bytes) == False:
            buffer.extend(self.read_bytes(1))

        return bytes(buffer)

    def test(self):
        self.send_bytes(b"t")
        if self.debug:
            cprint("Sending test command", 'yellow', end="... ")
        buf = self.read_until(b"\n\r")
        if buf.startswith(b"RPi3 Test OK") == False:
            cprint("Cannot connect to RPi3", 'red')
        elif self.debug:
            cprint("OK", 'green')

    def benchmark(self):
        self.send_bytes(b"b")
        if self.debug:
            cprint("Sending benchmark ('b') command", 'yellow', end="... ")
        
        timings = []

        
        max = 0
        while True:
            l = self.read_until(b"\n")
            if l == b"ack\n":
                break

            splitted = l.split(b',') #i, o, timing
            i = int(splitted[0])
            o = int(splitted[1])
            t = int(splitted[2])
            timings.append([i, o, t])
            if i > max:
                max = i
            if o > max:
                max = o

        max += 1 # 0-based index to size

        mat = np.zeros((max, max), dtype = int)

        for t in timings:
            mat[(t[0], t[1])] = t[2]

        # print(mat)
        return mat

    def intensity_benchmark(self, iterations = 1000):
        mat = self.benchmark()
        intens = np.zeros(mat.shape)

        for i in range(iterations):
            mat = self.benchmark()
            pm = timing_to_proba_min(mat)
            intens = np.add(intens, pm)
        
        return intens/iterations

    def multi_benchmark(self, iterations = 1000):
        mat = self.benchmark()

        for i in range(iterations-1):
            print("Benchmark " + str(i+1) + "/" + str(iterations))
            mat = np.add(mat, self.benchmark())

        return mat / iterations


if __name__ == '__main__':
    rpi = RPi("/dev/ttyUSB0", debug=False)
    # print(sys.argv[0])

    rpi.test()
    # mat = rpi.multi_benchmark()
    mat = rpi.intensity_benchmark(100)
    result_dir = "results/"

    if len(sys.argv) > 1:
        bench = sys.argv[1]
        os.makedirs(result_dir, exist_ok=True)
        print("Saving...")
        np.savetxt(result_dir + bench + "_matrix.csv", mat, delimiter=",",fmt='%s')
    else:
        np.savetxt("benchmark.csv", mat, delimiter=",",fmt='%s')