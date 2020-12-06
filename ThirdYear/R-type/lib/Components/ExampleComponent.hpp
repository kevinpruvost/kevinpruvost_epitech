#pragma once

#include "Engine/RComponent.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Example Component class.
     */
    class ExampleComponent : public RComponent
    {

        RCOMPONENT_MANDATORIES(RComponent)

    public:
        ExampleComponent(REngine & engine);
        ~ExampleComponent();

        void Start() override;
        void Update() override;
        void Tick() override;
        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest ud) override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
