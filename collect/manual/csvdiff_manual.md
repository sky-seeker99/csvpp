# CSV Diff Program

## 1. About the Program

Compares selected data columns cell by cell and reports mismatches.

### チェック対象

例えば、以下のようなCSV fileがあるとします。

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

この中で、**1カラム目のデータが `#key` の行だけ**をチェックします。

### 比較するファイル

以下の2つのファイルがあるとします。

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

この2つのファイルをThis programでDIFFすると、以下のように出力されます。

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

Only rows beginning with `#key` are checked. Matching data is marked `o`; mismatches are marked `x`.Rows outside the comparison scope are left blank.

If `[SKIP]` is present, the row is skipped and displayed as `-`.

## 2. Usage

This is a console program.

The syntax is as follows.

```text
csvdiff Key string File 1 File 2 [-m maximum_mismatches] [-w display_width] [-d] [-dbl_no_cut] [-integer]
```

### 引数・Option

- **Key string**  
  Specify the string corresponding to `#key`, as described in “1. About the Program.”
- **File 1、File 2**  
  Specify the two files to compare.
- **`-m` Option**  
  Stops the comparison when the specified mismatch count is reached.Specify `0` to check all data. The default is `20`.
- **`-w` Option**  
  横方向の表示文字数を指定します。Default valueは `30` です。
- **`-d` Option**  
  Displays comparison details.
- **`-dbl_no_cut` Option**  
  Does not remove double quotation marks.
- **`-integer` Option**  
  Compares data as numbers.

`-integer` Optionを指定すると、以下のように前ゼロがある場合でも、`0x` を付けた16進数を含めて数値としてチェックできます。

```text
19    |#key,0xc8,-500                |o|20    |#key,200,-000500              
20    |                              | |21    |                              
21    |#key,0000200,144              |o|22    |#key,200,0x000090             
22    |                              | |      |                              
```

### 実行例

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

- Ver 1.00　初公開
- Ver 1.01　`-dbl_no_cut` Optionを追加。4GBを超えるファイルも扱えるように変更
- Ver 1.02　データに `[SKIP]` を記述するとチェックしない機能を追加
- Ver 1.03　`-integer` Optionを追加
