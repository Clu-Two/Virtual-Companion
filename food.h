#pragma once 



class food_data
{
public:
	
	double hunger_reduction = 0;
	int health_restore = 10;
	int digestion_time = 5;
	int dish_fill = 50;

};

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
	bool food_list(bool& show);
	float dish_min = 0.0f;
	float dish_max = 100.0f;
	float dish_current = 0.0f;
	int dish_fill(food_data& obj);

	bool dish_full(bool& show);
	void Update();

	const char* food_empty[1] = { "has no food!" };
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

	bool Save_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
	bool Load_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
};
