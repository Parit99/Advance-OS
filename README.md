This is the OS assignment the problem statement can be found here [Link to Google](https://ufile.io/rm29eued)

List of Files:

1. driver.h
2. inital.c
3. Makefile

Description of each file:

1. driver.h

It is responsible for initializing methods and libraries that are required for our programm.

2. intial.c

It is responsible for constructing the stadium and playing matches simuntaneously.

3. Makefile:

It is responsible to compile links wrapper,spawn_child and level_order files and create exec executable file.


* Way to compile the files:

On the terminal one has to type command "make" and it will compile all the files and will generate exec executable file.


* Way to execute project:

Once you have compiled the file using "make" executable exec is generated so to run the file type following command on terminal.
./exec


* Structure of the program.

Functions that are used and their workflow:
1. readfile
2. init
3. intialize_sharedmem
4. create_process
5. create_childs 
6. compute_final_matrix

1. readfile:

There is readfile function in our driver file that helps us in reading the inp.txt file and from that we will compute the matrix of matches and also will compute number_of_matches. 

2. init:

It is responsible for initializing shared segment in the memory.

3. intialize_sharedmem:

It attaches the created share memory part for the current process.

4. create_process:

This is our main function, here from the problem statement we got a clear idea that
there are only 2 levels first level contains the stadium creation and there are toal
N stadium given in our problem statement. so we will prempt all nodes using SIGSTOP at first level and then do SIGCONT.

5. create_childs

As we know from the problem statement that there are N-1 matches being played at each stadium
So there would be N-1 stadiums assosiated with every N stadium so on second level we will have
N-1 nodes coressponding to every N node.These nodes are created in simentaneous order.

6. compute_final_matrix:

Final matrix is created which does printing of all the process as specified in problem statement.


* Process Of Synchronization

Synchronization is carried out with concept of seamaphore here our track array acts as semaphore for every process
We will wait if track[current_process]=1 and after process has accessed the critical section we will make semaphore down
track[current_process]=0.



* Bugs and Solution:

Bugs in program:
> Use of Static Memory:

Bug : We have used predefined buffer_size=1000 and size of shared memory=1000 


* Solution to both the mentioned above flaw 

> Static Memory problem:

Solution is we can use dynamic memory allocation for resolving this problem.
