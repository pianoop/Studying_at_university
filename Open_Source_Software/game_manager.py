import os
import pygame
import game_sub as sub

class Manager():
    def __init__(self) :
        self.time = 0
        self.stage_data = range(30, 1000, 50)
        
        
        
    def process(self, Main):
        for i in self.stage_data:
            if self.time == i:
                sub.enemy_gen(Main)
        self.time += 1
                
                
                