from src.maze import Maze
from src.maze_viz import Visualizer
from src.solver import DepthFirstBacktracker, BiDirectional, BreadthFirst


class MazeManager(object):
    def __init__(self):
        self.mazes = []
        self.media_name = ""
        self.quiet_mode = False

    def add_maze(self, row, col, id=0):
        if id is not 0:
            self.mazes.append(Maze(row, col, id))
        else:
            if len(self.mazes) < 1:
                self.mazes.append(Maze(row, col, 0))
            else:
                self.mazes.append(Maze(row, col, len(self.mazes) + 1))

        return self.mazes[-1]

    def add_existing_maze(self, maze, override=True):
        if self.check_matching_id(maze.id) is None:
            if override:
                if len(self.mazes) < 1:
                    maze.id = 0
                else:
                    maze.id = self.mazes.__len__() + 1
        else:
            return False
        self.mazes.append(maze)
        return maze

    def get_maze(self, id):
        for maze in self.mazes:
            if maze.id == id:
                return maze
        print("Unable to locate maze")
        return None

    def get_mazes(self):
        return self.mazes

    def get_maze_count(self):
        return self.mazes.__len__()

    def solve_maze(self, maze_id, method, neighbor_method="fancy"):
        maze = self.get_maze(maze_id)
        if maze is None:
            print("Unable to locate maze. Exiting solver.")
            return None

        if method == "DepthFirstBacktracker":
            solver = DepthFirstBacktracker(maze, neighbor_method, self.quiet_mode)
            maze.solution_path = solver.solve()
        elif method == "BiDirectional":
            solver = BiDirectional(maze, neighbor_method, self.quiet_mode)
            maze.solution_path = solver.solve()
        elif method == "BreadthFirst":
            solver = BreadthFirst(maze, neighbor_method, self.quiet_mode)
            maze.solution_path = solver.solve()

    def show_maze(self, id, cell_size=1):
        vis = Visualizer(self.get_maze(id), cell_size, self.media_name)
        vis.show_maze()

    def show_generation_animation(self, id, cell_size=1):
        vis = Visualizer(self.get_maze(id), cell_size, self.media_name)
        vis.show_generation_animation()

    def show_solution(self, id, cell_size=1):
        vis = Visualizer(self.get_maze(id), cell_size, self.media_name)
        vis.show_maze_solution()

    def show_solution_animation(self, id, cell_size=1):
        vis = Visualizer(self.get_maze(id), cell_size, self.media_name)
        vis.animate_maze_solution()

    def check_matching_id(self, id):
        return next((maze for maze in self.mazes if maze.id == id), None)

    def set_filename(self, filename):
        self.media_name = filename

    def set_quiet_mode(self, enabled):
        self.quiet_mode = enabled
