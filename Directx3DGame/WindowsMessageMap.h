#pragma once
#include <unordered_map>
#include <Windows.h>

class WindowsMessageMap
{
public:
	WindowsMessageMap();
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
private:
	// unordered_map
	// 重複不可能な順不同のmap(ハッシュによる連想配列)
	// 順番が規定されているmapに比べunordered_mapの方が速度が速い
	std::unordered_map <DWORD, std::string>map;
};

