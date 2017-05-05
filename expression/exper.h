#include <iostream>
#include <string>
using namespace std;

class Expr;

class ExprNode{
	friend class Expr;
	friend ostream& operator<<(ostream&, const Expr&);
	int use;
	protected:
		ExprNode():use(1){}
		virtual int eval()const = 0;
		virtual void print(ostream&) const = 0;
		virtual ~ExprNode() { }
};

class Expr{
	friend class ExprNode;
	friend ostream& operator<<(ostream& o, const Expr&);
	public:
		Expr(int n);
		Expr(const string& str, Expr val);
		Expr(const string& str, Expr left, Expr right);
		Expr(Expr, Expr, Expr);
		Expr(const Expr& t) { p = t.p; ++p->use; } // for initial
		~Expr(){ if (--p->use == 0) delete p; }
		Expr& operator=(const Expr&);
		int eval() const;
		ExprNode* p;
};


class IntNode: public ExprNode{
	friend class Expr;
	public:
		IntNode(int k): n(k){}
		int eval() const;
		void print(ostream&) const;
		int n;
};

class Unary: public ExprNode{
	friend class Expr;
	public:
		Unary(const string& str, Expr a):
	op(str), opnd(a){}
		int eval() const;
		void print(ostream&) const;
		string op;
		Expr opnd;
};


class Binary: public ExprNode{
	friend class Expr;
	public:
		Binary(const string& str, Expr a, Expr b):
	op(str), left(a), right(b){}
		int eval() const;
		void print(ostream&) const;
		string op;
		Expr left;
		Expr right;
};

class Tenary: public ExprNode{
	friend class Expr;
	public:
		Tenary(Expr a, Expr b, Expr c):
			flag(a), left(b), right(c){}
		int eval() const;
		void print(ostream&) const;
		Expr flag;
		Expr left;
		Expr right;
};