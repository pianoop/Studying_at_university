import pygame
import os
import random

import game_sub as sub
from game_effect import Effect
current_path = os.path.dirname(__file__) 

boss_imgs = [pygame.ima.load(os.path.join(current_path, "enemy/Boss_PyThony.png"))
    ]

class Boss(pygame.sprite.Sprite):
    def __init__(self, pos):
        pygame.sprite.Sprite.__init__(self)
        self.imgs = boss_imgs
        self.pos = pos
        self.image = self.imgs[0]
        self.rect = self.image. get_rect(center = pos)
        
        self.range = 700
        self.speed = 2
        self.dmg = [10, 15]
        self.hp = [1000, 1200]  # 양쪽 머리 따로
        
    def update(self, Main):
        self.move()
        
    def move(self, Main):
        #TODO 움직임 sprite 구현
        
        if self.pos[0] > self.range:
            self.pos = self.pos[0] - self.speed, self.pos[1]
        else:
            self.attack(Main)
            
    def attack(self, Main):
        #TODO
        Main.castle.attacked(self.dmg)
        
    
        