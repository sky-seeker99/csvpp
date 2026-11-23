# Log Concatenation Program

## 1. About the Program

This program concatenates log files into a single file.

If the output file exceeds a specified number of lines, the program can delete lines from the beginning until the file is reduced to a specified line count.

## 2. Usage

This is a console program.

### Syntax

```text
logcat input_file output_file
logcat -msg output_file "message"
logcat -cut output_file threshold_line_count line_count_after_trimming
```

### Options

- `-msg`: Appends a message to the output file.
- `-cut`: If the output file exceeds the threshold line count, deletes lines from the beginning until the file is reduced to the specified line count after trimming.

### Examples

```text
logcat c:\csv\aaa.log c:\csv\out.log
logcat -msg c:\csv\out.log "starting program"
logcat -cut c:\csv\out.log 20000 10000
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Added the `-msg` and `-cut` options.
