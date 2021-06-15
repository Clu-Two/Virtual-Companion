#pragma once 



class food_data
{
public:
	
	char food_name[100] = "void \0";
	double hunger_reduction = 0;
	int health_restore = 0;
	int digestion_time = 0;
	int dish_fill = 0;
};


// why u wana save food ? // Don't need to// 
// Originally I wanted to avoid initialising variables in code, for practice
// bret pratice u should always init ur variables// sure, but say I want to balance, balance , init to 0 , load from database ur value // ok
class food_menu
{

public:

	food_data potato;
	food_data pizza;
	food_data carrot;
	food_data salad;
	food_data doughnut;
	food_data brownie;
};

class food_dish
{

public:

	void Eater(food_dish& obj);
	bool food_list( bool& show);
	float dish_min = 0.0f;
	float dish_max = 100.0f;
	float dish_current = 0.0f;
	int dish_fill(food_data& obj);

	bool dish_full(bool& show);
	void Update();

	const char* food_empty = { "has no food!" };
	food_menu food_menu_obj;

};


class food_manager  
{
public:
	food_menu food_menu_obj;

	enum class DB_Type
	{
		FILE,
		SQLITE
	};

};
