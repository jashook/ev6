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

def dfs(url, _PassedList = None, _Set = None):
   """
   Recursive helper function that returns a list of urls
   in depth-first order
   """

   ######################################################################
   # initialize set and list if they are null
   ######################################################################

   if _Set is None: _Set = set() 
   if _PassedList is None: _List = list()

   _Set.add(url)

   _PassedList.append(url)

   _List = getLinks(url) # get all of the links from that url

   for _Url in _List:

      ######################################################################
      # if the url is in the set then skip over it
      ######################################################################

      if _Url not in _Set: continue

      dfs(_Url, _PassedList, _Set)

   return _PassedList

def print_dfs(url):
   """
   Print all links reachable from a starting **url** 
   in depth-first order
   """
  
   print dfs(url)

def bfs(url, _List = None, _Queue = None, _Set = None):
   """
   Recursive helper function that returns a list of urls
   in depth-first order
   """

   if _List is None: _List = list()
   if _Set is None: _Set = set()
   if _Queue is None: _Queue = queue()
   
   _Set.add(url)

   _List.append(url)

   _List = getLinks(url) # get all of the links from that url

   for _Url in _List:

      ######################################################################
      # if the url is in the set then skip over it
      ######################################################################

      if _Url not in _Set: continue

      bfs(_Url, _PassedList, _Set)

   return _PassedList

def print_bfs(url):
   """
   Print all links reachable from a starting **url** 
   in breadth-first order
   """
   print bfs(url)
    
def find_links(url):
   """
   Construct a graph of URLs linked from **url**,
   then use a constant-time operation to return
   all links that url points to.
   """
   #

def find_shortest_path(url1,url2):
   """
   Find and return the shortest path
   from **url1** to **url2** if one exists.
   If no such path exists, say so.
   """
   #
def find_max_depth(url):
   """
   Find and return the "longest shortest path" 
   from **url** to any other webpage
   """
   #

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
   print "*********** (e) Find the longest shortest path from a starting URL *****"
   find_max_depth(starturl)


################################################################################
################################################################################
