Project 1 
Vivek Reddy Kasireddy & Jahnavi 
Parts 1,2,& 3 are completed. 

1. How does the choice to generate random numbers before forking affect process behavior?

Generating random numbers before forking ensures that each child process inherits the same state of the random number generator from the parent process. If random numbers were generated after forking, each child process would have its own instance of the random number generator, which could lead to unintended behaviors such as repeating random values across processes if the random generator state is not updated independently in each child.

3. Describe the debugging steps you would follow if ”The Explorer” produced incorrect directory listings. How would you validate each step? Add your answer to your README.
To debug incorrect directory listings in "The Explorer," first verify the input path and ensure proper permissions. Then, check the code for directory listing, confirm hidden files are included, and test the output with other tools. Additionally, validate the file system integrity, restart the application, and check for updates or bugs.

PARTS 4 & 5 yet to be done. 