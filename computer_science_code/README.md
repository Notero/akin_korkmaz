# Comprehensive Syllabus: Computer Science Foundations

## 1. Educational Coursework Overview
This repository serves as a comprehensive academic portfolio covering core tenets of computer science, from low-level system architecture and memory management in C to high-level object-oriented programming, data structures, and advanced algorithms in Java. The coursework systematically progresses through fundamental control flow, intermediate data structures, and culminates in complex system-level projects and web APIs.

## 2. Featured Projects (Multi-file Folders)

### Custom Terminal (`lang_c/custom_terminal`)
* **Goal:** Implement process management, inter-process communication (IPC), and custom command parsing for a UNIX-like shell.
* **Tech Stack:** C, Makefile, Bash (for testing).
* **Core Logic:** Utilizes a custom parser and system calls (`fork`, `exec`, `pipe`) to handle command execution, piping, and input/output redirection.

### Computer Design Project (`lang_c/computer_design_project`)
* **Goal:** Simulate the core operations and datapath of a processor.
* **Tech Stack:** C.
* **Core Logic:** Implements the Arithmetic Logic Unit (ALU) and instruction fetch cycle, simulating low-level hardware execution.

### Java Spring API - Lab Tracker (`lang_java/java_spring_api`)
* **Goal:** Develop a web-based RESTful API to track student lab sign-ins and manage records.
* **Tech Stack:** Java, Spring Boot, Maven, HTML/Thymeleaf, H2 Database.
* **Core Logic:** Provides REST endpoints and controllers to persist and manage `signedstudent` entities, tracking attendance effectively.

### GUI Web (`lang_java/gui-web`)
* **Goal:** Demonstrate graphical element rendering and web controller integration.
* **Tech Stack:** Java.
* **Core Logic:** Manages UI elements and application states through an element repository and web controller.

### JUnit Testing (`lang_java/junit_testing`)
* **Goal:** Apply formal software testing methodologies to an Address Book application.
* **Tech Stack:** Java, JUnit, Maven.
* **Core Logic:** Asserts the correctness and robustness of data operations through comprehensive unit test cases.

### Data Structure Implementations (`lang_java/map`, `lang_java/queue_arraylist`, `lang_java/stack`)
* **Goal:** Create robust, object-oriented implementations of core data structures.
* **Tech Stack:** Java.
* **Core Logic:** Demonstrates practical use of Maps (AddressBook), Queues (TicketQueue), and Stacks (RandomStackof8) with custom domain models.

### Threading Simulation (`lang_java/threads`)
* **Goal:** Explore concurrent programming and thread synchronization.
* **Tech Stack:** Java.
* **Core Logic:** Utilizes Java threads to simulate a race condition and execution interleaving between a tortoise and a hare.

### Unique Pairs (`lang_java/unique_pairs`)
* **Goal:** Compute and verify unique data pairs against standardized test cases.
* **Tech Stack:** Java.
* **Core Logic:** Processes file-based input streams to identify unique pairs and systematically validates results against expected output sets.

## 3. Technical Exercise Index (Individual Files)

### Fundamentals (Variables, Loops, Conditionals)
* **`basics_and_variables.c`**: Learn primitive data types and basic variable initialization.
* **`input_and_arithmetic.c`**: Practice user input parsing and fundamental arithmetic operations.
* **`functions_and_switch.c`**: Understand function creation and `switch-case` control flow mechanisms.
* **`loop_patterns_modulo.c`**: Explore iterative constructs and modulo arithmetic.
* **`nested_conditionals.c`**: Implement complex decision-making trees using nested `if-else` blocks.
* **`while_loop_counters.c`**: Manage state and counters within `while` loop structures.
* **`sentinel_loop_logic.c`**: Utilize sentinel values to manage dynamic loop termination.
* **`input_output_streams.java`**: Handle basic console and file input/output streams in Java.

