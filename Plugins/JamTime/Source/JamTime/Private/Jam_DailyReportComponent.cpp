#include "Jam_DailyReportComponent.h"

#include "Jam_TimeSystem.h"


UJam_DailyReportComponent::UJam_DailyReportComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UJam_DailyReportComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld())
	{
		return;
	}

	UJam_TimeSystem* timeSystem = GetWorld()->GetSubsystem<UJam_TimeSystem>();
	if (!timeSystem)
	{
		return;
	}

	timeSystem->DayEnded.AddUObject(this, &UJam_DailyReportComponent::OnDayEnded);
}

void UJam_DailyReportComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		if (UJam_TimeSystem* timeSystem = GetWorld()->GetSubsystem<UJam_TimeSystem>())
		{
			timeSystem->DayEnded.RemoveAll(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UJam_DailyReportComponent::OnDayEnded()
{
	// todo UI Daily Report following up
	UE_LOG(LogTemp, Warning, TEXT("%hs"), __FUNCTION__);
}
