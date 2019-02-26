#include "CalamityBase.h"

class CalamityBlizzard : public CalamityBase
{
public:
	CalamityBlizzard();
	~CalamityBlizzard();

	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();
private:
	enum CALAMITY_EARTHQUAKE_STATE {
		STATE_NONE,
		STATE_STARTING,
		STATE_INTENSE,
		STATE_STOPPING
	};
	CALAMITY_EARTHQUAKE_STATE state;
	float fUIPopupTime;
	float fEffectTimer_BlizzardCloud;
};