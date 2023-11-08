import time
import random

algorithm_list = ["dfs_backtrack", "bin_tree", "dfs_backtrack_imperfect"]


def depth_first_recursive_backtracker(maze, start_coor):
    k_curr, l_curr = start_coor
    path = [(k_curr, l_curr)]
    maze.grid[k_curr][l_curr].visited = True
    visit_counter = 1
    visited_cells = list()

    print("\nGenerating the maze with depth-first search...")
    time_start = time.time()

    while visit_counter < maze.grid_size:
        neighbour_indices = maze.find_neighbours(k_curr, l_curr)
        neighbour_indices = maze._validate_neighbours_generate(neighbour_indices)

        if neighbour_indices is not None:
            visited_cells.append((k_curr, l_curr))
            k_next, l_next = random.choice(neighbour_indices)
            maze.grid[k_curr][l_curr].remove_walls(k_next, l_next)
            maze.grid[k_next][l_next].remove_walls(k_curr, l_curr)
            maze.grid[k_next][l_next].visited = True
            k_curr = k_next
            l_curr = l_next
            path.append((k_curr, l_curr))
            visit_counter += 1

        elif len(visited_cells) > 0:
            k_curr, l_curr = visited_cells.pop()
            path.append((k_curr, l_curr))

    print("Number of moves performed: {}".format(len(path)))
    print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))

    maze.grid[maze.entry_coor[0]][maze.entry_coor[1]].set_as_entry_exit("entry", maze.num_rows - 1, maze.num_cols - 1)
    maze.grid[maze.exit_coor[0]][maze.exit_coor[1]].set_as_entry_exit("exit", maze.num_rows - 1, maze.num_cols - 1)

    for i in range(maze.num_rows):
        for j in range(maze.num_cols):
            maze.grid[i][j].visited = False

    maze.generation_path = path


def binary_tree(maze, start_coor):
    time_start = time.time()

    for i in range(0, maze.num_rows):
        if (i == maze.num_rows - 1):
            for j in range(0, maze.num_cols - 1):
                maze.grid[i][j].remove_walls(i, j + 1)
                maze.grid[i][j + 1].remove_walls(i, j)

            break

        for j in range(0, maze.num_cols):
            if (j == maze.num_cols - 1):
                maze.grid[i][j].remove_walls(i + 1, j)
                maze.grid[i + 1][j].remove_walls(i, j)
                continue

            remove_top = random.choice([True, False])

            if remove_top:
                maze.grid[i][j].remove_walls(i + 1, j)
                maze.grid[i + 1][j].remove_walls(i, j)

            else:
                maze.grid[i][j].remove_walls(i, j + 1)
                maze.grid[i][j + 1].remove_walls(i, j)

    print("Number of moves performed: {}".format(maze.num_cols * maze.num_rows))
    print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))

    maze.grid[maze.entry_coor[0]][maze.entry_coor[1]].set_as_entry_exit("entry", maze.num_rows - 1, maze.num_cols - 1)
    maze.grid[maze.exit_coor[0]][maze.exit_coor[1]].set_as_entry_exit("exit", maze.num_rows - 1, maze.num_cols - 1)

    path = list()

    visit_counter = 0

    visited = list()

    k_curr, l_curr = (maze.num_rows - 1, maze.num_cols - 1)

    path.append((k_curr, l_curr))

    begin_time = time.time()

    while visit_counter < maze.grid_size:
        possible_neighbours = list()

        try:
            if not maze.grid[k_curr - 1][l_curr].visited and k_curr != 0:
                if not maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_curr - 1][l_curr]):
                    possible_neighbours.append((k_curr - 1, l_curr))
        except:
            print()

        try:
            if not maze.grid[k_curr][l_curr - 1].visited and l_curr != 0:
                if not maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_curr][l_curr - 1]):
                    possible_neighbours.append((k_curr, l_curr - 1))
        except:
            print()

        if len(possible_neighbours) != 0:
            k_next, l_next = possible_neighbours[0]

            path.append(possible_neighbours[0])

            visited.append((k_curr, l_curr))

            maze.grid[k_next][l_next].visited = True

            visit_counter += 1

            k_curr, l_curr = k_next, l_next

        else:
            if len(visited) != 0:
                k_curr, l_curr = visited.pop()
                path.append((k_curr, l_curr))
            else:
                break
    for row in maze.grid:
        for cell in row:
            cell.visited = False

    print(f"Generating path for maze took {time.time() - begin_time}s.")
    maze.generation_path = path


def imperfectMaze(maze, start_coor):
    k_curr, l_curr = start_coor
    path = [(k_curr, l_curr)]
    maze.grid[k_curr][l_curr].visited = True
    visit_counter = 1
    visited_cells = list()

    print("\nGenerating the imperfect maze with depth-first search...")
    time_start = time.time()

    while visit_counter < maze.grid_size:
        neighbour_indices = maze.find_neighbours(k_curr, l_curr)
        neighbour_indices = maze._validate_neighbours_generate(neighbour_indices)

        if neighbour_indices is not None:
            visited_cells.append((k_curr, l_curr))
            k_next, l_next = random.choice(neighbour_indices)
            k_rand, l_rand = random.choice(neighbour_indices)
            maze.grid[k_curr][l_curr].remove_walls(k_next, l_next)
            maze.grid[k_next][l_next].remove_walls(k_curr, l_curr)

            if random.randint(1, 3) == 1:
                maze.grid[k_rand][l_rand].remove_walls(k_curr, l_curr)
                maze.grid[k_curr][l_curr].remove_walls(k_rand, l_rand)

            maze.grid[k_next][l_next].visited = True
            k_curr = k_next
            l_curr = l_next
            path.append((k_curr, l_curr))
            visit_counter += 1

        elif len(visited_cells) > 0:
            k_curr, l_curr = visited_cells.pop()
            path.append((k_curr, l_curr))

    print("Number of moves performed: {}".format(len(path)))
    print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))

    maze.grid[maze.entry_coor[0]][maze.entry_coor[1]].set_as_entry_exit("entry", maze.num_rows - 1, maze.num_cols - 1)
    maze.grid[maze.exit_coor[0]][maze.exit_coor[1]].set_as_entry_exit("exit", maze.num_rows - 1, maze.num_cols - 1)

    for i in range(maze.num_rows):
        for j in range(maze.num_cols):
            maze.grid[i][j].visited = False

    maze.generation_path = path