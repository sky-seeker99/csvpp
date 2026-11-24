# Line Ending Conversion Program

## 1. About the Program

This console program converts between Windows, Mac, and Unix line endings.

Wildcards can be used in file names.

## 2. Usage

This is a console program.

### Syntax

```text
retchg -m|-w|-u file_to_convert [-buff buffer_size]
```

Specify the full path to the file to convert.

### Options

- `-m`: Converts line endings to the Mac format.
- `-w`: Converts line endings to the Windows format.
- `-u`: Converts line endings to the Unix format.
- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may be useful for large files. The default is 10 KB.

### Examples

```text
retchg -w c:\csv\*.txt
```

```text
retchg -m c:\csv\*.html
```

```text
retchg -u c:\csv\*.csv
```

```text
retchg -u c:\csv\*.csv -buff 100
```

## 3. Version History

- **Ver 1.00** Initial release.
- **Ver 1.01** Added support for Level 2 kanji characters.
- **Ver 1.02** Added support for files larger than 4 GB.
