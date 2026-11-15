# Binary File Processing Program

## 1. About the Program

This program processes binary files according to user-defined rules.

The rules use a state machine, enabling complex operations such as replacing, inserting, and deleting data.

Wildcards can also be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
bin_ctl rule_file file_to_process [-r] [-buff buffer_size]
```

Specify the full path to the file to process.

The rule file must be in CSV format.

- `-r`: Searches the file without modifying it.
- `-buff`: Specifies the buffer size for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.

### Examples

```text
bin_ctl rule.csv c:\csv\*.cpp
```

```text
bin_ctl rule.csv c:\csv\*.cpp -r
```

## 3. Example

Suppose you want to modify the data immediately following the `A8 10` data that appears after an `FF FF` sequence in a file named `aaa.dat`.

### aaa.dat

```text
00 00 00 00 20 00 00 00 FF FF 00 00 FF FF 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
A8 10 00 00 20 00 00 00 FF FF 03 00 FF FF 01 00
00 00 00 00 10 10 11 04 00 00 00 00 00 00 00 00
```

Create the rule file as follows:

```text
#st,IDLE
  #srch,0xff,0xff
  #go,SET_A

#st,SET_A
  #srch,0xa8,0x10
  #set,addr,srch_offset+1
  #printf,addr=%I64x,addr
  #chg,addr,1,0x56
  #go,IDLE
```

`#st` defines a state in the state machine.

The example has two states: `IDLE` and `SET_A`.

In the `IDLE` state, the program searches for `FF FF`. When it finds the sequence, it executes `#go` to transition to the next state.

In the `SET_A` state, the program searches for `A8 10`. When found, it changes the following byte to `56` and displays its address.

The program then returns to the `IDLE` state.

## 4. Command Reference

### (1) Define State Machine States

Defines the state names used by the state machine. Execution starts with the first state defined.

The state machine searches for a binary pattern. When a match is found, it executes the commands associated with the state transition, starting at the matching location.

Define the search data with `#srch`.

The `srch_offset` variable contains the address where the pattern was found.

#### Syntax

```text
#st,state_name
#srch,data,data,data,...
```

#### Example

```text
#st,IDLE
#srch,0x10,0x20,0x30
```

### (2) `#if`, `#else`, and `#endif` Statements

`#if` evaluates a conditional expression.

`#else` specifies the opposite condition of the corresponding `#if` statement.

`#endif` marks the end of the `#if` statement.

#### Syntax

```text
#if,condition
#else
#endif
```

#### Examples

```text
#if,a==0x90
  #printf,msg1
#endif
```

```text
#if,b==c+1
  #printf,msg2
#else
  #printf,msg3
#endif
```

### (3) Assignment Expressions

Defines variables and evaluates expressions.

#### Syntax

```text
#set,variable_name,expression
```

#### Example

```text
#set,a,b+10
```

### (4) State Transitions

`#go` transitions to another state.

`#act` activates the specified state without transitioning away from the current state. This allows states to run in parallel.

`#stop` stops the specified state if it is active. If `#act` or `#go` is also specified, `#act` and `#go` take precedence.

#### Syntax

```text
#go,target_state
#act,target_state
#stop,target_state
```

#### Example

```text
#st,IDLE
#srch,0x10
#read,a,srch_addr+1
#if,a==0
  #go,SET_A
  #act,SET_B
#endif

#st,SET_A
#srch,0x20
#read,b,srch_addr+1
#read,c,srch_addr+2
#if,b==0
  #stop,SET_B
  #go,IDLE
#else
  #if,c==0
    #printf,match
  #endif
#endif

#st,SET_B
#srch,0x30,0x30
#read,b,srch_addr+2
#if,b==0
  #printf,printf
#endif
```

### (5) Binary Data Operations

`#chg` modifies, deletes, or inserts data.

#### Syntax

```text
#chg,address,target_size,replacement_data,replacement_data,...
```

> The command deletes `target_size` bytes and inserts the replacement data. If no replacement data is specified, it only deletes data. If `target_size` is 0, it only inserts data.

#### Examples

```text
#chg,srch_addr+10,1,a+b
#chg,srch_addr+10,1
#chg,srch_addr+10,0,0x10,a,b
```

### (6) Read Data at a Specified Address

`#read` reads the data at the specified address.

#### Syntax

```text
#read,variable_name,address
```

#### Example

```text
#read,a,srch_addr+10
```

### (7) Initial Active State Settings

`#st_init` specifies the initial states to activate in the state machine.

If this setting is omitted, the first state defined is activated.

#### Syntax

```text
#st_init,state1,state2,...,stateN
```

#### Example

```text
#st_init,idle,idle_2
```

### (10) Console Output

`#printf` displays output in the console.

#### Syntax

```text
#printf,format,expression,expression,...
```

Use `%I64d` in the format string to display an expression in decimal, or `%I64x` to display it in hexadecimal.

#### Example

```text
#printf,addr=%I64x,srch_addr
```

## 5. Version History

- **Ver 0.90** Preliminary release.
