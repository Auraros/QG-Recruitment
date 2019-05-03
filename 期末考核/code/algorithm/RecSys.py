import random
import math
import sys
import csv
import os
from operator import itemgetter
import numpy as np
import pandas as pd
from code.database.dataBase import MySQLCommand

# movie_own 的数据结构为：id， title， actor，time，type， score， introduce

random.seed(0)

class UserBasedCF(object):
    """
    TopN 推荐算法.基于用户的协调过滤UserF
    """
    def __init__(self):
        self.trainset = {}
        self.testset = {}

        self.n_sim_user = 20
        self.n_rec_movie = 15

        self.movie_sim_mat={}
        self.user_sim_mat = {}
        self.movie_popular = {}
        self.movie_count = 0

        print('相似的用户id = %d '% self.n_sim_user, file=sys.stderr)
        print('推荐的电影id = %d' % self.n_rec_movie, file=sys.stderr)


    def loadfile(self, filename):
        """
        下载文件，并且返回一个生成器
        :param filename:
        :return:
        """
        fp = csv.reader(open(filename, 'r'))
        next(fp)
        # fp = pd.read_csv(filename)
        # input()
        for i, line in enumerate(fp):
            yield line
            if i % 100000 == 0:
                print('下载 %s(%s)' %(filename, i), file=sys.stderr)
                if i == 1000000:
                    break
        # fp.close()
        print('下载 %s 成功 '% filename, file=sys.stderr)

    def generate_dataset(self, filename, pivot=0.7):
        """下载rating.csv和将其拆分为训练集和测试集"""
        trainset_len = 0
        testset_len = 0


        for line in self.loadfile(filename):
            user, movie, rating, _ = line
            # print(user, movie, rating)

            if random.random() < pivot:
                self.trainset.setdefault(user, {})
                self.trainset[user][movie] = int(float(rating))
                trainset_len += 1
            else:
                self.testset.setdefault(user, {})
                self.testset[user][movie] = int(float(rating))
                testset_len += 1

        print('分成的训练集和测试集：', file=sys.stderr)
        print('训练集 = %s' % trainset_len, file=sys.stderr)
        print('测试集 = %s' % testset_len, file=sys.stderr)

    def calc_user_sim(self):
        """UserCf计算使用用户的相似度矩阵"""
        #建立用户的反向表
        print('正在建造电影用户反向表', file=sys.stderr)
        movie2users = dict()
        #键为电影id， 值为哪个用户观看过的列表

        for user, movies in self.trainset.items():
            for movie in movies:
                #项目用户的反向表
                if movie not in movie2users:
                    movie2users[movie] = set()
                movie2users[movie].add(user)
                #同时统计项目流行度
                if movie not in self.movie_popular:
                    self.movie_popular[movie] = 0
                self.movie_popular[movie] += 1
        print("项目用户的反向表建立成功", file=sys.stderr)

        #保存总电影编号，该编号将用于评估
        self.movie_count = len(movie2users)
        print("所有的电影名称 = %d" % self.movie_count, file=sys.stderr)

        #计算用户之间的共同评分项目
        usersim_mat = self.user_sim_mat
        print("正在建立用户相似度矩阵...", file=sys.stderr)

        for movie, users in movie2users.items():
            for u in users:
                for v in users:
                    if u == v:
                        continue
                    usersim_mat.setdefault(u, {})
                    usersim_mat[u].setdefault(v, 0)
                    usersim_mat[u][v] += 1
        print("建立用户相似度矩阵成功")

        #计算相似度矩阵
        print('正在计算相似度矩阵...', file=sys.stderr)
        simfactor_count = 0
        PRINT_STEP = 2000000

        for u, related_users in usersim_mat.items():
            for v, count in related_users.items():
                usersim_mat[u][v] = count / math.sqrt(len(self.trainset[u])* len(self.trainset[v]))
            simfactor_count += 1
            if simfactor_count % PRINT_STEP == 0:
                print('计算用户相似性系数（%d）'% simfactor_count, file=sys.stderr)

        print('计算用户相似度矩阵成功', file=sys.stderr)
        print('总类同因子数 = %d' % simfactor_count, file=sys.stderr)

    def calc_user_sim2(self):
        """User-IIF计算使用用户的相似度矩阵"""
        #建立用户的反向表
        print('正在建造电影用户反向表', file=sys.stderr)
        movie2users = dict()
        #键为电影id， 值为哪个用户观看过的列表

        for user, movies in self.trainset.items():
            for movie in movies:
                #项目用户的反向表
                if movie not in movie2users:
                    movie2users[movie] = set()
                movie2users[movie].add(user)
                #同时统计项目流行度
                if movie not in self.movie_popular:
                    self.movie_popular[movie] = 0
                self.movie_popular[movie] += 1
        print("项目用户的反向表建立成功", file=sys.stderr)

        #保存总电影编号，该编号将用于评估
        self.movie_count = len(movie2users)
        print("所有的电影名称 = %d" % self.movie_count, file=sys.stderr)

        #计算用户之间的共同评分项目
        usersim_mat = self.user_sim_mat
        print("正在建立用户相似度矩阵...", file=sys.stderr)

        for movie, users in movie2users.items():
            for u in users:
                for v in users:
                    if u == v:
                        continue
                    usersim_mat.setdefault(u, {})
                    usersim_mat[u].setdefault(v, 0)
                    usersim_mat[u][v] += 1 / math.log(1 + len(users))
        print("建立用户相似度矩阵成功")

        #计算相似度矩阵
        print('正在计算相似度矩阵...', file=sys.stderr)
        simfactor_count = 0
        PRINT_STEP = 2000000

        for u, related_users in usersim_mat.items():
            for v, count in related_users.items():
                usersim_mat[u][v] = count / math.sqrt(len(self.trainset[u])* len(self.trainset[v]))
            simfactor_count += 1
            if simfactor_count % PRINT_STEP == 0:
                print('计算用户相似性系数（%d）'% simfactor_count, file=sys.stderr)

        print('计算用户相似度矩阵成功', file=sys.stderr)
        print('总类同因子数 = %d' % simfactor_count, file=sys.stderr)


    def recommend(self, user):
        """找到k个相似用户和推荐n个电影"""
        K = self.n_sim_user
        N = self.n_rec_movie
        rank = dict()
        watched_movies = self.trainset[user]

        for similar_user, similarity_factor in sorted(self.user_sim_mat[user].items(), key=itemgetter(1), reverse=True)[0:K]:
            for movie in self.trainset[similar_user]:
                if movie in watched_movies:
                    continue
                #预测用户对每部电影的“兴趣
                rank.setdefault(movie, 0)
                rank[movie] += similarity_factor
        #返回 n 个最好的电影
        return sorted(rank.items(), key=itemgetter(1), reverse=True)[0:N]

    def evaluate(self):
        #计算精准度、召回率、覆盖率和新颖度
        print('评估开始...')

        N = self.n_rec_movie
        #精确和召回变量
        hit = 0
        rec_count = 0
        test_count = 0
        #覆盖率
        all_rec_movies = set()
        #新颖度
        popular_sum = 0

        for i, user in enumerate(self.trainset):
            if i % 500 == 0:
                print('推荐给%d个用户' % i)
            test_movies = self.testset.get(user, {})
            rec_movies = self.recommend(user)
            for movie, _ in rec_movies:
                if movie in test_movies:
                    hit += 1
                all_rec_movies.add(movie)
                popular_sum += math.log(1 + self.movie_popular[movie])
            rec_count += N
            test_count += len(test_movies)

        precision = hit / (1.0 * rec_count)
        recall = hit / (1.0 * test_count)
        coverage = len(all_rec_movies) / (1.0 * self.movie_count)
        papularity = popular_sum / (1.0 * rec_count)

        print('精确度为=%.4f' % precision)
        print('召回率 = %.4f' % recall)
        print('覆盖率 = %.4f' % coverage)
        print('新颖率 = %.4f' % papularity)


