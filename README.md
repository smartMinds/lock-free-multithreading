#Job interview task
Task for HFT company. 

##Desctiption

###Input data:
CSV file with numbers.
###Task:
To write an application in c++ under OS Linux, which will have 2 threads:

- <b>First thread</b> - reads numbers from the file and puts them to the circular buffer.
- <b>Second thread</b> - reads numbers from the circular buffer and adds them to data container. All values after the sorting should be unique.

###Output data:
- Application work time
- Sorted list of unique numbers

###Criteria for evaluation of the solution
1. Application work time
2. Code readability
3. Workarounds count

#### <i>Script for csv file generation located</i> – [csvGenerator.py](scvGenerator.py)
