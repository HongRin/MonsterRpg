#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/InputModeType.h"
#include "UIControllerWidget.generated.h"

UCLASS()
class MONSTERRPG_API UUIControllerWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class APlayableController* PlayableController;

	// �ش� ��ü�� �Ҵ�� â �������� ��Ÿ���ϴ�.
	TArray<class UClosableWnd*> AllocatedWnds;

	// �ش� ��ü�� �Ҵ�� â�� �ƴ� ���� ��ü���� ��Ÿ���ϴ�.
	TArray<class UUserWidget* > AllocatedWidgets;

	// ���� â���� ���� ��ġ�� �����մϴ�.
	TMap<FString, FVector2D> PrevClosedWndPositions;

private:
	// â ��ü���� �ƴ� �������� �߰��� ĵ����
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* CanvasPanel_WidgetParent;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* CanvasPanel_WndParent;

public:
	UUIControllerWidget(const FObjectInitializer& ObjectInitializer);

	void InitializeWidgetControllerWidget(class APlayableController* playableController);

private:
	// �Է� ��带 �ʱ�ȭ�մϴ�.
	/// - ���� �����̳�, â�� �����Ѵٸ� �Է� ��尡 �ʱ�ȭ���� �ʽ��ϴ�.
	/// - bForceChange : ���� �����̳� â�� ���� ���θ� �����ϰ� ������ �ʱ�ȭ ��ų �������� ���� ���θ� ��Ÿ���ϴ�.
	void ResetInputMode(bool bForceChange = false);

	// â�� ��ġ�� �����մϴ�
	/// - closableWnd : ��ġ�� �����ų â ��ü�� �����մϴ�.
	void SaveWndPosition(const class UClosableWnd* closableWnd);

public:
	// â�� �����մϴ�.
	/// - wndClass : ������ â UClass �� �����մϴ�.
	/// - bUsePrevPosition : â�� ���� ��ġ ��� ���θ� �����մϴ�.
	/// - changeInputMode : â�� ��� �� ������ �Է� ��带 �����մϴ�.
	/// - bShowMouseCursor : â�� ��� �� Ŀ���� ǥ���� �������� �����մϴ�.
	/// - alignmentX : ���� �������� �Ǵ� X ��ġ�� �����մϴ�.
	/// - alignmentY : ���� �������� �Ǵ� Y ��ġ�� �����մϴ�.
	/// - anchorMinX : ��ġ �� �������� �Ǵ� X ��ġ�� �����մϴ�.
	/// - anchorMinY : ��ġ �� �������� �Ǵ� Y ��ġ�� �����մϴ�.
	/// - anchorMaxX : ��ġ �� �������� �Ǵ� X ��ġ�� �����մϴ�.
	/// - anchorMaxY : ��ġ �� �������� �Ǵ� Y ��ġ�� �����մϴ�.
	class UClosableWnd* CreateWnd(TSubclassOf<class UClosableWnd> wndClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float alignmentX = 0.5f, float alignmentY = 0.5f,
		float anchorMinX = 0.5f, float anchorMinY = 0.5f,
		float anchorMaxX = 0.5f, float anchorMaxY = 0.5f);

	// â�� �ݽ��ϴ�.
	/// - bAllClose : ��� â�� �ݵ��� �� �������� ���� �����Դϴ�.
	/// - closableWndInstanceToClose : � â�� ���� ������ �����մϴ�.
	///   ���� nullptr �� ���޵ȴٸ� �������� ������ â�� �����ϴ�.
	void CloseWnd(bool bAllClose = false, class UClosableWnd* closableWndInstanceToClose = nullptr);

	// â�� �ƴ� ������ �߰��մϴ�.
	/// - �߰��� ������ CanvasPanel_WidgetParent ĵ���� ������ �߰��Ǹ�,
	///   â �����麸�� ����, ��ȣ�ۿ� �켱������ �����ϴ�.
	/// - childWidgetInstance : ���� �������� �߰��� ���� ��ü�� �����մϴ�.
	/// - changeInputMode : â�� ��� �� ������ �Է� ��带 ��Ÿ���ϴ�.
	/// - bShowMouseCursor : â�� ��� �� Ŀ���� ǥ���� �������� ��Ÿ���ϴ�.
	/// - width : ��� ������ �ʺ� ��Ÿ���ϴ�.
	/// - height : ��� ������ ���̸� ��Ÿ���ϴ�.
	void AddChildWidget(class UUserWidget* childWidgetInstance,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// �߰���Ų ���� ������ �ݽ��ϴ�.
	void CloseChildWidget(class UUserWidget* childWidgetInstance);

	// â�� �ֻ������ �����մϴ�.
	/// - closableWndInstance : �ֻ������ ��ġ�� â ��ü�� �����մϴ�.
	void SetHighestPriorityWnd(class UClosableWnd* closableWndInstance);

public:
	// �׸��� �г��� ��ҵ��� ���ʴ�� �����մϴ�.
	/// - gridPanelElem : ���Ľ�ų �׸��� �г� ��Ҹ� �����մϴ�.
	/// - maxColumnCount : �ִ� �� ������ �����մϴ�.
	/// - refCurrentColumCount : ���� �� ��ȣ�� �����մϴ�.
	///   ������ ������ ���� �޼��� ���ο��� ����˴ϴ�.
	static void SortGridPanelElem(class UUserWidget* gridPanelElem,
		int maxColumnCount, int& refCurrentColumCount);
};
