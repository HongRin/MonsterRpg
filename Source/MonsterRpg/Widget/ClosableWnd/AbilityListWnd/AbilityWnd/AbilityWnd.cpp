#include "AbilityWnd.h"

#include "Single/GameInstance/MRPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Single/PlayerManager/AbilitySystem/AbilitySystem.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UAbilityWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Select->OnClicked.AddDynamic(this, &UAbilityWnd::OnClickedSelectButton);
}

void UAbilityWnd::InitializeRating(EAbilityRatingType abilityType)
{
	switch (abilityType)
	{
	case EAbilityRatingType::AR_NORMAL :
		Text_Type->SetText(FText::FromString(FString(TEXT("노멀"))));
		Text_Type->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Text_Name->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Image_Background->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case EAbilityRatingType::AR_RARE:
		Text_Type->SetText(FText::FromString(FString(TEXT("레어"))));
		Text_Type->SetColorAndOpacity(FLinearColor(0.0f, 0.2f, 1.0f, 1.0f));
		Text_Name->SetColorAndOpacity(FLinearColor(0.0f, 0.2f, 1.0f, 1.0f));
		Image_Background->SetColorAndOpacity(FLinearColor(0.2f, 0.0f, 1.0f, 1.0f));
		break;
	case EAbilityRatingType::AR_UNIQUE:
		Text_Type->SetText(FText::FromString(FString(TEXT("유니크"))));
		Text_Type->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.7f, 1.0f));
		Text_Name->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.7f, 1.0f));
		Image_Background->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case EAbilityRatingType::AR_LEGENDARY:
		Text_Type->SetText(FText::FromString(FString(TEXT("레전드리"))));
		Text_Type->SetColorAndOpacity(FLinearColor(0.9f, 1.0f, 0.0f, 1.0f));
		Text_Name->SetColorAndOpacity(FLinearColor(0.9f, 1.0f, 0.0f, 1.0f));
		Image_Background->SetColorAndOpacity(FLinearColor(0.5f, 1.0f, 0.0f, 1.0f));
		break;
	}
}

void UAbilityWnd::InitializeAbilityWnd(FAbilityInfo abilityInfo)
{
	InitializeRating(abilityInfo.AbilityRating);
	Text_Name->SetText(abilityInfo.AbilityName);
	Text_Description->SetText(abilityInfo.AbilityDescription);
}

void UAbilityWnd::OnClickedSelectButton()
{
	GetManager(UPlayerManager)->GetAbilitySystem()->CloseAbilityListWnd();
}
