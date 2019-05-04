
how to run:
run make 
run ./FIRSTFIT FIRSTFIT 1024 ex75.txt for firstfit
run  ./BESTFIT BESTFIT 1024 ex75.txt for bestfit 
run ./NEXTFIT NEXTFIT 1024 ex75.txt for bestfit



For this project I have started with First Fit management system. As first Fit states my algorithm  begins to scan memory from the beginning and chooses the first available block that is large enough.
Here for the algorithm, I have dynamically allocated memory and flag, blocks and block2 are created to see the memory availability. Struc type big array is allocated dynamically to store all the bytes of process and their name.  
In this algorithm flag indicates if there is empty block. While adding or releasing new process flag  and block2 array keep tracks if block is empty or dirty respectively. By taking count of those information if new process size is smaller or equal then the process is allocated in that block. If added block is not dirty that means block is previously not used so available amount of memory is allocated as a new block.
In the script I have setup block name such that B1 to B8 denotes blocks to see if book example is satisfied. P1 t p7 as partition between them. After requesting B1 to B7 they are released and become block now new block name B is requested  which is allocated at block B2. B2 size is 12 also B size is 12. B2 is the first block from the beginning to hold B. this satisfies the First Fit algorithm.
Similarly for the BEST- FIT I have allocated a array dynamically and made sixteen blocks. FindKey function is defined to find closest big enough free block. After finding key block new process is added to that block.
Just opposite to FIRST-FIT I have searched free block from the end of allocated memory once the big enough block is found new process is added to that block.



