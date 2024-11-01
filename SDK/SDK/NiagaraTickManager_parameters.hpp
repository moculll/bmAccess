#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: NiagaraTickManager

#include "Basic.hpp"


namespace SDK::Params
{

// Function NiagaraTickManager.NiagaraTickWorldSubsystem.OnComponentActivated
// 0x0010 (0x0010 - 0x0000)
struct NiagaraTickWorldSubsystem_OnComponentActivated final
{
public:
	class UActorComponent*                        Component;                                         // 0x0000(0x0008)(Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bReset;                                            // 0x0008(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_9[0x7];                                        // 0x0009(0x0007)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(NiagaraTickWorldSubsystem_OnComponentActivated) == 0x000008, "Wrong alignment on NiagaraTickWorldSubsystem_OnComponentActivated");
//static_assert(sizeof(NiagaraTickWorldSubsystem_OnComponentActivated) == 0x000010, "Wrong size on NiagaraTickWorldSubsystem_OnComponentActivated");
//static_assert(offsetof(NiagaraTickWorldSubsystem_OnComponentActivated, Component) == 0x000000, "Member 'NiagaraTickWorldSubsystem_OnComponentActivated::Component' has a wrong offset!");
//static_assert(offsetof(NiagaraTickWorldSubsystem_OnComponentActivated, bReset) == 0x000008, "Member 'NiagaraTickWorldSubsystem_OnComponentActivated::bReset' has a wrong offset!");

}

