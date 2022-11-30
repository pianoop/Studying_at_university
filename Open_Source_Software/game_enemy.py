import pygame
import os
import random
current_path = os.path.dirname(__file__) 

enemy_imgs = [
    pygame.image.load(os.path.join(current_path, "Enemy1.png")),
    pygame.image.load(os.path.join(current_path, "Enemy2.png")),
    pygame.image.load(os.path.join(current_path, "Enemy3.png")),
    pygame.image.load(os.path.join(current_path, "Enemy4.png")),
    pygame.image.load(os.path.join(current_path, "Enemy5.png"))]
enemy_poses = [(1180, (550, 680)), (1180, (550, 680)), (1180, (550, 680)), (1180, (200, 300)), (1180, (350, 500))]
enemy_speeds= [5, 10, 3, 7, 7]
enemy_dmg   = [4, 8, 5, 4, 10]
enemy_range = [260, 260, 780, 260, 260]
enemy_hp   =  [50, 100, 40, 80, 50]

class Enemy(pygame.sprite.Sprite):
    def __init__(self, enemy_idx):
        pygame.sprite.Sprite.__init__(self)
        self.image = enemy_imgs[enemy_idx]
        
        posx, posy = enemy_poses[enemy_idx]
        self.pos = (posx, random(posy))
        self.speed = enemy_speeds[enemy_idx]
        self.damage = enemy_dmg[enemy_idx]
        self.range = enemy_range[enemy_idx]
        self.hp = enemy_hp[enemy_idx]
        
        self.rect = self.image.get_rect(center = self.pos)
    
    def update(self, Main):
        self.move_attack(Main)
    
    def move_attack(self, Main):
        if self.pos[0] <= self.range:
            self.attack(Main)
        else:
            self.pos = self.pos[0] - self.speed, self.pos[1]
            self.rect = self.image.get_rect(center = self.pos)
        # TODO 충돌처리도 동시에?
    
    def attack(self, Main):
        Main.castle.attacked(self.dmg)
        
    def damaged(self, Main, dmg):
        self.hp -= dmg
        if self.hp <= 0:
            # 죽는 effect 추가
            self.kill()

        # TODO 공격 모션 추가?
