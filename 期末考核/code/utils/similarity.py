import math
import sys

class simil(object):

    def claCosineSimilarity(self, list1, list2):
        """
        函数说明：余弦相似度
        :param list1:
        :param list2:
        :return:
        """
        res = 0
        denominator1 = 0
        denominator2 = 0
        for (val1, val2) in zip(list1, list2):
            res += (val1 * val2)
            denominator1 += val1 ** 2
            denominator2 += val2 ** 2
            return res / (math.sqrt(denominator1 * denominator2))


