#include "Scroll.h"
#include "ClassDiagramForm.h"
Scroll::Scroll(ClassDiagramForm *classDiagramForm) {
	this->classDiagramForm = classDiagramForm;
	this->scrollBar = new CScrollBar;
}
Scroll::Scroll(const Scroll& source) {
	this->classDiagramForm = source.classDiagramForm;
	this->scrollBar = source.scrollBar;
}
Scroll::~Scroll() {
	if (this->scrollBar != 0) {
		delete this->scrollBar;
	}
}
void Scroll::ScrollAction(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

}

Scroll& Scroll::operator=(const Scroll& source) {
	if (this->scrollBar != NULL) {
		delete this->scrollBar;
	}
	this->classDiagramForm = source.classDiagramForm;
	this->scrollBar = source.scrollBar;
	return *this;
}