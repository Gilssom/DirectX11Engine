#include "pch.h"
#include "CBackGroundScript.h"

CBackGroundScript::CBackGroundScript()
	: m_Intence(0.f)
{

}

CBackGroundScript::~CBackGroundScript()
{

}

void CBackGroundScript::Tick()
{
	// Dissolve Shader Effect
	//m_Intence += DT * 0.3f;
	//GetRenderComponent()->GetMaterial()->SetScalarParam(FLOAT_0, m_Intence);
}