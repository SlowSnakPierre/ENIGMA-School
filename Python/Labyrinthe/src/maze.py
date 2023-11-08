import random
import math
from src.cell import Cell
from src.algorithm import depth_first_recursive_backtracker, binary_tree, imperfectMaze


class Maze(object):
    def __init__(self, num_rows, num_cols, id=0, algorithm="dfs_backtrack"):
        self.num_cols = num_cols
        self.num_rows = num_rows
        self.id = id
        self.grid_size = num_rows * num_cols
        self.entry_coor = self._pick_random_entry_exit(None)
        self.exit_coor = self._pick_random_entry_exit(self.entry_coor)
        self.generation_path = []
        self.solution_path = None
        self.initial_grid = self.generate_grid()
        self.grid = self.initial_grid
        self.generate_maze(algorithm, (0, 0))

    def generate_grid(self):
        grid = list()

        for i in range(self.num_rows):
            grid.append(list())

            for j in range(self.num_cols):
                grid[i].append(Cell(i, j))

        return grid

    def find_neighbours(self, cell_row, cell_col):
        neighbours = list()

        def check_neighbour(row, col):
            if row >= 0 and row < self.num_rows and col >= 0 and col < self.num_cols:
                neighbours.append((row, col))

        check_neighbour(cell_row - 1, cell_col)
        check_neighbour(cell_row, cell_col + 1)
        check_neighbour(cell_row + 1, cell_col)
        check_neighbour(cell_row, cell_col - 1)

        if len(neighbours) > 0:
            return neighbours

        else:
            return None

    def _validate_neighbours_generate(self, neighbour_indices):
        neigh_list = [n for n in neighbour_indices if not self.grid[n[0]][n[1]].visited]

        if len(neigh_list) > 0:
            return neigh_list
        else:
            return None

    def validate_neighbours_solve(self, neighbour_indices, k, l, k_end, l_end, method="fancy"):
        if method == "fancy":
            neigh_list = list()
            min_dist_to_target = 100000

            for k_n, l_n in neighbour_indices:
                if (not self.grid[k_n][l_n].visited and not self.grid[k][l].is_walls_between(self.grid[k_n][l_n])):
                    dist_to_target = math.sqrt((k_n - k_end) ** 2 + (l_n - l_end) ** 2)

                    if (dist_to_target < min_dist_to_target):
                        min_dist_to_target = dist_to_target
                        min_neigh = (k_n, l_n)

            if "min_neigh" in locals():
                neigh_list.append(min_neigh)

        elif method == "brute-force":
            neigh_list = [n for n in neighbour_indices if not self.grid[n[0]][n[1]].visited and not self.grid[k][l].is_walls_between(self.grid[n[0]][n[1]])]

        if len(neigh_list) > 0:
            return neigh_list
        else:
            return None

    def _pick_random_entry_exit(self, used_entry_exit=None):
        rng_entry_exit = used_entry_exit

        while rng_entry_exit == used_entry_exit:
            rng_side = random.randint(0, 3)

            if (rng_side == 0):
                rng_entry_exit = (0, random.randint(0, self.num_cols - 1))

            elif (rng_side == 2):
                rng_entry_exit = (self.num_rows - 1, random.randint(0, self.num_cols - 1))

            elif (rng_side == 1):
                rng_entry_exit = (random.randint(0, self.num_rows - 1), self.num_cols - 1)

            elif (rng_side == 3):
                rng_entry_exit = (random.randint(0, self.num_rows - 1), 0)

        return rng_entry_exit

    def generate_maze(self, algorithm, start_coor=(0, 0)):
        if algorithm == "dfs_backtrack":
            depth_first_recursive_backtracker(self, start_coor)
        elif algorithm == "dfs_backtrack_imperfect":
            imperfectMaze(self, start_coor)
        elif algorithm == "bin_tree":
            binary_tree(self, start_coor)
