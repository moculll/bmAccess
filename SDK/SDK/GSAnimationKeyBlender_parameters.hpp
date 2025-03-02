#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GSAnimationKeyBlender

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "GSAnimationKeyBlender_structs.hpp"


namespace SDK::Params
{

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.BeforeInitAddBindingActor
// 0x0018 (0x0018 - 0x0000)
struct GSAnimKeyStateBlender_BeforeInitAddBindingActor final
{
public:
	class ALevelSequenceActor*                    RefLevelSequenceActor;                             // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   BindingActorTagName;                               // 0x0008(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class AActor*                                 InActor;                                           // 0x0010(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_BeforeInitAddBindingActor) == 0x000008, "Wrong alignment on GSAnimKeyStateBlender_BeforeInitAddBindingActor");
//static_assert(sizeof(GSAnimKeyStateBlender_BeforeInitAddBindingActor) == 0x000018, "Wrong size on GSAnimKeyStateBlender_BeforeInitAddBindingActor");
//static_assert(offsetof(GSAnimKeyStateBlender_BeforeInitAddBindingActor, RefLevelSequenceActor) == 0x000000, "Member 'GSAnimKeyStateBlender_BeforeInitAddBindingActor::RefLevelSequenceActor' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_BeforeInitAddBindingActor, BindingActorTagName) == 0x000008, "Member 'GSAnimKeyStateBlender_BeforeInitAddBindingActor::BindingActorTagName' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_BeforeInitAddBindingActor, InActor) == 0x000010, "Member 'GSAnimKeyStateBlender_BeforeInitAddBindingActor::InActor' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.DoTick
// 0x0004 (0x0004 - 0x0000)
struct GSAnimKeyStateBlender_DoTick final
{
public:
	float                                         DeltaTime;                                         // 0x0000(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_DoTick) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_DoTick");
//static_assert(sizeof(GSAnimKeyStateBlender_DoTick) == 0x000004, "Wrong size on GSAnimKeyStateBlender_DoTick");
//static_assert(offsetof(GSAnimKeyStateBlender_DoTick, DeltaTime) == 0x000000, "Member 'GSAnimKeyStateBlender_DoTick::DeltaTime' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.EasingToEndState
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlender_EasingToEndState final
{
public:
	float                                         Alpha;                                             // 0x0000(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          IsFromForceSetStateImmediately;                    // 0x0004(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_5[0x3];                                        // 0x0005(0x0003)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(GSAnimKeyStateBlender_EasingToEndState) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_EasingToEndState");
//static_assert(sizeof(GSAnimKeyStateBlender_EasingToEndState) == 0x000008, "Wrong size on GSAnimKeyStateBlender_EasingToEndState");
//static_assert(offsetof(GSAnimKeyStateBlender_EasingToEndState, Alpha) == 0x000000, "Member 'GSAnimKeyStateBlender_EasingToEndState::Alpha' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_EasingToEndState, IsFromForceSetStateImmediately) == 0x000004, "Member 'GSAnimKeyStateBlender_EasingToEndState::IsFromForceSetStateImmediately' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.ForceSetStateImmediately
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlender_ForceSetStateImmediately final
{
public:
	class FName                                   TargetStateName;                                   // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_ForceSetStateImmediately) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_ForceSetStateImmediately");
//static_assert(sizeof(GSAnimKeyStateBlender_ForceSetStateImmediately) == 0x000008, "Wrong size on GSAnimKeyStateBlender_ForceSetStateImmediately");
//static_assert(offsetof(GSAnimKeyStateBlender_ForceSetStateImmediately, TargetStateName) == 0x000000, "Member 'GSAnimKeyStateBlender_ForceSetStateImmediately::TargetStateName' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.GetBeginStateName
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlender_GetBeginStateName final
{
public:
	class FName                                   ReturnValue;                                       // 0x0000(0x0008)(ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_GetBeginStateName) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_GetBeginStateName");
//static_assert(sizeof(GSAnimKeyStateBlender_GetBeginStateName) == 0x000008, "Wrong size on GSAnimKeyStateBlender_GetBeginStateName");
//static_assert(offsetof(GSAnimKeyStateBlender_GetBeginStateName, ReturnValue) == 0x000000, "Member 'GSAnimKeyStateBlender_GetBeginStateName::ReturnValue' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.GetCurrentStateName
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlender_GetCurrentStateName final
{
public:
	class FName                                   ReturnValue;                                       // 0x0000(0x0008)(ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_GetCurrentStateName) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_GetCurrentStateName");
//static_assert(sizeof(GSAnimKeyStateBlender_GetCurrentStateName) == 0x000008, "Wrong size on GSAnimKeyStateBlender_GetCurrentStateName");
//static_assert(offsetof(GSAnimKeyStateBlender_GetCurrentStateName, ReturnValue) == 0x000000, "Member 'GSAnimKeyStateBlender_GetCurrentStateName::ReturnValue' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.GetEndStateName
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlender_GetEndStateName final
{
public:
	class FName                                   ReturnValue;                                       // 0x0000(0x0008)(ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_GetEndStateName) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_GetEndStateName");
//static_assert(sizeof(GSAnimKeyStateBlender_GetEndStateName) == 0x000008, "Wrong size on GSAnimKeyStateBlender_GetEndStateName");
//static_assert(offsetof(GSAnimKeyStateBlender_GetEndStateName, ReturnValue) == 0x000000, "Member 'GSAnimKeyStateBlender_GetEndStateName::ReturnValue' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.GetPredicToStateCfgEasingTime
// 0x0010 (0x0010 - 0x0000)
struct GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime final
{
public:
	class FName                                   TargetStateName;                                   // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         OutDelayEasingTime;                                // 0x0008(0x0004)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ReturnValue;                                       // 0x000C(0x0004)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime");
//static_assert(sizeof(GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime) == 0x000010, "Wrong size on GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime");
//static_assert(offsetof(GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime, TargetStateName) == 0x000000, "Member 'GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime::TargetStateName' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime, OutDelayEasingTime) == 0x000008, "Member 'GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime::OutDelayEasingTime' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime, ReturnValue) == 0x00000C, "Member 'GSAnimKeyStateBlender_GetPredicToStateCfgEasingTime::ReturnValue' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.InitAddStateToStateEasingCfg
// 0x0028 (0x0028 - 0x0000)
struct GSAnimKeyStateBlender_InitAddStateToStateEasingCfg final
{
public:
	class FName                                   FromStateName;                                     // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   ToStateName;                                       // 0x0008(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InEasingTime;                                      // 0x0010(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EEasingFunc                                   InEasingFunc;                                      // 0x0014(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_15[0x3];                                       // 0x0015(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         InEasingBlendExp;                                  // 0x0018(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         InEasingSteps;                                     // 0x001C(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAnimKBEnumBoolEasing                       InEnumValEasingType;                               // 0x0020(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAnimKBEnumBoolEasing                       InBoolValEasingType;                               // 0x0021(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_22[0x2];                                       // 0x0022(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         InDelayEasingTime;                                 // 0x0024(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_InitAddStateToStateEasingCfg");
//static_assert(sizeof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg) == 0x000028, "Wrong size on GSAnimKeyStateBlender_InitAddStateToStateEasingCfg");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, FromStateName) == 0x000000, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::FromStateName' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, ToStateName) == 0x000008, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::ToStateName' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InEasingTime) == 0x000010, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InEasingTime' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InEasingFunc) == 0x000014, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InEasingFunc' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InEasingBlendExp) == 0x000018, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InEasingBlendExp' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InEasingSteps) == 0x00001C, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InEasingSteps' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InEnumValEasingType) == 0x000020, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InEnumValEasingType' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InBoolValEasingType) == 0x000021, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InBoolValEasingType' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitAddStateToStateEasingCfg, InDelayEasingTime) == 0x000024, "Member 'GSAnimKeyStateBlender_InitAddStateToStateEasingCfg::InDelayEasingTime' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.InitSetDefaultEasingCfg
// 0x0018 (0x0018 - 0x0000)
struct GSAnimKeyStateBlender_InitSetDefaultEasingCfg final
{
public:
	float                                         InEasingTime;                                      // 0x0000(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EEasingFunc                                   InEasingFunc;                                      // 0x0004(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_5[0x3];                                        // 0x0005(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         InEasingBlendExp;                                  // 0x0008(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         InEasingSteps;                                     // 0x000C(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAnimKBEnumBoolEasing                       InEnumValEasingType;                               // 0x0010(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAnimKBEnumBoolEasing                       InBoolValEasingType;                               // 0x0011(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_12[0x2];                                       // 0x0012(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         InDelayEasingTime;                                 // 0x0014(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_InitSetDefaultEasingCfg");
//static_assert(sizeof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg) == 0x000018, "Wrong size on GSAnimKeyStateBlender_InitSetDefaultEasingCfg");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InEasingTime) == 0x000000, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InEasingTime' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InEasingFunc) == 0x000004, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InEasingFunc' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InEasingBlendExp) == 0x000008, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InEasingBlendExp' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InEasingSteps) == 0x00000C, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InEasingSteps' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InEnumValEasingType) == 0x000010, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InEnumValEasingType' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InBoolValEasingType) == 0x000011, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InBoolValEasingType' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetDefaultEasingCfg, InDelayEasingTime) == 0x000014, "Member 'GSAnimKeyStateBlender_InitSetDefaultEasingCfg::InDelayEasingTime' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.InitSetLevelSequence
// 0x0018 (0x0018 - 0x0000)
struct GSAnimKeyStateBlender_InitSetLevelSequence final
{
public:
	class UObject*                                InRefObject;                                       // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class ULevelSequence*                         InLevelSequence;                                   // 0x0008(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          InIsStrictStateMatchCfg;                           // 0x0010(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          InIsAlwaysUsingEndStateAsChanging;                 // 0x0011(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_12[0x6];                                       // 0x0012(0x0006)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(GSAnimKeyStateBlender_InitSetLevelSequence) == 0x000008, "Wrong alignment on GSAnimKeyStateBlender_InitSetLevelSequence");
//static_assert(sizeof(GSAnimKeyStateBlender_InitSetLevelSequence) == 0x000018, "Wrong size on GSAnimKeyStateBlender_InitSetLevelSequence");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetLevelSequence, InRefObject) == 0x000000, "Member 'GSAnimKeyStateBlender_InitSetLevelSequence::InRefObject' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetLevelSequence, InLevelSequence) == 0x000008, "Member 'GSAnimKeyStateBlender_InitSetLevelSequence::InLevelSequence' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetLevelSequence, InIsStrictStateMatchCfg) == 0x000010, "Member 'GSAnimKeyStateBlender_InitSetLevelSequence::InIsStrictStateMatchCfg' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetLevelSequence, InIsAlwaysUsingEndStateAsChanging) == 0x000011, "Member 'GSAnimKeyStateBlender_InitSetLevelSequence::InIsAlwaysUsingEndStateAsChanging' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.InitSetWidgetAnimation
// 0x0018 (0x0018 - 0x0000)
struct GSAnimKeyStateBlender_InitSetWidgetAnimation final
{
public:
	class UUserWidget*                            InRefUserWidget;                                   // 0x0000(0x0008)(Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UWidgetAnimation*                       InWidgetAnimation;                                 // 0x0008(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          InIsStrictStateMatchCfg;                           // 0x0010(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          InIsAlwaysUsingEndStateAsChanging;                 // 0x0011(0x0001)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_12[0x6];                                       // 0x0012(0x0006)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(GSAnimKeyStateBlender_InitSetWidgetAnimation) == 0x000008, "Wrong alignment on GSAnimKeyStateBlender_InitSetWidgetAnimation");
//static_assert(sizeof(GSAnimKeyStateBlender_InitSetWidgetAnimation) == 0x000018, "Wrong size on GSAnimKeyStateBlender_InitSetWidgetAnimation");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetWidgetAnimation, InRefUserWidget) == 0x000000, "Member 'GSAnimKeyStateBlender_InitSetWidgetAnimation::InRefUserWidget' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetWidgetAnimation, InWidgetAnimation) == 0x000008, "Member 'GSAnimKeyStateBlender_InitSetWidgetAnimation::InWidgetAnimation' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetWidgetAnimation, InIsStrictStateMatchCfg) == 0x000010, "Member 'GSAnimKeyStateBlender_InitSetWidgetAnimation::InIsStrictStateMatchCfg' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_InitSetWidgetAnimation, InIsAlwaysUsingEndStateAsChanging) == 0x000011, "Member 'GSAnimKeyStateBlender_InitSetWidgetAnimation::InIsAlwaysUsingEndStateAsChanging' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.IsInBlending
// 0x0001 (0x0001 - 0x0000)
struct GSAnimKeyStateBlender_IsInBlending final
{
public:
	bool                                          ReturnValue;                                       // 0x0000(0x0001)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_IsInBlending) == 0x000001, "Wrong alignment on GSAnimKeyStateBlender_IsInBlending");
//static_assert(sizeof(GSAnimKeyStateBlender_IsInBlending) == 0x000001, "Wrong size on GSAnimKeyStateBlender_IsInBlending");
//static_assert(offsetof(GSAnimKeyStateBlender_IsInBlending, ReturnValue) == 0x000000, "Member 'GSAnimKeyStateBlender_IsInBlending::ReturnValue' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlender.ToState
// 0x0010 (0x0010 - 0x0000)
struct GSAnimKeyStateBlender_ToState final
{
public:
	class FName                                   TargetStateName;                                   // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InStateDelayEasingTime;                            // 0x0008(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InStateOverideEasingTime;                          // 0x000C(0x0004)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlender_ToState) == 0x000004, "Wrong alignment on GSAnimKeyStateBlender_ToState");
//static_assert(sizeof(GSAnimKeyStateBlender_ToState) == 0x000010, "Wrong size on GSAnimKeyStateBlender_ToState");
//static_assert(offsetof(GSAnimKeyStateBlender_ToState, TargetStateName) == 0x000000, "Member 'GSAnimKeyStateBlender_ToState::TargetStateName' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_ToState, InStateDelayEasingTime) == 0x000008, "Member 'GSAnimKeyStateBlender_ToState::InStateDelayEasingTime' has a wrong offset!");
//static_assert(offsetof(GSAnimKeyStateBlender_ToState, InStateOverideEasingTime) == 0x00000C, "Member 'GSAnimKeyStateBlender_ToState::InStateOverideEasingTime' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlenderUtil.RegAnimKeyStateBlenderObjForTick
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick final
{
public:
	class UGSAnimKeyStateBlender*                 AnimKeyStateBlender;                               // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick) == 0x000008, "Wrong alignment on GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick");
//static_assert(sizeof(GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick) == 0x000008, "Wrong size on GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick");
//static_assert(offsetof(GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick, AnimKeyStateBlender) == 0x000000, "Member 'GSAnimKeyStateBlenderUtil_RegAnimKeyStateBlenderObjForTick::AnimKeyStateBlender' has a wrong offset!");

// Function GSAnimationKeyBlender.GSAnimKeyStateBlenderUtil.UnRegAnimKeyStateBlenderObjForTick
// 0x0008 (0x0008 - 0x0000)
struct GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick final
{
public:
	class UGSAnimKeyStateBlender*                 AnimKeyStateBlender;                               // 0x0000(0x0008)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick) == 0x000008, "Wrong alignment on GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick");
//static_assert(sizeof(GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick) == 0x000008, "Wrong size on GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick");
//static_assert(offsetof(GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick, AnimKeyStateBlender) == 0x000000, "Member 'GSAnimKeyStateBlenderUtil_UnRegAnimKeyStateBlenderObjForTick::AnimKeyStateBlender' has a wrong offset!");

}

