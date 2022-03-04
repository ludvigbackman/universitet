# Build and Run

To build the program type "make all"
In order to run the program you can either type "make test" to run the program with the 16k-words textfile 
or type "./freq-count filename.txt" with filename being replaced with the textfile of your choice.




# Handling Errors

For handling errors we decided to implement a struct called option_t. This struct contains two values, a boolean indicationg whether or not the operation failed, as well as the value returned if the function succeded. Where we used this struct is defined in the .h files. The responsibilty to handle a function that does not return a successful struct, falls upon the caller.






# Initial Profiling Results
When analysing the 2 smaller txt-files we got no result, all functions took 0.00 sec so we just looked at 10k and 16k.
The top three functions for our different inputs seems to be: h_t_has_key, l_l_create, and l_l_insert, as you can see below.
These top three functions seem to be consistent across load factors and inputs, however the insert functions does not seem to be as often used for the smaller inputs.
There does seem to be an upwards trend regarding the time spent on the has key function. The increase is exponential, which is to be expected as the amount of words the function has to loop through will increase linearly as the input size increases. 
This was to be expected, however not what we first anticipated. We believe that we could easily make the program faster by decreasing the reliance on the has_key function, as it appears to be called upon where other functions might be able to take its place with greater efficiency. The efficiency of the function itself appears to not be too demanding, considering the opperations whithin it are found in many other functions.




  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name 

 10k-words   load factor = 0.75
 83.45      0.05     0.05                             ioopm_hash_table_has_key
 16.69      0.06     0.01                             ioopm_hash_table_values
  0.00      0.06     0.00  1043663     0.00     0.00  main
  0.00      0.06     0.00    10001     0.00     0.00  process_file
  0.00      0.06     0.00      200     0.00     0.00  process_word

16k-words   load factor = 0.75
 60.23      0.83     0.83                             ioopm_hash_table_has_key
  7.98      0.94     0.11                             ioopm_linked_list_insert
  6.53      1.03     0.09                             ioopm_linked_list_clear
  6.53      1.12     0.09                             ioopm_linked_list_create
  5.81      1.20     0.08                             ioopm_linked_list_append
  4.35      1.26     0.06 26004715     2.31     2.31  main
  3.63      1.31     0.05                             ioopm_hash_table_values
  3.63      1.36     0.05                             ioopm_linked_list_all
  0.73      1.37     0.01                             ioopm_hash_table_dynamic_create
  0.73      1.38     0.01                             ioopm_linked_list_prepend
  0.00      1.38     0.00    16993     0.00     0.00  process_file
  0.00      1.38     0.00     4371     0.00     0.00  process_word

16k-words   load factor = 1
 56.77      0.89     0.89                             ioopm_hash_table_has_key
 10.21      1.05     0.16                             ioopm_hash_table_values
 10.21      1.21     0.16                             ioopm_linked_list_insert
  8.29      1.34     0.13                             ioopm_linked_list_append
  5.10      1.42     0.08                             ioopm_linked_list_create
  4.46      1.49     0.07                             ioopm_linked_list_clear
  1.91      1.52     0.03 26004715     1.16     1.16  main
  1.91      1.55     0.03                             ioopm_linked_list_all
  0.64      1.56     0.01                             ioopm_hash_table_dynamic_create
  0.64      1.57     0.01                             link_create
  0.00      1.57     0.00    16993     0.00     0.00  process_file
  0.00      1.57     0.00     4371     0.00     0.00  process_word

  16k-words   load factor = 3
 52.33      0.58     0.58                             ioopm_hash_table_has_key
  9.02      0.68     0.10                             ioopm_linked_list_insert
  8.12      0.77     0.09                             ioopm_linked_list_create
  7.22      0.85     0.08                             ioopm_hash_table_values
  7.22      0.93     0.08                             ioopm_linked_list_append
  7.22      1.01     0.08                             ioopm_linked_list_clear
  5.41      1.07     0.06                             ioopm_linked_list_all
  2.71      1.10     0.03 25888714     1.16     1.16  main
  0.90      1.11     0.01                             ioopm_linked_list_prepend
  0.00      1.11     0.00    16993     0.00     0.00  process_file
  0.00      1.11     0.00     4371     0.00     0.00  process_word