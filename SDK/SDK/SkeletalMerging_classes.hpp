#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SkeletalMerging

#include "Basic.hpp"

#include "Engine_classes.hpp"


namespace SDK
{

// Class SkeletalMerging.SkeletalMergingLibrary
// 0x0000 (0x0028 - 0x0028)
class USkeletalMergingLibrary final : public UBlueprintFunctionLibrary
{
public:
	static class USkeletalMesh* MergeMeshes(const struct FSkeletalMeshMergeParams& Params_0);
	static class USkeleton* MergeSkeletons(const struct FSkeletonMergeParams& Params_0);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"SkeletalMergingLibrary">();
	}
	static class USkeletalMergingLibrary* GetDefaultObj()
	{
		return GetDefaultObjImpl<USkeletalMergingLibrary>();
	}
};
//static_assert(alignof(USkeletalMergingLibrary) == 0x000008, "Wrong alignment on USkeletalMergingLibrary");
//static_assert(sizeof(USkeletalMergingLibrary) == 0x000028, "Wrong size on USkeletalMergingLibrary");

}
