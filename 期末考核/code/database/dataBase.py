import pymysql.cursors
import pymysql
import pandas as pd

class MySQLCommand(object):
    def __init__(self, user='root', passwords = '550909'):
        self.config = {
            'host': "localhost",
            'user': user,
            'password': passwords,
            'db': 'movies',
            'charset': 'utf8mb4',
            'cursorclass': pymysql.cursors.DictCursor
        }
        try:
            self.db = pymysql.connect(**self.config)
            self.cursor = self.db.cursor()
        except:
            print("connect mysql error.")


    #插入数据，插入之前先查询是否存在，如果存在就不再插入
    def upDateUrl(self, movies_url):
        """
        函数说明：读入url数据库（主要目的：获得每个电影链接的url）
        :param movies_url:
        :return:
        """
        table = 'movie_url' #要操作的表
        try:
            sqlExit = "SELECT title FROM movie_url WHERE title = '%s'" % (movies_url[0])
            res = self.cursor.execute(sqlExit)
        except pymysql.Error as e:
            return 0
        if res == 1:
            print("数据已存在", res)
            return 0
        #数据不存在执行下面的操作
        try:
            sql = 'INSERT INTO movie_url(title, url) VALUES ( "{}", "{}");'.format(movies_url[0], movies_url[1])
            try:
                result = self.cursor.execute(sql)
                self.db.commit()
            except pymysql.Error as e:
                #回滚
                self.db.rollback()
                if "key 'PRIMARY'" in e.args[1]:
                    print("数据已经存在，未插入数据")
                else:
                    print("插入数据失败，原因 %d: %s" % (e.args[0], e.args[1]))
        except pymysql.Error as e:
            print("数据库错误，原因%d: %s" % (e.args[0], e.args[1]))

        # 插入数据，插入之前先查询是否存在，如果存在就不再插入
    def upDateData(self, movies_data):
        """
        函数说明：读入url用网站爬取下来的数据
        :param movies_data:
        :return:
        """
        table = 'movie_own'  # 要操作的表
        try:
             sqlExit = "SELECT title FROM movie_own WHERE title = '%s'" % (movies_data[0])
             res = self.cursor.execute(sqlExit)
        except pymysql.Error as e:
            return 0
        if res == 1:
            print("数据已存在", res)
            return 0
        # 数据不存在执行下面的操作
        try:
            sql = 'INSERT INTO movie_own(title, actor, time, type, score, introduce) VALUES ( "{}", "{}", "{}", "{}", "{}", "{}");'.format(movies_data[0], movies_data[1], movies_data[2], movies_data[3], movies_data[4], movies_data[5])
            try:
                result = self.cursor.execute(sql)
                self.db.commit()
            except pymysql.Error as e:
                # 回滚
                self.db.rollback()
                if "key 'PRIMARY'" in e.args[1]:
                    print("数据已经存在，未插入数据")
                else:
                    print("插入数据失败，原因 %d: %s" % (e.args[0], e.args[1]))
        except pymysql.Error as e:
            print("数据库错误，原因%d: %s" % (e.args[0], e.args[1]))

    def getLastId(self, table):
        try:
            sql = "SELECT id FROM" + table
            self.cursor.execute(sql)
            row = self.cursor.fetchall()
            if row[0]:
                return  row[0]  #返回最后一条数据id
            else:
                return 0   #如果表格为空则返回
        except pymysql.Error as e:
            print(sql + 'execute failed.')




    #输出数据
    def exportData(self, n=5):
        try:
            with self.db.cursor() as cursor:
                sql = "SELECT * FROM movie_url WHERE id < 9000"
                cursor.execute(sql)
                result = cursor.fetchall()
        except pymysql.Error as e:
            print("数据库错误")
        df = pd.DataFrame(result)
        return df


    def searchOwnData(self):
        try:
            self.cursor.execute('SELECT title, actor, label, score FORM movie_own;')
            self.db.commit()
            return self.cursor.fetchall()
        except:
            self.db.rollback()
            return None

    def dropOut(self):
        self.cursor.close()
        self.db.close()