#pragma once

namespace Tmpl8
{
	class Map
	{
	public:
		Map() {}
		void DrawTileMap(Surface* screen);
		const bool bJustEntered = true;
		static char returnedBuffer[1000];
		float frame_timer = 0.0f;

	private:
		
	};
}
	