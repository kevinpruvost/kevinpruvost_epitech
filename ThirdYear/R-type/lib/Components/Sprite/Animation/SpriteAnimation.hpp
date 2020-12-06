#pragma once

#include "Engine/RComponent.hpp"
#include "lib/Chronometer.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class SpriteAnimation : public RComponent
    {
        RCOMPONENT_MANDATORIES(SpriteAnimation)

    public:

        SpriteAnimation(REngine & engine);
        ~SpriteAnimation();

        void stopAnimationLoop();
        void resetAnimation();
        void stopAndResetAnimation();
        void startAnimationLoop();
        void resumeAnimationLoop();

        void stopAnimationAtFirstFrame();
        void stopAnimationAtLastFrame();

        void animateToRight();
        void animateToLeft();

        void startChrono();
        float getChronoTime();

        void Update() override;

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

    public:
        /**
         * @brief Animations per seconds.
         */
        float animationRate = 0.2f;
        bool animationLooped = true;
        unsigned char animationIndex = 0;
        AnimationBoucle boucle = AnimationBoucle::DontStop;
        AnimationDirection sens = AnimationDirection::ToRight;
        Chronometer chrono;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
