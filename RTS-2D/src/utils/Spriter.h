#pragma once
namespace Tmpl8 
{
	class Spriter
	{
	public:
		// Spriter flags
		enum
		{
			FLARE = (1 << 0),
			OPFLARE = (1 << 1),
			FLASH = (1 << 4),
			DISABLED = (1 << 6),
			GMUL = (1 << 7),
			BLACKFLARE = (1 << 8),
			BRIGHTEST = (1 << 9),
			RFLARE = (1 << 12),
			GFLARE = (1 << 13),
			NOCLIP = (1 << 14)
		};
	};
}