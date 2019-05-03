# -*-coding:utf-8 -*-
import re
import time
import pandas as pd
import pickle
import random
import requests
from bs4 import BeautifulSoup
import urllib.request
import json
from fake_useragent import UserAgent
from code.database.dataBase import MySQLCommand

#从ip网站爬取ip
class clawIP(object):
    def __init__(self):
        self._headUrl()

    def _headUrl(self):
        ua = UserAgent(use_cache_server=False)
        self.header = {'User-Agent': ua.random}

    # 向一个url发起请求,成功返回文本,不成功继续发起请求
    def get_one_page(self, url):
        print("发起请求")
        response = requests.get(url, headers=self.header)
        response.encoding = "utf-8"
        if response.status_code == 200:
            # print(response.text)
            print("响应成功")
            return response.text
        else:
            print("响应失败")
            # 如果一直响应失败会超出递归最大层数,导致程序崩溃.
            return self.get_one_page(url)

    # 使用正则格式化处理文本
    def extract_page(self, text):
        str1 = '<td class="country"><img[\s\S]+?<td>'
        # ip
        str2 = '</td>[\s\S]*?<td>'
        # 端口号
        str3 = '</td>[\s\S]*?<td>[\s\S]*?<td>'
        # 协议类型
        str4 = '</td>'
        IP_List = re.findall(str1 + "([\s\S]*?)" + str2 + "([\s\S]*?)" + str3 + "([\s\S]*?)" + str4, text)
        return IP_List

    # 获取可用的IP_list
    def ip_pool(self, IP_list):
        for i in IP_list:
            # 如果IP不可用,从IP_list中删除
            if not self.test_ip(i[0], i[1]):
                print(i, "不可用")
                IP_list.remove(i)
        # 返回筛选后的IP_list
        return IP_list

    # 对每一个IP进行测试
    def test_ip(self, ip, port):
        server = ip + ":" + port
        proxies = {'http': 'http://' + server, 'https': 'https://' + server}
        try:
            r = requests.get('https://www.baidu.com/', proxies=proxies, timeout=1)
            if r.status_code == 200:
                return 1
            else:
                return 0
        except:
            return 0

    def ipMain(self):
        IP_text = self.get_one_page("http://www.xicidaili.com/")
        IP_list = self.extract_page(IP_text)
        self.IP_pool = self.ip_pool(IP_list)
        f = open("test.txt", 'wt')
        for i in range(len(self.IP_pool)):
            b = str(self.IP_pool[i][0]) +" " + str(self.IP_pool[i][1]) + "\n"
            f.write(b)
        f.close()
        return self.IP_pool



