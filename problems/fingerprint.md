# 指紋 (Fingerprint)

## 問題描述
彼得是一個生物專家，他從不同的資料中分析同一群物種間的演化關係，經常會得到不同的演化樹，他想知道不同演化樹間的相似程度。為了節省比較時間，他的想法是先將每一棵演化樹 $T$ 的結構用一個稱為「指紋 (fingerprint)」的數字來表示，然後再進一步去仔細比較「指紋」相近的不同演化樹。

演化樹是一棵無向無根樹 (undirected, unrooted tree)，葉節點代表現存物種。令 $S$ 是一個現存物種集合，令 $T$ 是 $S$ 的一棵演化樹；也就是說 $T$ 的葉節點集合是 $S$；令$\text{deg}(x)$ 表示與節點 $x$ 相鄰之節點個數，對於一個點$x \in T$，當$\text{deg}(x) = 1$時，我們稱 $x$ 為 $T$ 的葉節點；而不是葉節點的點就稱作為內節點，代表著物種的演化過程。對任兩個物種 $x, y\in S$，定義它們間的距離 $d(x, y)$ 為 $x$ 到 $y$ 路徑 (path) 上的邊數 (number of edges)。彼得用 $f(T)$ 來表示 $T$ 的「指紋」並定義 $T$ 的「指紋」為任兩物種距離平方的總和；也就是說
$$
f(T) =  \sum_{x, y \in S, x < y} d(x, y)^2。
$$
以下圖中的演化樹 $T$ 為例，這個演化樹的「指紋」 $f(T) = d(1, 2)^2 + d(1, 3)^2 + d(1, 4)^2 + d(1, 5)^2 + d(2, 3)^2 + d(2, 4)^2 + d(2, 5)^2 + d(3, 4)^2 + d(3, 5)^2 + d(4, 5)^2 = 3^2 + 3^2 + 3^2 + 3^2 + 4^2 + 4^2 + 2^2 + 2^2 + 4^2 + 4^2 = 108$。


\begin{figure}[H]
    \centering
    \begin{tikzpicture}[scale=0.8]
        \def \Nodes{ 1/2/2/white/black, 2/4/2/white/black, 3/0/0/white/black, 4/0/2/white/black, 5/4/0/white/black, 6/1/1/white/black, 7/2/1/white/black, 8/3/1/white/black}
        \def \Edges{ 1/7, 2/8, 3/6, 4/6, 5/8, 6/7, 7/8}
        \foreach \id / \x / \y / \c / \d in \Nodes{
            \node[draw,circle,fill=\c] (\id) at (\x, \y) {\textcolor{\d}{\id}};
        }
        \foreach \x / \y in \Edges{
            \path[draw,-,thick] (\x) -- (\y);
        }
    \end{tikzpicture}
    \caption{$圖一$}
\end{figure}


 


請撰寫一個程式來計算一棵演化樹 $T$ 的「指紋」 $f(T)$。因為 $f(T)$ 可能很大，所以你只要求出 $f(T)$ 除以 $10^9 + 7$ 的餘數。


## 輸入格式
\begin{format}
\f{
$m$
$u_1$ $v_1$
$u_2$ $v_2$
\vdots
$u_{m-1}$ $v_{m-1}$
}
\end{format}

* $m$ 代表演化樹 $T$ 的點數量。 
* $u_i$ 和 $v_i$ 代表的是在 $T$上 $u_i$ 和 $v_i$有一條邊。




## 輸出格式
\begin{format}
\f{
$a$
}
\end{format}
* $a$ 代表給定的演化樹 $T$ 的指紋除以 $10^9 + 7$ 的餘數。

## 測資限制

* $`2 \le m \le 10^6`$。
* $`1 \le u_i, v_i \le m`$。
* 輸入的數皆為整數。 
* 保證給定的圖是一棵連通的演化樹。 

## 範例測試

## 評分說明

本題共有三組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`m \le 1000`$。 |
| 2 | {{score.subtask2}} | 演化樹的所有內部節點 $v$ 的 deg($v$) 都等於 $3$，$m \le 10^5$。 |
| 3 | {{score.subtask3}} | 無額外限制。 |
