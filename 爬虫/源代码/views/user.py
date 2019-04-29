import tkinter as tk
from tkinter import ttk
import os.path
import re
import sys
sys.path.append('../utils')
sys.path.append('../db_tools')
import dbcollector
import crawlerutils
import account

#功能基类
class basefFrame:
    def __init__(self, root):
        '''初始化'''
        self.fFrame = tk.Frame(root, width=760, height=600, bg='#DCDCDC')
        self.fFrame.place(x=200, y=0)
        self.fFrame.bind("<Double-1>",self.callback)   #调试用：输出鼠标位置
        self.__iFrame()
        self.__sFrame()
        self.chooseList = []  # 批量下载用
    def callback(self,event):
        print("当前位置：", event.x, event.y)

    # 保护类型:可继承,实例不可调用(封装：类内部可以用，外部不可以 ->用户理解)
    def _kFrame(self):
        pass

    def _oFrame(self):
        '''选项的按钮和标签'''
        pass

    # 私有类型：不可继承,实例不可调用(封装：类内部可以用，外部不可以 ->用户理解)
    def __iFrame(self):
        '''显示信息的列表'''
        self.iFrame = tk.Frame(self.fFrame, width=760, height=420, bg='#DCDCDC')  # infoframe
        self.iFrame.place(x=0, y=110)
        # 显示搜索歌曲信息的列表
        self.strVarList = [[], [], []]  # 存放音乐信息
        y, ypad = 40, 35  # y位置、y间隔
        self.cLabelList = []  # 存放背景标签
        self.bgcolor = ('#FFFFFF', '#F5F5F5')  # '#DCDCDC'FFFFFF
        x = 80  # x位置
        tk.Label(self.iFrame, width=60, font=('', 21), bg=self.bgcolor[0]).place(x=0, y=y - 5)
        for index, lst in enumerate(self.strVarList):
            strVar = tk.StringVar(self.iFrame)
            lst.append(strVar)
            tk.Label(self.iFrame, textvariable=strVar, font=('', 12), fg='#8A2BE2', bg=self.bgcolor[0]).place(x=x, y=40)
            x += 220
        for i in range(1, 11):
            y += ypad
            x = 80  # x位置
            tk.Label(self.iFrame, width=60, font=('', 21), bg=self.bgcolor[i % 2]).place(x=0, y=y - 5)  # 背景色，为好看
            cLabel = tk.Label(self.iFrame, font=('', 12), bg=self.bgcolor[i % 2], width=2)  # 选择的时候变色
            cLabel.place(x=35, y=y)
            self.cLabelList.append(cLabel)
            for index, lst in enumerate(self.strVarList):
                strVar = tk.StringVar(self.iFrame)
                lst.append(strVar)
                musicInfoLabel = tk.Label(self.iFrame, textvariable=strVar, font=('', 12), fg='#8A2BE2',
                                          bg=self.bgcolor[i % 2])
                musicInfoLabel.id = (index, i)
                self.__Bind(musicInfoLabel)  # 可以变色
                # musicInfoLabel.configure(bg=bgChoic[(i)%2])
                musicInfoLabel.place(x=x, y=y)
                x += 220

    def __sFrame(self):
        '''搜索框和搜索按钮'''
        # 搜索框
        self.sVal = tk.StringVar()  # 存放搜索的内容
        searchCloumn = ttk.Entry(self.fFrame, width=60, textvariable=self.sVal)
        searchCloumn.place(x=120, y=75, anchor='nw')
        searchCloumn.focus()  # 光标
        # 搜索按钮
        ttk.Button(self.fFrame, text='搜索', width=4, command=self._sFunc).place(x=550, y=75)

    def _sFunc(self, event=0):
        pass

    def _showInfo(self, musicInfo):
        pass

    def _bbFunc(self, event):
        '''批量完成的任务:batchFunc'''
        pass

    def __Bind(self, label):
        '''鼠标移进去组建内部'''
        label.bind('<Motion>', self.__baColor)
        label.bind('<Leave>', self.__bcColor)
        label.bind("<Button-1>", self.__bchoose)
        label.bind("<Button-3>", self.__bcancel)
        label.bind("<Double-1>", self._bbFunc)   #双击下载或打开

    def __baColor(self, event):
        '''alterColor改变组件背景色'''
        event.widget.configure(bg='#DCDCDC')

    def __bcColor(self, event):
        '''cancerColor取消组件背景色'''
        i, j = event.widget.id
        event.widget.configure(bg=self.bgcolor[(j) % 2])

    def __bchoose(self, event):
        i, j = event.widget.id
        self.cLabelList[j - 1].configure(bg='#FFFF00')
        self.chooseList.append(self.strVarList[0][j].id)

    def __bcancel(self, event):
        i, j = event.widget.id
        self.cLabelList[j - 1].configure(bg=self.bgcolor[j % 2])
        if self.chooseList:
            self.chooseList.pop()

