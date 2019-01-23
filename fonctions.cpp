/*******************************************
    Programme   : PROJET année u. 18-19 - BEZIER - PROG-TOURRETTE-MOUSSARD
    Fichier     : fonctions.cpp
    Objectif    : Fournir les fonctions nécessaires à la partie mathématique du programme
    Auteurs     : Nicolas TOURRETTE (ESIREM Dijon) - nicolas_tourrette@etu.u-bourgogne.fr
                  Anindo MOUSSARD (ESIREM Dijon) - anindo_moussard@etu.u-bourgogne.fr
    Date        : 28-12-2018
    Version     : V0.4
    Modifié le  : 28-12-2018 14:49
********************************************/

#include "fonctions.hpp"

/**
  * Description	: Calcul du degré de la fonction
  * Arguments	: double (coefficients des degrés de x, indice 1 pour le numérateur, indice 2 pour le dénominateur)
  * Retour		: int degre, le degré de la fonction
  */

int degre_poly(double a, double b, double c, double d, double e, double f, double g){
    int degre;
    if(a != 0)
        degre = 3;
    else if(e != 0)
        degre = 3;
    else if(b != 0)
        degre = 2;
    else if(f != 0)
        degre = 2;
    else
        degre = 1;
    return degre;
}

/**
  * Description	: Calcul des asymptotes horizontales, verticales et obliques pour une fonction rationnelle passée en paramètre
  * Arguments	: int (coefficients des degrés de x, indice 1 pour le numérateur, indice 2 pour le dénominateur)
  * Retour		: int, le nombre d'asymptotes
  */

int CalculAsymptotes(double a, double b, double c, double d, double e, double f, double g, double tab_verticales[]){
    int nb_asymptote = 0;
    // Asymptote horizontale
    double horizontal ;
    horizontal = (a*1000000000.0 + b*1000000.0 + c*1000.0 + d)/(e*1000000.0 + f*1000.0 + g) ;
    if(horizontal < 10){
        cout << "On a une asymptote horizontale en y = " << horizontal << "." << endl ;
    }
    else{
        cout << "Pas d'asymptote horizontale." << endl ;
    }

    // Asymptote verticale
    bool asymptote_verticale = false ;
    if(e != 0){
        double r1, r2, delta ;
        delta = f*f - 4*e*g ;
        r1 = (-f-sqrt(delta))/(2*e) ;
        r2 = (-f+sqrt(delta))/(2*e) ;
        if(!isnan(r1) && !isinf(r1)){
            asymptote_verticale = true ;
            tab_verticales[0] = r1;
            nb_asymptote ++;
            cout << "On a une asymptote verticale en x = " << r1 << "." << endl ;
        }
        if(!isnan(r2) && !isinf(r2)){
            asymptote_verticale = true ;
            tab_verticales[1] = r2;
            nb_asymptote ++;
            cout << "On a une asymptote verticale en x = " << r2 << "." << endl ;
        }
    }
    else if(a == 0 && e == 0){
        double r = -(double)g/(double)f ;
        if(!isnan(r) && !isinf(r)){
            asymptote_verticale = true ;
            tab_verticales[0] = r;
            nb_asymptote ++;
            cout << "On a une asymptote verticale en x = " << r << "." << endl ;
        }
    }
    if(!asymptote_verticale){
        cout << "Pas d'asymptote verticale." << endl ;
    }

    // Asymptote oblique y = mx + p
    if(a!= 0 && e != 0){
        double m = (double)a/(double)e ;
        double p = (b-(double)((a*f)/(double)e))/(double)e ;
        cout << "On a une asymptote oblique en y(x) = " << m << "*x + " << p << "." << endl ;
    }
    else if(a == 0 && b != 0 && e == 0 && f != 0){
        double m = (double)b/(double)f ;
        double p = (c-(double)((b*g)/(double)f))/(double)f ;
        cout << "On a une asymptote oblique en y(x) = " << m << "*x + " << p << "." << endl ;
    }
    else if(a == 0 && b == 0 && e == 0 && f == 0){
        cout << "On a une asymptote oblique en y(x) = (" << c << "*x + " << d << ")/" << g << "." << endl ;
    }
    else{
        cout << "Pas d'asymptote oblique." << endl ;
    }

    // Appel de la fonction d'écriture de l'équation paramétrique pour la courbe de Bézier
    EquationParametrique(a, b, c, d, e, f, g) ;
    return nb_asymptote;
}

/**
  * Description	: Saisie d'une fonction rationnelle personnalisée non présente dans le menu par saisie des coefficients de x
  * Arguments	: void
  * Retour		: double, tableau des coefficients
  */

double* FonctionRationnelle(){
    double *coefficients=new double[7];
    cout << "Saisir une fonction rationnelle de la forme (ax³ + bx² + cx + d)/(ex² + fx + g) en saisissant les coefficients (entiers) a, b, c, d, e, f et g." << endl ;
    for(int i=0 ; i<7 ; ++i){
        cout << "Saisir le coefficient " << i+1 << " : " ;
        cin >> coefficients[i] ;
        viderBuffer() ;
    }
    cout << endl << "Vous avez saisi la fonction rationnelle f(x) = (" << coefficients[0] << "x³ + " << coefficients[1] << "x² + " << coefficients[2] << "x + " << coefficients[3] << ")/(" << coefficients[4] << "x² + " << coefficients[5] << "x + " << coefficients[6] << ")." << endl ;
   return coefficients;
}

