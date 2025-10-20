import pygame
pygame.init()
screen = pygame.display.set_mode((640, 480))
clock = pygame.time.Clock()

def main():
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill((0,0,0))
        pygame.draw.circle(screen, (255,0,0), (320,240), 50)  # пример отрисовки
        pygame.display.flip()

        clock.tick(60)
main()