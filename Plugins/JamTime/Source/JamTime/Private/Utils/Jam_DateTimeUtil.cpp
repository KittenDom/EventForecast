// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Jam_DateTimeUtil.h"

#include "DateTimeHeader.h"
#include "Jam_TimeSetting.h"

int32 UJam_DateTimeUtil::GetHourUnclamped(float seconds)
{
	if (seconds > MAX_SECONDS)
	{
		return MAX_int32;
	}
	if (seconds < MIN_SECONDS)
	{
		return MIN_int32;
	}
	if (seconds < 0)
	{
		return ((seconds + 1) / SECONDS_IN_AN_HOUR) - 1;
	}
	return seconds / SECONDS_IN_AN_HOUR;
}

int32 UJam_DateTimeUtil::GetHourClamped(float seconds)
{
	int32 clampedHours = GetHourUnclamped(seconds) % HOURS_IN_A_DAY;
	if (clampedHours < 0)
	{
		clampedHours += HOURS_IN_A_DAY;
	}
	return clampedHours;
}

int32 UJam_DateTimeUtil::GetHoursFromEpoch(int32 days, float seconds)
{
	return (days * HOURS_IN_A_DAY) + GetHourUnclamped(seconds);
}

EJam_TimeOfDay UJam_DateTimeUtil::GetTimeOfDay(float seconds)
{
	const int32 hour = GetHourClamped(seconds);
	if (hour >= 6 && hour < 12)
	{
		return EJam_TimeOfDay::Morning;
	}
	if (hour >= 12 && hour < 17)
	{
		return EJam_TimeOfDay::Noon;
	}
	if (hour >= 17 && hour < 21)
	{
		return EJam_TimeOfDay::Evening;
	}
	return EJam_TimeOfDay::Night;
}

int32 UJam_DateTimeUtil::GetDaysClamped(int32 days)
{
	if (days < 0)
	{
		return ((days + 1) % DAYS_IN_A_YEAR) + DAYS_IN_A_YEAR - 1;
	}
	return days % DAYS_IN_A_YEAR;
}

int32 UJam_DateTimeUtil::GetYear(int32 days)
{
	if (days < 0)
	{
		return (days + 1) / DAYS_IN_A_YEAR;
	}
	return days / DAYS_IN_A_YEAR + 1;
}

int32 UJam_DateTimeUtil::GetMonth(int32 days)
{
	return GetDaysClamped(days) / DAYS_IN_A_MONTH + 1;
}

int32 UJam_DateTimeUtil::GetDate(int32 days)
{
	return GetDaysClamped(days) % DAYS_IN_A_MONTH + 1;
}

EJam_TimeSeason UJam_DateTimeUtil::GetSeason(int32 days)
{
	return static_cast<EJam_TimeSeason>(GetMonth(days) / MONTHS_IN_A_SEASON);
}

EJam_TimeDayOfWeek UJam_DateTimeUtil::GetDayOfWeek(int32 days)
{
	return static_cast<EJam_TimeDayOfWeek>((days % DAYS_IN_A_WEEK) + 1);
}

int32 UJam_DateTimeUtil::GetDays(int32 date, EJam_TimeSeason season, int32 year)
{
	return ((year - 1) * DAYS_IN_A_YEAR) + ((static_cast<int32>(season) - 1) * DAYS_IN_A_SEASON) + (date - 1);
}

bool UJam_DateTimeUtil::IsDayTime(const float seconds)
{
	return GetHourClamped(seconds) >= GetDefault<UJam_TimeSetting>()->SunriseTimeHour && GetHourClamped(seconds) < GetDefault<UJam_TimeSetting>()->SunsetTimeHour;
}

float UJam_DateTimeUtil::InGameToRealTime(const float seconds)
{
	return seconds * GetDefault<UJam_TimeSetting>()->TimeScale / IRL_SECONDS_IN_A_MINUTE;
}
