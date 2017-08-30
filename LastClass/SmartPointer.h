//SmartPointer.h
#ifndef _SMARTPOINTER_H
#define _SMARTPOINTER_H

class Figure;
template<typename Figure*>
class SmartPointer {
public:
	SmartPointer(Iterator<Figure*>* index);
	~SmartPointer() {
		delete index;
	}
	Iterater<T>*  operater->() {
		return index;
	}
	Iterater<T>& operater*() {
		return *index;
	}
private:
	SmartPointer(const SmartPointer& source);
	SmartPointer& operator=(const SmartPointer& source);
private:
	Iterator<T>* index;
};

#endif // !_SMARTPOINTER_H