/**
  * Description	: Calcul de l'équation paramétrique d'une fonction rationnelle pour les courbes de Bézier
  * Arguments	: double (coefficients des degrés de x: a, b, c et d pour le numérateur, e, f et g pour le dénominateur)
  * Retour		: void
  */

void EquationParametrique(double a, double b, double c, double d, double e, double f, double g){
    cout << "Pour l'équation paramétrique pour les courbes de Bézier, on prend x(t) = t et y(t) = f(t). On a donc :" << endl ;
    cout << "   --" << endl ;
    cout << "   | x(t) = t" << endl ;
    cout << "   | y(t) = (" << a << "t³ + " << b << "t² + " << c << "t + " << d << ")/(" << e << "t² + " << f << "t + " << g << ")." << endl ;
    cout << "   --" << endl ;
}

/**
  * Description	: Calcul des poids
  * Arguments	: double (coefficients des degrés de x : e, f et g pour le dénominateur)
  * Retour		: double, le tableau des poids
  */

double* poid(double e, double f, double g, int degre){
    int i;
    //calcul des poids à partir des formules mathématiques
    double* tab_poid;
    if(degre == 1){
        tab_poid = new double[2];
        tab_poid[0] = g;
        tab_poid[1] = g;
    }
    else if(degre == 2){
       tab_poid = new double[3];
       tab_poid[0] = g;
       tab_poid[1] = f/2.0 + g;
       tab_poid[2] = f + g;
    }
    else if(degre == 3){
        tab_poid = new double[4];
        tab_poid[0] = g;
        tab_poid[1] = f/3.0 + g;
        tab_poid[2] = e/3.0 + (2.0*f)/3.0 + g;
        tab_poid[3] = e + f + g;
    }
    return tab_poid;
}

/**
  * Description	: Calcul des coefficients
  * Arguments	: double (coefficients des degrés de x : a, b, c et d pour le numérateur et e, f et g pour le dénominateur) et int degré de la fonction
  * Retour		: double, le tableau des poids*abscisses ou ordonnées (tableau à deux dimensions)
  */

double** coeff_num(double a, double b, double c, double d, double e, double f, double g, int degre){
    double** tab_coeff_num;
    if(degre == 1){
        tab_coeff_num = new double*[2];
        for(int i=0;i<2;i++){
            tab_coeff_num[i] = new double[2];
        }
        tab_coeff_num[0][0] = 0.0;
        tab_coeff_num[0][1] = d;
        tab_coeff_num[1][0] = g;
        tab_coeff_num[1][1] = c + d;
    }
    if(degre == 2){
        tab_coeff_num = new double*[3];
        for(int i=0;i<3;i++){
            tab_coeff_num[i] = new double[2];
        }
        tab_coeff_num[0][0] = 0;
        tab_coeff_num[0][1] = d;
        tab_coeff_num[1][0] = g/2.0;
        tab_coeff_num[1][1] = c/2.0 + d;
        tab_coeff_num[2][0] = f + g;
        tab_coeff_num[2][1] = b + c + d;
    }
    else if(degre == 3){
        tab_coeff_num = new double*[4];
        for(int i=0;i<4;i++){
            tab_coeff_num[i] = new double[2];
        }
        tab_coeff_num[0][0] = 0.0;
        tab_coeff_num[0][1] = d;
        tab_coeff_num[1][0] = g/3.0;
        tab_coeff_num[1][1] = c/3.0+d;
        tab_coeff_num[2][0] = f/3.0+2*g/3.0;
        tab_coeff_num[2][1] = b/3.0+2*c/3.0+d;
        tab_coeff_num[3][0] = e+f+g;
        tab_coeff_num[3][1] = a+b+c+d;
    }
    return tab_coeff_num;
}

/**
  * Description	: Calcul des points de contrôle
  * Arguments	: double (tableau des poids, des poids*coordonnées) et int degré de la fonction
  * Retour		: void
  */

void pts_controle(double* tab_poid , double** tab_coeff_num, int degre){
    int i,j;
    double tab_pts_controles[degre+1][2];
    ofstream objetfichier("fichier_test/Coordonnées_pts_controle.txt", ios::out | ios::trunc); //on ouvre le fichier en ecriture
	if (objetfichier.bad()) //permet de tester si le fichier s'est ouvert sans probleme
 		cout << "Problème lors de l'ouverture du fichier" <<endl;
    for(j=0;j<degre+1;j++){
        for(i=0;i<2;i++){
            if(tab_poid[j] == 0)
                tab_pts_controles[j][i] = tab_coeff_num[j][i]; //vecteurs de controle
            else
                tab_pts_controles[j][i] = tab_coeff_num[j][i]/tab_poid[j];

            if(i == 1)
				objetfichier << "P" << j << " : (" << tab_pts_controles[j][0] << ";" << tab_pts_controles[j][1] << ") w" << i << " = " << tab_poid[j] << endl;//on écrie les coordonées du pts dans le fichier
        }
    }
    objetfichier.close();
}

