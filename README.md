# SkipList
### Team members
Abhijith T R - 2020CSB1062  
Prashant Mittal - 2020CSB1113  
Shahnawaz Khan - 2020CSB1123  
Vinit Nana Hagone - 2020CSB1361  
### Teaching Assistant
Simran Setia
### Skip List Implementation as a part of CS201(DSA) project.
Implementation of Skip List and some of its functions such as insert, search, delete, traverse and find minimum element. We have also analysed the algorithms and studied their average time complexities. 
### Average Time Complexity of Skip List Operations :
1. Search : O(logn)
2. Delete : O(logn)
3. Insert : O(logn)
### How to run the program  
The program can be compiled and run directly in the terminal using gcc.  

### Expected inputs and outputs
First a query will be asked on whether you wish to see the times taken by each operation. Once Y or N is entered, the operation moves forward. You will be provided options and the operations can be carried out in any order. At any point during the execution, simply enter -1 when the choice is asked in order to stop the execution of the program.   

There are no restrictions on insert apart from the requirement to insert integers. This operation has no output.   

If search is pressed, there are no restrictions apart from the requirement to insert only integers. If the element is present, it will say so and it will also report if the element is not present in the skip list.  

If delete operation is used, there are no restrictions apart from the requirement to insert only integers. If the element is present, the element is simply deleted and nothing is displayed. If the element is not present, no error will be raised, however no element will be deleted from the skip list.  

The find minimum operation accepts no entries and simply returns the smallest valid element from the skip list. If the skip list was empty, it will say so on the screen. 
