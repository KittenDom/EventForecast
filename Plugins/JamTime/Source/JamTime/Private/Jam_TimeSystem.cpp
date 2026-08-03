#include "Jam_TimeSystem.h"
#include "Jam_DateTimeState.h"
#include "Jam_TimeSetting.h"
#include "Utils/Jam_DateTimeUtil.h"

#define TIME_SCALE_CLAMP_MIN 0.01
#define TIME_SCALE_CLAMP_MAX 60.0

#if !UE_BUILD_SHIPPING

#define CVAR_TIME_DEBUG_FROZEN TEXT("time.debug.frozen")
static TAutoConsoleVariable<bool> CVar_TimeFrozen(
	CVAR_TIME_DEBUG_FROZEN,
	false,
	TEXT("Toggle time (un-)freezing. Usage: time.debug.frozen 1"),
	ECVF_Cheat);

#define CVAR_TIME_DEBUG_SCALE TEXT("time.debug.scale")
static TAutoConsoleVariable<float> CVar_TimeScale(
	CVAR_TIME_DEBUG_SCALE,
	1.0,
	TEXT("Toggle time scale. Usage: time.debug.scale 0.5 (2x slower) | time.debug.scale 2 (2x faster)"),
	ECVF_Cheat);

#endif


void UJam_TimeSystem::OnWorldBeginPlay(UWorld& inWorld)
{
	Super::OnWorldBeginPlay(inWorld);

#if !UE_BUILD_SHIPPING
	CVar_TimeFrozen.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateUObject(this, &ThisClass::DebugTimeFrozen));
	CVar_TimeScale.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateUObject(this, &ThisClass::DebugTimeScale));
#endif

#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("%hs OnWorldBeginPlay TimeState IsValid status: %s from %s"), __FUNCTION__, IsValid(TimeState) ? TEXT("True") : TEXT("False"), inWorld.IsNetMode(NM_Client) ? TEXT("Client") : TEXT("Host"));
#endif

	if (inWorld.IsNetMode(NM_Client))
	{
		return;
	}

	const float timeScale = FMath::Clamp(GetDefault<UJam_TimeSetting>()->TimeScale, TIME_SCALE_CLAMP_MIN, TIME_SCALE_CLAMP_MAX);
	SetTimeScale(timeScale);

	TimeState = inWorld.SpawnActor<AJam_DateTimeState>();
	if (!TimeState)
	{
		return;
	}

	TimeState->SetCurrentDate(GetDefault<UJam_TimeSetting>()->DayBeginDate);
	TimeState->SetCurrentTime(GetDefault<UJam_TimeSetting>()->DayBeginTime);

	TimeChanged.Broadcast(GetCurrentTime());
	DateChanged.Broadcast(GetCurrentDate());
}

void UJam_TimeSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimeFrozen)
	{
		return;
	}

	if (!TimeState)
	{
		return;
	}

	UpdateDateTime(DeltaTime);
}

bool UJam_TimeSystem::IsTickable() const
{
	return !GetWorld()->IsNetMode(NM_Client);
}

TStatId UJam_TimeSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UJam_TimeSystem, STATGROUP_Tickables);
}

bool UJam_TimeSystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UJam_TimeSystem::RegisterState(AJam_DateTimeState* state)
{
	TimeState = state;
}

void UJam_TimeSystem::SetTimeFrozen(const bool bInTimeFrozen)
{
	if (!GetWorld())
	{
		return;
	}
	if (GetWorld()->IsNetMode(NM_Client))
	{
		return;
	}

	bTimeFrozen = bInTimeFrozen;
}

void UJam_TimeSystem::SetTimeScale(const float timeScale)
{
	if (!GetWorld())
	{
		return;
	}
	if (GetWorld()->IsNetMode(NM_Client))
	{
		return;
	}
	if (timeScale == TimeScale)
	{
		return;
	}
	if (timeScale < TIME_SCALE_CLAMP_MIN || timeScale > TIME_SCALE_CLAMP_MAX)
	{
		return;
	}
	TimeScale = timeScale;
}

float UJam_TimeSystem::GetCurrentTime() const
{
	return GetOrDefaultState()->GetCurrentTime();
}

int32 UJam_TimeSystem::GetCurrentDate() const
{
	return GetOrDefaultState()->GetCurrentDate();
}

void UJam_TimeSystem::UpdateDateTime(float deltaTime)
{
	float currentTime = GetOrDefaultState()->GetCurrentTime();
	int32 currentDate = GetOrDefaultState()->GetCurrentDate();
	const int32 previousHoursFromEpoch = UJam_DateTimeUtil::GetHoursFromEpoch(currentDate, currentTime);

	currentTime += deltaTime * IRL_SECONDS_IN_A_MINUTE * TimeScale;

	if (UJam_DateTimeUtil::GetHoursFromEpoch(currentDate, currentTime) > previousHoursFromEpoch)
	{
		HourChanged.Broadcast(currentTime);

		if (!bDayAdvanced && currentTime >= GetDefault<UJam_TimeSetting>()->MidnightTime)
		{
			currentDate += 1;
			TimeState->SetCurrentDate(currentDate);
			bDayAdvanced = true;
			DateChanged.Broadcast(currentDate);
		}
	}

	if (currentTime >= GetDefault<UJam_TimeSetting>()->DayEndTime)
	{
		bTimeFrozen = true;
		DayEnded.Broadcast();
	}

	TimeState->SetCurrentTime(currentTime);
	TimeChanged.Broadcast(currentTime);
}

AJam_DateTimeState* UJam_TimeSystem::GetOrDefaultState() const
{
	return TimeState != nullptr ? TimeState : AJam_DateTimeState::StaticClass()->GetDefaultObject<AJam_DateTimeState>();
}


#if !UE_BUILD_SHIPPING
void UJam_TimeSystem::DebugTimeFrozen(IConsoleVariable* cvar)
{
	const bool bTimeFrozenValue = CVar_TimeFrozen.GetValueOnGameThread();

	SetTimeFrozen(bTimeFrozenValue);
	if (bTimeFrozenValue)
	{
		return;
	}

	if (bDayAdvanced)
	{
		const FJam_Time UnfreezeTime = GetDefault<UJam_TimeSetting>()->DayBeginTime;
		TimeState->SetCurrentTime(UnfreezeTime);
		TimeChanged.Broadcast(UnfreezeTime);

		bDayAdvanced = false;
		DayStarted.Broadcast();
	}

}

void UJam_TimeSystem::DebugTimeScale(IConsoleVariable* cvar)
{
	float TimeScaleValue = CVar_TimeScale.GetValueOnGameThread();
	TimeScaleValue = FMath::Clamp(TimeScaleValue, TIME_SCALE_CLAMP_MIN, TIME_SCALE_CLAMP_MAX);
	SetTimeScale(TimeScaleValue);
}
#endif
