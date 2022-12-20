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

#include "mod_soullink.hpp"
#include "skill.hpp"
namespace mods {
extern SoulLinkDabatase soul_link_db;
std::map<std::string, e_skill> slname2skill =
	{
		{"alchemist",SL_ALCHEMIST},
		{"monk",SL_MONK},
		{"stargladiator",SL_STAR},
		{"sage",SL_SAGE},
		{"crusader",SL_CRUSADER},
		{"supernovice",SL_SUPERNOVICE},
		{"knight",SL_KNIGHT},
		{"wizard",SL_WIZARD},
		{"priest",SL_PRIEST},
		{"barddancer",SL_BARDDANCER},
		{"rogue",SL_ROGUE},
		{"assassin",SL_ASSASIN},
		{"blacksmith",SL_BLACKSMITH},
		{"hunter",SL_HUNTER},
		{"soullinker",SL_SOULLINKER},
		{"ninja",SL_NINJA},
		{"gunslinger",SL_GUNNER},
	};


soul_link_data::~soul_link_data() {
	if (this->script) {
		script_free_code(this->script);
		this->script = nullptr;
	}
}

const std::string SoulLinkDabatase::getDefaultLocation(){
	return std::string(db_path) + "/soul_link_db.yml";
}

uint64 SoulLinkDabatase::parseBodyNode(const ryml::NodeRef& node) {

	std::string entry;

	if (!this->asString(node, "Soul", entry)) {
		return 0;
	}
	std::string soulname = entry;
	uint16 soul_link_id = 0;
	std::transform(soulname.begin(), soulname.end(), soulname.begin(), ::tolower);
	soulname.erase(std::remove_if(soulname.begin(), soulname.end(), [](char c) {return c == ' '; }), soulname.end());
	if (slname2skill.count(soulname))
		soul_link_id = slname2skill.at(soulname);
	else{
		this->invalidWarning(node["Soul"], "Invalid Soul Link name \"%s\", skipping.\n", entry);
		return 0;
	}
	std::shared_ptr<soul_link_data> soul_link = this->find(soul_link_id);
	bool exists = soul_link != nullptr;
	if (!exists) {

		soul_link = std::make_shared<soul_link_data>(soul_link_id);
	}

	if (this->nodeExists(node, "Script")) {
		std::string script;

		if (!this->asString(node, "Script", script))
			return 0;

		if (exists && soul_link->script) {
			script_free_code(soul_link->script);
			soul_link->script = nullptr;
		}

		soul_link->script = parse_script(script.c_str(), this->getCurrentFile().c_str(), this->getLineNumber(node["Script"]), SCRIPT_IGNORE_EXTERNAL_BRACKETS);
	} else {
		if (!exists)
			soul_link->script = nullptr;
	}
	soul_link_db.put(soul_link_id, soul_link);
	return 1;
}
}
