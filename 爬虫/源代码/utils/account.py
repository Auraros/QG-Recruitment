import pickle

class account:
    def __init__(self,dbCollector = None):
        self.__config()
        self.loadUser()  # 加载配置文件
        self.dbCllector =dbCollector

    def __config(self):
        self.file ='user.txt'
        self.dir ='../downFile'


    def create(self,user,password):
        '''新建用户'''
        dbName = self.dbCllector.newDb(self.user['num'])
        if dbName:
            self.user['curUser'] =user
            self.user[user] = (password,dbName) #获得数据库名
            self.user['num'] += 1
            self.dumpUser() #写入文件
            return True
        else:
            return False


    def change(self,user,password):
        '''切换用户'''
        if user  in self.user.keys():
            if self.user[user][0] == password:
                self.dbCllector.change(self.user[user][1])
                return True
        return False

    def getPassw(self,user):
        '''忘记密码'''
        if user in self.user.keys():
            return self.user[user][0]
        else:
            return None

    def loadUser(self):
        '''配置文件中获得list'''
        try:
            with open(self.file,'rb') as f:
                self.user=pickle.load(f)
        except:
            with open(self.file,'wb') as f:
                self.user = {'curUser': None,'num':0}
                pickle.dump(self.user,f)

    def dumpUser(self):
        '''存入配置文件'''
        with open(self.file, 'wb') as f:
            pickle.dump(self.user,f)



