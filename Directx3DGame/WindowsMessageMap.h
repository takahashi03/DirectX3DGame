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
	// �d���s�\�ȏ��s����map(�n�b�V���ɂ��A�z�z��)
	// ���Ԃ��K�肳��Ă���map�ɔ��unordered_map�̕������x������
	std::unordered_map <DWORD, std::string>map;
};

