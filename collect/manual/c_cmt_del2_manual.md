# Comment Removal Program 2

## 1. About the Program

This console program removes comments (`// ...` and `/* ... */`) from C/C++ source files.

## 2. Usage

This is a console program.

### Syntax

```text
c_cmt_del2 file_to_process [-r string] [-buff buffer_size]
```

Specify the full path to the file.

Wildcards can be used in file names.

### Options

- `-r`: Preserves comments that contain the specified string.
- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.

### Examples

```text
c_cmt_del2 c:\csv\*.cpp -r \\
```

The `-r` option specifies a string that protects matching comments from deletion.

For example, specifying:

```text
-r \\
```

preserves comments such as:

```text
//\ ...
```

and

```text
/*\ ... */
```

## 3. Version History

- **Ver 0.90** Initial release.
- **Ver 0.91** Fixed a bug that prevented the comment exclusion option from taking effect.
- **Ver 1.00** Added support for files larger than 4 GB and fixed various bugs.
