#include<bits/stdc++.h>
using namespace std;
typedef long long L;
typedef pair<int,int> PII;
const int N=256;
const int M=2*N-1;//结点总数
map<char,string> mp;
map<string,char> mp1;
vector<char> CH;
vector<int> NUM;
struct HTNode{
    float weight;
    char code;
    int parent;
    int lchild,rchild;
};
HTNode HT[M+1];
class HuffmanTree{
public:
    char** c;

    priority_queue<PII> Q;
    L tot;
public:
    HuffmanTree(char *fname);
    void ReadTxt(char* fname);
    void init();//初始化
    void HuffmanCoding();
    void select(int i);
    //void Show();
    void writetofile(char* fname);
};
void HuffmanTree::writetofile(char* fname)
{
    ifstream fin(fname,ios::binary);
    string s(fname);
    ofstream fout((s+".cod").c_str(),ios::binary);
    char k;
    while(fin.read((char*)&k,sizeof(char)))
    {
        //fout.write(reinterpret_cast<char*>(&c[k]),sizeof(c[k]));
        fout<<mp[k];
    }
    fin.close();
    fout.close();
    return;
}/*
void HuffmanTree::Show()
{
    int n=NUM.size();
    for(int i=0;i<n;i++)
    {
        cout<<i<<"  weight:"<<NUM[i]<<" ASCII:"<<CH[i]<<" Code:"<<mp[HT[i].code]<<endl;
    }
}*/
void HuffmanTree::select(int i)
{
    PII s1,s2,s;
    s1=Q.top();
    Q.pop();
    s2=Q.top();
    Q.pop();
    HT[s1.second].parent=i;
    HT[s2.second].parent=i;
    HT[i].lchild=s1.second;
    HT[i].rchild=s2.second;
    s.second=i;
    s.first=s1.first+s2.first;
    Q.push(s);
    //cout<<"$$$$$$$$$$$$$$"<<HT[0].lchild<<endl;
}
void HuffmanTree::HuffmanCoding()
{
    int s1,s2,f;
    int n=NUM.size();
    int m=2*n-1;

    for(int i=n;i<=m-1;i++)//构建哈夫曼树
    {
        select(i);
    }
    //建立哈弗曼编码
    c =new char*[n];
    //char* cd = new char[n];
    string cd;
    for(int i=0;i<n;i++)
    {
        int start=n-1;
        cd[start]='\0';
        for(int k=i,f=HT[i].parent;f!=-1;k=f,f=HT[f].parent)//提炼出每个字符的编码
        {
            if(HT[f].lchild==k) cd[--start]='0';
            else    cd[--start]='1';
        }
       // int MM=n-start;
       // cout<<MM<<endl;
        c[i]=new char[n];
        for(int j=0;j<n-start;j++)//所以字符的编码
            c[i][j]=cd[j+start];
        mp[HT[i].code]=c[i];
        mp1[c[i]]=HT[i].code;
        //cout<<mp1[c[i]]<<endl;
        //cout<<"***********"<<HT[i].code<<":  "<<mp[HT[i].code]<<endl;
    }
    //delete[] cd;
}
HuffmanTree::HuffmanTree(char* fname)
{

    ReadTxt(fname);
    init();
    HuffmanCoding();
    //Show();
    writetofile(fname);
}

void HuffmanTree::init()
{
    while(!Q.empty())
        Q.pop();
    int n=NUM.size();
    for(int i=0;i<n;i++)
    {
        Q.push(make_pair(-NUM[i],i));
        HT[i].weight=NUM[i];
        HT[i].code=CH[i];
    }
    for(int i=0;i<M;i++)
    {
        HT[i].weight=0;
        HT[i].parent=-1;
        HT[i].lchild=-1;
        HT[i].rchild=-1;
    }
}
void HuffmanTree::ReadTxt(char* fname)
{
    char k;
    ifstream fin(fname,ios::binary);
    while(!fin)
    {
        //cout<<"文件错误！请输入正确的文件名称！"<<endl;
        cin>>fname;
        fin.open(fname);
    }

    int cont[N]={0};
    tot=0;
    while(fin.read((char*)&k,sizeof(char)))
    {
        cont[k]++;
        tot++;
    }

    for(int i=0;i<N;i++)
    {
        if(!cont[i])    continue;
        NUM.push_back(cont[i]);//权值存在NUM数组中
        CH.push_back(i);//字符所对应的ASCII存在CH数组中
    }
    fin.close();
};
class HuffmanDecode{
public:
    HuffmanDecode(char* fname)
    {
        int n=NUM.size();
        int m=2*n-1;
        ifstream fin(fname,ios::binary);
        while(!fin)
        {
            //cout<<"文件打开失败！请重新输入：";
            cin>>fname;
            fin.open(fname);
        }
        char name[100];
        char t;
        int len=strlen(fname);
        for(int i=0;i<len-4;i++)
            name[i]=fname[i];
        ofstream fout(name,ios::binary);
        int i=m-1,j=0;
        char s[100];
        while(fin.read((char*)&t,sizeof(char)))
        {
            //cout<<t<<endl;
            if((HT[i].lchild!=-1)||(HT[i].rchild!=-1))
            {
                s[j++]=t;
                if(t=='0')
                    i=HT[i].lchild;
                else
                    i=HT[i].rchild;
                if((HT[i].lchild==-1)||(HT[i].rchild==-1))
                {
                    s[j]='\0';
                    char w=mp1[s];
                    //cout<<s<<"     "<<w<<endl;
                    fout.write((char*)&w,sizeof(char));
                    j=0;
                    i=m-1;
                }


            }
        }
        fin.close();
        fout.close();
    }
};
int main()
{
    char fname[100];
    cout<<"输出要编码的文件：";
    cin>>fname;
    HuffmanTree H(fname);
    cout<<"编码成功！"<<endl;
    cout<<"输出要译码的文件：";
    cin>>fname;
    HuffmanDecode D(fname);
    cout<<"译码成功！"<<endl;
    return 0;
}
