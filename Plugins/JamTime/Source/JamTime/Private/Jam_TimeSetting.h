#pragma once

#include "DateTimeHeader.h"
#include "Engine/DeveloperSettings.h"
#include "Structs/Jam_Date.h"
#include "Structs/Jam_Time.h"

#include "Jam_TimeSetting.generated.h"

UCLASS(Config=DateTime, defaultconfig, meta=(DisplayName="Jam - Time Settings"))
class UJam_TimeSetting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override
	{
		return FName(TEXT("Plugins"));
	}

	virtual FName GetSectionName() const override
	{
		return FName(TEXT("Jam Time & Date"));
	}

public:
	UPROPERTY(Config, EditDefaultsOnly, Category="Time", meta=(UIMin="0.01", UIMax="60", ClampMin="0.01", ClampMax="60"))
	float TimeScale = 1.f;

	UPROPERTY(Config, EditDefaultsOnly, Category="Time")
	FJam_Time DayBeginTime = FJam_Time(6 * SECONDS_IN_AN_HOUR);

	UPROPERTY(Config, EditDefaultsOnly, Category="Time")
	FJam_Time DayEndTime = FJam_Time(24 * SECONDS_IN_AN_HOUR - 1);

	UPROPERTY(Config, EditDefaultsOnly, Category="Time")
	FJam_Time MidnightTime = FJam_Time(0);

	UPROPERTY(Config, EditDefaultsOnly, Category="Time", meta=(ClampMin=0, ClampMax=23))
	int32 SunriseTimeHour = 6;

	UPROPERTY(Config, EditDefaultsOnly, Category="Time", meta=(ClampMin=0, ClampMax=23))
	int32 SunsetTimeHour = 18;

	UPROPERTY(Config, EditDefaultsOnly, Category="Time", meta=(ClampMin=0, ClampMax=23))
	int32 MiddayTimeHour = 12;

	UPROPERTY(Config, EditDefaultsOnly, Category="Time", meta=(ClampMin=0, ClampMax=23))
	int32 MidnightTimeHour = 24;

	UPROPERTY(Config, EditDefaultsOnly, Category="Date")
	FJam_Date DayBeginDate = FJam_Date(1);

	UPROPERTY(Config, EditDefaultsOnly, Category="Localization")
	TSoftObjectPtr<UStringTable> DateTimeStringTable;
};
