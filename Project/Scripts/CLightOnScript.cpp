#include "pch.h"
#include "CLightOnScript.h"

#include <Engine\\CLight2D.h>

CLightOnScript::CLightOnScript()
	: CScript(SCRIPT_TYPE::LIGHTONSCRIPT)
	, m_Duration(0.33f)
{
	AddScriptProperty(PROPERTY_TYPE::VEC4, "Diffuse", &m_Diffuse);
	AddScriptProperty(PROPERTY_TYPE::FLOAT, "Duration", &m_Duration);
}

CLightOnScript::~CLightOnScript()
{

}

void CLightOnScript::Tick()
{
	if (m_Diffuse.x >= 1.f)
		return;

	tLightInfo tLight = Light2D()->GetLightInfo();
	m_Diffuse = tLight.Light.vDiffuse;
	m_Diffuse.x += DT * m_Duration;
	m_Diffuse.y = m_Diffuse.z = m_Diffuse.x;
	Light2D()->SetDiffuse(m_Diffuse);
}