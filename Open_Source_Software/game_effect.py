import pygame
import os
import game_sub as sub
current_path = os.path.dirname(__file__) 

effect_imgs = [[
    pygame.image.load(os.path.join(current_path, "sprite/arrow01.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow02.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow03.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow04.png")),
    pygame.image.load(os.path.join(current_path, "sprite/arrow05.png"))],
    [
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball01.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball02.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball03.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball04.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball05.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball06.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball07.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball08.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Cannonball09.png"))],
    [
    pygame.image.load(os.path.join(current_path, "sprite/Magic01-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic02-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic03-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic04-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic05-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic06-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic07-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic08-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic09-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic10-removebg-preview.png")),
    pygame.image.load(os.path.join(current_path, "sprite/Magic11-removebg-preview.png"))
    ]
]

class Effect(pygame.sprite.Sprite):
    def __init__(self, idx, pos):
        pygame.sprite.Sprite.__init__(self)
        self.imgs = effect_imgs[idx]
        self.pos = pos
        self.idx = 1
        self.interval = 3
        self.end = self.interval * len(self.imgs)
        self.image = self.imgs[self.idx]
        self.rect  = self.imgs[self.idx // self.interval].get_rect(center = pos)
        

    def update(self):
        # update를 통해 캐릭터의 이미지가 계속 반복해서 나타나도록 한다.
        if self.idx >= self.end:
            self.kill()
        else:
            self.image = self.imgs[self.idx // self.interval]
            self.rect= self.image.get_rect(center = self.pos)
            self.idx += 1
