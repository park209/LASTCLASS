//Line.h

#ifndef _LINE_H
#define _LINE_H

typedef signed long int Long;

class Line {
public:
	Line();
	Line(Long startX, Long startY, Long endX, Long endY);
	Line(const Line& source);
	Line& operator = (const Line& source);
	~Line();

	Long GetStartX() const;
	Long GetStartY() const;
	Long GetEndX() const;
	Long GetEndY() const;
private:
	Long startX;
	Long startY;
	Long endX;
	Long endY;
};

inline Long Line::GetStartX() const {
	return this->startX;
}
inline Long Line::GetStartY() const {
	return this->startY;
}
inline Long Line::GetEndX() const {
	return this->endX;
}
inline Long Line::GetEndY() const {
	return this->endY;
}

#endif // _LINE_H
