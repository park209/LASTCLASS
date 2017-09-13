
//Figure.h

#ifndef _FIGURE_H //가드선언
#define _FIGURE_H

typedef signed long int Long;

class Figure {
public:
	Figure();
	//Figure(Long x, Long y, Long width, Long height);
	Figure(const Figure& source);
	Figure& operator = (const Figure& source);
	virtual ~Figure() = 0;

	//virtual void Accept(Visitor& visitor) = 0;// , CDC *cPaintDc) = 0;
	virtual Figure* Clone() const = 0;

	Long GetX() ;
	Long GetY() ;
	Long GetWidth() ;
	Long GetHeight() ;
protected:
	Long x;
	Long y;
	Long width;
	Long height;
};

inline Long Figure::GetX()  {
	return this->x;
}
inline Long Figure::GetY()  {
	return this->y;
}
inline Long Figure::GetWidth()  {
	return this->width;
}
inline Long Figure::GetHeight()  {
	return this->height;
}

#endif //_FIGURE_H
