#include "pch.h"
#include "WaitCommandPlugin.h"


BAKKESMOD_PLUGIN(WaitCommandPlugin, "WaitCommandPlugin", plugin_version, PLUGINTYPE_FREEPLAY);

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void WaitCommandPlugin::onLoad()
{
	auto createInput = [this](std::vector<std::string> args, std::function<void(Input newInput)> callback)
		{
			if (args.size() != 3) {
				cvarManager->log("Syntax: wait <ms> <command>");
				return;
			}

			std::string timeoutInMs = args[1];
			std::string command = args[2];

			float timeoutInSeconds = std::stof(timeoutInMs) / 1000.f;
			float targetTime = GetTimeInSeconds() + timeoutInSeconds;

			callback({ targetTime, command });
		};

	cvarManager->registerNotifier(
		"wait",
		[this, createInput](std::vector<std::string> args)
		{
			createInput(
				args,
				[this](Input newInput) { inputs.push_back(newInput); }
			);
		},
		"Run a command after a timeout - works with multiple commands",
		PERMISSION_ALL
	);

	cvarManager->registerNotifier(
		"wait_once",
		[this, createInput](std::vector<std::string> args)
		{
			createInput(
				args,
				[this](Input newInput) { input = newInput; }
			);
		},
		"Run a command after a timeout - overwrite the previous command",
		PERMISSION_ALL
	);

	gameWrapper->HookEvent(
		"Function TAGame.Car_TA.SetVehicleInput",
		[this](std::string eventName)
		{
			if (inputs.empty() && !input) {
				return;
			}

			float time = GetTimeInSeconds();

			if (input && time >= input->targetTime) {
				cvarManager->executeCommand(input->command);
				input.reset();
			}

			for (auto inputIter = inputs.begin(); inputIter != inputs.end(); ) {
				if (time >= inputIter->targetTime) {
					cvarManager->executeCommand(inputIter->command);
					inputIter = inputs.erase(inputIter);
				}
				else {
					inputIter++;
				}
			}
		}
	);
}

float WaitCommandPlugin::GetTimeInSeconds()
{
	return gameWrapper->GetCurrentGameState().GetWorldInfo().GetTimeSeconds();
}
