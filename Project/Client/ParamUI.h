#pragma once

// Parameter 를 수정할 수 있는 함수만 모아놓는 Class
class ParamUI
{
private:
	static UINT g_ParamUI_ID;
	static int	g_DescWidth;

public:
	static void ResetParamID() { g_ParamUI_ID = 0; }
	static void SetDescWidth(int DescWidth) { g_DescWidth = DescWidth + 10; }

	// 접근성이 좋게 정적 멤버 함수로 작성
public:
	static int Param_DragInt(const string& strName, int* pInOut, int speed = 1);
	static int Param_DragFloat(const string& strName, float* pInOut, float speed = 1.f);
	static int Param_DragVec2(const string& strName, Vec2* pInOut, float speed = 1.f);
	static int Param_DragVec4(const string& strName, Vec4* pInOut, float speed = 1.f);
	static int Param_DragMat(const string& strName, Matrix* pInOut, float speed = 1.f);

	static int Param_Texture(const string& strName, Ptr<CTexture> texture);
};