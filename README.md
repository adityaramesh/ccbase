<!--
  ** File Name:	README.md
  ** Author:	Aditya Ramesh
  ** Date:	12/05/2012
  ** Contact:	_@adityaramesh.com
-->

# Introduction

This project contains a very small header (125 lines) that implements
FastFormat's nifty formatting syntax, without the monolithic frameworks that
come with FastFormat, and its dependency, STLSoft. The functions in this header
accept the format arguments as variadic templates, and invoke
`operator<<(ostream&, ...)` to print out each argument specified in the format
string. This header requires a C++11-conformant compiler.
