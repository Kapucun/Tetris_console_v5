#include "TestApp.h"
#include "time.h"


TestApp::TestApp() : Parent(26, 27)
{
	mDirection = true;
	mObjOld.X = mObj.X = 17 / 2;
	mObjOld.Y = mObj.Y = 1;
	mNextTetramino = 0;
	mTetramino = 0;
	FiguresOnField = new COORD[4];
	FiguresOnFieldOld = new COORD[4];
	mScore = 0;
	mNewTetramino = true;
	mDown = true;
	mCnt = 0;
	mSpeed = 0;
	int mIterCount = 0;
}

TestApp::~TestApp()
{
	delete[] FiguresOnField;
	delete[] FiguresOnFieldOld;
}

void TestApp::KeyPressed(int btnCode)
{

	if (mDown)
	{
		if (btnCode == 80) //down
		{
			mDown = false;
		}
		else if (btnCode == 75) //Left
		{
			mObj.X--;
			CheckX();
		}
		else if (btnCode == 77) //Right
		{
			mObj.X++;
			CheckX();
		}
		else if (btnCode == 32) //rotate
		{
			Rotate();
			CheckRotate();
		}
	}
}

void TestApp::UpdateF(float deltaTime)
{

	Field();
	DestroyLine();
	previj(20, 3);
	if (!mDown)
	{
		mObj.Y++;
		CheckY();
		mIterCount = 0;
	}
	if (mIterCount == mSpeed)
	{
		mObj.Y++;
		CheckY();
		mIterCount = 0;
	}
	EraseTetramino();
	artTetramino();
	show_score(3, 25);
	mIterCount++;
}



void  TestApp::Field()
{
	if (!mCnt)
	{
		mNextTetramino = 0;
		InicField();
		gorizontalLine(0, 0, 27);
		gorizontalLine(27, 0, 27);
		gorizontalLine(22, 0, 27);
		VertikalLine(0, 0, 27);
		VertikalLine(26, 0, 27);
		VertikalLine(16, 0, 22);
		InicFigureOnFieldOld();
	}
	mCnt++;
}

void TestApp::InicField()
{
	for (int x = 1; x < 16; x++)
	{
		for (int y = 1; y < 22; y++)
			SetChar(x, y, L'.');
	}
}

void TestApp::VertikalLine(int x, int start, int end)
{
	for (int y = start; y < end; y++)
	{
		SetChar(x, y, L'#');
	}
}
void TestApp::gorizontalLine(int y, int start, int end)
{
	for (int x = start; x < end; x++)
	{
		SetChar(x, y, L'#');
	}
}

void TestApp::show_score(int x, int y)
{
	char a[8] = { '>',' ','S','c','o','r','e',':' };
	for (int n = 0; n < 8; n++, x++)
	{
		SetChar(x, y, a[n]);
	}
	char str[6];
	sprintf_s(str, "%d", mScore);
	int strsz = strlen(str);
	for (int n = 0; n < strsz; n++)
	{
		SetChar(++x, y, str[n]);
	}

}

void TestApp::previj(int x, int y)
{
	if (mNewTetramino)
	{
		for (int i = 0; i < 4; i++)
		{

			SetChar(x + figures[mNextTetramino][i] % 2, y + figures[mNextTetramino][i] / 2, L' ');
		}
		mTetramino = mNextTetramino;
		srand(time(NULL));
		mNextTetramino = rand() % 7; // задаём тип тетрамино
		mNewTetramino = false;
		mDirection = true;
		mDown = true;
		mObjOld.X = mObj.X = 17 / 2;
		mObjOld.Y = mObj.Y = 0;
		InicFigureOnField();
		RewritingFiguresOnFieldOld();
		CheckGameOver();
		mSpeed = 30;
		for (int i = 0; i < 4; i++)
		{
			SetChar(x + figures[mNextTetramino][i] % 2, y + figures[mNextTetramino][i] / 2, L'o');//L'\033[47;30mo\033[0m'
		}
	}
}

