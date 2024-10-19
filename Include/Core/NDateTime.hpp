#ifndef N_DATE_TIME_HPP_INCLUDED
#define N_DATE_TIME_HPP_INCLUDED

#include <Core/NTimeSpan.hpp>
namespace Neurotec
{
#include <Core/NDateTime.h>
}
#if defined(N_FRAMEWORK_MFC)
	typedef CFileTime NDateTimeType;
#elif defined(N_FRAMEWORK_WX)
	typedef wxDateTime NDateTimeType;
#elif defined(N_FRAMEWORK_QT)
	#include <QDate>
	#include <QDateTime>
	typedef QDateTime NDateTimeType;
#endif

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec, NDayOfWeek)

namespace Neurotec
{

class NDateTime
{
	N_DECLARE_COMPARABLE_BASIC_CLASS(NDateTime)

private:
	static const NLong Win32FileEpoch = 504911232000000000LL;
	static const NLong UnixEpoch = 621355968000000000LL;

public:
	static bool IsLeapYear(NInt year)
	{
		NBool value;
		NCheck(NDateTimeIsLeapYear(year, &value));
		return value != 0;
	}

	static NInt DaysInMonth(NInt year, NInt month)
	{
		NInt value;
		NCheck(NDateTimeDaysInMonth(year, month, &value));
		return value;
	}

	static bool IsDateValid(NInt year, NInt month, NInt day)
	{
		return NDateTimeIsDateValid(year, month, day) != 0;
	}

	static bool IsDateTimeValid(NInt year, NInt month, NInt day, NInt hour, NInt minute, NInt second, NInt millisecond)
	{
		return NDateTimeIsDateTimeValid(year, month, day, hour, minute, second, millisecond) != 0;
	}

	static NDateTime GetUtcNow()
	{
		NDateTime_ value;
		NCheck(NDateTimeGetUtcNow(&value));
		return NDateTime(value);
	}

	static NDateTime GetNow()
	{
		NDateTime_ value;
		NCheck(NDateTimeGetNow(&value));
		return NDateTime(value);
	}

	static NDateTime GetToday()
	{
		NDateTime_ value;
		NCheck(NDateTimeGetToday(&value));
		return NDateTime(value);
	}

	static NDateTime FromTicks(NLong ticks)
	{
		NDateTime_ value;
		NCheck(NDateTimeCreateFromTicks(ticks, &value));
		return NDateTime(value);
	}

	static NInt Compare(NDateTime value1, NDateTime value2)
	{
		NInt result;
		NCheck(NDateTimeCompare(value1.value, value2.value, &result));
		return result;
	}

	static NDateTime FromOADate(NDouble oaDate)
	{
		NDateTime_ value;
		NCheck(NDateTimeFromOADate(oaDate, &value));
		return NDateTime(value);
	}

	NDateTime(NInt year, NInt month, NInt day, NInt hour, NInt minute, NInt second, NInt millisecond)
	{
		NCheck(NDateTimeCreate(year, month, day, hour, minute, second, millisecond, &value));
	}

	NDateTime(NInt year, NInt month, NInt day)
	{
		NCheck(NDateTimeCreateDate(year, month, day, &value));
	}

#if defined(N_FRAMEWORK_MFC)
	NDateTime(CFileTime value)
	{
		NLong theValue = (NLong)value.GetTime();
		if (theValue + Win32FileEpoch < 0 || N_DATE_TIME_MAX - Win32FileEpoch < theValue) NThrowOverflowException();
		this->value = Win32FileEpoch + theValue;
	}

	NDateTime(CTime value)
	{
		NLong theValue = (NLong)value.GetTime();
		if (theValue < 0 || (N_DATE_TIME_MAX - UnixEpoch) / N_TIME_SPAN_TICKS_PER_SECOND < theValue) NThrowOverflowException();
		this->value = UnixEpoch + theValue * N_TIME_SPAN_TICKS_PER_SECOND;
	}
#elif defined(N_FRAMEWORK_WX)
	NDateTime(wxDateTime value)
	{
		NLong value1 = (NLong)value.GetTicks();
		NLong value2 = (NLong)value.GetMillisecond();
		NLong result;
		if (N_DATE_TIME_MIN / N_TIME_SPAN_TICKS_PER_SECOND - UnixEpoch / N_TIME_SPAN_TICKS_PER_SECOND > value1
			|| (N_DATE_TIME_MAX - UnixEpoch) / N_TIME_SPAN_TICKS_PER_SECOND < value1) NThrowOverflowException();
		result = UnixEpoch + value1 * N_TIME_SPAN_TICKS_PER_SECOND;
		if (value2 < 0 || (N_DATE_TIME_MAX - result) / N_TIME_SPAN_TICKS_PER_MILLISECOND < value2) NThrowOverflowException();
		result += value2 * N_TIME_SPAN_TICKS_PER_MILLISECOND;
		this->value = result;
	}
#elif defined(N_FRAMEWORK_QT)
	NDateTime(QDateTime value)
	{
		NLong value1 = (NLong)value.toTime_t();
		NLong value2 = (NLong)value.time().msec();
		NLong result;
		if (N_DATE_TIME_MIN / N_TIME_SPAN_TICKS_PER_SECOND - UnixEpoch / N_TIME_SPAN_TICKS_PER_SECOND > value1
			|| (N_DATE_TIME_MAX - UnixEpoch) / N_TIME_SPAN_TICKS_PER_SECOND < value1) NThrowOverflowException();
		result = UnixEpoch + value1 * N_TIME_SPAN_TICKS_PER_SECOND;
		if (value2 < 0 || (N_DATE_TIME_MAX - result) / N_TIME_SPAN_TICKS_PER_MILLISECOND < value2) NThrowOverflowException();
		result += value2 * N_TIME_SPAN_TICKS_PER_MILLISECOND;
		this->value = result;
	}
#endif

