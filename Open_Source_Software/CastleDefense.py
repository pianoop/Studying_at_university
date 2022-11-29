# 배경 이미지 설정
import os
import pygame
import math

screen_width = 1280
screen_height = 720
angle0 = (180 / math.pi)

class BG(pygame.sprite.Sprite):
    def __init__(self, img, pos):
        super().__init__()
        self.image = img
        self.rect = img.get_rect(center=pos)

class Weapons(pygame.sprite.Sprite):
    def __init__(self, imgs, poses):
        super().__init__()
        self.mouse_angle = 0
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

    
class Enemys(pygame.sprite.Sprite):
    def __init__(self, imgs, poses):
        super().__init__()
        self.img = imgs
        self.rct = []
        for idx, img in enumerate(imgs):
            self.rct.append(img.get_rect(center = poses[idx]))
        
        self.now = 0
        
    def draw(self, screen):
        screen.blit(self.img[self.now], self.rct[self.now])
    # 소환된 적들을 list에 넣어서 따로 blit 시켜줄 예정


# 현재 파일의 위치 반환
current_path = os.path.dirname(__file__) 

# 배경 이미지 불러오기
background = pygame.image.load(os.path.join(current_path, "BG.png"))

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
    pygame.image.load(os.path.join(current_path, "Enemy1.png"))]

enemy_poses = [(1180, 620)]
enemy = Enemys(enemy_imgs, enemy_poses)


# 시작 관련
pygame.init()
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Castle Defense")
clock = pygame.time.Clock()


# main!!
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
            elif event.key == pygame.K_2:
                weapon.swap(1)
            elif event.key == pygame.K_3:
                weapon.swap(2)
        
    screen.blit(background, (0, 0))
    
    weapon.update()
    
    weapon.draw(screen)
    enemy.draw(screen)
    
    pygame.display.update()

pygame.quit()