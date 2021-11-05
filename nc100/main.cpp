//
//  main.cpp
//  nc100
//
//  Created by Petr Vanek on 30.08.2021.
//
#include <string>
#include <iostream>

#include <tuple>
#include <vector>
#include <algorithm>
#include "application.h"
#include "../utils/dirs.h"
#include "../utils/file.h"



int _tmain(int argc, const TCHAR *argv[]) {
    
  auto app = fv::ui::App::Factory::createInstance();
  app->wmain(argc, argv);
  return 0;
}
