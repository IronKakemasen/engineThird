#pragma once

enum BlockMode
{
	kEnter,
	kVanish,
	kMove,
	kFreeze
};

struct BlockBehavior
{
	BlockMode mode;
	Vector3 dstEnterPos;
	int no;
};