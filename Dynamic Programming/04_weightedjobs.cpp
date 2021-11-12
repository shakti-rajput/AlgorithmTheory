#include<iostream>
#include<vector>
#include<numeric>


/*
Dynamic solution to find the cost of optimal job scheduling

Problem:
Given N intervals, each with {start, end, profit}
Find optimal schedule of non-overlapping intervals,
such that total profit is maximized.

Solution:
Apply a lambda to store the indexes of the potentially sorted end times
Create a vector W which will store the optimal cost
for the moment right after a job is executed.
The optimal cost at time i is given by: max{W[i-1], p[i] + W[P[i]]}
-> p[i] is the profit of the current job;
-> W[P[i]] is the optimal profit until last job finished before start of job i;
-> P[i] is found with modified binary search.
In particular, P[i] is a redundant instance, thus omitted.
*/ 


int lBound(const std::vector<int>& A, const std::vector<size_t>& ind, const int & val){
	size_t len = A.size();
	size_t bound = 0;
	while (len){
		size_t half = len/2;
		size_t mid = bound + half;
		if (A[ind[mid]] < val) {
			bound = mid + 1;
			len -=  half + 1;
		}
		else
			 len = half;
	}
	return bound;
}


// to match the signature of 1235. in Leet Code ~~> ranked in top 3% in both time and space
int jobScheduling(const std::vector<int>& startTime, const std::vector<int>& endTime, const std::vector<int>& profit) {
	size_t N = startTime.size();
	std::vector<size_t> inds (N);
	std::iota(inds.begin(), inds.end(), 0);
	std::sort(inds.begin(), inds.end(), [&](size_t a, size_t b) -> bool { return endTime[a] <= endTime[b];});

	std::vector<int> W(N+1);
	for (size_t i=0; i < N; i++)
		W[i+1] = std::max(W[i], profit[inds[i]] + W[lBound(endTime, inds, startTime[inds[i]]+1)]);
	return W[N];   
}




int main(){
	std::vector<int> starts = {1,2,3,4,6};
	std::vector<int> ends = {3,5,10,6,9};
	std::vector<int> profits = {20,20,100,70,60};
	std::cout << jobScheduling(starts, ends, profits) << std::endl;
	return 0;
}