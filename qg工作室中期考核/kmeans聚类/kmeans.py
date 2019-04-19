# -*- coding:utf-8 -*-
import math
import warnings
import operator
import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import matplotlib.patches as mpatchs

warnings.filterwarnings('ignore')   #忽略警告
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 伪代码如下
# 创建k个点作为起始质心，可以随机选择(位于数据边界内)
# 　　当任意一个点的簇分配结果发生改变时
# 　　　　对数据集中每一个点
# 　　　　　　　　对每个质心
# 　　　　　　　　　　计算质心与数据点之间的距离
# 　　　　　　　　将数据点分配到距其最近的簇
#  　　　　对每一个簇，计算簇中所有点的均值并将均值作为质心

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



def distEclud(X,Y):
    """
    函数说明：欧式距离公式
    :param X:
    :param Y:
    :return:距离
    """
    return np.sqrt(np.sum((X-Y)**2))

def randCent(dataSet, k):
    """
    函数说明：为给定数据集构建一个包含k个随机质点的集合
    :param dataSet: 数据集
    :param k:  k个随机质点
    :return: centroids - 包含k个随机质点的集合
    """
    m, n = dataSet.shape   #得到行列数目
    centroids = np.zeros((k, n))#定义一个k行n列的全为0的质点集合
    for i in range(k):     #遍历得到每一个质点
        index = int(np.random.uniform(0, m)) #索引值在0到m中随机取样
        centroids[i, :] = dataSet[index, :] #索引值在dataSet的值为生成的随机质点
    return centroids   #范围随机质点数据集

def randCent(dataSet, k):
    """
    函数说明：随机初始化k个质心（质心满足数据边界之内）
    :param dataSet:数据集
    :param k:  质点个数
    :return:centroids 返回初始化得到的k个质心向量
    """
    m, n = dataSet.shape  # 得到行列数目
    centroids = np.zeros((k, n))  # 定义一个k行n列的全为0的质点集合
    for j in range(n):
        #得到该列数据的最小值
        minJ = min(dataSet[:, j])
        #得到该列数据的范围
        rangeJ = float(max(dataSet[:, j]) - minJ)
        #k个质心向量的第j维数据值随机为位于范围内的某一个值
        centroids[:, j] = np.mat(minJ + rangeJ * np.random.rand(k))
    return centroids


def KMeans(dataSet, k, distMeas=distEclud, createCent=randCent):
    """
    函数说明：k均值算法
    :param dataSet: 特征集
    :param k: k个值
    :return:
    """
    m = np.shape(dataSet)[0]     #得到行的数目
    clusterAssment = np.mat(np.zeros((m, 2))) #初始化一个（m，2）矩阵
    clusterChange = True      #定义聚类是否发生变化
    centroids = createCent(dataSet, k)        #创建初始化的k个质心向量
    while clusterChange:          #只要聚类结果一直发生变化，就一直执行聚类算法，直到所有数据点聚类结果不发生变化
        clusterChange = False  #聚类结果定义为False

        for i in range(m):     #遍历数据集中的每一个样本
            minDist = np.inf       #初始化最小距离为100000
            minIndex = -1    #最小距离索引定为-1

            for j in range(k): #循环k个类的质心
                distance = distMeas(centroids[j, :], dataSet[i, :]) #计算数据点到质心的欧式距离
                if distance < minDist:  #如果当前距离少于最小距离
                    minDist = distance#当前距离定为最小距离，最小距离的索引定为j
                    minIndex = j

            if clusterAssment[i, 0] != minIndex:  #当前聚类结果中第i个样本的结果发生变化
                clusterChange = True    #把clusterChange定义为Ture，代表发生了变化
            clusterAssment[i, :] = minIndex, minDist**2     #更新当前新变化的聚类结果和错误平方
             #打印kmeans聚类质心
        for j in range(k):                #遍历每一个质心
            #因此首先先比较clusterAssment[:,0].A==cent的真假，如果为真则记录了他所在的行，因此在用切片进行取值。
            pointsInCluster = dataSet[np.nonzero(clusterAssment[:, 0].A == j)[0]]
            # 计算这些数据的均值（axis=0：求列的均值），作为该类质心向量
            centroids[j, :] = np.mean(pointsInCluster, axis=0)
    print("Congratulation,cluster complete!")
    #返回k个聚类，聚类结果和误差
    return centroids, clusterAssment

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


if __name__ == '__main__':
    filename = "iris.data"
    attributes, label = loadDataSet(filename)
    normAttribute, ranges, minVal = autoNorm(attributes)
    centroids, clusterAssment = KMeans(normAttribute, 3)
    print(clusterAssment)