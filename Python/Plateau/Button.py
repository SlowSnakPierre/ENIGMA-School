import pygame
import pygame.gfxdraw

buttons = pygame.sprite.Group()


class Button(pygame.sprite.Sprite):
    def __init__(self, position, text, size,
                 colors="white on blue",
                 hover_colors="red on green",
                 style=1,
                 borderc=(255, 255, 255),
                 command=lambda: print("No command activated for this button")):

        super().__init__()
        self.text_render = None
        self.image = None

        self.text = text

        self.command = command
        self.colors = colors
        self.original_colors = colors
        self.fg, self.bg = self.colors.split(" on ")

        if hover_colors == "red on green":
            self.hover_colors = f"{self.bg} on {self.fg}"
        else:
            self.hover_colors = hover_colors

        self.style = style
        self.borderc = borderc  # for the style2
        self.font = pygame.font.SysFont("Arial", size)
        self.render(self.text)
        self.x, self.y, self.w, self.h = self.text_render.get_rect()
        self.x, self.y = position
        self.rect = pygame.Rect(self.x, self.y, 500, self.h)
        self.position = position
        self.pressed = 1
        buttons.add(self)

    def render(self, text):
        self.text_render = self.font.render(text, 1, self.fg)
        self.image = self.text_render

    def update(self, screen):
        self.fg, self.bg = self.colors.split(" on ")
        if self.style == 1:
            self.draw_button1(screen)
        elif self.style == 2:
            self.draw_button2(screen)
        if self.command is not None:
            self.hover()
            self.click()

    def draw_button1(self, screen):
        # horizontal up
        pygame.draw.line(screen, (150, 150, 150), (self.x, self.y), (self.x + self.w, self.y), 5)
        pygame.draw.line(screen, (150, 150, 150), (self.x, self.y - 2), (self.x, self.y + self.h), 5)
        # horizontal down
        pygame.draw.line(screen, (50, 50, 50), (self.x, self.y + self.h), (self.x + self.w, self.y + self.h), 5)
        pygame.draw.line(screen, (50, 50, 50), (self.x + self.w, self.y + self.h), [self.x + self.w, self.y], 5)
        # background of the button
        pygame.draw.rect(screen, self.bg, (self.x, self.y, self.w, self.h))

    def draw_button2(self, screen):
        pygame.draw.rect(screen, self.bg, (self.x - 50, self.y, 500, self.h))
        pygame.gfxdraw.rectangle(screen, (self.x - 50, self.y, 500, self.h), self.borderc)

    def check_collision(self):
        if self.rect.collidepoint(pygame.mouse.get_pos()):
            self.colors = self.hover_colors
        else:
            self.colors = self.original_colors

    def hover(self):
        self.check_collision()

    def click(self):
        if self.rect.collidepoint(pygame.mouse.get_pos()):
            if pygame.mouse.get_pressed()[0] and self.pressed == 1:
                self.command()
                self.pressed = 0
            if pygame.mouse.get_pressed() == (0, 0, 0):
                self.pressed = 1
