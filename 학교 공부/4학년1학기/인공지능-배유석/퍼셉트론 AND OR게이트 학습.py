# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

def AND(x,w,b):
    tmp = np.dot(x, w) + b
    if tmp <= 0:
        return 0
    elif tmp > 0:
        return 1
    
def NAND(x,w,b):
    tmp = np.dot(x, w) + b
    if tmp <= 0:
        return 0
    elif tmp > 0:
        return 1
    
def OR(x,w,b):
    tmp = np.dot(x, w) + b
    if tmp <= 0:
        return 0
    elif tmp > 0:
        return 1

dataNum = 2
trainData1 = np.zeros((dataNum,2))
trainData1[0][0] = 0
trainData1[0][1] = 0
trainData1[1][0] = 0
trainData1[1][1] = 1

trainData2 = np.zeros((dataNum,2))
trainData2[0][0] = 1
trainData2[0][1] = 0
trainData2[1][0] = 1
trainData2[1][1] = 1

trainData = np.zeros((dataNum*2, 2))

trainData[0:dataNum, : ] = trainData1
trainData[dataNum:dataNum*2, : ] = trainData2

trainout = np.zeros((dataNum*2, 1))

# AND
trainout[0] = 0
trainout[1] = 0
trainout[2] = 0
trainout[3] = 1

# OR
trainout[0] = 0
trainout[1] = 1
trainout[2] = 1
trainout[3] = 1

plt.plot(trainData1[:, 0], trainData1[:, 1], "*")
plt.plot(trainData2[:, 0], trainData2[:, 1], "*")

step = 500
input = 2; out = 1
w = np.random.rand(input, out);
b = np.random.randn(1)
a = np.arange(-1, 1.1, 0.1)
plt.plot(a, (-w[0, 0]*a - b)/w[1, 0])
eta = 0.5

for j in range(1, step, 1):
    for i in range(0, dataNum, 1):
        x = trainData[i]
        ry = trainout[i]
        
        #y = AND(x,w,b)
        #y = NAND(x,w,b)
        y = OR(x,w,b)
            
        e = ry - y
        dw = eta * e *np.transpose([np.array(x)])
        db = eta * e * 1
        w = w + dw
        b = b + db

plt.plot(a, (-w[0, 0]*a - b)/w[1, 0], 'r')
plt.show()