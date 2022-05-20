#include <iostream>
#include "windows.h"
#include <unordered_map>
#include <string>
#include <time.h> 
#include <vector>
#include <forward_list>
#include <utility>
#include <stack>
#include <chrono>
#include "defines.h"
using namespace std;


//initializations
int diff = 1;
int player_mode = 1;
int space_x = ((width - 1) / 2) - (space_len - 1) / 2 - 1;
int space_y = length - 4;
int stack_x = width + 9;
int stack_y = length - 6;
float slope = 0;
int dir = -1;
int x = midx;
int y = midy;
int stage = 1;
int flag = 0;
unordered_map<int, char> slab_gen
{
	//slab generator
	{0,219},	//█
	{1,176},	//░
	{2,178},	//▓
	{3,186},	//║	
	{4,205}		//═

};

stack<char> the_stack;
vector<char> slabs;


//time calculations
int time_elp_generate_1;
int time_elp_generate_2;
forward_list<long> time_elp_ball_movement;
forward_list<long> time_elp_space_movement;

char map[length][width + stack_width + 1] = {
	"                                                                                               ",
	" ##############################################################################################",
	" ##############################################################################################",
	" ##                                                            ##                            ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        #            #      ##",
	" ##                                                            ##        ##############      ##",
	" ##                                                            ##          THE  STACK        ##",
	" ##                                                            ##                            ##",
	" ##############################################################################################",
	" ##############################################################################################"

};
char start_map[length][width + stack_width + 1] = {
	"                                                                                               ",
	" ##############################################################################################",
	" ##############################################################################################",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##                        Mode                                  Difficulty                  ##",
	" ##                    ____________                             ____________                 ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##             --->   Single Player                        --->    Easy                     ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##                    Multi Player                                Medium                    ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##       CREATED BY: Moatasem Bayoumi                                                       ##",
	" ##                   Ahmed Mohamed Ibrahim                         Hard                     ##",
	" ##                   Hassan Moataz                                                          ##",
	" ##                   Hussain Moataz		                                             ##     ",
	" ##                   Ziad hassan ahmed                                                      ##",
	" ##                                                                                          ##",
	" ##############################################################################################",
	" ##############################################################################################"

};
char mid_map[length][width + stack_width + 1] = {
	"                                                                                               ",
	" ##############################################################################################",
	" ##############################################################################################",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##      #########   #                  #           #      #   #########    #########        ##",
	" ##      #       #   #                 # #          #      #   #            #       #        ##",
	" ##      #       #   #                #   #         #      #   #            #       #        ##",
	" ##      #########   #               #     #        ########   #########    #########        ##",
	" ##      #           #              #########              #   #            # #              ##",
	" ##      #           #             #         #             #   #            #  #             ##",
	" ##      #           #            #           #            #   #            #    #           ##",
	" ##      #           ########    #             #    ########   #########    #      #         ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##            ########                    ###########   #      #    #######   #    #        ##",
	" ##                   #                         #        #      #    #     #   ##   #        ##",
	" ##                   #                         #        #      #    #######   # #  #        ##",
	" ##            ########                         #        #      #    # #       #  # #        ##",
	" ##            #                                #        #      #    #  #      #   ##        ##",
	" ##            ########                         #        ########    #   #     #    #        ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##############################################################################################",
	" ##############################################################################################"

};
char player_one_win_map[length][width + stack_width + 1] = {
	"                                                                                               ",
	" ##############################################################################################",
	" ##############################################################################################",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##      #########   #                  #           #      #   #########    #########        ##",
	" ##      #       #   #                 # #          #      #   #            #       #        ##",
	" ##      #       #   #                #   #         #      #   #            #       #        ##",
	" ##      #########   #               #     #        ########   #########    #########        ##",
	" ##      #           #              #########              #   #            # #              ##",
	" ##      #           #             #         #             #   #            #  #             ##",
	" ##      #           #            #           #            #   #            #    #           ##",
	" ##      #           ########    #             #    ########   #########    #      #         ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##                #                 #                 #    ###########    #         #       ##",
	" ##              # #                  #               #     #         #    # #       #       ##",
	" ##            #   #                   #      #      #      #         #    #   #     #       ##",
	" ##                #                    #    # #    #       #         #    #     #   #       ##",
	" ##                #                     #  #   #  #        #         #    #       # #       ##",
	" ##            ########                   #      #          ###########    #         #       ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##############################################################################################",
	" ##############################################################################################"

};
char player_two_win_map[length][width + stack_width + 1] = {
	"                                                                                               ",
	" ##############################################################################################",
	" ##############################################################################################",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##      #########   #                  #           #      #   #########    #########        ##",
	" ##      #       #   #                 # #          #      #   #            #       #        ##",
	" ##      #       #   #                #   #         #      #   #            #       #        ##",
	" ##      #########   #               #     #        ########   #########    #########        ##",
	" ##      #           #              #########              #   #            # #              ##",
	" ##      #           #             #         #             #   #            #  #             ##",
	" ##      #           #            #           #            #   #            #    #           ##",
	" ##      #           ########    #             #    ########   #########    #      #         ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##            ########              #                 #    ###########    #         #       ##",
	" ##                   #               #               #     #         #    # #       #       ##",
	" ##                   #                #      #      #      #         #    #   #     #       ##",
	" ##            ########                 #    # #    #       #         #    #     #   #       ##",
	" ##            #                         #  #   #  #        #         #    #       # #       ##",
	" ##            ########                   #      #          ###########    #         #       ##",
	" ##                                                                                          ##",
	" ##                                                                                          ##",
	" ##############################################################################################",
	" ##############################################################################################"

};


