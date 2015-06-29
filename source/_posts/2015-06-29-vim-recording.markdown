---
layout: post
title: "vim recording"
date: 2015-06-29 22:04:48 +0800
comments: true
description: "vim recording"
keywords: vim, recording

categories: 
  - other

---

vim在Normal模式下有recording(录制)的功能,即可以录制一系列操作并回放, 该功能对于一些需要重复操作的场景很有效.

recording功能使用方法如下:
   
    1.在Normal模式下, 按下`qa`, 即start recording, 并将操作序列存与寄存器a中, 此处可以为`qb`, `qc`等.
    2.输入相关操作序列
    3.输入`q`结束recording.
    4.`@a`回放寄存器a中的操作

<!--more-->

下面以一个例子来具体说明.
文件test中只有一行字符串如下:

    1

指令序列`qaYp<C-a>q`可以存储这样一个操作, 将当前行的数字拷贝到下一行, 并在新行中增加1

    1.`qa`开始录制
    2.`Yp`复制当前行并粘贴, 同时光标移动到下一行
    3.`<C-a>`将该行的数字增加1
    4.`q`停止录制

当输入上面的一串指令后, `@a`会回放寄存器a的操作, `@@`会回放上一次回放,为了多次回放, 可以在@前加入数字来指定回放次数

现在我们在Normal模式下继续输入`10@a`, 文本变成如下:
    
     1
     2
     3
     4
     5
     6
     7
     8
     9
     10
     11

最终生成一个递增序列

如果我们希望等差数列的间隔为2, 则可以输入`qbYp<C-a><C-a>q`, 然后输入`10@b`回放

     1
     2
     3
     4
     5
     6
     7
     8
     9
     10
     11
     13
     15
     17
     19
     21
     23
     25
     27
     29
     31
