// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TestAIController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class TEST_API ATestAIController : public AAIController
{
	GENERATED_BODY()
	
public:

    ATestAIController();

    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    FName BBFollowKey = "TargetFollow";

protected:

    void OnPossess(APawn* InPawn);

    void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAIPerceptionComponent* PerceptionComp;

    UPROPERTY()
    UAISenseConfig_Sight* SightSenseConfig;

};
