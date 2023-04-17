#include "Container.h"

namespace engine::ioc
{
	Container& Get() noexcept
	{
		static Container container;
		return container;
	}
}