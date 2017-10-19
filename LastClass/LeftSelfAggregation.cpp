//LeftSelfAggregation.cpp

#include "LeftSelfAggregation.h"

LeftSelfAggregation::LeftSelfAggregation() :LeftSelfRelation() {

}

LeftSelfAggregation::LeftSelfAggregation(Long x, Long y, Long width, Long height) : LeftSelfRelation(x, y, width, height) {

}

LeftSelfAggregation::LeftSelfAggregation(const LeftSelfAggregation& source) : LeftSelfRelation(source) {

}

LeftSelfAggregation& LeftSelfAggregation::operator=(const LeftSelfAggregation& source) {
	LeftSelfAggregation::operator=(source);
	return *this;
}

LeftSelfAggregation::~LeftSelfAggregation() {

}

Figure* LeftSelfAggregation::Clone() const {
	return new LeftSelfAggregation(*this);
}

void LeftSelfAggregation::Accept(Visitor& visitor, CDC *pDC) {
	//visitor.Visit(this, pDC);
}
