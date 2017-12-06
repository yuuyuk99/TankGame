#include "SceneBase.h"
#include "SceneManager.h"
#include <d3d11.h>

SceneBase::SceneBase(std::shared_ptr<SceneManager> changer)
{
	//ƒV[ƒ“‚Ì•ÏX
	m_SceneChanger = changer;
}

SceneBase::~SceneBase()
{

}