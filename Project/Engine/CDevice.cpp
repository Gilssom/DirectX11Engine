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
		, m_Device.GetAddressOf(), &level, m_Context.GetAddressOf()))) // GetAddressOf() 멤버 변수 이중포인터 반환
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

	// View Port 설정
	// 윈도우 화면에 보여질 영역을 설정한다.
	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = m_RenderResolution.x;
	viewPort.Height = m_RenderResolution.y;

	// 깊이 텍스처에 저장되는 깊이 Min ~ Max 지정 ( 0.f ~ 1.f )
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;

	// ViewPort 정보 세팅
	m_Context->RSSetViewports(1, &viewPort);

	return S_OK;
}

void CDevice::ClearTarget(float(&ArrColor)[4])
{
	m_Context->ClearRenderTargetView(m_RTV.Get(), ArrColor);

	// Depth Stencil 에서 자신의 깊이 값보다 작은 값들의 물체들만 그려줌
	// 그래서 Depth Stencil View 의 초기값은 1로 초기화 해야 함
	m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_DEPTH, 1.f, 0);
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};

	// Swap Chain 출력 윈도우
	desc.OutputWindow = m_hMainHwnd;
	desc.Windowed = true; // 창모드

	// RenderTarget 텍스쳐의 해상도 설정
	desc.BufferCount = 1; // 생성되는 백버퍼의 갯수 ( API 의 더블버퍼링 렌더와 비슷한 개념 )
	desc.BufferDesc.Width = m_RenderResolution.x;
	desc.BufferDesc.Height = m_RenderResolution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32bit
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	desc.BufferDesc.RefreshRate.Denominator = 1; // 부모
	desc.BufferDesc.RefreshRate.Numerator = 60;  // 분모 = 60 ( 재생 비율 )
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // 기본 옵션
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // 기본 옵션

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

	// Swap Chain 생성
	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &desc, m_SwapChain.GetAddressOf())))
		return E_FAIL;

	return S_OK;
}

int CDevice::CreateView()
{
	// RenderTarget View
	// 그래픽스 파이프라인을 통해서 최종 렌더타겟 텍스쳐에 그려줘야 한다.
	// 중간에 정보를 전달해 주는 매개체 (전달자 역할)
	
	// 1. RenderTarget 용 텍스쳐를 SwapChain 으로부터 가져와야 한다. 이미 있는 정보들이라 간단하다. (포인터 형식)
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RenderTargetTex.GetAddressOf());

	// 2. 렌더타겟 텍스쳐를 이용해서 렌더타겟 뷰를 만든다.
	m_Device->CreateRenderTargetView(m_RenderTargetTex.Get(), nullptr, m_RTV.GetAddressOf());


	// DepthStencil View : 새로운 텍스쳐를 만들어 내야 한다.
	// 1. DepthStencil Texture 생성 ( RenderTarget Tex 와 1:1 비율이여야 한다. )
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 32bit / 3byte = depth , 1byte = stencil
	desc.Width = m_RenderResolution.x;
	desc.Height = m_RenderResolution.y;
	desc.ArraySize = 1; // 배열 텍스처
	
	// 깊이 텍스처는 시스템 상에서 접근이 불가능하기 때문에 꺼버림
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// 무언가를 만들어주는 역할은 Device 역할
	m_Device->CreateTexture2D(&desc, nullptr, &m_DepthStencilTex);

	// 2. DepthStencil View 를 생성한다.
	// 여기서 RenderTarget , DepthStencil View 가 필요하다.
	m_Device->CreateDepthStencilView(m_DepthStencilTex.Get(), nullptr, m_DSV.GetAddressOf());

	// Swap Chain 의 텍스처를 렌더타겟으로 지정하고, 
	// 새로 만든 DepthStencil 용 텍스처를 깊이 저장용 텍스처로 지정한다.
	m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get()); // 깊이 텍스쳐는 무조건 하나밖에 쓸수 없기 때문에 이중포인터로 안넘긴다.
	
	// 여기서 DepthStencil View 란?
	// Api 에서 더블 버퍼링 시스템으로 화면에 텍스처를 그려주는 방법이 있었다.
	// 누가 먼저 그려질지, 누가 후에 그려질지 각각 설정해줘서 렌더를 진행하는 방법을 사용했다.
	// 하지만 다이렉트에서는 말만 2d 일뿐 좌표계는 3d 이다.
	// 투영 좌표계 (직사각형) 에서 누가 앞에 있고 뒤에 있는지를 확인할 수 있다.
	// DepthStencil View 를 활용해서 깊이 렌더 타겟을 설정하여
	// 해당 텍스처의 stencil 값에 따라 렌더를 진행해주기 때문에 그런 번거로움이 없어지게 된다.

	// ShaderResource View
	// UnorderedAccess View

	return S_OK;
}
