#include "HealthExamples.h"
#include "PlayerClientHealthApi.h"
#include "PlayerClientHealthApiOperations.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamHealthApi, Log, All);

void UHealthExamples::CheckHealth()
{
	UE_LOG(LogBeamHealthApi, Log, TEXT("%hs"), __func__);
	auto healthApi = new OpenAPI::PlayerClientHealthApi();
	healthApi->SetURL("https://api.testnet.onbeam.com");
	auto request = OpenAPI::PlayerClientHealthApi::CheckRequest();
	auto callback = OpenAPI::PlayerClientHealthApi::FCheckDelegate::CreateUObject(this, &UHealthExamples::OnCheckResponse);
	healthApi->Check(request, callback);
}

void UHealthExamples::OnCheckResponse(const OpenAPI::PlayerClientHealthApi::CheckResponse& Response)
{
	UE_LOG(LogBeamHealthApi, Log, TEXT("%hs: code=%d"), __func__, Response.GetHttpResponseCode());
	
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogBeamHealthApi, Log, TEXT("%hs: Failed to execute health check request"), __func__);
		return;
	}
	
	if (!EHttpResponseCodes::IsOk(Response.GetHttpResponse()->GetResponseCode()))
	{
		UE_LOG(LogBeamHealthApi, Error, TEXT("%hs: Failed health check with api response: code=%d, body=%s"),
			__func__, Response.GetHttpResponse()->GetResponseCode(), *Response.GetHttpResponse()->GetContentAsString());
		return;
	}
	
	UE_LOG(LogBeamHealthApi, Log, TEXT("%hs: Success: body=%s"), __func__, *Response.GetHttpResponse()->GetContentAsString());
}
