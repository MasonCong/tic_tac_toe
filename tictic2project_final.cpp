#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<fstream>
#include<stdlib.h>
#include <ctime>


using namespace std;
void show_screen(vector<vector<vector<char>>> A,int size);
int win_lost_row(vector<vector<vector<char>>> B, int size1,int tempx, int tempy, char c);
int win_lost_col(vector<vector<vector<char>>> B, int size1, int tempx, int tempy, char c);
int win_lost_slash(vector<vector<vector<char>>> B, int size1, int tempx, int tempy, char c);
char play_d(int p);
bool zdsWaiting(int nSec);
int player_win(int x1, int y1, int z1, int sequence);

void main() 
{
	////////////input///////////////////////////
	char resume;
	int pause = 3;
	int board_size;
	int seq, temp_x, x, ty, y;
	char buff[255];
	int num_p;
	int a[100];//input
	int b[100];//output
	int num = 0;//length of the input
	int count_input=0;//determine the input file
	int input_num;
	cout << "If you like to resume a game{Y:resume/N:new game):";
	cin >> resume;
	while ((resume != 'Y') && (resume != 'N'))
	{
		cout << "You are not entering appropriate character,please enter Y or N£º";
		cin >> resume;
	}
	if (resume == 'Y')
	{
		//in_stream >> num_p >> board_size >> seq;
		ifstream in_stream;
		in_stream.open("game_save.txt");

		while (!in_stream.eof())
		{
			in_stream >> a[num];//number is of input is num
			b[num] = a[num];
			num++;
		}
		in_stream.close();
		num_p = a[0];
		board_size = a[1];
		seq = a[2];
		count_input = num-3;
		input_num = 3;
	}
	////////////////////////////
	else if (resume == 'N')
	{
		cout << "How many players are playing(input must be an integer):";
		cin >> num_p;
		while ((num_p > 20)||(num_p <= 0))
		{
			cout << "The number entered exceed range of players! Please enter again:";
			cin >> num_p;
		}
		b[0] = num_p;
		cout << "How large the board should be(input must be an integer):";
		cin >> board_size;
		while ((board_size > 100) || (board_size <= 0))
		{
			cout << "The board size exceed the console display! Please enter again";
			cin >> board_size;
		}
		b[1] = board_size;

		cout << "What the win sequence should be(input must be an integer):";
		cin >> seq;
		while (seq > board_size)
		{
			cout << "It is impossible to win! Please enter again:";
			cin >> seq;
		}
		b[2] = seq;
	}
///////////////////////////////////////////
	int count = 3;
	vector<vector<vector<char>>> board;
	board.resize(board_size);
	for (int i = 0; i < board_size; i++)
	{
		board[i].resize(board_size);
	};
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			board[i][j].resize(2);
	}

		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{
				board[i][j][0] = ' ';
				board[i][j][1] = ' ';
			}
		}
		show_screen(board, board_size);
//////////////////////////////////////////////////////////
		int win;//
		char temp_char;//X or O or something else;
		////////////////player/////////////////////
		int turn;
		vector<vector<int>> player;
		player.resize(num_p);
		for (int i = 0; i < num_p; i++)
			player[i].resize(3);
		//////////////////////////////////////
		vector<int> queue;///queue include row col slas
		//vector<int> temp_player1;
		//vector<int> temp_player2;
		queue.resize(3);
		//temp_player1.resize(3);
		//temp_player2.resize(3);
		for (int j = 0; j < num_p; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				player[j][i] = 0;
			}
		}
		int times=0;
