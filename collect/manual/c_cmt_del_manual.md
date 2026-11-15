# Comment Removal Program

## 1. About the Program

This console program removes comments (`// ...` and `/* ... */`) from C/C++ source files.

## 2. Usage

This is a console program.

### Syntax

```text
c_cmt_del Input file nameOutput file name [-r 指定文字] [-buff buffer_size]
```

Specify the full path to the file.

### Options

- `-r`：Preserves comments that contain the specified string.
- `-buff`: Specifies the buffer size for each read/write operation (KB).
  通常は指定する必要はありませんが、ファイルが大きい場合などには、大きな値を指定すると有効です。
  The default is 10 KB.

### Examples

```text
c_cmt_del c:\csv\in.cpp c:\csv\out.cpp -r \
```

```text
type c:\csv\in.cpp | c_cmt_del - - > c:\csv\out.cpp
```

The `-r` option specifies a string that protects matching comments from deletion.

```text
-r \
```

When specified this way,

```text
//\ ～
```

や

```text
/*\ ～ */
```

comments are not deleted.

## 3. Version History

- **Ver 0.90**　初公開！
- **Ver 0.91**　指定文字列を含むコメントを削除しない指定を追加。
- **Ver 0.92**　高速化しました。
- **Ver 1.00**　4Gバイトを超えるファイルも扱えるようにしました。いろいろとバグフィックス。
