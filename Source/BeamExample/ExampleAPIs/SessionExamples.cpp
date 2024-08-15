#include "SessionExamples.h"
#include "BeamExample/ExampleGameInstance.h"
#include "KeyPair.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamSessionApi, Log, All);

void USessionExamples::CreateSession(FString EntityId, FOnCreateSessionResponse Callback)
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
	
	KeyPair keyPair;
	BeamClient->GetOrCreateSigningKeyPair(keyPair, EntityId, true);

	auto Request =PlayerClientSessionsApi::CreateSessionRequestRequest();
	Request.EntityId = EntityId;
	Request.PlayerClientGenerateSessionUrlRequestInput.ChainId = 13337;
	Request.PlayerClientGenerateSessionUrlRequestInput.Address = keyPair.GetAddress().c_str();
	
	auto ResponseCallback = PlayerClientSessionsApi::FCreateSessionRequestDelegate::CreateUObject(
		this, &USessionExamples::OnCreateSessionResponse, Callback);
	
	SessionApi->CreateSessionRequest(Request, ResponseCallback);
}

void USessionExamples::OnCreateSessionResponse(
	const PlayerClientSessionsApi::CreateSessionRequestResponse& Response, FOnCreateSessionResponse Callback)
{
	UE_LOG(LogBeamSessionApi, Log, TEXT("%hs: code=%d"), __func__, Response.GetHttpResponseCode());

	Callback.ExecuteIfBound(Response.GetHttpResponse()->GetContentAsString());

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
