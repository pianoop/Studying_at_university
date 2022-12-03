import game_sub as sub
import random
from game_boss import Boss

stage = \
[
    [
        
    ],
    [
        
    ],
    [
        
    ]
]

class Manager():
    def __init__(self) :
        self.time = 0
        self.stage_data = stage
        
    def process(self, Main, stage):
        for i in self.stage_data:
            if self.time == i:
                sub.enemy_gen(Main)
        self.time += 1
        if self.time == 100:
            self.gen_BOSS(Main)
                
    def time_reset(self):
        self.time = 0
        
    def gen_BOSS(self, Main):
        BOSS = Boss((1230, random.randint(400, 500)))
        Main.enemy_group.add(BOSS)
    