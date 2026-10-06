#pragma once
#include <iostream>
#include <string>

class Player
{
public:

	/// <summary>
	///	プレイヤーの名前
	/// </summary>
	std::string name;

	/// <summary>
	/// プレイヤーのHP
	/// </summary>
	int HP;

	/// <summary>
	/// プレイヤーの攻撃力
	/// </summary>
	int ATK;

	/// <summary>
	/// プレイヤーの防御力
	/// </summary>
	int DEF;
};