#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GSAnimationKeyBlender

#include "Basic.hpp"

#include "CoreUObject_structs.hpp"
#include "UMG_structs.hpp"
#include "MovieScene_structs.hpp"
#include "Engine_structs.hpp"
#include "SlateCore_structs.hpp"


namespace SDK
{

// Enum GSAnimationKeyBlender.EGSAnimMarginChannel
// NumValues: 0x0006
enum class EGSAnimMarginChannel : uint8
{
	GSA_MARGIN_MIN                           = 0,
	GSA_MARGIN_TOP                           = 1,
	GSA_MARGIN_LEFT                          = 2,
	GSA_MARGIN_RIGHT                         = 3,
	GSA_MARGIN_BOTTOM                        = 4,
	GSA_MARGIN_MAX                           = 5,
};

// Enum GSAnimationKeyBlender.EGSAnimColorChannel
// NumValues: 0x0006
enum class EGSAnimColorChannel : uint8
{
	GSA_COLOR_MIN                            = 0,
	GSA_COLOR_RED                            = 1,
	GSA_COLOR_GREEN                          = 2,
	GSA_COLOR_BLUE                           = 3,
	GSA_COLOR_ALPHA                          = 4,
	GSA_COLOR_MAX                            = 5,
};

// Enum GSAnimationKeyBlender.EGSAKBObjType
// NumValues: 0x0005
enum class EGSAKBObjType : uint8
{
	GSA_OBJ_TYPE_MIN                         = 0,
	GSA_OBJ_TYPE_ACTOR                       = 1,
	GSA_OBJ_TYPE_WIDGET                      = 2,
	GSA_OBJ_TYPE_MPC_INST                    = 3,
	GSA_OBJ_TYPE_MAX                         = 4,
};

// Enum GSAnimationKeyBlender.EGSAnimKBEnumBoolEasing
// NumValues: 0x0005
enum class EGSAnimKBEnumBoolEasing : uint8
{
	GSEnd                                    = 0,
	GSBegin                                  = 1,
	GSCalc                                   = 2,
	GSHalf                                   = 3,
	EGSAnimKBEnumBoolEasing_MAX              = 4,
};

// ScriptStruct GSAnimationKeyBlender.GSAKMatParamBool
// 0x0020 (0x0020 - 0x0000)
struct FGSAKMatParamBool final
{
public:
	TArray<class FName>                           BrushPropertyNamePath;                             // 0x0000(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, NativeAccessSpecifierPublic)
	int32                                         ComponentMaterialIndex;                            // 0x0010(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   ParamName;                                         // 0x0014(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          Value;                                             // 0x001C(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_1D[0x3];                                       // 0x001D(0x0003)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKMatParamBool) == 0x000008, "Wrong alignment on FGSAKMatParamBool");
//static_assert(sizeof(FGSAKMatParamBool) == 0x000020, "Wrong size on FGSAKMatParamBool");
//static_assert(offsetof(FGSAKMatParamBool, BrushPropertyNamePath) == 0x000000, "Member 'FGSAKMatParamBool::BrushPropertyNamePath' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamBool, ComponentMaterialIndex) == 0x000010, "Member 'FGSAKMatParamBool::ComponentMaterialIndex' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamBool, ParamName) == 0x000014, "Member 'FGSAKMatParamBool::ParamName' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamBool, Value) == 0x00001C, "Member 'FGSAKMatParamBool::Value' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKMatParamScalar
// 0x0020 (0x0020 - 0x0000)
struct FGSAKMatParamScalar final
{
public:
	TArray<class FName>                           BrushPropertyNamePath;                             // 0x0000(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, NativeAccessSpecifierPublic)
	int32                                         ComponentMaterialIndex;                            // 0x0010(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   ParamName;                                         // 0x0014(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Value;                                             // 0x001C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSAKMatParamScalar) == 0x000008, "Wrong alignment on FGSAKMatParamScalar");
//static_assert(sizeof(FGSAKMatParamScalar) == 0x000020, "Wrong size on FGSAKMatParamScalar");
//static_assert(offsetof(FGSAKMatParamScalar, BrushPropertyNamePath) == 0x000000, "Member 'FGSAKMatParamScalar::BrushPropertyNamePath' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamScalar, ComponentMaterialIndex) == 0x000010, "Member 'FGSAKMatParamScalar::ComponentMaterialIndex' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamScalar, ParamName) == 0x000014, "Member 'FGSAKMatParamScalar::ParamName' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamScalar, Value) == 0x00001C, "Member 'FGSAKMatParamScalar::Value' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKMatParamVector4
// 0x0040 (0x0040 - 0x0000)
struct FGSAKMatParamVector4 final
{
public:
	TArray<class FName>                           BrushPropertyNamePath;                             // 0x0000(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, NativeAccessSpecifierPublic)
	int32                                         ComponentMaterialIndex;                            // 0x0010(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                   ParamName;                                         // 0x0014(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FLinearColor                           ValueFactor;                                       // 0x001C(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FLinearColor                           Value;                                             // 0x002C(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_3C[0x4];                                       // 0x003C(0x0004)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKMatParamVector4) == 0x000008, "Wrong alignment on FGSAKMatParamVector4");
//static_assert(sizeof(FGSAKMatParamVector4) == 0x000040, "Wrong size on FGSAKMatParamVector4");
//static_assert(offsetof(FGSAKMatParamVector4, BrushPropertyNamePath) == 0x000000, "Member 'FGSAKMatParamVector4::BrushPropertyNamePath' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamVector4, ComponentMaterialIndex) == 0x000010, "Member 'FGSAKMatParamVector4::ComponentMaterialIndex' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamVector4, ParamName) == 0x000014, "Member 'FGSAKMatParamVector4::ParamName' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamVector4, ValueFactor) == 0x00001C, "Member 'FGSAKMatParamVector4::ValueFactor' has a wrong offset!");
//static_assert(offsetof(FGSAKMatParamVector4, Value) == 0x00002C, "Member 'FGSAKMatParamVector4::Value' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyFloat
// 0x0028 (0x0028 - 0x0000)
struct alignas(0x08) FGSAKPropertyFloat final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	float                                         PropertyValue;                                     // 0x0014(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_18[0x10];                                      // 0x0018(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyFloat) == 0x000008, "Wrong alignment on FGSAKPropertyFloat");
//static_assert(sizeof(FGSAKPropertyFloat) == 0x000028, "Wrong size on FGSAKPropertyFloat");
//static_assert(offsetof(FGSAKPropertyFloat, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyFloat::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyFloat, PropertyValue) == 0x000014, "Member 'FGSAKPropertyFloat::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyDouble
// 0x0030 (0x0030 - 0x0000)
struct FGSAKPropertyDouble final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_14[0x4];                                       // 0x0014(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	double                                        PropertyValue;                                     // 0x0018(0x0008)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_20[0x10];                                      // 0x0020(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyDouble) == 0x000008, "Wrong alignment on FGSAKPropertyDouble");
//static_assert(sizeof(FGSAKPropertyDouble) == 0x000030, "Wrong size on FGSAKPropertyDouble");
//static_assert(offsetof(FGSAKPropertyDouble, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyDouble::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyDouble, PropertyValue) == 0x000018, "Member 'FGSAKPropertyDouble::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyLinearColor
// 0x0048 (0x0048 - 0x0000)
struct alignas(0x08) FGSAKPropertyLinearColor final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	struct FLinearColor                           PropertyFactor;                                    // 0x0014(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FLinearColor                           PropertyValue;                                     // 0x0024(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_34[0x14];                                      // 0x0034(0x0014)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyLinearColor) == 0x000008, "Wrong alignment on FGSAKPropertyLinearColor");
//static_assert(sizeof(FGSAKPropertyLinearColor) == 0x000048, "Wrong size on FGSAKPropertyLinearColor");
//static_assert(offsetof(FGSAKPropertyLinearColor, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyLinearColor::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyLinearColor, PropertyFactor) == 0x000014, "Member 'FGSAKPropertyLinearColor::PropertyFactor' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyLinearColor, PropertyValue) == 0x000024, "Member 'FGSAKPropertyLinearColor::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyObjectProperty
// 0x0030 (0x0030 - 0x0000)
struct FGSAKPropertyObjectProperty final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_14[0x4];                                       // 0x0014(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UObject*                                PropertyValue;                                     // 0x0018(0x0008)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_20[0x10];                                      // 0x0020(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyObjectProperty) == 0x000008, "Wrong alignment on FGSAKPropertyObjectProperty");
//static_assert(sizeof(FGSAKPropertyObjectProperty) == 0x000030, "Wrong size on FGSAKPropertyObjectProperty");
//static_assert(offsetof(FGSAKPropertyObjectProperty, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyObjectProperty::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyObjectProperty, PropertyValue) == 0x000018, "Member 'FGSAKPropertyObjectProperty::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyMargin
// 0x0048 (0x0048 - 0x0000)
struct alignas(0x08) FGSAKPropertyMargin final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	struct FMargin                                PropertyFactor;                                    // 0x0014(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	struct FMargin                                PropertyValue;                                     // 0x0024(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_34[0x14];                                      // 0x0034(0x0014)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyMargin) == 0x000008, "Wrong alignment on FGSAKPropertyMargin");
//static_assert(sizeof(FGSAKPropertyMargin) == 0x000048, "Wrong size on FGSAKPropertyMargin");
//static_assert(offsetof(FGSAKPropertyMargin, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyMargin::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyMargin, PropertyFactor) == 0x000014, "Member 'FGSAKPropertyMargin::PropertyFactor' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyMargin, PropertyValue) == 0x000024, "Member 'FGSAKPropertyMargin::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyVector4
// 0x0070 (0x0070 - 0x0000)
struct FGSAKPropertyVector4 final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	int32                                         VectorDimension;                                   // 0x0014(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_18[0x8];                                       // 0x0018(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector4                               PropertyFactor;                                    // 0x0020(0x0020)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector4                               PropertyValue;                                     // 0x0040(0x0020)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_60[0x10];                                      // 0x0060(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyVector4) == 0x000010, "Wrong alignment on FGSAKPropertyVector4");
//static_assert(sizeof(FGSAKPropertyVector4) == 0x000070, "Wrong size on FGSAKPropertyVector4");
//static_assert(offsetof(FGSAKPropertyVector4, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyVector4::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyVector4, VectorDimension) == 0x000014, "Member 'FGSAKPropertyVector4::VectorDimension' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyVector4, PropertyFactor) == 0x000020, "Member 'FGSAKPropertyVector4::PropertyFactor' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyVector4, PropertyValue) == 0x000040, "Member 'FGSAKPropertyVector4::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyByte
// 0x0028 (0x0028 - 0x0000)
struct alignas(0x08) FGSAKPropertyByte final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	uint8                                         PropertyValue;                                     // 0x0014(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_15[0x13];                                      // 0x0015(0x0013)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyByte) == 0x000008, "Wrong alignment on FGSAKPropertyByte");
//static_assert(sizeof(FGSAKPropertyByte) == 0x000028, "Wrong size on FGSAKPropertyByte");
//static_assert(offsetof(FGSAKPropertyByte, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyByte::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyByte, PropertyValue) == 0x000014, "Member 'FGSAKPropertyByte::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyInteger
// 0x0028 (0x0028 - 0x0000)
struct alignas(0x08) FGSAKPropertyInteger final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	int32                                         PropertyValue;                                     // 0x0014(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_18[0x10];                                      // 0x0018(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyInteger) == 0x000008, "Wrong alignment on FGSAKPropertyInteger");
//static_assert(sizeof(FGSAKPropertyInteger) == 0x000028, "Wrong size on FGSAKPropertyInteger");
//static_assert(offsetof(FGSAKPropertyInteger, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyInteger::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyInteger, PropertyValue) == 0x000014, "Member 'FGSAKPropertyInteger::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKPropertyBool
// 0x0028 (0x0028 - 0x0000)
struct alignas(0x08) FGSAKPropertyBool final
{
public:
	struct FMovieScenePropertyBinding             PropertyBinding;                                   // 0x0000(0x0014)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	bool                                          PropertyValue;                                     // 0x0014(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_15[0x13];                                      // 0x0015(0x0013)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKPropertyBool) == 0x000008, "Wrong alignment on FGSAKPropertyBool");
//static_assert(sizeof(FGSAKPropertyBool) == 0x000028, "Wrong size on FGSAKPropertyBool");
//static_assert(offsetof(FGSAKPropertyBool, PropertyBinding) == 0x000000, "Member 'FGSAKPropertyBool::PropertyBinding' has a wrong offset!");
//static_assert(offsetof(FGSAKPropertyBool, PropertyValue) == 0x000014, "Member 'FGSAKPropertyBool::PropertyValue' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAnimKeyCachedMatParamData
// 0x00F0 (0x00F0 - 0x0000)
struct FGSAnimKeyCachedMatParamData
{
public:
	TMap<class FString, struct FGSAKMatParamBool> MatParamBoolMap;                                   // 0x0000(0x0050)(Edit, BlueprintVisible, BlueprintReadOnly, EditConst, NativeAccessSpecifierPublic)
	TMap<class FString, struct FGSAKMatParamScalar> MatParamScalarMap;                                 // 0x0050(0x0050)(Edit, BlueprintVisible, BlueprintReadOnly, EditConst, NativeAccessSpecifierPublic)
	TMap<class FString, struct FGSAKMatParamVector4> MatParamVector4Map;                                // 0x00A0(0x0050)(Edit, BlueprintVisible, BlueprintReadOnly, EditConst, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSAnimKeyCachedMatParamData) == 0x000008, "Wrong alignment on FGSAnimKeyCachedMatParamData");
//static_assert(sizeof(FGSAnimKeyCachedMatParamData) == 0x0000F0, "Wrong size on FGSAnimKeyCachedMatParamData");
//static_assert(offsetof(FGSAnimKeyCachedMatParamData, MatParamBoolMap) == 0x000000, "Member 'FGSAnimKeyCachedMatParamData::MatParamBoolMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyCachedMatParamData, MatParamScalarMap) == 0x000050, "Member 'FGSAnimKeyCachedMatParamData::MatParamScalarMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyCachedMatParamData, MatParamVector4Map) == 0x0000A0, "Member 'FGSAnimKeyCachedMatParamData::MatParamVector4Map' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAnimKeyStateData
// 0x0400 (0x04F0 - 0x00F0)
struct FGSAnimKeyStateData final : public FGSAnimKeyCachedMatParamData
{
public:
	class FName                                   StateName;                                         // 0x00F0(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FFrameNumber                           FrameNumber;                                       // 0x00F8(0x0004)(Edit, EditConst, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_FC[0x4];                                       // 0x00FC(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector2D                              TranslationFactor;                                 // 0x0100(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AngleFactor;                                       // 0x0110(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_114[0x4];                                      // 0x0114(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FVector2D                              ScaleFactor;                                       // 0x0118(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector2D                              ShearFactor;                                       // 0x0128(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FWidgetTransform                       WidgetTransform;                                   // 0x0138(0x0038)(Edit, EditConst, NoDestructor, NativeAccessSpecifierPublic)
	struct FVector                                WorldTranslationFactor;                            // 0x0170(0x0018)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector                                WorldScale3DFactor;                                // 0x0188(0x0018)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector                                WorldRotate3DFactor;                               // 0x01A0(0x0018)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_1B8[0x8];                                      // 0x01B8(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FTransform                             WorldTransform;                                    // 0x01C0(0x0060)(Edit, EditConst, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyFloat>  PropertyFloatMap;                                  // 0x0220(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyDouble> PropertyDoubleMap;                                 // 0x0270(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyByte>   PropertyByteMap;                                   // 0x02C0(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyVector4> PropertyVector4Map;                                // 0x0310(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyInteger> PropertyIntegerMap;                                // 0x0360(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyBool>   PropertyBoolMap;                                   // 0x03B0(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyLinearColor> PropertyLinearColorMap;                            // 0x0400(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyMargin> PropertyMarginMap;                                 // 0x0450(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
	TMap<class FName, struct FGSAKPropertyObjectProperty> PropertyObjectPropertyMap;                         // 0x04A0(0x0050)(Edit, EditConst, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSAnimKeyStateData) == 0x000010, "Wrong alignment on FGSAnimKeyStateData");
//static_assert(sizeof(FGSAnimKeyStateData) == 0x0004F0, "Wrong size on FGSAnimKeyStateData");
//static_assert(offsetof(FGSAnimKeyStateData, StateName) == 0x0000F0, "Member 'FGSAnimKeyStateData::StateName' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, FrameNumber) == 0x0000F8, "Member 'FGSAnimKeyStateData::FrameNumber' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, TranslationFactor) == 0x000100, "Member 'FGSAnimKeyStateData::TranslationFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, AngleFactor) == 0x000110, "Member 'FGSAnimKeyStateData::AngleFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, ScaleFactor) == 0x000118, "Member 'FGSAnimKeyStateData::ScaleFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, ShearFactor) == 0x000128, "Member 'FGSAnimKeyStateData::ShearFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, WidgetTransform) == 0x000138, "Member 'FGSAnimKeyStateData::WidgetTransform' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, WorldTranslationFactor) == 0x000170, "Member 'FGSAnimKeyStateData::WorldTranslationFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, WorldScale3DFactor) == 0x000188, "Member 'FGSAnimKeyStateData::WorldScale3DFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, WorldRotate3DFactor) == 0x0001A0, "Member 'FGSAnimKeyStateData::WorldRotate3DFactor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, WorldTransform) == 0x0001C0, "Member 'FGSAnimKeyStateData::WorldTransform' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyFloatMap) == 0x000220, "Member 'FGSAnimKeyStateData::PropertyFloatMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyDoubleMap) == 0x000270, "Member 'FGSAnimKeyStateData::PropertyDoubleMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyByteMap) == 0x0002C0, "Member 'FGSAnimKeyStateData::PropertyByteMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyVector4Map) == 0x000310, "Member 'FGSAnimKeyStateData::PropertyVector4Map' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyIntegerMap) == 0x000360, "Member 'FGSAnimKeyStateData::PropertyIntegerMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyBoolMap) == 0x0003B0, "Member 'FGSAnimKeyStateData::PropertyBoolMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyLinearColorMap) == 0x000400, "Member 'FGSAnimKeyStateData::PropertyLinearColorMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyMarginMap) == 0x000450, "Member 'FGSAnimKeyStateData::PropertyMarginMap' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyStateData, PropertyObjectPropertyMap) == 0x0004A0, "Member 'FGSAnimKeyStateData::PropertyObjectPropertyMap' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAnimKeyObjST
// 0x0030 (0x0030 - 0x0000)
struct FGSAnimKeyObjST final
{
public:
	class UObject*                                TargetObject;                                      // 0x0000(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAKBObjType                                 ObjType;                                           // 0x0008(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_9[0x3];                                        // 0x0009(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FGuid                                  BindedGuid;                                        // 0x000C(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          IsSubActor;                                        // 0x001C(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_1D[0x3];                                       // 0x001D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<struct FGSAnimKeyStateData>            StateKeyDataList;                                  // 0x0020(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSAnimKeyObjST) == 0x000008, "Wrong alignment on FGSAnimKeyObjST");
//static_assert(sizeof(FGSAnimKeyObjST) == 0x000030, "Wrong size on FGSAnimKeyObjST");
//static_assert(offsetof(FGSAnimKeyObjST, TargetObject) == 0x000000, "Member 'FGSAnimKeyObjST::TargetObject' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyObjST, ObjType) == 0x000008, "Member 'FGSAnimKeyObjST::ObjType' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyObjST, BindedGuid) == 0x00000C, "Member 'FGSAnimKeyObjST::BindedGuid' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyObjST, IsSubActor) == 0x00001C, "Member 'FGSAnimKeyObjST::IsSubActor' has a wrong offset!");
//static_assert(offsetof(FGSAnimKeyObjST, StateKeyDataList) == 0x000020, "Member 'FGSAnimKeyObjST::StateKeyDataList' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKObjectEasingOneToOneStateData
// 0x0A00 (0x0A00 - 0x0000)
struct FGSAKObjectEasingOneToOneStateData final
{
public:
	class UObject*                                TargetObject;                                      // 0x0000(0x0008)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAKBObjType                                 ObjType;                                           // 0x0008(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_9[0x3];                                        // 0x0009(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FGuid                                  BindedGuid;                                        // 0x000C(0x0010)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          IsSubActor;                                        // 0x001C(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_1D[0x3];                                       // 0x001D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FGSAnimKeyStateData                    BeginStateData;                                    // 0x0020(0x04F0)(Edit, EditConst, NativeAccessSpecifierPublic)
	struct FGSAnimKeyStateData                    EndStateData;                                      // 0x0510(0x04F0)(Edit, EditConst, NativeAccessSpecifierPublic)
};
//static_assert(alignof(FGSAKObjectEasingOneToOneStateData) == 0x000010, "Wrong alignment on FGSAKObjectEasingOneToOneStateData");
//static_assert(sizeof(FGSAKObjectEasingOneToOneStateData) == 0x000A00, "Wrong size on FGSAKObjectEasingOneToOneStateData");
//static_assert(offsetof(FGSAKObjectEasingOneToOneStateData, TargetObject) == 0x000000, "Member 'FGSAKObjectEasingOneToOneStateData::TargetObject' has a wrong offset!");
//static_assert(offsetof(FGSAKObjectEasingOneToOneStateData, ObjType) == 0x000008, "Member 'FGSAKObjectEasingOneToOneStateData::ObjType' has a wrong offset!");
//static_assert(offsetof(FGSAKObjectEasingOneToOneStateData, BindedGuid) == 0x00000C, "Member 'FGSAKObjectEasingOneToOneStateData::BindedGuid' has a wrong offset!");
//static_assert(offsetof(FGSAKObjectEasingOneToOneStateData, IsSubActor) == 0x00001C, "Member 'FGSAKObjectEasingOneToOneStateData::IsSubActor' has a wrong offset!");
//static_assert(offsetof(FGSAKObjectEasingOneToOneStateData, BeginStateData) == 0x000020, "Member 'FGSAKObjectEasingOneToOneStateData::BeginStateData' has a wrong offset!");
//static_assert(offsetof(FGSAKObjectEasingOneToOneStateData, EndStateData) == 0x000510, "Member 'FGSAKObjectEasingOneToOneStateData::EndStateData' has a wrong offset!");

// ScriptStruct GSAnimationKeyBlender.GSAKBStateEasingCfg
// 0x0018 (0x0018 - 0x0000)
struct FGSAKBStateEasingCfg final
{
public:
	float                                         EasingTime;                                        // 0x0000(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DelayEasingTime;                                   // 0x0004(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EEasingFunc                                   EasingFunc;                                        // 0x0008(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_9[0x3];                                        // 0x0009(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         EasingBlendExp;                                    // 0x000C(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         EasingSteps;                                       // 0x0010(0x0004)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAnimKBEnumBoolEasing                       EnumValEasingType;                                 // 0x0014(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EGSAnimKBEnumBoolEasing                       BoolValEasingType;                                 // 0x0015(0x0001)(Edit, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_16[0x2];                                       // 0x0016(0x0002)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
//static_assert(alignof(FGSAKBStateEasingCfg) == 0x000004, "Wrong alignment on FGSAKBStateEasingCfg");
//static_assert(sizeof(FGSAKBStateEasingCfg) == 0x000018, "Wrong size on FGSAKBStateEasingCfg");
//static_assert(offsetof(FGSAKBStateEasingCfg, EasingTime) == 0x000000, "Member 'FGSAKBStateEasingCfg::EasingTime' has a wrong offset!");
//static_assert(offsetof(FGSAKBStateEasingCfg, DelayEasingTime) == 0x000004, "Member 'FGSAKBStateEasingCfg::DelayEasingTime' has a wrong offset!");
//static_assert(offsetof(FGSAKBStateEasingCfg, EasingFunc) == 0x000008, "Member 'FGSAKBStateEasingCfg::EasingFunc' has a wrong offset!");
//static_assert(offsetof(FGSAKBStateEasingCfg, EasingBlendExp) == 0x00000C, "Member 'FGSAKBStateEasingCfg::EasingBlendExp' has a wrong offset!");
//static_assert(offsetof(FGSAKBStateEasingCfg, EasingSteps) == 0x000010, "Member 'FGSAKBStateEasingCfg::EasingSteps' has a wrong offset!");
//static_assert(offsetof(FGSAKBStateEasingCfg, EnumValEasingType) == 0x000014, "Member 'FGSAKBStateEasingCfg::EnumValEasingType' has a wrong offset!");
//static_assert(offsetof(FGSAKBStateEasingCfg, BoolValEasingType) == 0x000015, "Member 'FGSAKBStateEasingCfg::BoolValEasingType' has a wrong offset!");

}
