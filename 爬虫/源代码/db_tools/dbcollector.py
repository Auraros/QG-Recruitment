import pymysql

class mySqlDb:
    def __init__(self,user,password):
        self.db =pymysql.connect(host='localhost',user=user,password=password,port=3306)
        self.handle =self.db.cursor()
        self.__config()

    def __config(self):
        '''配置文件'''
        self.dbName ='my_music_'
        self.cSql ='use {};'
        try:
            self.handle.execute('use my_music_;')
        except:
            self.newDb('')

    def upDate(self,mid):
        sql = 'SELECT * FROM mid WHERE mid = %s;'%mid
        self.handle.execute(sql)
        record =self.handle.fetchone()
        if record:
            return None
        else:
            try:
                self.handle.execute('INSERT INTO mid (mid) VALUES (%s) ;'%mid)
                self.handle.execute('SELECT COUNT(*) FROM mid;')
                num =self.handle.fetchone()[0]
                self.db.commit()
            except:
                self.db.rollback()
                return None
            return num

    def upDateInfo(self,info):
        try:
            self.handle.execute('INSERT INTO music_info(song,singer,album) VALUES("{}","{}","{}");'.format(info[0],info[1],info[2]))
            self.db.commit()
            return info
        except:
            self.db.rollback()
            return None

    def qureyInfo(self):
        try:
            self.handle.execute('SELECT song,singer,album FROM music_info ;')
            self.db.commit()
            return self.handle.fetchall()
        except:
            self.db.rollback()
            return None

    def newDb(self,num):
        try:
            name =self.dbName+str(num)
            sql ='CREATE DATABASE {};'.format(name)
            self.handle.execute(sql)
            self.handle.execute(self.cSql.format(name)) #更换数据库
            sql ='''CREATE TABLE mid (
            mid int(10),
            id int auto_increment  PRIMARY KEY
            );'''
            self.handle.execute(sql)
            sql ='''CREATE TABLE music_info (
                        id int auto_increment  PRIMARY KEY,
                        song varchar(255),
                        singer varchar(255),
                        album varchar(255)
                        );'''
            self.handle.execute(sql)
            self.db.commit()
            return name
        except Exception as e:
            self.db.rollback()
            print(e)
            return None

    def change(self,name):
        try:
            sql = self.cSql.format(name)
            self.handle.execute(sql)
            self.db.commit()
            return True
        except:
            self.db.rollback()
            return False

    def delteDb(self,num):
        try:
            name =self.dbName+str(num)
            sql ='drop database {}'.format(name)
            self.handle.execute(sql)
            self.db.commit()

        except Exception as e:
            self.db.rollback()
            print(e)
if __name__ =='__main__':
    db =mySqlDb()



