#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BI_TileView

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "b1MinusManaged_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass BI_TileView.BI_TileView_C
// 0x0010 (0x0468 - 0x0458)
class UBI_TileView_C final : public b1MinusManaged::UGSTileView
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0458(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UGSTileViewPanel*                       ItemTileView;                                      // 0x0460(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void PreConstruct(bool IsDesignTime);
	void ExecuteUbergraph_BI_TileView(int32 EntryPoint);
	void Construct();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BI_TileView_C">();
	}
	static class UBI_TileView_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBI_TileView_C>();
	}
};
//static_assert(alignof(UBI_TileView_C) == 0x000008, "Wrong alignment on UBI_TileView_C");
//static_assert(sizeof(UBI_TileView_C) == 0x000468, "Wrong size on UBI_TileView_C");
//static_assert(offsetof(UBI_TileView_C, UberGraphFrame) == 0x000458, "Member 'UBI_TileView_C::UberGraphFrame' has a wrong offset!");
//static_assert(offsetof(UBI_TileView_C, ItemTileView) == 0x000460, "Member 'UBI_TileView_C::ItemTileView' has a wrong offset!");

}
