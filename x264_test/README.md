# x264_test
x264_test
.x264

./configure --enable-shared --enable-pic --disable-opencl?

make

make install



2.x264_test

gcc -o test x264_test.c libx264.a -lm -lpthread

gcc -o x264_test x264_test.c -L. -lx264 -lm -lpthread
--------------------- 
作者：Tianyu-liu 
来源：CSDN 
原文：https://blog.csdn.net/wishfly/article/details/51841077 
版权声明：本文为博主原创文章，转载请附上博文链接！
