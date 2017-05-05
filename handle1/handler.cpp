/*************************************************************************
	> File Name: handler.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2017年04月16日 星期日 10时31分49秒
 ************************************************************************/
#include <cmath>
#include <cctype>
#include <cstdlib>
#include<iostream>
#include <cstdio>
#include <algorithm>
using namespace std;


class Point{
	public:
		Point(): xval(0), yval(0){}
		Point(int x, int y): xval(x), yval(y){}
		int x(){return xval;}
		int y(){return yval;}
		Point& x(int xv) {xval = xv; return *this;}
		Point& y(int yv) {yval = yv; return *this;}
	private:
		int xval, yval;
};

class uPoint{
	friend class Handle;
	Point p;
	int ref;
	uPoint(): ref(1){}
	uPoint(int x, int y): p(x, y), ref(1){}
	uPoint(Point& p0): p(p0), ref(1){}
};

class Handle{
	public:
		Handle(): up(new uPoint()){}
		Handle(int x, int y): up(new uPoint(x, y)){}
		Handle(Point& p0): up(new uPoint(p0)) {}
		Handle(Handle& h): up(h.up){h.up->ref++;}
		~Handle(){
			if (--up->ref == 0)
				delete up;
		}
		Handle& operator=(const Handle& h){
			++h.up->ref;
			if (--up->ref == 0){
				delete up;
			}
			up = h.up;
			return *this;
		}
		int x(){return up->p.x();}
		int y(){return up->p.y();}
		Handle& x(int xv){
			writeOncopy();
			up->p.x(xv);
			return *this;
		}
		Handle& y(int xv){
			writeOncopy();
			up->p.x(xv);
			return *this;
		}
	private:
		uPoint* up;
		void writeOncopy(){
			if (up->ref != 1){
				up->ref--;
				up = new uPoint(up->p);
			}
		}
};

int main(int argc, char** argv){
	Handle h(3, 4);
	Handle h2 = h;
	h2.x(5);
	cout << h.x() << endl;
	cout << h2.x() << endl;
	return 0;
}
