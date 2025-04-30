#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>
#include <functional>
/*
/ Doing
// Done
TODO:
- Button Class (uses std::function to call a passed in function for the button, as well as running logic for changing texture) /
- Managers
	* Dialogue Manager
	* General Game Manager (e.g. what scene are we on, and what level are we on)
- Scenes (Each scene consists of an image, buttons and objects e.g. npcs)
- Maps (A collection of scenes with information on how they connect, also contains a script for the map specific logic)
- Menus, e.g. a title menu, for starting a game with a map selection screen
*/
using std::vector;
class Button {
private:
	Rectangle mRect;
	vector<Texture> mTextures;
	Texture2D mRectTexture = mTextures[0];
	bool mToggle = false;
	bool mPowered = false;
	bool mHighlight = true;
	std::function<void(bool)> mCallback;
public:
	/// <summary>
	/// Creates a Button object
	/// </summary>
	/// <param name="Rect">{x, y, width, height}</param>
	/// <param name="Textures">{Not Pressed, Pressed, Hovered}</param>
	/// <param name="Callback">A function the button will call when pressed P.S if a button is a toggle this will be called every frame that the button is powered</param>
	/// <param name="Toggle">Whether the button will be a toggle</param>
	Button(Rectangle Rect, vector<Texture> Textures, std::function<void(bool)> Callback,  bool Highlight = true, bool Toggle = false) : mRect(Rect), mTextures(Textures), mCallback(Callback),  mToggle(Toggle), mHighlight(Highlight) {
		mRectTexture = mTextures[0];
	}
	void SetButtonPower(bool Powered) {
		mPowered = Powered;
	}
	//Draw the button to the screen
	void Draw(Vector2 mousePos) {
		//this button should not be a toggle
		if (!mToggle) {
			if (CheckCollisionPointRec(mousePos, mRect) && !IsMouseButtonPressed(0) && mHighlight) {
				mRectTexture = mTextures[2];
			}
			else if (CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonPressed(0)) {
				mPowered = true;
				mRectTexture = mTextures[1];
				mCallback(mPowered);
			}
			else {
				mRectTexture = mTextures[0];
				mPowered = false;
			}
		}
		//this button should be a toggle
		else {
			if (mPowered) {mRectTexture = mTextures[1]; mCallback(mPowered);}
			else if (!mPowered) mRectTexture = mTextures[0];
			//button is "Colliding" with the button
			if (CheckCollisionPointRec(mousePos, mRect)) {
				//button was pressed
				if (IsMouseButtonPressed(0)) mPowered = !mPowered;
				//button wasn't pressed
				else if (mHighlight) {
					mRectTexture = mTextures[2];
				}
			}
		}
		DrawTexturePro(mRectTexture, {0,0, float(mRectTexture.width), float(mRectTexture.height) }, mRect, { .0f,.0f }, .0f, WHITE);
	}
};

class EmptyButton {
private:
	Rectangle mRect;
	bool mToggle = false;
	bool mPowered = false;
	bool mHighlight = true;
	bool mDebugColours = false;
	std::function<void(bool)> mCallback;
public:
	/// <summary>
	/// an Empty Button (no image), can be used for stuff like doors
	/// </summary>
	/// <param name="Rect">{x, y, width, height}</param>
	/// <param name="Callback">A function the button will call when pressed</param>
	/// <param name="debugColours">Colour the buton using red green and blue for debugging purposes</param>
	EmptyButton(Rectangle Rect, std::function<void(bool)> Callback, bool debugColours = false) : mRect(Rect), mCallback(Callback), mDebugColours(debugColours){
	}
	void SetButtonPower(bool Powered) {
		mPowered = Powered;
	}
	//Draw the button to the screen
	void Draw(Vector2 mousePos) {
		//this button should not be a toggle
		if (!mToggle) {
			if (CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonPressed(0)) {
				mPowered = true;
				mCallback(mPowered);
			}
			else {
				mPowered = false;
			}
		}
		DrawRectangle(mRect.x, mRect.y, mRect.width, mRect.height, {0,0,0,0});
	}
};


void testButtonCallback(bool powered) {
	std::cout << "\n" << powered;
}
int main() {
	const char* text = "Sword lol";
	const int size = 20;
	//screen dimensions
	const int screenWidth = 1280;
	const int screenHeight = 720;
	
	//initialize the window
	InitWindow(screenWidth, screenHeight, "penis");
	Texture2D buttonPlay = LoadTexture("C:\\Users\\phill\\Pictures\\Sleep Cover.png");
	Texture2D buttonPause = LoadTexture("C:\\Users\\phill\\Pictures\\Shutdown Cover.png");
	//Button testButton = Button({0,0, float(buttonPlay.height/8), float(buttonPlay.width/4)}, {buttonPause, buttonPlay, buttonPause}, testButtonCallback, false, true);
	EmptyButton testButton2 = EmptyButton({ 0,0, 100,100 }, testButtonCallback);
	
	//textures must be loaded after Window initialization

	Texture2D backText = LoadTexture("resources/back.png");


	Texture2D testText = LoadTexture("resources/test.png");
	Font defaultFont = LoadFont("resources/alagard/alagard.ttf");
	//set the target fps to 60
	SetTargetFPS(60);

	Vector2 mousePos = { 0, 0 };
	//game loop
	//checks to see if the window should be closing
	while (!WindowShouldClose()) {
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
		/*testButton.Draw(mousePos);*/
		testButton2.Draw(mousePos);
		//finish drawing
		EndDrawing();
		
	}
}