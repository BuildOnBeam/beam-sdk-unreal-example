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
		Callback.Execute("Invalid ExampleGameInstance");
		return;
	}

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!IsValid(BeamClient))
	{
		Callback.Execute("Invalid BeamClient");
		return;
	}

	TSharedPtr<PlayerClientHealthApi> HealthApi = BeamClient->HealthApi;
	if (!HealthApi.IsValid())
	{
		Callback.Execute("Invalid HealthApi");
		return;
	}
	
	PlayerClientHealthApi::CheckRequest Request = PlayerClientHealthApi::CheckRequest();
	Request.SetShouldRetry(HttpRetryParams(10, 30));
	auto OpenApiCallback = PlayerClientHealthApi::FCheckDelegate::CreateUObject(this, &UHealthExamples::OnCheckResponse, Callback);
	HealthApi->Check(Request, OpenApiCallback);
}

void UHealthExamples::OnCheckResponse(const PlayerClientHealthApi::CheckResponse& Response, FOnHealthCheckResponse Callback)
{
	UE_LOG(LogBeamHealthApi, Log, TEXT("%hs: code=%d"), __func__, Response.GetHttpResponseCode());
	
	if (!Response.IsSuccessful())
	{
		Callback.Execute("Failed to execute health check request");
		return;
	}
	
	if (!EHttpResponseCodes::IsOk(Response.GetHttpResponseCode()))
	{
		Callback.Execute(FString::Printf(TEXT("Failed HealthCheck with code=%d"), Response.GetHttpResponseCode()));
		return;
	}
	
	Callback.Execute(Response.GetHttpResponse()->GetContentAsString());
}
