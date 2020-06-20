#include <stdio.h>

void Optimal(int* PageOrder,int* page,int m,int n){
    int pageCapacity=0;
    int missNum=0;
    
    for(int i=0;i<m;i++){
        if(pageCapacity<n){
            missNum++;
            page[pageCapacity++]=PageOrder[i];
        }else{
            int isExist=0;
            for(int j=0;j<n;j++){
                if(page[j]==PageOrder[i]){
                    isExist=1;
                }
            }
            //如果page里面已经存在所需的物理块，那么不需要操作
            if(isExist==1){
                printf("%d:",PageOrder[i]);
                for(int j=0;j<n;j++){
                    printf("%d ",page[j]);
                }
                printf("\n");
                continue;
            }
            missNum++;
            //从前向后遍历，找到最晚出现的那一个元素
            int* temp=(int*)malloc(sizeof(int)*n);
            int tempNum=0;
            for(int j=0;j<n;j++){
                temp[j]=page[j];
            }
            for(int j=i;j<m;j++){
                for(int k=0;k<n;k++){
                    if(temp[k]!=-1&&tempNum==n-1){
                        page[k]=PageOrder[i];
                        j=m;
                        break;
                    }
                    if(temp[k]!=-1&&temp[k]==PageOrder[j]){
                        tempNum++;
                        temp[k]=-1;
                        k=n;
                    }
                }
            }
            
            //最后几个物理块出现的时候的特殊处理，当剩余的物理块数少于page的容量时
            if(i+n>=m){
                for(int j=0;j<n;j++){
                    if(temp[j]!=-1){
                        page[j]=PageOrder[i];
                    }
                }
            }
        }
        printf("%d:",PageOrder[i]);
        for(int j=0;j<n;j++){
            printf("%d ",page[j]);
        }
        printf("\n");
    }
    printf("缺页数：%d\n",missNum);
    printf("缺页率：%f\n",((double)missNum)/(double)m);
}
void FIFO(int* PageOrder,int* page,int m,int n){
    int pageCapacity=0;
    int earliest=0;
    int missNum=0;
    
    for(int i=0;i<m;i++){
        if(pageCapacity<n){
            missNum++;
            page[pageCapacity++]=PageOrder[i];
        }else{
            int isExist=0;
            for(int j=0;j<n;j++){
                if(page[j]==PageOrder[i]){
                    isExist=1;
                }
            }
            //如果page里面已经存在所需的物理块，那么不需要操作
            if(isExist==1){
                printf("%d:",PageOrder[i]);
                for(int j=0;j<n;j++){
                    printf("%d ",page[j]);
                }
                printf("\n");
                continue;
            }
            missNum++;
            page[earliest]=PageOrder[i];
            earliest=(earliest+1)%n;
        }
        
        printf("%d:",PageOrder[i]);
        for(int j=0;j<n;j++){
            printf("%d ",page[j]);
        }
        printf("\n");
    }
    printf("缺页数：%d\n",missNum);
    printf("缺页率：%f\n",((double)missNum)/(double)m);
}
void LRU(int* PageOrder,int* page,int m,int n){
    int missNum=0;
    int pageCapacity=0;
    int* stack=(int*)malloc(sizeof(int)*n);
    
    for(int i=0;i<m;i++){
        if(pageCapacity<n){
            missNum++;
            stack[pageCapacity]=PageOrder[i];
            page[pageCapacity++]=PageOrder[i];
        }else{
            int isExist=0;
            for(int j=0;j<n;j++){
                if(stack[j]==PageOrder[i]){
                    isExist=1;
                    int temp=stack[j];
                    for(int k=j;k<n-1;k++){
                        stack[k]=stack[k+1];
                    }
                    stack[n-1]=temp;
                    break;
                }
            }
            //如果page里面已经存在所需的物理块，那么不需要操作
            if(isExist==1){
                printf("%d:",PageOrder[i]);
                for(int j=0;j<n;j++){
                    printf("%d ",page[j]);
                }
                printf("\n");
                continue;
            }
            missNum++;
            for(int j=0;j<n;j++){
                if(page[j]==stack[0]){
                    page[j]=PageOrder[i];
                    break;
                }
            }
            
            for(int j=0;j<n-1;j++){
                stack[j]=stack[j+1];
            }
            stack[n-1]=PageOrder[i];
        }
        
        printf("%d:",PageOrder[i]);
        for(int j=0;j<n;j++){
            printf("%d ",page[j]);
        }
        printf("\n");
    }
    printf("缺页数：%d\n",missNum);
    printf("缺页率：%f\n",((double)missNum)/(double)m);
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int pageNum=0;
    int option=0;
    int pageCapacity=-1;
    int* PageOrder=(int*)malloc(sizeof(pageNum));
    
    while(option!=4){
        printf("请输入页面个数：\n");
        scanf("%d",&pageNum);
        printf("请输入页面序列：\n");
        for(int i=0;i<pageNum;i++){
            scanf("%d",&PageOrder[i]);
        }
        printf("请输入系统分配的最小页面个数：\n");
        scanf("%d",&pageCapacity);
        int* page=(int*)malloc(sizeof(int)*pageCapacity);
        for(int i=0;i<pageCapacity;i++){
            page[i]=-1;
        }
        printf("请选择算法：\n");
        printf("1：先进先出FIFO 2：最佳置换算法Optimal 3：最近最久未使用置换算法 4：退出\n");
        scanf("%d",&option);
        
        switch (option) {
            case 1:
                FIFO(PageOrder,page,pageNum,pageCapacity);
                break;
            case 2:
                Optimal(PageOrder,page,pageNum,pageCapacity);
                break;
            case 3:
                LRU(PageOrder,page,pageNum,pageCapacity);
                break;
        }
        printf("输入4结束，否则继续\n");
        scanf("%d",&option);
    }
    //7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
    return 0;
}
