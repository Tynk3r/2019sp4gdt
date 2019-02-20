#include "UIBase.h"

class UIMenuButton : public UIBase
{
public:
	UIMenuButton(const std::string& text, float x = 0, float y = 0);
	~UIMenuButton();

	virtual void Update(float dt);
private:
	//Order of ui components matter
	enum UI_STARTBUTTON_COMPONENTS {
		COMPONENT_OUTLINEBAR,

		COMPONENT_GREYBAR,

		COMPONENT_TOTAL
	};
};