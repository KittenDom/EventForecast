// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "Jam_TimeDisplayActor.generated.h"

UCLASS()
class AJam_TimeDisplayActor : public AActor
{
	GENERATED_BODY()

public:
	AJam_TimeDisplayActor();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnTimeChanged(float currentTime) const;
	void OnDateChanged(int32 currentDate) const;

private:
	UPROPERTY()
	class UTextRenderComponent* TimeText = nullptr;

	UPROPERTY()
	UTextRenderComponent* DateText = nullptr;
};
