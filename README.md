# 2019程序设计实习免修考试

所有代码为本人所写，所有题目均AC。水平有限，部分代码可能可读性较弱。

## 题目网址（提交通道已关闭）：

- [2019程序设计实习免修考试(算法)](http://cxsjsx.openjudge.cn/2019freea/)
- [2019程序设计实习免修考试(C++)](http://cxsjsx.openjudge.cn/2019freec/)

## 算法部分：6题

### 01-上机

[提交网址](http://bailian.openjudge.cn/practice/4150/)

dp[n][i][j]表示前n个座位能力值之和的最大值，i,j=0或1，分别表示n号座位入座时，左,右侧是否有人。状态转移方程与初值见源代码。

### 02-棋盘问题

[提交网址](http://bailian.openjudge.cn/practice/1321/)

8皇后问题退化版。回溯。

### 03-Pots(英文题目)

[提交网址](http://bailian.openjudge.cn/practice/3151/)

大意：给你两个给定容积的空瓶，通过加水、倒水等操作获得要求体积的水，输出步数最少的方案之一。

纯BFS。

### 04-河中跳房子

[提交网址](http://noi.openjudge.cn/ch0111/10/)

NOIP2015提高组Day2T1（只是换了个情景）。二分+贪心。

### 05-2的幂次方表示

[提交网址](http://noi.openjudge.cn/ch0202/8758/)

NOIP1998普及组第一题题（还能再水一点吗）。递归。

### 06-回文序列

[提交网址](http://bailian.openjudge.cn/practice/4122/)

dp[i]表示前i个字符的最小切割数，状态转移方程：dp[i]=max(dp[j]+1|j=0,1,...,i-1.且j+1~n是回文序列)，其中dp[0]=-1.实际程序中下标前移了一位，所以实现细节略有区别。

算法部分难度：不难，但在规定时间内全部Debug完成不容易。难度：1>6>3>4>2>5.

## C++部分：7题

因为都是语法，所以就没有题解和难度评估之类的了，主要是类、派生、多态、模板、运算符重载等,题型都是编程填空。除了第6题比较打脑袋外其余知道语法就很trivial.

### 1：返回什么才好呢？

[提交网址](http://cxsjsxmooc.openjudge.cn/2019t3springall/007/)

### 2：编程填空：多态

可直接通过输出查看是否正确，无需提交。

### 3：编程填空：又是MyClass

未找到可用的提交地址，但与标程对拍无误。

### 4：编程填空：很眼熟的模板题

未找到可用的提交地址，但与标程对拍无误。

### 5：继承自string的MyString

[提交网址](http://cxsjsxmooc.openjudge.cn/2019t3springall/021/)

### 6：很难蒙混过关的CArray3d三维数组模板类

[提交网址](http://cxsjsxmooc.openjudge.cn/2019t3springall/036/)

### 7：函数对象过滤器

[提交网址](http://cxsjsxmooc.openjudge.cn/2019t3springall/037/)

