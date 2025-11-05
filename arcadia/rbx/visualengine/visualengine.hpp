#pragma once
#include <rbx/instance/instance.hpp>

namespace rbx {
	class c_visualengine {
	public:
		std::uint64_t address = 0;

		rbx::vector2 get_dimensions();
		rbx::matrix4 get_viewmatrix();
	 };
}