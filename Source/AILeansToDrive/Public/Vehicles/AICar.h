// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AICar.generated.h"

#define TRACE_LENGTH 100000.f

UCLASS()
class AILEANSTODRIVE_API AAICar : public AWheeledVehiclePawn
{
	GENERATED_BODY()


public:
	AAICar();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI Car")
		void MoveForward(float Value);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI Car")
		void MoveRight(float Value);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI Car")
		void HandBrake(bool _IsPressed);

	TArray<float> NeuralNetwork(TArray<float> _inputs);

	float Trace(FVector _TraceDirection);

	void AddDistance();

private:
	UPROPERTY(VisibleAnywhere)
		class UBrain* Brain;

	int inputs = 5;
	int hiddenLayers = 5;
	int outputs = 2;

	FVector AILocation;
	float DistanceTravelled = 0;

	float startTime = 0;

	FTimerHandle DistanceTimerHandle;

public:
	UFUNCTION(BlueprintCallable, Category = "AI Car")
		FORCEINLINE class UBrain* GetBrain() const { return Brain; }
	UFUNCTION(BlueprintCallable, Category = "AI Car")
		FORCEINLINE float GetDistanceTravelled() const { return DistanceTravelled; }
	UFUNCTION(BlueprintCallable, Category = "AI Car")
		FORCEINLINE float GetStartTime() const { return startTime; }
};
