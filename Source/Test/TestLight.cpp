// Fill out your copyright notice in the Description page of Project Settings.

#include "TestLight.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"

#include "TestPlayerCharacter.h"


ATestLight::ATestLight()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneComp = CreateDefaultSubobject<USceneComponent>("Root");
    RootComponent = SceneComp;

    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereCollision");
    SphereComp->SetSphereRadius(256.f);
    SphereComp->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    

    PointLightComp = CreateDefaultSubobject<UPointLightComponent>("PointLight");
    PointLightComp->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    PointLightComp->SetIntensity(DefaultLightIntensity);
    PointLightComp->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

    TimelineComp = CreateDefaultSubobject<UTimelineComponent>("TimelineComp");

}

void ATestLight::BeginPlay()
{
    Super::BeginPlay();

    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATestLight::OnSphereBeginOverlap);
    SphereComp->OnComponentEndOverlap.AddDynamic(this, &ATestLight::OnSphereEndOverlap);

    LightBlinkCurve = LoadObject<UCurveFloat>(this, TEXT("/Game/BP/FC_LightBlink"));
    ensure(LightBlinkCurve != nullptr);
    float MinTime, MaxTime = 0.f;
    LightBlinkCurve->GetTimeRange(MinTime, MaxTime);

    TimelineComp->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
    TimelineComp->SetTimelineLength(MaxTime);
    TimelineComp->SetLooping(true);

    FOnTimelineFloat OnTimelineInterpCallback;
    OnTimelineInterpCallback.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ATestLight, TimelineInterpCallback));
    TimelineComp->AddInterpFloat(LightBlinkCurve, OnTimelineInterpCallback);
}

void ATestLight::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor->IsA<ATestPlayerCharacter>())
    {
        TimelineComp->PlayFromStart();
    }
}

void ATestLight::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor->IsA<ATestPlayerCharacter>())
    {
        TimelineComp->Stop();
        PointLightComp->SetIntensity(DefaultLightIntensity);
    }
}

void ATestLight::TimelineInterpCallback(float Value)
{
    PointLightComp->SetIntensity(Value * DefaultLightIntensity);
}

