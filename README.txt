README for Genealogy
Original author: Morgan McKinney 4/2020

genealogy.cpp: Builds a family tree using user commands.
Output is piped into a .out file, displaying results of commands.
May invoke using 'make run' to run using testData.txt.
Expected input: ./genealogy < INPUT TEXT FILE > OUTPUT DESTINATION
Due to the nature of how edges are stored, issues arose while
trying to find the shortest path from vertex A to B. However,
the skeleton of what "should" work is included in the source code
under the function relate().

tmpRun.out: Holds output of genealogy program. May invoke using 'cat'
in the command prompt. Output based on provided data text file.
Expected input: cat tmpRun.out

testData.txt: Hold student created data. May invoke using 'cat' in 
the command prompt.
Expected input: cat testData.txt

testRun.out: Holds output of genealogy program. May invoke using 'cat'
in the command prompt. Output based on student created data.
Expected input: cat testRun.out

Makefile: Intended to easily compile and run student program. May invoke a
variety of commands using the 'make' prefix.
Expected input (example): make run
Modification of run based on desired input text file and output destination
may be done with ease using the included makefile.
