import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import argparse

def visualize_grid(grid):
    color_map = {
        -1: 'red',
        0: 'white',
        1: '#ADD8E6',  # Light Blue
        2: '#90EE90',  # Light Green
        3: '#FFFFE0',  # Light Yellow
        4: '#E0FFFF',  # Light Cyan
        5: '#DDA0DD',  # Plum
        6: '#FFA07A',  # Light Salmon
        7: '#E6E6FA',  # Lavender
        8: '#C3B091',  # Khaki
    }

    fig, ax = plt.subplots(figsize=(10, 10))
    ax.set_aspect('equal')
    
    n, m = len(grid), len(grid[0])

    if n > 50:
        print('Too much rows, reduced to 10')
        grid = grid[:50]
        n = 50
    if m > 50:
        print('Too much columns, reduced to 10')
        for row in grid:
            row = row[:50]
        m = 50
    
    for i in range(n):
        for j in range(m):
            value = grid[i][j]
            color = color_map[value]
            
            rect = patches.Rectangle(
                (j, i), 1, 1, 
                linewidth=1, edgecolor='black', facecolor=color
            )
            ax.add_patch(rect)
            
            overlay = patches.Rectangle(
                (j + 0.1, i + 0.1), 0.8, 0.8, 
                linewidth=0, facecolor='white', alpha=0.2
            )
            ax.add_patch(overlay)

    for i in range(0, n + 1, 5):
        ax.axhline(i, color='black', linewidth=3)
    for j in range(0, m + 1, 5):
        ax.axvline(j, color='black', linewidth=3)
    
    ax.set_xlim(0, m)
    ax.set_ylim(0, n)
    ax.invert_yaxis()
    ax.axis('off')
    
    plt.show()

def color_grid(grid):
    n, m = len(grid), len(grid[0])
    adj = dict()
    colors = set()
    
    def add_edge(u, v):
        if u == v or u <= 0 or v <= 0:
            return
        if u not in adj:
            adj[u] = set()
        if v not in adj:
            adj[v] = set()
        adj[u].add(v)
        adj[v].add(u)

    for i in range(n):
        for j in range(m):
            if grid[i][j] > 0:
                colors.add(grid[i][j])
                if i + 1 < n:
                    add_edge(grid[i][j], grid[i + 1][j])
                if j + 1 < m:
                    add_edge(grid[i][j], grid[i][j + 1])

    bucket = [[] for i in range(20)]
    deg = dict()
    order = []

    for c in colors:
        bucket[len(adj[c])].append(c)
        deg[c] = len(adj[c])

    new_color = dict()
    cur = 0
    while cur < 20:
        if len(bucket[cur]) == 0:
            cur += 1
            continue
        u = bucket[cur].pop()
        if u in new_color:
            continue
        for v in adj[u]:
            deg[v] -= 1
            bucket[deg[v]].append(v)
        order.append(u)
        new_color[u] = 0
        if cur > 0:
            cur -= 1
   
    for c in order[::-1]:
        used = set()
        for u in adj[c]:
            used.add(new_color[u])
        for i in range(1, 20):
            if i not in used:
                new_color[c] = i
                break

    for i in range(n):
        for j in range(m):
            if grid[i][j] > 0:
                grid[i][j] = new_color[grid[i][j]]

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file", type=str, help="The original input file.")
    parser.add_argument("--solution", type=str, help="The output file.", default="")
    args = parser.parse_args()

    with open(args.input_file, 'r') as file:
        n, m = map(int, file.readline().split())
        n *= 5
        m *= 5

        grid = []
        for _ in range(n):
            row = list(map(int, file.readline().split()))
            grid.append(row)

    if args.solution != '':
        with open(args.solution, 'r') as file:
            grid_sol = []
            for _ in range(n):
                row = list(map(int, file.readline().split()))
                grid_sol.append(row)
        color_grid(grid_sol)
        visualize_grid(grid_sol)
    else:
        visualize_grid(grid)

