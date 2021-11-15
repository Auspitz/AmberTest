// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestPlayerCharacter.generated.h"

class UCameraComponent;
class USceneComponent;
class UPhysicsHandleComponent;

UCLASS()
class TEST_API ATestPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATestPlayerCharacter();

    void Tick(float DeltaTime) override;

    void GrabObject();

    void ReleaseObject();

    bool IsHoldingObject() const;

protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCameraComponent* CameraComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USceneComponent* PickupLocationComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsHandleComponent* PhysicsHandleComp;

private:

    bool bIsHoldingObject;


};
