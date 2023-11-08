import time
import random
import logging

logging.basicConfig(level=logging.DEBUG)


class Solver(object):
    def __init__(self, maze, quiet_mode, neighbor_method):
        logging.debug("Class Solver ctor called")

        self.maze = maze
        self.neighbor_method = neighbor_method
        self.name = ""
        self.quiet_mode = quiet_mode

    def solve(self):
        logging.debug('Class: Solver solve called')
        raise NotImplementedError

    def get_name(self):
        logging.debug('Class Solver get_name called')
        raise self.name

    def get_path(self):
        logging.debug('Class Solver get_path called')
        return self.path


class BreadthFirst(Solver):
    def __init__(self, maze, quiet_mode=False, neighbor_method="fancy"):
        logging.debug('Class BreadthFirst ctor called')

        self.name = "Breadth First Recursive"
        super().__init__(maze, neighbor_method, quiet_mode)

    def solve(self):
        logging.debug("Class BreadthFirst solve called")
        current_level = [self.maze.entry_coor]
        path = list()

        print("\nSolving the maze with breadth-first search...")
        time_start = time.time()

        while True:
            next_level = list()

            while current_level:
                k_curr, l_curr = current_level.pop(0)
                self.maze.grid[k_curr][l_curr].visited = True
                path.append(((k_curr, l_curr), False))

                if (k_curr, l_curr) == self.maze.exit_coor:
                    if not self.quiet_mode:
                        print("Number of moves performed: {}".format(len(path)))
                        print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))
                    return path

                neighbour_coors = self.maze.find_neighbours(k_curr, l_curr)
                neighbour_coors = self.maze.validate_neighbours_solve(neighbour_coors, k_curr, l_curr, self.maze.exit_coor[0], self.maze.exit_coor[1], self.neighbor_method)

                if neighbour_coors is not None:
                    for coor in neighbour_coors:
                        next_level.append(coor)

            for cell in next_level:
                current_level.append(cell)
        logging.debug("Class BreadthFirst leaving solve")


class BiDirectional(Solver):
    def __init__(self, maze, quiet_mode=False, neighbor_method="fancy"):
        logging.debug('Class BiDirectional ctor called')

        super().__init__(maze, neighbor_method, quiet_mode)
        self.name = "Bi Directional"

    def solve(self):
        logging.debug("Class BiDirectional solve called")

        grid = self.maze.grid
        k_curr, l_curr = self.maze.entry_coor
        p_curr, q_curr = self.maze.exit_coor
        grid[k_curr][l_curr].visited = True
        grid[p_curr][q_curr].visited = True
        backtrack_kl = list()
        backtrack_pq = list()
        path_kl = list()
        path_pq = list()

        if not self.quiet_mode:
            print("\nSolving the maze with bidirectional depth-first search...")
        time_start = time.time()

        while True:
            neighbours_kl = self.maze.find_neighbours(k_curr, l_curr)
            real_neighbours_kl = [neigh for neigh in neighbours_kl if not grid[k_curr][l_curr].is_walls_between(grid[neigh[0]][neigh[1]])]
            neighbours_kl = [neigh for neigh in real_neighbours_kl if not grid[neigh[0]][neigh[1]].visited]

            neighbours_pq = self.maze.find_neighbours(p_curr, q_curr)
            real_neighbours_pq = [neigh for neigh in neighbours_pq if not grid[p_curr][q_curr].is_walls_between(grid[neigh[0]][neigh[1]])]
            neighbours_pq = [neigh for neigh in real_neighbours_pq if not grid[neigh[0]][neigh[1]].visited]

            if len(neighbours_kl) > 0:
                backtrack_kl.append((k_curr, l_curr))
                path_kl.append(((k_curr, l_curr), False))
                k_next, l_next = random.choice(neighbours_kl)
                grid[k_next][l_next].visited = True
                k_curr = k_next
                l_curr = l_next

            elif len(backtrack_kl) > 0:
                path_kl.append(((k_curr, l_curr), True))
                k_curr, l_curr = backtrack_kl.pop()

            if len(neighbours_pq) > 0:
                backtrack_pq.append((p_curr, q_curr))
                path_pq.append(((p_curr, q_curr), False))
                p_next, q_next = random.choice(neighbours_pq)
                grid[p_next][q_next].visited = True
                p_curr = p_next
                q_curr = q_next

            elif len(backtrack_pq) > 0:
                path_pq.append(((p_curr, q_curr), True))
                p_curr, q_curr = backtrack_pq.pop()

            if any((True for n_kl in real_neighbours_kl if (n_kl, False) in path_pq)):
                path_kl.append(((k_curr, l_curr), False))
                path = [p_el for p_tuple in zip(path_kl, path_pq) for p_el in p_tuple]
                if not self.quiet_mode:
                    print("Number of moves performed: {}".format(len(path)))
                    print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))
                logging.debug("Class BiDirectional leaving solve")
                return path


            elif any((True for n_pq in real_neighbours_pq if (n_pq, False) in path_kl)):
                path_pq.append(((p_curr, q_curr), False))
                path = [p_el for p_tuple in zip(path_kl, path_pq) for p_el in p_tuple]
                if not self.quiet_mode:
                    print("Number of moves performed: {}".format(len(path)))
                    print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))
                logging.debug("Class BiDirectional leaving solve")
                return path


class DepthFirstBacktracker(Solver):
    def __init__(self, maze, quiet_mode=False, neighbor_method="fancy"):
        logging.debug('Class DepthFirstBacktracker ctor called')

        super().__init__(maze, neighbor_method, quiet_mode)
        self.name = "Depth First Backtracker"

    def solve(self):
        logging.debug("Class DepthFirstBacktracker solve called")
        k_curr, l_curr = self.maze.entry_coor
        self.maze.grid[k_curr][l_curr].visited = True
        visited_cells = list()
        path = list()
        if not self.quiet_mode:
            print("\nSolving the maze with depth-first search...")

        time_start = time.time()

        while (k_curr, l_curr) != self.maze.exit_coor:
            neighbour_indices = self.maze.find_neighbours(k_curr, l_curr)
            neighbour_indices = self.maze.validate_neighbours_solve(neighbour_indices, k_curr, l_curr, self.maze.exit_coor[0], self.maze.exit_coor[1], self.neighbor_method)

            if neighbour_indices is not None:
                visited_cells.append((k_curr, l_curr))
                path.append(((k_curr, l_curr), False))
                k_next, l_next = random.choice(neighbour_indices)
                self.maze.grid[k_next][l_next].visited = True
                k_curr = k_next
                l_curr = l_next

            elif len(visited_cells) > 0:
                path.append(((k_curr, l_curr), True))
                k_curr, l_curr = visited_cells.pop()

        path.append(((k_curr, l_curr), False))
        if not self.quiet_mode:
            print("Number of moves performed: {}".format(len(path)))
            print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))

        logging.debug('Class DepthFirstBacktracker leaving solve')
        return path
