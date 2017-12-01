#ifndef FILE_TIME_SCHEME_H

#include "OdeSystem.h"

class TimeScheme
{
protected:
  // Pas de temps
  double _dt;

  // Temps en cours
  double _t;

  // Vecteur solution
  Eigen::VectorXd _sol;

  // evaluation de f
  Eigen::VectorXd _f;


  // Reference vers le système d'EDO
  OdeSystem& _sys;

 public:
  // Constructeur avec le system d'EDO
  TimeScheme(OdeSystem&);

  // Destructeur
  ~TimeScheme();

  // Initialisation de vos différentes variables
  virtual void Initialize(double t0, double dt, Eigen::VectorXd & sol0, std::string name_file);

  // Enregistre la solution un fichier
  void SaveSolution();

  // Une étape du schéma en temps
  virtual void Advance()=0;

  // Permet de récupérer _sol
  const Eigen::VectorXd & GetIterateSolution() const;

};

class EulerScheme:public TimeScheme
{
public:
  EulerScheme(OdeSystem&);
  void Advance();
};

class RungeKuttaScheme3:public TimeScheme
{
public:
  RungeKuttaScheme3(OdeSystem&);
  void Advance();
};

class RungeKuttaScheme4:public TimeScheme
{
public:
  RungeKuttaScheme4(OdeSystem&);
  void Advance();
};

class AdBashforthScheme3:public TimeScheme
{
  int num_iter;
  Eigen::VectorXd _sol_1;
  Eigen::VectorXd _sol_2;

public:
    AdBashforthScheme3(OdeSystem&);
    void Initialize(double t0, double dt, Eigen::VectorXd & sol0, std::string name_file);
    void Advance();
};

#define FILE_TIME_SCHEME_H
#endif
