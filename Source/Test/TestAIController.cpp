// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"



ATestAIController::ATestAIController()
{
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");

    SightSenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightSenseConfig");
    SightSenseConfig->SightRadius = 800.f;
    SightSenseConfig->LoseSightRadius = 1000.f;
    SightSenseConfig->DetectionByAffiliation.bDetectNeutrals = 1;

    PerceptionComp->ConfigureSense(*SightSenseConfig);
    PerceptionComp->SetDominantSense(SightSenseConfig->GetSenseImplementation());
}

void ATestAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
    if(BlackboardComp)
    {
        BlackboardComp->SetValueAsObject(BBFollowKey, Actor);
    }
}

void ATestAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    UBehaviorTree* FollowTree = LoadObject<UBehaviorTree>(this, TEXT("BehaviorTree'/Game/BP/AI/BT_AIFollow.BT_AIFollow'"));
    ensure(FollowTree != nullptr);
    RunBehaviorTree(FollowTree);
    
}

void ATestAIController::BeginPlay()
{
    UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

    PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ATestAIController::OnTargetPerceptionUpdated);

    Super::BeginPlay();
}
