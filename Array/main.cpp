#include <cstdio>
#include <iostream>
#include "array.h"
using namespace std;

int main(int argc, char** argv){
	Array<int>* ap = new Array<int>(10);
	Pointer<int> p(*ap, 5);
	delete ap;
	*p = 45;
	cout << *p << endl;

}