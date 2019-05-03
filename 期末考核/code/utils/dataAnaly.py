import csv
import matplotlib.pyplot as plt
import warnings

warnings.filterwarnings('ignore')   #忽略警告
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

class PlotBoth(object):
    def __init__(self):
        self.user_movies, self.movie_users = self.GetData()

    def GetData(self):   #得到数据
        user_movies = dict()
        movie_users = dict()
        csv_file = csv.reader(open('D:/movies/ml-20m/ratings.csv','r'))
        for info in csv_file:
            user = info[0]
            movie = info[1]
            user_movies.setdefault(user, [])
            user_movies[user].append(movie)
            movie_users.setdefault(movie, [])
            movie_users[movie].append(user)
        return user_movies, movie_users

    def PlotItem_Users(self):
        """
        横坐标：物品流行度
        纵坐标：物品流行度为k的物品个数
        :param movie_users:
        :return:
        """
        k = dict()
        max_len = 0
        for movie in self.movie_users.keys():
            if max_len <= (len(self.movie_users[movie])):
                max_len = len(self.movie_users[movie])
            k.setdefault(len(self.movie_users[movie]), 0)
            k[len(self.movie_users[movie])] += 1

        y = []
        x = []
        t = range(max_len)
        for i in t:
            if i in k:
                y.append(k[i])
                x.append(i)
        plt.title(u'物品流行度分析')
        plt.xlim(xmin=0, xmax=1000)
        plt.ylim(ymin=0, ymax=1000)
        plt.scatter(x, y, s=10)
        plt.show()
        #冷门占了大多数
        #少数的电影有很大流行度

    def PlotUser_tems(self):
        """
        横坐标：用户活跃度
        纵坐标：用户活跃度为k的用户个数
        :param user_movies:
        :return:
        """
        k = dict()
        max_len = 0
        for user in self.user_movies.keys():
            if max_len < (len(self.user_movies[user])):
                max_len = len(self.user_movies[user])
            k.setdefault(len(self.user_movies[user]), 0)
            k[len(self.user_movies[user])] += 1

        y = []
        x = []
        t = range(1, max_len)
        for i in t:
            if i in k:
                y.append(k[i])
                x.append(i)
        plt.title(u'用户活跃度分析')
        plt.xlim(xmin=0, xmax=2000)
        plt.ylim(ymin=0, ymax=175)
        plt.scatter(x, y, s=10)
        plt.show()
        #表明用户活跃度低的用户占用了大多数
        #少量高活跃用户贡献了用户活跃度

    def main(self):
        self.PlotUser_tems()
        self.PlotItem_Users()


class clacCorr():
    def __init__(self):
        self.user_movies, self.item_weight = self.GetData()

    def GetData(self):
        user_movies = dict()
        movies_weight = dict()
        movie_N = dict()
        csv_file = csv.reader(open('D:/movies/ml-20m/ratings.csv','r'))
        for info in csv_file:
            user = info[0]
            movie = info[1]
            weight = info[2]
            user_movies.setdefault(user, [])
            user_movies[user].append([movie, weight])
            movies_weight.setdefault(movie, 0)
            movie_N.setdefault(movie, 0)
            movie_N[movie] += 1
            movies_weight[movie] +=1

        #for movie in user_movies.keys():
        #    movies_weight[movie] /= movie_N[movie]
        return user_movies, movies_weight

    def PlotItem(self):
        pu = dict()
        pi = dict()
        max_len = 0
        for user in self.user_movies.keys():
            if max_len < len(self.user_movies[user]):
                max_len = len(self.user_movies[user])
            pu.setdefault(len(self.user_movies[user]), 0)
            pu[len(self.user_movies[user])] += 1
            pi.setdefault(len(self.user_movies[user]), 0)
            for movies in self.user_movies[user]:
                movie = movies[0]
                pi[len(self.user_movies[user])] += self.item_weight[movie]

        for k in pi.keys():
            pi[k] /= pu[k] * k

        t = range(1, max_len)
        y = []
        x = []
        for i in t:
            if i in pu:
                y.append(pi[i])
                x.append(i)
        plt.scatter(x, y, label='user_movies', s=10)
        plt.title(u'用户活跃度与物品流行度的关系')
        plt.show()


b = clacCorr()
b.PlotItem()