class ItemBaseedCf(UserBasedCF):
    """TOPN 推荐 - 基于物品的协同过滤算法"""
    def __init__(self):
        UserBasedCF.__init__(self)
    #
    # def loadfile(self, filename):
    #     super().loadfile(filename)
    #
    # def generate_dataset(self, filename, pivot=0.7):
    #     super().generate_dataset(filename, pivot=0.7)

    def calc_movie_sim(self):
        """计算电影相似度矩阵"""
        print("计算电影数量和人气...")

        for user, movies in self.trainset.items():
            for movie in movies:
                #计算电影的欢迎程度
                if movie not in self.movie_popular:
                    self.movie_popular[movie] = 0
                self.movie_popular[movie] += 1

        print("统计电影数量和人气成功")
        #保存所有电影的number
        self.movie_count = len(self.movie_popular)
        print("全部电影 = %d" % self.movie_count)

        #统计项目之间的共同评价用户
        itemsim_mat = self.movie_sim_mat
        print("正在建立用户相似度矩阵...")

        for user, movies in self.trainset.items():
            for m1 in movies:
                for m2 in movies:
                    if m1 == m2:
                        continue
                    itemsim_mat.setdefault(m1, {})
                    itemsim_mat[m1].setdefault(m2, 0)
                    itemsim_mat[m1][m2] += 1

        print('建立用户相似度矩阵成功')

        #计算相似度矩阵
        print('正在计算相似度矩阵...')
        simfactor_count = 0
        PRINT_STEP = 2000000

        for m1, related_movies in itemsim_mat.items():
            for m2, count in related_movies.items():
                itemsim_mat[m1][m2] = count / math.sqrt(self.movie_popular[m1] * self.movie_popular[m2])
            simfactor_count += 1
            if simfactor_count % PRINT_STEP == 0:
                print('计算电影相似性系数（%d）' % simfactor_count)

        print('计算电影相似度矩阵成功')
        print('总类同因子数 = %d' % simfactor_count)

    def calc_movie_sim2(self):
        """计算电影相似度矩阵"""
        print("计算电影数量和人气...")

        for user, movies in self.trainset.items():
            for movie in movies:
                #计算电影的欢迎程度
                if movie not in self.movie_popular:
                    self.movie_popular[movie] = 0
                self.movie_popular[movie] += 1

        print("统计电影数量和人气成功")
        #保存所有电影的number
        self.movie_count = len(self.movie_popular)
        print("全部电影 = %d" % self.movie_count)

        #统计项目之间的共同评价用户
        itemsim_mat = self.movie_sim_mat
        print("正在建立用户相似度矩阵...")

        for user, movies in self.trainset.items():
            for m1 in movies:
                for m2 in movies:
                    if m1 == m2:
                        continue
                    itemsim_mat.setdefault(m1, {})
                    itemsim_mat[m1].setdefault(m2, 0)
                    itemsim_mat[m1][m2] += 1 / math.log(1 + len(movies) * 1.0)

        print('建立用户相似度矩阵成功')

        #计算相似度矩阵
        print('正在计算相似度矩阵...')
        simfactor_count = 0
        PRINT_STEP = 2000000

        for m1, related_movies in itemsim_mat.items():
            for m2, count in related_movies.items():
                itemsim_mat[m1][m2] = count / math.sqrt(self.movie_popular[m1] * self.movie_popular[m2])
            simfactor_count += 1
            if simfactor_count % PRINT_STEP == 0:
                print('计算电影相似性系数（%d）' % simfactor_count)

        print('计算电影相似度矩阵成功')
        print('总类同因子数 = %d' % simfactor_count)

    def recommend(self, user):
        """ 找k部类似的电影，推荐n部"""
        K = self.n_sim_user
        N = self.n_rec_movie
        rank = {}
        watch_movies = self.trainset[user]

        for movie, rating in watch_movies.items():
            for related_movie, similarity_factor in sorted(self.movie_sim_mat[movie].items(), key=itemgetter(1), reverse=True)[:K]:
                if related_movie in watch_movies:
                    continue
            #预测用户对每部电影的“兴趣”
            rank.setdefault(related_movie, 0)
            rank[related_movie] += similarity_factor * rating

        return sorted(rank.items(), key=itemgetter(1), reverse=True)[0:N]

    def evaluate(self):
        super().evaluate()



if __name__ == '__main__':
    ratingfile = 'ratings.csv'
    usercf = UserBasedCF()
    usercf.generate_dataset(ratingfile)
    usercf.calc_user_sim2()
    i = usercf.recommend()
    # itemcf = ItemBaseedCf()
    # itemcf.generate_dataset(ratingfile)
    # itemcf.calc_movie_sim()
    print('基于用户的协调过滤指标：')
    usercf.evaluate()
    # print('基于物品的协调过滤的指标：')
    # itemcf.evaluate()




