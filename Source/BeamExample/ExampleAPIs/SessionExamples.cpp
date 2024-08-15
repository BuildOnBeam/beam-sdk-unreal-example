#include "SessionExamples.h"
#include "BeamExample/ExampleGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamSessionApi, Log, All);

void USessionExamples::CreateSession(FString EntityId)
{
	UE_LOG(LogBeamSessionApi, Log, TEXT("%hs"), __func__);

	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: Invalid ExampleGameInstance"), __func__);
		return;
	}

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!IsValid(BeamClient))
	{
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: Invalid BeamClient"), __func__);
		return;
	}
	
	auto SessionApi = BeamClient->SessionsApi;
	if (!SessionApi.IsValid())
	{
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: Invalid SessionApi"), __func__);
		return;
	}
	
	// KeyPair KeyPair;
	// BeamClient->GetOrCreateSigningKeyPair(KeyPair, EntityId);
	
	auto Request =PlayerClientSessionsApi::CreateSessionRequestRequest();
	Request.EntityId = EntityId;
	Request.PlayerClientGenerateSessionUrlRequestInput.ChainId = 13337;
	Request.PlayerClientGenerateSessionUrlRequestInput.Address = "<PUT_YOUR_ADDRESS_HERE>";
	
	auto Callback = PlayerClientSessionsApi::FCreateSessionRequestDelegate::CreateUObject(
		this, &USessionExamples::OnCreateSessionResponse);
	
	SessionApi->CreateSessionRequest(Request, Callback);
}

void USessionExamples::OnCreateSessionResponse(
	const PlayerClientSessionsApi::CreateSessionRequestResponse& Response)
{
	UE_LOG(LogBeamSessionApi, Log, TEXT("%hs: code=%d"), __func__, Response.GetHttpResponseCode());

	if (!Response.IsSuccessful())
	{
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: code=%d"), __func__, Response.GetHttpResponseCode());
		return;
	}

	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: Invalid ExampleGameInstance"), __func__);
		return;
	}

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!IsValid(BeamClient))
	{
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: Invalid BeamClient"), __func__);
		return;
	}
	
	FString Params, LaunchUrlError;
	BeamClient->LaunchURL(*Response.Content.Url, Params, LaunchUrlError);
	if (!LaunchUrlError.IsEmpty()) {
		UE_LOG(LogBeamSessionApi, Error, TEXT("%hs: Failed to call LaunchURL: error=%s"), __func__, *LaunchUrlError);
		return;
	}

	// TODO: Start polling for the session creation result
}
