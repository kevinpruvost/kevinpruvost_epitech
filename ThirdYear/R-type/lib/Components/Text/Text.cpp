#include "Text.hpp"

using namespace RType::Common::Engine;

Text::Text(REngine& engine)
    : RComponent(engine)
{

}

Text::~Text()
{
}

void Text::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    text = updateRequest.text.text;
    fontName = updateRequest.text.fontName;
    fontSize = updateRequest.text.fontSize;
    fontColor = updateRequest.text.fontColor;
}