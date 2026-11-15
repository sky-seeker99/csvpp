# バイナリFile Concatenation・分割Program

## 1. About the Program

This console program concatenates binary files and extracts selected portions.

## 2. Usage

This is a console program.

### Syntax

```text
bin_catcut in_file out_file [-new] [-r_offset offset] [-w_offset offset] [-size size] [-buff buffer_size]
```

If no options are specified, the contents of `in_file` are appended to `out_file`.

### Options

- `-new`: Creates a new file.
- `-r_offset`：Specifies the input byte offset. If omitted, reading starts at the beginning of the file.
- `-w_offset`：Output fileのオフセットバイト数を指定します。指定しない場合はファイルの最後から付加されます。
- `-size`: Specifies the number of bytes to read or write.指定しない場合は、Input fileのサイズからInput fileのオフセットバイト数を引いた値になります。
- `-buff`: Specifies the buffer size for each read/write operation (KB).
  通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。
  The default is 10 KB.

Note: Numbers can be specified in hexadecimal by prefixing them with `0x`.  
例：`0x1000`、`0xa0df`

### Examples

#### Concatenating Files

```text
bin_catcut in1.bin out.bin -new
bin_catcut in2.bin out.bin
bin_catcut in3.bin out.bin
```

#### Splitting into 100-Byte Blocks

```text
bin_catcut in.bin out1.bin -new -size 100
bin_catcut in.bin out2.bin -new -size 100 -r_offset 100
bin_catcut in.bin out3.bin -new -size 100 -r_offset 200
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　4Gバイトを超えるファイルも扱えるようにしました。
- **Ver 1.01a**　バグフィックス。
- **Ver 1.02**　バッファサイズのバグフィックス。