void TestApp::artTetramino()
{
	for (int i = 0; i < 4; i++)
	{
		if (!(mObj.Y + FiguresOnField[i].Y == 0 || mObj.Y + FiguresOnField[i].Y == 22) && !(mObj.X + FiguresOnField[i].X == 0 || mObj.X + FiguresOnField[i].X == 16))
			SetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y, L'o');//L'x'
		mObjOld.X = mObj.X;
		mObjOld.Y = mObj.Y;
		RewritingFiguresOnFieldOld();
	}

}

void TestApp::RewritingFiguresOnFieldOld()
{
	for (int i = 0; i < 4; i++)
	{
		FiguresOnFieldOld[i].X = FiguresOnField[i].X;
		FiguresOnFieldOld[i].Y = FiguresOnField[i].Y;
	}
}
void TestApp::RewritingFiguresOnField()
{
	for (int i = 0; i < 4; i++)
	{
		FiguresOnField[i].X = FiguresOnFieldOld[i].X;
		FiguresOnField[i].Y = FiguresOnFieldOld[i].Y;
	}
}


void TestApp::InicFigureOnField()
{
	for (int i = 0; i < 4; i++)
	{
		FiguresOnField[i].X = figures[mTetramino][i] % 2;
		FiguresOnField[i].Y = figures[mTetramino][i] / 2;
	}
}
void TestApp::InicFigureOnFieldOld()
{
	for (int i = 0; i < 4; i++)
	{
		FiguresOnFieldOld[i].X = 1;
		FiguresOnFieldOld[i].Y = 1;
	}
}

bool TestApp::CheckLine(int i)
{
	for (int j = 0; j < 15; j++)
	{
		if (GetChar(i, j) == '.')
			return 1;
	}
	return 0;
}

void TestApp::DestroyLine()
{
	int k = 21;
	for (int i = 21; i > 0; i--)
	{
		int count = 0;
		for (int j = 1; j < 16; j++)
		{
			if (GetChar(j, i) == 'o') count++;
			SetChar(j, k, GetChar(j, i));
		}
		if (count < 15) k--;
		else mScore += 100;
	}
}
void TestApp::CheckGameOver()
{
	for (int i = 0; i < 4; i++)
		if (GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == 'o')
		{
			exit(1);
		}
}


bool TestApp::Check(int i)
{
	for (int j = 0; j < 4; j++)
		if (mObj.X + FiguresOnField[i].X == mObjOld.X + FiguresOnFieldOld[j].X && mObj.Y + FiguresOnField[i].Y == mObjOld.Y + FiguresOnFieldOld[j].Y)
			return 1;
	return 0;
}
bool TestApp::CheckY()
{
	for (int i = 0; i < 4; i++)
		if ((GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == 'o' && !Check(i)) || GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == '#')
		{
			mObj.Y = mObjOld.Y;
			mNewTetramino = true;
			return 1;
		}
	return 0;
}
bool TestApp::CheckX()
{
	for (int i = 0; i < 4; i++)
		if ((GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == 'o' && !Check(i)) || GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == '#')
		{
			mObj.X = mObjOld.X;
			return 1;
		}
	return 0;
}
void TestApp::EraseTetramino()
{
	if (mDirection)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!(mObjOld.Y + FiguresOnFieldOld[i].Y == 0 || mObjOld.Y + FiguresOnFieldOld[i].Y == 22) && !(mObjOld.X + FiguresOnFieldOld[i].X == 0 || mObjOld.X + FiguresOnFieldOld[i].X == 16))
			{
				SetChar(mObjOld.X + FiguresOnFieldOld[i].X, mObjOld.Y + FiguresOnFieldOld[i].Y, L'.');
			}
		}
	}
}
void TestApp::Rotate()
{// Вращение

	int px = FiguresOnField[1].X; // указываем центр вращения
	int py = FiguresOnField[1].Y;
	for (int i = 0; i < 4; i++)
	{
		int x = FiguresOnField[i].Y - py;
		int y = FiguresOnField[i].X - px;
		FiguresOnField[i].X = px - x;
		FiguresOnField[i].Y = py + y;
	}
}
bool TestApp::CheckRotate()
{
	for (int i = 0; i < 4; i++)
		if ((GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == 'o' && !Check(i)) || GetChar(mObj.X + FiguresOnField[i].X, mObj.Y + FiguresOnField[i].Y) == '#')
		{
			RewritingFiguresOnField();
			return 1;
		}
}



