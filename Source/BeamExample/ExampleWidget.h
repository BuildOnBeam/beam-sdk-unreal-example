#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExampleWidget.generated.h"

UCLASS()
class BEAMEXAMPLE_API UExampleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnCreateSessionResponse, FString, Id, FString, Address, FString, ErrorMsg);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSignOperationResponse, FString, Status, FString, ErrorMsg);
	
	UFUNCTION(BlueprintCallable)
	void CreateSession(FString EntityId, FOnCreateSessionResponse Callback);

	UFUNCTION(BlueprintCallable)
	void SignOperation(FString EntityId, FString OperationId, FOnSignOperationResponse Callback);
};
