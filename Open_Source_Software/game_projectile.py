import os
import pygame
import game_sub
current_path = os.path.dirname(__file__) 

projectile_imgs = [
    pygame.image.load(os.path.join(current_path, "Arrow.png")),
    pygame.image.load(os.path.join(current_path, "Cannonball.png")),
    pygame.image.load(os.path.join(current_path, "Magic.png"))]
projectile_poses = [(170, 320), (170, 320), (170, 320)]
projectile_speeds= [25, 10, 50]
projectile_dmg   = [30, 90, 80]


class Projectile(pygame.sprite.Sprite):
    def __init__(self, idx, dpos = (0, 0), angle = 0):
        pygame.sprite.Sprite.__init__(self)
        self.idx = idx        
        self.image = projectile_imgs[idx]
        if idx == 0:
            self.pos = pygame.transform.rotate(self.imgs[self.now], int(angle))
        else:
            self.pos = projectile_poses[idx]
            
        self.dpos = dpos
        self.angle = angle
        self.speed = projectile_speeds[idx]
        self.dmg   = projectile_dmg[idx]
        
        self.rct = self.image.get_rect(center=self.pos)

    def update(self):
        self.move()
        if not(game_sub.range_check(self.pos)):
            self.kill()
    
    def move(self):
        for idx, enm in enumerate(self.active):
            if(enm == 0):
                self.move_arrow()
            elif(enm == 1):
                self.move_cannonball()
            elif(enm == 2):
                self.move_magic()

    def move_arrow(self):
        self.pos = self.pos[0] + self.dpos[0], self.pos[1] + self.dpos[1] 
        self.rect.center = self.pos
        
    def move_cannonball(self):
        pass
    
    def move_magic(self):
        pass
    
    # 충돌?