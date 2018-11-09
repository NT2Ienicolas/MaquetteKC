/**
 * \file UFonctionsKC.h
 * \brief Constantes et fonctions de base
 * \author E.N.
 * \version 0.1
 * \date 09/11/2018
 *
 * Regroupe la définition des constantes et les fonctions de
 * calcule des coordonnées
 *
 */

#pragma hdrstop

#include "UFonctionsKC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
 * \fn double GetAngleObject(int iTypeObj)
 * \brief Calcul de l'angle du secteur d'un objet en fonction de son type
 *
 * \param Sender
 * \return .
 *
 *
 */
double GetAngleObject(int iTypeObj)
{
	double dAngle = 0.0;
	if (iTypeObj  > 0)
	{
		if (iTypeObj == 1) //Reagent
			dAngle = (double)((1.0 / (double)(iNbReagent)) * 2 * Pi);
		else if (iTypeObj == 2) //Temp
			;//Nothing
		else if (iTypeObj == 3) //Cassette
			dAngle = (double)((1.0 / (double)(iNbK7)) * 2 * Pi);
		else if (iTypeObj == 4) //DilPlate
			dAngle = (double)((1.0 / (double)(iNbK7 * iNbDil)) * 2 * Pi);
		else if (iTypeObj == 5) //Bottle
			dAngle = (double)((1.0 / (double)(iNbK7 * iNbBottle)) * 2 * Pi);
		else if (iTypeObj == 6) //Tube "intérieur"
			dAngle = (double)((1.0 / (double)(iNbK7 * iNbTubeK7Int)) * 2 * Pi);
		else if (iTypeObj == 7) //Tube "Extérieur"
			dAngle = (double)((1.0 / (double)(iNbK7 * iNbTubeK7Ext)) * 2 * Pi);
	}
	return dAngle;
}

/**
 * \fn void Rotation(double dAngle, TImage *sBmp, TImage *dBmp, int iXDelta, int iYDelta)
 * \brief Rotation...
 *
 * \param
 * \return .
 *
 *
 */
void Rotation(double dAngle, TImage *sBmp, TImage *dBmp, int iXDelta, int iYDelta)
{
	int xDelta = iXDelta;
	int yDelta = iYDelta;

	for (int x = 0; x < sBmp->Width; x++)
	{
		for (int y = 0; y < sBmp->Height; y++)
		{
			int xt = x - sBmp->Width / 2;
			int yt = y - sBmp->Height / 2;

			int xs = (int)((cos(-dAngle) * xt - sin(-dAngle) * yt) + (sBmp->Width / 2));
			int ys = (int)((sin(-dAngle) * xt + cos(-dAngle) * yt) + (sBmp->Height / 2));

			if(xs >= 0 && xs < sBmp->Width && ys >= 0 && ys < sBmp->Height) {
				if (sBmp->Canvas->Pixels[xs][ys] != sBmp->Canvas->Pixels[0][0])
					dBmp->Canvas->Pixels[x+iXDelta][y+iYDelta] = sBmp->Canvas->Pixels[xs][ys];
			}
		}
	}
}

/**
 * \fn int CalculDistance(int X1, int Y1, int X2, int Y2)
 * \brief Calcule la distance entre deux points dont on reçoit les coordonnées en paramètre
 *
 * \param
 * \return Distance calculée
 *
 *
 */
int CalculDistance(int X1, int Y1, int X2, int Y2)
{
	return (int)sqrt(((X1 - X2) * (X1 - X2)) + (Y1 - Y2) * (Y1 - Y2));
}
