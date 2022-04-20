# CS-300-Project-2
CS-300 Binary Search Tree Project </br>
Nicholas Ciesla
</br>
</br>
In the projects for this course. We were asked to read data from a CSV or a text file and load it into a data structure, from there, we were asked to sort the information, remove information, search for information, and print all information. With this particular project, we were to read course information in from a text file and load it into a data structure of our choice. I decided to go with the Binary Search Tree as it is the most consistent performer out of all of our options. The Hash table was another tempting candidate for the purpose of possible o(1) operations, but I decided against it for reasons outlined in more detail in my pseudocode document. This includes a runtime analysis. Using the correct data structure can make a huge difference in the performance of a program. Memory is also important to consider. While using a Hash Table may have provided a faster runtime, in-order to create a perfect hash within my time constraint, I would have had to of used a n unnecessary amount of memory. The Binary Search Tree was my best choice at my current level of knowledge. 
</br>
</br>
My biggest roadblock on this assignment was reading and splitting a file by delimiter in C++. Previous to this class, I haven't had any experience using C++ to do this. I found it very difficult at first and couldn't understand why I was getting jumbled data. It turned out that I was using string's find() method incorrectly. Instead of checking for string::npos, I was checking for -1. This was solved with some specific googling and reading on stack overflow.
</br>
</br>
This project has really expanded my horizons on data structures. Previous to this course, I would have never implemented a Binary Search Tree when I wasn't required, but know that I know how simple it can be to implement, I plan on considering it going forward. The code I used for the basic tree operations will also be very easy to re-use and adapt to new projects.
