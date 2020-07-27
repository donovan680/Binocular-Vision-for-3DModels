// LabRoom0.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Insight.h"

using namespace std;
using namespace Insight;

int _tmain(int argc, _TCHAR* argv[])
{
	ImageBitmap24	img24;
	ImageBitmap32	img32;

	try
	{
		img24.FromFile("F:\\FireField\\2\\t0.bmp");
		img32.CopyFrom(&img24);
		img32.ToFile("F:\\FireField\\2\\t1.bmp");

	}
	catch (Exception excep)
	{
		cout << excep.ReadInfo() << endl;
	}

	return 0;
}

