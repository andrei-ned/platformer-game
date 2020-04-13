#pragma once
#include "Sprite.h"


// Animates the sprite component attached to game object
class SpriteAnimator : public Component
{
public:
	class Animation 
	{
	public:
		Animation(std::vector<RECT> frames, float secsPerFrame, ID3D11ShaderResourceView* texturePtr = nullptr, bool loop = true);
		~Animation();

		bool mLoop;
		bool mIsPlaying;
		float mSecsPerFrame;
		// Texture containing the sprite sheet with the animation, leave as nullptr to use Sprite's texture
		ID3D11ShaderResourceView *mpTexture;

		// Get next frame and increment index
		RECT cycleFrame();
		RECT getCurrentFrame();
		void play();
	private:
		std::vector<RECT> mFrames;
		unsigned int mCurrentFrameIndex;
	};

	bool mIsPlaying;

	SpriteAnimator(GameObject& gameObject);
	~SpriteAnimator() override;

	void start() override;
	void update(const float deltaTime) override;

	void addAnimation(std::string name, Animation animation);
	void removeAnimation(std::string name);
	void playAnimation(std::string name);
	void playAnimation(Animation* animationPtr);
	Animation* getAnimation(std::string name);
	void setSpeed(float secsPerFrame);
private:
	Sprite* mpSprite;
	float mElapsedSecs;
	std::unordered_map<std::string, Animation> mAnimations;
	Animation* mpCurrentAnimation;
};

