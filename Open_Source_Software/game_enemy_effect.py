import pygame
import os
import random
import game_sub as sub
current_path = os.path.dirname(__file__) 


enemy_effect_imgs = \
[
    [
    pygame.image.load(os.path.join(current_path, "sprite/arrow01.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow02.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow03.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow04.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow05.png"))
    ],
    [
    pygame.image.load(os.path.join(current_path, "enemy/Fire_end01.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Fire_end02.png"))
    ],
    [
    pygame.image.load(os.path.join(current_path, "enemy/Ice_end01.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Ice_end02.png"))    
    ]
]


class Enemy_effect(pygame.sprite.Sprite):
    def __init__(self, idx, pos):
        pygame.sprite.Sprite.__init__(self)
        self.imgs = enemy_effect_imgs[idx]
        
        self.idx = idx
        self.pos = pos
        self.idx = 1
        self.interval = 4
        self.end = self.interval * len(self.imgs)
        self.image = self.imgs[self.idx]
        self.rect  = self.imgs[self.idx // self.interval].get_rect(center = pos)
        
    def update(self, Main):
        if self.idx >= self.end:
            self.kill()
        else:
            self.image = self.imgs[self.idx // self.interval]
            self.rect= self.image.get_rect(center = self.pos)
            self.idx += 1