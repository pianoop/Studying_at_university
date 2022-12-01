import os
import pygame
import game_sub
import math
current_path = os.path.dirname(__file__) 

projectile_imgs = [
    pygame.image.load(os.path.join(current_path, "Arrow.png")),
    pygame.image.load(os.path.join(current_path, "Cannonball.png")),
    pygame.image.load(os.path.join(current_path, "Magic.png"))]
projectile_poses = [(170, 320), (170, 320), (170, 320)]
projectile_dmg   = [30, 90, 80]


class Projectile(pygame.sprite.Sprite):
    def __init__(self, idx, dpos = (0, 0), angle = 0):
        pygame.sprite.Sprite.__init__(self)
        self.idx = idx    
        self.dmg   = projectile_dmg[idx]    
        if idx == 0:
            self.image = pygame.transform.rotate(projectile_imgs[self.idx], -(int(math.degrees(angle))))
        else:
            self.image = projectile_imgs[idx]
        self.pos = projectile_poses[idx]
        self.dpos = dpos
        self.angle = angle
        
        self.rect = self.image.get_rect(center=self.pos)

    def update(self):
        self.move()
        if not(game_sub.range_check(self.pos)):
            self.kill()
    
    def move(self):
        if(self.idx == 0):
            self.move_arrow()
        elif(self.idx== 1):
            self.move_cannonball()
        elif(self.idx== 2):
            self.move_magic()

    def move_arrow(self):
        self.pos = self.pos[0] + self.dpos[0], self.pos[1] + self.dpos[1] 
        self.rect.center = self.pos
        
    def move_cannonball(self):
        pass
    
    def move_magic(self):
        pass
    
    # 충돌?