#include <iostream>
#include "help.h"
#include <cstdlib>
#include <ctime>

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
		fillR = 0;
		fillG = 62;
		fillB = 91;
		r = 255;
		g = 0;
		b = 0;
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

bool checkBullet(int b_y, int b_x, Enemy e[], int total) {
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


void updateEnemy(Enemy e[], char direction, int total) {
	for (int i = 0; i < total; i++) {
		e[i].direction = direction;
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


int main()
{
	cout << random(5);
	int left_limit = 20, right_limit = 940, top_limit = 30, bottom_limit = 470; // defining limits
	int box_x = 400, box_y = 400, step_size = 7, height = 12, width = 40; // player
	char direction = ' ';
	bool game_state = true; //true while playing and false when lost
	int oldScore = Score;
	int score_x = 1, score_y = -5; // score Axis for further reference



	// Bullet iniitialization

	bool shoot = false; // state of the bullet true => Shoot button is pressed is there and vice versa
	int bullet_x = 30, bullet_y = 360, step_bullet = 30; // bullet
	bool state_bullet = false; //

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
			case 6:
				shoot = true;
				break;
			}
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
			if (shoot && state_bullet) {
				Sleep(25);
				remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
				bullet_y -= step_bullet;
				draw(bullet_x + 19, bullet_y - 35, 2, 15, 0, 'b');
				if (checkBullet(bullet_y, bullet_x, enemies, number_of_enemies) || bullet_y < top_limit + 42) {
					shoot = false;
					remove(bullet_x + 19, bullet_y - 35, 2, 15, 'b');
					state_bullet = false;
				}
			}
			move_enemies(enemies, number_of_enemies, right_limit, left_limit, bottom_limit,previous_direction);

			// update header of game (includes game_score) except game name
			if (Score != 0) { // Score doesn't show when 0 so use a string when score is 0
				remove(score_x, score_y, right_limit / 2 - 120, 31, 'b');  // basically removes the whole header of game to update game header before Game name
				remove(right_limit / 2 + 130, score_y, right_limit, 31, 'b');  // basically removes the whole header of game to update game header before Game name
				drawText(16, score_x, score_y, 25, 255, 255, "", true, Score);
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
