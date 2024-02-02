#pragma once

class CConstBuffer;

class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice)

private:
	HWND					m_hMainHwnd;		// 출력 대상 윈도우
	POINT					m_RenderResolution; // 렌더링 타겟 해상도
	
	// ComPtr : 스마트포인터 ( 레퍼런스 관리 )
	// 직접 초기화를 할 필요가 없다. 클래스라서 생성자에서 직접 해주기 때문
	// 따라서 소멸자도 구현이 되어 있기 때문에 Release 를 직접 해줄 필요가 없다.
	// 포인터 주소를 넘겨주는 Get 함수와
	// 이중포인터 주소를 넘겨주는 GetAddressOf 함수가 구현되어 있다.
	ComPtr<ID3D11Device>			m_Device;		// GPU 메모리 할당, Dx11 관련 객체 생성			
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU 렌더링 관련 명령,
	ComPtr<IDXGISwapChain>			m_SwapChain;	// 렌더타겟 버퍼 소유, 화면에 최종 장면을 게시

	ComPtr<ID3D11Texture2D>			m_RenderTargetTex;
	ComPtr<ID3D11RenderTargetView>	m_RTV;

	ComPtr<ID3D11Texture2D>			m_DepthStencilTex;
	ComPtr<ID3D11DepthStencilView>  m_DSV;

	CConstBuffer*					m_CB[(UINT)CB_TYPE::END];

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();

public:
	int Init(HWND hwnd, POINT resolution);
	void ClearTarget(float(&ArrColor)[4]);
	void Present() { m_SwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	CConstBuffer* GetConstBuffer(CB_TYPE type) { return m_CB[(UINT)type]; }
};