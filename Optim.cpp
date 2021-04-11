#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>

using namespace std;

/*STRUCTURE*/
/*Dans mon programme trouve 3 grandes parties : La definition des fonctions des problèmes
						Une fonction minimisation
						Une fonction Main*/
/*FONCTIONNEMENT*/
/* Pour realiser le test j'ai fait un programme avec une fonction minimisation qui contient un switch sur les differents solveurs utilisés, afin de correspondre à celui que l'utilisateur choisira*/
/* Dans ma fonction main, on retrouve un autre switch sur les différents problèmes posés pour correspondre à celui que l'utilisateur choisira et on fait appel à la fonction minimisation pour appliquer le solveur*/


/* MISE EN ROUTE*/
/* l'executable de ce code a été généré via la commande "g++ Optim.cpp -o Optim.exe" sur le terminal Linux
   Afin de lancer l'éxécutable, il suffit de lancer la commande "./Optim.exe" 
					Un message oncernant le solveur à choisir (entre 1 et 7) vous sera demandé
					Un autre message concernant le problème à choisir (entre 1 et 4) vous sera demandé 
					Enfin un fichier result.txt sera généré. Ce fichier contient les variables à trouver et les éventuelles erreurs*/


/*INFOS*/
/* Les solveurs et les problèmes ont le même numéro que dans l'énoncé de ce test*/





					///////////////////////////////////////////////////////////////////////////////
    					          	/*fonctions à minimiser de chaque problème*/
					///////////////////////////////////////////////////////////////////////////////




/* toutes les fonctions prennent x et y en entrée pour ne pas à avoir à faire de condition sur la dimension du problème et alourdir le code par la suite*/



////////////////*fonction 1*///////////////////////
float f1(float x,float y) 
{
	float f;

	f = 2+3*x+4*x*x;

	return f;
}


////////////////*fonction 2*///////////////////////
float f2(float x, float y)
{
	float f;
	float P1[2] ={-1,2};
	float P2[2] ={-3,5};
	float P[2] ={x,y};

	/*distance entre deux points P et P1: ||P-P1|| = sqrt((x-x1)²+(y-y1)²)*/	
	f = pow(sqrt(pow(P[0]-P1[0],2)+pow(P[1]-P1[1],2)),2) + pow(sqrt(pow(P[0]-P2[0],2)+pow(P[1]-P2[1],2)),2);
	
	return f;
}


////////////////*fonction 3*///////////////////////
float f3(float x, float y)
{
	float f;
	float P1[2] ={-1,2};
	float P2[2] ={-3,5};
	float P3[2] ={-2.5,3.5};
	float P4[2] ={-4.2,3.7};
	float P[2] ={x,y};

	f = pow(sqrt(pow(P[0]-P1[0],2)+pow(P[1]-P1[1],2)),2) + pow(sqrt(pow(P[0]-P2[0],2)+pow(P[1]-P2[1],2)),2) + pow(sqrt(pow(P[0]-P3[0],2)+pow(P[1]-P3[1],2)),2) + pow(sqrt(pow(P[0]-P4[0],2)+pow(P[1]-P4[1],2)),2);

	return f;
}


////////////////*fonction 4*///////////////////////
float f4(float x, float y)
{
	float f;

	f = exp(2+3*x+4*x*x);

	return f;
}












					//////////////////////////////////////////////////////////////////////////////////////
     						/*fonction de minimisation en fonction du solveur choisi*/
					//////////////////////////////////////////////////////////////////////////////////////









