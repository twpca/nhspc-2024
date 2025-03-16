# 數獨 (Sudoku)

\textcolor{red}{\textbf{本題為 Output Only。}}請注意，你在第 $i$ 筆測試資料上傳的輸出檔名必須為 `output_i_1.txt`。

## 問題描述

費里敦（Fereydun）是一位傳說中的波斯英雄，根據預言，他將戰勝扎哈克（Zahhak）。費里敦相信，除了強壯的體魄外，還需要擁有強大的頭腦。他最近從一位日本商人那裡學到了一個名為數獨（Sudoku）的益智遊戲。

數獨是在一個 $n^2 \times n^2$ 的棋盤上進行的遊戲。整個棋盤被分成 $n^2$ 個子區域，每個子區域的大小為 $n \times n$。每個格子可以是空的，也可以包含一個從 $1$ 到 $n^2$ 之間的整數。一個數獨棋盤是合法的，需滿足以下條件：

1. 每一行中的所有數字都是不同的。
2. 每一列中的所有數字都是不同的。
3. 每個子區域中的所有數字都是不同的。

以下圖示顯示了兩個沒有空格子的合法數獨棋盤：

![數獨棋盤範例圖](Sudoku.png)

費里敦有一個帶有一些空格的合法數獨棋盤，並請求你的幫助。你的任務是**儘可能多**地填充這些空格，同時保持棋盤有效。

保證至少存在一種方法可以填滿所有空格且使棋盤保持合法。

## 輸入格式

\begin{format}
\f{
$n$
$a_{1, 1}$ $a_{1, 2}$ $\cdots$ $a_{1, n}$
$a_{2, 1}$ $a_{2, 2}$ $\cdots$ $a_{2, n}$
$\vdots$
$a_{n, 1}$ $a_{n, 2}$ $\cdots$ $a_{n, n}$
}
\end{format}

* $n$ 為棋盤的大小。
* $a_{i, j}$ 代表棋盤第 $i$ 列第 $j$ 欄格子內的數字。

## 輸出格式

\begin{format}
\f{
$b_{1, 1}$ $b_{1, 2}$ $\cdots$ $b_{1, n}$
$b_{2, 1}$ $b_{2, 2}$ $\cdots$ $b_{2, n}$
$\vdots$
$b_{n, 1}$ $b_{n, 2}$ $\cdots$ $b_{n, n}$
}
\end{format}

* $b_{i, j}$ 代表你給出的棋盤中，第 $i$ 列第 $j$ 欄格子內的數字。

## 測資限制

* $2\le n\le 20$。
* $0\leq a_{i, j} \leq n^2$。
* 測試資料保證存在一種可以填滿所有空格且使棋盤保持合法的方式。

\newpage

## 評分說明

本題共有 10 組測試資料，輸入檔案的說明如表所示。
對於每一組測試資料，若你上傳的輸出檔案滿足輸出格式且為合法的數獨棋盤，那麼你會得到以下分數
$$
\frac{10 \times (p - q)}{p}
$$
其中 $p$ 是最初棋盤的空格數量、$q$ 是你給出的棋盤內的空格數量。

若你上傳的輸出檔案不滿足輸出格式、有原本非空的格子被填入了不同的數字、或是你輸出的棋盤不是合法的數獨棋盤，那麼你將得到 $0$ 分。

|  測試資料  |  分數  | 輸入檔名 | 輸出檔名 |  說明 |
| :------: | :----: | :----: | :----: | ------------ |
| 1 | {{score.subtask1}} | `input_1_1.txt` | `output_1_1.txt` | $n = 2$。|
| 2 | {{score.subtask2}} | `input_2_1.txt` | `output_2_1.txt` | $n = 3$。|
| 3 | {{score.subtask3}} | `input_3_1.txt` | `output_3_1.txt` | $n = 3$。|
| 4 | {{score.subtask4}} | `input_4_1.txt` | `output_4_1.txt` | $n = 10$。|
| 5 | {{score.subtask5}} | `input_5_1.txt` | `output_5_1.txt` | $n = 20$。|
| 6 | {{score.subtask6}} | `input_6_1.txt` | `output_6_1.txt` | $n = 4$。|
| 7 | {{score.subtask7}} | `input_7_1.txt` | `output_7_1.txt` | $n = 8$。|
| 8 | {{score.subtask8}} | `input_8_1.txt` | `output_8_1.txt` | $n = 12$。|
| 9 | {{score.subtask9}} | `input_9_1.txt` | `output_9_1.txt` | $n = 16$。|
| 10 | {{score.subtask10}} | `input_10_1.txt` | `output_10_1.txt` | $n = 20$。|

\newpage

## 範例

作為範例，假設測試資料的長相為

```
2
0 2 0 0
3 0 0 0
0 0 4 0
0 0 0 1
```

則下面是一個可能的合法輸出

```
4 2 3 0
3 1 2 4
1 3 4 2
2 4 0 1
```

在這個範例中，$p$ 和 $q$ 的值分別為 $12$ 和 $2$。因此，這個輸出可以獲得 $\frac{10\times (12 - 2)}{12}\sim 8.33$ 分

## 視覺化工具（Visualizer）

為了方便選手觀看自己的輸出結果以及觀察測試資料，在此任務的附件（attachment）中，有一腳本程式（script）供選手視覺化（visualize）輸入檔與輸出檔。

請利用下列指令視覺化輸入檔。因為技術上的限制，附件中提供的視覺化工具僅能展示 $n\leq 4$ 的數獨棋盤。

```
python3 visualizer.py [input file]
```

你可利用下列指令，將你對於某個輸入計算出的解做視覺化。

```
python3 visualizer.py [input file] --solution [output file]
```

範例：

```
python3 visualizer.py input_1_1.txt --solution output_1_1.txt
```

請注意，若你傳入的資料的格式並不合法，將會產生一些不可預期的行為。
