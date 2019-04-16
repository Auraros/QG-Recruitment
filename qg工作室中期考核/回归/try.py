# -*- coding:utf-8 -*-
import math
import warnings
import operator
import random
import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import matplotlib.patches as mpatchs

warnings.filterwarnings('ignore')   #忽略警告
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

def loadDataSet(filename):
    """
    函数说明:加载数据
    Parameters:
        fileName - 文件名
    Returns:
        xArr - x数据集
        yArr - y数据集
    """
    #打开文件，以空格为分隔符
    dataSet = pd.read_csv(filename, delim_whitespace=True )
    #给每一列的数据加上一个标签，方便提取
    houseData = pd.DataFrame(data=np.array(dataSet), columns=['CRIM', 'ZN', 'INDUS', 'CHAS', 'NOX', 'RM', 'AGE', 'DIS', 'RAD', 'TAX', 'PTRATIO', 'B', 'LSTAT', 'MEDV'], index=range(505))
    #提取出自住房的平均房价的影响价格
    influencingFactor = houseData[['CRIM', 'ZN', 'INDUS', 'CHAS', 'NOX', 'RM', 'AGE', 'DIS', 'RAD', 'TAX', 'PTRATIO', 'B', 'LSTAT']]
    #提取出自主方的平均房价
    AverageHousePrice = houseData['MEDV']
    #返回两个数据集
    influencingFactor = influencingFactor.values
    AverageHousePrice = AverageHousePrice.values
    return influencingFactor, AverageHousePrice

def regularize(xMat, yMat):
    """
    函数说明:数据标准化
    Parameters:
        xMat - x数据集
        yMat - y数据集
    Returns:
        inxMat - 标准化后的x数据集
        inyMat - 标准化后的y数据集
    Website:
        https://www.cuijiahua.com/
    Modify:
        2017-12-03
    """
    inxMat = xMat.copy()                                                        #数据拷贝
    inyMat = yMat.copy()
    yMean = np.mean(yMat, 0)                                                    #行与行操作，求均值
    inyMat = yMat - yMean                                                        #数据减去均值
    inMeans = np.mean(inxMat, 0)                                                   #行与行操作，求均值
    inVar = np.var(inxMat, 0)                                                     #行与行操作，求方差
    # print(inxMat)
    print(inMeans)
    # print(inVar)
    inxMat = (inxMat - inMeans) / inVar                                            #数据减去均值除以方差实现标准化
    return inxMat, inyMat

def ridgeRegres(xMat, yMat, lam = 0.2):
    """
    函数说明:岭回归
    Parameters:
        xMat - x数据集
        yMat - y数据集
        lam - 缩减系数
    Returns:
        ws - 回归系数
    Website:
        https://www.cuijiahua.com/
    Modify:
        2017-11-20
    """
    xTx = xMat.T * xMat
    denom = xTx + np.eye(np.shape(xMat)[1]) * lam
    if np.linalg.det(denom) == 0.0:
        print("矩阵为奇异矩阵,不能转置")
        return
    ws = denom.I * (xMat.T * yMat)
    return ws


def rssError(yArr, yHatArr):
    """
    函数说明:计算平方误差
    Parameters:
        yArr - 预测值
        yHatArr - 真实值
    Returns:

    Website:
        https://www.cuijiahua.com/
    Modify:
        2017-12-03
    """
    return ((yArr - yHatArr) ** 2).sum()

def standRegres(xArr,yArr):
    """
    函数说明:计算回归系数w
    Parameters:
        xArr - x数据集
        yArr - y数据集
    Returns:
        ws - 回归系数
    Website:
        https://www.cuijiahua.com/
    Modify:
        2017-11-12
    """
    xMat = np.mat(xArr); yMat = np.mat(yArr).T
    xTx = xMat.T * xMat                            #根据文中推导的公示计算回归系数
    if np.linalg.det(xTx) == 0.0:
        print("矩阵为奇异矩阵,不能转置")
        return
    ws = xTx.I * (xMat.T*yMat)
    return ws


def crossValidation(xArr, yArr, numVal=10):
    """
    函数说明:交叉验证岭回归
    Parameters:
        xArr - x数据集
        yArr - y数据集
        numVal - 交叉验证次数
    Returns:
        wMat - 回归系数矩阵
    Website:
        https://www.cuijiahua.com/
    Modify:
        2017-11-20
    """
    m = len(yArr)  # 统计样本个数
    indexList = list(range(m))  # 生成索引值列表
    errorMat = np.zeros((numVal, 30))  # create error mat 30columns numVal rows
    for i in range(numVal):  # 交叉验证numVal次
        trainX = [];
        trainY = []  # 训练集
        testX = [];
        testY = []  # 测试集
        random.shuffle(indexList)  # 打乱次序
        for j in range(m):  # 划分数据集:90%训练集，10%测试集
            if j < m * 0.9:
                trainX.append(xArr[indexList[j]])
                trainY.append(yArr[indexList[j]])
            else:
                testX.append(xArr[indexList[j]])
                testY.append(yArr[indexList[j]])
        wMat = ridgeTest(trainX, trainY)  # 获得30个不同lambda下的岭回归系数
        for k in range(30):  # 遍历所有的岭回归系数
            matTestX = np.mat(testX);
            matTrainX = np.mat(trainX)  # 测试集
            meanTrain = np.mean(matTrainX, 0)  # 测试集均值
            varTrain = np.var(matTrainX, 0)  # 测试集方差
            matTestX = (matTestX - meanTrain) / varTrain  # 测试集标准化
            yEst = matTestX * np.mat(wMat[k, :]).T + np.mean(trainY)  # 根据ws预测y值
            errorMat[i, k] = rssError(yEst.T.A, np.array(testY))  # 统计误差
    meanErrors = np.mean(errorMat, 0)  # 计算每次交叉验证的平均误差
    minMean = float(min(meanErrors))  # 找到最小误差
    bestWeights = wMat[np.nonzero(meanErrors == minMean)]  # 找到最佳回归系数
    xMat = np.mat(xArr);
    yMat = np.mat(yArr).T
    meanX = np.mean(xMat, 0);
    varX = np.var(xMat, 0)
    unReg = bestWeights / varX  # 数据经过标准化，因此需要还原
    print(unReg)

def ridgeTest(xArr, yArr):
    """
    函数说明:岭回归测试
    Parameters:
        xMat - x数据集
        yMat - y数据集
    Returns:
        wMat - 回归系数矩阵
    Website:
        https://www.cuijiahua.com/
    Modify:
        2017-11-20
    """
    xMat = np.mat(xArr); yMat = np.mat(yArr).T
    #数据标准化
    yMean = np.mean(yMat, axis = 0)                        #行与行操作，求均值
    yMat = yMat - yMean                                    #数据减去均值
    xMeans = np.mean(xMat, axis = 0)                    #行与行操作，求均值
    xVar = np.var(xMat, axis = 0)                        #行与行操作，求方差
    xMat = (xMat - xMeans) / xVar                        #数据减去均值除以方差实现标准化
    numTestPts = 30                                        #30个不同的lambda测试
    wMat = np.zeros((numTestPts, np.shape(xMat)[1]))    #初始回归系数矩阵
    for i in range(numTestPts):                            #改变lambda计算回归系数
        ws = ridgeRegres(xMat, yMat, np.exp(i - 10))    #lambda以e的指数变化，最初是一个非常小的数，
        wMat[i, :] = ws.T                                 #计算回归系数矩阵
    return wMat

filename = 'housing.txt'
influencingFactor, AverageHousePrice = loadDataSet(filename)
crossValidation(influencingFactor, AverageHousePrice)