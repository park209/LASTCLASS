//TextComponent.h

#ifndef _TEXTCOMPONENT_H
#define _TEXTCOMPONENT_H

class TextComponent {
public:
	TextComponent() {};
	TextComponent(const TextComponent& source) {};
	virtual ~TextComponent() {};

	virtual TextComponent* Clone() const = 0;

	void operator = (const TextComponent& source) {};
};

#endif // _TEXTCOMPONENT_H