# -*- coding:utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import math
import warnings
import operator
import pandas as pd
import matplotlib as mpl
import matplotlib.lines as mlines
import matplotlib.patches as mpatchs


def loadDataSet(filename):
    """
    函数说明：从文件中下载数据，并将分离除连续型变量和标签变量
    :parameter:
            data - Iris数据集
            attributes - 鸢尾花的属性
            type - 鸢尾花的类别
            sl-花萼长度 , sw-花萼宽度, pl-花瓣长度, pw-花瓣宽度
    :return:
    """
    iris_data = pd.read_csv(filename)   #打开文件
    iris_data = pd.DataFrame(data=np.array(iris_data), columns=['sl', 'sw', 'pl', 'pw', 'type'], index=range(149))   #给数据集添加列名，方便后面的操作
    attributes = iris_data[['sl', 'sw', 'pl', 'pw']]   #分离出花的属性
    iris_data['type'] = iris_data['type'].apply(lambda x: x.split('-')[1])  # 最后类别一列，感觉前面的'Iris-'有点多余即把class这一列的数据按'-'进行切分取切分后的第二个数据
    labels = iris_data['type']     #分理出花的类别
    attriLabels = []      #建立一个标签列表
    for label in labels:        #为了更方便操作，将三中不同的类型分别设为1，2，3
        if label == 'setosa':    #如果类别为setosa的话，设为1
            attriLabels.append(1)
        elif label == 'versicolor':  #如果是versicolor的时候设为2
            attriLabels.append(2)
        elif label == 'virginica':  #如果是virginica的时候设为3
            attriLabels.append(3)
    return attributes, attriLabels


def autoNorm(attributes):
    """
    函数说明： 对数据进行归一化
    :parameter
            attributes - 特征矩阵
    :return:  nonormAttributes - 归一化后的矩阵
    """
    attributes = attributes.values  #将DataFrame类型转变为array类型
    minVal = attributes.min()      #找出数据中的最小值
    maxVal = attributes.max()      #找出数据中的最大值
    ranges = maxVal - minVal        #数据范围
    normAttributes = np.zeros(np.shape(attributes))  #初始化归一化数据
    m = attributes.shape[0]     #获取数据的行数
    normAttributes = attributes - np.tile(minVal, (m, 1))  #创建一个全是最小值得数组
    normAttributes = normAttributes / np.tile(ranges, (m, 1))  #创建一个全是范围值得数组
    return normAttributes, ranges, minVal   #返回归一化后的数据


def distEclud(vecA,vecB):
    return np.sqrt(np.sum(np.power((vecA-vecB),2)))
def randCent(dataSet,k):
    m = np.shape(dataSet)[1]
    center = np.mat(np.ones((k,m)))
    for i in range(m):
        centmin = min(dataSet[:,i])
        centmax = max(dataSet[:,i])
        center[:,i] = centmin + (centmax - centmin) * np.random.rand(k,1)
    return center
def kMeans(dataSet,k,distMeans = distEclud,createCent = randCent):
    m = np.shape(dataSet)[0]
    clusterAssment = np.mat(np.zeros((m,2)))
    centroids = createCent(dataSet,k)
    clusterChanged = True
    while clusterChanged:
        clusterChanged = False
        for i in range(m):
            minDist = np.inf
            minIndex = -1
            for j in range(k):
                distJI = distMeans(dataSet[i,:],centroids[j,:])
                if distJI < minDist:
                    minDist = distJI
                    minIndex = j
            if clusterAssment[i,0] != minIndex:
                clusterChanged = True
            clusterAssment[i,:] = minIndex,minDist**2
        for cent in range(k):
            ptsInClust = dataSet[np.nonzero(clusterAssment[:,0].A == cent)[0]]
            centroids[cent,:] = np.mean(ptsInClust,axis = 0)
    return centroids,clusterAssment

def biKmeans(dataSet,k,distMeans = distEclud):
    m = np.shape(dataSet)[0]
    clusterAssment = np.mat(np.zeros((m,2)))
    centroid0 = np.mean(dataSet,axis=0).tolist()
    centList = [centroid0]
    for j in range(m):
        clusterAssment[j,1] = distMeans(dataSet[j,:],np.mat(centroid0))**2
    while (len(centList)<k):
        lowestSSE = np.inf
        for i in range(len(centList)):
            ptsInCurrCluster = dataSet[np.nonzero(clusterAssment[:,0].A == i)[0],:]
            centroidMat,splitClustAss = kMeans(ptsInCurrCluster,2,distMeans)
            sseSplit = np.sum(splitClustAss[:,1])
            sseNotSplit = np.sum(clusterAssment[np.nonzero(clusterAssment[:,0].A != i)[0],1])
            if (sseSplit + sseNotSplit) < lowestSSE:
                bestCentToSplit = i
                bestNewCents = centroidMat.copy()
                bestClustAss = splitClustAss.copy()
                lowestSSE = sseSplit + sseNotSplit
        print('the best cent to split is ',bestCentToSplit)
#        print('the len of the bestClust')
        bestClustAss[np.nonzero(bestClustAss[:,0].A == 1)[0],0] = len(centList)
        bestClustAss[np.nonzero(bestClustAss[:,0].A == 0)[0],0] = bestCentToSplit

        clusterAssment[np.nonzero(clusterAssment[:,0].A == bestCentToSplit)[0],:] = bestClustAss.copy()
        centList[bestCentToSplit] = bestNewCents[0,:].tolist()[0]
        centList.append(bestNewCents[1,:].tolist()[0])
    return np.mat(centList),clusterAssment







data, labels = loadDataSet('iris.data')
normdata = autoNorm(data)
muCentroids, clusterAssing = biKmeans(normdata,3)
fig = plt.figure(0)
ax = fig.add_subplot(111)
ax.scatter(data[:,0],data[:,1],c = clusterAssing[:,0].A,cmap=plt.cm.Paired)
ax.scatter(muCentroids[:,0],muCentroids[:,1])
plt.show()

print(clusterAssing)
print(muCentroids)