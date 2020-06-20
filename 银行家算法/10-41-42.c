#include <stdio.h>

//���м��㷨
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
    printf("������̵���Ŀ�����ࣺ��ʹ��Ӣ�Ķ��Ÿ�����\n");
    scanf("%d,%d",&m,&n);
    int** max=(int**)malloc(sizeof(int*)*m);
    int** need=(int**)malloc(sizeof(int*)*m);
    int* finish=(int*)malloc(sizeof(int)*m);
    int* sequence=(int*)malloc(sizeof(int)*m);
    int** allocation=(int**)malloc(sizeof(int*)*m);
    int seqIndex=0;
    
    //����״̬�õ��м����
    int** max2=(int**)malloc(sizeof(int*)*m);
    int** need2=(int**)malloc(sizeof(int*)*m);
    int** allocation2=(int**)malloc(sizeof(int*)*m);
    int* finish2=(int*)malloc(sizeof(int)*m);

    printf("����ÿ�������������ĸ�����Դ����\n");
    for(int i=0;i<m;i++){
        max[i]=(int*)malloc(sizeof(int)*n);
        need[i]=(int*)malloc(sizeof(int)*n);
        max2[i]=(int*)malloc(sizeof(int)*n);
        need2[i]=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("����ÿ�������ѷ���ĸ���Դ����\n");
    
    for(int i=0;i<m;i++){
        allocation[i]=(int*)malloc(sizeof(int)*n);
        allocation2[i]=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++){
            scanf("%d",&allocation[i][j]);
        }
    }
    printf("�����������Դ���е���Ŀ��\n");
    int* available=(int*)malloc(sizeof(int)*n);
    int* available2=(int*)malloc(sizeof(int)*n);
    for(int j=0;j<n;j++){
        scanf("%d",&available[j]);
        available2[j]=available[j];
    }
    
    
    //��ʼ������
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
    
    // ����״̬
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            max2[i][j]=max[i][j];
            need2[i][j]=need[i][j];
        }
    }
    for(int j=0;j<n;j++){
        finish2[j]=finish[j];
    }

    
    //���÷������Դ
    int* request=(int *)malloc(sizeof(int)*n);
    int resourceType=1;
    int isSafe=1;
    char x='y';
   
    while (x=='y') {
        printf("����Ҫ����Ľ��̺ţ���ע����1�����̺�Ϊ0���Դ����ƣ�\n");
        scanf("%d",&resourceType);
        printf("�������������ĸ���Դ������\n");
        for(int j=0;j<n;j++){
            scanf("%d",&request[j]);
        }
        
        bankerAlgorithm(request,resourceType,need,available,allocation,finish,sequence,&seqIndex,m,n);
        for(int i=0;i<m;i++){
            if(finish[i]==0) isSafe=0;
        }
        if(isSafe==0){
            printf("Ϊ����p%d����(%d,%d,%d,%d)����Դʱ����ȫ\n",resourceType,request[0],request[1],request[2],request[3]);
            
        }else{
            printf("Ϊ����p%d����(%d,%d,%d,%d)����Դʱ��ȫ\n",resourceType,request[0],request[1],request[2],request[3]);
            //Ϊ���̷���һ�ΰ�ȫ����Դ
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
        
            printf("��ȫ�����ǣ�");
            
        }
        
        //�������
        for(int i=0;i<m-1;i++){
            printf("%d->",sequence[i]);
        }
        printf("%d\n",sequence[m-1]);
        
        //״̬�ع�
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
        
        //ѯ���Ƿ��������
        printf("�㻹���ٴ����������(����y����)\n");
        getchar();
        scanf("%c",&x);
        
    }
    
    return 0;
}
