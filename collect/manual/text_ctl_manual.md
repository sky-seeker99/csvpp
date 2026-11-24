# Text File Processing Program

This program applies user-defined rules to process text files.

## 1. About the Program

This program processes text files according to user-defined rules. Because the rules use a state machine, they can perform complex replacements, insertions, deletions, and other operations. Wildcards can also be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
text_ctl rule_file file_to_convert [-r] [-l log_file] [-buff buffer_size]
```

Specify the full path to the file to convert. The rule file must be in CSV format.

- `-r`: Searches without modifying the file.
- `-l`: Specifies a log file.
- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.

### Examples

```text
text_ctl rule.csv c:\csv\*.cpp
text_ctl rule.csv c:\csv\*.cpp -r
text_ctl rule.csv c:\csv\*.cpp -r -l log.txt
```

## 3. Examples

Suppose you want to process the contents between `module` and `endmodule` in a file named `aaa.v`.

### `aaa.v`

```verilog
module xxx
...
endmodule

module yyy
...
endmodule

module zzz
...
endmodule
```

Create a rule file as follows:

```text
#st,IDLE
#if,module
  #noif,endmodule
    #printf,Step1
    #go,SET_A
  #endif
#endif

#st,SET_A
#if,endmodule
  #go,IDLE
#else
#endif
```

`#st` defines a state in the state machine. The example above has two states: `IDLE` and `SET_A`.

In the `IDLE` state, if a line contains `module` but does not contain `endmodule`, the program executes `#printf` and `#go`. `#printf` displays the line, and `#go` changes the state to `SET_A`.

In the `SET_A` state, when a line containing `endmodule` is found, the state changes back to `IDLE`.

You can extend the example with specific processing rules as follows:

```text
#st,IDLE
#if,module
  #noif,endmodule
    #printf,Step1
    #go,SET_A
  #endif
#endif

#st,SET_A
#if,endmodule
  #go,IDLE
#else
  #if,always
    #printf,always
    #ins,"// sync_reset ""reset"""
  #endif
  #if,case
    #printf,register
    #chg,#@@# // parallel_case
  #endif
  #if,# register define ############################
    #printf,delete
    #del
  #endif
  #if,~reset_n
    #printf,replace
    #replace,~reset_n,~rst_n
  #endif
#endif
```

With these rules:

- In the `SET_A` state, when a line contains `always`, the line `// sync_reset "reset"` is inserted.
- When a line contains `case`, `// parallel_case` is appended to that line. `#@@#` is replaced with the matched text.
- A line containing `# register define ############################` is deleted.
- When `~reset_n` is found, it is replaced with `~rst_n`.

## 4. Command Reference

### 1. Define State Machine States

Defines state names for the state machine. Execution starts with the first state defined.

**Syntax**

```text
#st,state_name
```

**Example**

```text
#st,IDLE
```

### 2. `#if`, `#noif`, `#else`, and `#endif` Statements

`#if` checks whether the specified string exists in the line. `#noif` checks that the specified string does not exist. `#else` specifies the inverse condition of the corresponding `#if` or `#noif`. `#endif` marks the end of the conditional block.

Specify `aA_same` to search without distinguishing uppercase and lowercase letters.

**Syntax**

```text
#if,comparison_string,[aA_same]
#noif,comparison_string,[aA_same]
#else
#endif
```

**Examples**

```text
#if,module
  #printf,msg1
#endif
```

```text
#noif,endmodule
  #printf,msg2
#else
  #printf,msg3
#endif
```

```text
#if,module,aA_same
  #printf,msg1
#endif
```

### 3. Comments

A line beginning with `//` is treated as a comment.

**Syntax**

```text
//,comment_text
```

**Example**

```text
//,#if,module
```

### 4. State Transitions

`#go` transitions to the specified state.

`#act` activates the specified state without transitioning away from the current state. This allows states to run in parallel.

`#stop` stops the specified state if it is active. If `#act` or `#go` is also specified, `#act` and `#go` take precedence.

**Syntax**

```text
#go,target_state
#act,target_state
#stop,target_state
```

**Example**

