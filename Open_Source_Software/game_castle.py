import os
import pygame
from game_hp import Hpbar


class Castle():
    def __init__(self, castle_hp,  castle_hp_pos, castle_hp_blk_pos):
        self.hpbar = Hpbar(castle_hp, castle_hp_pos, castle_hp_blk_pos)
        
    def attacked(self, dmg):
        self.hpbar.attacked(dmg)
        if(self.hpbar.get_hp() <= 0):
            game_state = 3
            
    def update(self):
        self.hpbar.update()
        
    def draw(self,screen):
        self.hpbar.draw(screen)