void elapsed_time() 
{

	cout << endl;
	cout << "All numbers in nanosecond" << endl;	
	cout << endl;
	cout << "Time elpased for generate stage 1 = " << time_elp_generate_1 << endl;
	cout << "Time elpased for generate stage 2 = " << time_elp_generate_2 << endl;
	cout << endl;
	cout << endl;
	long long time = 0;
	long longest = 0;
	long shortest = 10000000000;
	long count = 0;
	forward_list<long>::iterator it = time_elp_ball_movement.begin();

	for (; it != time_elp_ball_movement.end(); it++)
	{
		if (*it < 0)
			continue;
		count++;
		longest = *it > longest ? *it : longest;
		shortest = *it < shortest ? *it : shortest;
		time += *it;
	}
	time = time / count;

	cout << "The number of the moves of the ball = " << count << endl;
	cout << "The longest time = " << longest << endl;
	cout << "The shortest time = " << shortest << endl;
	cout << "The average time for ball movement = " << time << endl;
	cout << endl;
	cout << endl;

	if (player_mode == 1)
	{
		time = 0;
		longest = 0;
		shortest = 10000000000;
		count = 0;
		it = time_elp_space_movement.begin();
		for (; it != time_elp_space_movement.end(); it++)
		{
			if (*it < 1)
				continue;
			count++;
			longest = *it > longest ? *it : longest;
			shortest = *it < shortest ? *it : shortest;
			time += *it;
		}
		time = time / count;

		cout << "The number of the moves of the space = " << count << endl;
		cout << "The longest time = " << longest << endl;
		cout << "The shortest time = " << shortest << endl;
		cout << "The average time for space movement = " << time << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;	
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}


void arrow_pos(int x_old, int y_old, int x_new, int y_new)
{
	//delete the old arrow
	for (int j = x_old; j < x_old + 4; j++)
	{
		start_map[y_old][j] = ' ';
	}

	int i = x_new;
	for (; i < x_new + 3; i++)
	{
		start_map[y_new][i] = '-';
	}
	start_map[y_new][i] = '>';
}
void place_the_ball()
{
	map[y][x] = ' ';
	x = midx;
	y = midy;
	map[midy][midx] = ball;
}
void place_the_space()
{	
	for (int i = 0; i < space_len; i++)
	{
		map[space_y][space_x + i] = ' ';
	}
	space_x = spacex;
	space_y = spacey;

	for (int i = 0; i < space_len; i++)
	{
		map[space_y][space_x + i] = '-';
	}
}
void space_move(int space_move)
{

	if (space_move == 1 && (space_x + space_len) < right_bond)
	{
		map[space_y][space_x] = ' ';
		map[space_y][space_x + space_len] = '-';
		space_x = space_x + 1;

	}
	else if (space_move == -1 && (space_x) > left_bond)
	{
		space_x = space_x - 1;
		map[space_y][space_x] = '-';
		map[space_y][space_x + space_len] = ' ';
	}
}
void slab_fill(int x ,int y,char type) 
{
	for (int i = x; i < x + slab_len; i++)
		map[y][i] = type;
	
}
int return_slab_boundary(int x)
{
	int pos = x - 2;
	int slab_index = ceil( (float) pos / (float)slab_len ) - 1;

	int x1 = 3 + slab_index * (slab_len);

	return x1;
}
void stack_push(char ch)
{
	int next_input = the_stack.size();
	the_stack.push(map[y - 1][x]);

	slab_fill(stack_x, stack_y - next_input, map[y - 1][x]);
}
void stack_pop()
{
	int next_input = the_stack.size();
	the_stack.pop();

	slab_fill(stack_x, stack_y - next_input + 1, ' ');
}
void winner(int player)
{
	system("cls");
	if (player == 1)
	{
		for (int display = 0; display < length; display++)
			cout << player_one_win_map[display] << endl;
	}
	if (player == 2)
	{
		for (int display = 0; display < length; display++)
			cout << player_two_win_map[display] << endl;
	}
	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;

	}
}
int out_of_Range()
{
	if (x > (space_x + space_len) )
	{
		return 1;
	}
	else if (x < space_x )
	{
		return -1;
	}
	return 0;
}

