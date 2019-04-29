import requests
import re
import threading
import sys


class Crawler:
    def __init__(self,db):
        self._config()
        self.errorCount = 0
        self.db =db

    # 配置函数
    def _config(self):
        # 关键词搜索部分
        self._serchUrl = (
        'https://c.y.qq.com/soso/fcgi-bin/client_music_search_songlist?format=json&p={}&remoteplace=txt.yqq.playlist&num_per_page=6&query={}',
        'https://c.y.qq.com/soso/fcgi-bin/client_search_cp?new_json=1&p={}&format=json&aggr=1&t={}&p=1&n=10&w={}')  # 参数：new_json:新的jspn、aggr：专辑、t：搜索方式、p：第几页、n：数量
        self._serchHeaders = {'referer': 'https://y.qq.com/portal/search.html'}
        self._serchName = ('song', 'album')
        # 歌单
        'https://c.y.qq.com/qzone/fcg-bin/fcg_ucc_getcdinfo_byids_cp.fcg?'
        # 打开部分
        self._openUrl = ('https://c.y.qq.com/v8/fcg-bin/fcg_v8_singer_track_cp.fcg?singermid={}&begin=0&num=10',
                         'https://c.y.qq.com/v8/fcg-bin/fcg_v8_album_info_cp.fcg?albummid={}')

        # 下载部分
        self._dUrl = 'https://u.y.qq.com/cgi-bin/musicu.fcg'
        self._dData = '''{"req":{"module":"CDN.SrfCdnDispatchServer","method":"GetCdnDispatch","param":{"guid":"8750934313","calltype":0,"userip":""}},"req_0":{"module":"vkey.GetVkeyServer","method":"CgiGetVkey","param":{"guid":"8750934313","songmid":["%s"],"songtype":[0],"uin":"0","loginflag":1,"platform":"20"}},"comm":{"uin":0,"format":"json","ct":24,"cv":0}}'''
        self._dParams = {'g_tk': '5381',
                         'loginUin': '0',
                         'hostUin': '0',
                         'format': 'json',
                         'inCharset': 'utf8',
                         'outCharset': 'utf-8',
                         'notice': '0',
                         'platform': 'yqq.json',
                         'needNewCode': '0',
                         }
        self._dHeaders = {'Accept-Encoding': 'identity;q=1, *;q=0', 'chrome-proxy': 'frfr', 'Range': 'bytes=0-',
                          'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3534.4 Safari/537.36'}
        self.nextPage = [-1,1]   #存放歌曲信息
        #实时显示正在下载部分
        self.downloadList = []  # 使用Queue太麻烦
        self.curDowner =None
        self.threadCourt = 0     #正在下载的数目
        self.lock =threading.Lock()


    # 获取mid等信息
    def getInfo(self, choicTuble=(0,(0, ''))):
        state,(choic, music) = choicTuble
        page = 1
        if state ==self.nextPage[0]:
            self.nextPage[1] +=1
            page =self.nextPage[1]
        self.nextPage[0] =state
        musicInfo = []
        # 歌单搜索
        if choic == 2:
            reqs = requests.get(self._serchUrl[0].format(page,music), headers=self._serchHeaders)  # 得到源码
            if reqs.status_code == 200:
                infoDict = reqs.json()
                if 'data' not in infoDict.keys(): return None
                songList = infoDict['data']['list']  # 歌单
                for i in songList:
                    tmpDict = {}
                    tmpDict['dissname'] = (i['dissname'], i['dissid'])  # 歌单名
                    tmpDict['listennum'] = (i['listennum'],'' )  # 听的人数
                    tmpDict['score'] = ( i['score'],'')  # 分数
                    musicInfo.append(tmpDict)
        # 专辑搜索
        elif choic == 1:
            reqs = requests.get(self._serchUrl[1].format(page,8, music))  # t=8,搜索专辑
            if reqs.status_code == 200:
                infoDict = reqs.json()
                musicList = infoDict['data']['album']['list']  # 存放每条歌曲的列表
                for i in musicList:
                    tmpDict = {}
                    tmpDict['album'] = (i['albumName'], i['albumMID'])
                    singers = i['singer_list'][0]
                    tmpDict['singers'] = (singers['name'], singers['mid'])
                    tmpDict['publicTime'] = (i['publicTime'], i['song_count'])
                    musicInfo.append(tmpDict)
        # 歌曲搜索
        else:
            reqs = requests.get(self._serchUrl[1].format(page,0, music))  # t=0,搜索歌曲
            if reqs.status_code == 200:
                infoDict = reqs.json()
                musicList = infoDict['data']['song']['list']  # 存放每条歌曲的列表
                for i in musicList:
                    if not i['action']['alert']: continue  # 歌曲有没有下架
                    tmpDict = {}
                    tmpDict['song'] = (i['title'], i['mid'],i['id'])  # 单曲
                    singers = i['singer'][0]
                    tmpDict['singers'] = (singers['name'], singers['mid'])
                    tmpDict['album'] = (i['album']['name'], i['album']['mid'])  # 专辑
                    musicInfo.append(tmpDict)
        return musicInfo
    def openInfo(self, choicTuble=((0, ''))):
        choic, mid = choicTuble
        if choic:
            rsp = requests.get(self._openUrl[choic].format(mid))  # 专辑
        else:
            rsp = requests.get(self._openUrl[choic].format(mid))    #
        musicInfo = []
        if rsp.status_code == 200:
            infoDict = rsp.json()
            if 'data' not in infoDict.keys(): return None
            musicList = infoDict['data']['list']  # 存放每条歌曲的列表
            for i in musicList:
                tmpDict = {}
                if not choic:
                    i = i['musicData']  # 歌单的信息
                tmpDict['song'] = (i['songname'], i['songmid'],i['songid'])
                singers = ''
                for j in i['singer']:
                    singers += j['name'] + ' '
                tmpDict['singers'] = (singers, i['singer'][0]['mid'])
                tmpDict['album'] = (i['albumname'], i['albummid'])
                musicInfo.append(tmpDict)
        return musicInfo

    def openSongList(self,id):
        url ='https://c.y.qq.com/qzone/fcg-bin/fcg_ucc_getcdinfo_byids_cp.fcg'
        headers ={'referer':'https://y.qq.com/n/yqq/playlist/4265836682.html',
                  'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3534.4 Safari/537.36'}
        params ={'type': '1',
                  'json': '1',
                  'utf8': '1',
                  'onlysong': '0',
                  'disstid': '4265836682',
                  'g_tk': '5381',
                  'loginUin': '0',
                  'hostUin': '0',
                  'format': 'json',
                  'inCharset': 'utf8',
                  'outCharset': 'utf-8',
                  'notice': '0',
                  'platform': 'yqq.json',
                  'needNewCode': '0'}
        #params['disstid'] =id
        rsp =requests.get(url,params=params,headers=headers)
        musicInfo = []
        if rsp.status_code == 200:
            infoDict = rsp.json()
            musicList = infoDict['cdlist'][0]['songlist']  # 存放每条歌曲的列表
            for i in musicList:
                tmpDict = {}
                tmpDict['song'] = (i['songname'], i['songmid'],i['songid'])
                singers = ''
                for j in i['singer']:
                    singers += j['name'] + ' '
                tmpDict['singers'] = (singers, i['singer'][0]['mid'])
                tmpDict['album'] = (i['albumname'], i['albummid'])
                musicInfo.append(tmpDict)
        return musicInfo




    # 生产者：从终端得到要下载的东西
    def tDownload(self, musics,status):
        '''
        :param musics:list或tuble
        :param status: 1：批量、0：单首
        :return:
        '''
        if status:
            self.downloadList.extend(musics)
            self.sendDList()
            while self.downloadList and self.threadCourt < len(self.downloadList):
                if self.threadCourt < 11:
                    _dThread(self)  # 开始多线程爬

        else:
            self.download(musics)
            self.sendDList(musics)

    # 消费者：用mid信息下载歌曲到本地
    def _getPurl(self, mId):
        '''获取歌曲位置url'''
        self._dParams['data'] = self._dData % mId
        rsp = requests.get(self._dUrl, params=self._dParams)
        if rsp.status_code == 200:
            rspDict = rsp.json()
            return rspDict['req_0']['data']['midurlinfo'][0]['purl']
    def download(self, songTuble):
        self.lock.acquire()     #在excute之前锁住
        id =self.db.upDate(songTuble[1])
        self.lock.release()
        if id :
            purl = self._getPurl(songTuble[0])
            rsp = requests.get('http://dl.stream.qqmusic.qq.com/' + purl, headers=self._dHeaders)
            if rsp.status_code == 206:
                with open(r'..\downFile\\' + re.sub(r'[\\/:*?"<>|]', '-', songTuble[2])+str(id) + '.mpa', 'wb') as f:
                    f.write(rsp.content)
                self.lock.acquire()
                self.db.upDateInfo(songTuble[2:])
                self.lock.release()
        else:
            print('已存在')

    def initCurDowner(self,curDown):
        self.curDowner =curDown

    #实时显示下载列表
    def sendDList(self,status =0):
        if self.curDowner:
            if status:
                self.curDowner([status])    #单首
            else:
                self.curDowner(self.downloadList,self.threadCourt)  #发送正在下载列表,正在下载的数目



class _dThread(threading.Thread):
    def __init__(self,crawler):
        super().__init__()
        self.crawler =crawler
        self.start()    #直接开始

    def run(self):
        while True:
            if not self.crawler.downloadList or self.crawler.threadCourt == len(self.crawler.downloadList):
                break
            song =self.crawler.downloadList[self.crawler.threadCourt]
            self.crawler.threadCourt += 1
            self.crawler.download(song)
            self.crawler.threadCourt -= 1
            self.crawler.downloadList.remove(song)
            self.crawler.sendDList()


def strToDict(strs):
    pattern=re.compile('([\w-].*?):\s*([\w{].*?)\n')
    header ={}
    for i in pattern.findall(strs):
        header[i[0]] =i[1]
    return header

def p():
    '''db.db.close()'''
    exit(0)



