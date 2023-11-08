import pygame

players = pygame.sprite.Group()

size = 28

num = 0
colors = [
    ((255, 0, 0), "Rouge"),
    ((0, 200, 0), "Vert"),
    ((0, 0, 200), "Bleu"),
    ((240, 240, 0), "Jaune"),
]


def CheckColliders(protected):
    for v in players.sprites():
        if v == protected:
            continue

        if v.position == protected.position:
            v.RestartPos()


def recalculatePosition(cell_size, cell_count, position):
    cells = []
    row, col = 0, 0
    for i in range(cell_count):
        col = (row % 2) * (cell_count - 1)
        for z in range(cell_count):
            cells.append([(cell_size) * (col + 2) - 25, (cell_size) * (row + 2) - 25])
            if row % 2 == 0:
                col += 1
            else:
                col -= 1
        row += 1
    cells.reverse()
    return cells[position][0], cells[position][1]


class Player(pygame.sprite.Sprite):
    def __init__(self, cellSize, cellCount):
        global num
        super().__init__()
        self.image = None
        self.cell_size = cellSize
        self.cell_count = cellCount

        self.originalX, self.originalY = size, 175 + num * (size + 25)
        self.x, self.y = self.originalX, self.originalY
        self.targetX, self.targetY = self.originalX, self.originalY
        self.position = -1
        self.rect = None

        self.playerColor = colors[num]

        players.add(self)
        num += 1

    def update(self, screen):
        dx = (self.targetX - self.x) // 2
        dy = (self.targetY - self.y) // 2
        self.x += dx
        self.y += dy
        pygame.draw.circle(screen, self.playerColor[0], (self.x, self.y), int(size / 2))

    def getColorName(self):
        return self.playerColor[1]

    def RestartPos(self):
        self.position = -1
        self.targetX, self.targetY = self.originalX, self.originalY

    def changePos(self, position):
        if self.position + position >= self.cell_count * self.cell_count:
            self.position = (self.cell_count * self.cell_count - 1) - ((self.position + position) % (self.cell_count * self.cell_count - 1))
        else:
            self.position += position
        self.targetX, self.targetY = recalculatePosition(self.cell_size, self.cell_count, self.position)
        CheckColliders(self)

    def getWon(self):
        return self.position == (self.cell_count * self.cell_count) - 1 and self or None
