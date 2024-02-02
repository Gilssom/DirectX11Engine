#pragma once

class CConstBuffer;

class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice)

private:
	HWND					m_hMainHwnd;		// ��� ��� ������
	POINT					m_RenderResolution; // ������ Ÿ�� �ػ�
	
	// ComPtr : ����Ʈ������ ( ���۷��� ���� )
	// ���� �ʱ�ȭ�� �� �ʿ䰡 ����. Ŭ������ �����ڿ��� ���� ���ֱ� ����
	// ���� �Ҹ��ڵ� ������ �Ǿ� �ֱ� ������ Release �� ���� ���� �ʿ䰡 ����.
	// ������ �ּҸ� �Ѱ��ִ� Get �Լ���
	// ���������� �ּҸ� �Ѱ��ִ� GetAddressOf �Լ��� �����Ǿ� �ִ�.
	ComPtr<ID3D11Device>			m_Device;		// GPU �޸� �Ҵ�, Dx11 ���� ��ü ����			
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU ������ ���� ���,
	ComPtr<IDXGISwapChain>			m_SwapChain;	// ����Ÿ�� ���� ����, ȭ�鿡 ���� ����� �Խ�

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