#include <raylib.h>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <Buttons.hpp>
using std::vector;
Font defaultFont = LoadFont("resources/alagard/alagard.ttf");
Texture2D defaultButtonTrue = LoadTexture(".\\defaultTrue.png");
Texture2D defaultButtonFalse = LoadTexture(".\\defaultFalse.png");
Texture2D defaultButtonHighlight = LoadTexture(".\\defaultHighlight.png");
//load test Button Images


/// <summary>
/// Creates a Button Object
/// </summary>
/// <param name="Callback">The function that will be called when the button is clicked</param>
/// <param name="font">The font to use for the tooltip</param>
/// <param name="Rect">size and position of the button</param>
/// <param name="Textures">{Not clicked, clicked, highlight}</param>
/// <param name="Highlight">whether to use highlight</param>
/// <param name="Toggle">whether this button is a toggle</param>
/// <param name="PoweredTimerMax">how long the button should stay powered for, (will only call callback once on a non toggle)</param>
/// <param name="Tooltip">a tooltip shown to the bottom right of the cursor</param>
/// <param name="Empty">whether the button should render textures</param>
Buttons::TextureButton::TextureButton(std::function<void(bool)> Callback, Font font = defaultFont, Rectangle Rect = { 0,0,100,100 }, std::vector<Texture2D> Textures = { defaultButtonFalse, defaultButtonTrue, defaultButtonHighlight }, bool Highlight = false, bool Toggle = false, int PoweredTimerMax = -1, std::string Tooltip = "", bool Empty = false) : mCallback(Callback), mFont(font), mRect(Rect), mTextures(Textures), mToggle(Toggle), mHighlight(Highlight), mPoweredTimerMax(PoweredTimerMax), mToolTip(Tooltip), mEmpty(Empty) {
	mRectTexture = mTextures[0];
}
void Buttons::TextureButton::SetButtonPower(bool Powered) {
	mPowered = Powered;
}
//Draw the button to the screen
void Buttons::TextureButton::Draw(Vector2 mousePos) {
	if (mPoweredTimerMax != -1) {
		if (mPoweredTimer > 0) {
			mPoweredTimer--;
			DrawTexturePro(mRectTexture, { 0,0, float(mRectTexture.width), float(mRectTexture.height) }, mRect, { .0f,.0f }, .0f, WHITE);
			return;
		}
	}
	//this button should not be a toggle
	if (!mToggle) {
		if (CheckCollisionPointRec(mousePos, mRect) && !IsMouseButtonPressed(0) && mHighlight) {
			mRectTexture = mTextures[2];
		}
		else if (CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonPressed(0)) {
			mPowered = true;
			mRectTexture = mTextures[1];
			mCallback(mPowered);
			if (mPoweredTimerMax != -1) {
				mPoweredTimer = mPoweredTimerMax;
			}
		}
		else {
			mRectTexture = mTextures[0];
			mPowered = false;
		}
	}
	//this button should be a toggle
	else {
		if (mPowered) { mRectTexture = mTextures[1]; mCallback(mPowered); }
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
	if (!mEmpty) {
		DrawTexturePro(mRectTexture, { 0,0, float(mRectTexture.width), float(mRectTexture.height) }, mRect, { .0f,.0f }, .0f, WHITE);
	}
	if (CheckCollisionPointRec(mousePos, mRect) && mToolTip != "") {
		//tooltip is enabled
		//display tooltip to the bottom right of the cursor
		//Calculate Where the tooltip will be
		Vector2 toolTipPos;
		toolTipPos.x = mousePos.x + 20;
		toolTipPos.y = mousePos.y + 20;
		DrawTextEx(mFont, mToolTip.c_str(), toolTipPos, 20, 5, WHITE);
	}
}