import os
import pygame
import math

import game_sub as sub
from game_effect import Effect
from game_projectile import Projectile
current_path = os.path.dirname(__file__)


weapon_imgs = [
    pygame.image.load(os.path.join(current_path, "Bow.png")),
    pygame.image.load(os.path.join(current_path, "Cannon.png")),
    pygame.image.load(os.path.join(current_path, "Bow2.png")),
    pygame.image.load(os.path.join(current_path, "Cane.png"))]
weapon_poses = [(60, 380), (30, 380), (60, 380), (60, 380)]
weapon_speeds= [25, 25, 30, 100]


class Weapons():
    def __init__(self):
        super().__init__()
        self.imgs = weapon_imgs
        self.poses = weapon_poses
        self.speed = weapon_speeds
        self.rct = []
        for idx, img in enumerate(self.imgs):
            self.rct.append(img.get_rect(center = self.poses[idx]))
        
        self.now    = 0  # 시작 기본 무기 bow
        self.Max = 0  # 무기 해금 관련
        self.image  = self.imgs[self.now]
        self.rect   = self.imgs[self.now].get_rect(center = self.poses[self.now])
        
    def draw(self, screen):
        screen.blit(self.image, self.rect)
        
    def update(self):
        self.rotate()
        
    def rotate(self):
        angle = sub.calc_angle(self.rct[self.now])
        self.image = pygame.transform.rotate(self.imgs[self.now], -int(math.degrees(angle)))
        self.rect = self.image.get_rect(center=self.poses[self.now])
    
    def keydown(self, key):
        if key == pygame.K_1:
            self.weapon.swap(0)
        elif key == pygame.K_2:
            if self.Max >= 1:
                self.weapon.swap(1)
        elif key == pygame.K_3:
            if self.Max >= 2:
                self.weapon.swap(2)
        elif key == pygame.K_4:
            if self.Max >= 3:
                self.weapon.swap(3)
    
    def swap(self, weapon):
        self.now = weapon
        self.image = self.imgs[self.now]
        self.rect  = self.rct[self.now]

    def attack(self, Main):
            if self.now == 0:
                self.attack_bow(Main)
            elif self.now == 1:
                self.attack_cannon(Main)
            if self.now == 2:
                self.attack_bow(Main)
            elif self.now == 3:
                self.attack_wand(Main)

    def attack_bow(self, Main):
        # TODO 쿨타임 관련 계산
        angle = sub.calc_angle(self.rct[self.now])
        dpos = (math.sin(angle) * self.speed[self.now], -math.cos(angle) * self.speed[self.now])
        projectile = Projectile(self.now, dpos, angle)
        Main.projectile_group.add(projectile)

    def attack_cannon(self, Main):
        angle = sub.calc_angle(self.rct[self.now])
        dpos = (math.sin(angle) * self.speed[self.now], -math.cos(angle) * self.speed[self.now])
        projectile = Projectile(self.now, dpos, angle)
        Main.projectile_group.add(projectile)

    def attack_wand(self, Main):
        eft = Effect(self.now, pygame.mouse.get_pos())
        Main.effect_group.add(eft)
        # TODO 임시projectile 소환