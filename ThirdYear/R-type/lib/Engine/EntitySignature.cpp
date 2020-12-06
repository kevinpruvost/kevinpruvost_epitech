#include "EntitySignature.hpp"

using namespace RType::Common::Engine;

EntitySignature::EntitySignature()
{
}

EntitySignature::~EntitySignature()
{
}

void EntitySignature::AddComponentSignature(ComponentSignature id) { insert(id); }

void EntitySignature::RemoveComponentSignature(ComponentSignature id) { erase(id); }

void EntitySignature::SetSignature(EntitySignature& signature) { *this = signature; }

bool EntitySignature::operator&(const EntitySignature& signature) const
{
    for (const auto & compSign : *this)
    {
        if (signature.find(compSign) == signature.end())
            return false;
    }
    return true;
}

bool EntitySignature::operator|(const EntitySignature& signature) const
{
    for (const auto& compSign : *this)
    {
        if (signature.find(compSign) != signature.end())
            return true;
    }
    return false;
}