class clawer():
    def __init__(self, MySQLCommand):
        self._store()
        self.mySql = MySQLCommand()
        self.clawIP = clawIP()

    def _store(self):
        #直接搜索全部电影
        self.allUrl = "https://movie.douban.com/j/new_search_subjects?sort=U&range=0,10&tags=&start={}"
        # self.header = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.110 Safari/537.36'}
        ua = UserAgent(use_cache_server=False)
        self.header = {'User-Agent': ua.random}
        return self.header

    def get_random_ip(self, ip_list):
        self.proxy_list = []
        for ip in ip_list:
            self.proxy_list.append('http://' + ip)
        self.proxy_ip = random.choice(self.proxy_list)
        self.proxies = {'http': self.proxy_ip}
        return self.proxies


    #检测ip可用性，移除不可用ip：（这里其实总会出问题，你移除的ip可能只是暂时不能用，剩下的ip使用一次后可能之后也未必能用）
    def get_ip_list(self):
        # web_data = requests.get(self.IpUrl, self.header)
        # soup = BeautifulSoup(web_data.text, 'lxml')
        # print(soup)
        # ips = soup.find_all('tr')
        # print(ips)
        # input()
        # self.ip_list = []
        # for i in range(1, len(ips)):
        #     ip_info = ips[i]
        #     tds = ip_info.find_all('td')
        #     self.ip_list.append(tds[1].text + ':' + tds[2].text)
        # 检测ip可用性，移除不可用ip：（这里其实总会出问题，你移除的ip可能只是暂时不能用，剩下的ip使用一次后可能之后也未必能用）
        for ip in self.ip_list:
            try:
                proxy_host = "https://" + ip
                proxy_temp = {"https": proxy_host}
                res = urllib.urlopen(self.IpUrl, proxies=proxy_temp).read()
            except Exception as e:
                self.ip_list.remove(ip)
                continue
        return self.ip_list

    def UpdateIp(self):
        self.clawIP.ipMain()


    def chooseIp(self):
        f = pd.read_csv("test.txt", sep=' ')
        f.columns = ['number', 'part']
        a = random.randint(0, len(f)-1)
        proxies = {f['number'][a]:f['part'][a]}
        print(proxies)
        return proxies





    def getUrl(self):
        for j in range(0,10000,20):   #分成二十个二十个电影的得到
            self.url = self.allUrl.format(j)
            self.wb_data = requests.get(self.url, headers=self.header)
            self.wb_data = json.loads(self.wb_data.text)['data']  #得到包含url等信息的json格式数据
            if self.wb_data == []:
                break
            for i in range(20):
                movies_url = []
                title = re.sub('"', "'", self.wb_data[i]['title'])
                movie_url = self.wb_data[i]['url']
                movies_url.append(title); movies_url.append(movie_url)
                print(movies_url)
                self.mySql.upDateUrl(movies_url)


    def getDetail(self):
        self.df = self.mySql.exportData()
        m = len(self.df)
        i = 5650
        flag = 0
        # ipNumbers = self.UpdateIp()
        while(i< m):
            try:
                proxies = self.chooseIp()
                self.detailUrl = self.df['url'][i]
                print(self.detailUrl, i)
                time.sleep(random.random()*3)
                header = self._store()
                # ip_list = self.get_ip_list()
                # proxies = self.get_random_ip(ip_list)
                self.detail_data = requests.get(self.detailUrl, headers=header, proxies=proxies, verify=False)  #防止证书
                requests.packages.urllib3.disable_warnings()
                soup = BeautifulSoup(self.detail_data.text, 'lxml')
                # self.detail_data = soup.find_all('script', type="application/ld+json")
                # self.detail_data = json.loads(soup.find_all('script', type="application/ld+json")[0].text)
                self.detail_data = json.loads(soup.findAll(name='script', attrs={'type':"application/ld+json"})[0].string, strict=False)
                # self.detail_data = json.loads(self.detail_data)

                # time = soup.findAll(name='span', attrs={'property': "v:runtime"})[0].string
                try:
                    actor = self.detail_data['actor'][0]['name']
                except IndexError:
                    actor = None
                title = self.detail_data['name']
                year = self.detail_data['datePublished']
                # introduce = self.detail_data['description']
                labels = self.detail_data['genre']
                score = self.detail_data['aggregateRating']['ratingValue']
                # detail_introduce = soup.find(style="margin-bottom:-10px;")
                # detail_introduce = soup.find_all(class_="all hidden")[0].string

                #因为要得到详细的影片介绍，中间很多错误报警，所以下面的代码用来调试错误
                try:
                    for a in  soup.findAll(name='span', attrs={'class':"all hidden"})[0].children:     #因为部分电影的简介太多了，很多都保存在all hidden的标签里面，因为有些数据里面会有<br/>
                        try:          #除去前后的空格
                            introduce = a.strip()
                        except TypeError as e:   #因为数据被分成了一个单标签分成了两个比分，一个部分为空，不需要，则遇到空的时候，跳出循环
                            break
                except IndexError as e:  #有些电影简介比较短，所以可能不会有all hidden ， 所以要另外找一个标签
                    try:
                        introduce =  soup.findAll(name='span', attrs={'property': "v:summary"})[0].string.strip()   #如果没有<br/>只需要直接读取
                    except AttributeError as e:
                        for b in soup.findAll(name='span', attrs={'property': "v:summary"})[0].children:  #如果有<br/>需要自己读取子标签
                            try:
                                introduce = b.strip()
                            except TypeError as e:  #跟上面一样错误处理
                                break
            # detail_introduce = soup.findAll(name='span', attrs={'class':"all hidden"})[0].string
                list = [title, actor, year, labels, score, introduce]
                self.mySql.upDateData(list)
            except IndexError as e:
                if flag == 5:
                    i += 1
                    flag = 0
                else:
                    flag +=1
                continue
            except IOError as e:
                i += 1
                continue
            except requests.exceptions.ConnectionError:
                requests.adapters.DEFAULT_RETRIES = 5
            else:
                pass
            i += 1


b = clawer(MySQLCommand)
b.getDetail()


