#pragma once

#include "BeamClient.h"
#include "BeamSDK/Public/Storage/BeamSaveGameStorage.h"
#include "Engine/GameInstance.h"
#include "ExampleGameInstance.generated.h"

UCLASS(config=Secrets)
class BEAMEXAMPLE_API UExampleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

public:
	UPROPERTY(config)
	FString BeamApiKey;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FString BeamStatus;
	
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	UBeamSaveGameStorage* BeamStorage = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Beam")
	UBeamClient* BeamClient = nullptr;
};
