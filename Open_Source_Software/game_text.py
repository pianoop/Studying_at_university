import os
import pygame

pygame.font.init()
WHITE   = (255, 255, 255)
YELLOW  = (255, 255, 0)
R       = (255, 153, 153)
B       = (204, 204, 255)
font_big = pygame.font.Font('font/Maplestory_Bold.ttf', 60)
font = pygame.font.Font('font/Maplestory_Light.ttf', 30)

shop1 = [font_big.render('상점', True, WHITE)]
shop1_pos = [(100, 100)]

shop2 = \
[
font_big.render('스킬', True, R),
font_big.render('기타', True, B),
font.render('150 G', True, YELLOW),
font.render('200 G', True, YELLOW),
font.render('250 G', True, YELLOW)
]
shop2_pos = [(180, 220), (180, 520), (320, 350), (520, 350), (720, 350)]

shop3 = \
[
font.render('성 수리 100 G', True, YELLOW)
]
shop3_pos = [(320, 650)]

shop4 = \
[
font.render('다음 스테이지로', True, WHITE)
]
shop4_pos = [(900, 650)]



class Text():
    def __init__(self):
        super().__init__()
        self.shop1      = shop1
        self.shop1_pos  = shop1_pos
        self.shop2      = shop2
        self.shop2_pos  = shop2_pos
        self.shop3      = shop3
        self.shop3_pos  = shop3_pos
        self.shop4      = shop4
        self.shop4_pos  = shop4_pos
        
        
    def draw_shop(self, screen):
        for idx, text in enumerate(self.shop1):
            screen.blit(text, self.shop1_pos[idx])
        for idx, text in enumerate(self.shop2):
            screen.blit(text, self.shop2_pos[idx])
        for idx, text in enumerate(self.shop3):
            screen.blit(text, self.shop3_pos[idx])
        for idx, text in enumerate(self.shop4):
            screen.blit(text, self.shop4_pos[idx])    
    
    def draw_stage(self, screen):
        pass
    
    def draw_title(self, screen):
        pass
    
    def draw_gameover(self, screen):
        pass
    
    def draw_gameclear(self, screen):
        pass