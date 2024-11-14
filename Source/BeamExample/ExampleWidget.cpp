#include "ExampleWidget.h"
#include "ExampleGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogExampleWidget, Log, All);


void UExampleWidget::CreateSession(FString EntityId, FOnCreateSessionResponse Callback)
{
	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!ensure(IsValid(GameInstance))) return;

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!ensure(IsValid(BeamClient))) return;
	
	BeamClient->CreateSessionAsync(EntityId)
	.Next([&, Callback](const BeamSessionResult& Response)
	{
		FString responseStatus = UEnum::GetDisplayValueAsText(Response.Status).ToString();
		UE_LOG(LogExampleWidget, Log, TEXT("CreateSessionAsync: Status=%s"), *responseStatus);
		if (Response.Status == EBeamResultType::Error)
		{
			Callback.Execute("", "", responseStatus, Response.Error);
			return;
		}
		
		// Note: This is a simple example, in a real application you will likely want to do more with the
		//   results than stringify and return them.
		Callback.Execute(Response.Result.Id, Response.Result.SessionAddress, responseStatus, "");
	});
}

void UExampleWidget::RevokeSession(FString EntityId, FString SessionAddress, FOnRevokeSessionResponse Callback)
{
	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!ensure(IsValid(GameInstance))) return;

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!ensure(IsValid(BeamClient))) return;
	
	BeamClient->RevokeSessionAsync(EntityId, SessionAddress)
	.Next([&, Callback](const BeamOperationResult& Response)
	{
		FString responseStatus = UEnum::GetDisplayValueAsText(Response.Status).ToString();
		UE_LOG(LogExampleWidget, Log, TEXT("RevokeSessionAsync: Status=%s"), *responseStatus);
		if (Response.Status == EBeamResultType::Error)
		{
			Callback.Execute("", Response.Error);
			return;
		}
		
		// Note: This is a simple example, in a real application you will likely want to do more with the
		//   results than stringify and return them.
		FString status = PlayerOperationResponse::EnumToString(Response.Result);
		Callback.Execute(status, "");
	});
}

void UExampleWidget::SignOperation(FString EntityId, FString OperationId, FOnSignOperationResponse Callback)
{
	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!ensure(IsValid(GameInstance))) return;

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!ensure(IsValid(BeamClient))) return;
	
	auto SigningBy = TestBrowserSigning ? EBeamOperationSigningBy::Browser : EBeamOperationSigningBy::Auto;
	BeamClient->SignOperationAsync(EntityId, OperationId, 13337, SigningBy)
	.Next([&, Callback](const BeamOperationResult& Response)
	{
		FString responseStatus = UEnum::GetDisplayValueAsText(Response.Status).ToString();
		UE_LOG(LogExampleWidget, Log, TEXT("SignOperation: Status=%s"), *responseStatus);
		if (Response.Status == EBeamResultType::Error)
		{
			Callback.Execute("", Response.Error);
			return;
		}
		
		// Note: This is a simple example, in a real application you will likely want to do more with the
		//   results than stringify and return them.
		FString status = PlayerOperationResponse::EnumToString(Response.Result);
		Callback.Execute(status, "");
	});
}