#搜索的类
class searchFrame(basefFrame):
    def __init__(self,root,crawler =None):
        super().__init__(root)
        self._oFrame()
        self._kFrame()
        self.crawler = crawler
        self.pageStatus =0


    def _bbFunc(self, event):
        try:
            if not event.widget.id:return
            i,j =event.widget.id
            self.cLabelList[j - 1].configure(bg=self.bgcolor[j % 2])
            if i:
                musicInfo=self.crawler.openInfo(self.strVarList[i][j].id)   #(索引,mid)
                if musicInfo:
                    self._showInfo(musicInfo)
            else:
                songTuble =self.strVarList[i][j].id
                if len(songTuble)>2:
                    self.crawler.tDownload(songTuble,0) #下载歌曲
                else:
                    musicInfo=self.crawler.openSongList(songTuble[1])
                    if musicInfo:
                        self._showInfo(musicInfo)
        except:
            pass#self.crawler.openInfo(event)

    def _oFrame(self):
        ttk.Button(self.fFrame,text='下一页',command=self.nextPage).place(x=450,y=550)   #下一页按钮
        ttk.Button(self.fFrame, text='下载', command=self.tDownload).place(x=550, y=550)    #下载按钮

    def _sFunc(self, event=0):
        if event != 0 and event !=-1:  # 为搜索Button设计的
            event = event.widget.id  # 0:单曲；1.专辑；2。歌单
        musicInfo = self.crawler.getInfo((event, (event, self.sVal.get())))
        if musicInfo:
            if event == 2:  # 歌单
                self._showInfo(musicInfo)
            else:  # 单曲、专辑
                self._showInfo(musicInfo)

    def _showInfo(self, musicInfo):
        col = list(musicInfo[0].keys())
        for i in range(3):
            self.strVarList[i][0].set(col[i])
        for i, info in enumerate(musicInfo):
            i += 1
            for index, key in enumerate(col):
                self.strVarList[index][i].set(info[key][0])
                if key == 'song':
                    self.strVarList[index][i].id = ( info[key][1], info[key][2],info[key][0], info['singers'][0],info['album'][0])
                else:
                    self.strVarList[index][i].id = (index - 1, info[key][1])
        if len(musicInfo)<10:
            info =''
            for i in range(len(musicInfo),11):
                for index, key in enumerate(col):
                    self.strVarList[index][i].set(info)
                    if key == 'song':
                        self.strVarList[index][i].id = info
                    else:
                        self.strVarList[index][i].id = info

    def _kFrame(self):
        self._kFrame = tk.Frame(self.fFrame, width=760, height=30)
        self._kFrame.place(x=0, y=105)
        text = ('单曲', '专辑', '歌单')
        x = 80
        for j, i in enumerate(text):
            l = tk.Label(self._kFrame, text=i, font=('', 12))
            l.id = j
            l.bind("<Button-1>", self._sFunc)
            l.place(x=x, y=5)
            x += 100

    def tDownload(self):
        self.crawler.tDownload(self.chooseList,1)
        for j,i in enumerate(self.cLabelList):  #选择标签变回原来的颜色
            i.configure(bg=self.bgcolor[(1+j) % 2])
        del self.chooseList
        self.chooseList = []

    def nextPage(self):     #很笨的函数
        self._sFunc(-1)

