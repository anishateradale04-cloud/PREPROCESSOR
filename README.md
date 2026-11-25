
PREPROCESSOR

Overview
A mini C preprocessor developed using C that performs comment removal, basic header file inclusion and macro substitution, generating a preprocessed ".i" file from the input source code.

Features
- Removes single-line and multi-line comments.
- Handles basic header file inclusion.
- Performs basic object-like macro substitution.
  
Project Structure
- "main.c" – Controls the preprocessing workflow.
- "comment_removal.c/.h" – Removes comments from source code.
- "file_inclusion.c/.h" – Handles header file inclusion.
- "macro_handler.c/.h" – Performs macro substitution.
- "Makefile" – Automates compilation and linking.
  
Workflow
1. Reads the input C file.
2. Removes comments and stores the result in "temp1.c".
3. Processes header file inclusion and stores the result in "temp2.c".
4. Performs macro substitution.
5. Generates the final ".i" output file.
6. Removes intermediate temporary files.
   
Compilation
make

Execution

./mypreprocessor filename.c
Example

./mypreprocessor test.c

The preprocessed output will be generated as "test.i".

Technologies Used
- C Programming
- GCC Compiler
- Linux
- Makefile
- File Handling and String Manipulation
Learning Outcomes
Practiced file handling, command-line arguments, modular programming, string manipulation, compilation and linking using Makefile.
