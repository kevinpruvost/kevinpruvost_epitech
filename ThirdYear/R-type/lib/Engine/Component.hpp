#pragma once

// Project includes
#include "IComponent.hpp"
#include "IEntity.hpp"

#include "Network/BinaryStructure.hpp"

// C++ includes
#include <vector>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Component base class used by the ComponentArray.
     */
    class Component : virtual public IComponent
    {
    public:
        Component();
        Component(const ComponentId id);
        ~Component();

        /**
         * @brief Compares the components ids.
         * @return bool
         */
        bool operator==(const Component & comp) { return id == comp.id; };

        virtual void Start() override;
        virtual void Update() override;
        virtual void Tick() override;
        virtual void UpdateEngine() override;
        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest);
        virtual RType::Common::Udp::Entities::UpdateRequest CreateUpdateRequest();

        /**
         * Gets the class name. Its main purpose is for derived classes.
         *
         * \return
         */
        virtual std::string ClassName() override;

        virtual Rfc::ComponentTypeId GetComponentTypeId() override { return Rfc::ComponentTypeId::Audio; }
        virtual size_t GetComponentSize() override { return sizeof(Component); }

    public:
        bool started = false;

    public:
        ComponentId id;
        EntityId entityId;

    protected:
        std::string _className;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
