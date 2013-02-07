# 2/2/2013
# CSE3353 H1 Starter code 

import datetime, random, itertools, timeit

movieTimes={"Tarjan of the Jungle": (datetime.date(2013,3,1),datetime.date(2013,10,15)),
     "The President's Algorist": (datetime.date(2013,1,1),datetime.date(2013,7,15)),
     "'Discreet' Mathematics": (datetime.date(2013,1,15),datetime.date(2013,5,15)),
     "Halting State": (datetime.date(2013,7,1),datetime.date(2013,11,30)),
     "Steiner's Tree": (datetime.date(2013,9,1),datetime.date(2014,1,15)),
     "The Four Volume Problem": (datetime.date(2013,12,15),datetime.date(2014,6,30)),
     "Programming Challenges": (datetime.date(2014,2,1),datetime.date(2014,6,15)),
     "Process Terminated": (datetime.date(2014,5,1),datetime.date(2014,10,15)),
     "Calculated Bets": (datetime.date(2014,6,25),datetime.date(2014,11,15))
     }



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
    
	return false;

    ###############################################################
    # Part (a): Write code here to check intervals for overlap. 
    # Be careful to consider all cases.
    ###############################################################



if __name__=='__main__':
    #Include a printout labeled "Test Code" of whatever output 
    #results from running the following test code.
    ###############################################################
    # (b) Test Job 1: confirm that the checkOverlap is working        
    ###############################################################
    startTimes = [(movieTimes[m][0]) for m in movieTimes]
    endTimes = [(movieTimes[n][1]) for n in movieTimes]
    titles = []
    for t in movieTimes:
        titles.append(t)
    #print titles[0]
    #print startTimes[0]
    #print endTimes[0]
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


    ###############################################################
    # (f) Test Job 3: see that exhaustiveScheduling and earliestFinish 
    # give the same answer, and that both appear correct for 15 
    # movies generated using generateJobs(15). 
    # Print the optimal selection movie names, plus start and end 
    # times, in sorted order for both algorithms. Also print the 
    # other movies that did overlap in sorted order.
    # (Test code for part (b/c))
    ###############################################################    
 
