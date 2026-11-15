# CSV Diff Program

## 1. About the Program

This program compares selected data columns cell by cell and reports mismatches.

### What Is Checked

Suppose you have a CSV file like the following:

```text
#key,900,200,300,300,44444444444444444

#ggg,200
#ggg,300

#gkkff,400,333333333333333333333

#key,200,300
#key,200,3012
#key,200,302
#gggg
#ddd
#key,200,303
#ffff
#key,200,3042
#ggg
```

Only rows whose first field is `#key` are checked.

### Files to Compare

Suppose you have the following two files.

#### `aaa.csv`

```text
#key,900,200,300,300,44444444444444444

#ggg,200
#ggg,300

#gkkff,400,333333333333333333333

#key,200,300
#key,200,3012
#key,200,302
#gggg
#ddd
#key,200,303
#ffff
#key,200,3042
#ggg
```

#### `bbb.csv`

```text
#key,900,200

#ggg,200
#ggg,300

#gkkff,400

#key,200,300
#fff,990

#key,200,301
#gggg

#key,200,302
#key,200,303
#key,[SKIP]

#key,200,304d
```

Comparing these two files with this program produces the following output:

```text
1   |#key,900,200,300,300,44444444 |x|1   |#key,900,200                  
2   |                              | |2   |                               
3   |#ggg,200                      | |3   |#ggg,200                      
4   |#ggg,300                      | |4   |#ggg,300                      
5   |                              | |5   |                               
6   |#gkkff,400,333333333333333333 | |6   |#gkkff,400                    
7   |                              | |7   |                               
8   |#key,200,300                  |o|8   |#key,200,300                  
    |                              | |9   |#fff,990                      
    |                              | |10  |                               
9   |#key,200,3012                 |x|11  |#key,200,301                  
    |                              | |12  |#gggg                         
    |                              | |13  |                               
10  |#key,200,302                  |o|14  |#key,200,302                  
11  |#gggg                         | |    |                               
12  |#ddd                          | |    |                               
13  |#key,200,303                  |o|15  |#key,200,303                  
14  |#ffff                         | |    |                               
15  |#key,200,3042                 |-|16  |#key,[SKIP]                   
16  |#ggg                          | |17  |                               
17  |                              | |    |                               
18  |                              | |    |                               
19  |                              | |    |                               
    |                              |x|18  |#key,200,304d                 
    |                              | |19  |                               
    |                              | |20  |                               
```

Only rows beginning with `#key` are checked. Matching data is marked `o`; mismatches are marked `x`. Rows outside the comparison scope are left blank.

If `[SKIP]` appears, that row is skipped and marked with `-`.

## 2. Usage

This is a console program.

Syntax:

```text
csvdiff key_string file1 file2 [-m max_mismatches] [-w display_width] [-d] [-dbl_no_cut] [-integer]
```

### Arguments and Options

- **Key string**: The string corresponding to `#key`, as described in “1. About the Program.”
- **File 1 and File 2**: The two files to compare.
- **`-m`**: Stops the comparison when the specified number of mismatches is reached. Specify `0` to check all data. The default is `20`.
- **`-w`**: Specifies the display width in characters. The default is `30`.
- **`-d`**: Displays comparison details.
- **`-dbl_no_cut`**: Preserves double quotation marks.
- **`-integer`**: Compares data as numbers.

With `-integer`, values are compared numerically, even if they contain leading zeros or use hexadecimal notation with a `0x` prefix, as shown below.

```text
19    |#key,0xc8,-500                |o|20    |#key,200,-000500              
20    |                              | |21    |                               
21    |#key,0000200,144              |o|22    |#key,200,0x000090             
22    |                              | |      |                               
```

### Examples

```text
csvdiff #key aaa.csv bbb.csv
csvdiff #key aaa.csv bbb.csv -m 2
csvdiff #key aaa.csv bbb.csv -w 80
csvdiff #key aaa.csv bbb.csv -w 80 -m 0 -d
csvdiff -w 80 -m 0 -d #key aaa.csv bbb.csv
csvdiff -dbl_no_cut -w 80 -m 0 -d #key aaa.csv bbb.csv
csvdiff -integer #key aaa.csv bbb.csv
```

## 3. Version History

- Ver 1.00 Initial release.
- Ver 1.01 Added the `-dbl_no_cut` option and support for files larger than 4 GB.
- Ver 1.02 Added the ability to skip checking rows containing `[SKIP]`.
- Ver 1.03 Added the `-integer` option.
