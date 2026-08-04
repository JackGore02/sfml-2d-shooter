#include "Sprite.h"
#include "../System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "RenderManager.h"

Sprite::Sprite()
	:m_bInitialised(false)
	,isHUDObject(false)
{
}

Sprite::~Sprite()
{
	if (this->isHUDObject)
	{
		C_SysContext::Get<RenderManager>()->RemoveHUDRenderObject(this);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
	}
}

void Sprite::Initialise(const char* filename, sf::Color spriteColor, sf::Vector2f spriteScale)
{
	auto* pAssetManager = C_SysContext::Get<AssetManager>();
	setTexture(pAssetManager->GetTexture(filename));

	setColor(spriteColor);
	setScale(spriteScale);

	m_bInitialised = true;

	if (this->isHUDObject)
	{
		C_SysContext::Get<RenderManager>()->AddHUDRenderObject(this);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	}
	
}
