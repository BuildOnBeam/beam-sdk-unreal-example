#pragma once

#include "CoreMinimal.h"
#include "PlayerClientHealthApiOperations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HealthExamples.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHealthCheckResponse, FString, Response);

UCLASS()
class UHealthExamples : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Example of how to call API functions that aren't wrapped by the BeamClient
	UFUNCTION(BlueprintCallable)
	void CheckHealth(FOnHealthCheckResponse Callback);
	void OnCheckResponse(const OpenAPI::PlayerClientHealthApi::CheckResponse& Response, FOnHealthCheckResponse Callback);
};
