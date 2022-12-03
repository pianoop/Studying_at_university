import os
import pygame
import game_sub as sub
from game_enemy_effect import Enemy_effect
import math
current_path = os.path.dirname(__file__) 

enemy_projectile_imgs = \
[
    pygame.image.load(os.path.join(current_path, "enemy/Fire01.png"))
]
enemy_projectile_dmg    = [20, 40, 20, 30, 50]
enemy_projectile_speed  = [14, 20, 20, 20, 20]
gravity                 = 1

class Projectile(pygame.sprite.Sprite):
    def __init__(self, idx, pos):
        pygame.sprite.Sprite.__init__(self)
        self.idx = idx    
        self.dmg   = enemy_projectile_dmg[idx]    
        self.pos = pos
        self.image = enemy_projectile_imgs[idx]
        self.rect = self.image.get_rect(center=self.pos)

    def update(self, Main):
        self.move(Main)

    def move(self, Main):
        if self.pos[0] <= 255:
            if self.idx == 0: #fireball
                eft = Enemy_effect(1, self.pos)
                Main.effect_group.add(eft)
                
            Main.castle.attacked(self.dmg)
            self.kill()
        else:
            self.pos = self.pos[0] - self.speed, self.pos[1] 
            self.rect= self.image.get_rect(center = self.pos)
            
    
        
    