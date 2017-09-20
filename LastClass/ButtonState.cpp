//ButtonState.cpp
#include "Unclicked.h"
#include"ButtonState.h"
#include "ClassButton.h"
#include "DrawingController.h"
#include "RealizationButton.h"
#include "GeneralizationButton.h"
#include "DependencyButton.h"
#include "AssociationButton.h"
#include "DirectAssociationButton.h"
#include "AggregationButton.h"
#include "AggregationsButton.h"
#include "CompositionButton.h"
#include "CompositionsButton.h"
#include "TemplateButton.h"
#include "MemoBoxButton.h"
#include "MemoLineButton.h"
ButtonState::ButtonState() {

}

ButtonState::ButtonState(const ButtonState& source) {

}

ButtonState::~ButtonState() {

}

void ButtonState::ChangeState(DrawingController *drawingController, UINT nChar) {

	if (nChar == 48) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new Unclicked;
	}

	if (nChar == 49) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new ClassButton;
	}

	if (nChar == 50) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new GeneralizationButton;
	}

	if (nChar == 51) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new RealizationButton;
	}

	if (nChar == 52) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new DependencyButton;
	}

	if (nChar == 53) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new AssociationButton;
	}

	if (nChar == 54) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new DirectAssociationButton;
	}

	if (nChar == 55) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new AggregationButton;
	}

	if (nChar == 56) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new AggregationsButton;
	}

	if (nChar == 57) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new CompositionButton;
	}

	if (nChar == 113) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new CompositionsButton;
	}

	if (nChar == 119) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new TemplateButton;
	}

	if (nChar == 101) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new MemoBoxButton;
	}

	if (nChar == 114) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new MemoLineButton;
	}

}

Figure* ButtonState::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	return 0;
}
void ButtonState::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {

}
ButtonState& ButtonState::operator=(const ButtonState& source) {
	return const_cast<ButtonState&>(source);
}