	bool IsValid() const
	{
		return NDateTimeIsValid(value) != 0;
	}

	NTimeSpan Subtract(NDateTime nDateTime) const
	{
		NTimeSpan_ result;
		NCheck(NDateTimeSubtract(this->value, nDateTime.value, &result));
		return NTimeSpan(result);
	}

	NDateTime Add(NTimeSpan timeSpan) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddTimeSpan(this->value, timeSpan.GetValue(), &result));
		return NDateTime(result);
	}

	NDateTime Subtract(NTimeSpan timeSpan) const
	{
		NDateTime_ result;
		NCheck(NDateTimeSubtractTimeSpan(this->value, timeSpan.GetValue(), &result));
		return NDateTime(result);
	}

	NDateTime AddTicks(NLong ticks) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddTicks(this->value, ticks, &result));
		return NDateTime(result);
	}

	NDateTime AddYears(NInt years) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddYears(this->value, years, &result));
		return NDateTime(result);
	}

	NDateTime AddMonths(NInt months) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddMonths(this->value, months, &result));
		return NDateTime(result);
	}

	NDateTime AddDays(NDouble days) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddDays(this->value, days, &result));
		return NDateTime(result);
	}

	NDateTime AddHours(NDouble hours) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddHours(this->value, hours, &result));
		return NDateTime(result);
	}

	NDateTime AddMinutes(NDouble minutes) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddMinutes(this->value, minutes, &result));
		return NDateTime(result);
	}

	NDateTime AddSeconds(NDouble seconds) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddSeconds(this->value, seconds, &result));
		return NDateTime(result);
	}

	NDateTime AddMilliseconds(NDouble milliseconds) const
	{
		NDateTime_ result;
		NCheck(NDateTimeAddMilliseconds(this->value, milliseconds, &result));
		return NDateTime(result);
	}

	NInt CompareTo(NDateTime nDateTime) const
	{
		NInt result;
		NCheck(NDateTimeCompare(this->value, nDateTime.value, &result));
		return result;
	}

	NDateTime ToLocalTime() const
	{
		NDateTime_ nDateTime;
		NCheck(NDateTimeToLocalTime(this->value, &nDateTime));
		return NDateTime(nDateTime);
	}

	NDateTime ToUniversalTime() const
	{
		NDateTime_ nDateTime;
		NCheck(NDateTimeToUniversalTime(this->value, &nDateTime));
		return NDateTime(nDateTime);
	}

	void Decode(NInt * pYear, NInt * pDayOfYear, NInt * pMonth, NInt * pDay, NDayOfWeek * pDayOfWeek, NInt * pHour, NInt * pMinute, NInt * pSecond, NInt * pMillisecond) const
	{
		NCheck(NDateTimeDecode(value, pYear, pDayOfYear, pMonth, pDay, pDayOfWeek, pHour, pMinute, pSecond, pMillisecond));
	}

	NString ToString(const NStringWrapper & format = NString()) const
	{
		HNString hValue;
		NCheck(NDateTimeToStringN(value, format.GetHandle(), &hValue));
		return NString(hValue, true);
	}

	NLong GetTicks() const
	{
		NLong ticks;
		NCheck(NDateTimeGetTicks(this->value, &ticks));
		return ticks;
	}

	NInt GetYear() const
	{
		NInt year;
		NCheck(NDateTimeGetYear(this->value, &year));
		return year;
	}

	NInt GetDayOfYear() const
	{
		NInt dayOfYear;
		NCheck(NDateTimeGetDayOfYear(this->value, &dayOfYear));
		return dayOfYear;
	}

	NInt GetMonth() const
	{
		NInt month;
		NCheck(NDateTimeGetMonth(this->value, &month));
		return month;
	}

	NInt GetDay() const
	{
		NInt day;
		NCheck(NDateTimeGetDay(this->value, &day));
		return day;
	}

	NDayOfWeek GetDayOfWeek() const
	{
		NDayOfWeek dayOfWeek;
		NCheck(NDateTimeGetDayOfWeek(this->value, &dayOfWeek));
		return dayOfWeek;
	}

	NInt GetHour() const
	{
		NInt hour;
		NCheck(NDateTimeGetHour(this->value, &hour));
		return hour;
	}

	NInt GetMinute() const
	{
		NInt minute;
		NCheck(NDateTimeGetMinute(this->value, &minute));
		return minute;
	}

	NInt GetSecond() const
	{
		NInt second;
		NCheck(NDateTimeGetSecond(this->value, &second));
		return second;
	}

	NInt GetMillisecond() const
	{
		NInt millisecond;
		NCheck(NDateTimeGetMillisecond(this->value, &millisecond));
		return millisecond;
	}

	NDateTime GetDate() const
	{
		NDateTime_ date;
		NCheck(NDateTimeGetDate(this->value, &date));
		return NDateTime(date);
	}

	NTimeSpan GetTimeOfDay() const
	{
		NTimeSpan_ timeOfDay;
		NCheck(NDateTimeGetTimeOfDay(this->value, &timeOfDay));
		return NTimeSpan(timeOfDay);
	}

	NDateTime operator+(const NTimeSpan & nTimeSpan) const
	{
		return Add(nTimeSpan);
	}

	NTimeSpan operator-(const NDateTime & nDateTime) const
	{
		return Subtract(nDateTime);
	}

	NDateTime operator-(const NTimeSpan & nTimeSpan) const
	{
		return Subtract(nTimeSpan);
	}

	double ToOADate() const
	{
		double oaDate;
		NCheck(NDateTimeToOADate(this->value, &oaDate));
		return oaDate;
	}

