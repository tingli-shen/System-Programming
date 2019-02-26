# System-Programming

Write an SIC assembler that reads an SIC assembly program, translates SIC
statements into their machine code equivalents, and generates an object file.
Goals
1. Get familiar with C programming language.
2. Learn to use the I/O facilities and library functions provided by standard C.
3. Get experience with the system-level programming.
4. Get experience with separate compilation, make utility, and C debugger.
Guideline:
1. You have to demonstrate your program in person.
2. When demonstrating your program, have one of the following formats of the
report with you:
1) A pdf file on external storage that is accessible with USB interface, or
2) A paper copy.
3. You will get 30% bonus (i.e., your score for this assignment * 1.3) if you
succeed in demonstrating your program on November 13 between 2:10pm and
5:00pm.
4. Your report have to include the following elements:
1) A cover page.
2) The problem description.
3) Highlight of the way you write the program.
4) The program listing.
5) Test run results.
6) Discussion.
Programming Assignment 1 System Programming
Due: November 20, 2014 2 Chung Yung
Programming Assignment #1 Addendum
Assembler Directives
START, END, BYTE, WORD, RESB, and RESW.
Format of SIC Assembly Program
1) Each line has 4 fields:
i. (Optional) Label (up to 6 characters)
ii. Operation
iii. (Optional) Operands (no blank allowed)
iv. (Optional) Comment
2) If the first character is a “.”, the whole line is a comment.
3) There is no blank line in an SIC assembly program source file, except for
the last line.
SIC OPCODE Table
Mnemonic Opcode Mnemonic Opcode Mnemonic Opcode
ADD 18 AND 40 COMP 28
DIV 24 J 3C JEQ 30
JGT 34 JLT 38 JSUB 48
LDA 00 LDCH 50 LDL 08
LDX 04 MUL 20 OR 44
RD D8 RSUB 4C STA 0C
STCH 54 STL 14 STSW 18
STX 10 SUB 1C TD 10
TIX 2C WD DC
SIC Instruction Format
Programming Assignment 1 System Programming
Due: November 20, 2014 3 Chung Yung
Types of Record in SIC Object Code
Example Target Program
