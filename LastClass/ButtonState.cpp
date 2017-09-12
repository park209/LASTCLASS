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
ButtonState::ButtonState() {

}

ButtonState::ButtonState(const ButtonState& source) {

}

ButtonState::~ButtonState() {

}

void ButtonState::ChangeState(DrawingController *drawingController, Long key) {
	if (key == 0) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new Unclicked;
	}
	if (key == 1) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new ClassButton;
	}
	if (key == 2) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new GeneralizationButton;
	}
	if (key == 3) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new RealizationButton;
	}
	if (key == 4) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new DependencyButton;
	}
	if (key == 5) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new AssociationButton;
	}
	if (key == 6) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new DirectAssociationButton;
	}
	if (key == 7) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new AggregationButton;
	}
	if (key == 8) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new AggregationsButton;
	}
	if (key == 9) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new CompositionButton;
	}
	if (key == 10) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new CompositionsButton;
	}
	if (key == 11) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new TemplateButton;
	}
	if (key == 12) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new MemoBoxButton;
	}
}

void ButtonState::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {

}

ButtonState& ButtonState::operator=(const ButtonState& source) {
	return const_cast<ButtonState&>(source);
}