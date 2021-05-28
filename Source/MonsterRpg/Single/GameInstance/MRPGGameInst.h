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
	// ����� �Ŵ��� Ŭ���� �ν��Ͻ��� �����մϴ�.
	TMap<FString, UManagerClass*> ManagerClasses;

private:
	// ManagerClass �� ����մϴ�.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	// ����� ManagerClass �� ����ϴ�.
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
