import random
from Label import *

bgC = (255,255,255)
bgF = (0,0,0)
size = 150

rows = [200, 250, 300]
cols = [575, 625, 675]

class Dice:
    def __init__(self, sides, cell_count):
        self.sides = sides
        self.number = 0
        self.label = None
        self.rows = [((cell_count * 60)/5)*2, ((cell_count * 60)/5)*2 + 50, ((cell_count * 60)/5)*2 + 100]
        self.cols = [(cell_count * 60) + 25 + (25/2), (cell_count * 60) + 75 + (25/2), (cell_count * 60) + 125 + (25/2)]

    def roll(self):
        self.number = random.randint(1, self.sides)
        return self.number

    def updateRoll(self, screen):
        if self.number == 0:
            return

        if not self.label:
            self.label = Label(f'+ {self.number} Cases !', 24, self.cols[0], self.rows[2]+50, "red")
        else:
            self.label.set(f'+ {self.number} Cases !', "red")

        if self.number % 2 == 1:
            pygame.draw.circle(screen, bgF, (self.cols[1],self.rows[1]), size//10)
        if self.number != 1:
            pygame.draw.circle(screen, bgF, (self.cols[0],self.rows[0]), size//10)
            pygame.draw.circle(screen, bgF, (self.cols[2],self.rows[2]), size//10)
        if self.number >= 4:
            pygame.draw.circle(screen, bgF, (self.cols[2],self.rows[0]), size//10)
            pygame.draw.circle(screen, bgF, (self.cols[0],self.rows[2]), size//10)
        if self.number == 6:
            pygame.draw.circle(screen, bgF, (self.cols[0], self.rows[1]), size // 10)
            pygame.draw.circle(screen, bgF, (self.cols[2], self.rows[1]), size // 10)