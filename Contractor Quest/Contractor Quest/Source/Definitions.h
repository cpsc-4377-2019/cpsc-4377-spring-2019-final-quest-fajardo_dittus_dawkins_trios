#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef unsigned int Uint32;
typedef float EngineFloat;
typedef Uint32 EngineInt;

struct Position
{
	EngineFloat x;
	EngineFloat y;

	friend Position operator+ (const Position & src1, const Position & src2)
	{
		return { src1.x + src2.x, src1.y + src2.y };
	}
	friend Position operator- (const Position & src1, const Position & src2)
	{
		return { src1.x - src2.x, src1.y - src2.y };
	}
	friend bool operator> (const Position & src1, int src2)
	{
		if (src1.x > src2 && src1.y > src2)
		{
			return true;
		}
		return false;
	}
	friend bool operator< (const Position & src1, int src2)
	{
		if (src1.x < src2 && src1.y < src2)
		{
			return true;
		}
		return false;
	}
	friend bool operator== (const Position & src1, const Position & src2)
	{
		if (src1.x == src2.x && src1.y == src2.y)
		{
			return true;
		}
		return false;
	}
	friend Position abs(Position & src)
	{
		return { abs((float)src.x),abs((float)src.y) };
	}
};


struct RGBA
{
	EngineInt R;
	EngineInt G;
	EngineInt B;
	EngineInt A;
};

enum GAME_OBJECT_SHAPE {GAME_RECTANGLE, GAME_CIRCLE};
enum GAME_BODY_TYPE {GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC};

//Constants
const EngineFloat PI = 3.14159f;
const EngineFloat DT = (1.0f / 100.0f);
const EngineFloat fPRV = 10.0f;
const Position GRAVITY = { 0.0f, 2000.0f };	//Adjust as needed

#endif
