// Fill out your copyright notice in the Description page of Project Settings.


#include "Jam_DateTimeState.h"

#include "Jam_TimeSystem.h"
#include "Net/UnrealNetwork.h"


AJam_DateTimeState::AJam_DateTimeState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AJam_DateTimeState::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (const UWorld* world = GetWorld())
	{
		if (world->IsNetMode(NM_Client))
		{
			return;
		}

		if (UJam_TimeSystem* dateTimeSystem = world->GetSubsystem<UJam_TimeSystem>())
		{
			dateTimeSystem->RegisterState(this);
		}
	}
}

void AJam_DateTimeState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentDate);
	DOREPLIFETIME(ThisClass, CurrentTime);
}

int32 AJam_DateTimeState::GetCurrentDate() const
{
	return CurrentDate;
}

float AJam_DateTimeState::GetCurrentTime() const
{
	return CurrentTime;
}

void AJam_DateTimeState::SetCurrentDate(const int32 currentDate)
{
	if (HasAuthority())
	{
		CurrentDate = currentDate;
	}
}

void AJam_DateTimeState::SetCurrentTime(const float currentTime)
{
	if (HasAuthority())
	{
		CurrentTime = currentTime;
	}
}

void AJam_DateTimeState::OnRep_CurrentDate() const
{
	if (!GetWorld())
	{
		return;
	}

	const UJam_TimeSystem* dateTimeSystem = GetWorld()->GetSubsystem<UJam_TimeSystem>();
	if (!dateTimeSystem)
	{
		return;
	}
	dateTimeSystem->DateChanged.Broadcast(CurrentDate);
}

void AJam_DateTimeState::OnRep_CurrentTime() const
{
	if (!GetWorld())
	{
		return;
	}

	const UJam_TimeSystem* dateTimeSystem = GetWorld()->GetSubsystem<UJam_TimeSystem>();
	if (!dateTimeSystem)
	{
		return;
	}
	dateTimeSystem->TimeChanged.Broadcast(CurrentTime);
}
