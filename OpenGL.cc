/*********************************************************/
/*                    openGL.cc                          */
/*********************************************************/
/*                                                       */
/*********************************************************/

/* inclusion des fichiers d'en-tete Glut */

#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include "fonctions.hpp"

#define Pi 3.141592654


double Scal=36;

double trX=0.0,trY=0.0,dist=0.;//,trZ=0.0
char presse;
int anglex,angley,x,y,xold,yold;


//-************************************************************
//
//  Procedure avec mise en file des sommets des primitives
//
//-***********************************************************
int degre;
int nb_asymptote;
double *tab_poid;
double **tab_coeff_num;
double *tab_coeff = new double[7];
double *tab_verticales = new double[2];
double **tab_homographique;

/**
  * Description	: Procédure qui fera afficher ce que l'on souhaite après saisie de l'entrée de menu souhaitée
  * Arguments	: double (coefficients des degrés de x : a, b, c et d pour le numérateur et e, f et g pour le dénominateur)
  * Retour		: void
  */

void procedure(double a, double b, double c, double d, double e, double f, double g){
 /* initialisation de glut et creation de la fenetre */
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1000,1000);
  glutCreateWindow("Affichage courbe de Bezier");
  /* Initialisation d'OpenGL */
  glClearColor(1.0,1.0,1.0,0.0);
  glColor3f(0.0,0.0,0.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);
  glColor3f(0.0,0.0,0.0);
  //glEdgeFlag(GL_FALSE);
  glEdgeFlag(GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  // glEnable(GL_LIGHTING);
  glDisable(GL_LIGHTING);
  // Calcul du degré de notre fonction
  degre = degre_poly(a,b,c,d,e,f,g);
  // Calcul du nombre d'asymptotes
  nb_asymptote = CalculAsymptotes(a,b,c,d,e,f,g,tab_verticales);
  // Calcul des poids et des coefficients
  tab_poid = poid(e,f,g,degre);
  tab_coeff_num = coeff_num(a,b,c,d,e,f,g,degre);
  // Calcul des points de contrôle pour Bézier
  pts_controle(tab_poid,tab_coeff_num,degre);
  // Affichage par OpenGL
  init();
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);
  //Entre dans la boucle principale de glut
  glutMainLoop();
}


int main(int argc,char **argv){
    glutInit(&argc,argv);
    int choix ;
    cout << "*******      PROJET MATHÉMATIQUES 2018-2019 / COURBES DE BÉZIER      *******" << endl ;
    cout << "*******             NICOLAS TOURRETTE ET ANINDO MOUSSARD             *******" << endl ;
    cout << "*******          -- ON TRAVAILLERA EN VALEURS APPROCHÉES --          *******" << endl ;
    do{
        cout << endl ;
        MenuPrincipal() ;
        cout << "Action souhaitée : " ;
        cin >> choix ;
        viderBuffer() ;
        cout << endl ;
        switch(choix){
            case 1 :
                cout << "Analyse de Bézier pour la figure 1 du sujet : (2x²-1)/(x²+2x-3)" << endl ;
                procedure(0.,2.,0.,-1.,1.,2.,-3.);
                break ;

            case 2 :
                cout << "Analyse de Bézier pour la figure 2 du sujet : (x³-4x²-11x+16)/(x²+2x-3)" << endl ;
                procedure(1,-4,-11,16,1,2,-3) ;
                break ;

            case 3 :
                cout << "Analyse de Bézier pour la figure 3 du sujet : (x²-x-1)/(2x-3)" << endl ;
                procedure(0,1,-1,-1,0,2,-3) ;
                break ;

            case 4 :
                cout << "Analyse de Bézier pour la figure 4 du sujet : x²" << endl ;
                procedure(0,1,0,0,0,0,1) ;
                break ;

            case 5 :
                cout << "Saisie d'une fonction rationnelle" << endl ;
                tab_coeff = FonctionRationnelle() ;
                procedure(tab_coeff[0],tab_coeff[1],tab_coeff[2],tab_coeff[3],tab_coeff[4],tab_coeff[5],tab_coeff[6]) ;
                break ;

            case 6 :
                cout << "Ce choix termine le programme." << endl ;
                break ;

            default :
                cout << "Choix " << choix << " invalide. Vous quittez le programme." << endl ;
                break ;
        }
    }while(choix > 0 && choix < 6) ;
    cout << "***  Fin du programme  ***" << endl ;

    return EXIT_SUCCESS ;
}




void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'q' : /*la touche 'q' permet de quitter le programme */
        exit(0);
    case '+' :
      dist+=0.5;
      Scal=Scal+0.5;
      glutPostRedisplay();
      break;
    case '-' :
      dist-=0.5;
      Scal=Scal-0.5;
      glutPostRedisplay();
      break;
    case '6' : trX-=0.25;  glutPostRedisplay();  break;
    case '4' : trX+=0.25;  glutPostRedisplay();  break;
    case '8' : trY+=0.25;  glutPostRedisplay();  break;
    case '2' : trY-=0.25;  glutPostRedisplay();  break;
    }
}



