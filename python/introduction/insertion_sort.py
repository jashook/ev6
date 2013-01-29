#!/usr/bin/python

################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: insertion_sort.py
#
# Modifications:
#
# 29-Jan-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

def insertion_sort(s):
   """
   Input: list s to be sorted
   Output: sorted list
   """

   for i in range(len(s)):

      j = i;

      while ((j>0) and (s[j] < s[j-i]))

         s[j], s[j-1] = s[j-1], s[j]
   
         ++j;
   
   return s


