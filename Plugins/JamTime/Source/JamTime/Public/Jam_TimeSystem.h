#pragma once

#include "Subsystems/WorldSubsystem.h"

#include "Jam_TimeSystem.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FJam_TimeChangedSignature, float currentTime)
DECLARE_MULTICAST_DELEGATE_OneParam(FJam_HourChangedSignature, float currentTime)
DECLARE_MULTICAST_DELEGATE_OneParam(FJam_DateChangedSignature, int32 currentDate)
DECLARE_MULTICAST_DELEGATE(FJam_DayStartedSignature)
DECLARE_MULTICAST_DELEGATE(FJam_DayEndedSignature)


UCLASS()
class JAMTIME_API UJam_TimeSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& inWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	void RegisterState(class AJam_DateTimeState* state);
	void SetTimeFrozen(const bool bTimeFrozen);
	void SetTimeScale(const float timeScale);

	float GetCurrentTime() const;
	int32 GetCurrentDate() const;

private:
	void UpdateDateTime(float deltaTime);
	AJam_DateTimeState* GetOrDefaultState() const;

public:
	FJam_TimeChangedSignature TimeChanged;
	FJam_HourChangedSignature HourChanged;
	FJam_DateChangedSignature DateChanged;
	FJam_DayStartedSignature DayStarted;
	FJam_DayEndedSignature DayEnded;

private:
	UPROPERTY()
	AJam_DateTimeState* TimeState = nullptr;

	float TimeScale = 1.f;
	bool bTimeFrozen = false;
	bool bDayAdvanced = false;

#if !UE_BUILD_SHIPPING
private:
	void DebugTimeFrozen(IConsoleVariable* cvar);
	void DebugTimeScale(IConsoleVariable* cvar);
#endif
};
