#! /usr/bin/python

################################################################################
################################################################################
##
## Author: Jarret Shook
##
## Module: test.py
##
## Modifications:
##
## 3-March-13: Version 1.0: Created
##
## Timeperiod: ev6
##
################################################################################
################################################################################

import random

################################################################################
################################################################################

def insertion_sort(_List):

   for i in range(1, len(_List)):

      j = i

      _Data = _List[j]

      while j > 0 and _List[j] < _List[j - 1]:

         _List[j], _List[j - 1] = _List[j - 1], _Data

         j = j - 1

   return _List

################################################################################
################################################################################

if __name__ == "__main__":

   _List = [6, 10, 22, 1, 0, 11]

   print _List

   insertion_sort(_List)

   print _List
