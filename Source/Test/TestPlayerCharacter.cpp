// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerCharacter.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

ATestPlayerCharacter::ATestPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    CameraComp->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
    CameraComp->bUsePawnControlRotation = true;

    PickupLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    PickupLocationComp->AttachToComponent(CameraComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    PickupLocationComp->SetRelativeLocation(FVector(100.f, 0.f, 40.f));

    PhysicsHandleComp = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComp"));
}

void ATestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(bIsHoldingObject)
    {
        if(PhysicsHandleComp)
        {
            PhysicsHandleComp->SetTargetLocation(PickupLocationComp->GetComponentLocation());
        }
    }
}

void ATestPlayerCharacter::GrabObject()
{
    if(PhysicsHandleComp)
    {
        FVector StartPoint = CameraComp->GetComponentLocation();
        FRotator ViewRot = CameraComp->GetComponentRotation();

        float TraceDistance = 200.f;
        FVector EndPoint = StartPoint + ViewRot.Vector() * TraceDistance;

        FCollisionObjectQueryParams ObjectQueryParams(ECC_TO_BITFIELD(ECC_PhysicsBody));

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);

        FHitResult Hit;
        bool bTrace = GetWorld()->LineTraceSingleByObjectType(Hit,
            StartPoint,
            EndPoint,
            ObjectQueryParams,
            QueryParams
        );

        if(bTrace)
        {
            if(UPrimitiveComponent* C = Hit.GetComponent())
            {
                PhysicsHandleComp->GrabComponentAtLocationWithRotation(C, NAME_None, C->GetComponentLocation(), C->GetComponentRotation());
                bIsHoldingObject = true;
            }
        }
    }
}

void ATestPlayerCharacter::ReleaseObject()
{
    if(PhysicsHandleComp)
    {
        PhysicsHandleComp->ReleaseComponent();
        bIsHoldingObject = false;
    }
}

bool ATestPlayerCharacter::IsHoldingObject() const
{
    return bIsHoldingObject;
}