void end_stage_2() {

	system("cls");
	for (int display = 0; display < length; display++)
		cout << map[display] << endl;

	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;

	}
	//player two win
	if (the_stack.empty())
		winner(2);

	//player one win
	else
		winner(1);


	system("cls");
	elapsed_time();
	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;

	}
	exit(0);
}
void generate_stage_2(int diff)
{
	auto start = chrono::steady_clock::now();
	system("cls");
	dir = -1;
	slope = 0;
	stage = 1;
	stage = 2;
	place_the_ball();
	place_the_space();
	//place the generated slabs
	for (int i = 1; i < diff + 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			slab_fill(3 + j * slab_len, up_bond - i + diff + 1, slabs[(i - 1) * 5 + j]);
		}
	}
	//show and wait
	for (int display = 0; display < length; display++)
	{
		cout << map[display] << endl;
	}
	auto end = chrono::steady_clock::now();
	time_elp_generate_2 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;

	}
	system("cls");
}
void end_stage_1()
{
	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;
	}
	system("cls");
		for (int display = 0; display < length; display++)
			cout << mid_map[display] << endl;
	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;
	}
	flag = 1;
	generate_stage_2(diff);

}
void generate_stage_1(int diff, int player_form)
{
	// diff
	// easy -> 1 layer
	// mid  -> 2 layer
	// hard -> 3 layer
	// layer === 5 slab
	auto start = chrono::steady_clock::now();

	//starting first stage conditions
	dir = -1;
	slope = 0;
	stage = 1;
	place_the_space();
	place_the_ball();

	srand(time(0));

	//slabs generator
	for (int i = 1; i < diff + 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//generate random shape
			int rand1 = rand() % slab_type_number;
			char slab = slab_gen[rand1];

			//save the genertated slabs
			slabs.push_back(slab);

			//			horizontal move		   vertical move
			//				  ||		     	    ||
			//				  \/			        \/
			//       (                        )(           )
			slab_fill(left_bond + j * slab_len, up_bond + i, slab);
		}
	}
	for (int display = 0; display < length; display++)
	{
		cout << map[display] << endl;
	}

	auto end = chrono::steady_clock::now();
	time_elp_generate_1 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

