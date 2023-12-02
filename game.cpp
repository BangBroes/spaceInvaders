#include <iostream>
#include "help.h"
#include <cstdlib>
#include <ctime>
#include <cmath> 

using namespace std;

// Global variables (Instead of passing to every function make it global (modern perablemss requires modern solution))

int Score = 0, Lives = 3;
char game_difficulty = 'e'; // Game difficulty e=> easy, m=> medieum, h => hard


// Struct for enemies 
struct Enemy {
	int uid;
	int x;
	int y;
	bool state;
	int score;
	char direction;
};

int random(int r_limit)
{
	srand(time(0));
	return (rand() % r_limit+1); // creates a random number between 0 and r_limit (+1 because else it will not return r_limit)
	
}

void remove(int box_x, int box_y, int width, int height, char type)
{
	myRect(box_x, box_y, box_x + width, box_y + height, 0, 0, 0);
	switch (type)
	{
	case 'c': // case c means the character or player
		myRect(box_x + 5, box_y - height + 8, box_x + width - 5, box_y - height + 15 + height, 0, 0, 0);
		myRect(box_x + 19, box_y - height - 5, box_x + width - 19, box_y - height + 15 + height, 0, 0, 0);
		myRect(box_x + 15, box_y - height + 2, box_x + width - 15, box_y - height + 15 + height, 0, 0, 0);
	}
}

