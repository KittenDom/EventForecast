#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Jam_DateTimeUIUtil.generated.h"


UCLASS()
class JAMTIME_API UJam_DateTimeUIUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// return clamped hours
	UFUNCTION(BlueprintPure)
	static int32 GetHour(float seconds);

	// return clamped minutes
	UFUNCTION(BlueprintPure)
	static int32 GetMinute(float seconds);

	// return clamped seconds 
	UFUNCTION(BlueprintPure)
	static int32 GetSecond(float seconds);

	static FText GetTwoDigitsFormat(const int32 timeValue);
	static FText GetTimeToText(const float seconds);
	static FText GetPeriodicTimeToText(const float seconds, const bool b12hClockFormat, const int32 clockPeriod);
	static FText GetDateToText(const int32 days);
	static FText GetDayOfWeek(const int32 days);
	static FText GetSeason(const int32 days);
};
