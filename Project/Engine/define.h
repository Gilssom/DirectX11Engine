#pragma once

#define SINGLE(Type)	private:\
							Type();\
							Type(const Type& _origin) = delete;\
						public:\
							~Type();\
							friend class CSingleton<Type>; // �θ� �ʿ����� ��� �����ϰ�

// #define �� �Լ� ������ �� " ; " �� ������ �ʴ´�.
#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;