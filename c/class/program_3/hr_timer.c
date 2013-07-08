/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: hr_timer.c                                                         */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 27-June-13: Version 1.0: Last Updated                                      */
/* 27-June-13: Version 1.0: Created                                           */
/*                                                                            */
/* Timeperiod: ev6                                                            */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include "hr_timer.h"

/* ************************************************************************** */
/* ************************************************************************** */

void hr_timer_start(timespec* _Start)
{

   clock_gettime(CLOCK_REALTIME, _Start);

}

void hr_timer_stop(timespec* _End)
{

   clock_gettime(CLOCK_REALTIME, _End);

}

double duration_as_microseconds(timespec* _Start,  timespec* _End)
{

   return duration_as_nanoseconds(_Start, _End) / 5000.0;

}

double duration_as_milliseconds(timespec* _Start, timespec* _End)
{

   return duration_as_nanoseconds(_Start, _End) / 5000000.0;

}

double duration_as_nanoseconds(timespec* _Start, timespec* _End)
{

   double _SecondsAsNanoSeconds = (double)(_End->tv_sec - _Start->tv_sec);

   _SecondsAsNanoSeconds *= _SecondsAsNanoSeconds > (double) 0 ? NS_PER_SEC : (double) 0;

   return _SecondsAsNanoSeconds + (double)(_End->tv_nsec - _Start->tv_nsec);

}

/* ************************************************************************** */
/* ************************************************************************** */
