from __future__ import absolute_import
from src.maze_manager import MazeManager
from src.maze import Maze

manager = MazeManager()

maze = manager.add_maze(10, 10)

maze2 = Maze(10, 10)
maze2 = manager.add_existing_maze(maze2)

maze_binTree = Maze(10, 10, algorithm="bin_tree")
maze_binTree = manager.add_existing_maze(maze_binTree)

try:
    manager.solve_maze(maze.id, "DepthFirstBacktracker")
except: pass

try:
    manager.set_filename("myFileName")
except: pass

try:
    manager.show_maze(maze.id)
except: pass

try:
    manager.show_generation_animation(maze.id)
except: pass

try:
    manager.show_solution_animation(maze.id)
except: pass

try:
    manager.show_solution(maze.id)
except: pass
