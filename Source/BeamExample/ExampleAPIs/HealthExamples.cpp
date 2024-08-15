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
		Callback.ExecuteIfBound("Invalid ExampleGameInstance");
		return;
	}

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!IsValid(BeamClient))
	{
		Callback.ExecuteIfBound("Invalid BeamClient");
		return;
	}

	TSharedPtr<PlayerClientHealthApi> HealthApi = BeamClient->HealthApi;
	if (!HealthApi.IsValid())
	{
		Callback.ExecuteIfBound("Invalid HealthApi");
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
		Callback.ExecuteIfBound("Failed to execute health check request");
		return;
	}
	
	if (!EHttpResponseCodes::IsOk(Response.GetHttpResponseCode()))
	{
		Callback.ExecuteIfBound(FString::Printf(TEXT("Failed HealthCheck with code=%d"), Response.GetHttpResponseCode()));
		return;
	}
	
	Callback.ExecuteIfBound(Response.GetHttpResponse()->GetContentAsString());
}
