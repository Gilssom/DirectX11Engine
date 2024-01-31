#pragma once

#define SINGLE(Type)	private:\
							Type();\
							Type(const Type& _origin) = delete;\
						public:\
							~Type();\
							friend class CSingleton<Type>; // 부모 쪽에서도 사용 가능하게

// #define 의 함수 재정의 는 " ; " 를 붙이지 않는다.
#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;