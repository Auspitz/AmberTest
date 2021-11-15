// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
#include "TestPlayerCharacter.h"

void ATestPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &ATestPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ATestPlayerController::MoveRight);

    InputComponent->BindAxis("Turn", this, &ATestPlayerController::Turn);
    InputComponent->BindAxis("LookUp", this, &ATestPlayerController::LookUp);

    InputComponent->BindAction("ToggleGrab", IE_Pressed, this, &ATestPlayerController::ToggleGrabObject);
}

void ATestPlayerController::MoveForward(float Value)
{
    APawn* MyPawn = GetPawn();
    if(MyPawn)
    {   
        MyPawn->AddMovementInput(MyPawn->GetActorForwardVector(), Value);
    }
}

void ATestPlayerController::MoveRight(float Value)
{
    APawn* MyPawn = GetPawn();
    if (MyPawn)
    {
        MyPawn->AddMovementInput(MyPawn->GetActorRightVector(), Value);
    }
}

void ATestPlayerController::Turn(float Value)
{
    APawn* MyPawn = GetPawn();
    if (MyPawn)
    {
        MyPawn->AddControllerYawInput(Value);
    }

}

void ATestPlayerController::LookUp(float Value)
{
    APawn* MyPawn = GetPawn();
    if (MyPawn)
    {
        MyPawn->AddControllerPitchInput(Value);
    }
}

void ATestPlayerController::ToggleGrabObject()
{
    APawn* MyPawn = GetPawn();
    if(ATestPlayerCharacter* Char = Cast<ATestPlayerCharacter>(MyPawn))
    {
        if(Char->IsHoldingObject())
        {
            Char->ReleaseObject();
        }
        else
        {
            Char->GrabObject();
        }
    }
}


