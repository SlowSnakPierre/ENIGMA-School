import matplotlib.pyplot as plt
from matplotlib import animation
import logging

logging.basicConfig(level=logging.DEBUG)


class Visualizer(object):
    def __init__(self, maze, cell_size, media_filename):
        self.maze = maze
        self.cell_size = cell_size
        self.height = maze.num_rows * cell_size
        self.width = maze.num_cols * cell_size
        self.ax = None
        self.lines = dict()
        self.squares = dict()
        self.media_filename = media_filename

    def set_media_filename(self, filename):
        self.media_filename = filename

    def show_maze(self):
        fig = self.configure_plot()

        self.plot_walls()

        plt.show()

        if self.media_filename:
            fig.savefig("{}{}.png".format(self.media_filename, "_generation"), frameon=None)

    def plot_walls(self):
        for i in range(self.maze.num_rows):
            for j in range(self.maze.num_cols):
                if self.maze.initial_grid[i][j].is_entry_exit == "entry":
                    self.ax.text(j * self.cell_size, i * self.cell_size, "START", fontsize=7, weight="bold")
                elif self.maze.initial_grid[i][j].is_entry_exit == "exit":
                    self.ax.text(j * self.cell_size, i * self.cell_size, "END", fontsize=7, weight="bold")
                if self.maze.initial_grid[i][j].walls["top"]:
                    self.ax.plot([j * self.cell_size, (j + 1) * self.cell_size], [i * self.cell_size, i * self.cell_size], color="k")
                if self.maze.initial_grid[i][j].walls["right"]:
                    self.ax.plot([(j + 1) * self.cell_size, (j + 1) * self.cell_size], [i * self.cell_size, (i + 1) * self.cell_size], color="k")
                if self.maze.initial_grid[i][j].walls["bottom"]:
                    self.ax.plot([(j + 1) * self.cell_size, j * self.cell_size], [(i + 1) * self.cell_size, (i + 1) * self.cell_size], color="k")
                if self.maze.initial_grid[i][j].walls["left"]:
                    self.ax.plot([j * self.cell_size, j * self.cell_size], [(i + 1) * self.cell_size, i * self.cell_size], color="k")

    def configure_plot(self):
        fig = plt.figure(figsize=(7, 7 * self.maze.num_rows / self.maze.num_cols))

        self.ax = plt.axes()

        self.ax.set_aspect("equal")

        self.ax.axes.get_xaxis().set_visible(False)
        self.ax.axes.get_yaxis().set_visible(False)

        title_box = self.ax.text(0, self.maze.num_rows + self.cell_size + 0.1, r"{}$\times${}".format(self.maze.num_rows, self.maze.num_cols), bbox={"facecolor": "gray", "alpha": 0.5, "pad": 4}, fontname="serif", fontsize=15)

        return fig

    def show_maze_solution(self):
        fig = self.configure_plot()

        self.plot_walls()

        list_of_backtrackers = [path_element[0] for path_element in self.maze.solution_path if path_element[1]]

        circle_num = 0

        self.ax.add_patch(plt.Circle(((self.maze.solution_path[0][0][1] + 0.5) * self.cell_size, (self.maze.solution_path[0][0][0] + 0.5) * self.cell_size), 0.2 * self.cell_size, fc=(0, circle_num / (len(self.maze.solution_path) - 2 * len(list_of_backtrackers)), 0), alpha=0.4))

        for i in range(1, self.maze.solution_path.__len__()):
            if self.maze.solution_path[i][0] not in list_of_backtrackers and self.maze.solution_path[i - 1][0] not in list_of_backtrackers:
                circle_num += 1
                self.ax.add_patch(plt.Circle(((self.maze.solution_path[i][0][1] + 0.5) * self.cell_size, (self.maze.solution_path[i][0][0] + 0.5) * self.cell_size), 0.2 * self.cell_size, fc=(0, circle_num / (len(self.maze.solution_path) - 2 * len(list_of_backtrackers)), 0), alpha=0.4))

        plt.show()

        if self.media_filename:
            fig.savefig("{}{}.png".format(self.media_filename, "_solution"), frameon=None)

    def show_generation_animation(self):
        fig = self.configure_plot()

        indicator = plt.Rectangle((self.maze.generation_path[0][0] * self.cell_size, self.maze.generation_path[0][1] * self.cell_size), self.cell_size, self.cell_size, fc="purple", alpha=0.6)

        self.ax.add_patch(indicator)

        color_walls = "k"
        for i in range(self.maze.num_rows):
            for j in range(self.maze.num_cols):
                self.lines["{},{}: right".format(i, j)] = self.ax.plot([(j + 1) * self.cell_size, (j + 1) * self.cell_size], [i * self.cell_size, (i + 1) * self.cell_size], linewidth=2, color=color_walls)[0]
                self.lines["{},{}: bottom".format(i, j)] = self.ax.plot([(j + 1) * self.cell_size, j * self.cell_size], [(i + 1) * self.cell_size, (i + 1) * self.cell_size], linewidth=2, color=color_walls)[0]

                self.squares["{},{}".format(i, j)] = plt.Rectangle((j * self.cell_size, i * self.cell_size), self.cell_size, self.cell_size, fc="red", alpha=0.4)
                self.ax.add_patch(self.squares["{},{}".format(i, j)])

        color_boundary = "k"
        self.ax.plot([0, self.width], [self.height, self.height], linewidth=2, color=color_boundary)
        self.ax.plot([self.width, self.width], [self.height, 0], linewidth=2, color=color_boundary)
        self.ax.plot([self.width, 0], [0, 0], linewidth=2, color=color_boundary)
        self.ax.plot([0, 0], [0, self.height], linewidth=2, color=color_boundary)

        def animate(frame):
            animate_walls(frame)
            animate_squares(frame)
            animate_indicator(frame)
            self.ax.set_title("Step: {}".format(frame + 1), fontname="serif", fontsize=19)
            return []

        def animate_walls(frame):
            if frame > 0:
                self.maze.grid[self.maze.generation_path[frame - 1][0]][self.maze.generation_path[frame - 1][1]].remove_walls(self.maze.generation_path[frame][0], self.maze.generation_path[frame][1])

                self.maze.grid[self.maze.generation_path[frame][0]][self.maze.generation_path[frame][1]].remove_walls(self.maze.generation_path[frame - 1][0], self.maze.generation_path[frame - 1][1])

                current_cell = self.maze.grid[self.maze.generation_path[frame - 1][0]][self.maze.generation_path[frame - 1][1]]
                next_cell = self.maze.grid[self.maze.generation_path[frame][0]][self.maze.generation_path[frame][1]]

                for wall_key in ["right", "bottom"]:
                    if current_cell.walls[wall_key] is False:
                        self.lines["{},{}: {}".format(current_cell.row, current_cell.col, wall_key)].set_visible(False)
                    if next_cell.walls[wall_key] is False:
                        self.lines["{},{}: {}".format(next_cell.row, next_cell.col, wall_key)].set_visible(False)

        def animate_squares(frame):
            self.squares["{},{}".format(self.maze.generation_path[frame][0], self.maze.generation_path[frame][1])].set_visible(False)
            return []

        def animate_indicator(frame):
            indicator.set_xy((self.maze.generation_path[frame][1] * self.cell_size, self.maze.generation_path[frame][0] * self.cell_size))
            return []

        logging.debug("Creating generation animation")
        anim = animation.FuncAnimation(fig, animate, frames=self.maze.generation_path.__len__(), interval=100, blit=True, repeat=False)

        logging.debug("Finished creating the generation animation")

        plt.show()

        if self.media_filename:
            print("Saving generation animation. This may take a minute....")
            mpeg_writer = animation.FFMpegWriter(fps=24, bitrate=1000, codec="libx264", extra_args=["-pix_fmt", "yuv420p"])
            anim.save("{}{}{}x{}.mp4".format(self.media_filename, "_generation_", self.maze.num_rows, self.maze.num_cols), writer=mpeg_writer)

    def add_path(self):
        color_walls = "k"
        for i in range(self.maze.num_rows):
            for j in range(self.maze.num_cols):
                if self.maze.initial_grid[i][j].is_entry_exit == "entry":
                    self.ax.text(j * self.cell_size, i * self.cell_size, "START", fontsize=7, weight="bold")
                elif self.maze.initial_grid[i][j].is_entry_exit == "exit":
                    self.ax.text(j * self.cell_size, i * self.cell_size, "END", fontsize=7, weight="bold")

                if self.maze.initial_grid[i][j].walls["top"]:
                    self.lines["{},{}: top".format(i, j)] = self.ax.plot([j * self.cell_size, (j + 1) * self.cell_size], [i * self.cell_size, i * self.cell_size], linewidth=2, color=color_walls)[0]
                if self.maze.initial_grid[i][j].walls["right"]:
                    self.lines["{},{}: right".format(i, j)] = self.ax.plot([(j + 1) * self.cell_size, (j + 1) * self.cell_size], [i * self.cell_size, (i + 1) * self.cell_size], linewidth=2, color=color_walls)[0]
                if self.maze.initial_grid[i][j].walls["bottom"]:
                    self.lines["{},{}: bottom".format(i, j)] = self.ax.plot([(j + 1) * self.cell_size, j * self.cell_size], [(i + 1) * self.cell_size, (i + 1) * self.cell_size], linewidth=2, color=color_walls)[0]
                if self.maze.initial_grid[i][j].walls["left"]:
                    self.lines["{},{}: left".format(i, j)] = self.ax.plot([j * self.cell_size, j * self.cell_size], [(i + 1) * self.cell_size, i * self.cell_size], linewidth=2, color=color_walls)[0]
                self.squares["{},{}".format(i, j)] = plt.Rectangle((j * self.cell_size, i * self.cell_size), self.cell_size, self.cell_size, fc="red", alpha=0.4, visible=False)
                self.ax.add_patch(self.squares["{},{}".format(i, j)])

    def animate_maze_solution(self):
        fig = self.configure_plot()

        indicator = plt.Rectangle((self.maze.solution_path[0][0][0] * self.cell_size, self.maze.solution_path[0][0][1] * self.cell_size), self.cell_size, self.cell_size, fc="purple", alpha=0.6)
        self.ax.add_patch(indicator)

        self.add_path()

        def animate_squares(frame):
            if frame > 0:
                if self.maze.solution_path[frame - 1][1]:
                    self.squares["{},{}".format(self.maze.solution_path[frame - 1][0][0], self.maze.solution_path[frame - 1][0][1])].set_facecolor("orange")

                self.squares["{},{}".format(self.maze.solution_path[frame - 1][0][0], self.maze.solution_path[frame - 1][0][1])].set_visible(True)
                self.squares["{},{}".format(self.maze.solution_path[frame][0][0], self.maze.solution_path[frame][0][1])].set_visible(False)
            return []

        def animate_indicator(frame):
            indicator.set_xy((self.maze.solution_path[frame][0][1] * self.cell_size, self.maze.solution_path[frame][0][0] * self.cell_size))
            return []

        def animate(frame):
            animate_squares(frame)
            animate_indicator(frame)
            self.ax.set_title("Step: {}".format(frame + 1), fontname="serif", fontsize=19)
            return []

        logging.debug("Creating solution animation")
        anim = animation.FuncAnimation(fig, animate, frames=self.maze.solution_path.__len__(), interval=100, blit=True, repeat=False)
        logging.debug("Finished creating solution animation")

        plt.show()

        if self.media_filename:
            print("Saving solution animation. This may take a minute....")
            mpeg_writer = animation.FFMpegWriter(fps=24, bitrate=1000, codec="libx264", extra_args=["-pix_fmt", "yuv420p"])
            anim.save("{}{}{}x{}.mp4".format(self.media_filename, "_solution_", self.maze.num_rows, self.maze.num_cols), writer=mpeg_writer)
