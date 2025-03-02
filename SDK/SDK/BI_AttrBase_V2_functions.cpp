#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BI_AttrBase_V2

#include "Basic.hpp"

#include "BI_AttrBase_V2_classes.hpp"
#include "BI_AttrBase_V2_parameters.hpp"


namespace SDK
{

// Function BI_AttrBase_V2.BI_AttrBase_V2_C.SequenceEvent__ENTRYPOINTBI_AttrBase_V2_1
// (Public, BlueprintCallable, BlueprintEvent)

void UBI_AttrBase_V2_C::SequenceEvent__ENTRYPOINTBI_AttrBase_V2_1()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BI_AttrBase_V2_C", "SequenceEvent__ENTRYPOINTBI_AttrBase_V2_1");

	UObject::ProcessEvent(Func, nullptr);
}


// Function BI_AttrBase_V2.BI_AttrBase_V2_C.SequenceEvent__ENTRYPOINTBI_AttrBase_V2_0
// (Public, BlueprintCallable, BlueprintEvent)

void UBI_AttrBase_V2_C::SequenceEvent__ENTRYPOINTBI_AttrBase_V2_0()
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BI_AttrBase_V2_C", "SequenceEvent__ENTRYPOINTBI_AttrBase_V2_0");

	UObject::ProcessEvent(Func, nullptr);
}


// Function BI_AttrBase_V2.BI_AttrBase_V2_C.SequenceEvent_0
// (BlueprintCallable, BlueprintEvent)
// Parameters:
// class FString                           EventName                                              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, HasGetValueTypeHash)

void UBI_AttrBase_V2_C::SequenceEvent_0(const class FString& EventName)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BI_AttrBase_V2_C", "SequenceEvent_0");

	Params::BI_AttrBase_V2_C_SequenceEvent_0 Parms{};

	Parms.EventName = std::move(EventName);

	UObject::ProcessEvent(Func, &Parms);
}


// Function BI_AttrBase_V2.BI_AttrBase_V2_C.PreConstruct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// bool                                    IsDesignTime                                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBI_AttrBase_V2_C::PreConstruct(bool IsDesignTime)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BI_AttrBase_V2_C", "PreConstruct");

	Params::BI_AttrBase_V2_C_PreConstruct Parms{};

	Parms.IsDesignTime = IsDesignTime;

	UObject::ProcessEvent(Func, &Parms);
}


// Function BI_AttrBase_V2.BI_AttrBase_V2_C.ExecuteUbergraph_BI_AttrBase_V2
// (Final, UbergraphFunction)
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UBI_AttrBase_V2_C::ExecuteUbergraph_BI_AttrBase_V2(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("BI_AttrBase_V2_C", "ExecuteUbergraph_BI_AttrBase_V2");

	Params::BI_AttrBase_V2_C_ExecuteUbergraph_BI_AttrBase_V2 Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}

}

