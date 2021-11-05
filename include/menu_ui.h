//
//  menu.h
//  base
//
//  Created by Petr Vanek on 11.09.2021.
//

#include <string>
#include <any>
#include <variant>
#include <iostream>
#include <vector>
#include <type_traits>
#include <optional>
#include <sstream>
#include <limits>
#include <cctype>
#include "cli_ui.h"

namespace fv::ui {
/********/

class ConsoleMenu {
public:
  using functor = void (*)(std::any &param);
  struct MenuItem {
    TCHAR _key;
    std::string _itemName;
    std::variant<functor, ConsoleMenu *> _execute;
  };

private:
  std::string _menuTitle;
  std::vector<MenuItem> _menuItems;
  static const TCHAR _returnKey = static_cast<char>('q');

public:
  ConsoleMenu() {}
  ConsoleMenu(const std::string &t, const std::vector<MenuItem> &vm)
      : _menuTitle(t), _menuItems(vm) {}

  auto getTitle() const noexcept { return _menuTitle; }

  void setTitle(const std::string &t) { _menuTitle = t; }

  void run(std::any &param) { showAndExec(*this, param); }

  bool append(const MenuItem &menuItem) {
    _menuItems.emplace_back(menuItem);
    return true;
  }

  bool insert(size_t index, const MenuItem &menuItem) {
    if (index < _menuItems.size()) {
      _menuItems.insert(_menuItems.begin() + index, menuItem);
      return true;
    }

    return false;
  }

  bool erase(size_t index) {
    if (index < _menuItems.size()) {
      _menuItems.erase(_menuItems.begin() + index);
      return true;
    }

    return false;
  }

private:
  class Executor {
  private:
    std::any &_param;

  public:
    Executor(std::any &param) : _param(param) {}
    void operator()(functor func) { func(_param); }
    void operator()(ConsoleMenu *menu) {
      ConsoleMenu::showAndExec(*menu, _param);
    }
  };

  static void showAndExec(const ConsoleMenu &topMenu, std::any &param) {

    const static auto showMenuAndGetKeyLambda = [](const ConsoleMenu &mu) {
      const auto nom = mu._menuItems.size();
      tcout << "\n\n*** " << mu.getTitle() << " ***\n\n";

      for (size_t i = 0U; i < nom; ++i) {
        tcout << mu._menuItems[i]._key << TEXT(": ")
              << mu._menuItems[i]._itemName << TEXT("\n");
      }

      tcout << TEXT("--\n");
      tcout << _returnKey << TEXT(":  Quit\n\n");
      tcout << "Choice:";
      return x__getch();
    };

    while (true) {
      auto key = showMenuAndGetKeyLambda(topMenu);
      if (key == _returnKey)
        break;

      auto it = std::find_if(std::cbegin(topMenu._menuItems),
                             std::cend(topMenu._menuItems),
                             [&](const MenuItem &i) { return key == i._key; });

      if (topMenu._menuItems.end() == it) {
        tcout << TEXT("\nInvalid choice, try again.\n");
        continue;
      }

      std::visit(Executor(param), it->_execute);
    }
  }
};

} // namespace fv::ui
