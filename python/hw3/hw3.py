#!/usr/bin/env python
################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: hw3.py
#
# Modifications:
#
# 21-March-13: Version 1.0: Created
#
# Timeperiod: ev6
#
################################################################################
################################################################################

import urllib
from collections import deque

################################################################################
################################################################################

def getLinks(url,baseurl="http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/"):
   """
   Input: url to visit, Boolean absolute indicates whether URLs should include absolute path (default) or not
   Output: list of pairs of URLs and associated text
   """
   #import the HTML parser package 
   try:
      from BeautifulSoup import BeautifulSoup
   except:
      print 'You must first install the BeautifulSoup package for this code to work.\n Visit http://lyle.smu.edu/~tylerm/courses/cse3353/pypackages.html for instructions.'
      raise
   #fetch the URL and load it into the HTML parser
   soup = BeautifulSoup(urllib.urlopen(url).read())
   #pull out the links from the HTML and return
   return [baseurl+a["href"].encode('ascii','ignore') for a in soup.findAll('a')]

def get_path(_Node, _List = None):

   if _List is None: _List = list()

   _List.append(_Node[0]) # append child

   if _Node[1] is not None: _List = get_path(_Node[1], _List) # append parent 

   return _List

def dfs(url, _PassedList = None, _Set = None, _Parent = None):
   """
   Recursive helper function that returns a list of urls
   in depth-first order
   """

   ######################################################################
   # initialize set and list if they are null
   ######################################################################

   if _Set is None: _Set = set() 
   if _PassedList is None: _PassedList = list()

   if _Parent is None: url = (url, None)

   else: url = (url, _Parent)

   _Set.add(url[0])

   _List = getLinks(url[0]) # get all of the links from that url

   _List = [ (_Index, url) for _Index in _List ] # store a node as tuple of its url and its parent's url

   for _Url in _List:

      ######################################################################
      # if the url is in the set then skip over it
      ######################################################################

      if _Url[0] in _Set: continue

      _PassedList = dfs(_Url[0], _PassedList, _Set, _Url[1])
   
      _PassedList.append(_Url[0]) # post order append (as the stack unwinds)

   return _PassedList

def print_dfs(url):
   """
   Print all links reachable from a starting **url** 
   in depth-first order
   """
  
   print "\n" # help make everything more readable

   print dfs(url)

   print "\n"

def bfs(url, _SearchTerm = None, _PassedList = None, _Queue = None, _Set = None, _Parent = None):
   """
   Recursive helper function that returns a list of urls
   in depth-first order
   """

   if _PassedList is None: _PassedList = list()
   if _Set is None: _Set = set()
   if _Queue is None: _Queue = deque()
   
   if _Parent is None: url = (url, None) 

   else: url = (url, _Parent) # store a url as a tuple of its url and its parent

   if url[0] not in _Set: 

      ######################################################################
      # Checking if in set because there may be repeats in the queue
      ######################################################################

      _Queue.append(url)

   _List = getLinks(url[0]) # get all of the links from that url

   _List = [ (_Index, url) for _Index in _List ]

   _Extended = False # boolean to make sure the queue is only added to once

   while _Queue:

      if not _Extended: 
         
         _Queue.extend(_List)
         _Extended = True # recursion will set the value to false on the next call

      _ToBeProcessed = _Queue.popleft() # url to be processed

      if _ToBeProcessed[0] in _Set: continue

      _Set.add(_ToBeProcessed[0])

      _PassedList.append(_ToBeProcessed[0])

      if _SearchTerm is not None:

         if _ToBeProcessed[0] == _SearchTerm: 

            # found the search term

            _PassedList = list() # empty the list and start backtracking

            _PassedList.extend(get_path(_ToBeProcessed)) # get the path back to the parent

            return _PassedList

      _PList = bfs(_ToBeProcessed[0], _SearchTerm, _PassedList, _Queue, _Set, _ToBeProcessed[1])

      if _SearchTerm: 

         _PassedList = _PList

         if _PassedList:

            # if the search term is in the list (would be at the last index if already reversed)

            if _PassedList[0] != _SearchTerm and _PassedList[-1] != _SearchTerm: 

               _PassedList = None

            elif _PassedList[-1] == _SearchTerm: return _PassedList


            # else reverse the list so it is the correct way down

            else: _PassedList = _PassdList[::-1]

         # pass the path up the stack
         return _PassedList

   return _PassedList

def print_bfs(url):
   """
   Print all links reachable from a starting **url** 
   in breadth-first order
   """
   
   print "\n" # help make everything more readable

   print bfs(url)
    
   print "\n"

def make_graph(url, _PassedGraph = None, _Queue = None, _Set = None):
   """
   Parameters: a url
   Returns: a graph of all the links using a dictionary to map a url to a list of links
   """

   if _PassedGraph is None: _PassedGraph = dict()
   if _Set is None: _Set = set()
   if _Queue is None: _Queue = deque()
   
   _List = getLinks(url) # get all of the links from that url
   
   if url not in _Set: 

      ######################################################################
      # Checking if in set because there may be repeats in the queue
      ######################################################################

      _PassedGraph[url] = _List

      _Set.add(url)

      _Queue.append(url)

   _Extended = False # boolean to make sure the queue is only added to once

   while _Queue:

      if not _Extended: 
         
         _Queue.extend(_List)
         _Extended = True # recursion will set the value to false on the next call

      _ToBeProcessed = _Queue.popleft() # url to be processed

      if _ToBeProcessed in _Set: continue

      _Set.add(_ToBeProcessed)

      _PassedGraph[_ToBeProcessed] = getLinks(_ToBeProcessed)

      make_graph(_ToBeProcessed, _PassedGraph, _Queue, _Set)

   return _PassedGraph


def find_links(url):
   """
   Construct a graph of URLs linked from **url**,
   then use a constant-time operation to return
   all links that url points to.
   """
   _Graph = make_graph(url)

   print "\n"

   print url + ": " + str(_Graph[url])

   print "\n"

def find_shortest_path(url1,url2):
   """
   Find and return the shortest path
   from **url1** to **url2** if one exists.
   If no such path exists, say so.
   """

   print "\n"

   print bfs(url1, url2)

   print "\n"

def find_max_depth(url):
   """
   Find and return the "longest shortest path" 
   from **url** to any other webpage
   """

   #########################################################################
   # Finds the max depth using the idea that path of the index of the 
   # last element in the bfs list is the longest shortest path
   #########################################################################

   print "\n"

   _BfsList = bfs(url) # get the breadth first search list

   print bfs(url, _BfsList[-1]) # determine the path between the last element in the bfs list

   print "\n"

################################################################################
# Main
################################################################################

if __name__=="__main__":
   starturl = "http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/index.html"
   print "*********** (a) Depth-first search   **********"
   print_dfs(starturl)
   print "*********** (b) Breadth-first search **********"
   print_bfs(starturl)
   print "*********** (c) Constant-time lookup of links for given URL once graph is made *****"
   find_links("http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/blink.html")
   print "*********** (d) Find shortest path between two URLs ********"
   find_shortest_path("http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/index.html","http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/matula.html")
   find_shortest_path("http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/turing.html","http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/dijkstra.html")
   find_shortest_path("http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/p5.html", "http://lyle.smu.edu/~tylerm/courses/cse3353/webtraverse/turing.html")
   print "*********** (e) Find the longest shortest path from a starting URL *****"
   find_max_depth(starturl)


################################################################################
################################################################################
