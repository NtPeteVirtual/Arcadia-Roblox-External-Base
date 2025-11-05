#pragma once
#include "instance.hpp"

namespace rbx {

	std::string c_instance::get_name() {
		std::uint64_t name = misc::g_memory->read<std::uint64_t>(this->address + Offsets::Instance::Name);

		if (name) {
			return misc::g_memory->read_string(name);
		}

		return "unknown";
	}

	std::string c_instance::get_class_name() {
		std::uint64_t class_descriptor = misc::g_memory->read<std::uint64_t>(this->address + Offsets::Instance::ClassDescriptor);
		std::uint64_t class_name = misc::g_memory->read<std::uint64_t>(class_descriptor + Offsets::Instance::ClassName);

		if (class_name) {
			return misc::g_memory->read_string(class_name);
		}

		return "unknown";
	}

	std::vector<c_instance> c_instance::get_children() {
		std::vector<c_instance> children;

		std::uint64_t children_start = misc::g_memory->read<std::uint64_t>(this->address + Offsets::Instance::ChildrenStart);
		std::uint64_t children_end = misc::g_memory->read<std::uint64_t>(children_start + Offsets::Instance::ChildrenEnd);

		for (auto i = misc::g_memory->read<std::uint64_t>(children_start); i != children_end; i += 0x10) {
			children.emplace_back(misc::g_memory->read<c_instance>(i));
		}

		return children;
	}

	c_instance c_instance::find_first_child(std::string name) {
		std::vector<c_instance> children = this->get_children();

		for (auto child : children) {
			if (child.get_name() == name) {
				return child;
			}
		}

		return c_instance();
	}

	c_instance c_instance::find_first_child_of_class(std::string name) {
		std::vector<c_instance> children = this->get_children();

		for (auto child : children) {
			if (child.get_class_name() == name) {
				return child;
			}
		}

		return c_instance();
	}

	c_instance c_instance::get_parent() {
		return misc::g_memory->read<c_instance>(this->address + Offsets::Instance::Parent);
	}
}