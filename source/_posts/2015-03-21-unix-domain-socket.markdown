---
layout: post
title: "Unix domain socket"
date: 2015-03-21 16:39:15 +0800
comments: true
description: unix domain socket example
keywords: unix socket IPC

categories: 
- Linux

---

这天因为项目需要, 接触到了Unix domain socket, 主要是用于本地进程之间进行通信的, 很方便.而且性能比本地IP socket通信要好, 主要是没有了协议栈的处理.

原理就是在本地文件系统创建各自的socket文件(程序中会自动创建), 然后就可以用ip socket的相关函数来操作.

下面是Server代码:
<!--more-->

{% include_code lang:c unix_socket_server.c %}

下面是Client代码:

{% include_code lang:c unix_socket_client.c %}

在Client端, 可以选择connect, 然后用send和recv收发数据, 也可以不connect, 用sendto 和 recvfrom收发数据, 这应该通IP socket是一样的.

需要注意的是, 由于用的是sockaddr_un结构, 而不是ip的sockaddr_in结构, 所有socket通信时跟IP地址和端口没有任何关系

运行时的系统截图:

{% img /images/unix_domain_socket.png %}

虽然这个例子中是SOCK_DGRAM, 但是, 当发送方发送过快, 接收方来不及收时, 发送放的sendto会自动阻塞, 直到接收方缓冲区有空时, 发送方再继续发.我想这就是为什么无论是stream 还是 dgram, unix domain socket总是可靠的原因吧(可同udp对比查看差异).

Finish
