#include "array.h"


template<class T>
void ArrayData<T>::resize(unsigned n)
{
	if (n == size)
		return ;
	T* odata = data;
	data = new T[n];
	copy(odata, size > n ? n : size);
	delete[] odata;
	size = n;// nothing
}

template<class T>
void ArrayData<T>::copy(T* arr,unsigned n){
	for (int i = 0; i < n; ++ i)
		data[i] = arr[i];
}

template<class T>
void ArrayData<T>::grow(unsigned sz){
	unsigned nsz = sz;
	if (nsz == 0) nsz = 1;
	while (nsz <= sz) nsz *= 2;
	resize(nsz);
}

template<class T>
void ArrayData<T>::clone(const ArrayData& a, unsigned n){
	delete[] data;
	new  T[size = a.size];
	copy(a.data, size);
}



