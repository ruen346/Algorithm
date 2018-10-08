#include <iostream>
#include <math.h>
using namespace std;

struct nums
{
	int x;
	int y;
};

nums num[30] = { {316, 353}, {253, 857}, {743, 851}, {183, 998}, {262, 439}, {330, 732}, {418, 232}, {856, 448}, {596, 658}, {266, 100}, {890, 793}, {665, 864}, {238, 657}, {636, 731}, {735, 606}, {562, 203}, {492, 701}, {306, 393}, {798, 939}, {921, 176}, {637, 780}, {620, 975}, {718, 94}, {887, 749}, {756, 560}, {525, 805}, {229, 29}, {352, 570}, {670, 589}, {644, 821}, };

int find_x[2];
int find_y[2];
float find_far = 5000;

void search(int cut1, int cut2)
{
	int cho = cut2 - cut1;
	if (cho <= 3)
	{
		float peta1 = sqrt((abs(num[cut1].x - num[cut2].x) * abs(num[cut1].x - num[cut2].x)) + (abs(num[cut1].y - num[cut2].y) * abs(num[cut1].y - num[cut2].y)));
		if (cho == 2)
		{
			cout << "(" << num[cut1].x << "," << num[cut1].y << ")(" << num[cut2].x << "," << num[cut2].y << ") : " << peta1 << endl;
			if (find_far > peta1)
			{
				find_far = peta1;
				find_x[0] = num[cut1].x;
				find_y[0] = num[cut1].y;
				find_x[1] = num[cut2].x;
				find_y[1] = num[cut2].y;
			}
		}
		else
		{
			cout << "(" << num[cut1].x << "," << num[cut1].y << ")(" << num[cut2].x << "," << num[cut2].y << ") : " << peta1 << endl;
			if (find_far > peta1)
			{
				find_far = peta1;
				find_x[0] = num[cut1].x;
				find_y[0] = num[cut1].y;
				find_x[1] = num[cut2].x;
				find_y[1] = num[cut2].y;
			}
		}
	}
	else
	{
		search(cut1, cut1 + cho / 2);
		search(cut1 + cho / 2 + 1, cut2);
	}
}

int main()
{
	int save = 0;
	for (int i = 1; i < 30; i++)
	{
		for (int j = 1; j < 30; j++)
		{
			if (num[j - 1].x > num[j].x)
			{
				save = num[j].x;
				num[j].x = num[j - 1].x;
				num[j - 1].x = save;
			}
			if (num[j - 1].y > num[j].y)
			{
				save = num[j].y;
				num[j].y = num[j - 1].y;
				num[j - 1].y = save;
			}
		}
	}

	search(0,29);

	cout << endl << "최단거리 = (" << find_x[0] << "," << find_y[0] << ")(" << find_x[1] << "," << find_y[1] << ") : " << find_far << endl;

	return 0;
}