from Button import *
from Dice import *
from Label import *
from Player import *

white, black, grey = (255, 255, 255), (0, 0, 0), (200, 200, 200)
current_player = 1

Players = 4
n = 0


def on_cleanup():
    pygame.quit()


class App:
    def __init__(self):
        self.auto_roll = None
        self._running = True
        self._display_surf = None
        self.cell_size = 50
        self.cell_count = 10
        self.dice_faces = 6
        self.size = self.weight, self.height = (self.cell_count * 60) + 250, (self.cell_count * 60)
        self.roll_dice = None
        self.current_player_label = None
        self.clock = None
        self.dice = None
        self.player_list = []
        self.auto_run = False
        self.won = None

    def on_init(self):
        pygame.init()
        pygame.display.set_icon(pygame.image.load("icon.png"))
        pygame.display.set_caption("Jeu de l'oie")
        self._display_surf = pygame.display.set_mode(self.size, pygame.HWSURFACE | pygame.DOUBLEBUF)
        self.dice = Dice(self.dice_faces, self.cell_count)
        self.roll_dice = Button(((self.cell_count * 60) + 25, ((self.cell_count * 60) / 5) * 4), " Lancer le dé ", 28,
                                "black on white", "black on lightgrey", 1, (0, 0, 0),
                                command=lambda: self.play())
        self.auto_roll = Button(((self.cell_count * 60) + 25, ((self.cell_count * 60) / 5) * 4.5), 'Automatique', 28,
                                "black on white", "black on lightgrey", 1, (0, 0, 0),
                                command=lambda: self.autoRun())
        self.current_player_label = Label("Au tour du Rouge de jouer !", 24, (self.cell_count * 60) - 25,
                                          (self.cell_count * 60) / 5)
        self.clock = pygame.time.Clock()
        self._running = True
        for i in range(Players):
            self.player_list.append(Player(self.cell_size, self.cell_count))

    def play(self):
        if self.won is None:
            global current_player
            self.player_list[current_player - 1].changePos(self.dice.roll())
            self.won = self.player_list[current_player - 1].getWon()
            if self.won is None:
                current_player = current_player >= Players and 1 or current_player + 1
                self.current_player_label.set("Au tour du " + (self.player_list[current_player - 1].getColorName()) + " de jouer !")
            else:
                self.current_player_label.set("Le pion " + (self.player_list[current_player - 1].getColorName()) + " a gagné la partie !")

    def autoRun(self):
        self.auto_run = not self.auto_run

    def on_event(self, event):
        if event.type == pygame.QUIT:
            self._running = False

    def on_loop(self):
        global n
        if self.auto_run and self.won is None:
            if n%20 == 0:
                n = 0
                self.play()
            n += 1

    def render_board(self):
        self._display_surf.fill(grey)
        cnt = 0
        for i in range(1, self.cell_count + 1):
            for z in range(1, self.cell_count + 1):
                if cnt % 2 == 0:
                    pygame.draw.rect(self._display_surf, white, [self.cell_size * z, self.cell_size * i, self.cell_size, self.cell_size])
                else:
                    pygame.draw.rect(self._display_surf, black, [self.cell_size * z, self.cell_size * i, self.cell_size, self.cell_size])
                cnt += 1
            cnt -= 1

    def on_render(self):
        self.render_board()

        self.dice.updateRoll(self._display_surf)
        show_labels(self._display_surf)

        players.update(self._display_surf)
        buttons.update(self._display_surf)
        buttons.draw(self._display_surf)

        pygame.display.update()

    def on_execute(self):
        self.on_init()

        while self._running:
            for event in pygame.event.get():
                self.on_event(event)

            self.on_loop()
            self.on_render()
            self.clock.tick(60)

        on_cleanup()


if __name__ == "__main__":
    theApp = App()
    theApp.on_execute()