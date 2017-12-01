#ifndef FILE_ODE_SYSTEM_H

#include "Dense"
#include <fstream>

class OdeSystem
{
protected:
    // Écriture du fichier
    std::ofstream _file_out;

  public:
    // Constructeur par défaut
    OdeSystem();

    // Destructeur par défaut
    virtual ~OdeSystem();

    // Initialiser le nom du fichier solution
    void InitializeFileName(const std::string& file_name);

    // Sauvegarde la solution
    virtual void SaveSolution(const double t, const Eigen::VectorXd & sol);

    // Pour construire f en fonction de votre système
    virtual void BuildF(const double t, const Eigen::VectorXd & sol, Eigen::VectorXd& f)=0;

};

class FirstExampleOdeSystem : public OdeSystem
{
public:
  void BuildF(const double t, const Eigen::VectorXd & sol, Eigen::VectorXd& f);
};

class SecondExampleOdeSystem :public OdeSystem{
public:
  void BuildF(const double t, const Eigen::VectorXd & sol, Eigen::VectorXd& f);
};

class ThirdExampleOdeSystem :public OdeSystem{
public:
  void BuildF(const double t, const Eigen::VectorXd & sol, Eigen::VectorXd& f);
};

class LotkaVolterraOdeSystem:public OdeSystem
{
private:
  double _a;double _b; double _c;double _d;

public:
  LotkaVolterraOdeSystem(double a, double b, double c, double d);
  void BuildF(const double t, const Eigen::VectorXd & sol, Eigen::VectorXd& f);
};


class PendulumOdeSystem:public OdeSystem
{
private:
  double _l;double _m; double _k;

public:
  PendulumOdeSystem(double m, double l); // _k=0
  PendulumOdeSystem(double m, double l, double k);
  void BuildF(const double t, const Eigen::VectorXd & sol, Eigen::VectorXd& f);
  void SaveSolution(const double t, const Eigen::VectorXd & sol);
};


#define FILE_ODE_SYSTEM_H
#endif
