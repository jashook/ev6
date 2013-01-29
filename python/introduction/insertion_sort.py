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

def selection_sort(s):
   """
   Input: list s to be sorted
   Output: sorted list
   """

   for i in range(len(2)):

      # don't name min since reserved word
      minidx = i;

      for j in range(i+1, len(s)):

         if s[j] < s[minidx]:
            minidx = j;

         s[i], s[minidx] = s[minidx], s[i]

   return s


