#ifndef FILE_TIME_SCHEME_CPP

#include "TimeScheme.h"
#include <iostream>

using namespace Eigen;
using namespace std;

/*************
* TimeScheme *
**************/


// Constructeur prenant en argument le system d'EDO
TimeScheme::TimeScheme(OdeSystem& sys) : _sys(sys)
{
}

// Destructeur
TimeScheme::~TimeScheme()
{
}

// Initialisation de vos différentes variables
void TimeScheme::Initialize(double t0, double dt, VectorXd & sol0, string results)
{
  _dt = dt;
  _t = t0 ;
  _sol = sol0;
  _f.resize(_sol.rows());
  // on ouvre un fichier que si le nom est non-nul
  if (results.size() > 0)
    _sys.InitializeFileName(results);
}


// Enregistre la solution : fait appel à OdeSystem car la solution
// que l'on souhaite sauvegarder peut être différente de _sol SaveSolution
// le système
void TimeScheme::SaveSolution()
{
  _sys.SaveSolution(_t, _sol);
}

// Renvoie _sol (pratique pour calculer l'ordre de votre méthode)
const VectorXd & TimeScheme::GetIterateSolution() const
{
  return _sol;
}

/***********
* EulerScheme *
***************/

EulerScheme::EulerScheme(OdeSystem& sys) : TimeScheme(sys)
{
}

// Schéma en temps par défaut : ici Euler Explicite
// Avancer d'un pas de temps
void EulerScheme::Advance()
{
  _sys.BuildF(_t, _sol, _f);
  _sol += _dt*_f;
  _t += _dt;
}
/*************
** RungeKuttaScheme3
*********/

RungeKuttaScheme3::RungeKuttaScheme3(OdeSystem& sys): TimeScheme(sys)
{
}

void RungeKuttaScheme3::Advance()
{
  VectorXd k1,k2,k3;
  _sys.BuildF( _t,_sol,_f);
  k1=_f;
  _sys.BuildF( _t+_dt/2,_sol+_dt/2*k1,_f);
  k2=_f;
  _sys.BuildF( _t+_dt, _sol+(-1)*_dt*k1+2*_dt*k2,_f);
  k3=_f;
  _sol =_sol+ _dt/6*(k1+4*k2+k3);
  _t += _dt;
}


/*************
** RungeKuttaScheme4
*********/

RungeKuttaScheme4::RungeKuttaScheme4(OdeSystem& sys): TimeScheme(sys)
{
}

void RungeKuttaScheme4::Advance()
{
  VectorXd k1,k2,k3,k4;
  _sys.BuildF( _t,_sol,_f);
  k1=_f;
  _sys.BuildF( _t+_dt/2,_sol+_dt/2*k1,_f);
  k2=_f;
  _sys.BuildF( _t+_dt/2, _sol+2*_dt*k2/2,_f);
  k3=_f;
  _sys.BuildF( _t+_dt, _sol+_dt*k3,_f);
  k4=_f;
  _sol =_sol+ _dt/6*(k1+2*k2+2*k3+k4);
  _t += _dt;
}


AdBashforthScheme3::AdBashforthScheme3(OdeSystem& sys): TimeScheme(sys)
{
}

void AdBashforthScheme3::Initialize(double t0, double dt, Eigen::VectorXd & sol0, std::string results)
{
  num_iter = 0;
  _dt = dt;
  _t = t0 ;
  _sol = sol0;
  _f.resize(_sol.rows());
  // on ouvre un fichier que si le nom est non-nul
  if (results.size() > 0)
    _sys.InitializeFileName(results);
}

void AdBashforthScheme3::Advance()
{

  VectorXd k1,k2,k3;
    if (num_iter < 2)
    {

      _sys.BuildF( _t,_sol,_f);
      k1=_f;

      _sys.BuildF( _t+_dt/2,_sol+_dt/2*k1,_f);
      k2=_f;
      _sys.BuildF( _t+_dt, _sol+(-1)*_dt*k1+2*_dt*k2,_f);
      k3=_f;
      _sol_2=_sol_1;
      _sol_1=_sol;
      _sol =_sol+ _dt/6*(k1+4*k2+k3);
      _t += _dt;
    }
    else
    {
  VectorXd k1,k2,k3,k4;
  _sys.BuildF( _t,_sol,_f);
  k1=_f;
  k2=_sol_1;
  k3=_sol_2;

  _sol_2=_sol_1;
  _sol_1=_sol;

  _sol =_sol+ _dt/12*(23*k1-16*k2+5*k3);
  _t += _dt;
}


num_iter++;
}
#define FILE_TIME_SCHEME_CPP
#endif
