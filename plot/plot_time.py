import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd

DATAPATH = "../data/"

def read(filename):
    df = pd.read_csv(DATAPATH+filename, header=None)
    data = df.to_numpy()

    ylim = 0
    
    x = data[:,0] 
    y = data[:,1] 

    for yi in y:
        if yi > ylim:
            ylim = yi
        
    print('ylimit = ', ylim)

    return x, y, ylim

def plot_data(x,y,color):
    plt.plot(x,y, c=color, linewidth=2, alpha=0.5)

def plot_mean(y,color):
    mean = 0.0
    for yi in y:
        mean += yi

    mean /= float(len(y))
    print('mean time = ', mean)

    plt.axhline(mean)

def cut_outliers(y,ylim): 
    yc = []

    for yi in y:
        if yi == ylim:
            yc.append(-1.0)
        else:
            yc.append(yi)

    return np.array(yc)

def main():

    xlearn,ylearn,ylearn_lim = read("learn_time.csv") 
    xcluster,ycluster,ycluster_lim = read("categorize_time.csv") 

    ylearn = cut_outliers(ylearn,ylearn_lim)
    ycluster = cut_outliers(ycluster,ycluster_lim)

    plot_data(xlearn,ylearn,'g')
    plot_data(xcluster,ycluster,'r')

    plot_mean(ylearn,'g')
    plot_mean(ycluster,'r')

    plt.title('Manhattan Distance - Standardization')
    plt.xlabel('Data Sample (no.)')
    plt.ylabel('Time (ns)')

    plt.show()


if __name__ == '__main__':
    main()
