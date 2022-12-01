import pygame
import os
import random

import game_sub as sub
from game_effect import Effect
current_path = os.path.dirname(__file__) 

enemy_imgs = [
    pygame.image.load(os.path.join(current_path, "Enemy1.png")).set_colorkey((0,0,0)),
    pygame.image.load(os.path.join(current_path, "Enemy2.png")).set_colorkey((0,0,0)),
    pygame.image.load(os.path.join(current_path, "Enemy3.png")).set_colorkey((0,0,0)),
    pygame.image.load(os.path.join(current_path, "Enemy4.png")).set_colorkey((0,0,0)),
    pygame.image.load(os.path.join(current_path, "Enemy5.png")).set_colorkey((0,0,0))]
enemy_poses = [(1180, (550, 680)), (1180, (550, 680)), (1180, (550, 680)), (1180, (200, 300)), (1180, (350, 500))]
enemy_speeds= [5, 10, 3, 7, 7]
enemy_dmg   = [4, 8, 5, 4, 10]
enemy_range = [260, 260, 780, 260, 260]
enemy_hp   =  [100, 200, 80, 160, 100]

class Enemy(pygame.sprite.Sprite):
    def __init__(self, enemy_idx):
        pygame.sprite.Sprite.__init__(self)
        self.image = enemy_imgs[enemy_idx]

        posx, (posy1, posy2) = enemy_poses[enemy_idx]
        self.pos = (posx, random.randint(posy1, posy2))
        self.speed = enemy_speeds[enemy_idx]
        self.damage = enemy_dmg[enemy_idx]
        self.dmg = enemy_dmg[enemy_idx]
        self.range = enemy_range[enemy_idx]
        self.hp = enemy_hp[enemy_idx]
        
        self.rect = self.image.get_rect(center = self.pos)

    def update(self, Main):
        self.move_attack(Main)
        self.check_colider(Main)
    
    def move_attack(self, Main):
        if self.pos[0] <= self.range:
            self.attack(Main)
        else:
            self.pos = self.pos[0] - self.speed, self.pos[1]
            self.rect = self.image.get_rect(center = self.pos)
        # TODO 충돌처리도 동시에?

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
