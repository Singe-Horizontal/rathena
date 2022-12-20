// Copyright(C) 2022 Singe Horizontal
// Soul Link Mod
// Version 1.1
// https://github.com/Singe-Horizontal
// This code is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

#ifndef MOD_SOULLINK_HPP
#define MOD_SOULLINK_HPP
#include "../common/database.hpp"
#include "script.hpp"

namespace mods {
struct soul_link_data {
	uint16 soul_link;
	script_code* script = nullptr;
	soul_link_data(uint16 soul_link) :soul_link{ soul_link } {}
	~soul_link_data();
};

class SoulLinkDabatase : public TypesafeYamlDatabase<uint16, soul_link_data> {
public:
	SoulLinkDabatase() : TypesafeYamlDatabase("SOUL_LINK_DB", 1) {

	}
	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
};
extern SoulLinkDabatase soul_link_db;
}

#endif // !MOD_SOULLINK_HPP
