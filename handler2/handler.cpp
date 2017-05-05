/*************************************************************************
	> File Name: handler.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2017年04月16日 星期日 10时55分08秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>
using namespace std;

class Point{
	public:
		Point(): xval(0), yval(0){}
		Point(int x, int y): xval(x), yval(y){}
		int x(){return xval;}
		int y(){return yval;}
		Point& x(int xv){xval = xv; return *this;}
		Point& y(int yv){yval = yv; return *this;}
	private:
		int xval, yval;
};

class UserCount{
	public:
		UserCount(): p(new int(1)){}
		UserCount(const UserCount& u): p(u.p){++ *p;}
		~UserCount(){
			if (--*p == 0){
				delete p;
			}
		}
		bool only(){
			return *p == 1;
		}
		bool makeonly(){
			if (!only()){
				--*p;
				p = new int(1);
				return true;
			}
			return false;
		}
		bool reattch(const UserCount& u){
			++ (*u.p);
			if (--*p == 0){
				delete p;
				p = u.p;
				return true;
			}
			p = u.p;
			return false;
		}
	private:
		int*p;
		UserCount& operator=(const UserCount&){}
};

class Handle{
	public:
	Handle(){}
	Handle(int x, int y): p(new Point(x, y)){}
	Handle(Point& p0): p(new Point(p0)){}
	Handle(const Handle& h): u(h.u), p(h.p){}
	Handle& operator= (const Handle& h){
		if (u.reattch(h.u)){
			delete p;
		}
		p = h.p;
		return *this;
	}
	~Handle(){
		if (u.only())
			delete p;
	}
	int x(){return p->x();}
	int y(){return p->y();}
	Handle& x(int xv){
		if (u.makeonly()){
			p = new Point(*p);
		}
		p->x(xv);
		return *this;
	}
	Handle& y(int yv){
		if (u.makeonly()){
			p = new Point(*p);
		}
		p->y(yv);
		return *this;
	}
	private:
		UserCount u;
		Point* p;
};


int main(){
	Handle h1(2, 3);
	Handle h2;
	h2 = h1;
	h1.x(10);
	cout << h1.x() << endl;
	cout << h2.x() << endl;
	return 0;
}


