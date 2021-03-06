## make_heap
Your task is to convert a given array of integers into a heap. You will
do that by applying a certain number of swaps to the array. Swap is an operation which exchanges
elements ππ and ππ of the array π for some π and π. You will need to convert the array into a heap using
only π(π) swaps. Note that you will need to use a min-heap insteadof a max-heap in this problem.

## job_queue
You have a program which is parallelized and uses π independent threads to process the given list of π
jobs. Threads take jobs in the order they are given in the input. If there is a free thread, it immediately
takes the next job from the list. If a thread has started processing a job, it doesnβt interrupt or stop
until it finishes processing the job. If several threads try to take jobs from the list simultaneously, the
thread with smaller index takes the job. For each job you know exactly how long will it take any thread
to process this job, and this time is the same for all the threads. You need to determine for each job
which thread will process it and when will it start processing.
### Solution idea: priority queue.

## merging tables
There are π tables stored in some database. The tables are numbered from 1 to π. All tables share
the same set of columns. Each table contains either several rows with real data or a symbolic link to
another table. Initially, all tables contain data, and π-th table has ππ rows. You need to perform π of
the following operations:
1. Consider table number πππ π‘ππππ‘ππππ. Traverse the path of symbolic links to get to the data. That is,
while πππ π‘ππππ‘ππππ contains a symbolic link instead of real data do
πππ π‘ππππ‘ππππ β symlink(πππ π‘ππππ‘ππππ)
2. Consider the table number π ππ’ππππ and traverse the path of symbolic links from it in the same
manner as for πππ π‘ππππ‘ππππ.
3. Now, πππ π‘ππππ‘ππππ and π ππ’ππππ are the numbers of two tables with real data. If πππ π‘ππππ‘ππππ ΜΈ=
π ππ’ππππ, copy all the rows from table π ππ’ππππ to table πππ π‘ππππ‘ππππ, then clear the table π ππ’ππππ
and instead of real data put a symbolic link to πππ π‘ππππ‘ππππ into it.
4. Print the maximum size among all π tables (recall that size is the number of rows in the table).
If the table contains only a symbolic link, its size is considered to be 0.
### Solution idea: disjoint sets.
### Note: using union heuristic does not really improve the efficiency of the algorithm for this problem.






