# CS315 Makefile for Program 5: Families
# Feel free to modify as needed.
# Original author: Raphael Finkel 4/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = genealogy
DATA = testData.txt
WORKING = workingGenealogy
PROG = prog5

# Compile and run student program, placing the result in tmpRun.out
run: $(GOAL) $(DATA)
	./$(GOAL) < $(DATA) > testRun.out
	less testRun.out

# Run a known working program, placing the result in tmpWorking.out
runWorking: $(WORKING) $(DATA)
	./$(WORKING) < $(DATA) > tmpWorking.out
	less tmpWorking.out

# Get the working program
$(WORKING):
	wget http://www.cs.uky.edu/~raphael/courses/CS315/$(PROG)/$(WORKING)
	chmod +x $(WORKING)

# Get the data
$(DATA):
	wget http://www.cs.uky.edu/~raphael/courses/CS315/$(PROG)/$(DATA)

# Modify the following recipe to zip what you want to include
zipAll:
	zip toSubmit.zip $(GOAL).* Makefile README.txt tmpRun.out testRun.out testData.txt

.PHONY: clean
clean:
	rm -f $(GOAL) $(WORKING) $(DATA) tmp* toSubmit.zip
