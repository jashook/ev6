#!/usr/bin/env python
# Elena Villamil, Jarret Shook
# Starter code to HW4 Q1: find shortest path in a DAG

# From Chapter 4:
def topsort(G):
   count = dict((u, 0) for u in G)             # The in-degree for each node
   for u in G:
      for v in G[u]:
         count[v] += 1  # Count every in-edge
   Q = [u for u in G if count[u] == 0]         # Valid initial nodes
   S = []               # The result
   while Q:             # While we have start nodes...
      u = Q.pop()       # Pick one
      S.append(u)       # Use it as first of the rest
      for v in G[u]:
         count[v] -= 1  # "Uncount" its out-edges
         if count[v] == 0: # New valid start nodes?
            Q.append(v) # Deal with them next
   return S

def dag_spp(_Graph, _Start, _End):       # Shortest path from s to t
   # Modify the following code to build the parent dictionary
   # and the shortest path
   _Distances = {_N:float('inf') for _N in _Graph}   # Distance estimates
   _Distances[_Start] = 0           # Start node: Zero distance
   _Parents = {}                    # parent dictionary
   _Parents[_Start] = None          # starting node has no parent
   _Path = []                       # shortest path list

   for _Node in topsort(_Graph):    # In top-sorted order...

      if _Node == _End: break       # Have we arrived?

      for _Child in _Graph[_Node]:  # For each out-edge ...

         if not _Child in _Parents: _Parents[_Child] = _Node

         _Saved = _Distances[_Child];

         _Distances[_Child] = min(_Distances[_Child], _Distances[_Node] + _Graph[_Node][_Child])                  # Relax the edge

         if _Saved != _Distances[_Child]: _Parents[_Child] = _Node

   _Parent = _Parents[_End]
   
   _Path.append(_Parent)

   while _Parent is not None:

      _Path.append(_Parents[_Parent])

      _Parent = _Parents[_Parent]
 
   _Path = _Path[::-1]
 
   _Path.append(_End)
         
   return _Distances[_End], _Path, _Parents  # return the distance, shortest path, and parent dict.

G1 ={'a': {'b':3, 'c':4},
   'b': {'c':7},
   'c': {'d':9, 'f':8},
   'd': {'e':2, 'f': -6},
   'e': {'f':3},
   'f': {}
}

G2 = {
   'a': {'b':0},
   'b': {'c':4, 'd':6},
   'c': {'g':2, 'h':-6},
   'd': {'f':3, 'e':5},
   'e': {'g':0, 'h':-6},
   'f': {'i':-1},
   'g': {'h':4},
   'h': {'i':7},
   'i': {}
}

if __name__=='__main__':
   print "shortest path from a to f in G1"
   print dag_spp(G1, 'a', 'f')
   print "shortest path from a to i in G2"
   print dag_spp(G2, 'a', 'i')
   print "shortest path from b to f in G1"
   print dag_spp(G1, 'b', 'f')
   print "shortest path from a to e in G1"
   print dag_spp(G1, 'a', 'e')
