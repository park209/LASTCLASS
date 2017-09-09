//FigureFactory.h
#ifndef _FIGUREFACTORY_H
#define _FIGUREFACTORY_H

typedef signed long int Long;
class Figure;
class FigureFactory {
public:
	FigureFactory();
	~FigureFactory();
	Figure* Create(Long x, Long y, Long width, Long height, Long type);
};

#endif // !_FIGUREFACTORY_H

