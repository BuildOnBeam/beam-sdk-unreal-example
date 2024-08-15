#include "ExampleGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamExampleGameInstance, Log, All);

void UExampleGameInstance::Init()
{
	Super::Init();
	
	if (BeamApiKey.IsEmpty())
	{
		// Note: You can invent your own system for injecting the BeamApiKey, usage of a Secret.ini is just to keep
		//    the BeamApiKey out of the source code and source control.
		UE_LOG(LogBeamExampleGameInstance, Error,
			TEXT("%hs: BeamApiKey not set, create a DefaultSecrets.ini in the Config folder with the "
			"[/Script/BeamExample.ExampleGameInstance] section and entry of BeamApiKey=YOUR_API_KEY"),
			__func__);
		BeamStatus = "Error - Missing Beam API Key";
	}
	else
	{
		BeamStatus = "Ready";
	}

	BeamStorage = UBeamSaveGameStorage::LoadOrCreate();
	BeamClient = NewObject<UBeamClient>(this)
		->SetBeamApiKey(BeamApiKey)
		->SetEnvironment(EBeamEnvironment::Testnet)
		->SetDebugLogging(true)
		->SetStorage(BeamStorage);
	BeamStorage->Save();
}
