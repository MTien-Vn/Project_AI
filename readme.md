# Finding optimize shipping path

**How to use**
Go to directory *final* and run file
>find_order_list_and_path.cpp
See result in file *result.txt*

**What output show**
Look at file *result.txt* in directory *final*
The output is following this format:
- First line is number of orders can be shipped
- In the several line after, show detail about each order, includes:
  - First line of group is 4 numbers: start location, destination location, number of street need to pass through(*M*), total time spend
  - Next *M* lines, each line contains 3 number explain the street: start location, destination location, time duration 