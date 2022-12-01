# 배경 이미지 설정
import os
import pygame
import math
from game_effect    import Effect
from game_castle    import Castle
from game_manager   import Manager
from game_weapon    import Weapons


screen_width        =   1280
screen_height       =   720
game_state          =   0      # 0: title, 1: in game, 2: game over
castle_xpos         =   260
castle_hp           =   314
castle_hp_pos       =   (0, 150)
castle_hp_slot_pos   =  (0, 153)
angle0              =   -180 / math.pi
ArrowSpeed          =   10
CannonballSpeed     =   7

# 현재 파일의 위치 반환
current_path = os.path.dirname(__file__) 

# 배경 이미지 불러오기
background = pygame.image.load(os.path.join(current_path, "BG.png"))


# 시작 관련
pygame.init()
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Castle Defense")
clock = pygame.time.Clock()

class GameMain():
    def __init__(self):
        self.screen = screen

        self.projectile_group = pygame.sprite.Group()
        self.enemy_group    = pygame.sprite.Group()
        self.effect_group   = pygame.sprite.Group()
        self.manager        = Manager()
        self.castle         = Castle(castle_hp, castle_hp_pos, castle_hp_slot_pos)      
        self.weapon         = Weapons()
        
    def play(self):
        clock = pygame.time.Clock()
        running = True
        
        while running:
            clock.tick(30) # FPS 값이 30 으로 고정
            screen.blit(background, (0, 0))
            
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_1:
                        self.weapon.swap(0)
                    elif event.key == pygame.K_2:
                        self.weapon.swap(1)
                    elif event.key == pygame.K_3:
                        self.weapon.swap(2)
                
                if event.type == pygame.MOUSEBUTTONDOWN: 
                    self.weapon.attack(self)
    
            self.castle.update()
            self.weapon.update()
            self.enemy_group.update(self)
            self.effect_group.update()
            self.projectile_group.update()
            
            self.castle.draw(screen)
            self.weapon.draw(screen)
            self.enemy_group.draw(screen)
            self.effect_group.draw(screen)
            self.projectile_group.draw(screen)
            
            self.manager.process(self)
    
            pygame.display.update()


if __name__ == "__main__":
    gameMain = GameMain()
    gameMain.play()
    pygame.quit()