void minimisation( int solv,int x_min,int x_max,int y_min,int y_max, float (&f)(float x, float y), float &optim_x, float &optim_y, float &optim_f, int &erreur)/* cette fonction permet de faire évoluer les variables optim_x, optim_y et optim_f que l'on cherche*/
{

	switch (solv)
	{
		case 1:///////////////////////////////////////////*solveur 1*//////////////////////////////////////////////////////////////////////////
		{
			optim_x = (x_max+x_min)*0.5;/*variable x recherchée*/
			optim_y = (y_max+y_min)*0.5;/*variable y recherchée*/
			optim_f = f(optim_x,optim_y);/* valeur minimale de f */
		}break;

		case 2:///////////////////////////////////////////*solveur 2*//////////////////////////////////////////////////////////////////////////
		{

			float F[10][10]; /*variable qui stocke les valeurs de f*/
			for(int i=0;i<=9;i++)
			{
				for(int j=0;j<=9;j++)
				{
					F[i][j] = f((x_min+i*(x_max-x_min)*0.1),(y_min+j*(y_max-y_min)*0.1));/* on calcul f pour chaque couple. Dans le cas ou la dimension est 1, on aura juste 10 fois la 														      meme ligne dans F, donc ceci ne provoquera pas de problèmes*/
													   /* la discretisation se fait dans cette étape en divisant l'espace par 10*/
				}
			}

			optim_x = x_min;
			optim_y = y_min;
			float Min_f = F[0][0];/*variable qui contient la plus petite valeur de f*/
			/* on parcours la matrice F créée précédament pour trouver la plus tpetite valeur de f*/
			for(int i=0; i<=9; i++)
			{
				for(int j=0; j<=9; j++)
				{
					if(F[i][j]<Min_f) /*on cherche la position en x, y de la plus petite valeur de la fonction f*/
					{
						Min_f = F[i][j];
						optim_x  = x_min + i*(x_max-x_min)*0.1;/*variable x recherchée*/
						optim_y = y_min + j*(y_max-y_min)*0.1;/*variable y recherchée*/
						optim_f = f(optim_x,optim_y);/* valeur minimale de f */
					}
				}
			}
	
		}break;

		case 3:///////////////////////////////////////////*solveur 3*//////////////////////////////////////////////////////////////////////////
		{
			/* pour ce solveur, j'ai eu du mal à comprendre ce qui était exactement demander, j'ai essayé de faire au mieux en fonction de l'énoncé*/

			/*definition du centre de l'espace*/

			float x_mid = (x_max+x_min)/2.0;
			float y_mid = (y_max+y_min)/2.0;
			
			float Min_f_x = f(x_mid,y_mid); /*varible qui contiendra le minimum de la fonction f suivant l'axe Ox */
			float Min_f_y = f(x_mid,y_mid); /*varible qui contiendra le minimum de la fonction f suivant l'axe Oy */

			/*on discretise 10 points suivant la direction d'une dimension( il y a donc 4 directions dans le cas ou la dimension dimension est 2 : suivant (x,0),(-x,0), (0,y) et (0,-y))*/
			
			float px = (x_max - x_mid)*0.1; /*pas entre chaque echantillon suivant x*/
			float py = (y_max - y_mid)*0.1; /*pas entre chaque echantillon suivant y*/

			for (int i=0;i<=9;i++) /* 10 points par directions */
			{
				if(f(i*px,0)<Min_f_x) /*on cherche le minimum de f suivant la direction (x,0)et on conserve le point associé*/
					{
						Min_f_x = f(i*px,0);
						optim_x  = i*px;
					}
			
			}

			for (int i=0;i<=9;i++) /* 10 points par directions */
			{
				if(f(-i*px,0)<Min_f_x) /*on cherche le minimum de f suivant la direction (-x,0) et on conserve le point associé*/
					{
						Min_f_x = f(i*px,0);
						optim_x  = -i*px;
					}
			

			}
	
			for (int i=0;i<=9;i++) /* 10 points par directions */
			{
				if(f(0,i*py)<Min_f_y) /*on cherche le minimum de f suivant la direction (0,y) et on conserve le point associé*/
					{
						Min_f_y = f(i*py,0);
						optim_y = i*py;
					}
			
			}
	
			for (int i=0;i<=9;i++) /* 10 points par directions */
			{
				if(f(0,-i*py)<Min_f_y) /*on cherche le minimum de f suivant la direction (0,-y) et on conserve le point associé*/
					{
						Min_f_y = f(0,-i*py);
						optim_y = -i*py;
					}
			
			}
			optim_f = f(optim_x,optim_y);/* valeur minimale de f */	
			
		}break;

		case 4:///////////////////////////////////////////*solveur 4*//////////////////////////////////////////////////////////////////////////
		/* le fait de ne pas avoir de doublons lors du tirage aléatoire n'étant pas spécifié dans l'énoncé, mon code est susceptible de générer des points doublons lors du tirage*/		
		{ 
			srand(time(NULL));/* initialisation de rand() à 0*/
			optim_x = x_min + (float(rand()) / float(RAND_MAX))*(x_max-x_min);/*tirage d'une coordonée suivant x*/
			optim_y = y_min + (float(rand()) / float(RAND_MAX))*(y_max-y_min);/*tirage d'une coordonée suivant y*/

			float R = f(optim_x,optim_y);/*premier point tiré*/
			float Min_f = R;/*variable qui contient la plus petite valeur de f*/

			for (int i=1; i<=999;i++) /*on commence à 1 car on a déjà tiré un point*/
			{
				float r_x = x_min + (float(rand()) / float(RAND_MAX))*(x_max-x_min);  /* selection aleatoire de x et y*/
				float r_y = y_min + (float(rand()) / float(RAND_MAX))*(y_max-y_min);
				R = f(r_x,r_y);/* point correspondant aux coordonnées tirées*/
				if (R<Min_f) /* on cherche f mini*/
				{
					Min_f=R;
					optim_x = r_x;/*variable x recherchée*/
					optim_y = r_y;/*variable y recherchée*/
					optim_f = Min_f;/* valeur minimale de f */
				}
			}
			
		}break;

		case 5:///////////////////////////////////////////*solveur 5*//////////////////////////////////////////////////////////////////////////
		{
			for (int i=0;i<=99;i++) /* 100 itérations */
			{

				/* ALGO 4 */
				srand(time(NULL));/* initialisation de rand() à 0*/
				optim_x = x_min + (float(rand()) / float(RAND_MAX))*(x_max-x_min);/*tirage d'une coordonée suivant x*/
				optim_y = y_min + (float(rand()) / float(RAND_MAX))*(y_max-y_min);/*tirage d'une coordonée suivant y*/

				float R = f(optim_x,optim_y);/*premier point tiré*/
				float Min_f = R;/*variable qui contient la plus petite valeur de f*/

				for (int i=1; i<=999;i++) /*on commence à 1 car on a déjà tiré un point*/
				{
					float r_x = x_min + (float(rand()) / float(RAND_MAX))*(x_max-x_min);  /* selection aleatoire de x et y*/
					float r_y = y_min + (float(rand()) / float(RAND_MAX))*(y_max-y_min);
					R = f(r_x,r_y);/* point correspondant aux coordonnées tirées*/
					if (R<Min_f) /* on cherche la fonction f minimale*/
					{
						Min_f=R;
						optim_x = r_x; /*variable x recherchée*/
						optim_y = r_y; /*variable y recherchée*/
						optim_f = Min_f;/* valeur minimale de f */
					}
				}
				/* FIN ALGO 4*/

				
				/* creation du nouvel espace de recherche centré autour du point trouvé en divisant par 2 la largeur suivant chaque dimension*/
				/* il y a des conditions car si l'on dépasse l'ancien espace de recherche, il faut rogné le nouvel espace*/

				if (optim_x + x_max/2.0<x_max)
				{	
					x_max = optim_x + x_max/2.0;
				}
		

				if (optim_x + x_min/2.0>x_min)
				{	
					x_min = optim_x + x_min/2.0;
				}
		

				if (optim_y + y_max/2.0<y_max)
				{	
					y_max = optim_y + y_max/2.0;
				}
			

				if (optim_y + y_max/2.0>y_min)
				{	
					y_min = optim_y + y_min/2.0;
				}
				
			}
			
		}break;

		case 6:///////////////////////////////////////////*solveur 6*//////////////////////////////////////////////////////////////////////////
		{
			/*definition du pas*/

			float px = 0.1*(x_max-x_min); /*pas suivant la dimension x*/
			float py = 0.1*(y_max-y_min); /*pas suivant la dimension y*/
			float p; /*pas du solveur*/
			/* on associe le pas du solveur à la dimension la plus large*/
			if (px>=py)
			{
				p=px;
			}
			else
			{
				p=py;
			}
	 
			/* varables qui permettront de vérifier la convergence*/
			float optim_x_prec[10];
			float optim_y_prec[10];

			optim_x_prec[0] = optim_x; 
			optim_y_prec[0] = optim_y;
			
			int d=0;
			int k=0;

			while (k==0) /* boucle while puisqu'on continu de réitérer le processus jusqu'à convergence ou sortie de l'espace de rtecherche */
			{
				if (optim_x<x_max and optim_x>x_min and optim_y<y_max  and optim_y>y_min) /* condition car on ne doit pas sortir de l'espace de recherche*/
				{
					/* on compare les valeurs de f pour chaque points (4 en dimension 2) et on associe les variables optim_x et otim_y pour f minimal*/
					if (f(optim_x+p,optim_y+p) <= f(optim_x-p,optim_y-p) and f(optim_x+p,optim_y+p) <= f(optim_x-p,optim_y+p) and f(optim_x+p,optim_y+p) <= f(optim_x+p,optim_y-p))
					{
						optim_x = optim_x + p;
						optim_y = optim_y + p;
					}
					else if (f(optim_x-p,optim_y-p) <= f(optim_x+p,optim_y+p) and f(optim_x-p,optim_y-p) <= f(optim_x-p,optim_y+p) and f(optim_x-p,optim_y-p) <= f(optim_x+p,optim_y-p))
					{
						optim_x = optim_x - p;
						optim_y = optim_y - p;
					}
					else if (f(optim_x+p,optim_y-p) <= f(optim_x-p,optim_y-p) and f(optim_x+p,optim_y-p) <= f(optim_x-p,optim_y+p) and f(optim_x+p,optim_y-p) <= f(optim_x+p,optim_y+p))
					{
						optim_x = optim_x + p;
						optim_y = optim_y - p;
					}
					else if (f(optim_x-p,optim_y+p) <= f(optim_x-p,optim_y-p) and f(optim_x-p,optim_y+p) <= f(optim_x+p,optim_y+p) and f(optim_x-p,optim_y+p) <= f(optim_x+p,optim_y-p))
					{
						optim_x = optim_x - p;
						optim_y = optim_y + p;
					}
					else 
					{
						cout << "ERREUR dans la comparaison."<< endl; /*le programme doit forcément remplir une des conditions du dessus, si il y a une erreur dans le code, 													l'informationsera transmise */
						erreur=4;						
					}
					
					/* on vérifie la convergence*/
					/* si jamais on retombe sur un meme point, alors la solution actuelle est la meilleure*/
					/* pour ce faire, je stocke les valeurs précédentes dans un tableau de taille 10 qui est normalement suffisantpuisque l'espavce est divisé en 10 et je compare à 						chaque passage ans la boucle for*/
					for (int i =0; i <=d;i++)
					{
						if ((optim_x==optim_x_prec[i]) and (optim_y==optim_y_prec[i]))
						{
							k=1;
							optim_f = f(optim_x,optim_y);/* valeur minimale de f */
						}
						else
						{
							optim_x_prec[d] = optim_x;
							optim_y_prec[d] = optim_y;
						}
					}
					d=d+1;
				}
				else
				{
					cout << "ERREUR, la solution est sortie de l'espace de recherche."<< endl;
					erreur=3;
					k=1;
				}
			
			}

			
			
		}break;

		case 7:///////////////////////////////////////////*solveur 7*//////////////////////////////////////////////////////////////////////////
		{

			/*on reprend la meme structure que l'algo précédent avec des conditions dans le while pour réduire le pas de 1/10 lorsque il y a convergence ALGO 6*/

			/*definition du pas*/

			float px = 0.1*(x_max-x_min); /*pas suivant la dimension x*/
			float py = 0.1*(y_max-y_min); /*pas suivant la dimension y*/
			float p; /*pas du solveur*/

			/* on associe le pas du solveur à la dimension la plus large*/
			if (px>=py)
			{
				p=px;
			}
			else
			{
				p=py;
			}
	 

			/* varables qui permettront de vérifier la convergence*/
			float optim_x_prec[10];
			float optim_y_prec[10];

			optim_x_prec[0] = optim_x; 
			optim_y_prec[0] = optim_y;
			
			int d=0;
			int k=0;

			while (k==0) /* boucle while puisqu'on continu jusqu'à convergence*/
			{
				if (optim_x<x_max and optim_x>x_min and optim_y<y_max  and optim_y>y_min) /* condition car on ne doit pas sortir de l'espace de recherche*/
				{
					/* on compare les valeurs de f pour chaque points (4 en dimension 2) et on associe les variables optim_x et otim_y pour f minimal*/
					if (f(optim_x+p,optim_y+p) <= f(optim_x-p,optim_y-p) and f(optim_x+p,optim_y+p) <= f(optim_x-p,optim_y+p) and f(optim_x+p,optim_y+p) <= f(optim_x+p,optim_y-p))
					{
						optim_x = optim_x + p;
						optim_y = optim_y + p;
					}
					else if (f(optim_x-p,optim_y-p) <= f(optim_x+p,optim_y+p) and f(optim_x-p,optim_y-p) <= f(optim_x-p,optim_y+p) and f(optim_x-p,optim_y-p) <= f(optim_x+p,optim_y-p))
					{
						optim_x = optim_x - p;
						optim_y = optim_y - p;
					}
					else if (f(optim_x+p,optim_y-p) <= f(optim_x-p,optim_y-p) and f(optim_x+p,optim_y-p) <= f(optim_x-p,optim_y+p) and f(optim_x+p,optim_y-p) <= f(optim_x+p,optim_y+p))
					{
						optim_x = optim_x + p;
						optim_y = optim_y - p;
					}
					else if (f(optim_x-p,optim_y+p) <= f(optim_x-p,optim_y-p) and f(optim_x-p,optim_y+p) <= f(optim_x+p,optim_y+p) and f(optim_x-p,optim_y+p) <= f(optim_x+p,optim_y-p))
					{
						optim_x = optim_x - p;
						optim_y = optim_y + p;
					}
					else 
					{
						cout << "ERREUR dans la comparaison."<< endl; /*le programme doit forcément remplir une des conditions du dessus, si il y a une erreur dans le code, 													l'information sera transmise */
						k=1;
					}
					
					/* on vérifie la convergence*/
					/* si jamais on retombe sur un meme point, alors la solution actuelle est la meilleure*/
					/* pour ce faire, je stocke les valeurs précédentes dans un tableau de taille 10 qui est normalement suffisantpuisque l'espavce est divisé en 10 et je compare à 						chaque passage ans la boucle for*/
					
					/* si il y a convergence le pas est reduit de 1/10 et on recommence*/
					for (int i=0; i<=d;i++)
					{
						if (optim_x == optim_x_prec[i] and optim_y ==optim_y_prec[i])
						{
							if (p<0.01)
							{
								k=1; /*lorsque k passe à 0, la boucle se temrine car on a trouvé un résultat à 10e-3 près*/
								optim_f = f(optim_x,optim_y);/* valeur minimale de f */
							}
							else
							{
								p=0.1*p;
							}
						}
						else
						{
							optim_x_prec[d] = optim_x;
							optim_y_prec[d] = optim_y;
						}
					}
					d=d+1;	
				}
				else
				{
					cout << "ERREUR, la solution est sortie de l'espace de recherche."<< endl;
					erreur=3;
					k=1;
				}
			
			}

			
		}break;

		default: ///////////////////////////////default//////////////////////////////////////////////////
		{
			cout << "ERREUR, le numéro du solveur est mal défini."<< endl;
			erreur =2;
		}break;
	}
}













					////////////////////////////////////////////////////////////////////////////
									/*MAIN*/
					///////////////////////////////////////////////////////////////////////////









