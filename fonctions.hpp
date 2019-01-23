/*******************************************
    Programme   : PROJET année u. 18-19 - BEZIER - PROG-TOURRETTE-MOUSSARD
    Fichier     : fonctions.hpp
    Objectif    : Fournir les fonctions nécessaires à la partie mathématique du programme
    Auteurs     : Nicolas TOURRETTE (ESIREM Dijon) - nicolas_tourrette@etu.u-bourgogne.fr
                  Anindo MOUSSARD (ESIREM Dijon) - anindo_moussard@etu.u-bourgogne.fr
    Date        : 28-12-2018
    Version     : V0.4
    Modifié le  : 28-12-2018 14:49
********************************************/

#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <iostream>
#include <cmath>
#include <fstream> 
#include <GL/glut.h>

using namespace std ;

int degre_poly(double a, double b, double c, double d, double e, double f, double g);
void EquationParametrique(double a, double b, double c, double d, double e, double f, double g) ;
int CalculAsymptotes(double a, double b, double c, double d, double e, double f, double g, double tab_verticales[]) ;
double* FonctionRationnelle() ;
double* poid(double e, double f, double g, int degre);
double** coeff_num(double a, double b, double c, double d, double e, double f, double g, int degre);
void pts_controle(double* tab_poid , double** tab_coeff_num, int degre);
double* pts_bezier(double* tab_poid , double** tab_coeff_num, double t, int degre);
double* homographie(double t, double borne1, double borne2, double deno1, double deno2, double* tab_poid, double** tab_coeff_num, int degre);
double** calcul_homo(int nb_asymptote, double t, double tab_vetrticales[], double* tab_poid, double** tab_coeff_num,int degre);
void viderBuffer();
void MenuPrincipal();
void affichage();//  procedure a modifier en fonction de la scene
void clavier(unsigned char touche,int x,int y); 
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void init();
void procedure(double a, double b, double c, double d, double e, double f, double g);
#endif
