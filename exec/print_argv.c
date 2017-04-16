#include<stdio.h>

int main(int argc, char* argv[])
{
    int i = 0;

    // 依次打印出main的参数列表
    for(i = 0; i < argc; ++i)
    {
        printf("argv[%d]:%s\n",i,argv[i]);    
    }
}
