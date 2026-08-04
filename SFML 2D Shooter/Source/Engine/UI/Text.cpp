#include "Text.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"

Text::Text()
	:m_Initialised(false)
{

}

Text::~Text()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void Text::Initialise(const char* fontfilename, std::string text, int charsize, sf::Color textcolor)
{
	const auto pAssetManager = C_SysContext::Get<AssetManager>();
	setFont(*pAssetManager->GetFont(fontfilename));

	
	setString(text); //Set the Text
	setCharacterSize(charsize); // in pixels, not points!
	setFillColor(textcolor);
	m_normalFillColor = textcolor;
	m_normalOutlineColor = sf::Color(m_normalFillColor.r * 0.5f, m_normalFillColor.g * 0.5f, m_normalFillColor.b * 0.5f);
	setOutlineThickness(charsize * 0.05f);
	setOutlineColor(m_normalOutlineColor);

	C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	m_Initialised = true;
}


