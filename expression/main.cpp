#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include "exper.h"
using namespace std;

int main(){
	Expr test = Expr("*", Expr(1), Expr(2));
	Expr next = Expr(test, Expr(2), Expr(1));
	cout << next << endl;
	cout << next.eval() << endl;
	return 0;
}