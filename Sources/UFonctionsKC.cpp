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

/**
 * \fn int CoordMilieu(TImage *imgCarouse, int *X, int *Y)
 * \brief Transforme les coordonnées en coordonnées par rapport au centre
 *
 * \param
 * \return
 *
 *
 */
void CoordMilieu(TImage *imgCarousel, int *X, int *Y)
{
	*X = imgCarousel->Width / 2 + DeltaCentreX;
	*Y = imgCarousel->Height / 2 + DeltaCentreY;
}

/**
 * \fn int GetClickObject(TImage *imgCarouse, int X, int Y, int iPrecision, int *iTypeObj, int *iIndObj)
 * \brief Retrouve le type et l'indice de l'objet cliqué en fonction des coordonnées cliquées
 *
 * \param
 * \return
 *
 *
 */
void GetClickObject(TImage *imgCarousel, int X, int Y, int iPrecision, int *iTypeObj, int *iIndObj)
{
	// iTypeObj : 1 : Reagent - 2 : cercle central - 3 : K7 - 4 : Dilution - 5 : Bottle
	*iTypeObj = -1;
	*iIndObj = -1;

    //Calcul des coordonnées du point par rapport au centre
	int Xmilieu, Ymilieu;
	CoordMilieu(imgCarousel, &Xmilieu, &Ymilieu);
	int iDistance = CalculDistance(X, Y, Xmilieu, Ymilieu);
	int Xcercle, Ycercle;
	Xcercle = X - Xmilieu;
	Ycercle = Ymilieu - Y;
	int iDistanceCercle = CalculDistance(Xcercle, Ycercle, 0, 0);
	double Angle = atan2(Xcercle, Ycercle);

	//Suivant la distance
	if (iDistance < RayonIntK7) //Rond central
		*iTypeObj = 0;
	else if (iDistance < RayonExtK7) //K7
	{
		Angle -= GetDelta() + (2.0 * Pi / 6.0);   //on décale d'un sixième de tour ?? Pourquoi ?
		while (Angle < 0)
			Angle += 2 * Pi;
		while (Angle >= (2 * Pi))
			Angle -= 2 * Pi;

		int iK7 = (int)(Angle / GetAngleObject(3));
		*iTypeObj = 3;
		*iIndObj = iK7;

		/*
		if (sgK7->Cells[1][iK7] == "T")
		{
			if (iDistance < (int)(RayonIntTube + (TubeWidth / 2))) //Cercle intérieur
			{
				int iTube = (int)(Angle / GetAngleObject(6));

				if (iPrecision == 1)
				{
					*iTypeObj = 6;
					iTube = (iTube % iNbTubeK7Int) + ((iNbTubeK7Int + iNbTubeK7Ext - 1) * iK7);
					*iIndObj = iTube;
				}
			}
			else //Cercle extérieur
			{
				int iTube = (int)(Angle / GetAngleObject(7));

				if ((iPrecision == 1) && ((iTube % iNbK7) != 4))
				{
					*iTypeObj = 6;
					iTube = (iTube % iNbTubeK7Ext);
					if (iTube > 4)
						iTube --;
					iTube += iNbTubeK7Int + ((iNbTubeK7Int + iNbTubeK7Ext - 1) * iK7);
					*iIndObj = iTube;
				}
			}
		}
		else if (sgK7->Cells[1][iK7] == "C")
		{
			if (iDistance < RayonExtDil) //Plaque de dilution
			{
				int iDil = (int)(Angle / GetAngleObject(4));

				if (iPrecision == 1)
				{
					*iTypeObj = 4;
					*iIndObj = iDil;
				}
			}
			else if (iDistance < RayonExtBottle)
			{
				int iBottle = (int)(Angle / GetAngleObject(5));

				if (iPrecision == 1)
				{
					*iTypeObj = 5;
					*iIndObj = iBottle;
				}
			}
		}
		*/
	}
	else //Coins "extérieurs"
		*iTypeObj = 0;
}

/**
 * \fn int GetDelta()
 * \brief
 *
 * \param
 * \return
 *
 *
 */
double GetDelta()
{
	double dDelta = (90.0 / 360.0) * 2.0 * Pi;

	double dDecalage = 0.0;
	dDecalage = (double)((double)iOffsetK7 /(double) iNbK7);
	dDecalage = (double)(dDecalage * 2.0 * Pi);

	dDelta += dDecalage;
	if (dDelta < 0)
		dDelta += 2.0 * Pi;
	if (dDelta >= (2.0 * Pi))
		dDelta -= 2.0 * Pi;
	return dDelta;
}

/**
 * \fn int SetOffsetK7(int iVal)
 * \brief
 *
 * \param
 * \return
 *
 *
 */
void SetOffsetK7(int iVal)
{
	iOffsetK7 = iVal;
}

/**
 * \fn int GetOffsetK7()
 * \brief
 *
 * \param
 * \return
 *
 *
 */
int GetOffsetK7()
{
    return iOffsetK7;
}

