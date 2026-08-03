// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enums/Jam_TimeDayOfWeek.h"
#include "Enums/Jam_TimeSeason.h"
#include "Enums/Jam_TimeOfDay.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Jam_DateTimeUtil.generated.h"

UCLASS()
class JAMTIME_API UJam_DateTimeUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static int32 GetHourUnclamped(float seconds);
	static int32 GetHourClamped(float seconds);
	static int32 GetHoursFromEpoch(int32 days, float seconds);
	static EJam_TimeOfDay GetTimeOfDay(float seconds);
	static int32 GetDaysClamped(int32 days);
	static int32 GetYear(int32 days);
	static int32 GetMonth(int32 days);
	static int32 GetDate(int32 days);
	static EJam_TimeSeason GetSeason(int32 days);
	static EJam_TimeDayOfWeek GetDayOfWeek(int32 days);
	static int32 GetDays(int32 date, EJam_TimeSeason season, int32 year = 1);
	static bool IsDayTime(const float seconds);
	static float InGameToRealTime(const float seconds);
};
