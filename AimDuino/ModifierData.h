#pragma once
#include <string>
namespace ModifierData {

	struct data {
		std::string type;
		float recoilMod;
		float timeOffset;
	};

	data none{
		"None",
		1.0f,
		1.0f
	};

	data silencer{
		"Silencer",
		0.8f,
		1.0f
	};

	data x8_scope{
		"8x Scope",
		3.84f,
		1.0f
	};

	data x16_scope{
		"16x Scope",
		7.68f,
		1.0f
	};

	data muzzle_boost{
		"Muzzle Boost",
		1.0f,
		0.9f
	};

	data muzzle_brake{
		"Muzzle Brake",
		0.5f,
		1.0f
	};
}