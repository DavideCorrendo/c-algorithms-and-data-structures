> **Note:** This is a university project. This README was provided by the professor for the Algorithms and Data Structures Lab course and has simply been translated into English; the content and requirements are unchanged from the original.

# Lab for the Algorithms and Data Structures course: exam rules, general guidelines and suggestions, exercise assignments

# Exam Rules


## Students from years prior to 2024/2025

Students enrolled in the second year in an academic year prior to 2024/2025 **may** complete the lab according to:
- these current specifications

or, alternatively and **no later than the September 2025 exam session**,

- the 2023/2024 academic year specifications:
> [https://gitlab2.educ.di.unito.it/audrito/laboratorio-algoritmi-2023-2024](https://gitlab2.educ.di.unito.it/audrito/laboratorio-algoritmi-2023-2024)

Students who have not yet started exercises 3 or 4 of the previous specifications are nonetheless advised to follow the new specifications.

## Students with Algorithms not worth 9 CFU

Students who have the Algorithms course in their study plan with a number of CFU (credits) **different from 9** are asked to contact the instructor as soon as possible, in order to agree on an exam program proportionate to the credits.

## Lab groups and shifts

The lab project can be completed individually or in a group (at most 3 people). **Members of the same group must all belong to the same lab shift**.

A student assigned to Shift X can move to Shift Y, **provided they find a colleague from Shift Y who agrees to move to Shift X**. The transfer request must be sent via email to the lab instructors by the person who wants to make the swap, cc'ing the person willing to make the reverse swap and both instructors involved. The swap is considered effective only after explicit authorization (via email) from the instructors.
Only one shift change is allowed per academic year.
Instructors reserve the right to reject transfer requests that are not submitted with sufficient advance notice (min. 1 month) before the date of the written exam the student intends to take.

## Overall exam

As specified in the official course description (https://laurea.informatica.unito.it/do/corsi.pl/Show?_id=iw3r):

The Algorithms and Data Structures exam consists of a written test, administered via the Esami platform, and an oral discussion of the lab project. Passing the written test grants access to the oral exams of the session in which the written test was passed. If this second test is not passed within the deadlines of the session, the written test must be repeated. The grade will be the weighted average of the grades obtained in the two written and oral tests [based on the credits associated with the theory (6 CFU) and lab (3 CFU) parts, in the average the written test will weigh 6 and the oral 3], evaluated out of 30+1, with a passing grade required in both tests.

## Project submission and oral discussion

The lab project must be submitted via Git (see below) no later than the date of the written exam the student intends to take. It is forbidden to take the written exam if the lab project has not been submitted.

The oral exam can only be taken after passing the written exam.

If the written exam is passed, the oral exam (lab discussion) must be taken **in the same session as the passed written exam** (recall that the sessions are January-February 2025, June-July 2025, September 2025).

Note that for sessions with two exam dates, there will be two opportunities for the lab discussion (first or second date of the session); for sessions with only one exam date, the discussion must necessarily be held on that date.

Example (case of a session with 2 exam dates):

- student X takes the written exam on the first date of a session with 2 dates;
- student X must make sure that the project on GitLab, as of the date of the written exam they intend to take (in this example, that of the first date of the session), is updated to the version they want to present to the lab instructor;
- if student X passes the written exam on the first date of the session, they must (under penalty of losing the grade obtained in the written exam):
-- enroll in one of the two oral exam dates of the same session
-- book a slot on i-learn among those made available by the instructor of their shift
-- take the oral exam in the booked time slot.

Different students belonging to the same lab group can take the **written** exam on the same date or on different dates. If different students belonging to the same group pass the written exam on the same date, they **must** take the **oral** exam on the same oral exam date. If different students belonging to the same group pass the written exam on different dates, they **may** take the **oral** exam on different dates.

For example, consider a lab group made up of students X, Y and Z, and suppose that only X and Y take the written exam on the first date of a session with two dates, with X passing and Y failing. The following conditions must be respected:

- as of the date of the written exam of the first date of the session, the group's lab project must be updated to the version to be presented;
- only student X must take the oral exam in the same session in which they passed the written exam, proceeding as indicated in the example above, while Y and Z will take the discussion once they have passed the written exam.
- Suppose Y and Z pass the written exam on the date of a session with only one date: they will have to take the oral exam on that same date.
- Students Y and Z will normally have to discuss the same version of the lab project that student X discussed; i.e., any changes to the lab made after X's discussion must be minor, duly documented (i.e., the change log must appear on GitLab) and justified.

**Validity of the lab project**: the specifications for the lab project described in this document will remain valid until the last exam date of the current academic year **(i.e., that of September 2025)** and no later! Exam dates of sessions after that one must be taken based on the specifications that will be described in the next edition of the algorithms lab.

# General guidelines and suggestions

## Use of Git

While writing code, it is required to use the Git versioning system appropriately. This requirement implies the following:

- the lab project must be initialized by "cloning" the lab repository as described in the Git.md file;
- as is standard practice in modern development environments, frequent commits are required, with a meaningful name. Ideally, one commit per completed block of work (e.g., creation and testing of a new function, bug fix, creation of a new interface, ...);
- each group member should commit the changes for which they were the main developer;
- at the end of the work, the entire repository must be submitted (giving access to the instructor).

The Git.md file contains an example of how to use Git for developing the exercises proposed for this lab.

---

**Important note**: Only source code should be uploaded to git; in particular, no data file should ever be committed!

---

Please note that the evaluation of the lab project will also consider each group member's appropriate use of git.

## Language to develop the lab in

The entire lab implementation must be done in the C language.

As indicated below, some exercises ask you to implement **generic code**. By "generic code" we mean code that must be able to run with data types not known at compile time.

**Suggestion for implementing generic code in C**: In the case of C, it is necessary to understand how to best approximate the idea of generic code using what the language allows. A common approach is to have the functions and procedures in the code take `void` pointers as input and use some user-provided function to access the necessary components (use of function pointers).

## Use of external and/or native libraries of the chosen language

The use of native data structures of the chosen language or those offered by external libraries is forbidden when their implementation is required by one of the proposed exercises.

It is, however, possible to use native data structures of the language or those offered by external libraries, if their implementation is not required by one of the proposed exercises.

**Example:** using a C library that implements dynamic arrays is allowed, only if no exercise asks for the implementation of a dynamic array.

## Report on the exercises

The report, for those exercises that require it, must be inserted into the project's README.md file, thus becoming an integral part of the documentation.

## Unit Testing

As explicitly indicated in the exercise texts, the lab project also includes the definition of appropriate unit test suites.

Note, however, that the focus of the lab is the implementation of data structures and algorithms. Regarding unit tests, it will therefore be sufficient for students to demonstrate that they have grasped the point and are able to build a test suite sufficient to cover the most common cases and edge cases.

## Implementation quality

Part of the mandate of the exercises is producing good-quality code.

By "good quality" we mean code that is well organized, well modularized, well commented, and well tested.

**Some suggestions:**

- **Important**: The exercises require (among other things) developing generic code. When developing this part, you must assume you are developing a generic library intended as the foundation for future programs. It is therefore not acceptable to make simplifying assumptions; in general, the implementation of the generic library must remain separate and must not be influenced in any way by the uses of it that may be required in the exercises (for example, if an exercise requires the implementation of the graph data structure and that same exercise or another one requires the implementation, based on that data structure, of an algorithm for computing the connected components of a graph, the implementation of the data structure should be separate from the algorithm for computing connected components and should *not* contain elements - variables, procedures, functions, type definitions, etc. - that may be useful to that algorithm but are not essential to the data structure; similarly, if an exercise requires operating on graphs with string-type nodes, the implementation of the graph data structure should remain generic and should therefore not assume string as the only type for nodes).
- verify that the code is correctly divided into packages or modules;
- add a comment, before a definition, that explains how the defined object works, preferably in [doxygen](https://www.doxygen.nl) format. Avoid, when possible, commenting directly inside the code of the implemented functions/methods (if the code is well written, comments are generally not needed);
- the length of a method/function is generally a warning sign: if it grows too much, it is probably necessary to refactor the code by splitting the function into multiple parts. As a general rule, it is advisable to intervene when the function grows beyond 30 lines (including comments and blank lines);
- comments in Italian are acceptable, although comments in English are preferred;
- all names (e.g., variable names, method names, class names, etc.) *must* be meaningful and in English;
- the code must be correctly indented; set indentation to 2 or 4 characters and set the editor so that it inserts "soft tabs" (i.e., it must insert the correct number of spaces instead of a tab character);
- for naming identifiers, follow the conventions in use for the C language:
  - macros and constants are all uppercase and in snake case format (e.g. THE\_MACRO, THE\_CONSTANT); type names (e.g. struct, typedefs, enums, ...) start with an uppercase letter and continue in camel case (e.g., TheType, TheStruct); function names start with a lowercase letter and continue in snake case (e.g., the\_function());
- files must be saved in UTF-8 format.

# Exercise assignments

During the exam discussion, the instructor may, at their discretion, ask you to run the implemented algorithms on data provided by the instructor. If this data is stored in files, they will be CSVs with the same structure as the datasets provided and described in the exercise text. The code developed must allow quick and simple adaptation to the provided inputs: for example, **a good implementation will allow you to input the name of the file on which to run the test**, while a worse one will require modifying the source code and recompiling just to change the name of the file containing the dataset.

For some parts of the exercises, a platform for automated correctness evaluation of the produced code will also be provided during the course.


## Exercise 1 - Merge Sort and Quick Sort

### Text

Implement a library offering the *Merge Sort* and *Quick Sort* sorting algorithms on generic data, implementing the following function prototypes:

```
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
```

- `base` is a pointer to the first element of the array to sort;
- `nitems` is the number of elements in the array to sort;
- `size` is the size in bytes of each element of the array;
- `compar` is the criterion by which to sort the data (given two **pointers to elements** of the array, it returns a number greater than, equal to, or less than zero if the first argument is respectively greater than, equal to, or less than the second).

It is also possible to implement, as an alternative, the following prototypes, which sort data provided they are organized in an array of pointers:

```
void merge_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));
void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));
```

- `base` is a pointer to the first element of the array of pointers to sort based on the referenced values;
- `nitems` is the number of elements in the array of pointers to sort;
- `compar` is the criterion by which to sort the data (given two **elements** of the array of pointers).

Since the first version is also able to sort arrays of pointers (by passing an appropriate comparator, whose arguments will be pointers to pointers to the data), it is not necessary to implement this second version if you have already implemented the first. In any case, it is also not necessary to implement the first if you have already implemented the second.

### Unit Testing

Implement the unit tests for the library according to the guidelines suggested in the [Unit Testing](UnitTesting.md) document.

### Use of the implemented sorting library

The `records.csv` file, which you can find (compressed) at:

> [https://datacloud.di.unito.it/index.php/s/9sQmzB9TdDHezX7](https://datacloud.di.unito.it/index.php/s/9sQmzB9TdDHezX7)

contains 20 million records to sort.
Each record is described on one line and contains the following fields:

- `id`: (integer type) unique record identifier;
- `field1`: (string type) contains words extracted from the Divine Comedy,
  you can assume the values do not contain spaces or commas;
- `field2`: (integer type);
- `field3`: (floating point type).

The format is a standard CSV: fields are separated by commas; records are
separated by `\n`.

Using the algorithm implemented previously, build the following function to sort *records* contained in the `records.csv` file in non-decreasing order according to the values contained in the three "field" fields.

```
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);
```

- `infile` is the file containing the records to sort;
- `outfile` is the file in which to save the sorted records (which must be different from `infile`);
- `field` can be 1, 2 or 3 and indicates which of the three fields must be used to sort the records.
- `algo` can be 1 or 2 and indicates which sorting algorithm must be used (MergeSort or QuickSort) to sort the records.

Measure the response times for the two algorithms, for each of the three fields that can be used as the sort key, and produce a brief report presenting the results obtained together with a commentary on them. The commentary must be based on numerical statistics on the measured execution times. If the sort takes more than 10 minutes, you may interrupt execution and report a failure of the operation. Are the results what you expected? If so, why? If not, formulate hypotheses about why the algorithms are not behaving as expected, verify them, and report what you discovered in the report. Do the results depend on the field used as the sort key?

**Remember that the `records.csv` file (and compiled files) MUST NOT BE COMMITTED TO GIT!**

### Submission conditions:

- Create a subfolder called `ex1` inside the repository.
- The submission must necessarily contain a `Makefile`. This file, with the `make all` command, must produce inside `ex1/bin` two executable files called `main_ex1` and `test_ex1`. If you used external libraries (such as Unity), include them too to allow correct compilation.
- The `test_ex1` executable must not require any parameters and must run all the automated unit tests produced.
- The `main_ex1` executable must receive as parameters the path to the CSV file containing the records to sort, the path to the file in which to save the sorted records, and the value of the `field` to use for sorting. For example:

```
$ ./main_ex1 /tmp/data/records.csv /tmp/data/sorted.csv 1
```


## Exercise 2 - Edit distance

### Text

Consider the problem of determining the minimum edit distance between two strings (_edit distance_): given two strings $s_1$ and $s_2$, not necessarily of the same length, determine the minimum number of operations needed to transform string $s_2$ into $s_1$. Assume that only two operations are available: **deletion** and **insertion**. For example:

- "casa" and "cassa" have edit distance 1 (1 deletion);
- "casa" and "cara" have edit distance 2 (1 deletion + 1 insertion);
- "vinaio" and "vino" have edit distance = 2 (2 insertions);
- "tassa" and "passato" have edit distance 4 (3 deletions + 1 insertion);
- "pioppo" and "pioppo" have edit distance 0.

First, implement a recursive function to compute the edit distance, implementing the following function prototype:

```
int edit_distance(const char *s1, const char* s2);
```

- `s1` is the string you want to obtain $s_1$;
- `s2` is the starting string $s_2$.

The structure of the function must reflect the following definition (we denote with $|s|$ the length of $s$ and with $\mathrm{rest}(s)$ the substring of $s$ obtained by ignoring the first character of $s$):

- if $|s_1|$ = 0, then $\mathrm{edit\_distance}(s_1,s_2) = |s_2|$;
- if $|s_2|$ = 0, then $\mathrm{edit\_distance}(s_1,s_2) = |s_1|$;
- otherwise, let:
  - $d_{\mathrm{no-op}} = \mathrm{edit\_distance}(\mathrm{rest}(s1),\mathrm{rest}(s2))$   if $s1[0]=s2[0]$, $\infty$ otherwise
  - $d_{\mathrm{canc}} = 1 + \mathrm{edit\_distance}(s1,\mathrm{rest}(s2))$
  - $d_{\mathrm{ins}} = 1 + \mathrm{edit\_distance}(\mathrm{rest}(s1),s2)$

So we have that: $\mathrm{edit\_distance}(s_1,s_2) = \min\{d_{\mathrm{no-op}}, d_{\mathrm{canc}}, d_{\mathrm{ins}}\}$.

Next, also implement a version of the edit distance computation function that adopts a dynamic programming strategy. This version must also be recursive (in particular, it must be obtained through a minimal set of changes made to the implementation required in the previous point). The function must implement the following prototype:

```
int edit_distance_dyn(const char *s1, const char* s2);
```

*Note*: The definitions given above do not correspond to the usual way of defining edit distance. They are, however, the ones needed to solve the exercise and on which the produced code must be based.

### Unit Testing

Implement the unit tests for the algorithms according to the guidelines suggested in the [Unit Testing](UnitTesting.md) document.

### Use of the implemented functions

At:

> [https://datacloud.di.unito.it/index.php/s/9BKY7BXFCY4bMcB](https://datacloud.di.unito.it/index.php/s/9BKY7BXFCY4bMcB)

you can find a dictionary (`dictionary.txt`) and a file to correct (`correctme.txt`).

The dictionary contains a list of words. The words are written one after another, each on its own line.

The `correctme.txt` file contains a text to correct. Some words in this text are not in the dictionary.

Implement an application that uses the `edit_distance_dyn` function to determine, for each word `w` in `correctme.txt`, a short list of words in `dictionary.txt` with minimum edit distance from `w`. Experiment with the application and report the results of the experiments in a brief report.

**Remember** that the `dictionary.txt` and `correctme.txt` files must not be committed to git!

### Submission conditions:

- Create a subfolder called `ex2` inside the repository.
- The submission must necessarily contain a `Makefile`. This file, with the `make all` command, must produce inside `ex2/bin` two executable files called `main_ex2` and `test_ex2`. If you used external libraries (such as Unity), include them too to allow correct compilation.
- The `test_ex2` executable must not require any parameters and must run all the automated unit tests produced.
- The `main_ex2` executable must receive as parameters the path to the dictionary to use as reference and the file to correct. For example:

```
$ ./main_ex2 /tmp/data/dictionary.txt /tmp/data/correctme.txt
```

---

**Important note**: the text for exercises 3 and 4 **is not yet final and may change** in the coming days.

---

## Exercise 3 - Hash tables (with chaining)


### Text

Implement, with the support of a system based on a Large Language Model, such as, for example, ChatGPT (see below), a generic library that implements the *hash table (with chaining)* data structure able to hold a set of pairs {<key_1,value_1>,...,<key_n,value_n>}.

The hash table must accept keys and values of generic types (all keys have the same type, all values have the same type, but keys and values may have different types from each other).

The data structure must offer at least the following functionalities (derive the meaning of the various functions and procedures and their parameters from their prototypes and from what was studied in the theory part of the course):

```
HashTable* hash_table_create(int (*f1)(const void*,const void*), unsigned long (*f2)(const void*));
void hash_table_put(HashTable*, const void*, const void*);
void* hash_table_get(const HashTable*, const void*);
int hash_table_contains_key(const HashTable*, const void*);
void hash_table_remove(HashTable*, const void*);
int hash_table_size(const HashTable*);
void** hash_table_keyset(const HashTable*);
void hash_table_free(HashTable*);
```

### Unit Testing

Implement, with the support of a system based on a Large Language Model (LLM), such as, for example, ChatGPT (see below), the unit tests for the algorithms according to the guidelines suggested in the [Unit Testing](UnitTesting.md) document.

### Use of an LLM-based system:

For this exercise, you are required to use the support of a system based on a Large Language Model, such as, for example, ChatGPT, to implement what is requested.

The development process may turn out to be iterative, involving multiple interactions with the LLM system.

Document, in a report (README.md on git), this development process in its main aspects (initial prompt, output produced by the system, critical analysis of the output, prompt refinement, etc.) and report some general considerations on the entire process.


## Exercise 4 - Sparse Graphs and Breadth-First Search

### Required language: C

### Text

Implement a library that realizes the *Graph* data structure in a way that is optimal for sparse data
(**note**: the implementation choices you make must be justified in relation to the concepts presented
during the lectures).

It is required that the implementation make use of the Hash Table implemented in exercise 3.

The implementation must be generic both with respect to the type of the nodes and with respect to the labels
of the edges, implementing the functions reported in the following header file (with minimum complexity requirements; where _N_ may indicate the number of nodes or the number of edges, depending on context):

```
graph.h

typedef enum {false = 0, true = 1} Bool;

typedef struct graph *Graph;

typedef struct edge {
   void* source; //source node
   void* dest; //destination node
   void* label; //edge label
}Edge;

Graph graph_create(Bool labelled, Bool directed,
                     int (*compare)(const void*, const void*),
                     unsigned long (*hash)(const void*));

//creates an empty graph, labelled if labelled == true and directed if directed == true,
//functions f1 and f2 are needed to build the hash table that must be used by the library -- O(1)

Bool graph_is_directed(const Graph gr);                                                           // tells whether the graph is directed or not -- O(1)
Bool graph_is_labelled(const Graph gr);                                                           // tells whether the graph is labelled or not -- O(1)
Bool graph_add_node(Graph gr, const void* node);                                                  // adds a node -- O(1)
Bool graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);           // adds an edge given endpoints and label -- O(1) (*)
Bool graph_contains_node(const Graph gr, const void* node);                                       // checks if a node is in the graph -- O(1)
Bool graph_contains_edge(const Graph gr, const void* node1, const void* node2);                   // checks if an edge is in the graph -- O(1) (*)
Bool graph_remove_node(Graph gr, const void* node);                                               // removes a node from the graph -- O(N)
Bool graph_remove_edge(Graph gr, const void* node1, const void* node2);                           // removes an edge from the graph -- O(1) (*)
int graph_num_nodes(const Graph gr);                                                              // number of nodes -- O(1)
int graph_num_edges(const Graph gr);                                                              // number of edges -- O(N)
void** graph_get_nodes(const Graph gr);                                                           // retrieves the graph's nodes -- O(N)
Edge** graph_get_edges(const Graph gr);                                                           // retrieves the graph's edges -- O(N)
void** graph_get_neighbours(const Graph gr, const void* node);                                    // retrieves the nodes adjacent to a given node -- O(1) (*)
int graph_num_neighbours(const Graph gr, const void* node);                                       // retrieves the number of nodes adjacent to a given node -- O(1)
void* graph_get_label(const Graph gr, const void* node1, const void* node2);                      // retrieves the label of an edge -- O(1) (*)
void graph_free(Graph gr);
```

_(*)_ when the graph is genuinely sparse, assuming the operation is performed on a node whose adjacency list has O(1) length.

The `struct graph` structure must be decided taking into consideration the requirement to use the Hash Table from the previous exercise.


*Suggestion*: an undirected graph can be represented using a modified implementation for directed graphs,
to ensure that, for every edge *(a,b)* labelled *w* present in the graph, the edge *(b,a)* labelled *w* is also present in the graph.
Obviously, the graph must retain the information specifying whether it is a directed or undirected graph.
Similarly, an unlabelled graph can be represented using the implementation for labelled graphs modified to ensure
that labels are always `null` (whereas they must never be `null` for labelled graphs).

### Unit Testing

Implement the unit tests for the algorithms according to the guidelines suggested in the [Unit Testing](UnitTesting.md) document.

### Use of the library implementing the Graph data structure

Implement the breadth-first search algorithm according to the following function prototype:

```
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));
//start is the starting node from which to begin the visit, the function returns the array of nodes in visit order.
//optionally, the function returns null if the start node is not present in the graph gr.

```

The implementation of the breadth-first search algorithm must use the graph library just implemented.
The algorithm must then be used with the data contained in the `italian_dist_graph.csv` file, which you can retrieve at:

> [https://datacloud.di.unito.it/index.php/s/FqneW99EGWLSRpY](https://datacloud.di.unito.it/index.php/s/FqneW99EGWLSRpY)

This file contains distances in meters between various Italian locations and a fraction of the locations closest to them. The format is a standard CSV: fields are separated by commas; records are separated by the end-of-line character (`\n`).

Each record contains the following data:

- `place1`: (string type) name of the "source" location (the string may contain spaces but not commas);
- `place2`: (string type) name of the "destination" location (the string may contain spaces but not commas);
- `distance`: (float type) distance in meters between the two locations.

**Notes:**

- You can interpret the information in the file's rows as **undirected** edges (so you will likely want to insert into your graph both the outgoing and the return edge for each row read).
- The file was created from a not-very-accurate dataset. The reported data contains inaccuracies and imprecisions.

**Remember that the `italian_dist_graph.csv` file (and compiled files) MUST NOT BE COMMITTED TO GIT!**

### Submission conditions:

- Create a subfolder called `ex3-4` inside the repository, which will contain the files related to this exercise and the previous one.
- Also include in the submission a `Makefile` that, with the `make all` command, must produce inside `ex3-4/bin` two executable files called `main_ex3-4` and `test_ex3-4`. If you used external libraries (such as Unity), include them too to allow correct compilation.
- The `test_ex3-4` executable must not require any parameters and must run all the automated unit tests produced.
- The `main_ex3-4` executable must receive as parameters the path to the `italian_dist_graph.csv` file, the name of the starting city, and the name of an output file, and save to the latter the names of the locations visited during a breadth-first search of the graph, one name per line, starting from a specified starting node. File names must not be hardcoded, but must be passed as command-line arguments.

```
$ ./main_ex3-4 italian_dist_graph.csv torino output.txt
```

Briefly document, in a report (README.md on git), the implementation choices made and the results and execution times of the algorithm compared to what was expected.
