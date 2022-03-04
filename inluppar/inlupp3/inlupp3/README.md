
## How to run
To run the calculator, simply enter "make all" to compile, followed by "make run" into the terminal. To run the test file, enter "make run_test" after "make all" instead.


## Design decisions
We decided to remove the stack traceback from the printing of the exceptions. This is easily removed by removing the overridden 
instances of fillInStackTrace() in the exception classes. 
