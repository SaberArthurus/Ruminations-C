#include "exper.h"
#include <iostream>
#include <string>
using namespace std;


Expr::Expr(int n){
    p = new IntNode(n);
}

Expr::Expr(const string& op, Expr t){
    p = new Unary(op, t);
}

Expr::Expr(const string& op, Expr left, Expr right){
    p = new Binary(op, left, right);
}
Expr::Expr(Expr flag, Expr left, Expr right){
	p = new Tenary(flag, left, right);
}


Expr& Expr::operator=(const Expr& rhs) 
{
	rhs.p->use++;
	if (--p->use == 0) 
		delete p;
	p = rhs.p;
	return *this;
}
ostream&
operator<<(ostream& o, const Expr& t){
        t.p->print(o);
        return o;
}

int IntNode::eval() const{
	return this->n;
}
int Unary::eval() const {
	if (op == "-")
		return -opnd.eval();
	throw "error bad unary op";
}
int Binary::eval() const{
	if (op == "+") return left.eval() + right.eval();
	if (op == "-") return left.eval() - right.eval();
	if (op == "*") return left.eval() * right.eval();
	if (op == "/") return left.eval() / right.eval();
	throw "Bad op";
}

int Tenary::eval()const {
	if (flag.eval())
		return left.eval();
	else 
		return right.eval();
}

int Expr::eval()const{
	return p->eval();
}
void IntNode::print(ostream& o) const{
	o << n;
}
void Unary::print(ostream& o) const{
	o << op << opnd;
}
void Binary::print(ostream& o) const{
	o << left << op << right;
}

void Tenary::print(ostream& o)const{
	o << flag << "?" << left << ":" << right;
}

