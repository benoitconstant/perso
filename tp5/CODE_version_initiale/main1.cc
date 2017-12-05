#include "TimeScheme.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
using namespace Eigen;
#include<ctime>

int main()
{
  double t0(0.), tfinal(30.0), dt(0.01); // temps initial, final, pas de temps
  int nb_iterations = int(ceil(tfinal/dt)); // Définition du nombre d'itérations
  dt = tfinal / nb_iterations; // Recalcul de dt
  string results; // nom du fichier résultat
  int userChoiceSys; // Choix de l'utilisateur
  VectorXd sol0, exactSol; // Condition initiale et Solution exacte
  cout << "------------------------------------" << endl;
  cout << "Choississez le système : " << endl;
  cout << "1) X' = X"<< endl;
  cout << "2) x' = -y et y' = x" << endl;
  cout << "3) x' = x^2 t" << endl;
  cout << "4) x'=x(a-by) et y'=y(cx-d)" << endl;
  cout << "5) pendule "<< endl;
  cin >> userChoiceSys;
  OdeSystem* sys(0);
  switch(userChoiceSys)
   {
   case 1:
     sys = new FirstExampleOdeSystem();
     sol0.resize(4);
     sol0(0) = 2.; sol0(1) = 3.1; sol0(2) = -5.1; sol0(3) = 0.1;

     exactSol = sol0*exp(tfinal);
     results = "first_ex";
     break;
   case 2:
     sys = new SecondExampleOdeSystem();
     sol0.resize(2); exactSol.resize(2); sol0(0) = 1; sol0(1) = -1;
     exactSol(0) = sol0(0)*cos(tfinal)-sol0(1)*sin(tfinal);
     exactSol(1) = sol0(1)*cos(tfinal)+sol0(0)*sin(tfinal);
     results = "second_ex";
     break;
   case 3:
     sys = new ThirdExampleOdeSystem();
     sol0.resize(1); exactSol.resize(1); sol0(0) = -2;
     exactSol(0) = 2.0*sol0(0)/(2.0-tfinal*tfinal*sol0(0));
     results = "third_ex";
     break;
   case 4:
      {
        double a=1;double b=2;double c=3;double d=4;
      sys= new LotkaVolterraOdeSystem(a,b,c,d);
      sol0.resize(2);
      //pour sol0(0)=d/c; sol0(1)=a/b; on obtient une solution constante :)
      sol0(0)=d/c; sol0(1)=a/b;
      results = "Lotka_ex";
    }
    break;
    case 5:
    {
      double m=0.1;double l=1;double k=0.1;
      sys= new PendulumOdeSystem(m,l,k);
      sol0.resize(2);
      sol0(0) = M_PI/5; sol0(1)=0;
      results="pendul_ex";
    }
    break;

    default:
     cout << "Ce choix n'est pas possible ! Veuillez recommencer !" << endl;
     exit(0);
    }



    cout << "------------------------------------" << endl;
    cout << "Choississez le schema en temps : " << endl;
    cout << "1) Euler"<< endl;
    cout << "2) RK3" << endl;
    cout << "3) RK4" << endl;
    cout << "4) Adbashforth" << endl;

    int userChoiceschema;
    cin >> userChoiceschema;
    TimeScheme* time_scheme;
    clock_t temps;
    string timee;
    switch(userChoiceschema)
    {
      case 1:
      {
        time_scheme= new  EulerScheme(*sys); // Objet de TimeScheme
        timee= "_euler.txt";
      }
      break;
      case 2:
        {
          time_scheme=new RungeKuttaScheme3(*sys);
          timee="_RK3.txt";
        }
        break;
      case 3:
      {
        time_scheme= new RungeKuttaScheme4(*sys);
        timee="_RK4.txt";
      }
        break;
      case 4:
      {
        time_scheme= new AdBashforthScheme3(*sys);

        timee="_Adbashforth.txt";
      }
      break;
      default:
       cout << "Ce choix n'est pas possible ! Veuillez recommencer !" << endl;
       exit(0);
    }

results=results+timee;


   time_scheme->Initialize(t0, dt, sol0, results); // Initialisation
   time_scheme->SaveSolution(); // Sauvegarde condition initiale
   for (int n = 0; n < nb_iterations; n++)
     { // Boucle en temps

        time_scheme->Advance();
        time_scheme->SaveSolution();
       }
       temps=clock();

   if ((userChoiceSys == 1) || (userChoiceSys == 2) || (userChoiceSys == 3))
     {
       VectorXd approxSol = time_scheme->GetIterateSolution(); // Itere au temps final
       double error = ((approxSol-exactSol).array().abs()).sum();
       cout << "Erreur = " << error<< " pour dt = " << dt << endl;

       time_scheme->Initialize(t0, dt/2., sol0, results);
       for (int n = 0; n < nb_iterations*2; n++)
          time_scheme->Advance();

       approxSol = time_scheme->GetIterateSolution(); // Itere au temps final
       double error2 = ((approxSol-exactSol).array().abs()).sum();
       cout << "Erreur = " << error2<< " pour dt = " << dt/2. << endl;
       cout << "Ordre de la méthode = " << log2(error/error2) << endl;
       //double res=
       std::cout << "le temps mis par la méthode " <<  timee << " est "<<(double) temps/CLOCKS_PER_SEC<< '\n';
    }
  return 0;
}
