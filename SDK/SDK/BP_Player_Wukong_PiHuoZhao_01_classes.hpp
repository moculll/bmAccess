#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_Player_Wukong_PiHuoZhao_01

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "b1MinusManaged_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BP_Player_Wukong_PiHuoZhao_01.BP_Player_Wukong_PiHuoZhao_01_C
// 0x0010 (0x0328 - 0x0318)
class ABP_Player_Wukong_PiHuoZhao_01_C final : public ABGUMagicFieldBaseCS
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0318(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class USphereComponent*                       CheckComp_Sphere;                                  // 0x0320(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData, NonTransactional, NoDestructor, HasGetValueTypeHash)

public:
	bool CheckDrawSignCondition(class AActor* HitActor);
	void ExecuteUbergraph_BP_Player_Wukong_PiHuoZhao_01(int32 EntryPoint);
	void OnDrawSign(class AActor* HitActor, const struct FTransform& HitTransform);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BP_Player_Wukong_PiHuoZhao_01_C">();
	}
	static class ABP_Player_Wukong_PiHuoZhao_01_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<ABP_Player_Wukong_PiHuoZhao_01_C>();
	}
};
//static_assert(alignof(ABP_Player_Wukong_PiHuoZhao_01_C) == 0x000008, "Wrong alignment on ABP_Player_Wukong_PiHuoZhao_01_C");
//static_assert(sizeof(ABP_Player_Wukong_PiHuoZhao_01_C) == 0x000328, "Wrong size on ABP_Player_Wukong_PiHuoZhao_01_C");
//static_assert(offsetof(ABP_Player_Wukong_PiHuoZhao_01_C, UberGraphFrame) == 0x000318, "Member 'ABP_Player_Wukong_PiHuoZhao_01_C::UberGraphFrame' has a wrong offset!");
//static_assert(offsetof(ABP_Player_Wukong_PiHuoZhao_01_C, CheckComp_Sphere) == 0x000320, "Member 'ABP_Player_Wukong_PiHuoZhao_01_C::CheckComp_Sphere' has a wrong offset!");

}
