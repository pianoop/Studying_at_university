import os
import pygame
import math

import game_sub as sub
from game_projectile import Projectile
current_path = os.path.dirname(__file__) 

angle0 = -180 / math.pi

weapon_imgs = [
    pygame.image.load(os.path.join(current_path, "Bow.png")),
    pygame.image.load(os.path.join(current_path, "Cannon.png")),
    pygame.image.load(os.path.join(current_path, "Wand.png"))]
weapon_poses = [(160, 320), (160, 320), (160, 320)]

class Weapons():
    def __init__(self):
        super().__init__()
        self.imgs = weapon_imgs
        self.poses = weapon_poses
        self.rct = []
        for idx, img in enumerate(self.imgs):
            self.rct.append(img.get_rect(center = self.poses[idx]))
        
        self.now    = 0  # 시작 기본 무기 bow
        self.nowMax = 0  # 무기 해금 관련
        self.image  = self.imgs[self.now]
        self.rect   = self.imgs[self.now].get_rect(center = self.poses[self.now])
        
    def draw(self, screen):
        screen.blit(self.image, self.rect)
        
    def update(self):
        self.rotate()
        
    def rotate(self):
        angle = angle0 * sub.calc_angle(self.rct[self.now])
        self.image = pygame.transform.rotate(self.imgs[self.now], int(angle))
        self.rect = self.image.get_rect(center=self.poses[self.now])
    
    def swap(self, weapon):
        self.now = weapon
        self.image = self.imgs[self.now]
        self.rect  = self.rct[self.now]

    def attack(self, Main):
            if self.now == 0:
                self.attack_bow(Main)
            elif self.now == 1:
                self.attack_cannon(Main)
            elif self.now == 2:
                self.attack_wand(Main)
            
    def attack_bow(self, Main):
        # TODO 쿨타임 관련 계산
        angle1 = sub.calc_angle(self.rct[0])
        angle = angle0 * angle1
        dpos = (math.cos(angle1) * self.speed[0], math.sin(angle1) * self.speed[0])
        projectile = Projectile(0, dpos, angle)
        Main.fractile_group.add(projectile)

    def attack_cannon(self, Main):
        pass

    def attack_wand(self, Main):
        pass