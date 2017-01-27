#include<iostream.h>
#include<math.h>
#include <string>
#include <vector>
#include <fstream>
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;

//const double INFINITY = 1e10;
const double ESP = 1e-5;
const int MAX_N = 1000;
//�����
struct Point
{
    double x, y;
};
//�����

struct LineSegment
{
    Point pt1, pt2;
};

typedef vector<Point> Polygon;


// ������ |P0P1| �� |P0P2|
double Multiply(Point p1, Point p2, Point p0)
{
    return ( (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y) );
}

// �ж��߶��Ƿ������point
bool IsOnline(Point point, LineSegment line)
{
    return( ( fabs(Multiply(line.pt1, line.pt2, point)) < ESP ) &&
            ( ( point.x - line.pt1.x ) * ( point.x - line.pt2.x ) <= 0 ) &&
            ( ( point.y - line.pt1.y ) * ( point.y - line.pt2.y ) <= 0 ) );
}

// �ж��߶��ཻ
bool Intersect(LineSegment L1, LineSegment L2)
{
    return( (max(L1.pt1.x, L1.pt2.x) >= min(L2.pt1.x, L2.pt2.x)) &&
            (max(L2.pt1.x, L2.pt2.x) >= min(L1.pt1.x, L1.pt2.x)) &&
            (max(L1.pt1.y, L1.pt2.y) >= min(L2.pt1.y, L2.pt2.y)) &&
            (max(L2.pt1.y, L2.pt2.y) >= min(L1.pt1.y, L1.pt2.y)) &&
            (Multiply(L2.pt1, L1.pt2, L1.pt1) * Multiply(L1.pt2, L2.pt2, L1.pt1) >= 0) &&
            (Multiply(L1.pt1, L2.pt2, L2.pt1) * Multiply(L2.pt2, L1.pt2, L2.pt1) >= 0)
          );
}

// �жϵ��ڶ������
bool InPolygon(Polygon & polygon, Point point)
{
    int n = polygon.size();
    int count = 0;
    LineSegment line;
    line.pt1 = point;
    line.pt2.x = point.x;
    line.pt2.y = - INFINITY;

    for( int i = 0; i < n; i++ )
    {
        // �õ�����ε�һ����
        LineSegment side;
        side.pt1 = polygon[i];
        side.pt2 = polygon[(i + 1) % n];
        //�ж���֪���Ƿ��ڱ���
        if( IsOnline(point, side) )
        {
            return 1 ;
        }

        // ���sideƽ��y����������
        if( fabs(side.pt1.x - side.pt2.x) < ESP )
        {
            continue;
        }

        if( IsOnline(side.pt1, line) )
        {
            if( side.pt1.x > side.pt2.x ) count++;
        }
        else if( IsOnline(side.pt2, line) )
        {
            if( side.pt2.x> side.pt1.x ) count++;
        }
        else if( Intersect(line, side) )
        {
            count++;
        }
    }

    if ( count % 2 == 1 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}




//�����ļ�����
vector<string> split(string str,string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}


//��ʼ�����ݣ����������)

Polygon initData()
{
    char *filePath = "E:\\aaa.txt";
    ifstream file;
    file.open(filePath,ios::in);

    if(!file.is_open()){
    	cout<<"��ȡ�ļ�ʧ��"<<endl;
    	exit(0);
    }
        

    std::string strLine;
    Polygon poly;
    while(getline(file,strLine))
    {

        if(strLine.empty())
            continue;
        vector<string>result=split(strLine,",");
        Point pt;
        pt.x=atof(result[0].c_str());
        pt.y=atof(result[1].c_str());
        poly.push_back(pt);

    }
    return poly;
}

//****************************************************************
int main()
{
    //���ݳ�ʼ����ɺ�����ݼ�
    Polygon p=initData();
    //��ʼ��Ҫ�жϵ�����(1000���㣬ѭ������1000��)
    double x=116.301707;
    double y=39.928721;
    clock_t start, end;
    start = clock();
    for(int i=0; i<1000; i++)
    {
        Point pt1;
        pt1.x=x+0.005;
        pt1.y=y+0.1;
        x=pt1.x;
        y=pt1.y;
        bool retur;
        retur=InPolygon(p, pt1);
        if(retur==1)
            cout<<"���ڶ�����⣡"<<endl;
        else
            cout<<"���ڶ�����ڣ�"<<endl;

    }
    end=clock();
    cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;
    /*
    int n;
    double x,y;

    Point pt1;
    cout<<"������һ�㣺"<<endl;
    cin>>x>>y;
    pt1.x=x;
    pt1.y=y;
    cout<<"������Ϊ��("<<pt1.x<<","<<pt1.y<<")"<<endl;

    Polygon poly;
    cout<<"���������εı�����"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
    	double m,j;
    	cout<<"�������"<<i+1<<"���㣺"<<endl;
    	cin>>m>>j;
    	Point pt;
    	pt.x=m;
    	pt.y=j;
    	poly.push_back(pt);
    }

    //cout<<"����εı���"<<poly.size()<<endl;
    clock_t start, end;
    start = clock();
    bool retur;
    retur=InPolygon(poly, pt1);
    if(retur==1)
    	cout<<"���ڶ�����⣡"<<endl;
    else
    	cout<<"���ڶ�����ڣ�"<<endl;
     end=clock();
     cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;*/
     getchar();
    return 0;
}
