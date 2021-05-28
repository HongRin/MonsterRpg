#pragma once

#include "CoreMinimal.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "Structure/PlayerInfo/PlayerInfo.h"
#include "PlayerManager.generated.h"

UCLASS()
class MONSTERRPG_API UPlayerManager : public UManagerClass
{
	GENERATED_BODY()


private:
	UPROPERTY()
		class APlayableController* PlayableController;

	UPROPERTY()
		class APlayableCharacter* PlayableCharacter;

	UPROPERTY()
		FPlayerInfo PlayerInfo;


public:
	// �÷��̾� ��Ʈ�ѷ��� ĳ���͸� ����մϴ�.
	void RegisterPlayer(class APlayableController* newPlayableController,
		class APlayableCharacter* newPlayableCharacter);

public:
	virtual void InitManagerClass() override;
	virtual void ShutdownManagerClass() override;



	FORCEINLINE class APlayableController* GetPlayableController() const
	{ return PlayableController; }

	FORCEINLINE class APlayableCharacter* GetPlayableCharacter() const
	{ return PlayableCharacter; }

	FORCEINLINE FPlayerInfo* GetPlayerInfo()
	{ return &PlayerInfo; }

};
