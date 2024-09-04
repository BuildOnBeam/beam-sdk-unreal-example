#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExampleWidget.generated.h"

UCLASS()
class BEAMEXAMPLE_API UExampleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_FourParams(FOnCreateSessionResponse, FString, Id, FString, Address, FString, Status, FString, ErrorMsg);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRevokeSessionResponse, FString, Status, FString, ErrorMsg);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSignOperationResponse, FString, Status, FString, ErrorMsg);
	
	UFUNCTION(BlueprintCallable)
	void CreateSession(FString EntityId, FOnCreateSessionResponse Callback);

	UFUNCTION(BlueprintCallable)
	void RevokeSession(FString EntityId, FString SessionAddress, FOnRevokeSessionResponse Callback);

	UFUNCTION(BlueprintCallable)
	void SignOperation(FString EntityId, FString OperationId, FOnSignOperationResponse Callback);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	bool TestBrowserSigning = false;
};
