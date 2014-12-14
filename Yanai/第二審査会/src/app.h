
#pragma once
#include "common.h"
#include <memory>


class App{
	App() = default;
	static bool isCreate;

public:
	static std::unique_ptr<AppEnv> app_env;
	//AppEnv* app_env;
	static void create();
};
