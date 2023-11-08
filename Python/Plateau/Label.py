import pygame

labels = []

class Label:
    def __init__(self, text, size, x, y, color="black"):
        self.font = pygame.font.SysFont("Arial", size)
        self.image = self.font.render(text, 1, color)
        self.x, self.y = x, y
        _, _, w, h = self.image.get_rect()
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        labels.append(self)

    def set(self, text, color="black"):
        self.text = text
        self.image = self.font.render(text, 1, color)

    def changefont(self, font, size, color="white"):
        self.font = pygame.font.SysFont(font, size)
        self.set(self.text, color)

    def draw(self, screen):
        screen.blit(self.image, (self.rect))

def show_labels(screen):
    for lab in labels:
        lab.draw(screen)