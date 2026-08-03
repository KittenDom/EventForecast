#pragma once

#include "Math/NumericLimits.h"


constexpr int32 IRL_SECONDS_IN_A_MINUTE = 60;

constexpr int32 SECONDS_IN_A_MINUTE = 60;
constexpr int32 MINUTES_IN_AN_HOUR = 60;
constexpr int32 SECONDS_IN_AN_HOUR = SECONDS_IN_A_MINUTE * MINUTES_IN_AN_HOUR;
constexpr int32 HOURS_IN_A_DAY = 24;

constexpr float MAX_SECONDS = static_cast<float>(SECONDS_IN_AN_HOUR) * static_cast<float>(MAX_int32);
constexpr float MIN_SECONDS = static_cast<float>(SECONDS_IN_AN_HOUR) * static_cast<float>(MIN_int32);

constexpr int32 DAYS_IN_A_WEEK = 5;
constexpr int32 WEEKS_IN_A_MONTH = 4;
constexpr int32 DAYS_IN_A_MONTH = DAYS_IN_A_WEEK * WEEKS_IN_A_MONTH;

constexpr int32 MONTHS_IN_A_SEASON = 1;
constexpr int32 DAYS_IN_A_SEASON = DAYS_IN_A_MONTH * MONTHS_IN_A_SEASON;
constexpr int32 SEASONS_IN_A_YEAR = 4;
constexpr int32 MONTHS_IN_A_YEAR = MONTHS_IN_A_SEASON * SEASONS_IN_A_YEAR;
constexpr int32 DAYS_IN_A_YEAR = DAYS_IN_A_MONTH * MONTHS_IN_A_YEAR;
