#include "HealthExamples.h"
#include "PlayerClientHealthApi.h"
#include "PlayerClientHealthApiOperations.h"
#include "BeamExample/ExampleGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamHealthApi, Log, All);

void UHealthExamples::CheckHealth(FOnHealthCheckResponse Callback)
{
	UE_LOG(LogBeamHealthApi, Log, TEXT("%hs"), __func__);
	
	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogBeamHealthApi, Error, TEXT("%hs: Invalid ExampleGameInstance"), __func__);
		return;
	}

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!IsValid(BeamClient))
	{
		UE_LOG(LogBeamHealthApi, Error, TEXT("%hs: Invalid BeamClient"), __func__);
		return;
	}

	TSharedPtr<PlayerClientHealthApi> HealthApi = BeamClient->HealthApi;
	if (!HealthApi.IsValid())
	{
		UE_LOG(LogBeamHealthApi, Error, TEXT("%hs: Invalid HealthApi"), __func__);
		return;
	}
	
	PlayerClientHealthApi::CheckRequest Request = PlayerClientHealthApi::CheckRequest();
	auto OpenApiCallback = PlayerClientHealthApi::FCheckDelegate::CreateUObject(this, &UHealthExamples::OnCheckResponse, Callback);
	HealthApi->Check(Request, OpenApiCallback);
}

void UHealthExamples::OnCheckResponse(const PlayerClientHealthApi::CheckResponse& Response, FOnHealthCheckResponse Callback)
{
	UE_LOG(LogBeamHealthApi, Log, TEXT("%hs: code=%d"), __func__, Response.GetHttpResponseCode());
	
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogBeamHealthApi, Error, TEXT("%hs: Failed to execute health check request"), __func__);
		return;
	}
	
	if (!EHttpResponseCodes::IsOk(Response.GetHttpResponseCode()))
	{
		UE_LOG(LogBeamHealthApi, Error, TEXT("%hs: Failed health check with api response: code=%d, body=%s"),
			__func__, Response.GetHttpResponse()->GetResponseCode(), *Response.GetHttpResponse()->GetContentAsString());
		return;
	}
	
	Callback.ExecuteIfBound(Response.GetHttpResponse()->GetContentAsString());
}
