#include "Sprite.hpp"

using namespace RType::Common::Engine;

Sprite::Sprite(REngine& engine)
    : RComponent(engine)
{

}

Sprite::~Sprite()
{
}

void Sprite::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    spriteName = updateRequest.sprite.spriteName;
    color = updateRequest.sprite.color;
}