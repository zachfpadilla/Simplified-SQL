# Simplified SQL
### - Data Structures Final Project -
This was my Data Structures final project for the Spring of 2023. The goal was to create a simplified version of SQL (a language for database querying) capable of handling basic commands and table/record management. This readme contains a summary of the program's features followed by a general overview of the components involved.


# Basic Definitions
### Record
A record is used to represent a singular table entry. It's composed of one piece of data for each field a table has. If a table has the fields "First Name", "Last Name", and "Age", then an example of a record that might be in that table is `Zachary Padilla 20`.

### Table
A table is a list of records, with each record being a row of the table. The table columns in turn represent fields, which define the data that each record in the table contains. An example of a table is as follows:
<pre>
Fields:   <ins>Full Name       | Age | Favorite Color</ins>
Records:  Zachary Padilla   20    Green
          Jeff Bezos        61    Red
          Bill Gates        69    N/A
</pre>

### View
A view is a table created to show the user the results of a command that they ran on an existing table. For example if the table above was named "people", then the command `select "Favorite Color" from people where Age > 20` will result in the following view:
<pre>
Fields:   <ins>Age</ins>
Records:  Red
          N/A
          
</pre>

## Features
- I/O via console
- Ability to create & insert data into tables
- Ability to select data from tables that matches given conditions
- Created tables can be accessed across sessions
- Existing tables can be overwritten and/or removed from the list of remembered files


