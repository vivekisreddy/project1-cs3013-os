
# Project 1 
# Vivek Reddy Kasireddy & Jahnavi  

## Remarks 
The 'make' compiles all the 5 files without problem. You have to individually run each program individually using ./ prolific, explorer, generation, slug, and slugrace. For ./ slug you have to add number 1-4 for the for slugs like this "./slug 1" would run slug.c on the "seed_slug_1.txt" file. Do the same for the other three files. 

The makefile compiles all of the 5 files at once using the make all command. Then the run command, executes all 5 filea at once.


# Project 1 


## Question 1
How does the choice to generate random numbers before forking affect process behavior?

Generating random numbers before forking ensures that each child process inherits the same state of the random number generator from the parent process. If random numbers were generated after forking, each child process would have its own instance of the random number generator, which could lead to unintended behaviors such as repeating random values across processes if the random generator state is not updated independently in each child.


## Question 2
What would happen if child processes did not wait for their descendants?

If the child processes did not wait for their descendants, then the parent-child hierarchy is broken. Each process will exit immediately after forking its child, without waiting for it to complete. This is a chaotic and unpredictable order of stopping the process since it has no proper exit codes up the chain.


## Question 3

Describe the debugging steps you would follow if ”The Explorer” produced incorrect directory listings. How would you validate each step? Add your answer to your README.

To debug incorrect directory listings in "The Explorer," first verify the input path and ensure proper permissions. Then, check the code for directory listing, confirm hidden files are included, and test the output with other tools. Additionally, validate the file system integrity, restart the application, and check for updates or bugs.

To debug incorrect directory listings in "The Explorer," first verify the input path and ensure proper permissions. Then, check the code for directory listing, confirm hidden files are included, and test the output with other tools. Additionally, validate the file system integrity, restart the application, and check for updates or bugs.

## Question 4
Why is using different seed files critical when running parallel processes in the Slug Race? 

If you use different seed files when running parallel processes, it will make sure that each process behaves uniquely and avoids identical random behavior. If the same seed is used for every process, the rand() will generate same sequence of random numbers each time. This means, that all processes would have same delay times, and same coin flips, which means that the program would execute the same commands at the same time. This is not a realistic behavior.

## Question 5 
Imagine a real-world application for ”The Slug Race” concept. How would you implement additional logging or monitoring? Add your answer your README.

"The Slug Race" concept can be applied to a delivery system where robots or drones transport packages across a city. These robots race to their destination, with the goal of delivering packages as quickly as possible.