#include <raylib.h>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <Buttons.hpp>
using std::vector;
/// <summary>
	/// Creates a Button object
	/// </summary>
	/// <param name="Rect">{x, y, width, height}</param>
	/// <param name="Textures">{Not Pressed, Pressed, Hovered}</param>
	/// <param name="Callback">A function the button will call when pressed P.S if a button is a toggle this will be called every frame that the button is powered</param>
	/// <param name="Toggle">Whether the button will be a toggle</param>
Buttons::TextureButton::TextureButton(Rectangle Rect, vector<Texture2D> Textures, std::function<void(bool)> Callback, bool Highlight = true, bool Toggle = false, int PoweredTimerMax = -1, std::string Tooltip = "") : mRect(Rect), mTextures(Textures), mCallback(Callback), mToggle(Toggle), mHighlight(Highlight), mPoweredTimerMax(PoweredTimerMax), mToolTip(Tooltip) {
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
	DrawTexturePro(mRectTexture, { 0,0, float(mRectTexture.width), float(mRectTexture.height) }, mRect, { .0f,.0f }, .0f, WHITE);
}


void Buttons::EmptyButton::SetButtonPower(bool Powered) {
	mPowered = Powered;
}
//Draw the button to the screen
void Buttons::EmptyButton::Draw(Vector2 mousePos) {
	
	//this button should not be a toggle
	if (mDebugColours) {
		if (!mToggle) {
			if (CheckCollisionPointRec(mousePos, mRect) && !IsMouseButtonPressed(0) && mHighlight) {
				mRectColour = mColours[2];
				//create tooltip
				if (mToolTip != "") {

				}

			}
			else if (CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonPressed(0)) {
				mPowered = true;
				mRectColour = mColours[1];
				mCallback(mPowered);

			}
			else {
				mRectColour = mColours[0];
				mPowered = false;
			}
		}
		DrawRectangle(mRect.x, mRect.y, mRect.width, mRect.height, mRectColour);
	}
	else {
		if (!mToggle) {
			if (CheckCollisionPointRec(mousePos, mRect) && IsMouseButtonPressed(0)) {
				mPowered = true;
				mCallback(mPowered);
			}
			else {
				mPowered = false;
			}
		}
		DrawRectangle(mRect.x, mRect.y, mRect.width, mRect.height, { 0,0,0,0 });
	}
}
/// <summary>
/// an Empty Button (no image), can be used for stuff like scene transitions
/// </summary>
/// <param name="Rect">{x, y, width, height}</param>
/// <param name="Callback">A function the button will call when pressed</param>
/// <param name="debugColours">Colour the buton using red green and blue for debugging purposes</param>
Buttons::EmptyButton::EmptyButton(Rectangle Rect, std::function<void(bool)> Callback, bool debugColours = false, std::string Tooltip = "") : mRect(Rect), mCallback(Callback), mDebugColours(debugColours), mToolTip(Tooltip) {
}