//makes sure it cannot be declared twice in a source file.
//with ifndef it checks if the header file is already defined and return a blank file is so.
//otherwise just return the header file
#ifndef Buttons_HPP
#define Buttons_HPP
#include <raylib.h>
#include <vector>
#include <functional>
#include <string>

namespace Buttons {
	class EmptyButton {
	private:
		//invisible rectangle used for collision detection
		Rectangle mRect;
		//whether this button is a toggle
		bool mToggle = false;
		//whether the button is powered
		bool mPowered = false;
		//whether this button will be highlighted when you hover over it
		bool mHighlight = false;
		//whether to show debug colours, red, green and blue
		bool mDebugColours = false;
		//doesnt show tooltip if empty
		std::string mToolTip = "";
		//debug colours
		const std::vector<Color> mColours = {RED, GREEN, BLUE};
		//the current colour
		Color mRectColour = mColours[0];
		//callback function
		std::function<void(bool)> mCallback;
	public:
		//constructor
		EmptyButton(Rectangle Rect, std::function<void(bool)> Callback, bool debugColours, std::string mToolTip);
		//draw function
		void Draw(Vector2 mousePos);
		//mPowered setter
		void SetButtonPower(bool Powered);
	};
	class TextureButton {
	private:
		//invisible rectangle used for collision detection
		Rectangle mRect;
		//textures to use for the button
		std::vector<Texture2D> mTextures;
		//current texture
		Texture2D mRectTexture = mTextures[0];
		//how long the button should stay powered (in frames) (will only call callback once if not a toggle) -1 for disabled
		int mPoweredTimerMax = -1;
		int mPoweredTimer = 0;
		//whether this button is a toggle
		bool mToggle = false;
		//whether the button is powered
		bool mPowered = false;
		//whether this button will be highlighted when you hover over it
		bool mHighlight = false;
		//
		std::string mToolTip = "";
		//callback function
		std::function<void(bool)> mCallback;
	public:
		//constructor
		TextureButton(Rectangle Rect, std::vector<Texture2D> Textures, std::function<void(bool)> Callback, bool Highlight, bool Toggle, int PoweredTimerMax, std::string mToolTip);
		//draw function
		void Draw(Vector2 mousePos);
		//mPowered setter
		void SetButtonPower(bool powered);
	};
}

#endif
