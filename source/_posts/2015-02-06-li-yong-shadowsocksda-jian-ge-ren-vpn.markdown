---
layout: post
title: "利用shadowsocks搭建个人VPN"
date: 2015-02-07 00:23:56 +0800
comments: true
description: "shadowsocks vpn"
keywords: shadowsocks, vpn, fanqiang 

categories: 
- other
---

之前一直在用123ssh的vpn, 最近发现他们的服务器不太稳定, Linux下还能连上服务器, windows下直接连接不上.

今天在RamNode上买了一个VPS, 利用shadowsocks搭建了个人VPN, 特此记录下来.
<!--more-->
#shadowsocks和vpn
shadowsocks 是一个基于socks5协议的代理服务器.
利用shadowsocks搭建VPN的原理就是:

> * 本地浏览器将http请求发送到本地shadowsocks (sslocal进程会监听本地端口)
* sslocal进程将http请求转发给远端的shadowsocks(sssever)
* ssserver向internet请求该http请求
* 请求的数据再依次转发到浏览器

翻墙的原理就是: 找一个美国的服务器!可以直接在ramnode上买vps或者AWS上买个ec2都行, 重点该虚拟机访问外国网站不会被qiang.

#详细步骤:

1. 搞定虚拟机.
   一定要国外的服务器, 不然怎么fan..我就是在RamNode上买了个最低配的vps.一年流量500G, 才不到100.是不是超值?

2. 安装shadowsocks

        apt-get install python-gevent python-pip
        pip install shadowsocks

3. shadowsocks配置说明

   shadowsocks的配置很简单, 其配置文件是json格式的, 可选的字段值含义如下:
   
        server          服务器 IP (IPv4/IPv6)，注意这也将是服务端监听的 IP 地址
        server_port     服务器端口
        local_port      本地端端口
        password        用来加密的密码
        timeout         超时时间（秒）
        method          加密方法，可选择 "bf-cfb", "aes-256-cfb", "des-cfb", "rc4", 等等。默认是一种不安全的加密，推荐用 "aes-256-cfb"

4. 配置服务器shadowsocks
   在服务器上的/etc/shadowsocks目录下创建 config.json.填入以下内容:
        
        {
            "server":"server_ip",
            "server_port":server_port_num,
            "password":"用来加密的密码",
            "method":"aes-256-cfb"
        }

5. 启动服务器服务进程.

        /usr/local/bin/ssserver -c /etc/shadowsocks/config.json >
        /etc/shadowsocks/log 2>&1 &
  为了开机启动, 可以把上面那条命令写到 /etc/rc.local

6. 配置本地shadowsocks
   在本地上的/etc/shadowsocks目录下同样创建 config.json, 填入以下内容:

        {
            "server":"server_ip",
            "server_port":server_port_num,
            "local_address":"127.0.0.1",
            "local_port":local_port_num,
            "password":"用来加密的密码,同上",
            "passwordtimeout":300,
            "method":"aes-256-cfb",
            "fast_open":false,
            "workers":1
        }
7. 启动本地进程

        /usr/local/bin/sslocal -c /etc/shadowsocks/config.json > /etc/shadowsocks/log 2>&1 &
   同样, 为了开机启动, 可以把上面那条命令写到 /etc/rc.local

8. 浏览器设置, 启用ssh代理
   我用的chrom浏览器, 安装了拓展SwitchyOmega, 只需要添加一个Profile, 代理协议选socks5, server填127.0.0.1, port填步骤6中的local_port_num

9. done!
   打开Youtube, 发现1080P都是秒开, 瞬间心情大好啊. 哈哈哈~~

Finish
