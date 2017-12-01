#include "TimeScheme.h"
#include <string>
#include <iostream>
using namespace std;
using namespace Eigen;

int main()
{
  // Définition du temps initial, du temps final et du pas de temps
  double t0(0.), tfinal(1.), dt(0.01);

  // Définition du nombre d'itérations à partir du temps final et du pas de temps
  int nb_iterations = int(ceil(tfinal/dt));

  // Recalcul de dt
  dt = tfinal / nb_iterations;

  // Nom du fichier solution
  string results = "solution.txt";

  // Définition du vecteur initial (vecteur de Eigen)
  // Ici dans R^4
  VectorXd sol0(1);

  // Initialisation des valeurs
  sol0(0) = 2.;


  // Définition d'un pointeur de OdeSystem
  OdeSystem* sys = new ThirdExampleOdeSystem();

  // Définition d'un objet de TimeScheme
  TimeScheme time_scheme(*sys);

  cout << "------------------------------------" << endl;
  cout << "Euler Explicite" << endl;
  cout << "------------------------------------" << endl;
  cout << "Système : X' = X avec X0 = " << endl;
  cout << sol0 << endl;
  cout << "------------------------------------" << endl;

  // Initialisation
  time_scheme.Initialize(t0, dt, sol0, results);

  // On sauvegarde la solution
  time_scheme.SaveSolution();

  // Boucle en temps
  for (int n = 0; n < nb_iterations; n++)
    {
      time_scheme.Advance();
      time_scheme.SaveSolution();
    }

  // a decommenter
  /*
  // On récupère la solution approchée au temps final
  VectorXd approxSol = time_scheme.GetIterateSolution();

  // Définition de la solution exacte au temps final
  VectorXd exactSol = sol0*exp(tfinal);
  double error = ((approxSol-exactSol).array().abs()).sum();
  cout << "Erreur = " << error << " pour dt = " << dt << endl;
  cout << "------------------------------------" << endl;


  time_scheme.Initialize(t0, dt/2., sol0, results);
  for (int n = 0; n < nb_iterations*2; n++)
    {
      time_scheme.Advance();
    }

  // On récupère la solution approchée au temps final
  approxSol = time_scheme.GetIterateSolution();
  double error2 = ((approxSol-exactSol).array().abs()).sum();
  cout << "Erreur = " << error2<< " pour dt = " << dt/2. << endl;
  cout << "------------------------------------" << endl;

  cout << "Ordre de la méthode = " << log2(error/error2) << endl;
  cout << "------------------------------------" << endl;
  */

  // on supprime le pointeur cree
  delete sys;

  return 0;
}
