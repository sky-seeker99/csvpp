# Log Concatenation Program

## 1. About the Program

Concatenates log files into a single file.

また、ファイルの行数が指定したThreshold line countを超えた場合、先頭から指定した行数まで削除することができます。

## 2. Usage

This is a console program.

### Syntax

```text
logcat Input file Output file
logcat -msg Output file "Message"
logcat -cut Output file Threshold line count Line count after trimming
```

### Options

- `-msg`：MessageをOutput fileに追加します。
- `-cut`：Output fileの行数がThreshold line countを超えた場合、先頭から行を削除し、Line count after trimmingまで行数を減らします。

### Examples

```text
logcat c:\csv\aaa.log c:\csv\out.log
logcat -msg c:\csv\out.log "startting program"
logcat -cut c:\csv\out.log 20000 10000
```

## 3. Version History

- **Ver 1.00**　初公開！
- **Ver 1.01**　`-msg`、`-cut` を追加。