#if defined(N_FRAMEWORK_MFC)
	operator CFileTime() const
	{
		NLong value = this->value - Win32FileEpoch;
		if (value < 0) NThrowOverflowException();
		return CFileTime((ULONGLONG)value);
	}

	operator CTime() const
	{
		NLong value = this->value;
		NLong value1 = value / N_TIME_SPAN_TICKS_PER_SECOND;
		NLong value0 = value - value1 * N_TIME_SPAN_TICKS_PER_SECOND;
		if (value0 >= (N_TIME_SPAN_TICKS_PER_SECOND / 2)) value1++;\
		value1 -= UnixEpoch / N_TIME_SPAN_TICKS_PER_SECOND;
		if (value < 0 || value1 > (NLong)(((NULong)((__time64_t)-1)) / 2)) NThrowOverflowException();
		return CTime((__time64_t)value1);
	}
#elif defined(N_FRAMEWORK_WX)
	operator wxDateTime() const
	{
		NLong value1 = value / N_TIME_SPAN_TICKS_PER_SECOND;
		NLong value2 = (value - value1 * N_TIME_SPAN_TICKS_PER_SECOND) / N_TIME_SPAN_TICKS_PER_MILLISECOND;
		NLong value0 = value - value1 * N_TIME_SPAN_TICKS_PER_SECOND - value2 * N_TIME_SPAN_TICKS_PER_MILLISECOND;
		if (value0 >= N_TIME_SPAN_TICKS_PER_MILLISECOND / 2) { if (++value2 == 1000) { value2 = 0; value1++; } }
		value1 -= UnixEpoch / N_TIME_SPAN_TICKS_PER_SECOND;
		if (value1 < -(NLong)(((NULong)((time_t)-1)) / 2) || value1 >= (NLong)(((NULong)((time_t)-1)) / 2)) NThrowOverflowException();
		wxDateTime dateTime((time_t)value1);
		dateTime.SetMillisecond((wxDateTime::wxDateTime_t)value2);
		return dateTime;
	}
#elif defined(N_FRAMEWORK_QT)
	operator QDateTime() const
	{
		NLong value = this->value;
		NLong value1 = value / N_TIME_SPAN_TICKS_PER_SECOND;
		NLong value2 = (value - value1 * N_TIME_SPAN_TICKS_PER_SECOND) / N_TIME_SPAN_TICKS_PER_MILLISECOND;
		NLong value0 = value - value1 * N_TIME_SPAN_TICKS_PER_SECOND - value2 * N_TIME_SPAN_TICKS_PER_MILLISECOND;
		if (value0 >= N_TIME_SPAN_TICKS_PER_MILLISECOND / 2) { if (++value2 == 1000) { value2 = 0; value1++; } }
		value1 -= UnixEpoch / N_TIME_SPAN_TICKS_PER_SECOND;
		if (value < -(NLong)(((NULong)((uint)-1)) / 2) || value1 >= (NLong)(((NULong)((uint)-1)) / 2)) NThrowOverflowException();
		return QDateTime::fromTime_t((uint)value1).addMSecs((qint64)value2);
	}
#endif
};

#undef N_DATE_TIME_MIN
#undef N_DATE_TIME_MAX
const NDateTime N_DATE_TIME_MIN(0LL);
const NDateTime N_DATE_TIME_MAX(3155378975999999999LL);
}

#endif // !N_DATE_TIME_HPP_INCLUDED
