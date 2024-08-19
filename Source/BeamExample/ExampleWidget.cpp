#include "ExampleWidget.h"
#include "ExampleGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogExampleWidget, Log, All);


void UExampleWidget::CreateSession(FString EntityId, FOnCreateSessionResponse Callback)
{
	UExampleGameInstance* GameInstance = Cast<UExampleGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		Callback.Execute("", "", "Invalid ExampleGameInstance");
		return;
	}

	UBeamClient* BeamClient = GameInstance->BeamClient;
	if (!IsValid(BeamClient))
	{
		Callback.Execute("", "", "Invalid BeamClient");
		return;
	}
	
	BeamClient->CreateSessionAsync(EntityId)
	.Next([&](const TBeamResult<FBeamSession>& Response)
	{
		UE_LOG(LogExampleWidget, Log, TEXT("%hs: Status=%d"), __func__, static_cast<int>(Response.Status));
		if (!Response.Error.IsEmpty())
		{
			Callback.Execute("", "", Response.Error);
			return;	
		}
		
		// Note: This is a simple example, in a real application you will likely want to do more with the
		//   results than stringify and return them.
		Callback.Execute(Response.Result.Id, Response.Result.SessionAddress, "");
	});
}

void UExampleWidget::SignOperation(FString EntityId, FString OperationId, FOnSignOperationResponse Callback)
{
	UE_LOG(LogExampleWidget, Log, TEXT("TODO: %hs: EntityId=%s, OperationId=%s"), __func__, *EntityId, *OperationId);
	Callback.Execute("", "Not Implemented");
}
