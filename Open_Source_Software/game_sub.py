import os
import pygame
import math
import random
from game_enemy import Enemy

screen_width        =   1280
screen_height       =   720

def range_check(pos):
    return (pos[0] >=0) and (pos[0] <= screen_width) and (pos[1] >= 0) and (pos[1] <= screen_height)

def calc_angle(rct):
        mouse_x, mouse_y = pygame.mouse.get_pos()
        return math.atan2(mouse_x - rct.centerx, mouse_y - rct.centery)
    
def enemy_gen(Main):
    enemy = Enemy(random(0, 5))
    Main.enemy_group.add(enemy)