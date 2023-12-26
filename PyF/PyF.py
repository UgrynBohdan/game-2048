# -*- coding: cp1251 -*-

import pygame
import ctypes
import random

lib = ctypes.CDLL('C++/CppF.dll')


class Game_2048(ctypes.Structure):
    pass

#/////////////////////////////////////////////////////////////////////////////////////
#ініціалізуємо методи бібліотеки
lib.Start_game.argtypes = []
lib.Start_game.restype = ctypes.POINTER(Game_2048)

lib.End_game.argtypes = [ctypes.POINTER(Game_2048)]
lib.End_game.restype = None


lib.Get_obj.argtypes = [ctypes.POINTER(Game_2048), ctypes.c_int]
lib.Get_obj.restype = ctypes.c_int

lib.Create_square.argtypes = [ctypes.POINTER(Game_2048), ctypes.c_int]
lib.Create_square.restype = None

lib.Move_objs.argtypes = [ctypes.POINTER(Game_2048), ctypes.c_char]
lib.Move_objs.restype = None

lib.Get_score.argtypes = [ctypes.POINTER(Game_2048)]
lib.Get_score.restype = ctypes.c_int
#/////////////////////////////////////////////////////////////////////////////////////


class Game_2048_Keyboard:
    def __init__(self):
        self.game1 = lib.Start_game()
        lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])
        lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])

        pygame.init()
        self.size_x = 400
        self.size_y = 500
        self.screen = pygame.display.set_mode((self.size_x, self.size_y))
        pygame.display.set_caption('2048') #встановлюємо назву вікна
        pygame.display.set_icon(pygame.image.load('images/2048_logo.png')) # іконка
        self.screen.fill((205, 193, 180)) #заповнюємо екран (color picker)
        self.text_fonts = pygame.font.Font('fonts/Roboto-Medium.ttf', 44)

        self.square = pygame.Surface((100, 100))
        self.square.fill((100, 100, 255))

        self.menu = pygame.Surface((400, 100))
        self.menu.fill((185, 173, 160))

    def __del__(self):
        lib.End_game(self.game1)


    def control(self, event):

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_j:
                lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])



        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_w:
                lib.Move_objs(self.game1, b'w')
                lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_s:
                lib.Move_objs(self.game1, b's')
                lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_a:
                lib.Move_objs(self.game1, b'a')
                lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_d:
                lib.Move_objs(self.game1, b'd')
                lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])


    def Play(self):
        run = True
        play = True
        while run:
            pygame.display.update()
            self.screen.fill((205, 193, 180))
            self.menu.fill((185, 173, 160))
            self.menu.blit(self.text_fonts.render('Рахунок: ' + str(lib.Get_score(self.game1)), True, (50, 255, 0)), (0, 0))
            
            if not play:
                self.menu.blit(self.text_fonts.render('Гра завершена!', True, (50, 255, 0)), (0, 50))

            self.screen.blit(self.menu, (0, 0))
            
            counter = 0
            for i in range(4):
                for j in range(4):
                    square_obj = lib.Get_obj(self.game1, i * 4 + j)
                    if square_obj != 0:
                        if square_obj == 2048:
                            play = False
                        self.square.fill((100, 100, 255))
                        self.screen.blit(self.square, (j * 100, 100 + i * 100))
                        self.screen.blit(self.text_fonts.render(str(square_obj), True, (50, 255, 0)), (j * 100, 100 + 20 + i * 100))#40 + j * 100
                        counter += 1
                    else:
                        counter = 0
                    
            if counter == 16:
                play = False
                    
            for event in pygame.event.get():
                if event.type == pygame.QUIT: #закриваємо екран на хрестик
                    run = False
                    pygame.quit()

                #if event.type == pygame.KEYDOWN:
                #    if event.key == pygame.K_b:
                #        play = False

                #if event.type == pygame.KEYDOWN:
                #    if event.key == pygame.K_j:
                #        lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])
                
                if play:
                    self.control(event)


class Game_2048_Mouse(Game_2048_Keyboard): #Успадкування
    def __init__(self):
        super().__init__()

        # Початкові координати мишки
        self.mouse_x = 0
        self.mouse_y = 0

        # Попередні координати мишки
        self.prev_mouse_x = 0
        self.prev_mouse_y = 0


    def control(self, event): #Поліморфізм
     
        if event.type == pygame.MOUSEMOTION:
            # Отримання поточних координат мишки
            self.mouse_x, self.mouse_y = event.pos


        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:  # ЛКМ
                # Зберігання початкових координат мишки
                self.prev_mouse_x = self.mouse_x
                self.prev_mouse_y = self.mouse_y


        if event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:  # ЛКМ
                # Визначення сторони руху мишки
                x_diff = self.mouse_x - self.prev_mouse_x
                y_diff = self.mouse_y - self.prev_mouse_y
                if abs(x_diff) > abs(y_diff):
                    if x_diff < 0:
                        lib.Move_objs(self.game1, b'a')
                    else:
                        lib.Move_objs(self.game1, b'd')
                else:
                    if y_diff < 0:
                        lib.Move_objs(self.game1, b'w')
                    else:
                        lib.Move_objs(self.game1, b's')
                lib.Create_square(self.game1, random.choices([2, 4], [0.9, 0.1])[0])
                


if int(input("\nВведіть як хочете грати з клавіатури(1) чи мишки(2): ")) == 1:
    a = Game_2048_Keyboard()
else:
    a = Game_2048_Mouse()
a.Play()




