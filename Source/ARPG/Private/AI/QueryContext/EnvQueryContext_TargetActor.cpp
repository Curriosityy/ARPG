// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/QueryContext/EnvQueryContext_TargetActor.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Engine.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

UEnvQueryContext_TargetActor::UEnvQueryContext_TargetActor()
{
}

void UEnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                  FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

#if UE_EDITOR
	//Check if we are in editor and not Play in Editor
	if (GEngine->IsEditor() && !GWorld->HasBegunPlay())
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData,
		                                          UGameplayStatics::GetActorOfClass(
			                                          GetWorld(), APlayerStart::StaticClass()));

		return;
	}
#endif


	UObject* QueryOwner = QueryInstance.Owner.Get();
	AActor* QueryActor = Cast<AActor>(QueryOwner);


	UBlackboardComponent* BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(QueryActor);

	if (!BlackBoard)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BlackBoard->GetValueAsObject(FName("TargetActor")));

	if (!TargetActor)
	{
		return;
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
}