void reshape(int x,int y)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //taille de la scene
  double  Ortho=-150;
  glOrtho(-Ortho,Ortho,-Ortho,Ortho,-Ortho,Ortho);// fenetre
  glMatrixMode(GL_MODELVIEW);
  glViewport(0,0,x,y);
}

void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }



/****************************************************************
 **                                                            **
 **                    Affichage de  la scene                  **
 **                                                            **
 ****************************************************************/

void openGL(double x, double y, double r0,double g0, double b0, double size)
{
        glColor3f(r0,g0,b0);	//initialisation de la couleur
	glPointSize(size);	// initialisation de la taille
	glBegin(GL_POINTS);	// on trace un point
	  glVertex2f(x,y);	// coordonnees du point
	glEnd();	// fin de glBegin
}

void trace_segment(double x0, double y0,double x1, double y1, double red, double green, double blue, double size)
{
        glColor3f(red,green,blue);//initialisation de la couleur
	glLineWidth(size); // initialisation de la taille
	glBegin(GL_LINES); // on trace un segment
	  glVertex2f(x0,y0); // coordonnees du premier point
          glVertex2f(x1,y1); // coordonnees du dernier point
	glEnd(); // fin de glBegin
}


//fonction ou les objets sont a definir
void init()
{
  double i;
  double *tab_pts = new double[2];
  double *tab_tmp = new double[2];
  int intervale;
  if(nb_asymptote == 0 || nb_asymptote == 1)
    intervale = 2;
  else
    intervale = 3;
  double xO=0.,yO=0.,xI=1.,yI=0.,xJ=0.,yJ=1.,xabs=GLUT_WINDOW_WIDTH,yabs=0.,xord=0.,yord=GLUT_WINDOW_HEIGHT;
  glNewList(1,GL_COMPILE_AND_EXECUTE); //liste numero 1
  openGL(xI,yI,1.,0.,0.,10.); //I
  openGL(xJ,yJ,0.,0.5,0.,10.); //J
  openGL(xO,yO,0.,0.,1.,15.);//O
  glEndList();
  glNewList(2,GL_COMPILE_AND_EXECUTE);  //liste numero 2
    trace_segment(xO,yO,xI,yI,0.0,.0,1.0,2.0); // on trace [OI]
    trace_segment(xO,yO,xJ,yJ,0.0,0.50,0.0,2.0);// on trace [OJ]
    trace_segment(xO,yO,xabs,yabs,0.5,0.5,0.5,2.0);// on trace l'abscisse -> redimensionner la fenêtre pour le bon affichages
    trace_segment(xO,yO,-xabs,yabs,0.5,0.5,0.5,2.0);// on trace l'abscisse
    trace_segment(xO,yO,xord,yord,0.5,0.5,0.5,2.0);// on trace l'ordonnée
    trace_segment(xO,yO,xord,-yord,0.5,0.5,0.5,2.0);// on trace l'ordonnée

    for(i=0;i<=1;i+=0.001){
      if(i==0){
        tab_tmp = pts_bezier(tab_poid,tab_coeff_num,i,degre);

        openGL(tab_tmp[0],tab_tmp[1],1.0,0.50,0.0,4.0);
        }
      else{
        tab_pts = pts_bezier(tab_poid,tab_coeff_num,i,degre);

        openGL(tab_pts[0],tab_pts[1],1.0,0.50,0.0,4.0);
        trace_segment(tab_tmp[0],tab_tmp[1],tab_pts[0],tab_pts[1],1.0,0.50,0.0,2.0);
        tab_tmp = tab_pts;

      }
    }


    for(int j=0;j<intervale;j++){
      for(i=0;i<=1;i+=0.001){
         tab_homographique=calcul_homo(nb_asymptote, i, tab_verticales, tab_poid, tab_coeff_num, degre);
        if(i==0){
          tab_tmp = tab_homographique[j];
        }
        else{
          tab_pts = tab_homographique[j];
          trace_segment(tab_tmp[0],tab_tmp[1],tab_pts[0],tab_pts[1],0.0,0.0,1.0,2.0);
          tab_tmp = tab_pts;
        }
      }
    }
  glEndList();

  glNewList(4,GL_COMPILE_AND_EXECUTE);  //liste numero 4

  glEndList();

  glNewList(5,GL_COMPILE_AND_EXECUTE);  //liste numero 5

  glEndList();
  glNewList(6,GL_COMPILE_AND_EXECUTE); //liste numero 6

  glEndList();

  cout<<"\n Voila, c'est fini"<<endl;
}

// fonction permettant d'afficher les objets en utilisant des listes
void affichage()
{
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0,0.0,dist);
  // Pour la 3D
 // glRotatef(-angley,1.0,0.0,0.0);
 //  glRotatef(-anglex,0.0,1.0,0.0);
 // Pour la 2D
  glRotatef(-anglex+angley,0.0,0.0,1.0);
  glScalef(Scal,Scal,Scal); // diminution de la vue de la scene
  glRotatef(180,0.0,1.0,0.0);
  glRotatef(180,1.0,0.0,0.0);
  glTranslatef(-trX,trY,0.);
      glCallList(1); // appel de la liste numero 1
      glCallList(2);   // appel de la liste numero 2
 glFlush();
  // On echange les buffers
  glutSwapBuffers();
}
