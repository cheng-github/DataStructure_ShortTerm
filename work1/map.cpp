#include <stdio.h>
#include <stdlib.h>
#include "city.h"

enum {
    Create = 1,
    LookupRouter = 2,
    DepthSearchTraverse = 3
};

void showMenu();

int main(){
    int chooseMenuNumber = 0;

    while(chooseMenuNumber != -1){
        showMenu();
        scanf("%d", &chooseMenuNumber);
        getchar();
        printf("\n");
        switch (chooseMenuNumber) {
        case Create:
            CreateMap();
            break;
        case LookupRouter:
            FindShortestRouter();
            break;
        case DepthSearchTraverse:
            ShowDepthSearchResult();
            break;
        default:
            printf("\n\t输入了错误的选择，请重新输入");
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
}

void showMenu(){
    printf("\t--------------- 交通咨询 ---------------\n");
    printf("\t1. 创建地图\n");
    printf("\t2. 查询最短线路\n");
    printf("\t3. 根据城市名显示搜索路线\n");
    printf("\t请输入选项编号进行操作(用Enter键结束输入): ");
}







