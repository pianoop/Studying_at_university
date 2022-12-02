import pygame
import os
import random

import game_sub as sub
from game_effect import Effect
current_path = os.path.dirname(__file__) 

enemy_imgs = [[
    pygame.image.load(os.path.join(current_path, "enemy/Slime001.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Slime002.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Slime003.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Slime004.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Slime005.png")),
    pygame.image.load(os.path.join(current_path, "enemy/Slime006.png"))],
    [
    pygame.image.load(os.path.join(current_path, "Enemy2.png"))],
    [
    pygame.image.load(os.path.join(current_path, "Enemy3.png"))],
    [
    pygame.image.load(os.path.join(current_path, "Enemy4.png"))],
    [
    pygame.image.load(os.path.join(current_path, "Enemy5.png"))
    ]
]
enemy_poses = [(1180, (550, 680)), (1180, (550, 680)), (1180, (550, 680)), (1180, (200, 300)), (1180, (350, 500))]
enemy_speeds= [5, 10, 3, 7, 7]
enemy_dmg   = [4, 8, 5, 4, 10]
enemy_range = [260, 260, 780, 260, 260]
enemy_hp   =  [50, 100, 40, 80, 50]

class Enemy(pygame.sprite.Sprite):
    def __init__(self, idx):
        pygame.sprite.Sprite.__init__(self)
        self.imgs = enemy_imgs[idx]
        self.idx = 1
        self.interval = 3
        self.end = self.interval * len(self.imgs)
        
        self.image = self.imgs[0]
        posx, (posy1, posy2) = enemy_poses[idx]
        self.pos = (posx, random.randint(posy1, posy2))
        self.speed = enemy_speeds[idx]
        self.damage = enemy_dmg[idx]
        self.dmg = enemy_dmg[idx]
        self.range = enemy_range[idx]
        self.hp = enemy_hp[idx]
        
        self.rect = self.image.get_rect(center = self.pos)

    def update(self, Main):
        self.move_attack(Main)
        self.check_colider(Main)
    
    def move_attack(self, Main):
        if self.pos[0] <= self.range:
            self.attack(Main)
        else:
            self.pos = self.pos[0] - self.speed, self.pos[1]
            self.image = self.imgs[self.idx // self.interval]
            self.rect= self.image.get_rect(center = self.pos)
            self.idx += 1
            if self.idx >= self.end:
                self.idx = 1

    def attack(self, Main):
        Main.castle.attacked(self.dmg)

    def check_colider(self, Main):
        projectile = pygame.sprite.spritecollide(self, Main.projectile_group, False, pygame.sprite.collide_mask)
        if projectile:
            if projectile[0].idx == 0:
                self.attacked(projectile[0].dmg)
                eft = Effect(projectile[0].idx, projectile[0].pos)
                Main.effect_group.add(eft)
                projectile[0].kill()
            elif projectile[0].idx == 1:
                self.attacked(projectile[0].dmg)
                # TODO projectile 소환
                eft = Effect(projectile[0].idx, projectile[0].pos)
                Main.effect_group.add(eft)
                projectile[0].kill()
        
        
    def attacked(self, dmg):
        self.hp -= dmg
        if self.hp <= 0:
            # 죽는 effect 추가
            self.kill()

        # TODO 공격 모션 추가?
