from __future__ import absolute_import
from src.maze_manager import MazeManager

manager = MazeManager()

maze = manager.add_maze(25, 500)

manager.solve_maze(maze.id, "DepthFirstBacktracker")

# manager.show_maze(maze.id)

# manager.show_generation_animation(maze.id)

manager.show_solution_animation(maze.id)

# manager.show_solution(maze.id)
