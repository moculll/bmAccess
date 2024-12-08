#pragma once
#include <windows.h>
#include <Psapi.h>
#include <future>
#include "include/MinHook.h"
#include "common.h"
#include "mocIPC.h"
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#pragma warning(push)
#pragma warning(disable: 4267)

#define DEBUG_PRINT_ENABLE 1


#define DEBUG_WRITE(path, fmt, ...) \
        do { \
                char buf_FILE[384]; \
                snprintf(buf_FILE, 384, ""fmt"\n", ##__VA_ARGS__); \
                writeDebugInfoToFile(path, buf_FILE); \
        } while (0);

namespace Memory
{

template<typename T>
void Write(uintptr_t writeAddress, T value)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)(writeAddress), sizeof(T), PAGE_EXECUTE_WRITECOPY, &oldProtect);
	*(reinterpret_cast<T*>(writeAddress)) = value;
	VirtualProtect((LPVOID)(writeAddress), sizeof(T), oldProtect, &oldProtect);
}

void PatchBytes(uintptr_t address, const char* pattern, unsigned int numBytes)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)address, numBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)address, pattern, numBytes);
	VirtualProtect((LPVOID)address, numBytes, oldProtect, &oldProtect);
}

std::uint8_t* PatternScan(void* module, const char* signature)
{
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
		};

	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return &scanBytes[i];
		}
	}
	return nullptr;
}

static HMODULE GetThisDllHandle()
{
	MEMORY_BASIC_INFORMATION info;
	size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetThisDllHandle, &info, sizeof(info));
	assert(len == sizeof(info));
	return len ? (HMODULE)info.AllocationBase : NULL;
}

uint32_t ModuleTimestamp(void* module)
{
	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);
	return ntHeaders->FileHeader.TimeDateStamp;
}

uintptr_t GetAbsolute(uintptr_t address) noexcept
{
	return (address + 4 + *reinterpret_cast<std::int32_t*>(address));
}

} /* namespace Memory */





struct blackMyth {
	inline static HANDLE hConsoleOut;
	inline static HANDLE hConsoleIn;

	struct SDKMgr {
		std::map<std::string, void*> data;

		bool registPtr(std::string key, void* ptr)
		{
			DEBUG_PRINT("[registered] %s:%llx", key.c_str(), ptr);
			data[key] = ptr;
			return true;
		}

		template<typename T>
		T get(std::string key)
		{
			auto it = data.find(key);
			if (it != data.end()) {
				return reinterpret_cast<T>(it->second);
			}
			return nullptr;
		}


	};

	inline static SDKMgr sdkMgr;
	inline static char loggerBuffer[512];
	inline static std::vector<std::wstring> textQueue;
	inline static std::map<std::string, int> mMap;

	using fn = void(__thiscall*)(SDK::UGameViewportClient*, SDK::UObject*);
	using pevent_fn = void(__thiscall*)(SDK::UObject*, SDK::UObject*, void* params);
	inline static pevent_fn processEventOriginal = 0;
	inline static fn postRenderOriginal = 0;

	struct enemyAttr {
		float delta;
		float Hp;
	};

	

	inline static std::map<std::string, enemyAttr> aiCharacterMap;
	static void writeDebugInfoToFile(const char* filePath, const std::string& debugMessage)
	{
		HANDLE hFile = CreateFileA(
			filePath,
			FILE_APPEND_DATA,
			FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE) {
			DEBUG_PRINT("Unable to open file: %d", GetLastError());
			return;
		}

		std::string messageWithNewline = debugMessage + "\n";
		DWORD bytesWritten;
		BOOL result = WriteFile(
			hFile,
			messageWithNewline.c_str(),
			messageWithNewline.length(),
			&bytesWritten,
			NULL
		);

		if (!result)
			DEBUG_PRINT("Failed to write to file: %d", GetLastError());

		CloseHandle(hFile);
	}



	static bool DataCompare(PBYTE pData, PBYTE bSig, char* szMask)
    {
        for (; *szMask; ++szMask, ++pData, ++bSig)
        {
            if (*szMask == 'x' && *pData != *bSig)
                return false;
        }
        return (*szMask) == 0;
    }

    static PBYTE FindPattern(PBYTE dwAddress, DWORD dwSize, PBYTE pbSig, const char* szMask, long offset)
    {
        size_t length = strlen(szMask);
        char* ptr = (char*)(szMask);
        for (size_t i = NULL; i < dwSize - length; i++)
        {
            if (DataCompare(dwAddress + i, pbSig, ptr))
                return dwAddress + i + offset;
        }
        return nullptr;
    }

    static void post_render_hook(SDK::UGameViewportClient* viewport_client, SDK::UObject* canvas) {
		postRenderOriginal(viewport_client, canvas);
		
    }


	void DebugPrint(const wchar_t* text) {
		const size_t chunkSize = 10;
		wchar_t chunkBuffer[chunkSize + 1];
		size_t len = wcslen(text);

		for (size_t i = 0; i < len; i += chunkSize) {

			size_t charactersToCopy = (i + chunkSize > len) ? len - i : chunkSize;

			wcsncpy_s(chunkBuffer, text + i, charactersToCopy);

			chunkBuffer[charactersToCopy] = L'\0';

			WriteConsoleW(hConsoleOut, chunkBuffer, charactersToCopy, NULL, NULL);

			WriteConsoleW(hConsoleOut, "\n", 1, NULL, NULL);
		}
	}

