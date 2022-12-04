import os
import pygame

castle_hp           =   314
current_path = os.path.dirname(__file__)

game_start = pygame.image.load(os.path.join(current_path, "bg/gamestart.png"))
game_start_pos = (900, 460)

game_home = pygame.image.load(os.path.join(current_path, "bg/Home.png"))
game_home_pos = (780, 290)

gameover_restart = pygame.image.load(os.path.join(current_path, "bg/Restart.png"))
gameover_restart_pos = (550, 420)

gameover_home = game_home
gameover_home_pos = (800, 420)



class System():
    def __init__(self):
        super().__init__()
        self.game_start_pos = game_start_pos
        self.game_start = game_start
        self.game_start_rct = game_start.get_rect(center= game_start_pos)
        
        self.game_home_pos = game_home_pos
        self.game_home = game_home
        self.game_home_rct = game_home.get_rect(center= game_home_pos)
        
        self.gameover_restart_pos = gameover_restart_pos
        self.gameover_restart = gameover_restart
        self.gameover_restart_rct = gameover_restart.get_rect(center= gameover_restart_pos)
        
        self.gameover_home_pos = gameover_home_pos
        self.gameover_home = gameover_home
        self.gameover_home_rct = gameover_home.get_rect(center= gameover_home_pos)
        
        
    def update(self, Main):
        pass
    
    def draw_title(self,screen, Main):
        screen.blit(self.game_start, self.game_start_rct)
        
    def collide_title(self, Main, mouse_pos):
        if self.game_start_rct.collidepoint(mouse_pos):
            Main.state = 1
            Main.group_reset()
    
    def draw_gameover(self,screen, Main):
        screen.blit(self.gameover_restart, self.gameover_restart_rct)
        screen.blit(self.gameover_home, self.gameover_home_rct)
    
    def collide_gameover(self, Main, mouse_pos):
        if self.gameover_restart_rct.collidepoint(mouse_pos):
            Main.state = 1
            Main.money = Main.save_money
            Main.castle.hpbar.set_hp(Main.save_hp)
            Main.group_reset()
            
        if self.gameover_home_rct.collidepoint(mouse_pos):
            self.reset(Main)
    
    def draw_gameclear(self,screen, Main):
        screen.blit(self.game_home, self.game_home_rct)
    
    def collide_gameclear(self, Main, mouse_pos):
        if self.game_home_rct.collidepoint(mouse_pos):
            self.reset(Main)
            
    def reset(self, Main):
        Main.money = 0
        Main.save_money = 0
        Main.castle.hpbar.set_hp(castle_hp)
        self.save_hp = castle_hp
        Main.weapon.reset()
        Main.weapon.cool_reset()
        Main.stage = 0
        Main.state = 0
        Main.group_reset()
        
        