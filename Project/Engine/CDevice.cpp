#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
	: m_hMainHwnd(nullptr)
	, m_RenderResolution{}
{
	
}

CDevice::~CDevice()
{
}

int CDevice::Init(HWND hwnd, POINT resolution)
{
	m_hMainHwnd = hwnd;
	m_RenderResolution = resolution;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), &level, m_Context.GetAddressOf()))) // GetAddressOf() ��� ���� ���������� ��ȯ
	{
		return E_FAIL;
	}

	// Swap Chain
	if (FAILED(CreateSwapChain()))
	{
		return E_FAIL;
	}

	// View
	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}

	// View Port ����
	// ������ ȭ�鿡 ������ ������ �����Ѵ�.
	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = m_RenderResolution.x;
	viewPort.Height = m_RenderResolution.y;

	// ���� �ؽ�ó�� ����Ǵ� ���� Min ~ Max ���� ( 0.f ~ 1.f )
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;

	// ViewPort ���� ����
	m_Context->RSSetViewports(1, &viewPort);

	return S_OK;
}

void CDevice::ClearTarget(float(&ArrColor)[4])
{
	m_Context->ClearRenderTargetView(m_RTV.Get(), ArrColor);

	// Depth Stencil ���� �ڽ��� ���� ������ ���� ������ ��ü�鸸 �׷���
	// �׷��� Depth Stencil View �� �ʱⰪ�� 1�� �ʱ�ȭ �ؾ� ��
	m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_DEPTH, 1.f, 0);
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};

	// Swap Chain ��� ������
	desc.OutputWindow = m_hMainHwnd;
	desc.Windowed = true; // â���

	// RenderTarget �ؽ����� �ػ� ����
	desc.BufferCount = 1; // �����Ǵ� ������� ���� ( API �� ������۸� ������ ����� ���� )
	desc.BufferDesc.Width = m_RenderResolution.x;
	desc.BufferDesc.Height = m_RenderResolution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32bit
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	desc.BufferDesc.RefreshRate.Denominator = 1; // �θ�
	desc.BufferDesc.RefreshRate.Numerator = 60;  // �и� = 60 ( ��� ���� )
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // �⺻ �ɼ�
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // �⺻ �ɼ�

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	ComPtr<IDXGIDevice>  pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	ComPtr<IDXGIFactory> pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	// Swap Chain ����
	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &desc, m_SwapChain.GetAddressOf())))
		return E_FAIL;

	return S_OK;
}

int CDevice::CreateView()
{
	// RenderTarget View
	// �׷��Ƚ� ������������ ���ؼ� ���� ����Ÿ�� �ؽ��Ŀ� �׷���� �Ѵ�.
	// �߰��� ������ ������ �ִ� �Ű�ü (������ ����)
	
	// 1. RenderTarget �� �ؽ��ĸ� SwapChain ���κ��� �����;� �Ѵ�. �̹� �ִ� �������̶� �����ϴ�. (������ ����)
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RenderTargetTex.GetAddressOf());

	// 2. ����Ÿ�� �ؽ��ĸ� �̿��ؼ� ����Ÿ�� �並 �����.
	m_Device->CreateRenderTargetView(m_RenderTargetTex.Get(), nullptr, m_RTV.GetAddressOf());


	// DepthStencil View : ���ο� �ؽ��ĸ� ����� ���� �Ѵ�.
	// 1. DepthStencil Texture ���� ( RenderTarget Tex �� 1:1 �����̿��� �Ѵ�. )
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 32bit / 3byte = depth , 1byte = stencil
	desc.Width = m_RenderResolution.x;
	desc.Height = m_RenderResolution.y;
	desc.ArraySize = 1; // �迭 �ؽ�ó
	
	// ���� �ؽ�ó�� �ý��� �󿡼� ������ �Ұ����ϱ� ������ ������
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// ���𰡸� ������ִ� ������ Device ����
	m_Device->CreateTexture2D(&desc, nullptr, &m_DepthStencilTex);

	// 2. DepthStencil View �� �����Ѵ�.
	// ���⼭ RenderTarget , DepthStencil View �� �ʿ��ϴ�.
	m_Device->CreateDepthStencilView(m_DepthStencilTex.Get(), nullptr, m_DSV.GetAddressOf());

	// Swap Chain �� �ؽ�ó�� ����Ÿ������ �����ϰ�, 
	// ���� ���� DepthStencil �� �ؽ�ó�� ���� ����� �ؽ�ó�� �����Ѵ�.
	m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get()); // ���� �ؽ��Ĵ� ������ �ϳ��ۿ� ���� ���� ������ ���������ͷ� �ȳѱ��.
	
	// ���⼭ DepthStencil View ��?
	// Api ���� ���� ���۸� �ý������� ȭ�鿡 �ؽ�ó�� �׷��ִ� ����� �־���.
	// ���� ���� �׷�����, ���� �Ŀ� �׷����� ���� �������༭ ������ �����ϴ� ����� ����ߴ�.
	// ������ ���̷�Ʈ������ ���� 2d �ϻ� ��ǥ��� 3d �̴�.
	// ���� ��ǥ�� (���簢��) ���� ���� �տ� �ְ� �ڿ� �ִ����� Ȯ���� �� �ִ�.
	// DepthStencil View �� Ȱ���ؼ� ���� ���� Ÿ���� �����Ͽ�
	// �ش� �ؽ�ó�� stencil ���� ���� ������ �������ֱ� ������ �׷� ���ŷο��� �������� �ȴ�.

	// ShaderResource View
	// UnorderedAccess View

	return S_OK;
}
