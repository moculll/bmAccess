#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BI_RoleLevel

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "b1MinusManaged_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass BI_RoleLevel.BI_RoleLevel_C
// 0x0050 (0x0428 - 0x03D8)
class UBI_RoleLevel_C final : public UBUI_Widget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x03D8(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UWidgetAnimation*                       MinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinus; // 0x03E0(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       AKBInfoState;                                      // 0x03E8(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       GSAKBShowHide;                                     // 0x03F0(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UBI_AttrBase_V2_C*                      BI_RoleAttr_1;                                     // 0x03F8(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UBI_AttrBase_V2_C*                      BI_RoleAttr_2;                                     // 0x0400(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UCanvasPanel*                           ExpBar;                                            // 0x0408(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 ImgLine;                                           // 0x0410(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UGSProcBar*                             ProgBar;                                           // 0x0418(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 ProgBG;                                            // 0x0420(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void PreConstruct(bool IsDesignTime);
	void ExecuteUbergraph_BI_RoleLevel(int32 EntryPoint);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BI_RoleLevel_C">();
	}
	static class UBI_RoleLevel_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBI_RoleLevel_C>();
	}
};
//static_assert(alignof(UBI_RoleLevel_C) == 0x000008, "Wrong alignment on UBI_RoleLevel_C");
//static_assert(sizeof(UBI_RoleLevel_C) == 0x000428, "Wrong size on UBI_RoleLevel_C");
//static_assert(offsetof(UBI_RoleLevel_C, UberGraphFrame) == 0x0003D8, "Member 'UBI_RoleLevel_C::UberGraphFrame' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, MinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinus) == 0x0003E0, "Member 'UBI_RoleLevel_C::MinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinusMinus' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, AKBInfoState) == 0x0003E8, "Member 'UBI_RoleLevel_C::AKBInfoState' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, GSAKBShowHide) == 0x0003F0, "Member 'UBI_RoleLevel_C::GSAKBShowHide' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, BI_RoleAttr_1) == 0x0003F8, "Member 'UBI_RoleLevel_C::BI_RoleAttr_1' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, BI_RoleAttr_2) == 0x000400, "Member 'UBI_RoleLevel_C::BI_RoleAttr_2' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, ExpBar) == 0x000408, "Member 'UBI_RoleLevel_C::ExpBar' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, ImgLine) == 0x000410, "Member 'UBI_RoleLevel_C::ImgLine' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, ProgBar) == 0x000418, "Member 'UBI_RoleLevel_C::ProgBar' has a wrong offset!");
//static_assert(offsetof(UBI_RoleLevel_C, ProgBG) == 0x000420, "Member 'UBI_RoleLevel_C::ProgBG' has a wrong offset!");

}

