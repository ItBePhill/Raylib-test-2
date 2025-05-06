#include <raylib.h>
#include "raymath.h"
#include <vector>
#include <iostream>
#include <functional>
#include <Buttons.hpp>
#include <sstream>
/*
/ Doing
// Done
Bugs:
- 
TODO:
- Button Class (uses std::function to call a passed in function for the button, as well as running logic for changing texture) /
- NPC Class (basically just an image and dialogue) 
- Managers
	* Dialogue Manager /
	* General Game Manager (e.g. what scene are we on, and what level are we on)
- Scenes (Each scene consists of an image, buttons and objects e.g. npcs) 
- Maps (A collection of scenes with information on how they connect, also contains a script for the map specific logic)
- Menus, e.g. a title menu, for starting a game with a map selection screen

Stuff I Might Add:
- Shop (built from NPC Class, or menu framework)
*/
using std::vector;



void testButtonCallback(bool powered) {
	std::cout << "\n" << powered;
}
int main() {
	int frameCounter = 0;
	std::stringstream textStream;
	std::string textStreamString;
	const int size = 20;
	//screen dimensions
	const int screenWidth = 1280;
	const int screenHeight = 720;
	
	//initialize the window
	InitWindow(screenWidth, screenHeight, "penis");
	//textures must be loaded after Window initialization
	Texture2D buttonPlay = LoadTexture("C:\\Users\\phill\\Pictures\\Sleep Cover.png");
	Texture2D buttonPause = LoadTexture("C:\\Users\\phill\\Pictures\\Shutdown Cover.png");
	Buttons::TextureButton testButton2 = Buttons::TextureButton({ 0,0, 100,100 }, {buttonPause, buttonPlay, buttonPlay}, testButtonCallback, false, false, 10);
	Texture2D backText = LoadTexture("resources/back.png");
	Texture2D testText = LoadTexture("resources/test.png");
	Font defaultFont = LoadFont("resources/alagard/alagard.ttf");
	//set the target fps to 60
	SetTargetFPS(60);

	Vector2 mousePos = { 0, 0 };
	//game loop
	//checks to see if the window should be closing
	while (!WindowShouldClose()) {
		frameCounter++;
		textStream = std::stringstream();
		textStream << frameCounter;
		textStreamString = textStream.str();
		const char* text = textStreamString.c_str();
		mousePos = GetMousePosition();
		//update variables here:
		
		//draw the window
		BeginDrawing();
		//set background to white
		ClearBackground(WHITE);
		//draw text to the screen
		
		DrawTexture(backText, screenWidth/2 - backText.width/2, screenHeight / 2 - backText.height / 2, WHITE);
		DrawTexture(testText, 0, 0, WHITE);
		DrawTextEx(defaultFont, text, {10,screenHeight/1.3}, size, 10, WHITE);
		testButton2.Draw(mousePos);
		//finish drawing
		EndDrawing();
		
	}
}