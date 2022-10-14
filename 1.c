# coding:utf-8
import pygame
from pygame.locals import *
import time
import random
import sys

pygame.init()

x = 80
y = 27
import os

os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (x, y)
canvas = pygame.display.set_mode((1200, 715))

canvas.fill((255, 255, 255))

pygame.display.set_caption("飞机大战")

enemy1=pygame.image.load("images/enemy1.png")
enemy2=pygame.image.load("images/enemy2.png")
enemy3=pygame.image.load("images/enemy3.png")
h=pygame.image.load("images/hero1.png")
bg=pygame.image.load("images/bg1.png")
b=pygame.image.load("images/bullet1.png")


e1 = []
e1.append(pygame.image.load("images/enemy1.png"))
e1.append(pygame.image.load("images/enemy1_down1.png"))
e1.append(pygame.image.load("images/enemy1_down2.png"))
e1.append(pygame.image.load("images/enemy1_down3.png"))
e1.append(pygame.image.load("images/enemy1_down4.png"))
e1.append(pygame.image.load("images/enemy1_down5.png"))
e2 = []
e2.append(pygame.image.load("images/enemy2.png"))
e2.append(pygame.image.load("images/enemy2_down1.png"))
e2.append(pygame.image.load("images/enemy2_down2.png"))
e2.append(pygame.image.load("images/enemy2_down3.png"))
e2.append(pygame.image.load("images/enemy2_down4.png"))
e2.append(pygame.image.load("images/enemy2_down5.png"))
e3 = []
e3.append(pygame.image.load("images/enemy3_1.png"))
e3.append(pygame.image.load("images/enemy3_2.png"))
e3.append(pygame.image.load("images/enemy3_down1.png"))
e3.append(pygame.image.load("images/enemy3_down2.png"))
e3.append(pygame.image.load("images/enemy3_down3.png"))
e3.append(pygame.image.load("images/enemy3_down4.png"))
e3.append(pygame.image.load("images/enemy3_down5.png"))
e3.append(pygame.image.load("images/enemy3_down6.png"))
e3.append(pygame.image.load("images/enemy3_down7.png"))
h = []
h.append(pygame.image.load("images/hero.png"))
h.append(pygame.image.load("images/hero_down1.png"))
h.append(pygame.image.load("images/hero_down2.png"))
h.append(pygame.image.load("images/hero_down3.png"))
h.append(pygame.image.load("images/hero_down4.png"))

bg = pygame.image.load("images/bg4.png")

b = []
b.append(pygame.image.load("images/bullet1.png"))

startgame = pygame.image.load("images/startGame.png")

logo = pygame.image.load("images/LOGO.png")

pause = pygame.image.load("images/game_pause_nor.png")

score = pygame.image.load("images/score.png")

over = pygame.image.load("images/over.png")

bgg = pygame.image.load("images/bg235.jpg")


def handleEvent():
for event in pygame.event.get():
if event.type == QUIT or event.type == KEYDOWN and event.key == K_ESCAPE:
pygame.quit()
sys.exit()

if event.type == pygame.MOUSEMOTION:


if GameVar.state == GameVar.STATES["RUNNING"]:
GameVar.hero.x = event.pos[0] - GameVar.hero.width / 2
GameVar.hero.y = event.pos[1] - GameVar.hero.height / 2




if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
if GameVar.state == GameVar.STATES["START"]:
GameVar.state = GameVar.STATES["RUNNING"]
if event.type == KEYDOWN and event.key == K_r:
if GameVar.state == GameVar.STATES["GAME_OVER"]:
GameVar.score = 0
GameVar.heroes = 4
GameVar.state = GameVar.STATES["START"]

def draw(img, x, y):
canvas.blit(img, (x, y))



def isActionTime(lastTime, interval):
if lastTime == 0:
return True
        currentTime = time.time()
return currentTime - lastTime >= interval



        def renderText(text, position, view=canvas):

my_font = pygame.font.Font("my_font/font1.ttf", 30)

text = my_font.render(text, True, (255, 255, 255))
view.blit(text, position)



