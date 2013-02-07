# 2/2/2013
# CSE3353 H1 Starter code 

import datetime, random, itertools, timeit

movieTimes={ "Tarjan of the Jungle": (datetime.date(2013,3,1),datetime.date(2013,10,15)),
     "The President's Algorist": (datetime.date(2013,1,1),datetime.date(2013,7,15)),
     "'Discreet' Mathematics": (datetime.date(2013,1,15),datetime.date(2013,5,15)),
     "Halting State": (datetime.date(2013,7,1),datetime.date(2013,11,30)),
     "Steiner's Tree": (datetime.date(2013,9,1),datetime.date(2014,1,15)),
     "The Four Volume Problem": (datetime.date(2013,12,15),datetime.date(2014,6,30)),
     "Programming Challenges": (datetime.date(2014,2,1),datetime.date(2014,6,15)),
     "Process Terminated": (datetime.date(2014,5,1),datetime.date(2014,10,15)),
     "Calculated Bets": (datetime.date(2014,6,25),datetime.date(2014,11,15))
}

def subsets(x):
    """
    Input: list x
    Output: all subsets of x (as list objects)
    Gives up on lists with more than 30 elements
    """
    if len(x)>30:
        return "Set too large"
    #enumerate all subsets of size i for i = 1 .. length(x) 
    sublists=[list(itertools.combinations(x,i)) for i in range(1,len(x)+1)]
    #flatten the subsets
    flatsubs=itertools.chain.from_iterable(sublists)
    return list(flatsubs)

def generateJobs(numjobs=10):
    """
    Input: number of jobs to create (default 10)
    Output: dictionary mapping movie names to random start and end dates
    """
    #set a seed value so everyone gets the same random jobs
    random.seed(33531337)
    moviejobs={}
    for i in range(numjobs):
        title = "Movie %i" % i
        startmonth = random.randint(1,12)
        startday = random.randint(1,28)
        startyr = random.randint(2013,2014+numjobs/10)
        startdt = datetime.datetime(startyr,startmonth,startday)
        #make job last between 3 and 6 months
        enddt = startdt+datetime.timedelta(random.randint(90,270))
        moviejobs[title]=(startdt,enddt)
    return moviejobs

def earliestJobFirst(movies):
    """
    Problem: Movie scheduling problem
    Input: dictionary mapping movie title to range of times
    Output: movie titles that returns the maximal subset of non-overlapping titles
    Solution: use earliest job heuristic to (incorrectly) calculate job list
    """
    #start by using a list comprehension to sort movie titles by start date
    starttimes=[(movies[m][0],m) for m in movies]
    starttimes.sort()                    #sort() takes n lg n time
    titlesort=[m[1] for m in starttimes] #one more comprehension to get the titles only
    joblist=[]
    #go through all jobs sorted by start date
    for jobcand in titlesort:
        overlap=False
        #check all jobs already accepted for overlap with the candidate job
        for job in joblist:
            if checkOverlap(movies[jobcand][0],movies[jobcand][1],movies[job][0],movies[job][1]):
                overlap=True
                break
        #if there's no overlap with existing jobs, add the job candidate
        if not overlap: joblist.append(jobcand)
    return joblist


def exhaustiveScheduling(movies):
    """
    Input: dictionary mapping movie title to range of times
    Output: movie titles that returns the maximal subset of non-overlapping titles
    """
    ###############################################################
    # Part (c): Write code here to check all subsets of movies  
    # to find the most movies that can be selected without overlaps
    # Note: you should use the subset() function defined above 
    # to enumerate all subsets of movies
    ###############################################################

    

def earliestFinish(movies):
    """
    Problem: Movie scheduling problem
    Input: dictionary mapping movie title to range of times
    Output: movie titles that returns the maximal subset of non-overlapping titles
    Solution: use "first job to finish" criterion to optimally select job list
    """
    ###############################################################
    # Part (d): Write code to implement the OptimalScheduling 
    # algorithm based on the pseudocode from p. 11
    ###############################################################
    #hint: start by using a list comprehension to sort movie titles by completion date

#def compareSpeed():
    ###############################################################
    # Part (g): Write code to compare times for implementation of 
    # earliestFinish and exhaustiveScheduling for 10,15,20,25 
    # movies and times. Use the timeit library and execute the 
    # function 100 times for earliestFinish and 10 times for 
    # exhaustive scheduling (3 times for 25 movies due to slow 
    # running time). 
    # Print the times for each algorithm and number of movies
    # Include the printout with your assignment
    ###############################################################

def checkOverlap(start1,end1,start2,end2):
    """
    Problem: check to see if the (start1,end1) interval overlaps with (start2,end2) interval.
    Input: 
      arg 1: start time 1
      arg 2: end time 1
      arg 3: start time 2
      arg 4: end time 2
    Output : True if there is overlap, False otherwise
    """

    if start2>=start1 and start2<=end1:
        return True
    elif end2>=start1 and end2<=end1:
        return True
    elif start1 >= start2 and start1 <= end2:
        return True

    return False;

    ###############################################################
    # Part (a): Write code here to check intervals for overlap. 
    # Be careful to consider all cases.
    ###############################################################

def isMutuallyNonOverlapping(_List):

    startTimes = [ (_List[m][0]) ] for m in _List ]
    endTimes = [ (_List[n][1]) ] for n in _List ]
    titles = [ (i) for i in _List ]

    for i in range(len(startTimes)):
        for j in range(i+1, len (startTimes)):
            overlap = checkOverlap(startTimes[i], endTimes[i], startTimes[j], endTimes[j])
            if overlap:
                return False
    
    return True

if __name__=='__main__':
    #Include a printout labeled "Test Code" of whatever output 
    #results from running the following test code.
    ###############################################################
    # (b) Test Job 1: confirm that the checkOverlap is working        
    ###############################################################
    
    startTimes = [(movieTimes[m][0]) for m in movieTimes]
    endTimes = [(movieTimes[n][1]) for n in movieTimes]
    titles = [ ( i ) for i in movieTimes ]

    for i in range(len(startTimes)):
        for j in range(i+1, len (startTimes)):
            overlap = checkOverlap(startTimes[i], endTimes[i], startTimes[j], endTimes[j])
            if overlap:
                print 'movie %s and movie %s overlap: true' % (titles[i], titles[j])
            else:
                print 'movie %s and movie %s overlap: false' % (titles[i], titles[j])

    ##################################################################
    # (e) Test Job 2: show a test case that shows earliestFinish working 
    # but earliestJobFirst does not select optimally. 
    # 
    ##################################################################

    print "################################################################################"
    print "################################################################################"
    


    print "################################################################################"
    print "################################################################################"
 
    ###############################################################
    # (f) Test Job 3: see that exhaustiveScheduling and earliestFinish 
    # give the same answer, and that both appear correct for 15 
    # movies generated using generateJobs(15). 
    # Print the optimal selection movie names, plus start and end 
    # times, in sorted order for both algorithms. Also print the 
    # other movies that did overlap in sorted order.
    # (Test code for part (b/c))
    ###############################################################    
 
