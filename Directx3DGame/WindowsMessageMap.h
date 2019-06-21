#pragma once
#include <unordered_map>
#include "MyWindows.h"

class WindowsMessageMap
{
public:
	WindowsMessageMap() noexcept;
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const noexcept;
private:
	// unordered_map
	// 重複不可能な順不同のmap(ハッシュによる連想配列)
	// 順番が規定されているmapに比べunordered_mapの方が速度が速い
	std::unordered_map <DWORD, std::string>map;
};

