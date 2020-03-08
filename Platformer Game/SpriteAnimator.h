#pragma once
#include "Sprite.h"

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
		// Texture containing the sprite sheet with the animation, leave as nullptr to use Sprite's texture
		ID3D11ShaderResourceView *mpTexture;

		// Get next frame and increment index
		RECT cycleFrame();
		RECT getCurrentFrame();
		float getSecsPerFrame() const;
		void play();
	private:
		std::vector<RECT> mFrames;
		unsigned int mCurrentFrameIndex;
		float mSecsPerFrame;
	};

	bool mIsPlaying;

	SpriteAnimator(GameObject& gameObject);
	~SpriteAnimator();

	void start() override;
	void update(const float deltaTime) override;
	Animation* addAnimation(std::string name, Animation animation);
	void removeAnimation(std::string name);
	void playAnimation(std::string name);
	void playAnimation(Animation* animationPtr);
	Animation* addAndPlayAnimation(std::string name, Animation animation);
	Animation* getAnimation(std::string name);

private:
	Sprite* mpSprite;
	float mElapsedSecs;
	std::unordered_map<std::string, Animation> mAnimations;
	Animation* mpCurrentAnimation;
};

