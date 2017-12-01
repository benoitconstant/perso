#ifndef FILE_ODE_SYSTEM_CPP

#include "OdeSystem.h"
#include <iostream>

using namespace Eigen;
using namespace std;

// Constructeur par défaut
OdeSystem::OdeSystem()
{}

// Destructeur par défaut
OdeSystem::~OdeSystem()
{
  _file_out.close();
}

// Initialisation du nom du fichier
void OdeSystem::InitializeFileName(const std::string& file_name)
{

  _file_out.open(file_name.data());
  if (!_file_out.is_open())
    {
      cout << "Impossible d'ouvrir le fichier " << file_name << endl;
      abort();
    }

  _file_out.precision(15);
}

// Construit le vecteur f(t, sol)
// arguments d'entree : t (temps), sol (vecteur x)
// arguments de sortie : f (evaluation de f(t, sol))
void FirstExampleOdeSystem::BuildF(const double t, const VectorXd & sol, VectorXd& f)
{
  f = sol; // f(t,X) = X pour résoudre X' = X
}

void SecondExampleOdeSystem::BuildF(const double t, const VectorXd & sol, VectorXd& f)
{
  f(0)=- sol(1);
  f(1)=sol(0);
}

void ThirdExampleOdeSystem::BuildF(const double t, const VectorXd & sol, VectorXd& f)
{
  f=t*sol*sol;

}
LotkaVolterraOdeSystem::LotkaVolterraOdeSystem(double a, double b, double c, double d)
{
  _a=a;
  _b=b;
  _c=c;
  _d=d;
}

void LotkaVolterraOdeSystem::BuildF(const double t, const VectorXd & sol, VectorXd& f)
{
  f(0)=sol(0)*(_a-_b*sol(1));
  f(1)=sol(1)*(_c*sol(0)-_d);
}



PendulumOdeSystem::PendulumOdeSystem(double m,double l)
{
  _m=m;
  _l=l;
  _k=0;
}

PendulumOdeSystem::PendulumOdeSystem(double m,double l,double k)
{
  _m=m;
  _l=l;
  _k=k;
}

void PendulumOdeSystem::BuildF(const double t, const VectorXd & sol, VectorXd& f)
{
  f(0)=sol(1);
  f(1)=-9.81/_l*sin(sol(0))- _k/(_m*_l*_l)*sol(1);
}


void PendulumOdeSystem::SaveSolution(const double t, const VectorXd & sol)
{
  // mettre 4 colonnes : t, teta, sin(teta), -cos(teta)
  _file_out <<t;
  _file_out << " "<< sol(0)<< " "<< sin(sol(0))<< " "<< -cos(sol(0))<<endl; // À compléter !

}

// Enregistre la solution
// Pour le moment : sol_1, sol_2 ...
void OdeSystem::SaveSolution(const double t, const VectorXd & sol)
{

  _file_out << t;
  for (int i = 0 ; i < sol.rows() ; ++i)
    {
      _file_out << " " << sol(i);

    }

_file_out << " "<< std::endl;
}
#define FILE_ODE_SYSTEM_CPP
#endif
