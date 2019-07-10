#include <time.h>
#include <string.h>

const int MAX_CARS_NUM = 3;     // 最多停放车辆数目
const int EVERY_HOUR_PRICE = 12.5; // 每小时停车费用

// 定义停车场每辆车的数据类型
typedef struct car {
    char licenseNum[30]; 
    char brand[30];
    time_t arriveTime;  // 车辆到达时间
    time_t startParkTime;   // 车辆停车场内开始停放时间
    time_t endParkTime;     // 车辆停车结束时间
    time_t leaveTime; // 车辆离开该区域时间
    float cost;     // 车辆停车费
    struct car *next; // 指向下一辆车
} car, *pcar;

pcar innerHead;
pcar outerHead;
pcar leaveHead;
char showtime[40];  // 用于格式化输出显示
char *nomsg = "------";

void AddInnerCar();
void AddOuterCar();

void InitData(){
    innerHead = NULL;
    outerHead = NULL;
    leaveHead = NULL;
}

int GetListSize(pcar head){
    int count = 0;
    while (head != NULL){
        count++;
        head = head -> next;
    }
    return count;
}

/*
    根据time_t的值格式化输出时间
 */
char * FormatPrintTime(time_t time){
    if (!time){
        return nomsg;
    }
    struct tm *format = localtime(&time);
    strftime(showtime, 40, "%Y-%m-%d %H:%M:%S", format);
    return showtime;
}


/* 此处处理车辆进入仅仅为直接进入停车场的情况，针对离开再进入的情况之后再处理 */
void HandleCarEnter(){
    if(GetListSize(innerHead) < MAX_CARS_NUM){
        AddInnerCar();
    } else {
        AddOuterCar();
    }
}

void AddInnerCar(){
    pcar tail = NULL;
    pcar temp = (pcar)malloc(sizeof(car));
    printf("\t请输入车牌号码: ");
    gets(temp -> licenseNum);
    printf("\t请输入车辆品牌: ");
    gets(temp -> brand);
    temp -> arriveTime = time(NULL);
    temp -> startParkTime = time(NULL);
    temp -> endParkTime = NULL;
    temp -> leaveTime = NULL;
    temp -> next = NULL;
    if (!innerHead){
        innerHead = temp;
    } else {
        tail = innerHead;
        while(tail -> next != NULL){
            tail = tail -> next;
        }
        tail -> next = temp;
    }
    printf("数据添加成功!");
    printf("\n\n\n");
    system("pause");
    system("cls");
}

void AddOuterCar(){
    pcar tail = NULL;
    pcar temp = (pcar)malloc(sizeof(car));
    printf("\t请输入车牌号码: ");
    gets(temp -> licenseNum);
    printf("\t请输入车辆品牌: ");
    gets(temp -> brand);
    temp -> arriveTime = time(NULL);
    temp -> startParkTime = NULL;
    temp -> endParkTime = NULL;
    temp -> leaveTime = NULL;
    temp -> next = NULL;
    if (!outerHead){
        outerHead = temp;
    } else {
        tail = outerHead;
        while (tail -> next != NULL){
            tail = tail -> next;
        }
        tail -> next = temp;
    }
    printf("\t由于当前车位已满，车辆停靠在旁道等候\n");
    printf("数据添加成功!");
    printf("\n\n\n");
    system("pause");
    system("cls");
}

void AddLeaveCar(pcar item){
    pcar tail = NULL;
    if (!leaveHead){
        leaveHead = item;
    } else {
        tail = leaveHead;
        while (tail -> next != NULL){
            tail = tail -> next;
        }
        tail -> next = item;
    }
}

void CheckInnerStatus(int isPause){
    pcar temp = innerHead;
    int count = 1;
    printf("\t停车场内停车状态:\n");
    printf("\t车位顺序编号\t车牌号码\t车辆品牌\t        开始停车时间\t        结束停车时间\n");
    while(temp != NULL){
        printf("\t%6d      \t%8s\t%8s\t%20s\t",
            count++, temp -> licenseNum, temp -> brand,
            FormatPrintTime(temp -> startParkTime));
        printf("%20s\n", FormatPrintTime(temp -> endParkTime));
        temp = temp -> next;
    }
    if (count > MAX_CARS_NUM){
        printf("\n\t目前没有空余车位");
    } else {
        printf("\n\t目前剩余车位: %d\n", MAX_CARS_NUM + 1 - count );
    }
    
    if (isPause) {
        printf("\n\n\n");
        system("pause");
        system("cls");
    } else {
        printf("\n");
    }
}

void CheckOuterStatus(int isPause){
    pcar temp = outerHead;
    int count = 1;
    printf("\n\t便道停车状态:\n");
    printf("\t排队序号\t车牌号码\t车辆品牌\t        旁道停靠时间\t        结束停车时间\n");
    while(temp != NULL){
        printf("\t%4d    \t%8s\t%8s\t%20s\t",
            count++, temp -> licenseNum, temp -> brand,
            FormatPrintTime(temp -> arriveTime));
        printf("%20s\n", FormatPrintTime(temp -> leaveTime));
        temp = temp -> next;
    }
    if (count == 1)
    {
        printf("\t当前旁道无任何车辆\n");
    }

    if (isPause) {
        printf("\n\n\n");
        system("pause");
        system("cls");
    } else {
        printf("\n");
    }
}

