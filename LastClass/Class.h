//Class.h
#ifndef _CLASS_H
#define _CLASS_H

typedef signed long int Long;
class Class {
public:
	Class();
	Class(Long x, Long y, Long width, Long height);
	Class(const Class& source);
	Class& operator = (const Class& source);
	~Class();
	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
private:
	Long x;
	Long y;
	Long width;
	Long height;
};
inline Long Class::GetX()const {
	return this->x;
}
inline Long Class::GetY()const {
	return this->y;
}
inline Long Class::GetWidth()const {
	return this->width;
}
inline Long Class::GetHeight()const {
	return this->height;
}

#endif // !_CLASS_H

