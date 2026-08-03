#pragma once

#include "Components/ActorComponent.h"

#include "Jam_DailyReportComponent.generated.h"


UCLASS(ClassGroup=(JamTime))
class JAMTIME_API UJam_DailyReportComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJam_DailyReportComponent();
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnDayEnded();
};