void draw(int box_x, int box_y, int width, int height, int color, char type)
{
	int r, g, b, fillR, fillG, fillB;
	switch (color)
	{
	case 0: // COLOR CODING SCHEME
		// red
		fillR = 255;
		fillG = 0;
		fillB = 0;
		r = 255;
		g = 0;
		b = 0;
		break;
	case 1:
		// white
		fillR = 255;
		fillG = 255;
		fillB = 255;
		r = 255;
		g = 255;
		b = 255;
		break;
	case 2:
		// enemy
		fillR = 69;
		fillG = 69;
		fillB = 69;
		r = 105;
		g = 105;
		b = 105;
		break;
	case 3:
		// enemy
		fillR = 0;
		fillG = 0;
		fillB = 255;
		r = 0;
		g = 0;
		b = 255;
		break;
	default:
		// white
		fillR = 255;
		fillG = 255;
		fillB = 255;
		r = 255;
		g = 255;
		b = 255;
		break;
	}
	myRect(box_x, box_y, box_x + width, box_y + height, r, g, b, fillR, fillG, fillB); //bottom spaceship
	switch (type)
	{
	case 'c': //player
		myRect(box_x + 5, box_y - height + 8, box_x + width - 5, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship 2nd part
		myRect(box_x + 15, box_y - height + 2, box_x + width - 15, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship shooter part
		myRect(box_x + 19, box_y - height - 5, box_x + width - 19, box_y - height + 15, r, g, b, fillR, fillG, fillB); // spaceship gun part
		break;
	}

}

bool checkBullet(int b_x, int b_y, Enemy e[], int total, bool enemyPrespective = false, int box_x=0, int box_y=0, int width=0,int height=0) {
	if (enemyPrespective == false) {
		for (int i = 0; i < total; i++) {
			//cout << "{" << b_x << " , " << e[i].x << ", " << e[i].x + 30 << "} ";
			//cout << (b_x >= e_x && b_x <= e_x + 100 && b_y >= e_y && b_y <= e_y + 30);
			if (e[i].state) {
				if (b_x >= e[i].x - 20 && b_x <= e[i].x + 15 && b_y >= e[i].y && b_y <= e[i].y + 70) {// 30 is width of enemy
					remove(e[i].x, e[i].y, 30, 30, 'e');
					Score += e[i].score;
					e[i].state = false;
					return true;
				}
			}
		}
		return false;
	}
	else {
		if (b_x >= box_x-width/2 && b_x <= box_x + width/2 && b_y >= box_y-20 && b_y <= box_y + height){
			Lives -= 1;
			Sleep(10);
			remove(b_x, b_y, 2, 15, 'b'); // remove the bullet when collide with player 

			return true;
		}
		else {
			return false;
		}
	}
}

void updateEnemy(Enemy e[], char direction, int total) {
	for (int i = 0; i < total; i++) {
		e[i].direction = direction;
	}
}

void display_lives(int width,int height) {
	int live_x = 800, live_y = 15;
	for (int i = 0; i < Lives; i++) {
		live_x += width + 20;
		draw(live_x, live_y, width, height, 1, 'c');
	}
}

void move_enemies(Enemy e[], int total, int r_limit, int l_limit, int b_limit, char& previous_direction) {
	Sleep(2);
	int step_horizontal = 1;
	int step_vertical = 10;
	//char previous_direction = ' '; // to keep track of previous direction before moving down so after moving down we can change position to this (updated: now declared in  main function)
	switch (game_difficulty) {
		case 'e':
		{
			step_horizontal = 1;
			step_vertical = 8;
			break;
		}
		case 'm':
		{
			step_horizontal = 3;
			step_vertical = 13;
			break;

		}
		case 'h':
		{
			step_horizontal = 8;
			step_vertical = 18;
			break;

		}
	}
	
	for (int i = 0; i < total; i++) {
		if (e[i].state) {
			if (e[i].direction == 'r') {
				if (e[i].x+30 >= r_limit) {
					for (int j = 0; j < total; j++) {
						e[j].direction = 'd'; // Move Down
						previous_direction = 'l';
					}
					break;
				}
				else {
					remove(e[i].x, e[i].y, 30, 30, 'e'); // 30 is the width and height
					e[i].x += step_horizontal;
					draw(e[i].x, e[i].y, 30, 30, 2, 'e'); // 2 is enemy color coding sceheme
				}
			}
			else if (e[i].direction == 'l') {
				if (e[i].x-30 <= l_limit) {
					for (int j = 0; j < total; j++) {
						e[j].direction = 'd'; // Move Down
						previous_direction = 'r';
					}
					break;
				}
				else {
					remove(e[i].x, e[i].y, 30, 30, 'e'); // 30 is the width and height
					e[i].x -= step_horizontal;
					draw(e[i].x, e[i].y, 30, 30, 2, 'e'); // 2 is enemy color coding sceheme
				}
			}else if (e[i].direction == 'd'){
				remove(e[i].x, e[i].y, 30, 30, 'e'); // 30 is the width and height
				e[i].y += step_vertical;
				draw(e[i].x, e[i].y, 30, 30, 2, 'e'); // 2 is enemy color coding sceheme
				e[i].direction = previous_direction;
			}
		}
	}

}

void shoot_bullet_player(int& bullet_x, int& bullet_y, Enemy enemies[], int number_of_enemies , int top_limit , bool& shoot, bool& state_bullet) {
	Sleep(5);
	int step_bullet = -30;
	remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
	bullet_y += step_bullet;
	draw(bullet_x + 19, bullet_y - 35, 2, 15, 0, 'b');
	if (checkBullet(bullet_x, bullet_y, enemies, number_of_enemies) || bullet_y < top_limit + 42) {
		shoot = false;
		remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
		state_bullet = false;
	}
}

void shoot_bullet_enemy(int& bullet_x, int& bullet_y, int box_x, int box_y, int bottom_limit, bool& shoot, bool& state_bullet, int width_box, int height_box) {
	Enemy e[1]; // creating a prototype Enemies that I can pass to check bullet function
	Sleep(5);
	int step_bullet = 20;
	remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
	bullet_y += step_bullet;
	draw(bullet_x + 19, bullet_y - 35, 2, 15, 3, 'b');
	if (bullet_y >= bottom_limit || checkBullet(bullet_x, bullet_y, e, 0,true,box_x,box_y,width_box,height_box)){
		shoot = false;
		remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
		state_bullet = false;
	}
}

int main()
{
	int left_limit = 20, right_limit = 940, top_limit = 30, bottom_limit = 470; // defining limits
	int box_x = 400, box_y = 400, step_size = 7, height = 12, width = 40; // player
	char direction = ' ';
	bool game_state = true; //true while playing and false when lost
	int oldScore = Score;
	int score_x = 1, score_y = -5; // score Axis for further reference



	// Bullet iniitialization (Player)

	bool shoot = false; // state of the bullet true => Shoot button is pressed is there and vice versa
	int bullet_x = 30, bullet_y = 360; // bullet
	bool state_bullet = false; //

	// Bullet iniitialization (Enemies)

	bool shoot_e = false; // state of the bullet true 
	int bullet_x_e = 30, bullet_y_e = 360; // bullet
	bool state_bullet_e = false; 
	int shooter_index = 0; // stores the enemy who shot 


	// Enemy initialization
	int latest_x = 30, latest_y = top_limit+10; // axis where you want to start putting your enemies 
	const int number_of_enemies = 50, rows = 5, columns = 10; // constant
	Enemy enemies[number_of_enemies]; // array of my created struct
	int index = 0; // uid
	char previous_direction = ' '; // instead of making this in moving enemies create it here and pasas it by reference to avoid loss of data



	for (int i = 0; i < rows; ++i) {
		// handling rows of enemies
		for (int j = 0; j < columns; j++) {
			// handling columns of enemies
			switch (i) {
			case 4: // Assigning score based on the row number of the enemies // Lowest score to first row , more to second row and like that most to last (top) row 
				enemies[index].score = 20;
				break;
			case 3:
			case 2:
				enemies[index].score = 30;
				break;
			case 1:
				enemies[index].score = 40;
				break;
			case 0:
				enemies[index].score = 50;
				break;

			}
			enemies[index].x = latest_x + 30;
			enemies[index].uid = index;
			enemies[index].y = latest_y;
			enemies[index].state = true;
			enemies[index].direction = 'r';
			latest_x += 70;
			index++;
		}
		latest_y += 40;
		latest_x = 30;
	}


	// drawText function draws text on the screen with arguments size, x, y, r, g, b, text
	myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 0, 0, 139); // myRect function draws a rectangle with arguments x1, y1, x2, y2, r, g, b, r2, g2, b2
	//drawText(16, score_x, score_y, 25, 255, 255, "0"); // draw score as a string in the beginning because 0 doesn't show in thius function when passed as a integer
	drawText(16, right_limit/2-110, score_y, 25, 255, 255, "SPACE INVADERS");
	draw(box_x, box_y, width, height, 1, 'c');
	
	for (int i = 0; i < number_of_enemies; i++) { // create enemies 
		draw(enemies[i].x, enemies[i].y, 30, 30, 2, 'e');
	}


	int whichKey = 0;

	while (whichKey != 7) // 7 is the code for ESC key
	{
		if (isKeyPressed(whichKey)) // isKeyPressed function returns true if a key is pressed and whichKey tells that which key was pressed
		{
			switch (whichKey)
			{
			case 1:
				direction = 'L';
				break;
			case 2:
				direction = 'U';
				break;
			case 3:
				direction = 'R';
				break;
			case 4:
				direction = 'D';
				break;
			case 8: // space key ADDED IN HELP.H
				shoot = true;
				break;
			}
		}

		// enemies shoot randomly logic is implemented here

		if (random(5) == 3 && !shoot_e) {
			shoot_e = true;
		}

		if (shoot_e && !state_bullet_e) {
			for (int i = number_of_enemies-1; i > 0; i--) {
				int distance = abs(enemies[i].x - box_x);
				if (distance <= 30 && enemies[i].state) { // checks distance among box and enemy
					shooter_index = i;
					state_bullet_e = true;
					break;
				}
			}
			/*shooter_index = -1;
			srand(time(0));
			do {
				shooter_index = random(number_of_enemies-1);
			} while (!enemies[shooter_index].state);*/
			bullet_x_e = enemies[shooter_index].x-5;
			bullet_y_e = enemies[shooter_index].y+65;
			state_bullet_e = true;
		}

		Sleep(10); // 25 milliseconds
		if (shoot && !state_bullet) {
			bullet_x = box_x;
			bullet_y = box_y;
			draw(bullet_x + 19, bullet_y - 35, 2, 15, 0, 'b');
			state_bullet = true;
		}

		if (game_state == false) {
			myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 139, 0, 0); // change color when user lost the game
		}
		else {
			// bullet movement
			if (shoot && state_bullet) { // call a bullet function for player => parent
				shoot_bullet_player(bullet_x, bullet_y, enemies, number_of_enemies, top_limit, shoot, state_bullet); 
			}
			if (shoot_e && state_bullet_e) {// call a bullet function for enemy[shoter_index] => parent
				shoot_bullet_enemy(bullet_x_e, bullet_y_e,box_x, box_y, bottom_limit, shoot_e, state_bullet_e,width,height); // parent is player 'p'
			}
			move_enemies(enemies, number_of_enemies, right_limit, left_limit, bottom_limit,previous_direction);
			display_lives(width,height);

			// update header of game (includes game_score) except game name
			if (Score != 0) { // Score doesn't show when 0 so use a string when score is 0
				remove(score_x, score_y, right_limit / 2 - 120, 31, 'b');  // basically removes the whole header of game to update game header before Game name
				remove(right_limit / 2 + 130, score_y, right_limit, 31, 'b');  // basically removes the whole header of game to update game header before Game name
				drawText(16, score_x, score_y, 25, 255, 255, "", true, Score);
				drawText(16, score_x + 100, score_y, 25, 255, 255, "", true, Lives);
			}

			switch (direction)
			{
			case 'L':
				// Left
				step_size = 8;
				remove(box_x, box_y, width, height, 'c');
				if (box_x-10 > left_limit)
					box_x -= step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			case 'U':
				// Up
				step_size = 4;
				remove(box_x, box_y, width, height, 'c');
				if (box_y - 20 > top_limit) // right_limit/2+90 if want to restrict movement half way of player
					box_y -= step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			case 'R':
				// Right
				step_size = 8;
				remove(box_x, box_y, width, height, 'c');
				if (box_x + 50 < right_limit)
					box_x += step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			case 'D':
				// Down
				step_size = 4;
				remove(box_x, box_y, width, height, 'c');
				if (box_y + 20 < bottom_limit)
					box_y += step_size;
				draw(box_x, box_y, width, height, 1, 'c');
				direction = ' ';
				break;
			}
		}
	}
	return 0;
}
