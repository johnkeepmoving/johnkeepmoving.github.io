---
layout: post
title: "博客域名风波"
date: 2015-05-13 22:49:40 +0800
comments: true
description: "octopress dns 404 not found"
keywords: octopress, github, gitcafe, dns, CNAME, A

categories:
- other

---
我的博客是基于Octopress搭建的,但是由于一开始不太明白怎么弄,把本地Octopress目录弄得很乱,看着不爽(强迫症...),于是乎前天想重新搭建一遍.

参考[破船大哥](http://beyondvincent.com/2013/08/03/2013-08-03-108-creating-a-github-blog-using-octopress/)的博客,很快就将Octopress部署到了github上(Octopress源码+生成的blog), 这次使用的是bootstrap主题,并且增加了如下功能:
        
        1.右下角的revolvermaps, 实时显示访问情况.(不好看,也许回头会去掉)
        2.右侧的微薄show, 纯粹好奇玩玩.
        3.快速返回顶部的按钮

随后, 因为国内线路访问github实在有点慢,而国内良心厂家gitcafe也可以提供类似与github一样的pages服务,所以参考[唐巧的博客](http://blog.devtang.com/blog/2014/06/02/use-gitcafe-to-host-blog/),又将生成的blog也push到了gitcafe一份.

然后, 在配置DNS解析的时候(其实压根就不需要改动), 由于我购买了二级域名johnkeepmoving.com, 所以我将二级域名johnkeepmoving.com, 以及子域名www.johnkeepmoving.com和blog.johnkeepmoving.com都一起指向了gitcafe的服务器.

问题来了, 我发现2个子域名可以正常访问, 而二级域名也可以正常解析(能ping通), 但是http请求会返回404错误. 我一直以为是我gitcafe里page服务的某些配置可能有问题, 所以就不断检查, 可检查得出的结论是跟我之前博客的域名解析一模一样啊.之前(2015过年前)一直都是可以所有域名都正常访问的.
<!--more-->

悲催的我终于脑门开窍, google了关键词"gitcafe 二级域名失效".结果发现人家[gitcafe已经关闭了.com二级域名的访问](http://blog.gitcafe.com/?p=478), 而且刚好是最近才停止的.汗,怪不得可以ping通,但却显示404错误.

解决办法:
    既然gitcafe关闭了.com二级的访问, 那就把二级域名解析到github上就好了,子域名www和blog依然解析到gitcafe.
最后的域名解析方法:
    
    主机记录    记录类型    记录值
    @           A           199.27.74.133(github地址)
    blog        CNAME       johnkeepmoving.gitcafe.io
    www         CNAME       johnkeepmoving.gitcafe.io
    

**最后总结,** 
    
    url:                    博客代码所在位置:
    johnkeepmoving.com      github
    www.johnkeepmoving.com      gitcafe
    blog.johnkeepmoving.com     gitcafe
    
目前只是硬性对域名进行解析, 将来如果有条件, 可以考虑针对用户的不同链路类型, 配置不同的DNS解析, 最终提升用户体验.

Finish
