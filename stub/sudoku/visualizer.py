import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import argparse

def visualize_grid(n, grid):

    fig, ax = plt.subplots(figsize=(6, 6))
    ax.set_aspect('equal')

    base_font_size = 40
    font_size = base_font_size - n * n * 1.5
    
    for i in range(n * n):
        for j in range(n * n):
            value = str(grid[i][j])
            
            rect = patches.Rectangle(
                (j, i), 1, 1, 
                linewidth=1, edgecolor='black', facecolor='#FFFAF4'
            )
            ax.add_patch(rect)
            ax.text(j + 0.5, n * n - i - 0.5, value, color="black", ha="center", va="center", fontsize=font_size)
            
            overlay = patches.Rectangle(
                (j + 0.1, i + 0.1), 0.8, 0.8, 
                linewidth=0, facecolor='white', alpha=0.2
            )
            ax.add_patch(overlay)

    for i in range(0, n * n + 1, n):
        ax.axhline(i, color='black', linewidth=3)
    for j in range(0, n * n + 1, n):
        ax.axvline(j, color='black', linewidth=3)
    
    ax.set_xlim(0, n * n)
    ax.set_ylim(0, n * n)
    ax.invert_yaxis()
    ax.axis('off')
    
    plt.show()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file", type=str, help="The original input file.")
    parser.add_argument("--solution", type=str, help="The output file.", default="")
    args = parser.parse_args()

    with open(args.input_file, 'r') as file:
        n = int(file.readline().strip())

        grid = []
        for _ in range(n * n):
            row = list(map(int, file.readline().split()))
            grid.append(row)

    if n > 4:
        print('The size of the grid is too big.')
        exit(0)

    if args.solution != '':
        with open(args.solution, 'r') as file:
            grid_sol = []
            for _ in range(n * n):
                row = list(map(int, file.readline().split()))
                grid_sol.append(row)
        visualize_grid(n, grid_sol)
    else:
        visualize_grid(n, grid)

