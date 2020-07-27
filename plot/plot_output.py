import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd

DATAPATH = "../data/"

def read(filename):
    df = pd.read_csv(DATAPATH+filename, header=None)
    data = df.to_numpy()
    x = data[:,0] 
    y = data[:,1] 
    z = data[:,2] 
    cat = data[:,3] 

    return x, y, z, cat

def plot_data(x,y,z,c):

    xs = [[],[],[],[]]
    ys = [[],[],[],[]]
    zs = [[],[],[],[]]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    #split
    for (xi,yi,zi,ci) in zip(x,y,z,c):
        xs[int(ci)].append(xi)
        ys[int(ci)].append(xi)
        zs[int(ci)].append(xi)

    ax.scatter(xs[0],ys[0],zs[0])
    ax.scatter(xs[1],ys[1],zs[1])
    ax.scatter(xs[2],ys[2],zs[2])
    ax.scatter(xs[3],ys[3],zs[3])
    plt.show()

def main():
    x,y,z,cat = read("outfile.csv") 
    plot_data(x,y,z,cat)

if __name__ == '__main__':
    main()
