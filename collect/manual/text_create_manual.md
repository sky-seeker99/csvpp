# Text File Generation Program

## 1. About the Program

This program generates text files using a variety of patterns.

## 2. Usage

This is a console program.

### Syntax

```text
text_create rule_file [-buff buffer_size]
```

Specify the full path to the rule file.

The rule file must be in CSV format.

`-buff` specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.

### Example

```text
text_create rule.csv
```

## 3. Examples

The following is an example CSV rule file.

```csv
#file,ptn3.txt
#key,cc

#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA1
#writeln,aa,
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA1
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA2
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA3
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA4
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA5
#writeln,aa,aaAAAAAAAAAAAAAAAAAAAAA6

#writeln,bb,bbBBBBBBBBBBBBBBBBBBBBB1
#write,bb,2
#write,bb,3
#write,bb,4
#write,bb,5
#write,bb,6
#writeln,bb,7

#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC1
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC2
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC3
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC4
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC5
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC6
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC7
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC8
#writeln,cc,ccCCCCCCCCCCCCCCCCCCCCC9

#file,ptn1.txt
#key,aa

#file,ptn2.txt
#key,bb
#key,cc

#file,ptn3.txt
#key,dd

#file,ptn3.txt
#key,aa
#key,bb
#file,ptn3.txt
#key,cc
```

### Assigning Keys and Data

In `#write` or `#writeln`, the field following the command is the key. The subsequent fields contain the data associated with that key.

In the example above, the keys are `aa`, `bb`, and `cc`. Their data is shown below.

#### `[aa]`

```text
aaAAAAAAAAAAAAAAAAAAAAA1

aaAAAAAAAAAAAAAAAAAAAAA1
aaAAAAAAAAAAAAAAAAAAAAA2
aaAAAAAAAAAAAAAAAAAAAAA3
aaAAAAAAAAAAAAAAAAAAAAA4
aaAAAAAAAAAAAAAAAAAAAAA5
aaAAAAAAAAAAAAAAAAAAAAA6
```

#### `[bb]`

```text
bbBBBBBBBBBBBBBBBBBBBBB1
234567
```

#### `[cc]`

```text
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
```

The data associated with each key is distributed among the specified files and written to them.

### Writing to Files

`ptn1.txt` includes the following key:

```text
[aa]
```

`ptn2.txt` includes the following keys:

```text
[bb]
[cc]
```

`ptn3.txt` first specifies the following key:

```text
[cc]
```

`[dd]` is not a defined key, so no data is written for it.

The following keys are then selected for output:

```text
[aa]
[bb]
[cc]
```

### Output

#### `ptn1.txt`

```text
aaAAAAAAAAAAAAAAAAAAAAA1

aaAAAAAAAAAAAAAAAAAAAAA1
aaAAAAAAAAAAAAAAAAAAAAA2
aaAAAAAAAAAAAAAAAAAAAAA3
aaAAAAAAAAAAAAAAAAAAAAA4
aaAAAAAAAAAAAAAAAAAAAAA5
aaAAAAAAAAAAAAAAAAAAAAA6
```

#### `ptn2.txt`

```text
bbBBBBBBBBBBBBBBBBBBBBB1
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
```

#### `ptn3.txt`

```text
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
aaAAAAAAAAAAAAAAAAAAAAA1

aaAAAAAAAAAAAAAAAAAAAAA1
aaAAAAAAAAAAAAAAAAAAAAA2
aaAAAAAAAAAAAAAAAAAAAAA3
aaAAAAAAAAAAAAAAAAAAAAA4
aaAAAAAAAAAAAAAAAAAAAAA5
aaAAAAAAAAAAAAAAAAAAAAA6
bbBBBBBBBBBBBBBBBBBBBBB1
234567
ccCCCCCCCCCCCCCCCCCCCCC1
ccCCCCCCCCCCCCCCCCCCCCC2
ccCCCCCCCCCCCCCCCCCCCCC3
ccCCCCCCCCCCCCCCCCCCCCC4
ccCCCCCCCCCCCCCCCCCCCCC5
ccCCCCCCCCCCCCCCCCCCCCC6
ccCCCCCCCCCCCCCCCCCCCCC7
ccCCCCCCCCCCCCCCCCCCCCC8
ccCCCCCCCCCCCCCCCCCCCCC9
```

## 4. Command Reference

### 4.1 Define an Output File

**Syntax**

```text
#file,file_name
```

**Example**

```text
#file,c:\aaa.txt
```

### 4.2 Define Output Patterns for a File

**Syntax**

```text
#key,pattern_name
```

**Example**

```text
#key,aaa
```

### 4.3 Define Pattern Output

**Syntax**

```text
#write,pattern_name,string_data       -> no line break
#writeln,pattern_name,string_data     -> followed by a line break
```

**Example**

```text
#write,aaa,ABCDEFGHIJKLMN
#writeln,aaa,ABCDEFGHIJKLMN
```

### 4.4 Configure Leading Spaces

Sets the number of leading spaces (indentation) used when outputting a pattern.

**Syntax**

```text
#sp,pattern_name,number_of_leading_spaces
#sp++,pattern_name,amount_to_add
#sp--,pattern_name,amount_to_subtract
#sp_push,pattern_name,storage_key
#sp_pop,pattern_name,storage_key
```

- `#sp`: Sets the number of leading spaces to the specified value.
- `#sp++`: Adds the specified value to the current number of leading spaces.
- `#sp--`: Subtracts the specified value from the current number of leading spaces.
- `#sp_push`: Saves the current number of leading spaces under the specified storage key.
- `#sp_pop`: Sets the current number of leading spaces to the value saved under the storage key.

**Example**

```text
#writeln,aa,if (a==0){
#sp++,aa,2
#writeln,aa,b=c;
#sp--,aa,2
#writeln,aa,}
```

Output:

```text
if (a==0){
  b=c;
}
```

You can use `#sp` to set the number of spaces directly.

```text
#writeln,aa,if (a==0){
#sp,aa,2
#writeln,aa,b=c;
#sp,aa,0
#writeln,aa,}
```

Output:

```text
if (a==0){
  b=c;
}
```

### 4.5 Read a File

**Syntax**

```text
#wr_file,pattern_name,file_to_read
```

**Example**

```text
#wr_file,aaa,c:\aaa.dat
```

Reads `c:\aaa.dat` and adds its contents to the `aaa` pattern.

You can specify multiple files:

```text
#wr_file,aaa,c:\a0.dat
#wr_file,aaa,c:\a1.dat
```

When multiple files are specified this way, their contents are merged in the output.

## 5. Version History

- Ver 1.00 Released.
- Ver 1.01 Changed `#wr` to `#write` and `#writeln`.
- Ver 1.02 Added `#sp`, `#sp++`, and `#sp--`.
- Ver 1.03 Added `#wr_file`.
- Ver 1.04 Added `#sp_push` and `#sp_pop`.
