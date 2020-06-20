#include <stdio.h>

//银行家算法
void bankerAlgorithm(int* request,int resourceType,int** need,int* available,int** allocation,int* finish,int* sequence,int* seqIndex,int m,int n){
    for(int j=0;j<n;j++){
        if(request[j]>need[resourceType][j]||request[j]>available[j]){
            return;
        }
    }
    int flag=1;
    for(int j=0;j<n;j++){
        available[j] -= request[j];
        allocation[resourceType][j] += request[j];
        need[resourceType][j]=need[resourceType][j]- request[j];
        if(need[resourceType][j]>0){
            flag=0;
        }
    }
    if(flag==1){
        finish[resourceType]=1;
        sequence[(*seqIndex)++]=resourceType;
        for(int j=0;j<n;j++){
            available[j]+=allocation[resourceType][j];
            allocation[resourceType][j]=0;
        }
    }
    for(int i=0;i<m;i++){
        if(finish[i]==0){
            bankerAlgorithm(need[i],i,need,available,allocation,finish,sequence,seqIndex,m,n);
        }
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int m,n;
    printf("输入进程的数目和种类：（使用英文逗号隔开）\n");
    scanf("%d,%d",&m,&n);
    int** max=(int**)malloc(sizeof(int*)*m);
    int** need=(int**)malloc(sizeof(int*)*m);
    int* finish=(int*)malloc(sizeof(int)*m);
    int* sequence=(int*)malloc(sizeof(int)*m);
    int** allocation=(int**)malloc(sizeof(int*)*m);
    int seqIndex=0;
    
    //保存状态用的中间变量
    int** max2=(int**)malloc(sizeof(int*)*m);
    int** need2=(int**)malloc(sizeof(int*)*m);
    int** allocation2=(int**)malloc(sizeof(int*)*m);
    int* finish2=(int*)malloc(sizeof(int)*m);

    printf("输入每个进程最多所需的各类资源数：\n");
    for(int i=0;i<m;i++){
        max[i]=(int*)malloc(sizeof(int)*n);
        need[i]=(int*)malloc(sizeof(int)*n);
        max2[i]=(int*)malloc(sizeof(int)*n);
        need2[i]=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("输入每个进程已分配的各资源数：\n");
    
    for(int i=0;i<m;i++){
        allocation[i]=(int*)malloc(sizeof(int)*n);
        allocation2[i]=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++){
            scanf("%d",&allocation[i][j]);
        }
    }
    printf("请输入各个资源现有的数目：\n");
    int* available=(int*)malloc(sizeof(int)*n);
    int* available2=(int*)malloc(sizeof(int)*n);
    for(int j=0;j<n;j++){
        scanf("%d",&available[j]);
        available2[j]=available[j];
    }
    
    
    //初始化数据
    for(int i=0;i<m;i++){
        int flag=1;
        for(int j=0;j<n;j++){
            need[i][j]=max[i][j]-allocation[i][j];
            if(need[i][j]!=0){
                flag=0;
            }
        }
        if(flag==1){
            sequence[seqIndex++]=i;
            for(int j=0;j<n;j++){
                available[j]+=allocation[i][j];
                allocation[i][j]=0;
            }
        }
        finish[i]=flag;
    }
    
    // 保存状态
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            max2[i][j]=max[i][j];
            need2[i][j]=need[i][j];
        }
    }
    for(int j=0;j<n;j++){
        finish2[j]=finish[j];
    }

    
    //设置分配的资源
    int* request=(int *)malloc(sizeof(int)*n);
    int resourceType=1;
    int isSafe=1;
    char x='y';
   
    while (x=='y') {
        printf("输入要申请的进程号：（注：第1个进程号为0，以此类推）\n");
        scanf("%d",&resourceType);
        printf("输入进程所请求的各资源的数量\n");
        for(int j=0;j<n;j++){
            scanf("%d",&request[j]);
        }
        
        bankerAlgorithm(request,resourceType,need,available,allocation,finish,sequence,&seqIndex,m,n);
        for(int i=0;i<m;i++){
            if(finish[i]==0) isSafe=0;
        }
        if(isSafe==0){
            printf("为进程p%d分配(%d,%d,%d,%d)的资源时不安全\n",resourceType,request[0],request[1],request[2],request[3]);
            
        }else{
            printf("为进程p%d分配(%d,%d,%d,%d)的资源时安全\n",resourceType,request[0],request[1],request[2],request[3]);
            //为进程分配一次安全的资源
            int flag=1;
            for(int j=0;j<n;j++){
                available2[j] -= request[j];
                allocation2[resourceType][j] += request[j];
                need2[resourceType][j] -= request[j];
                if(need2[resourceType][j]>0){
                    flag=0;
                }
            }
            if(flag==1){
                finish2[resourceType]=1;
                for(int j=0;j<n;j++){
                    available2[j]+=allocation2[resourceType][j];
                    allocation2[resourceType][j]=0;
                }
            }
        
            printf("安全序列是：");
            
        }
        
        //输出序列
        for(int i=0;i<m-1;i++){
            printf("%d->",sequence[i]);
        }
        printf("%d\n",sequence[m-1]);
        
        //状态回滚
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                max[i][j]=max2[i][j];
                need[i][j]=need2[i][j];
                allocation[i][j]=allocation2[i][j];
            }
            sequence[i]=-1;
        }
        for(int j=0;j<n;j++){
            finish[j]=finish2[j];
            available[j]=available2[j];
            
        }
        seqIndex=0;
        
        //询问是否继续分配
        printf("你还想再次请求分配吗？(输入y继续)\n");
        getchar();
        scanf("%c",&x);
        
    }
    
    return 0;
}