class dManageFrame(basefFrame):
    def __init__(self,root,dbcollector =None):
        super().__init__(root)
        self._kFrame()
        self.dbcollector =dbcollector
        self.curNum = None

    def _kFrame(self):
        self._kFrame = tk.Frame(self.fFrame, width=760, height=30)
        self._kFrame.place(x=0, y=105)
        text = ('正在下载', '歌单', '歌曲')
        x = 80
        for j, i in enumerate(text):
            l = tk.Label(self._kFrame, text=i, font=('', 12))
            l.id = j
            l.bind("<Button-1>", self._sFunc)
            l.place(x=x, y=5)
            x += 100

    def _sFunc(self, event=0):
        if event:
            if event.widget.id ==1:
                info =self.dbcollector.qureyInfo()
                if info:
                    self._showInfo(info)

    def _showInfo(self, musicInfo):
        if not musicInfo:return
        status =len(musicInfo[0]) < 3
        for i, info in enumerate(musicInfo):
            i += 1
            if i > 10: break
            for index, key in enumerate(info if status else info[2:]):
                self.strVarList[index][i].set(key)
                self.strVarList[index][i].id =index - 1
        if len(musicInfo)<10:
            info =''
            for i in range(len(musicInfo),11):
                for index in range(3):
                    self.strVarList[index][i].set(info)


    def haveDownload(self):
        '''跟缓存交互使用pickle'''
        pass

    def curDownload(self,musicInfo,curDNum =1):
        '''直接跟爬虫交互'''
        self._showInfo(musicInfo)
        if self.curNum:
            self.curNum(len(musicInfo))

    def initCurNum(self,curNum):
        '''显示下载数目'''
        self.curNum =curNum

class lManageFrame(basefFrame):
    def __init__(self,root):
        super().__init__(root)
        self.dir =['..\downFile']
        self.getList()

    def addPath(self,path):
        '''增加文件夹'''
        self.dir.append(path)

    def getList(self):
        '''获取文件列表'''
        names = [name for name in os.listdir(self.dir[0])
                 if os.path.isfile(os.path.join(self.dir[0], name))]
        self._showInfo(names)

    def _showInfo(self, musicInfo):
        for i, info in enumerate(musicInfo):
            i += 1
            if i > 9: break
            self.strVarList[0][i].set(info)
            self.strVarList[0][i].id =-1
        if len(musicInfo)<10:
            info =''
            for i in range(len(musicInfo),11):
                for index in range(3):
                    self.strVarList[index][i].set(info)



class accountM:
    def __init__(self,root,account):
        self.fFrame = tk.Frame(root, width=760, height=600, bg='#DCDCDC')
        self.fFrame.place(x=200, y=0)
        self.iFrame()
        self.account =account

    def iFrame(self):
        self.varList =[]
        x,y =200,200
        #两个文本框
        for i in range(2):
            y += 40
            strVal =tk.StringVar(self.fFrame)
            self.varList.append(strVal)
            tk.Entry(self.fFrame,width=40, textvariable=strVal).place(x=x,y=y)
        #三个按钮
        ttk.Button(self.fFrame, text='忘记密码',width =8, command=self.getPassw).place(x=500, y=y)
        y+=40
        x += 100
        ttk.Button(self.fFrame, text='注册',width =8, command=self.register).place(x=x, y=y)
        x += 100
        ttk.Button(self.fFrame, text='登陆',width =8, command=self.change).place(x=x, y=y)
        #一个标签
        self.curUser =tk.StringVar(self.fFrame,'root')
        tk.Label(self.fFrame, textvariable = self.curUser, font = ('', 12), bg ='#DCDCDC').place(x =250,y=180)


    def getPassw(self):
        '''忘记密码'''
        user = self.varList[0].get()
        if not user or self.isbadStr(user):
            self.varList[0].set('请输入用户名')
            return
        passw =self.account.getPassw(user)
        if passw:
            self.varList[1].set(passw)
        else:
            self.varList[1].set('用户不存在')
    def register(self):
        '''注册'''
        user =self.varList[0].get()
        passw =self.varList[1].get()
        if not user or self.isbadStr(user):
            self.varList[0].set('请输入用户名')
            return
        if not passw or self.isbadStr(passw):
            self.varList[1].set("请输入密码")
            return
        if self.account.create(user,passw):
            self.varList[1].set("注册成功")
        else:
            self.varList[1].set("注册失败")
    def change(self):
        '''切换'''
        user = self.varList[0].get()
        passw =self.varList[1].get()
        if not user or self.isbadStr(user):
            self.varList[0].set('请输入用户名')
            return
        if not passw or self.isbadStr(passw):
            self.varList[1].set("请输入密码")
            return
        if self.account.change(user,passw):
            self.varList[1].set("登陆成功")
            self.curUser.set(user)
        else:
            self.varList[1].set("登陆失败")

    def isbadStr(self,strs):
        '''输入的用户、密码十分合法'''
        pattern =re.compile('[^A-Za-z0-9_.]')
        if pattern.search(strs):
            return True
        return False