```text
#st,IDLE
#if,module
  #noif,endmodule
    #go,SET_A
    #act,SET_B
  #endif
#endif

#st,SET_A
#if,endmodule
  #stop,SET_B
  #go,IDLE
#else
  #if,always
    #printf,always
  #endif
#endif

#st,SET_B
#if,sample1_fp
  #printf,printf
#endif
```

### 5. Insert Lines

`#ins` and `#ins_after` insert the specified text as a line. `#ins` inserts it before a line containing the search string. `#ins_after` inserts it after that line.

**Syntax**

```text
#ins,text_to_insert
#ins_after,text_to_insert
```

**Example**

```text
#ins,aaaaaaa
#ins_after,aaaaaaa
```

### 6. Delete a Line

`#del` deletes the current line.

**Syntax**

```text
#del
```

**Example**

```text
#del
```

### 6. Modify a Line

`#chg` modifies a line. `#@@#` is replaced with the text that was read.

**Syntax**

```text
#chg,modification
```

**Example**

```text
#chg,#@@# // aaa
```

For example, if the input text is `case(xxx)`, it becomes `case(xxx) // aaa`.

### 7. Replace a String

`#replace` replaces the specified string.

**Syntax**

```text
#replace,text_to_find,replacement_text,[aA_same]
```

Specify `aA_same` to replace text without distinguishing uppercase and lowercase letters.

**Examples**

```text
#replace,reset_n,rst_n
#replace,reset_n,rst_n,aA_same
```

### 8. Debugging

`#debug` displays information about how the CSV file was read.

**Syntax**

```text
#debug
```

**Example**

```text
#debug
```

### 9. Initial Active State Settings

`#st_init` specifies the states to activate when the state machine starts. If omitted, the first state defined is activated.

**Syntax**

```text
#st_init,state1,state2,...,stateN
```

**Example**

```text
#st_init,idle,idle_2
```

### 10. Collect Log Context

`#log` collects lines from `n` lines before the specified point through `m` lines after it. The output format follows `#line_chg`.

**Syntax**

```text
#log,number_of_preceding_lines,number_of_following_lines
```

**Example**

```text
#log,3,4
```

### 11. Rewrite a Specified Line

`#line_chg` rewrites the specified line.

**Syntax**

```text
#line_chg,line_number,content
```

**Example**

```text
#line_chg,100,aaaaadd
```

If the content contains a comma, enclose it in double quotation marks. To include a double quotation mark in the content, enter it twice.

### 12. Trace Commands

`#itrace` traces command execution.

**Syntax**

```text
#itrace
```

**Example**

```text
#itrace
```

### 13. Trace the Buffer

`#trace` traces the buffer.

**Syntax**

```text
#trace
```

**Example**

```text
#trace
```

### 14. Delete a Line Break

`#retdel` deletes a line break and joins the current line with the next line.

**Syntax**

```text
#retdel
```

**Example**

```text
#retdel
```

### 15. Insert a File into the Text

`#ins_file` and `#ins_file_after` insert the contents of a text file as lines. `#ins_file` inserts the contents before a line containing the search string. `#ins_file_after` inserts them after that line.

**Syntax**

```text
#ins_file,text_file_name
#ins_file_after,text_file_name
```

**Example**

```text
#ins_file,ccc.txt
#ins_file_after,ccc.txt
```

## 5. Version History

- **Ver 0.90** Preliminary release.
- **Ver 0.91** Added the `-r` option.
- **Ver 0.92** Fixed bugs. Made search and rewriting stop when all states have finished. Added support for specifying multiple initial states and added logging.
- **Ver 0.93** Bug fixes.
- **Ver 0.94** Bug fixes and added debugging features.
- **Ver 0.95** Added `#retdel`.
- **Ver 0.97** Added `#ins_after`.
- **Ver 0.98** Improved performance and fixed a bug that added unnecessary line ending codes.
- **Ver 1.00** Changed execution to run as a background job.
- **Ver 1.01** Fixed a bug that caused an error when a command was NULL.
- **Ver 1.02** Added support for files larger than 4 GB and added the `-buff` option.
- **Ver 1.03** Fixed CSV reading when a cell contains a line break.
- **Ver 1.04** Added the `aA_same` option.
- **Ver 1.04a** Fixed a bug in the `aA_same` option.
- **Ver 1.05** Added `#ins_file` and `#ins_file_after`.