////////save the game///////////
		char save_or_con;
		for (turn = 0; turn < ((board_size*board_size)/num_p+1); turn++)
		{
			/////////////////////////////////////
			if ((times - 1) == (board_size*board_size))
			{
				cout << "No one win the game:" << endl;
				break;
			}
			for (int z=0; z < num_p; z++)
			{
				///////////////////////////////////////////
				
				if (count_input<=1)
				{
					cout << "Continue or save the game:(Y:continue/N:save and exit)" << endl;
					cin >> save_or_con;
				while ((save_or_con != 'Y') && (save_or_con != 'N'))
				{
					cout << "The input must be Y or N,please enter again:";
					cin >> save_or_con;
				}
				if (save_or_con == 'N')
				{
					b[0] = num_p;
					b[1] = board_size;
					b[2] = seq;
					if (resume == 'Y')
					{
						for (int q = 3; q < (num - 1); q++)
							b[q] = a[q];
					}
					ofstream out_stream;
					out_stream.open("game_save.txt");
					for (int i = 0; i < (count); i++)
					{
						out_stream << b[i] << endl;
					}
					out_stream.close();
					exit(0);
				}
				else if (save_or_con == 'Y')
				{
				}
				}
				///////////////////////////////////////
				times = times + 1;
				if (count_input <= 1)
				{
					cout << "Please enter the position(input must be two integer):"<<endl;
					cin >> temp_x;
					cin >> ty;
					while (cin.fail())
					{
						cin.clear();
						cout << "Input should be two integer! please enter again:";
						cin.getline(buff, 255);
						cin >> temp_x;
						cin >> ty;
					}
					while ((temp_x > board_size) || (temp_x<1)|| (ty>board_size) || (ty<1))
					{
						cout << "The input exceed the board size,please enter again:"<<endl;
						cin >> temp_x;
						cin >> ty;
					}
					b[count] = temp_x;
					count = count + 1;
					b[count] = ty;
					count = count + 1;
				}
				else if (count_input>1)
				{
					temp_x = a[input_num];
					count = count + 1;///////
					b[input_num] = temp_x;
					count_input = count_input - 1;
					input_num++;
					ty = a[input_num];
					count = count + 1;
					b[input_num] = ty;
					count_input = count_input - 1;
					input_num++;
				}
				//out_stream << temp_x << endl<<ty<<endl;
				x = temp_x - 1;
				y = ty - 1;
				if (board[x][y][0] == ' ')
				{
					temp_char = play_d(z);
					board[x][y][0] = temp_char;
					board[x][y][1] = ' ';
					queue[0] = win_lost_row(board, board_size, x, y, temp_char);
					queue[1] = win_lost_col(board, board_size, x, y, temp_char);
					queue[2] = win_lost_slash(board, board_size, x, y, temp_char);
					for (int i = 0; i < 3; i++)
						player[z][i] = player[z][i] + queue[i];
					win = player_win(player[z][0], player[z][1], player[z][2], seq);
					if (win == 1)
					{
						show_screen(board, board_size);
						cout << "Player "<<(z+1)<<" win the game!" << endl;
						cout << "exit" << endl;
						break;
					}


				}
				else
				{
					cout << "The position have been taken!" << endl;
					z = z - 1;
				}
				if (count_input > 1)
				{
					zdsWaiting(pause);
				}
				show_screen(board, board_size);
			}
			if (win == 1)
				break;
			
			
			
			//win_lost(board, board_size, seq,x,y,);
		}
}

