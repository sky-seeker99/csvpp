# CSV-to-XML Conversion Program

## 1. About the Program

This program converts CSV files to XML files.

It supports data larger than 2 GB.

## 2. Usage

This is a console program.

### Syntax

```text
csvxml csv_file xml_file [-tag tag_config_file] [-header header_file] [-buff size] [-e]
```

### Options

- `-e`: Disables conversion to escape codes.
- `-tag`: Specifies the tag configuration file.
- `-header`: Specifies the header file.
- `-buff`: Specifies the buffer size used for each read/write operation (KB). This option is usually unnecessary, but a larger value may help with large files. The default is 10 KB.

### Examples

```text
csvxml data.csv data.xml
csvxml data.csv data.xml -tag tag.csv -header header.txt
```

## 3. Tag Configuration File

The tag configuration file specifies the root tag name, the record tag name, and the tag names for fields.

### Configuration Example

```text
#total_tag,DOC
#record_tag,REC
#tag,hinmei
#tag,tanka
#tag,suuryo
```

If no tags are specified, the following default names are used:

- Root tag: `DOC`
- Record tag: `REC`
- Field tags: `TAG` followed by the field number

### (1) Specify the Root Tag Name

#### Syntax

```text
#total_tag,root_tag_name
```

#### Example

```text
#total_tag,DOC
```

### (2) Specify the Record Tag Name

#### Syntax

```text
#record_tag,record_tag_name
```

#### Example

```text
#record_tag,REC
```

### (3) Specify Field Tag Names

#### Syntax

```text
#tag,field_tag_name
```

#### Example

```text
#tag,suuryo
```

### (4) Escape Conversion

In XML, the following characters are converted to escape codes:

| Character | Escape code |
|---|---|
| `&` (ampersand) | `&amp;` |
| `>` (greater-than sign) | `&gt;` |
| `<` (less-than sign) | `&lt;` |
| `"` (double quotation mark) | `&quot;` |
| `'` (single quotation mark) | `&apos;` |

The `-e` option disables this escaping.

## 4. Header File

The header file specifies the content to place on the first and second lines of the XML file.

### Example

```xml
<?xml version="1.0" encoding="Shift_JIS"?>
<?xml:stylesheet type="text/xsl" href="aaa.xsl"?>
```

For details, refer to the XML specification.

## 5. Version History

- **Ver 1.00** Released.
- **Ver 1.01** Made the header file and tag configuration file selectable through options.
- **Ver 1.02** Added escape code conversion and the `-e` option.