int main()
{
	/* instruction pour l'utilisateur*/
	int solv;
	int probl;
	cout << "numéro du solveur :";cin>>solv;/*on demande à l'opérateur d'écrire le numéro du solveur */
	cout << "numéro du problème :";cin>>probl;/*on demande à l'opérateur d'écrire le numéro du problème  */
	
	/*generation du fichier txt où sont contenus les resultats*/
	ofstream flux;
	flux.open("result.txt");
	
	/*switch sur les problemes choisis*/
	if(flux)
	{
		/* initialisation variables*/
		float optim_x = 0; /* variable à écrire dans le fichier texte*/
		float optim_y = 0; /* variable à écrire dans le fichier texte*/
		float optim_f = 0; /* valeur optimale de f*/
		int x_min = -1000;
		int x_max = 1000;
		int y_min = -1000;
		int y_max = 1000;
		int erreur = 0;/* variable permettant d'identifier les erreurs
					1 : numéro du problème mal défini 
					2 : numéro du solveur mal défini
					3 : la solution est sortit de l'espace de recherche
				elles s'affichent dans le fichier texte comme demander et aussi sur le terminal (ceci est plus pratique que de recharger le fichier texte à chaque fois)*/

		switch (probl)
		{
			case 1: ////////////////////////////////////*probleme 1*/////////////////////////////////////
			{
				/*definition du problème*/
				x_min = -2;
				x_max = 2;
				y_min = -2;
				y_max = 2;
				
				/* application de la minimisation*/
				minimisation(solv,x_min,x_max,y_min,y_max,f1,optim_x,optim_y,optim_f,erreur);
				
				/* ecriture sur le fichier txt de sortie*/

				/* verificationsi il y a une erreur*/
		
				if (erreur ==2)
				{
					flux << "ERREUR, le numéro du solveur est mal défini." << endl;
				}
				else if (erreur ==3)
				{
					flux << "ERREUR, la solution est sortie de l'espace de recherche." << endl;
				}
				else /* ecriture du resultat*/
				{
					flux << " valeur optimale : F ="<< optim_f << endl;
					flux << "                   X ="<< optim_x << endl;
				}
			}break;


			case 2: ////////////////////////////////////*probleme 2*/////////////////////////////////////
			{
				/*definition du problème*/
				x_min = -100;
				x_max = 100;
				y_min = -100;
				y_max = 100;

				/* application de la minimisation*/
				minimisation(solv,x_min,x_max,y_min,y_max,f2,optim_x,optim_y,optim_f,erreur);
	
				/* ecriture sur le fichier txt de sortie*/

				/* verificationsi il y a une erreur*/
				if (erreur ==2)
				{
					flux << "ERREUR, le numéro du solveur est mal défini." << endl;
				}
				else if (erreur ==3)
				{
					flux << "ERREUR, la solution est sortie de l'espace de recherche." << endl;
				}
				else /* ecriture du resultat*/
				{
					flux << " valeurs optimales : F ="<< optim_f << endl;
					flux << "                     X ="<< optim_x << endl;
					flux << "                     Y ="<< optim_y << endl;

				}
			}break;


			case 3: ////////////////////////////////////*probleme 3*/////////////////////////////////////
			{
				/*definition du problème*/
				x_min = -100;
				x_max = 100;
				y_min = -100;
				y_max = 100;

				/* application de la minimisation*/
				minimisation(solv,x_min,x_max,y_min,y_max,f3,optim_x,optim_y,optim_f,erreur);

				/* ecriture sur le fichier txt de sortie*/

				/* verificationsi il y a une erreur*/
				if (erreur ==2)
				{
					flux << "ERREUR, le numéro du solveur est mal défini." << endl;
				}
				else if (erreur ==3)
				{
					flux << "ERREUR, la solution est sortie de l'espace de recherche." << endl;
				}
				else /* ecriture du resultat*/
				{
					flux << " valeurs optimales : F ="<< optim_f << endl;
					flux << "                     X ="<< optim_x << endl;
					flux << "                     Y ="<< optim_y << endl;

				}
			}break;


			case 4: ////////////////////////////////////*probleme 4*/////////////////////////////////////
			{
				/*definition du problème*/
				x_min=-2;
				x_max=2;
				y_min = -2;
				y_max = 2;

				/* application de la minimisation*/
				minimisation(solv,x_min,x_max,y_min,y_max,f4,optim_x,optim_y,optim_f,erreur);

				/* ecriture sur le fichier txt de sortie*/

				/* verificationsi il y a une erreur*/
		
				if (erreur ==2)
				{
					flux << "ERREUR, le numéro du solveur est mal défini." << endl;
				}
				else if (erreur ==3)
				{
					flux << "ERREUR, la solution est sortie de l'espace de recherche." << endl;
				}
				else /* ecriture du resultat*/
				{
					flux << " valeur optimale : F ="<< optim_f << endl;
					flux << "                   X ="<< optim_x << endl;
				}
			}break;

			
			default:/*numero du problème incorrect*/
			{
				cout << "ERREUR, le numéro du problème est mal défini."<< endl;
				erreur=1;
				flux <<"ERREUR, le numéro du problème est mal défini."<< endl;
			}break;
		
		}

	}

	else
	{
		cout << "ERREUR."<< endl;
	}

	return 0;
}






