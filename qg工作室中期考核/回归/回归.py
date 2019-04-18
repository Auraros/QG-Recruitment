# -*- coding:utf-8 -*-
import math
import random
import warnings
import operator
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
    influencingFactor = influencingFactor.tolist()
    AverageHousePrice = AverageHousePrice.values
    AverageHousePrice = AverageHousePrice.tolist()
    return influencingFactor, AverageHousePrice, houseData


def regularize(xMat, yMat):
    """
    函数说明:数据标准化
    Parameters:
        xMat - x数据集
        yMat - y数据集
    Returns:
        inxMat - 标准化后的x数据集
        inyMat - 标准化后的y数据集
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

def calcMean(x,y):
    sum_x = sum(x)
    sum_y = sum(y)
    n = len(x)
    x_mean = float(sum_x+0.0)/n
    y_mean = float(sum_y+0.0)/n
    return x_mean,y_mean

def calcPearson(x,y):
    x_mean,y_mean = calcMean(x,y)	#计算x,y向量平均值
    n = len(x)
    sumTop = 0.0
    sumBottom = 0.0
    x_pow = 0.0
    y_pow = 0.0
    for i in range(n):
        sumTop += (x[i]-x_mean)*(y[i]-y_mean)
    for i in range(n):
        x_pow += math.pow(x[i]-x_mean,2)
    for i in range(n):
        y_pow += math.pow(y[i]-y_mean,2)
    sumBottom = math.sqrt(x_pow*y_pow)
    p = sumTop/sumBottom
    return p


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

def correlateAnalysis(influencingFactor, AverageHousePrice, houseData):
    # for column in houseData:
        # p = calcPearson(houseData[column], houseData['MEDV'])
        # print(column, "和MEDV的相关系数为", p)
        # sns.jointplot(x=column, y='MEDV', data=houseData)
        # plt.show()
    # plt.rcParams['figure.figsize'] = (15, 10)
    # corrmatrix = houseData.corr()
    # sns.heatmap(corrmatrix, square=True, vmax=1, vmin=-1, center=0.0, cmap='rainbow')
    # plt.show()
    #删掉'CHAS','DIS','B'
    influencingFactor = houseData[['CRIM','INDUS','NOX', 'RM', 'AGE', 'RAD', 'TAX', 'PTRATIO', 'LSTAT']]
    influencingFactor = influencingFactor.values
    influencingFactor = influencingFactor.tolist()
    return influencingFactor, AverageHousePrice

def ProPressData(houseData):
    total = houseData.isnull().sum().sort_values(ascending=False)
    precent = (houseData.isnull().sum()/houseData.isnull().count()).sort_values(ascending=False)
    missing_data = pd.concat([total, precent], axis=1, keys=['Total', 'Precent'])
    print(missing_data)

def standRegres(xArr,yArr):
    """
    函数说明:计算回归系数w
    Parameters:
        xArr - x数据集
        yArr - y数据集
    Returns:
        ws - 回归系数
    """
    xMat = np.mat(xArr); yMat = np.mat(yArr).T
    xTx = xMat.T * xMat
    if np.linalg.det(xTx) == 0.0:
        print("矩阵为奇异矩阵,不能求逆")
        return
    ws = xTx.I * (xMat.T*yMat)
    return ws

def lwlr(testPoint, xArr, yArr, k = 1.0):
    """
    函数说明:使用局部加权线性回归计算回归系数w
    Parameters:
        testPoint - 测试样本点
        xArr - x数据集
        yArr - y数据集
        k - 高斯核的k,自定义参数
    Returns:
        ws - 回归系数
    """
    xMat = np.mat(xArr); yMat = np.mat(yArr).T
    m = np.shape(xMat)[0]
    weights = np.mat(np.eye((m)))                                        #创建权重对角矩阵
    for j in range(m):                                                  #遍历数据集计算每个样本的权重
        diffMat = testPoint - xMat[j, :]
        weights[j, j] = np.exp(diffMat * diffMat.T/(-2.0 * k**2))
    xTx = xMat.T * (weights * xMat)
    if np.linalg.det(xTx) == 0.0:
        print("矩阵为奇异矩阵,不能求逆Erroor")
        return
    ws = xTx.I * (xMat.T * (weights * yMat))                            #计算回归系数
    return testPoint * ws

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
    return unReg


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


def lwlrTest(testArr, xArr, yArr, k=1.0):
    """
    函数说明:局部加权线性回归测试
    Parameters:
        testArr - 测试数据集,测试集
        xArr - x数据集,训练集
        yArr - y数据集,训练集
        k - 高斯核的k,自定义参数
    Returns:
        ws - 回归系数
    Website:
