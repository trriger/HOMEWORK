#include<iostream>
#include <cstring>
#include"stdafx"
int m=9, n=9;
#include<fstream>
using namespace std;
int board[9][9];


bool Check(int check_number, int check_now_line, int check_now_column,
	int ch_blockline, int ch_blockcolumn)
{
	for (int i = 0; i <= m - 1; ++i)
	{
		if (board[check_now_line][i] == check_number || board[i][check_now_column] == check_number)
			return false;
	}
	if (m == 9)for (int i = 0; i <= 2; ++i)
	{
		for (int j = 0; j <= 2; ++j)
		{
			if (board[ch_blockline + i][ch_blockcolumn + j] == check_number)
				return false;
		}
	}
	if (m == 8)for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j <= 1; j++)
		{
			if (board[ch_blockline + i][ch_blockcolumn + j] == check_number)
				return false;
		}
	}
	if (m == 6)for (int i = 0; i <= 1; ++i)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (board[ch_blockline + i][ch_blockcolumn + j]== check_number)
				return false;
		}
	}
	if (m == 4)for (int i = 0; i <= 1; ++i)
	{
		for (int j = 0; j <= 1; j++)
		{
			if (board[ch_blockline + i][ch_blockcolumn + j]== check_number)
				return false;
		}
	}
	return true;
}

bool work(int now_line, int now_column)
{
	if (now_line == m)
	{
		return true;//Èç¹û½«Êý¶À½âÍê£¬·µ»Øtrue 
	}
	else
	{
		int next_line, next_column, block_line=0, block_column=0;
		next_column = now_column + 1;
		next_line = (next_column >= m ? now_line + 1 : now_line);
		next_column = (next_column >= m ? 0 : next_column);
		if (board[now_line][now_column] != 0)//Èç¹ûµ±Ç°×ø±êÓÐÊý×Ö£¬Ôò¶ÔÏÂÒ»¸ö×ø±ê½øÐÐ¹¤×÷ 
		{
			if (work(next_line, next_column)) return true;//Èç¹ûÊý¶À×îÖÕÓÐ½â£¬Ôò²»¶ÏÏòÇ°·µ»Øtrue 
		}
		else
		{
			if (m == 9)
			{
				block_line = (now_line / 3) * 3;//¼ÆËãËùÔÚµÄ3*3·½¸ñ×óÉÏ½Ç×ø±ê
				block_column = (now_column / 3) * 3;
			}
			if (m == 8)
			{
				block_line = (now_line / 4) * 4;//¼ÆËãËùÔÚµÄ4*2·½¸ñ×óÉÏ½Ç×ø±ê
				block_column = (now_column / 2) * 2;
			}
			if (m == 6)
			{
				block_line = (now_line / 2) * 2;//¼ÆËãËùÔÚµÄ2*3·½¸ñ×óÉÏ½Ç×ø±ê
				block_column = (now_column / 3) * 3;
			}
			if (m == 4)
			{
				block_line = (now_line / 2) * 2;//¼ÆËãËùÔÚµÄ3*3·½¸ñ×óÉÏ½Ç×ø±ê
				block_column = (now_column / 2) * 2;
			}
			for (int i = 1; i <= m; ++i)
			{
				if (Check(i, now_line, now_column, block_line, block_column))
				{
					board[now_line][now_column] = i;
					if (work(next_line, next_column)) return true;
				}
			}
			board[now_line][now_column] = 0;//»ØËÝ²Ù×÷ 
			return false;
		}
	}
}
void Input(int t, int* save)
{
	for (int i = 0; i <= m - 1; ++i)
	{
		for (int j = 0; j <= m - 1; ++j)
		{
			board[i][j] = save[t * m * m + i * m + j];
		}
	}
}
void Output(int t, int* save)
{
	for (int i = 0; i <= m - 1; ++i)
	{
		for (int j = 0; j <= m - 1; ++j)
		{
			save[t * m * m + i * m + j] = board[i][j];
		}
	}
}
int main(int argc, char* argv[])
{
	ifstream infile;
	ofstream outfile;
	/*char str[20];
	strcpy(str, argv[2]);
	m = (int)(str[0]) - 48;*/
	m = argv[2][0]-48;

	n = argv[4][0]-48;
	int save[500];
	int cer = 0;
	infile.open(argv[6]);
	char ch;
	while (!infile.eof())
	{
		infile.get(ch);
		if ('0' <= ch && ch <= '9')save[cer++] = ch - 48;
	}
	infile.close();
	for (int t = 0; t < n; t++)
	{
		Input(t, save);
		if (work(0, 0));
		else cout << "wrong!" << endl;
		Output(t, save);
	}
	outfile.open(argv[8]);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < m; k++)
			{
				outfile << save[i * m * m + j * m + k];
				outfile << " ";
			}
			outfile << endl;
		}
		outfile << endl;
	}
	outfile.close();
	return 0;
}
