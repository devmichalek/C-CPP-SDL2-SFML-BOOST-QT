#!/usr/bin/python

import pygame

pygame.init()

gameDisplay = pygame.display.set_mode((800, 600))
pygame.display.set_caption('Slither')

pygame.display.update()

quit = False;

while not quit:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			quit = True
		#print(event)
	

pygame.quit()
quit()