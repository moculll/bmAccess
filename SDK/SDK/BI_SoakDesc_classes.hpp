#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BI_SoakDesc

#include "Basic.hpp"

#include "b1MinusManaged_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass BI_SoakDesc.BI_SoakDesc_C
// 0x0018 (0x0578 - 0x0560)
class UBI_SoakDesc_C final : public UBUI_ButtonNone
{
public:
	class UWidgetAnimation*                       AKBMatSlotState;                                   // 0x0560(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UImage*                                 ImgDot;                                            // 0x0568(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UGSImage*                               ImgNew;                                            // 0x0570(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BI_SoakDesc_C">();
	}
	static class UBI_SoakDesc_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBI_SoakDesc_C>();
	}
};
//static_assert(alignof(UBI_SoakDesc_C) == 0x000008, "Wrong alignment on UBI_SoakDesc_C");
//static_assert(sizeof(UBI_SoakDesc_C) == 0x000578, "Wrong size on UBI_SoakDesc_C");
//static_assert(offsetof(UBI_SoakDesc_C, AKBMatSlotState) == 0x000560, "Member 'UBI_SoakDesc_C::AKBMatSlotState' has a wrong offset!");
//static_assert(offsetof(UBI_SoakDesc_C, ImgDot) == 0x000568, "Member 'UBI_SoakDesc_C::ImgDot' has a wrong offset!");
//static_assert(offsetof(UBI_SoakDesc_C, ImgNew) == 0x000570, "Member 'UBI_SoakDesc_C::ImgNew' has a wrong offset!");

}
