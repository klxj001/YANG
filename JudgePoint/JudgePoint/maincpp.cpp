#include<iostream.h>
#include<math.h>
#include <vector>
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;

const double INFINITY = 1e10;
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
	return ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
}

// �ж��߶��Ƿ������point 
bool IsOnline(Point point, LineSegment line)
{
	return((fabs(Multiply(line.pt1, line.pt2, point)) < ESP) &&
		((point.x - line.pt1.x) * (point.x - line.pt2.x) <= 0) &&
		((point.y - line.pt1.y) * (point.y - line.pt2.y) <= 0));
}

// �ж��߶��ཻ 
bool Intersect(LineSegment L1, LineSegment L2)
{
	return((max(L1.pt1.x, L1.pt2.x) >= min(L2.pt1.x, L2.pt2.x)) &&
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
	line.pt2.y = -INFINITY;

	for (int i = 0; i < n; i++) {
		// �õ�����ε�һ���� 
		LineSegment side;
		side.pt1 = polygon[i];
		side.pt2 = polygon[(i + 1) % n];
		//�ж���֪���Ƿ��ڱ���
		if (IsOnline(point, side)) {
			return 1;
		}

		// ���sideƽ��y���������� 
		if (fabs(side.pt1.x - side.pt2.x) < ESP) {
			continue;
		}

		if (IsOnline(side.pt1, line))
		{
			if (side.pt1.x > side.pt2.x) count++;
		}
		else if (IsOnline(side.pt2, line))
		{
			if (side.pt2.x> side.pt1.x) count++;
		}
		else if (Intersect(line, side))
		{
			count++;
		}
	}

	if (count % 2 == 1) { return 0; }
	else { return 1; }
}



//****************************************************************
void main()
{
	int n;
	double x, y;

	Point pt1;
	cout << "������һ�㣺" << endl;
	cin >> x >> y;
	pt1.x = x;
	pt1.y = y;
	cout << "������Ϊ��(" << pt1.x << "," << pt1.y << ")" << endl;

	Polygon poly;
	cout << "���������εı�����" << endl;
	cin >> n;
	for (int i = 0;i<n;i++)
	{
		double m, j;
		cout << "�������" << i + 1 << "���㣺" << endl;
		cin >> m >> j;
		Point pt;
		pt.x = m;
		pt.y = j;
		poly.push_back(pt);
	}

	//cout<<"����εı���"<<poly.size()<<endl;
	bool retur;
	retur = InPolygon(poly, pt1);
	if (retur == 1)
		cout << "���ڶ�����⣡" << endl;
	else
		cout << "���ڶ�����ڣ�" << endl;

}