	static void DEBUG_PRINT(const char* fmt, ...)
	{
#if DEBUG_PRINT_ENABLE
		va_list args;
		va_start(args, fmt);

		int len = vsnprintf(loggerBuffer, sizeof(loggerBuffer) - 2, fmt, args);
		va_end(args);

		if (len >= 0 && len < sizeof(loggerBuffer) - 1) {
			loggerBuffer[len] = '\n';
			loggerBuffer[len + 1] = '\0';
		}
		else {

			loggerBuffer[sizeof(loggerBuffer) - 2] = '\n';
			loggerBuffer[sizeof(loggerBuffer) - 1] = '\0';
		}

		WriteConsoleA(hConsoleOut, loggerBuffer, strlen(loggerBuffer), NULL, NULL);
#endif
	}

	static std::string WCharToChar(const wchar_t* wStr)
	{

		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wStr, -1, nullptr, 0, nullptr, nullptr);
		if (bufferSize == 0) {

			return "";
		}

		char* buffer = new char[bufferSize];

		WideCharToMultiByte(CP_UTF8, 0, wStr, -1, buffer, bufferSize, nullptr, nullptr);

		std::string result(buffer);

		delete[] buffer;

		return result;
	}
	
    static void process_event_hook(SDK::UObject* caller, SDK::UObject* fn, void* params)
	{
		processEventOriginal(caller, fn, params);
		if (sdkMgr.get<SDK::UObject*>("Function b1.BGUFunctionLibrary.GetPlayerCharacter") == fn) {

			
		}
		
		if (sdkMgr.get<SDK::UObject*>("Function b1-Managed.BUI_Widget.OnAddedToFocusPath") == fn) {

			/*textblocks.clear();*/

		}

		if (sdkMgr.get<SDK::UObject*>("Function UMG.TextBlock.SetText") == fn /*&& strstr(caller->GetName().c_str(), "TxtName") != nullptr*/) {
			/*if (textblocks.find(caller) == textblocks.end()) {
				textblocks.insert(caller);
			}*/
			SDK::UTextBlock* textblock = (SDK::UTextBlock*)caller;
			
			

			/*DEBUG_PRINT("[setText_fn][TxtName]: %s, textname: %llx, widgetTree: %llx, outer: %llx", caller->GetFullName().c_str(), caller, caller->Outer, caller->Outer->Outer);*/
		}

		if (sdkMgr.get<SDK::UObject*>("Function b1-Managed.BUI_Button.OnAddedToFocusPath") == fn) {
			
			SDK::UBUI_Button *button = (SDK::UBUI_Button *)caller;
			

			/*DEBUG_PRINT("[%s]:%llx, [%s]:%llx, [%s]:%llx", caller->GetName().c_str(),caller, caller->Outer->Outer->GetName().c_str(), caller->Outer->Outer, caller->Outer->Outer->Outer->Outer->GetName().c_str(), caller->Outer->Outer->Outer->Outer);*/
			//if(button->GSParentButtonUIStat == )
			for (int i = 0; i < button->UIDataConfigMap.Num(); i++) {
				auto data = button->UIDataConfigMap[i];
				
				if ((data.First == SDK::EButtonUIStat::Focused) /*|| (data.First == SDK::EButtonUIStat::Normal) || (data.First == SDK::EButtonUIStat::LockFocused)*/) {
					auto uidata = data.Second;
					for (int j = 0; j < uidata.Text.Num(); j++) {
						auto textdata = uidata.Text[j];
						DEBUG_PRINT("[focusedWidgetName][%d]: %s", data.First, textdata.WidgetName.ToString().c_str());
						SDK::TArray<class SDK::UWidget*> childs = (sdkMgr.get<SDK::UGSE_UMGFuncLib*>("UMGLib"))->GetAllChildWidget((SDK::UUserWidget*)caller);

						for (int i = 0; i < childs.Num(); i++) {
							class SDK::UWidget* child = childs[i];
							DEBUG_PRINT("child[%d]: name: %s, class: %s", i, child->GetName().c_str(), child->Class->GetName().c_str());
							if (!child->Class)
								continue;
							if (strcmp(child->GetName().c_str(), textdata.WidgetName.ToString().c_str()) == 0 ) {
								UC::FString stng = (sdkMgr.get<SDK::UKismetTextLibrary*>("KismetLib"))->Conv_TextToString(((SDK::UTextBlock*)child)->Text);
								DEBUG_PRINT("[UIStat][%s]: %s", child->Class->GetName().c_str(), stng.ToString().c_str());
								std::wstring news = stng.ToWString();
								
								textQueue.emplace_back(std::move(news));
								
							}
						}

					}
					
				}
			}
			
		}
		

		if (sdkMgr.get<SDK::UObject*>("Function b1.BGUCharacterMovementComponent.TryGetCurNormalFromMovement") == fn && caller->Outer != sdkMgr.get<SDK::UObject*>("playerCharacter")) {
			SDK::ACharacter* aiCharacter = ((SDK::UCharacterMovementComponent*)caller)->CharacterOwner;
			SDK::ACharacter* playerCharacter = sdkMgr.get<SDK::ACharacter*>("playerCharacter");
			if (aiCharacter) {
				
				auto location = aiCharacter->K2_GetActorLocation();
				if (playerCharacter) {
					auto location2 = playerCharacter->K2_GetActorLocation();
					float result = static_cast<float>(sqrt((location.X - location2.X) * (location.X - location2.X) + (location.Y - location2.Y) * (location.Y - location2.Y) + (location.Z - location2.Z) * (location.Z - location2.Z)));
					float enemyHp = (sdkMgr.get<SDK::UBGUFunctionLibraryCS*>("BGULib"))->BGUGetFloatAttr(aiCharacter, SDK::EBGUAttrFloat::Hp);
					DEBUG_PRINT("name: %s, DELTA: %.5f, HP: %.5f", aiCharacter->GetName().c_str(), result, enemyHp);

					aiCharacterMap[aiCharacter->GetName()] = { result,enemyHp };
				}
			}
		}

		if (sdkMgr.get<SDK::UObject*>("Function b1.BGUFunctionLibrary.GetPlayerCharacter") == fn) {
			SDK::UBGUFunctionLibraryCS *BGULib = sdkMgr.get<SDK::UBGUFunctionLibraryCS*>("BGULib");
			struct param_t {
				SDK::UObject* WorldContextObject;
				SDK::ACharacter* character;
			} *param;
			param = (param_t*)params;

			SDK::ACharacter* playerCharacter = param->character;
			SDK::UGameplayStatics* GameplayStatics = sdkMgr.get<SDK::UGameplayStatics*>("GameplayStatics");
			if (!playerCharacter) {
				sdkMgr.registPtr("playerCharacter", nullptr);
				return;
			}

			sdkMgr.registPtr("playerCharacter", reinterpret_cast<void*>(param->character));
			auto location = playerCharacter->K2_GetActorLocation();

			DEBUG_PRINT("location: x: %.5f, y:%.5f, z:%.5f", location.X, location.Y, location.Z);

			float playerHp = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::Hp);
			float playerMp = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::Mp);
			float playerFreeze = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::FreezeAbnormalAcc);
			float playerBurn = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::BurnAbnormalAcc);
			float playerPoison = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::PoisonAbnormalAcc);
			float playerThunder = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::ThunderAbnormalAcc);
			float playerBloodButton = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::BloodBottomNum);
			float playerEnergy = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::CurEnergy);
			float playerStamina = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::Stamina);
			float playerStaminaRecover = BGULib->BGUGetFloatAttr(playerCharacter, SDK::EBGUAttrFloat::StaminaRecover);

			/*DEBUG_PRINT("hp: %.0f, mp: %.0f, Stamina: %.0f, recover: %.0f, freeze: %.0f, burn: %.0f, posion: %.0f, thunder: %.0f, bloodButton: %.0f, energy: %.0f", playerHp, playerMp, playerStamina, playerStaminaRecover, playerFreeze, playerBurn, playerPoison, \
				playerThunder, playerBloodButton, playerEnergy);*/

			std::string currentLevelName(GameplayStatics->GetCurrentLevelName(param->WorldContextObject, false).ToString());
			
			
			
			int levelId = 0;
			auto mapContainer = mMap.find(currentLevelName);
			if (mapContainer != mMap.end()) {
				levelId = mapContainer->second;
			}
			/* DEBUG_PRINT("current level: %s, id: %d", currentLevelName.c_str(), levelId); */

			CommonData::levelInfoBuffer.event = CommonData::event_t::EVENT_LEVELINFO;
			CommonData::levelInfoBuffer.levelInfo.levelId = levelId;
			
			
			/* SDK::UGSE_WorldFuncLib *worldfunclib = sdkMgr.get<SDK::UGSE_WorldFuncLib*>("WorldFuncLib"); */

			
			/* DEBUG_PRINT("current levelName: %s", (SDK::UWorld::GetWorld())->PersistentLevel->Outer->GetName().c_str()); */
			

			CommonData::infoBuffer.event = CommonData::event_t::EVENT_PLAYER_INFO;
			CommonData::infoBuffer.playerInfo = { playerHp , playerMp , playerFreeze , playerBurn , playerPoison , playerThunder , playerBloodButton , playerEnergy , playerStamina , playerStaminaRecover };

			/*memset(&CommonData::locationBuffer, 0, sizeof(CommonData::locationBuffer));*/
			CommonData::locationBuffer.event = CommonData::event_t::EVENT_PLAYER_LOCATION;
			CommonData::locationBuffer.playerLocation = { location.X, location.Y, location.Z };

			CommonData::gameStatus.event = CommonData::event_t::EVENT_GAMEINITED_RESULT;
			CommonData::gameStatus.gameInited = 1;


		}
		
		
		if ( (sdkMgr.get<SDK::UObject*>("Function b1-Managed.BUI_Button.OnAddedToFocusPath") == fn) || (sdkMgr.get<SDK::UObject*>("Function b1-Managed.BUI_Widget.OnAddedToFocusPath") == fn)/*|| (fn == inputFocusChanging_fn) || (fn == userFocusChange_fn) || (fn == buiFocusChange_fn)*/ /* || (fn == inputFocusChanging_fn) */ ) {

			SDK::TArray<class SDK::UWidget*> childs = (sdkMgr.get<SDK::UGSE_UMGFuncLib*>("UMGLib"))->GetAllChildWidget((SDK::UUserWidget*)caller);
			
			for (int i = 0; i < childs.Num(); i++) {
				class SDK::UWidget* child = childs[i];
				/*DEBUG_PRINT("child[%d]: name: %s, class: %s", i, child->GetName().c_str(), child->Class->GetName().c_str());*/
				if(!child->Class)
					continue;
				
					DEBUG_PRINT("[access]: %s", (sdkMgr.get<SDK::UKismetTextLibrary*>("KismetLib"))->Conv_TextToString(((SDK::UWidget*)child)->GetAccessibleSummaryText()).ToString().c_str());
					if (strcmp(child->GetName().c_str(), "TxtName") == 0 || strcmp(child->GetName().c_str(), "TxtOwn") == 0\
						/*|| strcmp(child->GetName().c_str(), "TxtLevel") == 0 || strcmp(child->GetName().c_str(), "TxtLevelUnfold") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtLevelTitle") == 0 || strcmp(child->GetName().c_str(), "TxtExpNow") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtExpSlash") == 0 || strcmp(child->GetName().c_str(), "TxtExpTotal") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtAttrTitleA") == 0 || strcmp(child->GetName().c_str(), "TxtAttrTitleA_1") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtWBTips") == 0 || strcmp(child->GetName().c_str(), "TxtNameRuby") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtCostTItle") == 0 || strcmp(child->GetName().c_str(), "TxtAttrTitleA_1") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtInputTips") == 0 || strcmp(child->GetName().c_str(), "TxtSkillName") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtSkillDesc") == 0 || strcmp(child->GetName().c_str(), "TxtHuluDesc") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtActiveTitle") == 0 || strcmp(child->GetName().c_str(), "TxtActiveDesc") == 0 \
						|| strcmp(child->GetName().c_str(), "TxtPassiveTitle") == 0 || strcmp(child->GetName().c_str(), "TxtQuickItemTitleRuby") == 0 */) {
						UC::FString stng = (sdkMgr.get<SDK::UKismetTextLibrary*>("KismetLib"))->Conv_TextToString(((SDK::UTextBlock*)child)->Text);
						DEBUG_PRINT("[OUT][%s]: %s", child->Class->GetName().c_str(), stng.ToString().c_str());
						std::wstring news = stng.ToWString();
						
						textQueue.emplace_back(std::move(news));
						
						
					}
					
				if (strstr(child->Class->GetName().c_str(), "BI_") != nullptr || strstr(child->Class->GetName().c_str(), "BUI_") != nullptr || strstr(child->Class->GetName().c_str(), "UBP_UI_") != nullptr) {
					SDK::TArray<class SDK::UWidget*> childusers = (sdkMgr.get<SDK::UGSE_UMGFuncLib*>("UMGLib"))->GetAllChildWidget((SDK::UUserWidget*)child);
					
					for (int j = 0; j < childusers.Num(); j++) {
						class SDK::UWidget* childuser = childusers[j];
						if (!childuser->Class)
							continue;
						/*DEBUG_PRINT("child[%d]: name: %s, class: %s", i, childuser->GetName().c_str(), childuser->Class->GetName().c_str());*/
						if (strcmp(childuser->GetName().c_str(), "TxtName") == 0 || strcmp(childuser->GetName().c_str(), "TxtOwn") == 0) {
							UC::FString stng = (sdkMgr.get<SDK::UKismetTextLibrary*>("KismetLib"))->Conv_TextToString(((SDK::UTextBlock*)childuser)->Text);
							DEBUG_PRINT("[IN][%s]: %s", childuser->Class->GetName().c_str(), stng.ToString().c_str());
							std::wstring news = stng.ToWString();
							
							textQueue.emplace_back(std::move(news));
							
						}
						
						if (strstr(childuser->Class->GetName().c_str(), "BI_") != nullptr || strstr(childuser->Class->GetName().c_str(), "BUI_") != nullptr || strstr(child->Class->GetName().c_str(), "UBP_UI_") != nullptr) {
							SDK::TArray<class SDK::UWidget*> childchildusers = (sdkMgr.get<SDK::UGSE_UMGFuncLib*>("UMGLib"))->GetAllChildWidget((SDK::UUserWidget*)childuser);
						
							for (int k = 0; k < childchildusers.Num(); k++) {
								class SDK::UWidget* childchilduser = childchildusers[k];
								if (strcmp(childchilduser->GetName().c_str(), "TxtName") == 0 || strcmp(childchilduser->GetName().c_str(), "TxtOwn") == 0) {
									UC::FString stng = (sdkMgr.get<SDK::UKismetTextLibrary*>("KismetLib"))->Conv_TextToString(((SDK::UTextBlock*)childchilduser)->Text);
									DEBUG_PRINT("[%s]: %s", childchilduser->Class->GetName().c_str(), stng.ToString().c_str());
									std::wstring news = stng.ToWString();

									textQueue.emplace_back(std::move(news));
								}
							
							}
						
						}


					}
				}
			}
			

			

		}
		
		
		/*if (fn == hitmove_fn) {
			SDK::UBGUDataComp *comp = (SDK::UBGUDataComp*)caller;
			if(!(comp->MUBUC_ACharacterComponent->OwnerCharacter && comp->MUBUC_ACharacterComponent->OwnerCharacter->AIControllerClass && comp->MUBUC_ACharacterComponent->OwnerCharacter->Outer))
				return;
			SDK::APawn *character = (SDK::APawn*)comp->MUBUC_ACharacterComponent->OwnerCharacter->AIControllerClass->OuterPrivate;
			auto location = character->K2_GetActorLocation();
			if (playerCharacter) {
				auto location2 = playerCharacter->K2_GetActorLocation();
				float result = sqrt((location.X - location2.X) * (location.X - location2.X) + (location.Y - location2.Y) * (location.Y - location2.Y) + (location.Z - location2.Z) * (location.Z - location2.Z));
				DEBUG_PRINT("name: %s, DELTA: %.5f", aiCharacter->GetName(GNamePool).c_str(), result);
			}
		}*/
		/*if (fn == playerApproached_fn) {
			TArray<AActor*> actorarray;
			actorarray.Count = 0;
			defaultBGU->GetAllActorsInWorld(getAllActorsInWorld_fn, GWorld, &actorarray);
			DEBUG_PRINT("actor number: %d", actorarray.Count)
			for (int i = 0; i < actorarray.Count; i++) {
				AActor *actor = actorarray.Data[i];

				auto location = actor->K2_GetPawn(K2_GetPawn_fn)->K2_GetActorLocation(K2_GetActorLocation_fn);
				if (playerCharacter) {
					auto location2 = playerCharacter->K2_GetActorLocation(K2_GetActorLocation_fn);
					float result = sqrt((location.X - location2.X) * (location.X - location2.X) + (location.Y - location2.Y) * (location.Y - location2.Y) + (location.Z - location2.Z) * (location.Z - location2.Z));
					DEBUG_PRINT("name: %s, DELTA: %.5f", aiCharacter->GetName(GNamePool).c_str(), result);
				}
			}
			
		}*/

		
		
		
    }

    blackMyth()
    {
		
    }

	bool deinit()
	{

		MH_DisableHook(sdkMgr.get<LPVOID>("ProcessEvent"));
		MH_RemoveHook(sdkMgr.get<LPVOID>("ProcessEvent"));
		MH_Uninitialize();

		
#if DEBUG_PRINT_ENABLE
		FreeConsole();
#endif
		return true;
	}
	
    bool init()
    {
#if DEBUG_PRINT_ENABLE
		system("chcp 65001");
		AllocConsole();
		hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
#endif
		MH_Initialize();
		MODULEINFO info;
		DWORD_PTR BaseAddress = (DWORD_PTR)GetModuleHandle(NULL);
		while (!BaseAddress) {
			BaseAddress = (DWORD_PTR)GetModuleHandle(NULL);
			Sleep(1000);
		}
			

		GetModuleInformation(GetCurrentProcess(), (HMODULE)BaseAddress, &info, sizeof(info));
		
		uint8_t* GObjectsScanResult = Memory::PatternScan((void *)BaseAddress, "48 8B ?? ?? ?? ?? ?? 48 8B ?? ?? 48 8D ?? ?? EB ?? 33 ?? 8B ?? ?? C1 e8 ?? a8 ?? 75 16");
		if (GObjectsScanResult) {
			/*DEBUG_PRINT("Offsets: GObjects: Address is {%s}+{%llx}", "blackmyth", (uintptr_t)GObjectsScanResult - (uintptr_t)BaseAddress);*/
			uintptr_t GObjectsAddr = Memory::GetAbsolute((uintptr_t)GObjectsScanResult + 0x3);
			SDK::Offsets::GObjects = (UC::int32)((uintptr_t)GObjectsAddr - (uintptr_t)BaseAddress);

			/*DEBUG_PRINT("Offsets: GObjects: Offset: {%llx}", SDK::Offsets::GObjects);*/
		}
		else {
			DEBUG_PRINT("Offsets: GObjects: Pattern scan failed.");
			return false;
		}

		/* necessary for SDK register */
		uint8_t* AppendStringScanResult = Memory::PatternScan((void*)BaseAddress, "48 89 ?? ?? ?? 57 48 83 ?? ?? 80 3D ?? ?? ?? ?? 00 48 8B ?? 48 8B ?? 74 ?? 4C 8D ?? ?? ?? ?? ?? EB ?? 48 8D ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 4C ?? ?? C6 ?? ?? ?? ?? ?? 01 8B ?? 8B ?? 0F ?? ?? C1 ?? 10 89 ?? ?? ?? 89 ?? ?? ?? 48 8B ?? ?? ?? 48 ?? ?? ?? 8D ?? ?? 49 ?? ?? ?? ?? 48 8B ?? E8 ?? ?? ?? ?? 83 ?? ?? 00");
		if (AppendStringScanResult) {
			DEBUG_PRINT("Offsets: AppendString: Address is +{%llx}", (uintptr_t)AppendStringScanResult - (uintptr_t)BaseAddress);
			SDK::Offsets::AppendString = (UC::int32)((uintptr_t)AppendStringScanResult - (uintptr_t)BaseAddress);
			DEBUG_PRINT("Offsets: AppendString: Offset: {%llx}", SDK::Offsets::AppendString);
		}
		else {
			DEBUG_PRINT("Offsets: AppendString: Pattern scan failed.");
			return false;
		}

		uint8_t* ProcessEventScanResult = Memory::PatternScan((void*)BaseAddress, "40 ?? 56 57 41 ?? 41 ?? 41 ?? 41 ?? 48 ?? ?? ?? ?? ?? ?? 48 8D ?? ?? ?? 48 89 ?? ?? ?? ?? ?? 48 8B ?? ?? ?? ?? ?? 48 ?? ?? 48 89 ?? ?? ?? ?? ?? 4D ?? ?? 48 ?? ?? 4C ?? ?? 48 ?? ??");
		
		/*auto AddrUWorld = Memory::PatternScan((void*)BaseAddress, "48 8b 1d ?? ?? ?? ?? 48 85 db 74 33 41 b0 01 33 d2");
		auto OffUWorld = *reinterpret_cast<uint32_t*>(AddrUWorld + 3);
		auto UWorldPtr = AddrUWorld + 7 + OffUWorld;
		SDK::UWorld *GWorld = (*(SDK::UWorld**)UWorldPtr);
		DEBUG_PRINT("UWorldPtr: %llx, GWorld: %llx", UWorldPtr, GWorld);
		ProcessEventScanResult = (uint8_t *)GWorld->GetProcessEventAddr();*/

		if (ProcessEventScanResult) {
			DEBUG_PRINT("Offsets: ProcessEvent: Address is+{%llx}", (uintptr_t)ProcessEventScanResult - (uintptr_t)BaseAddress);
			SDK::Offsets::ProcessEvent = (UC::int32)((uintptr_t)ProcessEventScanResult - (uintptr_t)BaseAddress);

			sdkMgr.registPtr("ProcessEvent", reinterpret_cast<void *>(ProcessEventScanResult));

			MH_STATUS ret = MH_CreateHook(reinterpret_cast<LPVOID>(ProcessEventScanResult), &process_event_hook, reinterpret_cast<void**>(&processEventOriginal));
			DEBUG_PRINT("Offsets: ProcessEvent: Offset: {%llx}", SDK::Offsets::ProcessEvent);
		}
		else {
			DEBUG_PRINT("Offsets: ProcessEvent: Pattern scan failed.");
			return false;
		}
		

		
		sdkMgr.registPtr("Function Engine.Actor.K2_GetActorLocation", reinterpret_cast<void*>(SDK::UObject::FindObject("Function Engine.Actor.K2_GetActorLocation")));
		sdkMgr.registPtr("Function Engine.Actor.K2_SetActorLocation", reinterpret_cast<void*>(SDK::UObject::FindObject("Function Engine.Actor.K2_SetActorLocation")));
		sdkMgr.registPtr("Function Engine.Controller.K2_GetPawn", reinterpret_cast<void*>(SDK::UObject::FindObject("Function Engine.Controller.K2_GetPawn")));
		sdkMgr.registPtr("Function b1.BGUFunctionLibrary.GetPlayerCharacter", reinterpret_cast<void*>(SDK::UObject::FindObject("Function b1.BGUFunctionLibrary.GetPlayerCharacter")));
		sdkMgr.registPtr("Function b1.BGUCharacterMovementComponent.TryGetCurNormalFromMovement", reinterpret_cast<void*>(SDK::UObject::FindObject("Function b1.BGUCharacterMovementComponent.TryGetCurNormalFromMovement")));
		sdkMgr.registPtr("Function UMG.TextBlock.SetText", reinterpret_cast<void*>(SDK::UObject::FindObject("Function UMG.TextBlock.SetText")));
		sdkMgr.registPtr("Function b1-Managed.BUI_Button.OnAddedToFocusPath", reinterpret_cast<void*>(SDK::UObject::FindObject("Function b1-Managed.BUI_Button.OnAddedToFocusPath")));
		sdkMgr.registPtr("Function UMG.UserWidget.OnAddedToFocusPath", reinterpret_cast<void*>(SDK::UObject::FindObject("Function UMG.UserWidget.OnAddedToFocusPath")));
		sdkMgr.registPtr("Function b1-Managed.BUI_Widget.OnAddedToFocusPath", reinterpret_cast<void*>(SDK::UObject::FindObject("Function b1-Managed.BUI_Widget.OnAddedToFocusPath")));
		sdkMgr.registPtr("Function UnrealExtent.GSE_UMGFuncLib.CreateUserWidgetWithClass", reinterpret_cast<void*>(SDK::UObject::FindObject("Function UnrealExtent.GSE_UMGFuncLib.CreateUserWidgetWithClass")));
		sdkMgr.registPtr("Function GSInput.GSInputWidget.OnFocusChanging", reinterpret_cast<void*>(SDK::UObject::FindObject("Function GSInput.GSInputWidget.OnFocusChanging")));
		sdkMgr.registPtr("Function UMG.Widget.SetFocus", reinterpret_cast<void*>(SDK::UObject::FindObject("Function UMG.Widget.SetFocus")));
		sdkMgr.registPtr("UMGLib", reinterpret_cast<void*>(SDK::UGSE_UMGFuncLib::GetDefaultObj()));
		sdkMgr.registPtr("KismetLib", reinterpret_cast<void*>(SDK::UKismetTextLibrary::GetDefaultObj()));
		sdkMgr.registPtr("BGULib", reinterpret_cast<void*>(SDK::UBGUFunctionLibraryCS::GetDefaultObj()));
		sdkMgr.registPtr("GameplayStatics", reinterpret_cast<void*>(SDK::UGameplayStatics::GetDefaultObj()));
		sdkMgr.registPtr("WorldFuncLib", reinterpret_cast<void*>(SDK::UGSE_WorldFuncLib::GetDefaultObj()));

		/*process_event_addr = SDK::UWorld::GetWorld()->GetProcessEventAddr();
		DEBUG_PRINT("processEventAddr: %llx", process_event_addr);*/
		mMap.insert(std::pair<std::string, int>("LYS_paintingworld_01", 31));               // 如意画轴-六六村
		mMap.insert(std::pair<std::string, int>("HFS01_PersistentLevel", 10));               // 黑风山
		mMap.insert(std::pair<std::string, int>("HFS01_Old_GYCY_YKX_PersistentLevel", 11));  // 隐·旧观音禅院
		mMap.insert(std::pair<std::string, int>("HFS_WoodDragon", 12));                      // 黑风山-尺木间
		mMap.insert(std::pair<std::string, int>("HFM02_PersistentLevel", 20));               // 黄风岭
		mMap.insert(std::pair<std::string, int>("HFM_DuJiaoXian_Persist", 25));              // 隐·斯哈里国
		mMap.insert(std::pair<std::string, int>("HFM_DustDragon_01", 24));                  // 黄风岭-藏龙洞
		mMap.insert(std::pair<std::string, int>("LYS_PersistentLevel", 30));                 // 小西天
		mMap.insert(std::pair<std::string, int>("PSD_PersistentLevel", 40));                 // 盘丝岭
		mMap.insert(std::pair<std::string, int>("ZYS01_persistentlevel", 80));               // 隐·紫云山
		mMap.insert(std::pair<std::string, int>("HYS_PersistentLevel", 50));                 // 火焰山
		mMap.insert(std::pair<std::string, int>("BYS_persistentlevel", 98));                 // 花果山
		mMap.insert(std::pair<std::string, int>("BSD02_persistentlevel", 70));               // 隐·壁水洞

		for (auto &it : mMap) {
			DEBUG_PRINT("added [%s]:[%d] to mMap", it.first.c_str(), it.second);
		}

		/* DEBUG_PRINT("K2_GetActorLocation_fn: %llx, K2_GetPawn_FN: %llx", (uintptr_t)K2_GetActorLocation_fn, (uintptr_t)K2_GetPawn_fn);
		DEBUG_PRINT("K2_GetActorLocation_fn: %llx, K2_GetPawn_FN: %llx", (uintptr_t)BGUGetFloatAttr_fn, (uintptr_t)K2_GetPawn_fn);
		DEBUG_PRINT("defaultCS: %llx", (uintptr_t)defaultCS);
		DEBUG_PRINT("defaultBGU: %llx", (uintptr_t)defaultBGU);
		DEBUG_PRINT("GetPlayerCharacter: %llx", (uintptr_t)GetPlayerCharacter_fn);
		DEBUG_PRINT("GetPlayerCharacter: %llx", (uintptr_t)GetMovement_fn);
		DEBUG_PRINT("GetPlayerCharacter: %llx", (uintptr_t)playerStateGetPawn_fn);
		DEBUG_PRINT("playerApproached_fn: %llx", (uintptr_t)playerApproached_fn);
		DEBUG_PRINT("getAllActorsInWorld_fn: %llx", (uintptr_t)getAllActorsInWorld_fn);
		DEBUG_PRINT("hitmove_fn: %llx", (uintptr_t)hitmove_fn);
		DEBUG_PRINT("setText_fn: %llx", (uintptr_t)setText_fn);
		DEBUG_PRINT("richSetText_fn: %llx", (uintptr_t)richSetText_fn);
		DEBUG_PRINT("buttonFocusChange_fn: %llx", (uintptr_t)buttonFocusChange_fn);
		DEBUG_PRINT("userFocusChange_fn: %llx", (uintptr_t)userFocusChange_fn);
		DEBUG_PRINT("buiFocusChange_fn: %llx", (uintptr_t)buiFocusChange_fn);
		DEBUG_PRINT("widgetInit_fn: %llx", (uintptr_t)widgetInit_fn);
		DEBUG_PRINT("setbyname_fn: %llx", (uintptr_t)setbyname_fn);
		DEBUG_PRINT("setbytext_fn: %llx", (uintptr_t)setbytext_fn);
		DEBUG_PRINT("setbytext_fn: %llx", (uintptr_t)inputFocusChanging_fn);
		DEBUG_PRINT("setbytext_fn: %llx", (uintptr_t)gsFocusChanging_fn); */
		if(MH_OK != MH_EnableHook(sdkMgr.get<LPVOID>("ProcessEvent"))) {
			DEBUG_PRINT("ProcessEvent failed");
			return false;
		}
		
		CommonData::gameStatus.event = CommonData::event_t::EVENT_GAMEINITED_RESULT;
		CommonData::gameStatus.gameInited = 0;

		return true;

    }

	void exit()
	{

	}


};


