#pragma once

#include "BaseApp.h"


class TestApp : public BaseApp
{
	typedef BaseApp Parent;

private:
	COORD mObjOld;
	COORD mObj;
	bool mDirection;
	int figures[7][4] =
	{
		1,3,5,7, // I
		2,4,5,7,// S
		3,5,4,6,// Z
		3,5,4,7,// T
		2,3,5,7,// L
		3,5,7,6,  //J
		2,3,4,5, // O
	};

	COORD* FiguresOnField;
	COORD* FiguresOnFieldOld;

	int mScore;
	bool mNewTetramino;
	bool mDown;
	int mNextTetramino;
	int mTetramino;
	int mCnt;
	int mSpeed;
	int mIterCount;





public:
	TestApp();
	~TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	
	
	//рисует поле
	void  Field();
	void InicField();
	//рисует вертикальные линии
	void VertikalLine(int x, int start, int end);
	//рисует горизонтальные линии
	void gorizontalLine(int y, int start, int end);
	//рисует счет
	void show_score(int x,int y);
	void previj(int x, int y);
	void RewritingFiguresOnFieldOld();
	void RewritingFiguresOnField();
	void artTetramino();
	bool CheckLine(int i);
	void DestroyLine();
	void CheckGameOver();
	bool Check(int i);
	bool CheckY();
	bool CheckX();
	bool CheckRotate();
	void EraseTetramino();
	void Rotate();
	void InicFigureOnField();
	void InicFigureOnFieldOld();

};

