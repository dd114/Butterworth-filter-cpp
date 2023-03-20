import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

if __name__ == '__main__':

    f = open('inputSignal.txt', 'r') # требования к файлу: первая колонка - координата/время, вторая - значения функции
    # f = open('approxY.txt', 'r')
    tempX = list()
    tempY = list()

    for line in f:
        tempValue = [float(i) for i in line.strip().split()]
        tempX += [tempValue[0]]
        tempY += [tempValue[1]]
    f.close()

    tempX = np.array(tempX)
    tempY = np.array(tempY)

    # print(tempX)
    print(tempY)

    # plt.plot(tempX, tempY, ".-")
    plt.plot(tempX, tempY)
    plt.xlabel("ось X")
    plt.ylabel("ось Y")
    plt.show()