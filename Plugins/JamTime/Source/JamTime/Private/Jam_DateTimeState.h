// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Info.h"
#include "Structs/Jam_DateTime.h"

#include "Jam_DateTimeState.generated.h"

UCLASS()
class JAMTIME_API AJam_DateTimeState : public AInfo
{
	GENERATED_BODY()

public:
	AJam_DateTimeState();
	
public:
	virtual void PreInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	int32 GetCurrentDate() const;
	float GetCurrentTime() const;
	void SetCurrentDate(const int32 currentDate);
	void SetCurrentTime(const float currentTime);
	
private:
	UFUNCTION()
	void OnRep_CurrentDate() const;

	UFUNCTION()
	void OnRep_CurrentTime() const;

	
private:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentDate)
	int32 CurrentDate = 0;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentTime)
	float CurrentTime = 6 * SECONDS_IN_AN_HOUR;
};