class dataMgr {
public:

	dataMgr() {}
	bool running;
	~dataMgr()
	{
		
	}

	void exit()
	{
		running = false;
	}

	static void testRecv(void* arg)
	{

		if(MocIPC::getArg<CommonData::gameInfo_t*>(arg)->event & CommonData::event_t::EVENT_PLAYER_LOCATION_SET) {
			CommonData::config.targetPlayerLocation = MocIPC::getArg<CommonData::gameInfo_t*>(arg)->targetPlayerLocation;
			if(!gameInstance->sdkMgr.get<SDK::ACharacter*>("playerCharacter"))
				return;
			auto pawn = (gameInstance->sdkMgr.get<SDK::ACharacter*>("playerCharacter"))->PlayerState->PawnPrivate;
			/* DEBUG_PRINT("location: x: %.5f, y:%.5f, z:%.5f", location.X, location.Y, location.Z); */
			bool result = pawn->K2_SetActorLocation(CommonData::config.targetPlayerLocation, false, nullptr, false);
			gameInstance->DEBUG_PRINT("transResult: %d", result ? 1 : 0);
			
		}

		gameInstance->DEBUG_PRINT("received message");
	}

	bool init()
	{

		client = std::shared_ptr<MocIPC::IPCClient>(new MocIPC::IPCClient, [](MocIPC::IPCClient* instance) {});
		client->registerRecvHOOK(testRecv);
        gameInstance = std::shared_ptr<blackMyth>(new blackMyth, [](blackMyth* instance) { instance->deinit(); });

		bool ret = gameInstance->init();
		if(ret) {
			running = true;
		}

        return ret;


	}

