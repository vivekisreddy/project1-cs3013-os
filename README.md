# project1-cs3013-os

##Question 1


##Question 2
- What would happen if child processes did not wait for their descendants?
If the child processes did not wait for their descendants, then the parent-child hierarchy is broken. Each process will exit immediately after forking its child, without waiting for it to complete. This is a chaotic and unpredictable order of stopping the process since it has no proper exit codes up the chain.
