# MyBigInteger
BigInteger in CPP.


# 欢迎关注微信公众号：第1维度.

公众号内容涵盖：个人成长、行业思考、计算机科学技术。 目标：以尽量浅显易懂的表达方式，传播知识。

本项目详细文档 / Here is the documentation of MyBigInteger：
https://mp.weixin.qq.com/s/FFn4JLDox_aBWVrM0-g3Zg




# optimisedBigInteger.cpp对第一版代码进行了三个方面的优化 / optimisedBigInteger.cpp is the optimized code of fist commitment, it is optimized from the following three aspects：

1.优化后的代码支持负整数的存储和表示，并能对负整数进行运算 / Make representing and manipulating negetive integer possible；

2.第一版代码将大整数以8位十进制位为一段的方式存储和处理处理，优化后以按1位十进制位存储和处理大整数，显著提高了除法运算的效率 / Optimized the performance of division by changing the way we represent big integer;

3.修改了一些bug / Fixed some bugs.
