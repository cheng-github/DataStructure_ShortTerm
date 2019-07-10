#include <string.h>

const int MAX_CITY_NUM = 30;
const int MAX_DISTANCE = 100000;

typedef struct indexname {
    char cityName[30];
    int cityIndex;
} pair;

typedef struct city {
    double distance;
    int destinationIndex;
    char destinationName[30];
    struct city *next;
} city, *pcity;

pair paris[MAX_CITY_NUM];
pcity map[MAX_CITY_NUM];
int currentIndex;
int flags[MAX_CITY_NUM] = {0}; // 用于深度优先搜索遍历

void Init(){
    currentIndex = -1;
    for (int i = 0; i < MAX_CITY_NUM; i++) {
        map[i] = NULL;
    }
}

void AddCityPairs(char name[]){
    currentIndex ++;
    paris[currentIndex].cityIndex = currentIndex;
    strcpy(paris[currentIndex].cityName, name);
}

/*
    根据输入的城市名找到对应的城市索引,没有找到则返回-1
 */
int findCityIndexByName(char name[]){
    for(int i = 0;i <= currentIndex; i++){
        if (strcmp(paris[i].cityName, name) == 0) {
            return i;
        }
    }
    return -1;
}

/*
    根据城市索引找到对应的城市名称
 */
char *findCityNameByIndex(int index){
    for (int i = 0; i <= currentIndex; i++) {
        if (paris[i].cityIndex == index) {
            return paris[i].cityName;
        }   
    }
    return NULL;
}

/*
    添加地图中的关系
 */
void AddMap(int fristIndex, int secondIndex, double distance, char *descCityName){
    pcity item = (pcity)malloc(sizeof(city));
    item -> distance = distance;
    item -> destinationIndex = secondIndex;
    strcpy(item -> destinationName, descCityName);
    item -> next = NULL;
    if (map[fristIndex] == NULL) {
        map[fristIndex] = item;
    } else {
        item -> next = map[fristIndex];
        map[fristIndex] = item;
    }
    printf("\t数据添加成功\n");
}

void CreateMap(){
    char input[30] = "start";
    char delim[] = "-";
    char *firstCity;
    char *secondCity;
    int firstIndex;
    int secondIndex;
    double distance;

    Init();
    printf("\t开始创建地图(按照城市名称-城市名称-距离的格式填写，要结束创建，输入exit结束):\n");
    while (true) {
        printf("\t请输入要添加的数据: ");
        gets(input);
        if (strcmp(input, "exit") == 0) {
            break;
        }
        // 分割三次，对应的值分别为城市名、城市名、距离
        firstCity = strtok(input, delim);
        firstIndex = findCityIndexByName(firstCity);
        if (firstIndex == -1) {
            AddCityPairs(firstCity);
            firstIndex = currentIndex;
        }
        // 注意第二次和第三次需要为空
        secondCity = strtok(NULL, delim);
        secondIndex = findCityIndexByName(secondCity);
        if (secondIndex == -1) {
            AddCityPairs(secondCity);
            secondIndex = currentIndex;
        } 
        distance = atof(strtok(NULL, delim));
        // 将输入的数据添加到邻接表中去
        AddMap(firstIndex, secondIndex, distance, secondCity);
    }
    printf("\t地图创建完成\n");
    system("pause");
    system("cls");
}


void DoDeptPrioritySearch(int start){
    // 标记本身
    pcity temp = map[start];
    flags[start] = 1;
    
    // 标记子节点
    while (temp != NULL) {
        int nextIndex = temp -> destinationIndex;    
        if (!flags[nextIndex]) {
            printf("\t%8s", temp -> destinationName);
            DoDeptPrioritySearch(nextIndex);
        }
        temp = temp -> next;
    }
    
}


/*
    使用深度优先搜索遍历路线
 */
void ShowDepthSearchResult(){
    char startCityName[30];
    int startIndex = -1;
    
    printf("\t请输入出发城市:");
    gets(startCityName);
    startIndex = findCityIndexByName(startCityName);
    if (startIndex == -1) {
        printf("\t对不起,当前地图数据中暂无该城市信息");
    } else {
        for (int i = 0; i < MAX_CITY_NUM; i++) {
                flags[i] = 0;
        }
        printf("\t该城市所有搜索线路上的城市如下:\n");
        DoDeptPrioritySearch(startIndex);
    }
    printf("\n");
    system("pause");
    system("cls"); 
}

/*
    计算当前的最小节点索引
 */