class Menu(tk.Tk):
    def __init__(self,user ='root',passw='123456'):
        super().__init__()
        self.geometry('960x600+200+100')  # 设置窗口大小和相对屏幕位置
        # self.resizable(0, 0)  # 阻止Python GUI的大小调整
        self.protocol("WM_DELETE_WINDOW", crawlerutils.p)  # 关闭时触发时触发函数
        self.title("qq音乐爬虫")
        self.initFFrame(user,passw)
        self.mainloop()

    def initFFrame(self,user,passw):
        # 初始化各个Frame
        db =dbcollector.mySqlDb(user,passw)
        crawler =crawlerutils.Crawler(db)
        search = searchFrame(self,crawler )      #搜索类
        label = tk.Label(self, text='搜索', font=('', 12), bg='#F5F5F5')
        label.frame =search
        label.bind('<Motion>', self.baColor)
        label.bind('<Leave>', self.bcColor)
        label.bind('<Button-1>', self.bCFrame)
        x = 60
        y=100
        label.place(x=x, y=y)
        #dManager
        dManager =dManageFrame(self,db)
        dManager.initCurNum(self.curNum)
        self.dNum =tk.StringVar(self,value='下载管理')
        y += 50
        crawler.initCurDowner(dManager.curDownload)    #初始化正在下载
        label = tk.Label(self, textvariable=self.dNum, font=('', 12), bg='#F5F5F5')
        label.frame = dManager
        self.bFunc(label)
        label.place(x=x, y=y)

        #本地管理
        lManager = lManageFrame(self)
        y += 50
        label = tk.Label(self, text='本地管理', font=('', 12), bg='#F5F5F5')
        label.frame = lManager
        self.bFunc(label)
        label.place(x=x, y=y)

        #用户管理
        uManager= accountM(self,account.account(db))
        y += 50
        label = tk.Label(self, text='用户管理', font=('', 12), bg='#F5F5F5')
        label.frame = uManager
        self.bFunc(label)
        label.place(x=x, y=y)

    def bCFrame(self,event):
        event.widget.frame.fFrame.tkraise()

    def bFunc(self,label):
        '''绑定鼠标飘过变色的函数'''
        label.bind('<Motion>', self.baColor)
        label.bind('<Leave>', self.bcColor)
        label.bind('<Button-1>', self.bCFrame)

    def baColor(self, event):
        '''alterColor改变组件背景色'''
        event.widget.configure(bg='#DCDCDC')

    def bcColor(self, event):
        '''cancerColor取消组件背景色'''
        event.widget.configure(bg='#F5F5F5')

    def curNum(self,num):
        if num:
            self.dNum.set("下载数:"+str(num))
        else:
            self.dNum.set("下载管理")



if __name__ == '__main__':
    inst =Menu()



