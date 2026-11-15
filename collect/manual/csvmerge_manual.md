# Horizontal CSV Merge Program

## 1. About the Program

This program merges multiple CSV files horizontally.

## 2. Usage

This is a console program.

The syntax is as follows.

```text
csvmerge CSV file 1 CSV file 2 CSV file 3 .... > Merged output
```

### Example

```text
csvmerge sample1.csv sample2.csv > out.csv
```

#### `sample1.csv`

```csv
aa0,bb1,cc2
aa1,bb2,cc3
aa2,bb3,cc4
```

#### `sample2.csv`

```csv
dd4,ee5,ff6
dd5,ee6,ff7
dd6,ee7,ff8
```

上記の2つのCSV fileをマージすると、The result is as follows.

#### `out.csv`

```csv
aa0,bb1,cc2,dd4,ee5,ff6
aa1,bb2,cc3,dd5,ee6,ff7
aa2,bb3,cc4,dd6,ee7,ff8
,,,dd7,ee8,ff9
```

This is how multiple CSV files are combined horizontally.

## 3. Version History

- Ver 1.00　初公開
- Ver 1.01　バグ修正