/**
  * Description	: Calcul des coordonnées d'un point avec les polynômes de Bernstein appliqués avec les points de contrôles
  * Arguments	: double (tableau des poids, des poids*coordonnées), double t variable et int degré de la fonction
  * Retour		: double tableau des coordonnées
  */

double* pts_bezier(double* tab_poid , double** tab_coeff_num, double t, int degre){
    int i,j;
    double Px, Py, num_Px=0, num_Py=0, deno_Px=0, deno_Py=0;
    double *tab_coord=new double[2];
    double *tab_poly_bern;
    if(degre == 1){
        tab_poly_bern = new double[2];
        tab_poly_bern[0] = 1-t;
        tab_poly_bern[1] = t;
    }
    else if(degre == 2){
        tab_poly_bern = new double[3];
        tab_poly_bern[0] = pow(1-t,2);
        tab_poly_bern[1] = 2*t*(1-t);
        tab_poly_bern[2] = pow(t,2);
    }
    else if(degre == 3){
        tab_poly_bern = new double[4];
        tab_poly_bern[0] = pow(1-t,3);
        tab_poly_bern[1] = 3*t*pow(1-t,2);
        tab_poly_bern[2] = 3*pow(t,2)*(1-t);
        tab_poly_bern[3] = pow(t,3);
    }
        for(j=0;j<degre+1;j++){
            for(i=0;i<2;i++){

                if(i == 0){
                    num_Px = num_Px + tab_coeff_num[j][i]*tab_poly_bern[j];
                    deno_Px = deno_Px + tab_poid[j]*tab_poly_bern[j];
                }
                if(i == 1){
                    num_Py = num_Py + tab_coeff_num[j][i]*tab_poly_bern[j];
                    deno_Py = deno_Py + tab_poid[j]*tab_poly_bern[j];
                }
            }
        }
    tab_coord[0] = num_Px/deno_Px;
    tab_coord[1] = num_Py/deno_Py;
    return tab_coord;
}



double* homographie(double t, double borne1, double borne2, double deno1, double deno2, double* tab_poid, double** tab_coeff_num, int degre){
	double a = borne1;
	double b = borne2;
	double c = deno1;
	double d = deno2;
	double h = (a*(1-t)+b*t)/((1-t)*c+t*d);
    double* test = new double[2];
	test =pts_bezier(tab_poid,tab_coeff_num,h,degre);
	return test;
}

double** calcul_homo(int nb_asymptote, double t, double tab_verticales[], double* tab_poid, double** tab_coeff_num,int degre){
 	double **tab_homo;
 	if(nb_asymptote == 0){
 		tab_homo=new double*[2];
 		tab_homo[0] = homographie(t,-1,0,0,1,tab_poid,tab_coeff_num,degre);
 		tab_homo[1] = homographie(t,0,1,1,0,tab_poid,tab_coeff_num,degre);

 	}
 	else if(nb_asymptote == 1){
 		tab_homo=new double*[2];
 		tab_homo[0] = homographie(t,-1,tab_verticales[0],0,1,tab_poid,tab_coeff_num,degre);
 		tab_homo[1] = homographie(t,tab_verticales[0],1,1,0,tab_poid,tab_coeff_num,degre);
 	}
 	else if(nb_asymptote == 2){
 		tab_homo=new double*[3];
 		tab_homo[0] = homographie(t,-1,tab_verticales[0],0,1,tab_poid,tab_coeff_num,degre);
 		tab_homo[1] = homographie(t,tab_verticales[0],tab_verticales[1],1,1,tab_poid,tab_coeff_num,degre);
 		tab_homo[2] = homographie(t,tab_verticales[1],1,1,0,tab_poid,tab_coeff_num,degre);
  	}
 	return tab_homo;
}

/**
  * Description	: Affichage du menu principal
  * Arguments	: void
  * Retour		: void
  */

void MenuPrincipal(){
    cout << "*******                         MENU PRINCIPAL                       *******" << endl ;
    cout << "Vous voici dans le menu principal. On modélisera ici les fonctions représentées dans le sujet.\nVoici les actions que vous pouvez exécuter :" << endl ;
    cout << "    1- Fonction rationnelle de la figure 1" << endl ;
    cout << "    2- Fonction rationnelle de la figure 2" << endl ;
    cout << "    3- Fonction rationnelle de la figure 3" << endl ;
    cout << "    4- Fonction de la figure 4" << endl ;
    cout << "    5- Saisir une fonction rationnelle" << endl ;
    cout << "    6- Quitter le programme" << endl ;
}

/**
  * Description	: Permet d'éviter des problèmes de saisie avec le clavier (retour chariot non consommé)
  * Arguments	: void
  * Retour		: void
  */

void viderBuffer(){
    int c ;
    while((c=getchar()) != EOF && c != '\n') ;
}