int CalNextIndexValue(double minDistance[], int visited[]){
    double minValue = -1;
    int nextIndex = -1;

    for (int i = 0; i < currentIndex + 1; i++) {
        // 不比较已经为最小的节点和距离为默认最大的节点(表示当前不可达)
        if (!visited[i] && minDistance[i] != MAX_DISTANCE) {
            if (minValue == -1) {
                minValue = minDistance[i];
                nextIndex = i;
            } else if (minValue > minDistance[i]) { 
                minValue = minDistance[i];
                nextIndex = i;
            }
        }
    }

    return nextIndex;
}

/*
    根据保留的path数组打印最短路径
 */
void PrintShortestRouter(int path[], int startIndex, int endIndex){
    int router[currentIndex] = {0};
    int count = 0;
    int currentIndex = endIndex;
    
    router[count++] = currentIndex;
   
    while (currentIndex != startIndex) {
        currentIndex = path[currentIndex];
        router[count++] = currentIndex;
    }

    // 从数组末尾开始打印结果
    for (int i = count - 1; i >= 0; i--) {
        printf("\t%8s", findCityNameByIndex(router[i]));
    }
    
}

/*
    根据Dijkstra算法计算最短路径
 */
void DijkstraShortestRouter(int start, int endIndex){
    int visited[currentIndex + 1] = {0}; // 使用该数组用于标记哪些节点已存在最小节点中
    double minDistance[currentIndex + 1]; // 使用该数组去计算到对应节点的最短距离
    int path[currentIndex + 1] = {0}; // 记录到达的上一个节点的值，数组编号表示对应节点，值表示上个节点
    int nextIndex = start;
    int bonusValue = 0;  // 表示当前循环的节点到出发节点的值
    pcity current = NULL;
    // 必须手动初始化非零的浮点数组
    for(int i = 0; i <= currentIndex; i++){
        minDistance[i] = MAX_DISTANCE;
    }
    // 设置初始值避免纳入计算
    visited[start] = 1;
    minDistance[start] = 0.0;
    current = map[nextIndex];

    // 每次通过一个while循环重置nextIndex的值，nextIndex应该为每次被选出的节点
    while (nextIndex != -1 && current != NULL) {
        if (minDistance[current -> destinationIndex] > current -> distance + bonusValue) {
            // 每次修改这个值说明有路径的变化，我们在这里可更新子当前最短的上一个节点
            path[current -> destinationIndex] = nextIndex;
            minDistance[current -> destinationIndex] = current -> distance + bonusValue;
        }
        current = current -> next;
        // 每次遍历完到最后一个节点，需要计算下一个节点的值
        while (current == NULL) {
            // 在获得endIndex之前获得-1表示这两个城市没有线路
            nextIndex = CalNextIndexValue(minDistance, visited);
            if (nextIndex == -1) {
                printf("\t对不起，这两个城市线路暂时未连通");
                return ;
            }
            // 标记当前已被访问
            visited[nextIndex] = 1;
            if (nextIndex == endIndex) {
                // 那途径的城市该怎么输出呢？？？？
                // 可以在每次计算下一个最短节点的时候记录上个索引，这样最终达到记录最短路径的目的
                printf("\t这两个城市最短距离为: %8f \n", minDistance[endIndex]);
                printf("\t最短线路为: \n");
                PrintShortestRouter(path, start, endIndex);
                return ;
            }
            // 考虑两种情况，一、当前的最小没有下一个节点 二、当前的最小有下面的节点
            // 如果没有下一节点，我们继续循环体即可，也就是再次在现有的数据中寻找最小
            // 如果有下一个节点，那么我们需要跳出当前循环体，并将当前的最小值作为bonusValue进行修改
            if (map[nextIndex] != NULL) {
                bonusValue = minDistance[nextIndex];
                current = map[nextIndex];
            }
            
        }
    }
    // 如果没有进入循环，说明这个城市没有开通的线路
    printf("\t对不起，这两个城市线路暂时未连通");
    return ;
}

/*
    根据用户输入的两个城市名称查询最短线路，使用Dijkstra算法实现最短距离计算
 */
void FindShortestRouter(){
    char input[30];
    char delim[] = "-";
    char *startCity;
    int startIndex = -1;
    char *endCity;
    int endIndex = -1;

    printf("\t请输入起始城市和到达城市(使用城市名-城市名的格式):");
    gets(input);
    startCity = strtok(input, delim);
    endCity = strtok(NULL, delim);
    startIndex = findCityIndexByName(startCity);
    endIndex = findCityIndexByName(endCity);

    if (startIndex == -1 || endIndex == -1) {
        printf("\t对不起，您输入的城市名暂时未录入地图，请确认后输入");
    } else {
        DijkstraShortestRouter(startIndex, endIndex);
    }
    printf("\n");
    system("pause");
    system("cls");
}

