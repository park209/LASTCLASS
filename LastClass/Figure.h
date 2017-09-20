//Figure.h

#ifndef _FIGURE_H //���弱��
#define _FIGURE_H

#include <string>
using namespace std;

typedef signed long int Long;

class Figure {
public:
	Figure();
	Figure(Long x, Long y, Long width, Long height);
	Figure(Long x, Long y, Long width, Long height, string content);
	Figure(const Figure& source);
	Figure& operator = (const Figure& source);
	virtual ~Figure() = 0;

	//virtual void Accept(Visitor& visitor) = 0;// , CDC *cPaintDc) = 0;
	virtual Figure* Clone() const = 0;
	void ReplaceString(string content);
	Figure* Move(Long distanceX, Long distanceY);
	Figure* EndPointMove(Long distanceX, Long distanceY);

	Figure* Modify(Long x, Long y, Long width, Long height);

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
	string& GetContent() const;
protected:
	Long x;
	Long y;
	Long width;
	Long height;
	string content;
};

inline Long Figure::GetX() const {
	return this->x;
}
inline Long Figure::GetY() const {
	return this->y;
}
inline Long Figure::GetWidth() const {
	return this->width;
}
inline Long Figure::GetHeight() const {
	return this->height;
}
inline string& Figure::GetContent() const {
	return const_cast<string&>(this->content);
}

#endif //_FIGURE_H
