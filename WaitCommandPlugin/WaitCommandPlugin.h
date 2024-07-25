#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "bakkesmod/wrappers/Engine/WorldInfoWrapper.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


struct Input {
	float targetTime;
	std::string command;
};

class WaitCommandPlugin: public BakkesMod::Plugin::BakkesModPlugin
{
	std::vector<Input> inputs;
	std::optional<Input> input;

	float GetTimeInSeconds();
	void onLoad() override;
};
