# 배경 이미지 설정
import os
import pygame
from game_castle    import Castle
from game_manager   import Manager
from game_weapon    import Weapons


screen_width        =   1280
screen_height       =   720
game_state          =   0      # 0: title, 1: in game, 2: game over
castle_xpos         =   260
castle_hp           =   314
castle_hp_pos       =   (0, 150)
castle_hp_slot_pos  =   (0, 153)


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
        self.state = 1
        self.stage = 0
        # 0: title, -1: shop, -2: gameover, -3: gameclear, 1: stage
        self.money = 0

        self.projectile_group       = pygame.sprite.Group()
        self.enemy_projectile_group = pygame.sprite.Group()
        self.enemy_group            = pygame.sprite.Group()
        self.effect_group           = pygame.sprite.Group()
        self.enemy_effect_group     = pygame.sprite.Group()
        self.manager                = Manager()
        self.weapon                 = Weapons()
        self.castle                 = Castle(castle_hp, castle_hp_pos, castle_hp_slot_pos)      
        
        
    def play(self):
        clock = pygame.time.Clock()
        running = True
        
        while running:
            clock.tick(30) # FPS 값이 30 으로 고정
            screen.blit(background, (0, 0))
            
            if self.state == 1:  # defense stage
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        running = False
                        
                    if event.type == pygame.KEYDOWN:
                        self.weapon.keydown(event.key)
                    
                    if event.type == pygame.MOUSEBUTTONDOWN: 
                        self.weapon.attack(self)
        
                self.castle.update()
                self.weapon.update()
                self.enemy_group.update(self, screen)
                self.effect_group.update(self)
                self.projectile_group.update(self)
                self.enemy_projectile_group.update(self)
                self.enemy_effect_group.update(self)
                
                self.castle.draw(screen)
                self.weapon.draw(screen)
                self.enemy_group.draw(screen)
                self.effect_group.draw(screen)
                self.projectile_group.draw(screen)
                self.enemy_projectile_group.draw(screen)
                self.enemy_effect_group.draw(screen)
                
                self.manager.process(self, self.stage)
            
            elif self.state == -1:
                pass
                # TODO shop 구현
            elif self.state == -2:
                pass
                # TODO game over 화면, 현재 스테이지 재도전 or (re ->) 타이틀로
            elif self.state == -3:
                pass
                # TODO game clear 축하 화면! -> re ->타이틀
            elif self.state == 0:   # title
                pass
                # TODO title화면 구현, stage1로 연계
                
            
            
            pygame.display.update()


if __name__ == "__main__":
    gameMain = GameMain()
    gameMain.play()
    pygame.quit()
