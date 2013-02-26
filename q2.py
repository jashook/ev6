# Jarret Shook
# HW2 Question 2

import sys,random,math

def distance(x1,y1,x2=None,y2=None):
   if x1 is None and y1 is None: return
   if x2 is None and y2 is None:
      return math.fabs(y1-x1)
   else:
      return math.sqrt((x2-x1)**2+(y2-y1)**2)

def closestpair_line(_Sequence):
   """
   Input: sequence seq of numbers on a line
   Output: [(x_1,x_2), [sorted seq]] where (x_1,x_2) is the closest pair
   """
   _Length = len(_Sequence)

   if (_Length == 2 or _Length == 1):

      if (_Length == 1): return None, _Sequence

      # the first _Sequence ends up being the pair
      else: return _Sequence, _Sequence 
   
   _Sequence.sort()

   _Midpoint = len(_Sequence) / 2

   _FirstHalf, _SecondHalf = _Sequence[:_Midpoint], _Sequence[_Midpoint:]

   _LeftPair, _LeftList = closestpair_line(_FirstHalf)
   _RightPair, _RightList = closestpair_line(_SecondHalf)

   _ShortestPair = _LeftPair

   if (_LeftPair != None):

      if (distance(_LeftPair[0], _LeftPair[1]) > distance(_RightPair[0], _RightPair[1])):

         _ShortestPair = _RightPair

   return _ShortestPair, _LeftList + _RightList


def getNeighbors(seq,num,index):
   """
   Input: sorted sequence of values and number of nearest neighbors to item at position index requested 
   Ouput: list of nearest neighbors
   """
   startidx = max(0,index-num/2)
   #case where index < num/2, must check more rhs neighbors
   shift=0
   if (index - num/2) < 0: shift = int(math.fabs(index - num/2))
   endidx = index+num/2+shift+1
   #case where index exceeds list length, correct by taking more lhs neighbors
   shiftback = 0
   if (index+num/2+shift+1) > len(seq): shiftback = index+num/2+shift+1-len(seq)
   return seq[max(startidx-shiftback,0):index]+seq[index+1:endidx]

def generatePairs(numpairs=10):
   #set a seed value so everyone gets the same random jobs
   random.seed(33531337)
   pairs = []
   for i in range(numpairs):
      x = random.uniform(1,100)
      y = random.uniform(1,100)
      pairs.append((x,y))
   return pairs
    
def closestpair_plane(_Seq):
   """
   Input: sequence seq of pairs of numbers on a plane
   Output: [((x1,y1),(x2,y2)), [sorted seq]] where (x_1,x_2) is the closest pair
   Uses divide-and-conquer method for worst-case O(n lg n) time
   """

   _Seqx = [ x for x in _Seq ]

   _Seqy = [ (y[1], y[0]) for y in _Seq ]

   _Seqx.sort()
   _Seqy.sort()

   _Seqy = [ (y[1], y[0]) for y in _Seqy ]

   return cpp_helper(_Seqx, _Seqy)
   
