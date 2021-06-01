#include "AbilityListWnd.h"

#include "Components/HorizontalBox.h"

#include "Single/GameInstance/MRPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Single/PlayerManager/AbilitySystem/AbilitySystem.h"

#include "Structure/AbilityInfo/AbilityInfo.h"
#include "Widget/ClosableWnd/AbilityListWnd/AbilityWnd/AbilityWnd.h"

UAbilityListWnd::UAbilityListWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABILITY_INFO(
		TEXT("DataTable'/Game/Resource/DataTable/DT_AbilityInfo.DT_AbilityInfo'"));
	if (DT_ABILITY_INFO.Succeeded()) DT_AbilityInfo = DT_ABILITY_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UAbilityListWnd.cpp::%d::LINE::DT_ABILITY_INFO is not loaded"));

	static ConstructorHelpers::FClassFinder<UAbilityWnd> BP_ABILITY_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/AbilityWnd/BP_AbilityWnd.BP_AbilityWnd_C'"));
	if (BP_ABILITY_WND.Succeeded()) BP_AbilityWnd = BP_ABILITY_WND.Class;
}

void UAbilityListWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(1500.0f, 400.0f);

	AbilitySystem = GetManager(UPlayerManager)->GetAbilitySystem();

	InitializeAbilityList();
}

void UAbilityListWnd::InitializeAbilityList()
{
		FString contextSting;
		TArray<FAbilityInfo*> allAbilityInfos;
		TArray<FAbilityInfo> abilityInfos;
		DT_AbilityInfo->GetAllRows(contextSting, allAbilityInfos);

		for (auto i : allAbilityInfos)
			abilityInfos.Add(*i);

		for (int i = 0; i < 3; ++i)
		{
			float randRating = FMath::FRandRange(0.0f, 100.0f);

			EAbilityRatingType ratingType;

			TArray<FAbilityInfo> ratingAbilityInfos;


			if (randRating <= 50.0f)
				ratingType = EAbilityRatingType::AR_NORMAL;
			else if (randRating <= 80.0f)
				ratingType = EAbilityRatingType::AR_RARE;
			else if (randRating <= 95.0f)
				ratingType = EAbilityRatingType::AR_LEGENDARY;
			else ratingType = EAbilityRatingType::AR_UNIQUE;

			for (int j = 0; j < abilityInfos.Num(); ++j)
			{
				if (abilityInfos[j].AbilityRating == ratingType && !abilityInfos[j].IsVeiw)
					ratingAbilityInfos.Add(abilityInfos[j]);
				if ((abilityInfos.Num() - 1) == j)
				{
					int32 randAbility = (ratingAbilityInfos.Num() == 1) ? 0 :
						FMath::RandRange(0, (ratingAbilityInfos.Num() - 1));
					auto abilityWnd = CreateWidget<UAbilityWnd>(this, BP_AbilityWnd);
					abilityWnd->InitializeAbilityWnd(ratingAbilityInfos[randAbility]);
					HorizontalBox_AbilityList->AddChild(abilityWnd);
					for (int k = 0; k < abilityInfos.Num(); ++k)
					{
						if (abilityInfos[k].AbilityCode == ratingAbilityInfos[randAbility].AbilityCode)
							abilityInfos[k].IsVeiw = true;
					}
				}
			}
		}

}
