README:

CREDITS AND FOR MORE INFO VISIT: 


http://ranger.uta.edu/~weems/NOTES2320/LAB/LAB5FALL18/

PROGRAM:

Design, code, and test a C program to determine strongly connected components for a directed graph whose input is strings. For the original code visit the link below.

http://ranger.uta.edu/~weems/NOTES2320/dfsSCC.c

INPUT:
1. The first line is two integer values: n, the number of vertices, and m, the number of edges.
2. The remaining m lines will each contain two values defining an edge: a tail name (string of no more than 25 characters) and a head name (another string).
While reading the input, new vertex names should be stored in a double hash table along with consecutively assigned vertex numbers. The first line of your output should indicate the size of your double hash table

Here the purpose of Hash Table is to only remove the duplicates. This can be done by other methods but anyone can use it if they have trouble creating hash tables for strings.
In addition to the double hash table, a table of vertex names will be needed. This is needed when printing your results
for the end user
The assigned vertex numbers are used to build compressed adjacency lists 
 Perform Kosaraju’s SCC algorithm. The elements of each SCC must be output using the vertex names, not numbers.
 
 Your double hash table should have the smallest prime size to assure a load factor no larger than 90%. You will need code
for a simple function to compute this value.