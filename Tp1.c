#include "Outil.h"
#include "Graphe.h"
#include "Tp1.h"
int bTp1AmorceR;//ie ce module a effectivement été amorcé

void DistancierCalculeR(graf *pgSimple,int bAfficher){//(O(S3)
	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgSimple->coulh[]
	int i, j, k; // Les entiers pour les boucles
	int aK,sX,sY;//a comme arc;s comme sommet
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgSimple->nSommetEnTout;
	int dM[1+nSommet][1+nSommet];//matrice des distances sur les arcs,supposées être des entiers ou des réels déjà ramenés à des entiers
	Assert1("DistancierCalculeR",bGrapheSimple(pgSimple));
	//générer la matrice d'incidence sommet-sommet dM qui décrit le graphe simple pgSimple
		//dM:=0
	int d[1+nSommet][1+nSommet];  // Matrice D des plus courtes distances
	int p[1+nSommet][1+nSommet]; // Matrice pour retrouver le plus court chemin

	for(i = 1; i <= nSommet ; i++){
		for(j = 1; j <= nSommet ; j++){
			p[i][j] = 0; // 0 partout
			if(i == j){
				d[i][j] = 0; // 0 sur la diagonale
			}else{
				d[i][j] = 1048575; // 1048575 partout, équivaut a l'infini
			}
		}
	}
	for (uL=1;uL<=nSommet;uL++){
		for (uC=1;uC<=nSommet;uC++){
			dM[uL][uC]=0;
		}
	}
	for (sX=1;sX<=nSommet;sX++){
		for (aK=pgSimple->aHed[sX];aK<pgSimple->aHed[sX+1];aK++){
			sY=pgSimple->sSuk[aK];
			dM[sX][sY]=pgSimple->coulh[aK];//distance (sX,sY), si dM existe, il y a un successeur

			if( (dM[sX][sY] != 0) && (sX != sY) ){	//exécuter l'algorithme de Floyd sur dM
				d[sX][sY] = pgSimple->coulh[aK];
				p[sX][sY] = sX;
			}
		}
	}

	for(k = 1; k <= nSommet; k++){
		for(i = 1; i <= nSommet; i++){
			for(j = 1; j < nSommet; j++){
				if(d[i][j] > d[i][k] + d[k][j]){
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = p[k][j];
				}
			}
		}
	}
	if (bAfficher){//afficher le distancier dM
		for(i = 1; i <= nSommet ; i++){
			for(j = 1; j <= nSommet ; j++){
				printf("%8i", d[i][j]);
				printf("  ");
			}
			printf("\n\n");
		}
	}
}//DistancierCalculeR

void GrapheAllouerInitialiseR(int nGraphe,int bAfficher,graf **ppgSimple){
	//alloue et décrit dans ppgSimple le graphe de rang1 nGraphe
	//pour simplifier la saisie,les sommets vont de A à Z puis de a à z et les données sont supposées être des entiers dans [0..9] 
    char ksGros[]="AB1AD1AE2BC3BG2CJ2CK1DM1DN2EF2EQ1FG2FR1GS1HI2HT1IJ1IV1JX3KY2LM2LZ1Ma1NO1Nb3OP2Oc3Pe1Qe2Qf2Rf2Rg2ST2Sg2TU2UV1Uh3VW2WX1Yj1Zj2ab2ak3bm1cd1cm2de2dn2fn1go1hi2ip1kl1lm2ln2op2Aq5Br5Cs5Dt5";
	char kcMoyen[]="AB2AH1BC1BK2CD2DE1DM2EF2FG1FO2GH2HI2IJ2IP1JK1JQ2KL2LM1LS2MN2NO1NU2OP2PU2QR5RU1ST5TU1AV2CW2EX2GY2";
	char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char *sGrapheType="ksPetit,kcMoyen,ksGros";
	Appel0("GrapheAllouerInitialiseR");
		switch(nGraphe){//NB ci-dessous,GrapheGenerer alloue puis initialise ppgSimple
			case 1:	GrapheGenerer(ksPetit,ppgSimple);
					break;
			case 2:	GrapheGenerer(kcMoyen,ppgSimple);
					break;
			case 3:	GrapheGenerer(ksGros,ppgSimple);
					break;
			default: Assert1("GrapheAllouerInitialiseR default",0);
		}//switch
		GrapheVoir0(*ppgSimple,sC2b("Graphe",sG(sItem(sGrapheType,nGraphe))),grCouleur);
		Assert1("GrapheAllouerInitialiseR",bGrapheSimple(*ppgSimple));
	Appel1("GrapheAllouerInitialiseR");
}//GrapheAllouerInitialiseR

void PerformanceCompareR(){
	int complexite[1][1]; 
	// Ligne 0: Graphe simple, Ligne 1: Graphe complexe
	// Colonne 0: DistancierCalculeR, Colonne 1: Tp1Distancier

	// Utilisation de pnComplexiteh dans l'algo de dijkstra pour calculer la complexité puis comparer

}//PerformanceCompareR

void Tp1AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp1AmorceR=kV;
}//Tp1AMORCER

void Tp1Distancier(graf *pgG,int bAfficher){
	//calculer le distancier de pgG supposé peu dense (algo de Dijkstra avec tas)
	int complexite;
	int i,j;
	int nSommet=pgG->nSommetEnTout;
	int distancier[nSommet][nSommet];

	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

	VecteurVoir1("Les vecteurs : ",pgG->nCout,1,pgG->nArcEnTout);

	for(i = 1; i <= nSommet; i++){
		for(j = 1; j <= nSommet; j++){
			distancier[i][j] = nGrapheChemineR(pgG, i, j, &complexite);
		}
	}
	
	if (bAfficher){//afficher le distancier dM
		for(i = 1; i <= nSommet ; i++){
			for(j = 1; j <= nSommet ; j++){
				printf("%8i", distancier[i][j]);
				printf("  ");
			}
			printf("\n\n");
		}
	}

}//Tp1Distancier

void Tp1INITIALISER(){//O(?)
	//relance le présent module
	Assert1("Tp1INITIALISER",bTp1AmorceR);
}//Tp1INITIALISER

void Tp1TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	float fDensiteh;
	Appel0(sC2("Tp1TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 0: //calculer la densité d'un graphe simple
			GrapheCreer(4,&pgG);
				fDensiteh=fGrapheDensiteh(pgG);
				GrapheVoir(pgG,"Graphe simple généré");
				f(fDensiteh);
			GrapheCreer(0,&pgG);
			break;
		case 1: //appeler DistancierCalculeR sur le graphe ksHomeSlipHome
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			DistancierCalculeR(pgG,k1Afficher);
			break;
		case 2: //appeler Tp1Distancier sur le graphe ksHomeSlipHome
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			Tp1Distancier(pgG,k1Afficher);
			break;
		case 3: //comparer les performances de DistancierCalculeR et Tp1Distancier
			PerformanceCompareR();
			break;
		default: Assert1("Tp1TESTER default",0);
	}
	Appel1(sC2("Tp1TESTER,test n°",sEnt(iTest)));
}//Tp1TESTER	