void show_screen(vector<vector<vector<char>>> A, int size)
{
	int size_b = size * 2, tempi, tempj;
	vector<vector<vector<char>>> show_board;
	show_board.resize(size_b);
	for (int i = 0; i < size_b; i++)
	{
		show_board[i].resize(size_b);
	};
	for (int i = 0; i < size_b; i++)
	{
		for (int j = 0; j < size_b; j++)
			show_board[i][j].resize(2);
	}

	for (int i=0; i < size_b; i++)
	{
		for (int j=0; j < size_b; j++)
		{
			if ((i == 0) && (j % 2 == 1))
			{
				tempi = (j + 1) / 2;
				show_board[i][j][0] = tempi / 10 + 48;
				show_board[i][j][1] = tempi % 10 + 48;
				
			}
			else if ((i == 0) && (j % 2 == 0))
			{
				show_board[i][j][0] = ' ';
				show_board[i][j][1] = ' ';
			}
			else if ((j == 0) && (i % 2 == 1))
			{
				tempj = (i + 1) / 2;
				show_board[i][j][0] = tempj / 10 + 48;
				show_board[i][j][1] = tempj % 10 + 48;
			}
			else if ((j == 0) && (i % 2 == 0))
			{
				show_board[i][j][0] = ' ';
				show_board[i][j][1] = ' ';
			}
			else if ((i % 2 == 1) && (j > 0) && (j % 2 == 0))
			{
				show_board[i][j][0] = static_cast<char>('|');
				show_board[i][j][1] = static_cast<char>(' ');
			}
			else if ((j % 2 == 1) && (i > 0) && (i % 2 == 0))
			{
				show_board[i][j][0] = '---';
				show_board[i][j][1] = '---';
			}
			else if ((i > 0) && (j > 0) && (i % 2 == 0) && (j % 2 == 0))
			{
				show_board[i][j][0] = '+';
				show_board[i][j][1] = '-';
			}
			else if ((i % 2 == 1) && (j % 2 == 1))
			{
				show_board[i][j][0] = A[(i - 1) / 2][(j - 1) / 2][0];
				show_board[i][j][1] = A[(i - 1) / 2][(j - 1) / 2][1];
			}
		}
	}


	for (int i=0; i < size_b; i++)
	{
		for (int j=0; j < size_b; j++)
		{
			cout << show_board[i][j][0];
			cout << show_board[i][j][1];
		}
		cout << endl;
	}

}
/////////////////////////////////////////////////////
//return value row,col,slash in vector
int win_lost_row(vector<vector<vector<char>>> B, int size1,int tempx, int tempy, char c)
{
	int row=0;
	if (tempx == 0)
	{
		if ((B[tempx + 1][tempy][0] == c) && (B[tempx][tempy][0] == c))
			row = row + 1;
	}
	else if (tempx == (size1 - 1))
	{
		if ((B[tempx - 1][tempy][0] == c) && (B[tempx][tempy][0] == c))
			row = row + 1;
	}
	else if ((tempx >= 1) && (tempx <= (size1 - 2)))
	{
		if ((B[tempx - 1][tempy][0] == c) && (B[tempx][tempy][0] == c))
			row = row + 1;

		if ((B[tempx + 1][tempy][0] == c) && (B[tempx][tempy][0] == c))
			row = row + 1;
	}
	else
		row = 0;
	return row;

}
int win_lost_col(vector<vector<vector<char>>> B, int size1,int tempx, int tempy, char c)
{
	int col = 0;
	if (tempy == 0)
	{
		if ((B[tempx][tempy + 1][0] == c) && (B[tempx][tempy][0] == c))
			col = col + 1;
	}
	else if (tempy == (size1-1))
	{
		if ((B[tempx][tempy - 1][0] == c) && (B[tempx][tempy][0] == c))
			col = col + 1;
	}
	else if ((tempy >= 1) && (tempy <= (size1 - 2)))
	{
		if ((B[tempx][tempy - 1][0] == c) && (B[tempx][tempy][0] == c))
			col = col + 1;
		if ((B[tempx][tempy + 1][0] == c) && (B[tempx][tempy][0] == c))
			col = col + 1;
	}
	else
		col = 0;
	return col;
}

int win_lost_slash(vector<vector<vector<char>>> B, int size1,int tempx, int tempy, char c)
{
	int slash=0;
	if ((tempx == 0) && (tempy == 0))
	{
		if ((B[tempx + 1][tempy + 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
	}
	else if ((tempx == 0) && (tempy == (size1 - 1)))
	{
		if ((B[tempx + 1][tempy - 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
	}
	else if ((tempx == (size1 - 1)) && (tempy == 0))
	{
		if ((B[tempx - 1][tempy + 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
	}
	else if ((tempx == (size1 - 1)) && (tempy == (size1 - 1)))
	{
		if ((B[tempx - 1][tempy - 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
	}
	else if ((tempy >= 1) && (tempy <= size1 - 2) && (tempx >= 1) && (tempx <= size1 - 2))
	{
		if ((B[tempx - 1][tempy + 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
		if ((B[tempx + 1][tempy + 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
		if ((B[tempx - 1][tempy - 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
		if ((B[tempx + 1][tempy - 1][0] == c) && (B[tempx][tempy][0] == c))
			slash = slash + 1;
	}
	return slash;
}

//int win_lost_square00(vector<vector<vector<char>>> B, int size1, int tempx, int tempy, char c)
//{
//
//
//}
int player_win(int x1, int y1, int z1, int sequence)
{
	int win=0;//win = 1 win;win = 0 lost;
	if (x1 >= (sequence - 1))
		win = 1;
	else if (y1 >= (sequence - 1))
		win = 1;
	else if (z1 >= (sequence - 1))
		win = 1;
	else
		win = 0;

	return win;		
}

char play_d(int p)
{
	char play_char[27] = "XOABCDEFGHIJKLMNPQRSTUVWYZ";
	return play_char[p];
}

bool zdsWaiting(int nSec)

{

	if (nSec > 0){

		clock_t cinTime = nSec * CLOCKS_PER_SEC;

		clock_t startTime = clock();

		while (clock() - startTime < cinTime){

		}
		return true;

	}
	else{

		return false;

	}

}