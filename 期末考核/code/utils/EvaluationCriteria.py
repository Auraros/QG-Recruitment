import math
from operator import itemgetter

def RMSE(records):
    """
    函数说明：均方根误差（RMSE），records[i] = [u,i,rui,pui]，其
    中rui是用户u对物品i的实际评分，pui是算法预测出来的用户u对物品i的评分
    :param records:评分数据列表
    :return:
    """
    return math.sqrt(sum([(rui - pui)*(rui - pui) for u,i,rui,pui in records])/float(len(records)))

def MAE(records):
    """
    函数说明：平均绝对误差（MAE）,跟上面一样
    :param records:
    :return:
    """
    return sum([abs(rui - pui) for u,i,rui,pui in records])/float(len(records))

def PrecisionRecall(test, N):
    """
    TopN推荐,TopN推荐的预测准确率一般通过准确率（precision）/召回率（recall）度量。
    :param test:
    :param N:
    :return:
    """
    hit = 0
    n_recall = 0
    n_precision = 0
    for user, items in test.items():
        rank = Recomend(user, N)
        hit += len(rank & items)
        n_recall += len(items)
        n_precision += N
    return [hit / (1.0 * n_recall), hit / (1.0 * n_precision)]

def GiniIndex(p):
    """
    基尼系数（Gini Index）：，ij是按照物品流行度p()从小到大排序的物品列表中第j个物品。
    :param p:
    :return:
    """
    j = 1
    n = len(p)
    G = 0
    for item, weight in sorted(p.items(), key=itemgetter(1)):
        G += (2 * j - n - 1) * weight
    return G / float(n - 1)


