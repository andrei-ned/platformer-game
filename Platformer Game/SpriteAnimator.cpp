#include "SpriteAnimator.h"
#include "GameObject.h"


SpriteAnimator::SpriteAnimator(GameObject& gameObject) : Component(gameObject), mElapsedSecs(0)
{
}


SpriteAnimator::~SpriteAnimator()
{
}

void SpriteAnimator::start()
{
	mpSprite = mpGameObject->getComponent<Sprite>();
}

void SpriteAnimator::update(const float deltaTime)
{
	if (!mIsPlaying || !mpCurrentAnimation)
		return;
	if (!mpCurrentAnimation->mIsPlaying)
		return;
	mElapsedSecs += deltaTime;
	if (mElapsedSecs > mpCurrentAnimation->mSecsPerFrame)
	{
		mpSprite->setTextureRect(mpCurrentAnimation->cycleFrame());
		mElapsedSecs -= mpCurrentAnimation->mSecsPerFrame;
	}
}

SpriteAnimator::Animation* SpriteAnimator::addAnimation(std::string name, Animation animation)
{
	mAnimations.insert({ name, animation });
	return &animation;
}

void SpriteAnimator::removeAnimation(std::string name)
{
	auto search = mAnimations.find(name);
	if (search != mAnimations.end())
	{
		if (&(*search).second == mpCurrentAnimation)
			mpCurrentAnimation = nullptr;
		mAnimations.erase(search);
	}
}

void SpriteAnimator::playAnimation(std::string name)
{
	auto search = mAnimations.find(name);
	assert(search != mAnimations.end());
	playAnimation(&(*search).second);
}

void SpriteAnimator::playAnimation(Animation* animationPtr)
{
	if (animationPtr == mpCurrentAnimation)
		return;
	mpCurrentAnimation = animationPtr;
	// If animation has a texture, update the sprite
	if (mpCurrentAnimation->mpTexture)
		mpSprite->setTexture(*mpCurrentAnimation->mpTexture);
	mpCurrentAnimation->play();
	mpSprite->setTextureRect(mpCurrentAnimation->getCurrentFrame());
	mIsPlaying = true;
	mElapsedSecs = 0;
}

void SpriteAnimator::setSpeed(float secsPerFrame)
{
	assert(secsPerFrame > 0);
	mpCurrentAnimation->mSecsPerFrame = secsPerFrame;
}

SpriteAnimator::Animation* SpriteAnimator::addAndPlayAnimation(std::string name, Animation animation)
{
	Animation* animPtr = addAnimation(name, animation);
	playAnimation(animPtr);
	return animPtr;
}

SpriteAnimator::Animation* SpriteAnimator::getAnimation(std::string name)
{
	auto search = mAnimations.find(name);
	if (search != mAnimations.end())
	{
		return &(*search).second;
	}
	return nullptr;
}

SpriteAnimator::Animation::Animation(std::vector<RECT> frames, float secsPerFrame, ID3D11ShaderResourceView* texturePtr, bool loop)
	: mFrames(frames), mSecsPerFrame(secsPerFrame), mpTexture(texturePtr), mLoop(loop), mIsPlaying(true), mCurrentFrameIndex(0)
{}

SpriteAnimator::Animation::~Animation() {}

RECT SpriteAnimator::Animation::cycleFrame()
{
	assert(mFrames.size() > 0);
	mCurrentFrameIndex++;
	if (mCurrentFrameIndex >= mFrames.size())
	{
		if (mLoop)
			mCurrentFrameIndex = 0;
		else
			mIsPlaying = false;
	}
	return mFrames.at(mCurrentFrameIndex);
}

RECT SpriteAnimator::Animation::getCurrentFrame()
{
	assert(mFrames.size() > 0);
	return mFrames.at(mCurrentFrameIndex);
}

void SpriteAnimator::Animation::play()
{
	mIsPlaying = true;
	mCurrentFrameIndex = 0;
}
