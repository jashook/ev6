/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: algorith.h                                                        */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 21-Feb-13: Version 1.0: Created                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: ev6                                                           */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "algorithm.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

void* min(void* _First, void* _Second, bool (*_Compare)(void*, void*))
{
   /* if the max is _First, then return _Second */

   if (max(_First, _Second, _Compare) == _First) return _Second;

   /* else if the max is _Second, return _First */
   
   else return _First;
}

void* max(void* _First, void* _Second, bool (*_Compare)(void*, void*))
{
   /* if _First is less than _Second, return _Second */

   if (_Compare(_First, _Second)) return _Second;

   /* else return _First */
   
   else return _First;
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
