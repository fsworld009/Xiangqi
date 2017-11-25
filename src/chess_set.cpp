#include "stdafx.h"
#include "chess_set.h"

chess_set::chess_set(void)
:selected(false)
{
	player_1 = true;
	/*		初始暫存棋		*/
	record_chess.x = -1;
	record_chess.y = -1;
	record_chess.is_dead = false;
	record_index = -1;
	/*		初始24顆棋子	*/
	/*前16顆為紅棋	座標為 紅下黑上*/
	/* 0~4 = 兵, 5~6 = 炮, 7~8 = 車, 9~10 = 馬,  11~12 = 相,  13~14 = 士, 15 = 帥*/
	for(int i = 0; i < 16; i++)
	{
		if(i < 5)
		{
			chesses[i].x = 1 + 2 * i;
			chesses[i].y = 7;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 4;
		}
		else if(i < 7)
		{
			chesses[i].x = 2 + (i - 5) * 6;
			chesses[i].y = 8;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 3;
		}
		else if(i < 9)
		{
			chesses[i].x = 1 + (i - 7) * 8;
			chesses[i].y = 10;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 1;
		}
		else if(i < 11)
		{
			chesses[i].x = 2 + (i - 9) * 6;
			chesses[i].y = 10;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 1;
		}
		else if(i < 13)
		{
			chesses[i].x = 3 + (i - 11) * 4;
			chesses[i].y = 10;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 1;
		}
		else if(i < 15)
		{
			chesses[i].x = 4 + (i -13) * 2;
			chesses[i].y = 10;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 1;
		}
		else
		{
			chesses[i].x = 5;
			chesses[i].y = 10;
			chesses[i+16].x = chesses[i].x;
			chesses[i+16].y = 1;
		}
		chesses[i].is_dead = true;
		chesses[i+16].is_dead = true;
	}
}

chess_set::~chess_set(void)
{
}

void chess_set::GetAllPoint(int x[], int y[], int &light)
{
	light = record_index;
	for(int i = 0; i < 32; i++)
	{
		if(chesses[i].is_dead)
		{
			x[i] = chesses[i].x;
			y[i] = chesses[i].y;
		}
		else
		{
			x[i] = -1;
			y[i] = -1;
		}
	}
}

int chess_set::IsGoal()
{
	if(!chesses[15].is_dead)
		return 1; //黑勝
	else if(!chesses[31].is_dead)
		return -1; //紅勝
	else
		return 0;
}

void chess_set::Save(CArchive &ar)
{
	ar << selected << record_chess.x << record_chess.y << record_index;
	for(int i = 0; i < 32; i++)
		ar << chesses[i].x << chesses[i].y << chesses[i].is_dead;
}

void chess_set::Load(CArchive &ar)
{
	ar >> selected >> record_chess.x >> record_chess.y >> record_index;
	for(int i = 0; i < 32; i++)
		ar >> chesses[i].x >> chesses[i].y >> chesses[i].is_dead;
}

bool chess_set::GetPlayer()
{
	return player_1;
}

int chess_set::Action(int x, int y, Record& m_record)
{
	if(x <= 0 || y <= 0)
		return 0;
	if(!selected)
	{
		for(int i = 0; i < 32; i++)
		{
			if(chesses[i].x == x && chesses[i].y == y && chesses[i].is_dead)
			{
				record_chess.x = x;
				record_chess.y = y;
				record_index = i;
				selected = true;
				break;
			}
		}
		if(selected)
		{
			if(player_1 && record_index > 15)
			{
				record_index = -1;
				selected = false;
				return 0;
			}
			else if(!player_1 && record_index < 16)
			{
				record_index = -1;
				selected = false;
				return 0;
			}
		}
		return 1;
	}
	else
	{
		if(record_chess.x == x && record_chess.y == y)
		{
			selected = false;
			record_index = -1;
			return 1;
		}
		int ate = -1;
		for(int i = 0; i < 32; i++)
		{
			if(chesses[i].x == x && chesses[i].y == y && chesses[i].is_dead)
			{
				if(i < 16 && record_index <16)
				{
					selected = false;
					record_index = -1;
					return 0;
				}
				else if(i > 15 && record_index > 15)
				{
					selected = false;
					record_index = -1;
					return 0;
				}
				ate = i;
				break;
			}
		}

		bool return_value = check_rule(ate, x, y);
		if(return_value)
		{
			chesses[record_index].x = x;
			chesses[record_index].y = y;
			player_1 = !player_1;
			m_record.setChessStep(record_chess.x, record_chess.y, x, y, record_index, ate);
			if(ate >= 0)
				chesses[ate].is_dead = false;
		}
		selected = false;
		record_index = -1;
		if(return_value == true)
			return 2;
		else
			return 0;

	}
}

