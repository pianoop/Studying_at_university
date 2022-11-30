import os
import pygame

current_path = os.path.dirname(__file__) 
img_bar = pygame.image.load(os.path.join(current_path, "HP_bar.png"))
img_slot = pygame.image.load(os.path.join(current_path, "HP_blk.png"))

class Hpbar():
    def __init__(self, hp, pos, pos_blk):
         self.hp = hp
         self.img_bar = img_bar
         self.img_slot = img_slot
         self.pos = pos
         self.pos_blk = pos_blk
         
    def attacked(self, dmg):
        self.hp -= dmg
         
    def get_hp(self):
        return self.hp
    
    def update(self):
        pass
    
    def draw(self, screen):
        screen.blit(self.img_bar, self.pos)
        for h1 in range(self.pos[0] - 1, self.pos[0] + self.hp):
            screen.blit(self.img_slot, (h1+3, self.pos_blk[1]))