void ball_movement()
{
	auto start = chrono::steady_clock::now();

	// Destroying slab
	if ((map[y - 1][x] != ' ' && map[y - 1][x] != '#') && dir == 1)
	{
		int x1 = return_slab_boundary(x);

		// First stage : stack pushing
		if (stage == 1)
			stack_push(map[y - 1][x]);
		// Second stage : stack poping
		else
		{     // Hitting slab as slabs in the stack 
			char above_slab = map[y - 1][x];
			if (above_slab == the_stack.top())   // If the slab was at the top of the slab
			{
				stack_pop();
				if (the_stack.empty())
				{
					end_stage_2();             // Player 2 Won
				}
			}
			else
				end_stage_2();              // Player 1 Won
		}

		slab_fill(x1, y - 1, ' ');        // Remove the hitted slab from screen

		// Reflect the ball after hitting a slab
		dir *= -1;
		slope *= -1;

		// Player 1 finished the game
		if (the_stack.size() == diff * 5)
		{
			for (int display = 0; display < length; display++)
			{
				cout << map[display] << endl;
			}
			end_stage_1();
		}
	}
	// Normal cases of moving in the screen
	else if (dir == 1)
	{
		if (slope == -1)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y - 1][x - 1] = ball;
			y = y - 1;
			x = x - 1;
		}
		else if (slope == -0.5)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y - 1][x - 2] = ball;
			y = y - 1;
			x = x - 2;
		}
		else if (slope == 0)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y - 1][x] = ball;
			y = y - 1;
		}
		else if (slope == 0.5)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y - 1][x + 2] = ball;
			y = y - 1;
			x = x + 2;
		}
		else
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y - 1][x + 1] = ball;
			y = y - 1;
			x = x + 1;
		}
		if (up_bond == y - 1)
		{
			dir *= -1;
			slope *= -1;
		}
		if (right_bond == x + 1)
		{
			slope *= -1;
		}
		if (left_bond == x - 1)
		{
			slope *= -1;
		}
	}

	else if (dir == -1)  // The ball is falling
	{
		if (slope == -1)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y + 1][x + 1] = ball;
			y = y + 1;
			x = x + 1;
		}
		else if (slope == -0.5)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y + 1][x + 2] = ball;
			y = y + 1;
			x = x + 2;
		}
		else if (slope == 0)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y + 1][x] = ball;
			y = y + 1;
		}
		else if (slope == 0.5)
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y + 1][x - 2] = ball;
			y = y + 1;
			x = x - 2;
		}
		else
		{
			//remove old place and adding the ball in new place due to geometry
			map[y][x] = ' ';
			map[y + 1][x - 1] = ball;
			y = y + 1;
			x = x - 1;
		}

		if (down_bond == y + 1 )
		{
			// If the ball hitted the space
			if (map[y + 1][x] == '-')
			{
				int pos = x - space_x;
				dir = 1;

				// If the ball hitted the right part of the space
				if (pos < 3)
					slope = -0.5;
				// If the ball hitted the right part of the space
				else if (pos < 6)
					slope = -1;
				// If the ball hitted the middle part of the space
				else if (pos < 9)
					slope = 0;
				// If the ball hitted the left part of the space
				else if (pos < 12)
					slope = 1;
				// If the ball hitted the left part of the space
				else
					slope = 0.5;
			}
			else
			{

				for (int display = 0; display < length; display++)
				{
					cout << map[display] << endl;
				}
				
				if (stage == 1)
					end_stage_1();
				else
					end_stage_2();
				
			}
		}
		if (right_bond == x + 1)
		{
			slope *= -1;
		}
		if (left_bond == x - 1)
		{
			slope *= -1;
		}
	}

	auto end = chrono::steady_clock::now();
	long time_elp = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_elp_ball_movement.push_front(time_elp);
}
void space_movement()
{
	auto start = chrono::steady_clock::now();

	int here = out_of_Range();
	srand(x*y*time(0));
	if (slope == 0 )
	{
		int rand1 = rand() % 2;
		if (!(space_x == x || space_x + space_len - 1 == x))
		{
			if (rand1 == 0)
				space_move(1);
			else
				space_move(-1);
		}
	}

	else if (slope == 1 && dir == 1)			//move right
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != -1)						//right or on the space
				space_move(1);
			else
				space_move(-1);
		}
		else                                    //the wrong way
			if (rand1 % 2 == 0)
				space_move(-1);

	}
	else if (slope == -1 && dir == 1)		//move left
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != 1)
				space_move(-1);
			else
				space_move(1);
		}
		else 
			if (rand1 % 2 == 0)		
				space_move(1);
		
	}
	else if (slope == 1 && dir == -1)		//move left
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != 1)
				space_move(-1);
			else
				space_move(1);
		}
		else
			if (rand1 % 2 == 0)
				space_move(1);
	}
	else if (slope == -1 && dir == -1) //move right
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != -1)
				space_move(1);
			else
				space_move(-1);
		}
		else
			if (rand1 % 2 == 0)
				space_move(-1);
	}

	else if (slope == 0.5 && dir == 1)			//move right
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != -1)					//right or on the space
			{
				space_move(1);
				space_move(1);
			}
			else
			{
				space_move(-1);
				space_move(-1);
			}
		}
		else                                    //the wrong way
			if (rand1 % 2 == 0)
				space_move(-1);


	}
	else if (slope == -0.5 && dir == 1)		//move left
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != 1)
			{
				space_move(-1);
				space_move(-1);
			}
			else
			{
				space_move(1);
				space_move(1);
			}
		}
		else
			if (rand1 % 2 == 0)
				space_move(1);

	}
	else if (slope == 0.5 && dir == -1)		//move left
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != 1)
			{
				space_move(-1);
				space_move(-1);
			}
			else
			{
				space_move(1);
				space_move(1);
			}
		}
		else
			if (rand1 % 2 == 0)
				space_move(1);
	}
	else if (slope == -0.5 && dir == -1) //move right
	{
		int rand1 = rand() % true_ratio;
		if (rand1 != 0)
		{
			if (here != -1)
			{
				space_move(1);
				space_move(1);
			}
			else
			{
				space_move(-1);
				space_move(-1);
			}
		}
		else
			if (rand1 % 2 == 0)
				space_move(-1);
	}


	auto end = chrono::steady_clock::now();
	long time_elp = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_elp_space_movement.push_front(time_elp);

}

