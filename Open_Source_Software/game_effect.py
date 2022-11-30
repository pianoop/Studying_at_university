import pygame
import os
current_path = os.path.dirname(__file__) 

effect_arrow_imgs = [
    pygame.image.load(os.path.join(current_path, "sprite/arrow01.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow02.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow03.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow04.png"))]


class Effect(pygame.sprite.Sprite):
    def __init__(self, imgs, pos):
        pygame.sprite.pygame.sprite.Sprite(self)
        self.imgs = imgs
        
        self.index = 0
        self.interval = 8
        self.end = self.interval * len(self.imgs)
        self.image = imgs[self.index]
        self.rect  = imgs[self.idx // self.interval].get_rect(center = pos)
        

    def update(self):
        # update를 통해 캐릭터의 이미지가 계속 반복해서 나타나도록 한다.
        if self.index >= self.end:
            self.kill()
        else:
            self.image = self.imgs[self.idx // self.interval]
            self.idx += 1
