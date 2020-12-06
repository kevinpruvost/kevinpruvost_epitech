#pragma once

// Project includes
#include "RAccess.hpp"
#include "REngine.hpp"

// C++ includes
#include <functional>

#define RCOMPONENT_MANDATORIES(className) \
    public : \
        virtual std::string ClassName() override { _className = typeid(className).name(); return _className; } \
        virtual Rfc::ComponentTypeId GetComponentTypeId() override { return _engine.get().GetComponentTypeId<className>(); } \
        virtual size_t GetComponentSize() override { return _engine.get().GetComponentSize(*this); }

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Component derivation that aims to be a simplified version of Component
     * to handle.
     */
    class RComponent : public Component, public RAccess
    {
        RCOMPONENT_MANDATORIES(RComponent)

    public:
        RComponent(REngine & engine);
        ~RComponent();

        virtual void Start() override;
        virtual void Update() override;
        virtual void Tick() override;
        virtual void UpdateEngine() final override;
        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;
        virtual RType::Common::Udp::Entities::UpdateRequest CreateUpdateRequest();

        template<typename T>
        T& GetComponent(size_t index = 0) const
        {
            try {
                return _engine.get().GetComponent<T>(entityId, index);
            } catch (const MinorException& e) {
                std::cerr << e.what() << std::endl;
                throw MINOR_EXCEPTION("");
            }
        }

        template<typename T>
        std::weak_ptr<T> GetComponentPtr(size_t index = 0) const
        {
            try {
                return _engine.get().GetComponentPtr<T>(entityId, index);
            }
            catch (const MinorException& e) {
                std::cerr << e.what() << std::endl;
                throw MINOR_EXCEPTION("");
            }
        }
};
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
