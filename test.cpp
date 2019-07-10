#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char buf[40];

char * FormatPrintTime(time_t time){
    if (!time){
        return "---";
    }
    struct tm *format = localtime(&time);
    strftime(buf, 40, "%Y-%m-%d %H:%M:%S", format);
    return buf;
}

typedef struct test
{
    int empty = 0; 
} test, *ptest;


int main(){
    // time_t t1 = time(NULL);
    // printf("%d\n", t1);
    // system("pause");
    // time_t t2 = time(NULL);
    // printf("%d\n", t2);
    // printf("%d\n", t2 - t1);
    // system("pause");

    // printf("%f", 4321/(60 *60) * 12.5);
    // system("pause");
    // char *temp = FormatPrintTime(time(NULL));
    // printf("%s", temp);

    // test t[10];
    // int tt[10];
    // ptest p[10];
    // for (int i = 0; i < 10; i++)
    // {
    //     if (p[i]) {
    //         printf("不为空\n");
    //     }else{
    //         printf("为空\n");
    //     }
        
    // }

    // char input[16]="abc,d,ef,g";//待分解字符串
    // char* delim=",";//分隔符字符串
    // char* p=strtok(input,delim);//第一次调用strtok
    // while(p!=NULL){//当返回值不为NULL时，继续循环
    //     printf("%s\n",p);//输出分解的字符串
    //     p=strtok(NULL,delim);//继续调用strtok，分解剩下的字符串
    // }
    int currentIndex = 10;
    int flags[currentIndex] = {0};
    for (int i = 0; i < currentIndex; i++) {
        printf("%d", flags[i]);
    }

    system("pause");
}



