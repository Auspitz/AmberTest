// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestLight.generated.h"

class USceneComponent;
class UPointLightComponent;
class USphereComponent;
class UTimelineComponent;

UCLASS()
class TEST_API ATestLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestLight();

protected:

    void BeginPlay() override;

    UFUNCTION()
    void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void TimelineInterpCallback(float Value);

    UPROPERTY()
    UCurveFloat* LightBlinkCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPointLightComponent* PointLightComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent* SphereComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTimelineComponent* TimelineComp;

    float DefaultLightIntensity = 30000.f;

};
