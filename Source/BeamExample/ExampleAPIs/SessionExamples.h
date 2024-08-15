#pragma once

#include "CoreMinimal.h"
#include "PlayerClientSessionsApiOperations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SessionExamples.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCreateSessionResponse, FString, Response);

UCLASS()
class BEAMEXAMPLE_API USessionExamples : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CreateSession(FString EntityId, FOnCreateSessionResponse Callback);
	void OnCreateSessionResponse(const OpenAPI::PlayerClientSessionsApi::CreateSessionRequestResponse& Response, FOnCreateSessionResponse Callback);
};
