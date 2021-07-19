// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "mqtt.h"
#include <thread>

mqtt* mqttSession = new mqtt("first", "alphaBot/rotation", "broker.emqx.io", 1883);

ARobot::ARobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ARobot::MoveForward(float vx)
{
	if ((Controller != NULL) && (vx != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, vx);
	}
}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{	
	Super::BeginPlay();
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{	
	mqttSession->loop();
	AddControllerYawInput(-atof(mqttSession->lastMsg));		
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARobot::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawn::AddControllerYawInput);
}

