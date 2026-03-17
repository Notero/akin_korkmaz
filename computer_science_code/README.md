# Computer Science Codebase: Comprehensive Syllabus

This repository serves as a centralized archive of academic and independent development in Computer Science. It spans from low-level systems programming in C to high-level application architecture and API development in Java, documenting a progression through fundamental computer science pillars.

## Table of Contents

- Featured Projects

- Technical Exercise Index: C Language

- Technical Exercise Index: Java Language

- Compilation and Usage

- Environment

- Skills Demonstrated

- Featured Projects (Multi-File Architectures)

$$C$$

Custom Terminal and Shell Implementation (/lang_c/custom_terminal)

Educational Core: Operating Systems, Process Management, and Inter-process Communication (IPC).

Logic: A custom shell (mysh) that handles command parsing, process forking via fork(), and program execution using the exec family of system calls. It implements robust I/O redirection (>, <) and piping (|) between processes.

Features: Includes a comprehensive suite of proc-tests to validate edge cases in piping logic and argument handling.

Build Tool: Makefile

$$C$$

Computer Design Project (/lang_c/computer_design_project)

Educational Core: Computer Architecture and MIPS Instruction Set Simulation.

Logic: Implementation of spimcore to simulate the internal components of a processor. This includes the Arithmetic Logic Unit (ALU), instruction fetching cycles, register file management, and memory access control.

Tech: C programming with strict header file management and modular code separation.

$$Java$$

Spring Boot API and Student Lab Tracker (/lang_java/java_spring_api)

Educational Core: Full-stack architecture, RESTful APIs, and Persistence.

Logic: A Model-View-Controller (MVC) application using Spring Boot and an H2 Database. It tracks student lab attendance, managing student profiles and session records.

Tech: Java, Spring Framework, Maven (pom.xml), Thymeleaf templates for the frontend, and Spring Data JPA for persistence.

Technical Exercise Index: C Language (/lang_c)

1. Data Structures and Advanced Algorithms

binary_search_tree.c (BST): Implementation of insertion, deletion, and search algorithms in a sorted tree structure.

list_implementation.c (Linked Lists): Manual pointer manipulation for creating and traversing dynamic linear data structures.

queue_implementation.c (Queues): Implementing First-In-First-Out (FIFO) logic using both array-based and pointer-based approaches.

Tries.c (Prefix Trees): Specialized tree structure optimized for efficient string retrieval and prefix matching.

flood_fill.c (Graph Algorithms): Implementing Breadth-First Search (BFS) for regional area processing and grid traversal.

shortest_possible_string.c (Greedy/Strings): Solving the Shortest Common Superstring problem via overlap detection and string manipulation.

2. Systems Programming and Resource Management

joint_dynamic_memory.c (Memory): Deep dive into heap allocation, manual memory management, and pointer arithmetic to prevent leaks.

osystems_file.c (File Systems): Utilizing low-level system calls for file descriptor manipulation and persistent data storage.

resource_allocation.c (Deadlock): Algorithmic simulation of resource requests and implementation of deadlock avoidance strategies.

sorted_array_resource_allocation.c (Resource Mgmt): Managing available system resources efficiently within sorted data constraints.

file_system_project.c (Storage): High-level simulation of file storage, directory structures, and metadata management.

alu_insfetch.c (Hardware Logic): Simulation of the fundamental CPU cycles: Arithmetic Logic Unit operations and Instruction Fetch.

3. Application Logic and Utilities

battle_ships_terminal_game.c (Game Logic): Complex state management and 2D array manipulation within a CLI environment.

common_search_sort_functions.c (Sorting): Comparative implementation of standard search (Linear/Binary) and sort (Bubble/Quick) algorithms.

math_library_logic.c (Computation): Recreating standard mathematical library functions to understand algorithmic complexity.

word_frequency_string.java (Text Processing): Tokenizing strings to analyze frequency (housed in C directory for cross-language comparison).

reciperion.c / .h (Modularization): Practicing header file separation, interface-based programming, and modular C design.

djauto.c (Automation): Script-like C implementation designed for automated task logic and execution.

vase_project.c (Geometry/Logic): Utilizing programming to solve specific spatial, geometric, or mathematical problems.

4. Language Fundamentals and Syntax

Basics: basics_and_variables.c, input_and_arithmetic.c, menu_functions.c, review.c.

Control Flow: nested_conditionals.c, functions_and_switch.c, loop_patterns_modulo.c, while_loop_counters.c, sentinel_loop_logic.c.

Data Handling: 2d_array.c, structs.c, structs_and_arrays.c, strings.c, substring_extraction.c.

Technical Exercise Index: Java Language (/lang_java)

1. Algorithms and Optimization

backtrack.java (Recursion): Navigating state-space trees to find solutions via backtracking and pruning.

dynamic_programming.java (DP): Optimizing recursive solutions using memoization to reduce time complexity.

dynamic_programming_2.java (DP): Advanced table-based (bottom-up) optimization strategies for complex problems.

greedy_algorithms.java (Optimization): Implementing locally optimal choices to solve global optimization problems.

kruskals_algorithm.java (Graphs): Finding the Minimum Spanning Tree (MST) using Disjoint Set Union (DSU).

2. Object-Oriented Design and Systems

threads (Race.java, etc.) (Concurrency): Managing Hare/Tortoise threads and synchronizing shared states to prevent race conditions.

gui-web (UI Architecture): Designing component-based web interfaces and handling user interaction events.

junit_testing (QA/Testing): Writing robust unit tests to ensure code reliability and validate edge-case handling.

input_output_streams.java (I/O): Managing data flow between applications and external files using Java IO/NIO.

3. Data Collections and Project Modules

Unique Pairs: unique_pairs.java & test_cases (HashMap-based relationship mapping and student pair counting).

Map/Address Book: AddressBook.java, Address.java, AddressBookController.java (MVC-lite approach to data management).

Stack Logic: Card.java, FacedCard.java, RandomStackof8.java (LIFO data structure applications).

Queue Logic: Person.java, TicketQueue.java (ArrayList-based FIFO queueing simulation).

Compilation and Usage

For Individual Files

All code is developed and tested on a 14-inch MacBook Pro (Apple M3 Pro, 18GB Unified Memory).

C Files:

clang -Wall file_name.c -o program
./program



Java Files:

javac FileName.java
java FileName



For Projects

Makefile Projects: Navigate to the folder and run make.

Maven Projects: Navigate to the folder and run ./mvnw spring-boot:run.

Environment

Platform: macOS

Hardware: Apple M3 Pro (14-inch MacBook Pro)

Memory: 18GB Unified Memory

Skills Demonstrated

Through the completion of these exercises and projects, the following core competencies have been established:

Systems-Level Thinking: Understanding memory hierarchies, process states, and hardware-software interfaces.

Algorithmic Problem Solving: Selecting the correct data structure (Trees, Graphs, HashMaps) for optimal time and space complexity.

Software Architecture: Moving from procedural, single-file scripts to modular, object-oriented, and MVC-based web applications.

Toolchain Proficiency: Comfortable using terminal-based compilers (clang, javac), build automation (make, maven), and POSIX-compliant environments.

Contact

Akin Korkmaz Computer Science Student & Developer GitHub Profile
