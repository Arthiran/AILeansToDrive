// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/AICar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Brain.h"
#include "DrawDebugHelpers.h"
#include "AILeansToDrive/AILeansToDrive.h"
#include "Kismet/GameplayStatics.h"


AAICar::AAICar()
{
	Brain = CreateDefaultSubobject<UBrain>(TEXT("BrainComponent"));
}

void AAICar::BeginPlay()
{
	Super::BeginPlay();

	AILocation = GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(DistanceTimerHandle, this, &AAICar::AddDistance, 1, true);

	startTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetBrain() && GetBrain()->Weights.Num() > 0)
	{
		TArray<float> Inputs = TArray<float>();
		Inputs.Add(Trace(GetActorRightVector()));
		Inputs.Add(Trace(-GetActorRightVector()));
		Inputs.Add(Trace(GetActorForwardVector()));
		Inputs.Add(Trace(GetActorForwardVector() + GetActorRightVector()));
		Inputs.Add(Trace(GetActorForwardVector() - GetActorRightVector()));

		TArray<float> Outputs = NeuralNetwork(Inputs);

		MoveForward(Outputs[0]);
		MoveRight(Outputs[1]);
	}
}

float AAICar::Trace(FVector _TraceDirection)
{
	FHitResult TraceHitResult;
	FVector Start = GetActorLocation() + FVector::UpVector * 50;

	FVector End = Start + _TraceDirection * TRACE_LENGTH;

	GetWorld()->LineTraceSingleByChannel(
		TraceHitResult,
		Start,
		End,
		ECC_Wall
	);

	//if (TraceHitResult.bBlockingHit)
	//{
	//	DrawDebugLine(
	//		GetWorld(),
	//		Start,
	//		TraceHitResult.ImpactPoint,
	//		FColor::Red,
	//		false
	//	);
	//}
	//else
	//{
	//	DrawDebugLine(
	//		GetWorld(),
	//		Start,
	//		End,
	//		FColor::Red,
	//		false
	//	);
	//}

	return TraceHitResult.Distance;
}

void AAICar::AddDistance()
{
	DistanceTravelled = ((AILocation - GetActorLocation()).Length()) + DistanceTravelled;
	AILocation = GetActorLocation();
}

// Main function which determines whether ball should change direction
TArray<float> AAICar::NeuralNetwork(TArray<float> _inputs)
{
	int counter = 0;
	float sum1 = 0;
	
	TArray<float> HiddenLayerValues = TArray<float>();
	TArray<float> OutputLayerValues = TArray<float>();
	
	// Calculates values between input layer and hidden layer to pass off to the output layer
	for (int i = 0; i < hiddenLayers; i++)
	{
		for (int j = 0; j < inputs; j++)
		{
			sum1 += _inputs[j] * Brain->Weights[counter];
			counter++;
		}
	
		HiddenLayerValues.Add(tanh(sum1));
		sum1 = 0;
	}

	// Calculates values from hidden layer to output layer to determine value between 0 to 1
	for (int i = 0; i < outputs; i++)
	{
		for (int j = 0; j < hiddenLayers; j++)
		{
			sum1 += HiddenLayerValues[j] * Brain->Weights[counter];
			counter++;
		}
	
		OutputLayerValues.Add(tanh(sum1));
		sum1 = 0;
	}
	
	return OutputLayerValues;
}