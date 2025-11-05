#pragma once
#include "visualengine.hpp"

namespace rbx {

	vector2 c_visualengine::get_dimensions() {
		return misc::g_memory->read<vector2>(this->address + Offsets::VisualEngine::Dimensions);
	}

	matrix4 c_visualengine::get_viewmatrix() {
		return misc::g_memory->read<matrix4>(this->address + Offsets::VisualEngine::ViewMatrix);
	}

}