	void start()
	{

		while (running) {

			
			this->client->write(&CommonData::infoBuffer, sizeof(CommonData::infoBuffer));
			this->client->write(&CommonData::locationBuffer, sizeof(CommonData::locationBuffer));
			this->client->write(&CommonData::gameStatus, sizeof(CommonData::gameStatus));

			if (!gameInstance->textQueue.empty()) {
				

				std::unordered_set<std::wstring> wstrSet(gameInstance->textQueue.begin(), gameInstance->textQueue.end());

				gameInstance->textQueue.assign(wstrSet.begin(), wstrSet.end());
				std::wostringstream woss;
				for (size_t i = 0; i < gameInstance->textQueue.size(); ++i) {
					if (i != 0) {
						woss << L",";
					}
					woss << gameInstance->textQueue[i];
				}
				std::wstring concatenated = woss.str();
				gameInstance->textQueue.clear();
				gameInstance->textQueue.push_back(concatenated);

				const std::wstring &str = gameInstance->textQueue.front();

				const wchar_t* cStr = str.c_str();
				/*gameInstance->DEBUG_PRINT("text: %s", cStr);*/
				size_t charCount = str.size() * 2 + 2;
				memset(&CommonData::speakerInfo, 0, sizeof(CommonData::speakerInfo));
				CommonData::speakerInfo.event = CommonData::event_t::EVENT_SPEAKERINFO;
				memcpy(&CommonData::speakerInfo.speakerInfo.label, cStr, charCount);
				CommonData::speakerInfo.speakerInfo.length = charCount;
				
				this->client->write(&CommonData::speakerInfo, sizeof(CommonData::speakerInfo));
				gameInstance->textQueue.erase(gameInstance->textQueue.begin());
			}
			

			int index = 0;
			float minDealta = 999999999.0f;
			float Hp = 0;
			for (const auto& pair : gameInstance->aiCharacterMap) {
				if (pair.second.delta < minDealta) {
					minDealta = pair.second.delta;
					Hp = pair.second.Hp;
				}
					
			}
			CommonData::enemyInfo.event = CommonData::event_t::EVENT_ENEMY_MAP;
			CommonData::enemyInfo.enemyInfo.enemyDelta = minDealta;
			CommonData::enemyInfo.enemyInfo.playerHp = Hp;
			this->client->write(&CommonData::enemyInfo, sizeof(CommonData::enemyInfo));
			
			this->client->write(&CommonData::levelInfoBuffer, sizeof(CommonData::levelInfoBuffer));
			Sleep(100);
		}
		
		
	}


public:
	inline static std::shared_ptr<blackMyth> gameInstance;
	inline static std::shared_ptr<MocIPC::IPCClient> client;

	
};


#pragma warning(pop)