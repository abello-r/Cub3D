#include "mini.h"

int		main(void)
{
	//int		x;
	//int		y;
	int		screenwidth;
	int		rayCount;
	float	rayAngle;
	float	playerangle;
	float	playerhalfov;
	float	rayCos;
	float	raySin;

	rayCount = 0;
	raySin = 0;
	rayCos = 0;
	screenwidth = 1080;
	playerangle = -30;
	playerhalfov = 60;
	rayAngle = playerangle - playerhalfov;

	while (rayCount < screenwidth)
	{
		rayCount++;
		rayAngle++;
	}
	printf("%3.f\n", rayAngle);
	//rayCos = cos(rayAngle * M_PI / 180);
	rayCos = cos(rayAngle * M_PI / 180);

	printf("%.3f raycos", rayCos);
	printf("\n%d raycount", rayCount);
	return(0);
}

