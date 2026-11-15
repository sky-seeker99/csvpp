# CSVファイル横マージプログラム

## 1. ソフトの紹介

複数のCSVファイルを横方向にマージするプログラムです。

## 2. 使用方法

本プログラムはコンソールプログラムです。

実行形式は以下のとおりです。

```text
csvmerge CSVファイル1 CSVファイル2 CSVファイル3 .... > マージファイル
```

### 例

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

上記の2つのCSVファイルをマージすると、以下のようになります。

#### `out.csv`

```csv
aa0,bb1,cc2,dd4,ee5,ff6
aa1,bb2,cc3,dd5,ee6,ff7
aa2,bb3,cc4,dd6,ee7,ff8
,,,dd7,ee8,ff9
```

このように、複数のCSVファイルを横方向に結合します。

## 3. 履歴

- Ver 1.00　初公開
- Ver 1.01　バグ修正
