import pygame
import os
import random
from game_enemy_effect import Enemy_effect

current_path = os.path.dirname(__file__) 

enemy_imgs = [[
    pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime001.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime002.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime003.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime004.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime005.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime006.png"))
    ],
    [
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (1).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (2).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (3).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (4).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (5).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (6).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (7).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (8).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (9).png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy2/Walk (10).png"))
    ],
    [
    pygame.image.load(os.path.join(current_path, "Enemy3.png"))
    ],
    [
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/walk_1.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/walk_2.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/walk_3.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/walk_4.png"))
    ],
    [
    pygame.image.load(os.path.join(current_path, "Enemy5.png"))
    ]
]

enemy_a_imgs = \
[
    [
        pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime001.png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime002.png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime003.png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime004.png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime005.png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy1/Slime006.png"))
    ],
    [
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (1).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (2).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (3).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (4).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (5).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (6).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (7).png")),
        pygame.image.load(os.path.join(current_path, "enemy/enemy2/Attack (8).png"))
    ],
    [
    ],
    [
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/attack_1.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/attack_2.png")),
    pygame.image.load(os.path.join(current_path, "enemy/enemy4/attack_3.png"))
    ],
    [
    ]
]
enemy_interval = [(3, 4), (3, 4), (3, 4), (3, 15), (3, 10)]
enemy_poses = [(1180, (550, 680)), (1180, (550, 680)), (1180, (550, 680)), (1180, (550, 680)), (1180, (200, 350))]
enemy_speeds= [5, 3, 8, 3, 7]
enemy_dmg   = [4, 8, 8, 4, 10]
enemy_range = [270, 270, 270, 750, 260]
enemy_hp   =  [80, 160, 160, 100, 200]

class Enemy(pygame.sprite.Sprite):
    def __init__(self, idx):
        pygame.sprite.Sprite.__init__(self)
        self.w_imgs = enemy_imgs[idx]
        self.a_imgs = enemy_a_imgs[idx]
        self.idx = idx
        self.w_idx, self.a_idx = enemy_interval[idx]
        self.w_end = self.w_interval * len(self.w_imgs)
        self.a_end = self.a_interval * len(self.a_imgs)
        self.at_attack = self.a_end // 2
        
        self.image = self.w_imgs[0]
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
    
    def move_attack(self, Main):
        if self.pos[0] <= self.range:
            self.image = self.a_imgs[self.a_idx // self.w_interval]
            self.rect= self.image.get_rect(center = self.pos)
            self.a_idx += 1
            
            if self.a_idx >= self.a_end:
                self.a_idx = 1
                
            if self.a_idx == self.at_attack:
                if self.idx == 3:
                    pass #TODO 파이어볼
                else:
                    self.attack(Main)
                    eft = Enemy_effect(0, (245, self.pos[1]))
                    Main.effect_group.add(eft)
        else:
            self.pos = self.pos[0] - self.speed, self.pos[1]
            self.image = self.w_imgs[self.w_idx // self.w_interval]
            self.rect= self.image.get_rect(center = self.pos)
            self.w_idx += 1
            if self.w_idx >= self.w_end:
                self.w_idx = 1

    def attack(self, Main):
        Main.castle.attacked(self.dmg)

    def attacked(self, dmg):
        self.hp -= dmg
        if self.hp <= 0:
            # 죽는 effect 추가
            self.kill()

        # TODO 공격 모션 추가?