### Data Structures (Tries, BSTs, Linked Lists)
* **`structs.c`**: Define and instantiate custom composite data types.
* **`structs_and_arrays.c`**: Combine structures and arrays to manage complex datasets.
* **`2d_array.c`**: Allocate, manipulate, and traverse two-dimensional array structures.
* **`list_implementation.c`**: Build and manage dynamic singly or doubly linked lists.
* **`queue_implementation.c`**: Implement a First-In-First-Out (FIFO) queue data structure in C.
* **`binary_search_tree.c`**: Implement insertion, deletion, and ordered traversal in a BST.
* **`Tries.c`**: Construct a prefix tree for highly efficient string searching and retrieval.

### Advanced Algorithms (Greedy, Backtracking, Dynamic Programming)
* **`common_search_sort_functions.c`**: Implement foundational searching (e.g., binary search) and sorting (e.g., quicksort/mergesort) algorithms.
* **`flood_fill.c`**: Apply the flood fill algorithm for multi-directional region traversal.
* **`shortest_possible_string.c`**: Solve string reduction and optimization challenges.
* **`substring_extraction.c`**: Extract and manipulate string subsets efficiently.
* **`backtrack.java`**: Utilize recursive backtracking to traverse combinatorial search spaces.
* **`greedy_algorithms.java`**: Apply greedy choice properties for local optimization problems.
* **`dynamic_programming.java` / `dynamic_programming_2.java`**: Solve complex problems by breaking them down into simpler, overlapping subproblems.
* **`kruskals_algorithm.java`**: Compute the minimum spanning tree of a graph using Kruskal's greedy approach.
* **`word_frequency_string.java`**: Parse strings to compute occurrence frequencies of individual words.

### Systems Programming (File Systems, Threads, Resource Allocation)
* **`osystems_file.c`**: Interact with low-level operating system file management APIs.
* **`file_system_project.c`**: Simulate core file system operations and directory structures.
* **`joint_dynamic_memory.c`**: Master complex manual dynamic memory allocation (`malloc`, `free`) and pointer arithmetic.
* **`resource_allocation.c` / `sorted_array_resource_allocation.c`**: Implement strategies for managing and allocating constrained system resources.
* **`alu_insfetch.c`**: Simulate Arithmetic Logic Unit operations and instruction fetch sequences.
* **`djauto.c`**: Automate specific system-level tasks and processes.

### Miscellaneous Applications
* **`battle_ships_terminal_game.c`**: Apply 2D arrays and game logic to build an interactive terminal game.
* **`menu_functions.c`**: Create interactive, terminal-based user selection menus.
* **`math_library_logic.c`**: Utilize standard mathematical libraries for advanced computations.
* **`strings.c`**: Perform advanced manual string manipulations in C.
* **`vase_project.c`**: A specialized capstone project applying core C programming concepts.
* **`reciperion.c` / `reciperion.h`**: Demonstrate modular C programming using header files and separated implementations.
* **`review.c`**: Synthesize and review multiple core C programming concepts in a single execution flow.

## 4. Compilation Guide

### Single-File Execution
* **C (`.c` files):**
  Use GCC or Clang to compile into an executable:
  ```bash
  clang filename.c -o output_name
  ./output_name
  ```
* **Java (`.java` files):**
  Use the Java compiler followed by the Java Runtime Environment:
  ```bash
  javac filename.java
  java filename
  ```

### Multi-File & Managed Projects
* **Makefiles (`lang_c/custom_terminal`):**
  Navigate to the specific directory and use `make` to execute the build instructions defined in the `Makefile`:
  ```bash
  cd lang_c/custom_terminal
  make
  ./mysh
  ```
* **Maven Projects (`lang_java/java_spring_api`, `lang_java/junit_testing`):**
  Navigate to the project root containing the `pom.xml` and use the Maven wrapper (or system `mvn`):
  ```bash
  cd lang_java/java_spring_api
  ./mvnw spring-boot:run
  ```
  *(For general compilation and testing: `./mvnw clean install`)*