bool chess_set::check_rule(int &index, int x, int y)
{
	/* 0~4 = 兵, 5~6 = 炮, 7~8 = 車, 9~10 = 馬,  11~12 = 相,  13~14 = 士, 15 = 帥*/
	if(record_index < 5)
	{
		if(record_chess.y > 5)
		{
			if(record_chess.x != x)
				return false;
		}
		if(record_chess.y < y)
			return false;
		else if(record_chess.y != y && record_chess.x != x)
			return false;
		else if((x - record_chess.x == 1) || (x - record_chess.x == -1) || (record_chess.y - y == 1))
			return true;
		else 
			return false;
	}
	else if(record_index < 7)
	{
		int block = 0;
		if(x != record_chess.x && y != record_chess.y)
			return false;
		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(x == record_chess.x  && x == chesses[i].x)
			{
				if(chesses[i].y > record_chess.y && chesses[i].y < y)
					block++;
				else if(chesses[i].y > y && chesses[i].y < record_chess.y)
					block++;
			}
			else if(y == record_chess.y && y == chesses[i].y)
			{
				if(chesses[i].x > record_chess.x && chesses[i].x < x)
					block++;
				else if(chesses[i].x > x && chesses[i].x < record_chess.x)
					block++;
			}
		}
		if(index == -1)
			return block == 0;
		else
			return block == 1;
	}
	else if(record_index < 9)
	{
		if(x != record_chess.x && y != record_chess.y)
			return false;
		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(x == record_chess.x && x == chesses[i].x)
			{
				if(chesses[i].y > record_chess.y && chesses[i].y < y)
					return false;
				else if(chesses[i].y > y && chesses[i].y < record_chess.y)
					return false;;
			}
			else if(y == record_chess.y && y == chesses[i].y)
			{
				if(chesses[i].x > record_chess.x && chesses[i].x < x)
					return false;
				else if(chesses[i].x > x && chesses[i].x < record_chess.x)
					return false;
			}
		}
		return true;
	}
	else if(record_index < 11)
	{
		bool frount = false;
		bool back = false;
		bool left = false;
		bool right = false;

		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(chesses[i].x == record_chess.x)
			{
				if(chesses[i].y == record_chess.y + 1)
					back = true;
				else if(chesses[i].y == record_chess.y - 1)
					frount = true;
			}
			else if(chesses[i].y == record_chess.y)
			{
				if(chesses[i].x == record_chess.x + 1)
					right = true;
				else if(chesses[i].x == record_chess.x - 1)
					left = true;
			}
		}
		if(y == record_chess.y + 2 && ( x == record_chess.x + 1 || x == record_chess.x - 1))
			return !back;
		else if(y == record_chess.y - 2 && ( x == record_chess.x + 1 || x == record_chess.x - 1))
			return !frount;
		else if(x == record_chess.x + 2 && ( y == record_chess.y + 1 || y == record_chess.y - 1))
			return !right;
		else if(x == record_chess.x - 2 && ( y == record_chess.y + 1 || y == record_chess.y - 1))
			return !left;
		return false;
	}
	else if(record_index < 13)
	{
		if(y < 6)
			return false;
		bool left_up = false;
		bool left_down = false;
		bool right_up = false;
		bool right_down = false;

		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(chesses[i].x == record_chess.x+1)
			{
				if(chesses[i].y == record_chess.y + 1)
					right_down = true;
				else if(chesses[i].y == record_chess.y - 1)
					right_up = true;
			}
			else if(chesses[i].x == record_chess.x-1)
			{
				if(chesses[i].y == record_chess.y + 1)
					left_down = true;
				else if(chesses[i].y == record_chess.y - 1)
					left_up = true;
			}
		}
		if(x == record_chess.x+2 && y == record_chess.y+2)
			return !right_down;
		else if(x == record_chess.x+2 && y == record_chess.y-2)
			return !right_up;
		else if(x == record_chess.x-2 && y == record_chess.y+2)
			return !left_down;
		else if(x == record_chess.x-2 && y == record_chess.y-2)
			return !left_up;
		else
			return false;
	}
	else if(record_index < 15)
	{
		if(y < 8 || x < 4 || x > 6)
			return false;
		else if(x == record_chess.x || y == record_chess.y)
			return false;
		else
			return true;
	}
	else if(record_index == 15)
	{
		if(chesses[15].x == chesses[31].x)
		{
			int j = 0;
			for(; j < 32; j++)
			{
				if(j == 15 || j == 31)
					continue;
				if(chesses[j].x == chesses[15].x && chesses[j].is_dead)
					break;
			}
			if(j == 32)
			{
				if(x == chesses[31].x && y == chesses[31].y)
					return true;
			}
		}
		if(y < 8 || x < 4 || x > 6)
			return false;
		if(x != record_chess.x && y != record_chess.y)
			return false;
		if(x == record_chess.x && (y == record_chess.y+1 || y == record_chess.y-1))
			return true;
		else if(y == record_chess.y && (x == record_chess.x+1 || x == record_chess.x-1))
			return true;
		else
			return false;
	}


	if(record_index < 21)
	{
		if(record_chess.y < 6)
		{
			if(record_chess.x != x)
				return false;
		}
		if(record_chess.y > y)
			return false;
		if((x - record_chess.x == 1) || (x - record_chess.x == -1) || (record_chess.y - y == -1))
			return true;
		else 
			return false;
	}
	else if(record_index < 23)
	{
		if(x != record_chess.x && y != record_chess.y)
			return false;
		int block = 0;
		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(x == record_chess.x && x == chesses[i].x)
			{
				if(chesses[i].y > record_chess.y && chesses[i].y < y)
					block++;
				else if(chesses[i].y > y && chesses[i].y < record_chess.y)
					block++;
			}
			else if(y == record_chess.y && y == chesses[i].y)
			{
				if(chesses[i].x > record_chess.x && chesses[i].x < x)
					block++;
				else if(chesses[i].x > x && chesses[i].x < record_chess.x)
					block++;
			}
		}
		if(index == -1)
			return block == 0;
		else
			return block == 1;
	}
	else if(record_index < 25)
	{
		if(x != record_chess.x && y != record_chess.y)
			return false;
		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(x == record_chess.x && x == chesses[i].x)
			{
				if(chesses[i].y > record_chess.y && chesses[i].y < y)
					return false;
				else if(chesses[i].y > y && chesses[i].y < record_chess.y)
					return false;;
			}
			else if(y == record_chess.y && y == chesses[i].y)
			{
				if(chesses[i].x > record_chess.x && chesses[i].x < x)
					return false;
				else if(chesses[i].x > x && chesses[i].x < record_chess.x)
					return false;
			}
		}
		return true;
	}
	else if(record_index < 27)
	{
		bool frount = false;
		bool back = false;
		bool left = false;
		bool right = false;

		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(chesses[i].x == record_chess.x)
			{
				if(chesses[i].y == record_chess.y + 1)
					back = true;
				else if(chesses[i].y == record_chess.y - 1)
					frount = true;
			}
			else if(chesses[i].y == record_chess.y)
			{
				if(chesses[i].x == record_chess.x + 1)
					right = true;
				else if(chesses[i].x == record_chess.x - 1)
					left = true;
			}
		}
		if(y == record_chess.y + 2 && ( x == record_chess.x + 1 || x == record_chess.x - 1))
			return !back;
		else if(y == record_chess.y - 2 && ( x == record_chess.x + 1 || x == record_chess.x - 1))
			return !frount;
		else if(x == record_chess.x + 2 && ( y == record_chess.y + 1 || y == record_chess.y - 1))
			return !right;
		else if(x == record_chess.x - 2 && ( y == record_chess.y + 1 || y == record_chess.y - 1))
			return !left;
		else
			return false;
	}
	else if(record_index < 29)
	{
		if(y > 5)
			return false;
		bool left_up = false;
		bool left_down = false;
		bool right_up = false;
		bool right_down = false;

		for(int i = 0; i < 32; i++)
		{
			if(!chesses[i].is_dead)
				continue;

			if(chesses[i].x == record_chess.x+1)
			{
				if(chesses[i].y == record_chess.y + 1)
					right_down = true;
				else if(chesses[i].y == record_chess.y - 1)
					right_up = true;
			}
			else if(chesses[i].x == record_chess.x-1)
			{
				if(chesses[i].y == record_chess.y + 1)
					left_down = true;
				else if(chesses[i].y == record_chess.y - 1)
					left_up = true;
			}
		}
		if(x == record_chess.x+2 && y == record_chess.y+2)
			return !right_down;
		else if(x == record_chess.x+2 && y == record_chess.y-2)
			return !right_up;
		else if(x == record_chess.x-2 && y == record_chess.y+2)
			return !left_down;
		else if(x == record_chess.x-2 && y == record_chess.y-2)
			return !left_up;
		else
			return false;
	}
	else if(record_index < 31)
	{
		if(y > 3 || x < 4 || x > 6)
			return false;
		else if(x == record_chess.x || y == record_chess.y)
			return false;
		else
			return true;
	}
	else if(record_index == 31)
	{
		if(chesses[15].x == chesses[31].x)
		{
			int j = 0;
			for(; j < 32; j++)
			{
				if(j == 15 || j == 31)
					continue;
				if(chesses[j].x == chesses[15].x && chesses[j].is_dead)
					break;
			}
			if(j == 32)
			{
				if(x == chesses[15].x && y == chesses[15].y)
					return true;
			}
		}

		if(y > 3 || x < 4 || x > 6)
			return false;
		if(x != record_chess.x && y != record_chess.y)
			return false;
		if(x == record_chess.x && (y == record_chess.y+1 || y == record_chess.y-1))
			return true;
		else if(y == record_chess.y && (x == record_chess.x+1 || x == record_chess.x-1))
			return true;
		else
			return false;
	}
	else
		return false;
	return true;
}

void chess_set::NextStep(int x1, int y1, int x2, int y2, int chessType, int eat)
{
	chesses[chessType].x = x2;
	chesses[chessType].y = y2;
	if(eat != -1)
		chesses[eat].is_dead = false;
}

void chess_set::PreviousStep(int x1, int y1, int x2, int y2, int chessType, int eat)
{
	chesses[chessType].x = x1;
	chesses[chessType].y = y1;
	if(eat != -1)
		chesses[eat].is_dead = true;
}