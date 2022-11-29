# 배경 이미지 설정
import os
import pygame
import math
import random

screen_width    =   1280
screen_height   =   720
game_state      =   0      # 0: title, 1: in game, 2: game over
castle_xpos     =   260
castle_hp       =   100
castle_hp_pos   =   (100, 450)
angle0          =   180 / math.pi
ArrowSpeed      =   10
CannonballSpeed =   7

def range_check(pos):
    return (pos[0] >=0) and (pos[0] <= screen_width) and (pos[1] >= 0) and (pos[1] <= screen_height)

class BG(pygame.sprite.Sprite):
    def __init__(self, img, pos):
        super().__init__()
        self.image = img
        self.rect = img.get_rect(center=pos)
        
class Castle():
    def __init__(self):
        self.hpbar = Hpbar(castle_hp, castle_hp_bar, castle_hp_blk, castle_hp_pos)
        
        
    def attacked(self, dmg):
        self.hpbar.attacked(dmg)
        if(self.hpbar.get_hp <= 0):
            game_state = 2
    def update(self):
        self.hpbar.update()
        
        
class Hpbar():
    def __init__(self, hp, img_bar, img_blk, pos):
         self.hp = hp
         self.img_bar = img_bar
         self.img_blk = img_blk
         self.pos = pos
         
    def attacked(self, dmg):
        self.hp -= dmg
         
    def get_hp(self):
        return self.hp
    
    def draw(self, screen):
        screen.blit(self.img_bar, self.pos)
        for h1 in range(100, 401):
            screen.blit(self.img_blk, (h1+3, self.pos[1]))
    
    def update(self):
        pass
    

class Weapons(pygame.sprite.Sprite):
    def __init__(self, imgs, poses):
        super().__init__()
        self.imgs = imgs
        self.poses = poses
        self.rct = []
        for idx, img in enumerate(imgs):
            self.rct.append(img.get_rect(center = poses[idx]))
        
        self.now    = 0  # 시작 기본 무기 bow
        self.nowMax = 0  # 무기 해금 관련
        self.image  = imgs[self.now]
        self.rect   = imgs[self.now].get_rect(center = poses[self.now])
        
    def draw(self, screen):
        screen.blit(self.image, self.rect)
        
    def update(self):
        self.rotate()
        
    def rotate(self):
        global angle0
        mouse_x, mouse_y = pygame.mouse.get_pos()
        rel_x, rel_y = mouse_x - self.rct[self.now].centerx, mouse_y - self.rct[self.now].centery
        angle = angle0 * -math.atan2(rel_y, rel_x)
        self.image = pygame.transform.rotate(self.imgs[self.now], int(angle))
        self.rect = self.image.get_rect(center=self.poses[self.now])
    
    def swap(self, weapon):
        self.now = weapon
        self.image = self.imgs[self.now]
        self.rect  = self.rct[self.now]
        
class Projectiles(pygame.sprite.Sprite):
    def __init__(self, imgs, poses):
        super().__init__()
        self.imgs = imgs
        self.poses = poses
        self.rct = []
        for idx, img in enumerate(imgs):
            self.rct.append(img.get_rect(center = poses[idx]))
            
        self.now    = 0  # 시작 기본 무기 Bow에 맞는 Arrow
        
    def swap(self, projectile):
        self.now = projectile
        self.image = self.imgs[self.now]
        self.rect  = self.rct[self.now]
        
    def attack(self):
        pass
    

    
class Enemys(pygame.sprite.Sprite):
    def __init__(self, imgs, poses, speeds, dmg):
        super().__init__()
        self.img = imgs
        self.pos = poses
        self.speed = speeds
        self.dmg = dmg
        self.rct = []
        for idx, img in enumerate(imgs):
            self.rct.append(img.get_rect(center = poses[idx]))
        
        self.now_active = [0, 1, 2, 3, 4]
        self.active_poses = poses
        
    def draw(self, screen):
        for idx, enm in enumerate(self.now_active):
            self.rct[enm].center = self.active_poses[idx]
            screen.blit(self.img[enm], self.rct[enm])
            
    def update(self):
        self.move()
    
    def move(self):
        for idx, enm in enumerate(self.now_active):
            if self.active_poses[idx][0] <= castle_xpos:
                self.attack(idx)
            else:
                self.active_poses[idx] = self.active_poses[idx][0] - self.speed[idx], self.active_poses[idx][1]
            # TODO 충돌처리도 동시에?
            
    def attack(self, idx):
        castle.attacked(self.dmg[idx])
        # TODO 공격 모션 추가?
            


# 현재 파일의 위치 반환
current_path = os.path.dirname(__file__) 

# 배경 이미지 불러오기
background = pygame.image.load(os.path.join(current_path, "BG.png"))

# 성 관련
castle = Castle()

# HP 관련
castle_hp_bar = pygame.image.load(os.path.join(current_path, "HP_bar.png"))
castle_hp_blk = pygame.image.load(os.path.join(current_path, "HP_blk.png"))


# 무기 관련
weapon_imgs = [
    pygame.image.load(os.path.join(current_path, "Bow.png")),
    pygame.image.load(os.path.join(current_path, "Cannon.png")),
    pygame.image.load(os.path.join(current_path, "Wand.png"))]
weapon_poses = [(160, 340), (160, 320), (160, 300)]
weapon = Weapons(weapon_imgs, weapon_poses)

# 투사체 관련
projectile_imgs = [
    pygame.image.load(os.path.join(current_path, "Arrow.png")),
    pygame.image.load(os.path.join(current_path, "Cannonball.png")),
    pygame.image.load(os.path.join(current_path, "Magic.png"))]
projectile_poses = [(180, 340), (180, 320), (180, 300)]

projectile = Projectiles(projectile_imgs, projectile_poses)

# 적 관련
enemy_imgs = [
    pygame.image.load(os.path.join(current_path, "Enemy1.png")),
    pygame.image.load(os.path.join(current_path, "Enemy2.png")),
    pygame.image.load(os.path.join(current_path, "Enemy3.png")),
    pygame.image.load(os.path.join(current_path, "Enemy4.png")),
    pygame.image.load(os.path.join(current_path, "Enemy5.png"))]
enemy_poses = [(1180, 620), (1180, 660), (1180, 560), (1180, 220), (1180, 350)]
enemy_speeds= [5, 10, 3, 7, 7]
enemy_dmg   = [4, 8, 5, 4, 10]

enemy = Enemys(enemy_imgs, enemy_poses, enemy_speeds, enemy_dmg)


# 시작 관련
pygame.init()
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Castle Defense")
clock = pygame.time.Clock()

# Main Loop!!
running = True
#clock.tick(30)
#screen.blit(background, (0, 0))
while running:
    clock.tick(30) # FPS 값이 30 으로 고정

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:
                weapon.swap(0)
                projectile.swap(0)
            elif event.key == pygame.K_2:
                weapon.swap(1)
                projectile.swap(1)
            elif event.key == pygame.K_3:
                weapon.swap(2)
                projectile.swap(2)
        
        if event.type == pygame.MOUSEBUTTONDOWN: 
            projectile.attak()
            
        
    screen.blit(background, (0, 0))
    
    weapon.update()
    enemy.update()
    
    weapon.draw(screen)
    enemy.draw(screen)
    
    pygame.display.update()

pygame.quit()