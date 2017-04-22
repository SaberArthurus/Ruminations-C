#include <iostream>
using namespace std;

template<class T> class Array;
template<class T> class ArrayData;


template<class T> class Ptr_to_const {
	friend class Array<T>;
	friend class ArrayData<T>;
public:
	Ptr_to_const(const Array<T>& a, unsigned n = 0):
		ap(a.data), 	
		sub(n) { ++ap->use; }

	Ptr_to_const(): ap(0), sub(0) { }

	Ptr_to_const(const Ptr_to_const<T>& p): 
		ap(p.ap), sub(p.sub) 
	{
		if (ap)
			++ap->use;
	}

	~Ptr_to_const() 
	{
		if (ap && --ap->use == 0)
			delete ap;
	}

	Ptr_to_const& operator=(const Ptr_to_const<T>& p) 
	{
		if (p.ap)
			++p.ap->use;
		if (ap && --ap->use == 0)
			delete ap;
		ap = p.ap;
		sub = p.sub;
		return *this;
	}

	const T& operator*() const 
	{
		if (ap == 0) 
			throw "* of unbound Ptr_to_const";
		return (*ap)[sub];
	}

protected:
	ArrayData<T>* ap;
	unsigned sub;
};

template<class T> class Pointer: public Ptr_to_const<T> {
	friend class Array<T>;
	friend class ArrayData<T>;
public:
	Pointer(Array<T>& a, unsigned n = 0):
		Ptr_to_const<T>(a,n) { }
	T& operator*() const 
	{
		if (Ptr_to_const<T>::ap == 0) 
			throw "* of unbound Ptr_to_const";
		return (*(Ptr_to_const<T>::ap))[Ptr_to_const<T>::sub];
	}
};

template<class T>
class Array{
	friend class Pointer<T>;
	friend class ArrayData<T>;
	friend class Ptr_to_const<T>;
public:
	Array():data(0), size(0){}
	Array(unsigned n): data(new ArrayData<T>(n)), size(n){}
	T operator[](unsigned sz)const{
		if (sz >= size || !data)
			throw "out of bounded";
		return (*data)[sz];
	}
	T& operator[] (int sz){
		if (sz >= size || !data)
			throw "out of bounded";
		return (*data)[sz];
	}
	~Array(){
		if (data && --data->use == 0)
			delete data;
	}
private:
	unsigned size;
	ArrayData<T>* data;
	Array& operator=(const Array<T>&);
	Array(const Array<T>&);
};


template<class T>
class ArrayData{
	friend class Array<T>;
	friend class Pointer<T>;
	friend class Ptr_to_const<T>;
	ArrayData(unsigned n):data(new T[n]), size(n), use(1){}
	~ArrayData(){delete[] data;}
	const T& operator[](unsigned n)const{
		if (n >= size)
			throw "out of range";
		return data[n];
	}
	T& operator[](unsigned n){
		if (n >= size)
			throw "out of range";
		return data[n];
	}
	void resize(unsigned );
	void copy(T*, unsigned);
	void grow(unsigned);
	void clone(const ArrayData&, unsigned);
	ArrayData(const ArrayData<T>&);
	ArrayData<T>& operator=(const ArrayData<T>&);
	T* data;
	unsigned size;
	int use;
};