from __future__ import absolute_import
from src.maze_manager import MazeManager
from src.maze import Maze

manager = MazeManager()
maze_using_btree = Maze(15, 15, algorithm="bin_tree")

maze_using_btree = manager.add_existing_maze(maze_using_btree)

manager.show_maze(maze_using_btree.id)

manager.show_generation_animation(maze_using_btree.id)

manager.show_solution_animation(maze_using_btree.id)