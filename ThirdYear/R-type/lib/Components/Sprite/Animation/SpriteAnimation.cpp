#include "SpriteAnimation.hpp"

using namespace RType::Common::Engine;

SpriteAnimation::SpriteAnimation(REngine& engine)
    : RComponent(engine)
{

}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Update()
{
    if (boucle == AnimationBoucle::DontStop)
        animationLooped = true;
}

void SpriteAnimation::resumeAnimationLoop()
{
    animationLooped = true;
}

void SpriteAnimation::startAnimationLoop()
{
    animationLooped = true;
}

void SpriteAnimation::stopAndResetAnimation()
{
    animationLooped = false;
}

void SpriteAnimation::stopAnimationLoop()
{
    animationLooped = false;
}

void SpriteAnimation::animateToRight()
{
    sens = AnimationDirection::ToRight;
}

void SpriteAnimation::animateToLeft()
{
    sens = AnimationDirection::ToLeft;
}

void SpriteAnimation::stopAnimationAtFirstFrame()
{
    boucle = AnimationBoucle::StopAtFirstFrame;
}

void SpriteAnimation::stopAnimationAtLastFrame()
{
    boucle = AnimationBoucle::StopAtLastFrame;
}

void SpriteAnimation::startChrono()
{
    chrono.start();
}

float SpriteAnimation::getChronoTime()
{
    return chrono.getPastTimeInSeconds();
}

void SpriteAnimation::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    animationRate = updateRequest.spriteAnimation.animationRate;
    animationLooped = updateRequest.spriteAnimation.animationLooped;
    animationIndex = updateRequest.spriteAnimation.animationIndex;
    boucle = updateRequest.spriteAnimation.boucle;
    sens = updateRequest.spriteAnimation.sens;
}