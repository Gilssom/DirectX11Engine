#pragma once

// 데이터 영역 메모리 : 전역 변수
// 프로세스 시작할 때 초기화
// 프로세스 종료 시 해제
// 프로세스가 실행 도중 상시 유지되는 메모리

//class CEngine
//{
//private:
//	// 전체를 통 틀어서 하나만
//	static CEngine* m_This;
//
//public:
//	// 정적 멤버함수 : 객체가 업어도 호출 가능
//	static CEngine* GetInst() // 싱글톤 패턴
//	{
//		// 정적 멤버함수에서 접근할 수 있는 변수는 정적 변수
//		if (m_This == nullptr)
//		{
//			m_This = new CEngine;
//		}
//
//		return m_This;
//	}
//
//	static void Destroy()
//	{
//		if (m_This != nullptr)
//		{
//			delete m_This;
//			// 삭제된 곳은 무조건 nullptr 로 다시 채워주기
//			m_This = nullptr;
//		}
//	}
//
//private:
//	CEngine();
//};

class CEngine
{
private:
	HWND	m_hMainHwnd;
	POINT	m_Resolution;

public:
	int Init(HWND hwnd, POINT resolution);

	void Progress();

public:
	static CEngine* GetInst()
	{
		// 데이터 영역의 메모리라 프로세스 종료 시 메모리 해제 됨
		// 하지만 도중에는 메모리 해제가 불가능하다.
		static CEngine mgr;
		return &mgr;
	}

private:
	CEngine();
	// 복사 생성자 삭제로 싱글톤 객체가 추가적으로 생성되는 것을 방지
	CEngine(const CEngine& _origin) = delete;
};