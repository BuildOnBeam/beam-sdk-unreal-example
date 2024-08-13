#pragma once

#include "CoreMinimal.h"
#include "PlayerClientHealthApiOperations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HealthExamples.generated.h"


UCLASS()
class UHealthExamples : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CheckHealth();
	void OnCheckResponse(const OpenAPI::PlayerClientHealthApi::CheckResponse& Response);
};
