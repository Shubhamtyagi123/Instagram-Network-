OOPS using C++ assignment

We as the members of group were assigned the solving the problem number 6 from the given set of questions which was about creating a INSTAGRAM network of the class students.

In this problem we have taken the data of all the classmates in form of a table separated by a delimiter (,) in a file (Newfile.csv). In this question the inputs were in form of 0 and 1 i.e., if a student follows any of the other student then the input is 1 otherwise 0. Let us take a 2-D matrix to understand this, for example, in a position say [1,3] if the input is 1 then 1 follows 3 but it may not be possible that 3 follows 1 at [3,1].

The number of students can be changed by making changes in the file, but then u will have to verify the number of students during input. If number entered is not equal to the numbers of students registered then it will display invalid input.

The massage “Invalid Input” will be shown whenever :- 

* Number of students entered is less than number of students in the file.
* Any other input except 0 and 1 is given in the file including characters(a,b,..) or special symbols($,#,…).
* Inputs like 00,01 or 0,,1,,,1. It will only read 0,1.
* The file is not included.

It is a menu driven program and it will display the contents of the file followed by a menu when we enter the correct number of students.

1. The first option will display the list of all the students who follow each other along with their names. 

The algorithm behind this part was we checked the value at index position of both students is equal to the index position in reverse order, then print the names of both.
2. The second option asks for inputing two students and tell whether they follow each other or not. If yes display they follow each other else display all the possible routes between the two. 
DUE TO VERY LARGE DATA, CONNECTIONS PROCESSING WILL TAKE TIME. Please be patient.

The algorithm behind this question was doing a BFS (Breadth First Search) in the given list of data. In this algorithm all the possible routes from the source to the destination can be calculated in a adjacency
Matrix(a matrix having input 1 and 0 with all diagonals as 0). 

It implies :
* Visit the adjacent unvisited data. Store it in a variable. Display it and insert it in a queue.
* If all the adjacent vertices are covered , dequeue the first data from queue.
* Repeat the above two processes until the queue gets empty.
* As soon as the queue gets empty, the program is over.

     In this way we will get all the possible routes between the two students if they don’t follow each other. And if there is no possible ways between the two then it will display No Connections found.

3. In option 3, we find out all the students who are followed by these two students entered.
The algorithm used in this part is keeping the row index equal to their roll number and searching the columns. If the data at any position is 1 for same column then print the column number else if no search is found it will display they don’t follow a common person. 

4. In option 3, we find out all the students who follow these two students entered.
The algorithm used in this part is keeping the column index equal to their roll number and searching the rows. If the data at any position is 1 for same row then print the row number else if no search is found it will display they don’t have a common follower.
In options 2,3,4, if the roll numbers entered are wrong(like 0 or any no. greater than the number of students), then it will display Invalid roll numbers.

5. In this option we find the student(s) who have the maximum followers.
Firstly, we count all the followers for every roll number.
Next we store them in a array.
then find the maximum among them and print their roll number which is the index.

6. The last option is for exiting the program.

  As it is a menu driven program so it will ask for continuation or not.

The differents modules were tackled by all the group members equally including the file handling part and validation checks. All the algorithms were discussed and implemented after that.

Bibliography:   C++ by Herbert Schildt, tutorialspoint.com ,Wikipedia, stackoverflow.com 
 


