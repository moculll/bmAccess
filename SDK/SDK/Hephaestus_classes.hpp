#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Hephaestus

#include "Basic.hpp"

#include "Engine_classes.hpp"


namespace SDK
{

// Class Hephaestus.HephaestusBPLibrary
// 0x0000 (0x0028 - 0x0028)
class UHephaestusBPLibrary final : public UBlueprintFunctionLibrary
{
public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"HephaestusBPLibrary">();
	}
	static class UHephaestusBPLibrary* GetDefaultObj()
	{
		return GetDefaultObjImpl<UHephaestusBPLibrary>();
	}
};
//static_assert(alignof(UHephaestusBPLibrary) == 0x000008, "Wrong alignment on UHephaestusBPLibrary");
//static_assert(sizeof(UHephaestusBPLibrary) == 0x000028, "Wrong size on UHephaestusBPLibrary");

}
