#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Single/ManagerClass/ManagerClass.h"

#include "MRPGGameInst.generated.h"

#ifndef GAME_INST
#define GAME_INST
#define GetGameInst(worldContextObj) (Cast<UMRPGGameInst>(worldContextObj->GetGameInstance()))
#endif

UCLASS()
class MONSTERRPG_API UMRPGGameInst : public UGameInstance
{
	GENERATED_BODY()

private:
	// 등록한 매니저 클래스 인스턴스를 저장합니다.
	TMap<FString, UManagerClass*> ManagerClasses;

private:
	// ManagerClass 를 등록합니다.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	// 등록한 ManagerClass 를 얻습니다.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{
		return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]);
	}

	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{
		return &UAssetManager::GetStreamableManager();
	}

	
};
