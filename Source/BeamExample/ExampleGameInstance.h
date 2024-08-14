#pragma once

#include "BeamClient.h"
#include "Engine/GameInstance.h"
#include "ExampleGameInstance.generated.h"

UCLASS(config=Secrets)
class BEAMEXAMPLE_API UExampleGameInstance : public UGameInstance {
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

public:
	UPROPERTY(config)
	FString BeamApiKey;
	
	UPROPERTY()
	UBeamClient* BeamClient;
};
