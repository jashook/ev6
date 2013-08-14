#!/usr/bin/env python

# Elena Villamil, Jarret Shook
# Starter code for HW4 Q2

from functools import wraps

def read_playlist(filename):
    """
    Input: filename of CSV file listing (song,artist,genre) triples
    Output: List of (song,artist,genre)
    """
    playlist = []
    for line in open(filename):
        bits = [b.strip() for b in line.split(',')]
        playlist.append(bits)
    return playlist

def compare_artist (first, second):
     if first is None or second is None: return False
     if first[1] == second[1]:
          return True
     else:
          return False

def compare_genre (first, second):
     if first is None or second is None: return False
     if first[2] == second[2]:
          return True
     else:
          return False

def compare_song (first, second):
     if first is None or second is None: return False
     if compare_genre (first, second) and compare_artist(first, second) and first[0] == second[0]:
          return True
     else:
          return False

def back_track(table, i, j):
 
     myMin = table[j][i]

     outputList = []

     while i > 0 or j > 0:

          if myMin is None: break

          if myMin[0] == "ins":
               
               str1 = "Insert " + str(myMin[2])

               outputList.append(str1)
               
               #print "Insert " + str(myMin[2])

               j = j - 1
               myMin = table[j][i]

          elif myMin[0] == "del":

               str2 = "Delete " + str(myMin[2])
               #print "Delete " + str(myMin[2])

               outputList.append(str2)

               i = i - 1
               myMin = table[j][i]

          elif myMin[0] == "match":

               str3 = "Leave " + str(myMin[2]) + " unchanged"
               #print "Leave " + str(myMin[2]) + " unchanged"
      
               outputList.append(str3)
               
               i = i - 1
               j = j - 1

               myMin = table[j][i]

          elif myMin[0] == "subs":

               str4 = "Replace " + str(myMin[2]) + " with " + str(myMin[3])
               #print "Replace " + str(myMin[2]) + " with " + str(myMin[3])

               outputList.append(str4)

               i = i - 1
               j = j - 1
               myMin = table[j][i]


     outputList.reverse()

     for temp in outputList: print temp

def playlist_transform(s,t,compareType="Song"):
     def memo(func):
          cache = {}
          @wraps(func)
          def wrap(*args):
               if args not in cache:
                    cache[args] = func(*args)
               return cache[args]
          return wrap

    
     s.insert(0, None)
     t.insert(0, None)

     a = len(s) - 1
     b = len(t) - 1
     #print ("a = %d and b = %d" % (a, b))
     table = [[None for x in s] for c in t]

     #print len(table)

     @memo 
     def edit_dist(i, j):
          if i == 0: return j
          if j == 0: return i

          if compareType == "Song":
               #if both songs are equal
               if compare_song(s[i], t[j]):
                    isMatch = True
                    match = edit_dist(i-1, j-1)
                    
               else:
                    isMatch = False 
                    match = edit_dist(i-1, j-1)+1

          elif compareType == "Artist":
               
               #if both songs are equal
               if compare_artist(s[i], t[j]): 
                    isMatch = True
                    match = edit_dist(i-1, j-1)
               
               else:
                    isMatch = False 
                    match = edit_dist(i-1, j-1)+1

          elif compareType == "Genre":
               #if both songs are equal
               if compare_genre(s[i], t[j]): 
                    isMatch = True
                    match = edit_dist(i-1, j-1)
               
               else:
                    isMatch = False 
                    match = edit_dist(i-1, j-1)+1
    
          #we might  need to insert a song
          inst = edit_dist(i, j-1)+1
          #we might need to delete a song

          dele = edit_dist(i-1, j)+1

          myMin =  min(match, inst, dele)

          # recursion will break before meeting these two spots in the table
          if table[1][0] is None: 
               for x in range(1, len(t)): 
                    table[x][0] = ("ins", x, t[x])
               table[0][0] = None
          if table[0][1] is None: 
               for x in range(1, len(s)): table[0][x] = ("del", x, s[x])
               table[0][0] = None

          if i >=0 and j >=0:
               if myMin == match and table[j][i] is None: 
                    if isMatch == True:
                         table[j][i] = ("match", myMin, s[i])
                    else:
                         table[j][i] = ("subs", myMin, s[i], t[i])
               elif myMin == inst and table[j][i] is None:
                    table[j][i] = ("ins", myMin, t[j])
               elif table[j][i] is None: table[j][i] = ("del", myMin, s[i])

          return myMin

     distance = edit_dist(a, b)

     back_track(table, a, b)

     s.remove(None)
     t.remove(None)
     
     return distance

if __name__=="__main__":
    #obtain local copy from http://lyle.smu.edu/~tylerm/courses/cse3353/blues1.csv
    b1 = read_playlist("blues1.csv")
    #obtain local copy from http://lyle.smu.edu/~tylerm/courses/cse3353/blues2.csv
    b2 = read_playlist("blues2.csv")
    print "Playlist 1"
    for song in b1:
        print song
    print "Playlist 2"
    for song in b2:
        print song
    print "Comparing playlist similarity by song"
    print playlist_transform(b1,b2)
    print "Comparing playlist similarity by genre"
    print playlist_transform(b1,b2,"Genre")
    print "Comparing playlist similarity by artist"
    print playlist_transform(b1,b2,"Artist")
    #include your own playlists below