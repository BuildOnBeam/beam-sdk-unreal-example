#pragma once

#include "CoreMinimal.h"
#include "PlayerClientSessionsApiOperations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SessionExamples.generated.h"

UCLASS()
class BEAMEXAMPLE_API USessionExamples : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CreateSession(FString EntityId);
	void OnCreateSessionResponse(const OpenAPI::PlayerClientSessionsApi::CreateSessionRequestResponse& Response);
};
