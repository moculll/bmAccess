#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GSEArteries

#include "Basic.hpp"

#include "CoreUObject_structs.hpp"


namespace SDK
{

// Enum GSEArteries.GSArteriesIteractType
// NumValues: 0x0004
enum class EGSArteriesIteractType : uint8
{
	Spline                                   = 0,
	Box                                      = 1,
	BoxWithSpline                            = 2,
	GSArteriesIteractType_MAX                = 3,
};

// Enum GSEArteries.GSATERIES_SIDE_SELECT_FEATURE
// NumValues: 0x0006
enum class EGSATERIES_SIDE_SELECT_FEATURE : uint8
{
	RANDOM_SIDE                              = 0,
	LONGEST_SIDE                             = 1,
	SHORTEST_SIDE                            = 2,
	EACH_SIDE                                = 3,
	FIRST_SIDE                               = 4,
	GSATERIES_SIDE_SELECT_MAX                = 5,
};

// Enum GSEArteries.EGSATERIES_PLACEMENT_TYPE
// NumValues: 0x0002
enum class EGSATERIES_PLACEMENT_TYPE : uint32
{
	PLACEMENT_CRATE                          = 0,
	PLACEMENT_MAX                            = 1,
};

// Enum GSEArteries.GSATERIES_SIDE_DISTRIBUTION_FEATURE
// NumValues: 0x0004
enum class EGSATERIES_SIDE_DISTRIBUTION_FEATURE : uint8
{
	CENTER                                   = 0,
	END                                      = 1,
	EVEN                                     = 2,
	GSATERIES_SIDE_DISTRIBUTION_MAX          = 3,
};

// Enum GSEArteries.GSATERIES_SAMPLE_AXIS
// NumValues: 0x0004
enum class EGSATERIES_SAMPLE_AXIS : uint8
{
	X                                        = 0,
	Y                                        = 1,
	Z                                        = 2,
	GSATERIES_SAMPLE_MAX                     = 3,
};

// Enum GSEArteries.EGSARTERIES_PLACEMENT_STRATEGY
// NumValues: 0x0004
enum class EGSARTERIES_PLACEMENT_STRATEGY : uint8
{
	ANY                                      = 0,
	PREFER_STACKABLE                         = 1,
	BASE                                     = 2,
	EGSARTERIES_PLACEMENT_MAX                = 3,
};

// Enum GSEArteries.EGSARTERIES_PLACEMENT_LEVEL
// NumValues: 0x0006
enum class EGSARTERIES_PLACEMENT_LEVEL : uint8
{
	NONE                                     = 0,
	BUTTOM                                   = 1,
	TOP                                      = 2,
	TOP_OR_BOTTOM                            = 3,
	ALL                                      = 7,
	EGSARTERIES_PLACEMENT_MAX                = 8,
};

// ScriptStruct GSEArteries.BaseTransformedSoftObject
// 0x0080 (0x0080 - 0x0000)
struct FBaseTransformedSoftObject final
{
public:
	struct FSoftObjectPath                        SoftObjectPath;                                    // 0x0000(0x0018)(Edit, BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_18[0x8];                                       // 0x0018(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FTransform                             BaseTransform;                                     // 0x0020(0x0060)(Edit, BlueprintVisible, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FBaseTransformedSoftObject) == 0x000010, "Wrong alignment on FBaseTransformedSoftObject");
//static_assert(sizeof(FBaseTransformedSoftObject) == 0x000080, "Wrong size on FBaseTransformedSoftObject");
//static_assert(offsetof(FBaseTransformedSoftObject, SoftObjectPath) == 0x000000, "Member 'FBaseTransformedSoftObject::SoftObjectPath' has a wrong offset!");
//static_assert(offsetof(FBaseTransformedSoftObject, BaseTransform) == 0x000020, "Member 'FBaseTransformedSoftObject::BaseTransform' has a wrong offset!");

// ScriptStruct GSEArteries.GSArteriesStackParam
// 0x0005 (0x0005 - 0x0000)
struct FGSArteriesStackParam final
{
public:
	bool                                          bCanBeStackedOnto;                                 // 0x0000(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSARTERIES_PLACEMENT_LEVEL                   EFixToLevel;                                       // 0x0001(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSARTERIES_PLACEMENT_LEVEL                   ECanPitchAt;                                       // 0x0002(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSARTERIES_PLACEMENT_LEVEL                   ECanRollAt;                                        // 0x0003(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSARTERIES_PLACEMENT_LEVEL                   ECanYawAt;                                         // 0x0004(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSArteriesStackParam) == 0x000001, "Wrong alignment on FGSArteriesStackParam");
//static_assert(sizeof(FGSArteriesStackParam) == 0x000005, "Wrong size on FGSArteriesStackParam");
//static_assert(offsetof(FGSArteriesStackParam, bCanBeStackedOnto) == 0x000000, "Member 'FGSArteriesStackParam::bCanBeStackedOnto' has a wrong offset!");
//static_assert(offsetof(FGSArteriesStackParam, EFixToLevel) == 0x000001, "Member 'FGSArteriesStackParam::EFixToLevel' has a wrong offset!");
//static_assert(offsetof(FGSArteriesStackParam, ECanPitchAt) == 0x000002, "Member 'FGSArteriesStackParam::ECanPitchAt' has a wrong offset!");
//static_assert(offsetof(FGSArteriesStackParam, ECanRollAt) == 0x000003, "Member 'FGSArteriesStackParam::ECanRollAt' has a wrong offset!");
//static_assert(offsetof(FGSArteriesStackParam, ECanYawAt) == 0x000004, "Member 'FGSArteriesStackParam::ECanYawAt' has a wrong offset!");

// ScriptStruct GSEArteries.GSArteriesStackRule
// 0x0010 (0x0010 - 0x0000)
struct FGSArteriesStackRule final
{
public:
	struct FGSArteriesStackParam                  StackParam;                                        // 0x0000(0x0005)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_5[0x3];                                        // 0x0005(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         MinTotalNumber;                                    // 0x0008(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         MaxTotalNumber;                                    // 0x000C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSArteriesStackRule) == 0x000004, "Wrong alignment on FGSArteriesStackRule");
//static_assert(sizeof(FGSArteriesStackRule) == 0x000010, "Wrong size on FGSArteriesStackRule");
//static_assert(offsetof(FGSArteriesStackRule, StackParam) == 0x000000, "Member 'FGSArteriesStackRule::StackParam' has a wrong offset!");
//static_assert(offsetof(FGSArteriesStackRule, MinTotalNumber) == 0x000008, "Member 'FGSArteriesStackRule::MinTotalNumber' has a wrong offset!");
//static_assert(offsetof(FGSArteriesStackRule, MaxTotalNumber) == 0x00000C, "Member 'FGSArteriesStackRule::MaxTotalNumber' has a wrong offset!");

// ScriptStruct GSEArteries.GSArteriesPlacementInfo
// 0x00C0 (0x00C0 - 0x0000)
struct FGSArteriesPlacementInfo final
{
public:
	EGSARTERIES_PLACEMENT_LEVEL                   ECurEnumLevel;                                     // 0x0000(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_1[0x3];                                        // 0x0001(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	EGSATERIES_PLACEMENT_TYPE                     EPlacementType;                                    // 0x0004(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FSoftObjectPath                        PlacedSoftPath;                                    // 0x0008(0x0018)(ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FBoxSphereBounds                       PlacedBound;                                       // 0x0020(0x0038)(ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_58[0x8];                                       // 0x0058(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FTransform                             NoisedTransform;                                   // 0x0060(0x0060)(IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSArteriesPlacementInfo) == 0x000010, "Wrong alignment on FGSArteriesPlacementInfo");
//static_assert(sizeof(FGSArteriesPlacementInfo) == 0x0000C0, "Wrong size on FGSArteriesPlacementInfo");
//static_assert(offsetof(FGSArteriesPlacementInfo, ECurEnumLevel) == 0x000000, "Member 'FGSArteriesPlacementInfo::ECurEnumLevel' has a wrong offset!");
//static_assert(offsetof(FGSArteriesPlacementInfo, EPlacementType) == 0x000004, "Member 'FGSArteriesPlacementInfo::EPlacementType' has a wrong offset!");
//static_assert(offsetof(FGSArteriesPlacementInfo, PlacedSoftPath) == 0x000008, "Member 'FGSArteriesPlacementInfo::PlacedSoftPath' has a wrong offset!");
//static_assert(offsetof(FGSArteriesPlacementInfo, PlacedBound) == 0x000020, "Member 'FGSArteriesPlacementInfo::PlacedBound' has a wrong offset!");
//static_assert(offsetof(FGSArteriesPlacementInfo, NoisedTransform) == 0x000060, "Member 'FGSArteriesPlacementInfo::NoisedTransform' has a wrong offset!");

}
