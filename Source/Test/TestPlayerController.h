// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:

    void SetupInputComponent() override;

    void MoveForward(float Value);
    void MoveRight(float Value);
	
    void Turn(float Value);
    void LookUp(float Value);

    void ToggleGrabObject();
    


};