def isMouseOut(x, y):
if x >= 1190 or x <= 0 or y > 700 or y <= 0:
return True
else:
return False



        def isMouseOver(x, y):
if x > 0 and x < 1150 and y > 1 and y < 648:
return True
else:
return False



        class Sky(object):
def __init__(self):
self.width = 480
self.height = 680
self.img = bgg
self.x1 = 0
self.y1 = 0
self.x2 = 0
self.y2 = -self.height

def paint(self, view):
# view.blit(bgg,(0,0))
draw(self.img, self.x1, self.y1)
draw(self.img, self.x2, self.y2)

def step(self):
self.y1 = self.y1 + 1
self.y2 = self.y2 + 1
if self.y1 > self.height:
self.y1 = -self.height
if self.y2 > self.height:
self.y2 = -self.height


class FlyingObject(object):
def __init__(self, x, y, width, height, life, frames, baseFrameCount):
self.x = x
self.y = y
self.width = width
self.height = height
self.life = life
self.lastTime = 0
self.interval = 0.01
self.down = False
self.canDelete = False

self.frames = frames
self.frameIndex = 0
self.img = self.frames[self.frameIndex]
self.frameCount = baseFrameCount

def paint(self, view):

draw(self.img, self.x, self.y)

def step(self):

if not isActionTime(self.lastTime, self.interval):
return
self.lastTime = time.time()

self.y = self.y + 5


def hit(self, component):
c = component
return c.x > self.x - c.width and c.x < self.x + self.width and c.y > self.y - c.height and c.y < self.y + self.height

        def bang(self):
self.life -= 1
if self.life == 0:

self.down = True

self.frameIndex = self.frameCount


# if self.down == True:
# self.canDelete = True

            if hasattr(self, "score"):
                GameVar.score += self.score


    def outOfBounds(self):
        return self.y > 650


    def animation(self):
        if self.down:

            if self.frameIndex == len(self.frames):
                self.canDelete = True
            else:
                self.img = self.frames[self.frameIndex]
                self.frameIndex += 1
        else:
            self.img = self.frames[self.frameIndex % self.frameCount]
            self.frameIndex += 1



class Enemy(FlyingObject):
    def __init__(self, x, y, width, height, type, life, score, frames, baseFrameCount):
        FlyingObject.__init__(self, x, y, width, height, life, frames, baseFrameCount)
        self.x = random.randint(0, 1300 - self.width)
        self.y = -self.height
        self.type = type
        self.score = score




class Hero(FlyingObject):
    def __init__(self, x, y, width, height, life, frames, baseFrameCount):
        FlyingObject.__init__(self, x, y, width, height, life, frames, baseFrameCount)
        self.width = 60
        self.height = 75
        self.x = 450 + 480 / 2 - self.width / 2
        self.y = 650 - self.height - 30

        self.shootLastTime = 0.5
        self.shootInterval = 0.3

    def paint(self, view):
        draw(self.img, self.x, self.y)
    def shoot(self):
        if not isActionTime(self.shootLastTime, self.shootInterval):
            return
        self.shootLastTime = time.time()
        GameVar.bullets.append(Bullet(self.x + self.width / 2, self.y, 9, 21, 1, b, 1))
        #GameVar.bullets.append(Bullet(self.x + self.width / 2+15, self.y, 9, 21, 1, b, 1))
        #GameVar.bullets.append(Bullet(self.x + self.width / 2-15, self.y, 9, 21, 1, b, 1))

class Bullet(FlyingObject):
    def __init__(self, x, y, width, height, life, frames, baseFrameCount):
        FlyingObject.__init__(self, x, y, width, height, life, frames, baseFrameCount)


    def step(self):
        self.y = self.y - 10


    def outOfBounds(self):
        return self.y < -self.height