https://www.cuijiahua.com/
    Modify:
        2017-11-19
    """
    m = np.shape(testArr)[0]                                            #计算测试数据集大小
    yHat = np.zeros(m)
    for i in range(m):                                                    #对每个样本点进行预测
        yHat[i] = lwlr(testArr[i],xArr,yArr,k)
    return yHat

def rssError(yArr, yHatArr):
    """
    误差大小评价函数
    Parameters:
        yArr - 真实数据
        yHatArr - 预测数据
    Returns:
        误差大小
    """
    return ((yArr - yHatArr) **2).sum()

def testAlgrim():
    filename = 'housing.txt'
    influencingFactor, AverageHousePrice, houseData = loadDataSet(filename)
    influencingFactor, AverageHousePrice = correlateAnalysis(influencingFactor, AverageHousePrice, houseData)
    # influencingFactor, AverageHousePrice = regularize(influencingFactor, AverageHousePrice)
    # ProPressData(houseData)
    # print('训练集与测试集相同:局部加权线性回归,核k的大小对预测的影响:')
    # yHat01 = lwlrTest(influencingFactor[0:250], influencingFactor[0:250], AverageHousePrice[0:250], 0.1)
    # yHat1 = lwlrTest(influencingFactor[0:251], influencingFactor[0:251], AverageHousePrice[0:251], 1)
    # yHat10 = lwlrTest(influencingFactor[0:251], influencingFactor[0:251], AverageHousePrice[0:251], 10)
    # print('k=0.1时,误差大小为:', rssError(AverageHousePrice[0:251], yHat01.T))
    # print('k=1  时,误差大小为:', rssError(AverageHousePrice[0:251], yHat1.T))
    # print('k=10 时,误差大小为:', rssError(AverageHousePrice[0:251], yHat10.T))
    # print('')
    # print('训练集与测试集不同:局部加权线性回归,核k的大小是越小越好吗？更换数据集,测试结果如下:')
    # yHat01 = lwlrTest(influencingFactor[252:504], influencingFactor[0:251], AverageHousePrice[0:251], 0.1)
    # yHat1 = lwlrTest(influencingFactor[252:504], influencingFactor[0:251], AverageHousePrice[0:251], 1)
    # yHat10 = lwlrTest(influencingFactor[252:504], influencingFactor[0:251], AverageHousePrice[0:251], 10)
    # print('k=0.1时,误差大小为:', rssError(AverageHousePrice[252:504], yHat01.T))
    # print('k=1  时,误差大小为:', rssError(AverageHousePrice[252:504], yHat1.T))
    # print('k=10 时,误差大小为:', rssError(AverageHousePrice[252:504], yHat10.T))
    # print('')
    # print('训练集与测试集不同:简单的线性归回与k=1时的局部加权线性回归对比:')
    # print('k=1时,误差大小为:', rssError(AverageHousePrice[252:504], yHat1.T))
    wMat = ridgeRegres(np.mat(influencingFactor[0:251]),np.mat(AverageHousePrice[0:251]).T)
    m = np.shape(influencingFactor[252:504])[0]
    yHat02 = np.zeros(m)
    for i in range(m):
        yHat02[i] = influencingFactor[252+i] *wMat
    print('不用交叉验证的岭回归误差大小：', rssError(AverageHousePrice[252:504], yHat02))
    unReg = crossValidation(influencingFactor[0:251], AverageHousePrice[0:251], numVal=10)
    unReg = np.array(unReg)
    unReg = unReg.reshape(9,1)
    unReg = np.mat(unReg)
    m = np.shape(influencingFactor[252:504])[0]  # 计算测试数据集大小
    yHat01 = np.zeros(m)
    for i in range(m):
        yHat01[i] = influencingFactor[252+i] * unReg
    print('经过交叉验证的岭回归误差大小：', rssError(AverageHousePrice[252:504], yHat01))
    ws = standRegres(influencingFactor[0:251], AverageHousePrice[0:251])
    m = np.shape(influencingFactor[252:504])[0]  # 计算测试数据集大小
    yHat = np.zeros(m)
    for i in range(m):  # 对每个样本点进行预测
        yHat[i] = influencingFactor[252+i] * ws
    print('简单的线性回归误差大小:', rssError(AverageHousePrice[252:504], yHat))




if __name__ == "__main__":
    testAlgrim()