void CheckLeaveStatus(){
    pcar temp = leaveHead;
    int count = 1;
    printf("\t已经离开的车辆信息:\n");
    printf("\t离开序号\t车牌号码\t车辆品牌\t        到达时间\t        离开时间\n");
    while(temp != NULL){
        // 分两次输出避免时间输出被覆盖
        printf("\t%4d    \t%8s\t%8s\t%16s\t",
            count, temp -> licenseNum, temp -> brand,
            FormatPrintTime(temp -> arriveTime));
        printf("%16s\n", FormatPrintTime(temp -> leaveTime));
        temp = temp -> next;
    }
    
    printf("\n\n\n");
    system("pause");
    system("cls");
   
}

void CheckAllStatus(){
    CheckInnerStatus(0);
    CheckOuterStatus(0);
    CheckLeaveStatus();
}

/*
    取外部旁道的第一辆车
 */
pcar GetOuterFirstCar(){
    pcar temp = outerHead;
    if (temp){
        outerHead = outerHead -> next;
        temp -> next = NULL;
        return temp;
    }
    return NULL;
}

/*
    将旁道的车插入到停车场最后一个位置
 */
void MakeOuterEnterInter(){
    pcar temp = innerHead;
    pcar income = GetOuterFirstCar();
    // 从进入停车场内开始计算停车时间
    income -> startParkTime = time(NULL);
    if (!temp){
        innerHead = income;
        return ;
    }
    while (temp) {
       if (temp -> next == NULL){
          temp -> next = income;
          break;
       }
       temp = temp -> next;
    }
}

/*
    离开的情况比较复杂一些
 */
void HandleCarLeave(){
    pcar temp = innerHead;
    pcar current = NULL;
    char leaveCarNum[30];
    if (GetListSize(innerHead) < 1 && GetListSize(outerHead) < 1) {
        printf("\t提示: 当前停车场以及旁道无车辆\n\n\n");
        system("pause");
        return;
    }
    printf("\t请输入离开的车辆车牌号码: ");
    gets(leaveCarNum);
    if (temp && strcmp(temp -> licenseNum, leaveCarNum) == 0){
        temp -> endParkTime = time(NULL);
        temp -> leaveTime = time(NULL);
        temp -> cost =  (temp -> endParkTime - temp -> startParkTime)/(60 * 60) * EVERY_HOUR_PRICE;
        printf("\t车牌号为%s的车从停车场内离开，停车费为%f\n\n\n", temp -> licenseNum, temp -> cost);
        innerHead = innerHead -> next;
        temp -> next = NULL;
        AddLeaveCar(temp);
        if (GetListSize(outerHead) < 1) {
            system("pause");
            system("cls");
            return;
        }
        MakeOuterEnterInter();
        system("pause");
        system("cls");
        return ;
    }
    // 如果第一个不满足条件，从第二个开始寻找并向下遍历
    while(temp){
        current = temp -> next;
        if (current && strcmp(current -> licenseNum, leaveCarNum) == 0) {
            current -> endParkTime = time(NULL);
            current -> leaveTime = time(NULL);
            current -> cost =  (current -> endParkTime - current -> startParkTime)/(60 * 60) * EVERY_HOUR_PRICE;
            printf("\t车牌号为%s的车从停车场内辆离开，停车费为%f\n\n\n", current -> licenseNum, current -> cost);
            // 移除该节点
            temp -> next = current -> next;
            current -> next = NULL;
            AddLeaveCar(current);
            if (GetListSize(outerHead) < 1) {
                system("pause");
                system("cls");
                return;
            }
            MakeOuterEnterInter();
            system("pause");
            system("cls");
            return ;
        }
        temp = temp -> next;
    }

    // 如果输入的车牌号不在停车场内，那么在旁道中寻找是否存在对应车辆
    temp = outerHead;
    if (temp && strcmp(temp -> licenseNum, leaveCarNum) == 0) {
        temp -> leaveTime = time(NULL);
        temp -> cost =  0.0;
        printf("\t车牌号为%s的车从旁道离开，停车费为%f\n\n\n", temp -> licenseNum, temp -> cost);
        outerHead = outerHead -> next;
        temp -> next = NULL;
        AddLeaveCar(temp);
        system("pause");
        system("cls");
        return ;
    }

    while (temp){ 
        current = temp -> next;
        if (current && strcmp(current -> licenseNum, leaveCarNum) == 0) {
            current -> leaveTime = time(NULL);
            current -> cost =  0.0;
            printf("\t车牌号为%s的车从旁道离开，停车费为%f\n\n\n", current -> licenseNum, current -> cost);
            temp -> next = current -> next;
            temp -> next = NULL;
            AddLeaveCar(current);
            system("pause");
            system("cls");
        }
        temp = temp -> next;
    }
    
    printf("\t无法找到对应车牌号，请输入确认车牌号后再次输入\n");
    system("pause");
    system("cls");
}