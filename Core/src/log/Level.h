#pragma once

#include <string>

namespace engine::log{

	enum class Level
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal,
	};

	std::wstring GetLevelName(Level);
}
