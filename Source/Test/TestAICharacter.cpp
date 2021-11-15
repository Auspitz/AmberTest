// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAICharacter.h"

#include "TestAIController.h"

ATestAICharacter::ATestAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
    AIControllerClass = ATestAIController::StaticClass();

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> M(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
    if(M.Succeeded())
    {
        USkeletalMeshComponent* MeshComp = GetMesh();
        MeshComp->SetSkeletalMesh(M.Object);
        MeshComp->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
        MeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

        static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
        if(AnimBP.Succeeded())
        {
            MeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
            MeshComp->SetAnimInstanceClass(AnimBP.Object->GeneratedClass);
        }
        

    }
}


