# Contact-Search-Application
User can add contacts to directory and search the contact name using a given prefix.


Instructions to Run Code:

1) User need to enter 1 to insert contact, 2 to search contact, 3 for exit.
2) After inserting any of 1,2 user need to enter the name that he wants to search.
3) To exit, user need to enter 3.

Test Cases:

    1
    Enter Name: sam curran
    1
    Enter Name: tom curran
    2
    Enter Name to Search : cur
    tom curran
    sam curran
    2
    Enter Name to Search : sa
    sam curran
    1
    Enter Name: Virat Kohli
    1
    Enter Name: Virat Singh
    2
    Enter Name to Search : Vir
    Virat Kohli
    Virat Singh
    2
    Enter Name to Search : irat
    No Results Found for irat
    1
    Enter Name: Vishal
    2
    Enter Name to Search : Vi
    Virat Kohli
    Virat Singh
    Vishal
    3
    Happy Searching
    


How Code Works

1) We are using Trie data structure to store and search every inserts.
2) Each node has 2 boolean variable one denote if this is the end of string, other denote if this string is having
   both first and last name i.e if it is space seprated.
3) If we encounter such strings (space seprated) we reverse it i.e last name after first name,mark its end node as reverse true,
   so that we can again reverse it to get our desired string.
4) Whenever we encounter any space we repace it with a underscore and before printing output we again change it to space.
5) Each node holds pointer to upper/lower case [A-Z] [a-z] and some special characters as well.
6) For inserts we simply mark each char true in our trie and at the end mark its end parameter as true.
7) For space sperated string we insert it twice, one with normal first and last name, other with last name first and first name after and mark its toReverse parameter in the end as true (as we need to again reverse it).
8) For searching we first move to end of the node of serached string, and apply dfs to get all the results after the end of the prefix string.


Handling User Input Errors:

1) *If searching is applied before inserting any string, code simply gives warning.
2) *If any other input is provided other than 1,2,3 code again gives warning.
3) *To exit user need to enter 3.
    
    

    