def cpp_helper(_Seqx, _Seqy):
   """
   Recursive helper function for the divide-and-conquer closest-pair algorithm.
   Should be invoked only by closestpair_plane(seq).
   """
   #more part (c) code here
   ################### Base Case ##################
   
   _Length = len(_Seqx)

   if (_Length == 2 or _Length == 1):

      if (_Length == 1): return None, _Seqx, _Seqy

      # the first _Sequence ends up being the pair
      else: return _Seqx, _Seqx,  _Seqy

   ################### End Base Case ##############

   ################### Divide #####################

   _Middle = len(_Seqx) / 2

   _LeftSeqx, _RightSeqx = _Seqx[:_Middle], _Seqx[_Middle:]

   _LargestLeftX = _Seqx[len(_LeftSeqx) - 1]

   _LeftSeqy, _RightSeqy = list(), list()

   for _Item in _Seqy:

      if (_Item > _LargestLeftX): _LeftSeqy.append(_Item)
      else: _RightSeqy.append(_Item)
 
   _LeftPairx, _XLeftList, _YLeftList  = cpp_helper(_LeftSeqx, _LeftSeqy)
   _RightPairx, _XRightList, _YRightList = cpp_helper(_RightSeqx, _RightSeqy)

   _ShortestLeftPair = _LeftPairx
   _ShortestRightPair = _RightPairx

   _ShortestPair = _ShortestLeftPair

   ################### End Divide #################

   ################### Glue #######################

   if (_LeftPairx != None):

      _LeftMinDistance = distance(_ShortestLeftPair[0][0], _ShortestLeftPair[0][1], _ShortestLeftPair[1][0], _ShortestLeftPair[1][1])

      _RightMinDistance = distance(_ShortestRightPair[0][0], _ShortestRightPair[0][1], _ShortestRightPair[1][0], _ShortestRightPair[1][1])

      _ShortestDistance = _LeftMinDistance

      if _LeftMinDistance > _RightMinDistance: 
   
         _ShortestPair = _ShortestRightPair
         _ShortestDistance = _RightMinDistance

      _Midpoint = ( _XLeftList[0][0] + _XRightList[len(_XRightList) - 1][0] ) / 2

      _Newy = list()

      for _Temp in _YLeftList:

         if (_Temp[0] > _Midpoint - _LeftMinDistance and _Temp[0] < _Midpoint + _RightMinDistance): _Newy.append(_Temp)

      for _Temp in _YRightList:

         if (_Temp[0] > _Midpoint - _LeftMinDistance and _Temp[0] < _Midpoint + _RightMinDistance): _Newy.append(_Temp)

      for _Index in range(len(_Newy)):

         _TempList = getNeighbors(_Newy, 6, _Index)
         
         for _Point in _TempList:

            _TempDistance = distance(_Newy[_Index][0], _Newy[_Index][1], _Point[0], _Point[1])

            if (_ShortestDistance > _TempDistance):

               _ShortestDistance = _TempDistance
      
               _ShortestPair = [ _Newy[_Index], _Point ]

   else: _ShortestPair = _ShortestRightPair

   print "_ShortestPair: " + str(_ShortestPair)

   return _ShortestPair, _XLeftList + _XRightList, _YLeftList + _YRightList

   ################### End Glue #######################


def closestpairExhaustive(_Sequence):
   """
   Input: sequence seq of pairs of numbers on a plane
   Output: [((x1,y1),(x2,y2)), [sorted seq]] where (x_1,x_2) is the closest pair
   Checks all pairs exhaustively
   """    
   
   _ShortestPair = [_Sequence[0], _Sequence[1]]
   _ShortestDistance = distance(_ShortestPair[0][0], _ShortestPair[0][1], _ShortestPair[1][0], _ShortestPair[1][1])

   for i in range(len(_Sequence)):

      _NewList = _Sequence[i + 1:]

      for j in range(len(_NewList)):

         _Distance = distance(_Sequence[i][0], _Sequence[i][1], _NewList[j][0], _NewList[j][1])

         if (_ShortestDistance > _Distance):
   
            _ShortestPair = [ _Sequence[i], _NewList[j] ]
            _ShortestDistance = _Distance

   return _ShortestPair


if __name__=="__main__":

   print "Testing part a"

   print "---------------------------------------------------------------------------"

   _Pairs = [ 0, 3, 6, 8, 21, 30, 42, 55 ]

   _SecondList = [ 55, 42, 30, 21, 8, 6, 3, 0 ]

   print "_Pairs:" +  str(_Pairs)

   print "_SecondList: " + str(_SecondList)

   _Pair, _List = closestpair_line(_Pairs)

   _Pair2, _List2 = closestpair_line(_SecondList)

   print "Shortest Pair: " + str(_Pair)

   print "Shortest Pair: " + str(_Pair2)

   print _List

   print _List2

   print "---------------------------------------------------------------------------\n"

   print "Testing part b"

   print " "

   _PairList = generatePairs(100)

   _ShortestPair = closestpairExhaustive(_PairList)

   print "Shortest pair: " + str(_ShortestPair)

   print distance( _ShortestPair[0][0], _ShortestPair[0][1], _ShortestPair[1][0], _ShortestPair[1][1]) 

   print " "

   print "---------------------------------------------------------------------------\n"

   print "Testing part c"

   print " "

   _ShortestList2, _XList, _YList = closestpair_plane(_PairList)

   print "Shortest Pair: " + str(_ShortestList2)
   
   print distance(_ShortestList2[0][0], _ShortestList2[0][1], _ShortestList2[1][0], _ShortestList2[1][1])

   print " "
