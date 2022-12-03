import os
import pygame

current_path = os.path.dirname(__file__)

shop_skill_imgs = \
[
pygame.image.load(os.path.join(current_path, "skill/Bow1_shop.png")),
pygame.image.load(os.path.join(current_path, "skill/Cannon_shop.png")),
pygame.image.load(os.path.join(current_path, "skill/Bow2_shop.png")),
pygame.image.load(os.path.join(current_path, "skill/Fire_shop.png"))
]


class Shop():
    def __init__(self):
        super().__init__()