void single_player_mode()
{
	generate_stage_1(diff, 1);

	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;
	}
	while (1)
	{
		system("cls");
		if (flag == 0)
			//flag == 0 --> computer turn
			space_movement();
		else
		{
			if (GetAsyncKeyState(VK_RIGHT))
				space_move(1);

			if (GetAsyncKeyState(VK_LEFT))
				space_move(-1);
		}
		
		ball_movement();

		//frames
		for (int display = 0; display < length; display++)
			cout << map[display] << endl;
		
		Sleep(speed_reciprocal);
	}
}
void multi_player_mode()

{
	generate_stage_1(diff, 2);
	while (1)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
			break;
	}
	//frames
	while (1)
	{
		system("cls");

		if (GetAsyncKeyState(VK_RIGHT))
				space_move(1);

		if (GetAsyncKeyState(VK_LEFT))
				space_move(-1);

		if (slope == 0.5 || slope == -0.5)
		{
			if (GetAsyncKeyState(VK_RIGHT))
				space_move(1);

			if (GetAsyncKeyState(VK_LEFT))
				space_move(-1);
		}

		ball_movement();

		for (int display = 0; display < length; display++)
		{
			cout << map[display] << endl;
		}
		if (slope == 0.5 || slope == -0.5)
			Sleep(2*speed_reciprocal);
		else
			Sleep(speed_reciprocal);
	}

}
void start()
{
	//the first position of the arrow
	int arrow_x = 16;
	int arrow_y = 9;
	flag = 0;

	//choose the game mode
	while (1)
	{
		//new frame
		system("cls");					
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (player_mode != 2)
			{
				player_mode = 2;
				arrow_pos(arrow_x, arrow_y, arrow_x, arrow_y + 5);
				arrow_y += 5;
			}
		}
		if (GetAsyncKeyState(VK_UP))
		{
			if (player_mode != 1)
			{
				player_mode = 1;
				arrow_pos(arrow_x, arrow_y, arrow_x, arrow_y - 5);
				arrow_y -= 5;
			}
		}

		if (GetAsyncKeyState(VK_RETURN))
			break;
		
		for (int display = 0; display < length; display++)
			cout << start_map[display] << endl;
		
		//wait until any key is pressed
		system("pause>nul");

	}

	//the second position of the arrow
	arrow_x = 60;
	arrow_y = 9;
	Sleep(100);

	//choose the game difficulty
	while (1)
	{
		//new frame
		system("cls");

		if (GetAsyncKeyState(VK_DOWN))
		{
			if (diff != 3)
			{
				diff++;
				arrow_pos(arrow_x, arrow_y, arrow_x, arrow_y + 5);
				arrow_y += 5;
			}
		}
		if (GetAsyncKeyState(VK_UP))
		{
			if (diff != 1)
			{
				diff--;
				arrow_pos(arrow_x, arrow_y, arrow_x, arrow_y - 5);
				arrow_y -= 5;
			}
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			break;
		}
		for (int display = 0; display < length; display++)
		{
			cout << start_map[display] << endl;
		}
		//wait until any key is pressed
		system("pause>nul");
	}

	if (player_mode == 1)
		single_player_mode();
	else
		multi_player_mode();
	
}


int main()
{
	start();
}