# Example Interactions
An example of 2 very basic interactions with the program; showcases the following features:
- Handling invalid command syntax
- Creating & dropping tables
- Selecting from tables from previous sessions
- Attempting to insert into a table with an incorrect # of fields
- Inserting into tables with varied inputs e.g. John Doe (2 tokens: "John" and "Doe") vs. "John Doe" (1 token: "John Doe")
- Selecting specific fields from tables with basic conditions
- Exiting the program <br><br>
![demonstration](https://user-images.githubusercontent.com/73139549/235829252-822cb46e-8053-4198-bc0d-6c6ca5b8dea8.gif)
![ezgif-3-8aaa62578d](https://github.com/RZ187/SQL-Final-README.md/assets/73139549/994f0837-d54b-4f86-9f0c-298a87d6ed44)

## Input
### Console Command Format
<pre>
&ltCREATE | MAKE&gt : {  &ltcreate | make&gt table &ltTABLE_NAME&gt fields &ltFIELD_NAME&gt [, &ltFIELD_NAME&gt...]  }
&ltINSERT&gt : { insert &ltINTO&gt &ltTABLE_NAME&gt values &ltVALUE&gt [, &ltVALUE&gt...]      }
&ltSELECT&gt : {  select &lt* | FIELD_NAME&gt [, ,FIELD_NAME&gt...]
					from &ltTABLE_NAME&gt
					where &ltFIELD_NAME&gt &ltRELATIONAL_OPERATOR&gt &ltVALUE&gt
						[&ltLOGICAL_OPERATOR&gt
							&ltFIELD_NAME&gt &ltRELATIONAL_OPERATOR&gt &ltVALUE&gt...]
			}

&ltVALUE&gt  : A string of alphanumeric characters, or a string of alphanumeric
 			characters and spaces enclosed by double quotation marks:
 			"Jean Luise", Finch, 1923
&ltRELATIONAL OPERATOR&gt : [ = | &gt | &lt | &gt | &lt= ]
&ltLOGICAL OPERATOR&gt    : [and | or]
</pre>

### Examples
Table Creation:
<pre>
> make table students fields fname, lname, age
</pre>
Selection (quotes allow for values with mixed spaces, symbols, letters & numbers):
<pre>
> select * from students where fname = Zachary and (lname > Lee or age <= 25)

> select age, lname from students where lname = "Frank Padilla"
</pre>
Insertion:
<pre>
> insert into students values Bjarne, Stroustrup, 72
</pre>
Table Dropping:
<pre>
> drop table students
</pre>
Listing Managed Tables:
<pre>
> list
</pre>
Exiting the Program:
<pre>
> exit
</pre>
or
<pre>
> quit
</pre>
Prompting Help:
<pre>
> help
</pre>
Reading From a File "_!select.txt" (Executes all contained commands; lines prepended with "//" are simply written back to the console):
<pre>
> batch "_!select.txt"
</pre>



## SQL Output
### Console Messages
After creating a table named "students":
<pre>
SQL::run: table "students" created successfully.
</pre>
After selecting a table:
<pre>
SQL: DONE.
</pre>
After inserting values into a table named "students":
<pre>
SQL::run: successfully inserted into "students".
</pre>
After attempting to enter an incorrect number of values into "students":
<pre>
SQL::error: incorrect number of values (expected 3 but received 0)!
</pre>
After dropping a table named "students":
<pre>
SQL::run: table dropped.
</pre>
After attemping to drop "students" again:
<pre>
SQL::error: table students does not exist!
</pre>
Upon compilation/requesting list of managed tables ("employee" and "student" in this case):
<pre>
------ SQL Tables I Manage: --------
employee
student
---------------------------
</pre>
Upon exiting the program:
<pre>
SQL::run: ending program...
</pre>
Prompting help:
<pre>
------- available commands -------
"create" | "make": creates a new table with the specified field(s).                                  
syntax: { &ltcreate | make> &lttable> &ltTABLE_NAME> &ltfields> &ltFIELD_NAME> [, &ltFIELD_NAME>...] }           
                                                                                                     
"insert": inserts a record with the specified values into the selected table.                        
syntax: { &ltinsert> &ltinto> &ltTABLE_NAME> &ltvalues> &ltvalue> [, &ltVALUE>...] }                             

"select": prints a copy of the selected table with the specified field(s) and parameter(s).
syntax: { &ltselect> &lt* | FIELD_NAME> [, FIELD_NAME>...] &ltfrom> &ltTABLE_NAME> &ltwhere> [&ltCONDITION>...] }

"list": lists all tables managed by the program.
syntax: { &ltlist> }

"exit" | "quit": exits the program.
syntax: { &ltexit | quit> }

"help": reprints this menu.
syntax: { &lthelp> }
</pre>

### Examples
Example of a selected table:
<pre>
Table name: _select_table_0, records: 5
              record                last               first                 dep

                   0             Johnson               Jimmy           Chemistry
                   1                Yang                  Bo                  CS
                   2             Jackson               Billy                Math
                   3             Johnson               Billy             Phys Ed
                   4            Van Gogh             Jim Bob             Phys Ed
</pre>
Example of an empty table
<pre>
Table name: employee, records: 0
              record                last               first                 dep
              
</pre>

### Error Handling
- Basic user errors are accounted for:
  - Incorrect command syntax (not including conditions)
  - Dropping nonexistent tables (more to remind users of handled tables during runtime)
  - Attempts at inserting incorrect numbers of values into tables
- Some cases that are *not* handled:
  - Opening nonexistent tables (can also be considered a feature as it implicitly creates attempted tables)
  - Creating tables/fields with empty strings
  - Creating a table with duplicate fields
  - Checking for validity of conditional statements


## Class Overview
### Class Diagram
The following is a class diagram of how each major component in the program interacts with the others.
![Simplified SQL - Class Diagram](https://github.com/user-attachments/assets/78483255-4348-4621-a99a-17b5330153ac)


### Token
<pre>
Input:  select * from employee where Name > J
Tokens: | select |  | * |     | from |  | employee |  | where |  | Name |    | > |      | J |
	    ^         ^          ^           ^            ^         ^          ^          ^
	  string   string   relational    string       string    string   relational   string

</pre>
Tokens are the result of user input being split into its constituent pieces. There are three main types of tokens: **relational** tokens, **logical** tokens, and **string** tokens. String tokens are used to define what the arguments of the input are (the fields/values & command type), while relational & logical tokens are used for the filtering needed to get the final result set.

### Tokenizer
The Tokenizer is used to divide a given string into tokens of the appropriate types. Due to the potential complexity of user commands, a state machine is used to iterate through the strings it receives character by character. Once a singular token is completed, or the end of the string is reached, the tokenizer returns it (or reports the lack thereof).

### Shunting Yard
The shunting yard algorithm is a way of converting a logical expression in infix notation into postfix notation. Once this is achieved, the expression can be evaluated simply by calculating it in order from left to right. The algorithm works by iterating through an infix expression and putting operators into a stack & everything else into a queue, pushing/popping the former once done (or in the case of parenthesis) Further reading can be found [here](https://brilliant.org/wiki/shunting-yard-algorithm/).

### File Record
File records are simply used to write/read records to/from files, with each file containing a table's worth of records. Like tokens through the Tokenizer, file records are read in one per invocation.

### Parser
The Parser recieves commands from SQL, passes them to the Tokenizer, then uses those tokens to build a multimap with the potential indexes (depending on which are present in each command) being: "command", "fields", "table_name", "where", "condition", "values", and "file_name". An adjacency matrix is used in order to tell which token means what, and therefore where in the multimap to place it.

### Table
Tables are the structures in which records are stored. The responsibilities of this class are to read/write records between tables and files, to add records to existing tables, to keep track of all tables, and to appropriately create/return new tables (views) based on specified operations (logical or relational).

### SQL
The SQL class is responsible for receiving user input and for the tables they create. When the user enters a command, it gets passed to the Parser to generate the multimap of instructions to follow. It will then execute the appropriate command with the appropriate arguments, such as dropping a table or applying a filter to one. It will then print a confirmation (or an error) to the console, and if applicable, will display some sort of result.


### Design Philosophy
- Maps are used in many cases where direct string comparisons would likely be more efficient; this is done for readability
- Certain features (notably Table's RPN & SQL's command processor) have tasks delegated between multiple other functions
  - Especially in the case of the former, this results in cleaner code at the cost of redundant parameters/operations
<br><br>

## Reflections
- My biggest takeaway from this project was to ensure that all components of large projects in the future function with at least 99% certainty, as there were some issues that arose from bugs in ground-level functions.
  - Related to this point is to not take "shortcuts" (i.e. hardcoding) when first implementing said components, as I had to go back and change them to account for things that I didn't originally think they'd have to do.