def componentEnter():

    if not isActionTime(GameVar.lastTime, GameVar.interval):
        return
    GameVar.lastTime = time.time()


    x = random.randint(0, 1300 - 57)
    x1 = random.randint(0, 1300 - 50)
    x2 = random.randint(0, 1300 - 169)

    n = random.randint(0, 9)
    if n <= 7:

        GameVar.enemies.append\
            (Enemy(x, 0, 57, 45, 1,  1,1, e1, 1))
    elif n == 8:
        GameVar.enemies.append\
            (Enemy(x1, 0, 50, 68, 2, 3, 5, e2, 1))
    elif n == 9:

        if len(GameVar.enemies) == 0 or GameVar.enemies[0].type != 3:
            GameVar.enemies.insert\
                (0, Enemy(x2, 0, 169, 258, 3, 10, 20, e3, 2))



def paintComponent(view):

        if not isActionTime(GameVar.paintLastTime, GameVar.paintInterval):
            return
        GameVar.paintLastTime = time.time()


        GameVar.sky.paint(view)

        for enemy in GameVar.enemies:
            enemy.paint(view)

        GameVar.hero.paint(view)

        for bullet in GameVar.bullets:
            bullet.paint(view)

        draw(score, 10, 10)
        renderText(str(GameVar.score), (165, 25))
        renderText(str(GameVar.heroes), (165, 58))



def componentStep():

    GameVar.sky.step()
    for enemy in GameVar.enemies:
        enemy.step()

    for bullet in GameVar.bullets:
        bullet.step()



def checkHit():

    for enemy in GameVar.enemies:

        if enemy.down == True:
            continue

        if GameVar.hero.hit(enemy):
            enemy.bang()
            GameVar.hero.bang()
        for bullet in GameVar.bullets:

            if bullet.down == True:
                continue

            if enemy.hit(bullet):
                enemy.bang()
                bullet.bang()



def deleteComponent():

    for i in range(len(GameVar.enemies) - 1, -1, -1):
        x = GameVar.enemies[i]
        if x.canDelete or x.outOfBounds():
            GameVar.enemies.remove(x)

    for i in range(len(GameVar.bullets) - 1, -1, -1):
        x = GameVar.bullets[i]
        if x.canDelete or x.outOfBounds():
            GameVar.bullets.remove(x)

    if GameVar.hero.canDelete == True:
        GameVar.heroes -= 1
        if GameVar.heroes == 0:
            # renderText("游戏结束",(100, 200))
            # print("游戏结束")
            GameVar.state = GameVar.STATES["GAME_OVER"]
        else:
            GameVar.hero = Hero(0, 0, 60, 75, 1, h, 1)


def componentAnimation():

    for enemy in GameVar.enemies:
        enemy.animation()

    for bullet in GameVar.bullets:
        bullet.animation()

    GameVar.hero.animation()



class GameVar(object):
    sky = None

    hero = None
    enemies = []

    bullets = []


    lastTime = 0
    interval = 0.5# 单位为秒

    paintLastTime = 0
    paintInterval = 0.03

    score = 0

    # with open('tools/score.txt', 'r') as h:
    #     h = h.read()
    heroes = 3
    # heroes = 3000

    STATES = {"START": 1, "RUNNING": 2, "PAUSE": 3, "GAME_OVER": 4}
    state = STATES["START"]



GameVar.sky = Sky()

GameVar.hero = Hero(0, 0, 60, 75, 1, h, 1)



def contralState():
    if GameVar.state == GameVar.STATES["START"]:
        GameVar.sky.paint(canvas)
        GameVar.sky.step()
        draw(logo, 200, 200)
        draw(startgame, 460, 450)
    elif GameVar.state == GameVar.STATES["RUNNING"]:
        componentEnter()

        paintComponent(canvas)

        componentStep()

        componentAnimation()

        GameVar.hero.shoot()

        checkHit()

        deleteComponent()
    elif GameVar.state == GameVar.STATES["PAUSE"]:
        paintComponent(canvas)
        GameVar.sky.step()
        draw(pause, 500, 250)
    elif GameVar.state == GameVar.STATES["GAME_OVER"]:
        paintComponent(canvas)
        GameVar.sky.step()
        draw(over, 230, 250)


while True:


    contralState()

    pygame.display.update()

    handleEvent()

    pygame.time.delay(15)