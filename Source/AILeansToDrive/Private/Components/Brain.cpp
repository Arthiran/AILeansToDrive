// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Brain.h"

UBrain::UBrain()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBrain::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBrain::Init(TArray<float> _Weights, bool _Copy, float _MutationRate)
{
    if (_Weights.Num() > 0)
    {
        for (int i = 0; i < Size; i++)
        {
            if (_Copy)
            {
                Weights.Add(_Weights[i]);
            }
            else
            {
                if (FMath::RandRange(0.0f, 1.0f) < _MutationRate)
                {
                    float letssee = FMath::RandRange(0.0f, 1.0f);
                    if (letssee < 0.4f)
                    {
                        Weights.Add(_Weights[i] * -letssee);
                    }
                    else
                    {
                        Weights.Add(FMath::RandRange(-1.0f, 1.0f));
                    }
                }
                else
                {
                    Weights.Add(_Weights[i]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < Size; i++)
        {
            Weights.Add(FMath::RandRange(-2.5f, 2.5f));
        }
    }
}

