
#include "app.h"


bool App::isCreate = false;

std::unique_ptr<AppEnv> App::app_env;

void App::create(){
	if (!isCreate){
		app_env = std::make_unique<AppEnv>(WIDTH, HEIGHT, false, true);
		//app_env = new AppEnv();
		isCreate = true;
	}
}
