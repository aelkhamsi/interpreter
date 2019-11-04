# Compiler / Interpreter

## Description

### Introduction
A compiler is a program that can read a program in one language - the source language - and translate it into an equivalent program in another language - the target language;

An interpreter is another common kind of language processor. Instead of producing a target program as a translation, an interpreter appears to directly execute the operations specified in the source program on inputs supplied by the user

There is two parts during the compilation: analysis and synthesis. 


The analysis part reads the stream of characters making up the source program and groups the characters into meaningful sequences (Lexical Analysis), then it imposes a grammatical structure on them (Semantic Analysis). It then uses this structure to create an intermediate representation of the source program. After syntax and semantic analysis of the source program, many compilers generate an explicit low-level or machine-like intermediate representation, which we can think of as a program for an abstract machine.

The synthesis part constructs the desired target program from the intermediate representation.

### Implemented features

In this project, we've implemented the first part of the compilation, which is the Analysis phase until an intermediate representation of the source program is generated. The intermediate code is generated in the C language and maps the structure of an assembly source code (usage of registers and conditional or non conditional jumps, non-use of conditional structure (if else) or loop (for, while) ).

The program can also be used as an interpreter. It executes the commands giver by the user without producing an intermediate code.

## Languages  used
* C
* Lex
* YACC

## Syntax
This compiler is specific for a hybrid language that we created. its syntax is the following : 
```bash
a = 1;  			(affect a positif or negative integer to a variable) 
b = 1.0;  			(affect a positif or negative float to a variable) 
c = 2+1.0;			(affect the sum of two numbers, integers or floats, to a variable)
c = a+b; 			(affect the sum of two variables to a variable) 
c = if (a == 2) then 3 else 6;  (conditional structure) 
c = let x = 3 in (1+x);  	(local bindings)
```


### Use as a compiler

1. Write a source code with the hybrid language whose syntax is described in the last section. For example:
```c
a=1;
b=2;
c=a+b:
```
Examples of source codes are in the directory /tst

2. Run the following command:
```bash
./compil.sh (source_code_file)
```
The intermediate code (file test.c) and the final executable (file test) will be generated

### Use as an interpreter

1.Run the following commands in the root directory of the project:
```bash
make clean && make
./myml
```

	

	
