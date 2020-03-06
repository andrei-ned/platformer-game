#pragma once
#include "Sprite.h"

class SpriteAnimator : public Component
{
public:
	SpriteAnimator(GameObject& gameObject);
	~SpriteAnimator();

	//void update(const float deltaTime) override;

	class Animation 
	{
	public:
		//Animation();
		//Animation(std::vector<RECT> frames);
		//Animation(std::vector<RECT> frames, float secsPerFrame);
		//~Animation();
		std::vector<RECT> mFrames;
		float mSecsPerFrame;
		//RECT cycleFrame();
	private:
		int mCurrent;
	};
private:
	Sprite* mpSprite;
	float mElapsed;
};

