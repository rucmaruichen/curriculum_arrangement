#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int ran_stu_num=2000;   //学生总数，这里先为定值
int total_class=0;   //共有total_class个班
struct A{
    int num;
    int eva;
    int curnum=0;
    int stu[100];  //存的是学生结构体数组下标
    string type;
    string coll;
}cla[3000];
struct B{
    int num;
    int volnum;
    int actnum=0;
    int vol[50];  //按照志愿顺序排，存的是班级结构体数组下标
    int whether[50]={0};
    int act[50];
    int count=0;
    string coll;
}stu[4000];
string total_coll[30]={"国际关系学院","农业与农村发展学院","外国语学院","国学院","经济学院","财政金融学院","商学院"
                ,"公共管理学院","信息学院","物理学系","马克思主义学院","信息资源管理学院","统计学院","劳动人事学院"
                ,"法学院","哲学院","社会与人口学院","新闻学院","历史学院","艺术学院","化学系","文学院"
                ,"环境学院","心理学系","教育学院","国际学院","中法学院","理学院"};   //28
typedef struct QNode{
    int data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
   QueuePtr front;
   QueuePtr rear;
}LinkQueue;
void InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(QueuePtr)malloc(sizeof (QNode));
    if(!Q.front) cout<<"OVERFLOW";
    Q.front->next=NULL;
}
void DestroyQueue(LinkQueue &Q){
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front=Q.rear;
    }
    cout<<"删除完毕";
}
void push(LinkQueue &Q,int e){
    QueuePtr p=(QueuePtr)malloc(sizeof (QNode));
    if(!p) cout<<"OVERFLOW";
    p->data=e; p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
}
void pop(LinkQueue &Q){
    if(Q.front==Q.rear) cout<<"ERROR";
    QueuePtr p=Q.front->next;
    Q.front->next=p->next;
    if(Q.rear==p) Q.rear=Q.front;
    free(p);
}
bool empty(LinkQueue Q){
    if(Q.front==Q.rear) return true;
    return false;
}
int front(LinkQueue Q){
    return Q.rear->data;
}
void printcoll()
{
    int num,count=0;
    cout<<"请输入学院号：";
    cin>>num;
    cout<<total_coll[num]<<":"<<endl;
    int temp[2000],j=0;
    for(int i=0;i<ran_stu_num;i++)
    {
        if(stu[i].coll==total_coll[num])
        {
            temp[j++]=stu[i].num;
            count++;
        }
    }
    sort(temp,temp+j);
    for(int i=0;i<j;i++)
        cout<<temp[i]<<" ";
    cout<<endl;
    cout<<"共："<<count<<"人"<<endl;
}
void printstu()
{
    int num;
    cout<<"请输入学生学号：";
    cin>>num;
    for(int i=0;i<ran_stu_num;i++)
    {
        if(stu[i].num==num)
        {
            cout<<"学号为："<<num<<" 学院为："<<stu[i].coll<<endl;
            cout<<"该生志愿填报的班级为："<<endl;
            for(int j=0;j<stu[i].volnum;j++)
            {
                cout<<cla[stu[i].vol[j]].num<<" ";
                if(stu[i].whether[j]) cout<<"选上了";
                else cout<<"未选上";
                cout<<endl;
            }
            cout<<"该生实际选上的班级为："<<endl;
            for(int j=0;j<stu[i].actnum;j++)
                cout<<cla[stu[i].act[j]].num<<" ";
            cout<<endl;
            break;
        }
    }
}
void printcla()  //可以通过输入一个班号，可以输出该班所有bidding了的学生以及最后派了的学生
{
    int num,whether_find=0;
    cout<<"请输入一个班号：";
    cin>>num;
    for(int i=0;i<total_class;i++)
    {
        if(cla[i].num==num)
        {
           whether_find=1;
           cout<<"选报该班的学生："<<endl;
           for(int j=0;j<ran_stu_num;j++)
           {
               for(int k=0;k<stu[j].volnum;k++)
               {
                   if(stu[j].vol[k]==i)
                   {
                       cout<<stu[j].num<<" ";
                       break;
                   }
               }
           }
           cout<<endl;
           cout<<"该班实际选上的学生："<<endl;
           for(int j=0;j<cla[i].curnum;j++)
               cout<<stu[cla[i].stu[j]].num<<" ";
           cout<<endl;
           break;
        }
    }
    if(whether_find==0)
        cout<<"输入的班号不存在"<<endl;
}
void menu()
{
    int button;
    cout<<"1 输入学院编号，可以打印该学院所有学生，按照学号排序"<<endl;
    cout<<"2 输入学号，可以检索该学生的信息，包括学号、所在学院，并输出该学生所有bidding的班号以及每个班是否被分配给该生"<<endl;
    cout<<"3 输入一个班号，可以输出该班所有bidding了的学生以及最后派了的学生"<<endl;
    cout<<"其它数字 退出程序"<<endl;
    cout<<"请输入一个数字来执行一个功能："<<endl;
    cin>>button;
    switch (button) {
    case 1:
        printcoll();
        menu();
        break;
    case 2:
        printstu();
        menu();
        break;
    case 3:
        printcla();
        menu();
        break;
    default:
        cout<<"退出成功"<<endl;
        break;
    }
}
int main(int argc, char *argv[])
{
    cout<<"欢迎来到雪落无声的选课系统"<<endl;
    cout<<"请输入模拟人数(2000-4000)"<<endl;
    cin>>ran_stu_num;
    std::ifstream ifs("C:/Users/DELL/Documents/print2016-2017class/courses.txt");
    string line;
    char ts1[150];
    char *t;
    string st1[10];
    int i=0,j=0,row=0;
    int eva=0,temp,k;
    if(ifs)
    {
        getline(ifs,line);
        while(getline(ifs,line))
        {
            row++;
            i=0; j=0;
            while(j<line.length())   //预处理数据，给空的地方填上NULL
            {
                if(line[j]=='\t'&&line[j+1]=='\t')
                {
                    line.replace(j+1,0,"NULL");
                }
                j++;
            }
            strncpy(ts1,line.c_str(),line.length()+1);
            t=strtok(ts1,"\t\r");
            while(t!=NULL)
            {
                st1[i]=t;
                i++;
                t=strtok(NULL,"\t\r");
            }
            stringstream ss;
            ss<<st1[2];
            ss>>eva;
            ss.clear();
           if(st1[6]=="2016-2017"&&st1[1]!="NULL"&&st1[5]!="NULL"&&eva!=0)
           {
               total_class++;
              cla[total_class-1].num=total_class;   //班号应该为row，但输入数字时班号不存在概率极高，所以这里改为total_class
              cla[total_class-1].eva=eva;
              cla[total_class-1].coll=st1[5];
              cla[total_class-1].type=st1[1];
           }
            eva=0;
        }
    }
    vector <int> V;
    for(i=0;i<ran_stu_num;i++)
        V.push_back(i+1);
    random_shuffle(V.begin(),V.end());
    int tag=0;   //标签，不要忘了归零，0代表没问题，1代表有问题
    for(i=0;i<ran_stu_num;i++)
    {
        stu[i].num=V[i];   //学生学号1-2000随机生成且不重复
        stu[i].volnum=rand()%46+5;  //学生志愿课程数5-50随机生成
        stu[i].coll=total_coll[i%28];   //现在不是随机生成学院了，而是按轮次分配，这样就保证了每个学院人数大于50
        for(j=0;j<stu[i].volnum;j++)
        {
            tag=0;
            temp=rand()%total_class;   //随机生成一个班
            for(k=0;k<j;k++)   //把当前学生选的班遍历一次，防止重复选同一个班
                if(stu[i].vol[k]==temp)
                {
                    tag=1;   //这个temp选过了
                    break;
                }
            while(tag==1||stu[i].coll!=cla[temp].coll&&(cla[temp].type=="学科基础"||cla[temp].type=="专业必修"||cla[temp].type=="专业选修"))
            {   //只要出现问题就重新生成新班
                tag=0;
                temp=rand()%total_class;
                for(k=0;k<j;k++)   //把当前学生选的班遍历一次，防止重复选同一个班
                    if(stu[i].vol[k]==temp)
                    {
                        tag=1;   //这个temp选过了
                        break;
                    }
            }
            stu[i].vol[j]=temp;  //把班级的数组下标分给学生志愿数组
        }
    }
    //至此，学生随机化完毕
//    for(i=0;i<ran_stu_num;i++)
//    {
//        cout<<stu[i].num<<" "<<stu[i].coll<<" "<<stu[i].volnum<<" ";
//        for(j=0;j<stu[i].volnum;j++)
//            cout<<stu[i].vol[j]<<" ";
//        cout<<endl;
//    }
    LinkQueue q;   //队列里存的是结构体数组下标
    InitQueue(q);

//   queue <int> q;
//队列里存的是结构体数组下标
    int dele_stu_num=0;  //已满足条件的学生
    while(1)
    {
        //先将队列清空
        while(!empty(q))
        {
            while(1)   //一定要给队首学生分配某个志愿的课
            {
                if(stu[front(q)].count==stu[front(q)].volnum)
                    break;
                if(cla[stu[front(q)].count].curnum<cla[stu[front(q)].count].eva)
                {
                    cla[stu[front(q)].vol[stu[front(q)].count]].stu[cla[stu[front(q)].vol[stu[front(q)].count]].curnum++]=front(q);
                    stu[front(q)].whether[stu[front(q)].count]=1;
                    stu[front(q)].act[stu[front(q)].actnum++]=stu[front(q)].vol[stu[front(q)].count++];
                    break;
                }
                else
                {
                    stu[front(q)].count++;
                }
            }
            pop(q);
        }
        for(i=0;i<ran_stu_num;i++)
        {
            if(stu[i].count==stu[i].volnum)   //该学生志愿已满足
            {
                dele_stu_num++;
                continue;
            }
            if(cla[stu[i].vol[stu[i].count]].curnum<cla[stu[i].vol[stu[i].count]].eva)
            {
                cla[stu[i].vol[stu[i].count]].stu[cla[stu[i].vol[stu[i].count]].curnum++]=i;
                stu[i].whether[stu[i].count]=1;
                stu[i].act[stu[i].actnum++]=stu[i].vol[stu[i].count++];
            }
            else
            {
                stu[i].count++;
                push(q,i);
            }
        }
        if(dele_stu_num==ran_stu_num)
            break;
        dele_stu_num=0;
    }
//    for(j=0;j<total_class;j++)
//    {
//    for(i=0;i<cla[j].curnum;i++)
//    {
//        cout<<cla[j].stu[i]<<" ";
//    }
//    cout<<endl;
//    }
//    for(i=0;i<ran_stu_num;i++)
//    {
//        for(j=0;j<stu[i].actnum;j++)
//            cout<<stu[i].act[j]<<" ";
//        cout<<endl;
//    }
//   cout<<total_class;
        menu();
        DestroyQueue(q);
    return 0;
}
