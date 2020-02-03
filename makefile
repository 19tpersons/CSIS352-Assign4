# Your name here 
# CSIS 352 - Asmt #1
# Makefile - prog1

# Note: There are a lot of comments in this makefile that describe how
# a makefile works.  You don't need to keep these comment in there.
 
# This file allows an administrator of another unix system to "install"
# the 'prog1' program on his/her system. 

# MACRO DEFINITIONS

# The CC macro is used to indicate which compiler to use.
# This allows you to write the rules and then have the installer 
# specify the appropriate compile tool.

CC = g++ 

# The OBJECTS macro indicates all the .o files necessary to "build
# your executable ... to simplify later lines

OBJECTS = main.o read.o write.o sort.o findsum.o

# The LFLAGS macro is used to tell the compiler to use other libraries.

LFLAGS = 

# The CFLAGS macro is used to indicate flags for the compiler.
# Eg. you MAY want to put '-g' on this line to generate symbol table
# information so that you can use the 'ladebug' debugger to view your
# program in execution, or you could use the '-O' option to do
# optimized compilation, etc.  Again, as with other macros, it may
# be empty.

CFLAGS =  
 
# The EXE macro is used to indicate the name of the executable to
# be produced.

EXE = prog1

# This ends the MACRO DEFINITIONS SECTION

# DEPENDENCIES AND RULES SECTION
# This next section contains groups of lines that look like:
#
# target: dependencies
#       rules(s) or action(s)
#
# Note that each group has a line that starts on the left margin
# followed by one or more lines that begin with a TAB
# This is VERY IMPORTANT ... THE RULES MUST START WITH A TAB!!!!
# 
# The dependencies list the files that the target DEPENDS on,
# the rules tell how to (re)construct the target.
#
# Where ever you see a $(macro_name), the 'make' utility makes a 
# text substitution, using the Right Hand Side of the macro
# definitions from the above section.
#
# Compiling source code to create the object files.
# This is an example only and is modified for your needs
# A backslash continues a command on the next line if needed.
# The backslash would have to be THE LAST character on the line.
# A semicolon can be used to separate multiple commands.

$(EXE):		$(OBJECTS) 
		$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS) 

main.o:		main.cpp
		$(CC) $(CFLAGS) -c main.cpp 

read.o:		read.cpp
		$(CC) $(CFLAGS) -c read.cpp 
    
write.o:	write.cpp
		$(CC) $(CFLAGS) -c write.cpp 

sort.o:		sort.cpp
		$(CC) $(CFLAGS) -c sort.cpp 
    
findsum.o:	findsum.cpp
		$(CC) $(CFLAGS) -c findsum.cpp 
    
# The next lines allow you to type 'make clean' to remove unnecessary
# files following compilation and linking of your program.  Generally,
# the executable is not deleted but for purposes of this class, remove
# the executable to reduce the size of the tarred and compressed file
# you are to electronically handin.

clean:
		rm -rf $(EXE) $(OBJECTS) 

