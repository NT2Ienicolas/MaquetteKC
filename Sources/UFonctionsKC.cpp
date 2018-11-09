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
