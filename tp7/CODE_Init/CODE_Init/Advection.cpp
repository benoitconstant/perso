#ifndef FILE_ADVECTION_CPP

#include "Advection.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace Eigen;

double square(double x)
{
  return x*x;
}

// Constructeur
Advection::Advection(const DataFile& data, const Function& fct, const Mesh2D& mesh)
  : _function(fct), _mesh(mesh), _triangles(mesh.GetTriangles()), _edges(mesh.GetEdges()),
    _tri_center(mesh.GetTrianglesCenter()), _tri_area(mesh.GetTrianglesArea()),
    _edg_normal(mesh.GetEdgesNormal()), _edg_center(mesh.GetEdgesCenter())
{
  _results = data.Get_results();

  system(("mkdir -p ./" + data.Get_results()).c_str());
  system(("rm -f ./" + data.Get_results() + "/*.vtk").c_str());
  system(("cp ./" + data.Get_file_name() + " ./" + data.Get_results() + "/" + data.Get_file_name()).c_str());
  if (data.Get_numerical_flux_choice() == "centered")
    _type_flux = Centered;
  else
    _type_flux = Upwind;
}


// Construit le tableau contenant V pour tous les centres de triangle
void Advection::BuildVelocity(double t)
{


  int ii=_triangles.size();
  _V.resize(ii);
  for (int i=0; i< ii ;i++)
	{
		_V[i](0)=_function.Velocity_x(_tri_center[i][0],_tri_center[i][1],t);
		_V[i](1)=_function.Velocity_y(_tri_center[i][0],_tri_center[i][1],t);
	}
  // A FAIRE : remplir _V avec les vitesses pour chaque triangle
}


// Construit y = g(t, U)
void Advection::BuildF(const double& t, const Eigen::VectorXd& sol, Eigen::VectorXd& y)
{

  // on calcule v pour tous les triangles
    int nb_tri = _triangles.size();
    int nb_edges = _edges.size();
    int num1;
    int num2;
    double scale(0.);
    double scale2(0.);

    y.resize(nb_tri);

    for (int i = 0; i < nb_tri; i++) {
      y[i] = 0. ;
    }
    BuildVelocity(t);
    for (int i = 0; i < nb_edges; i++) {
       num1 = _edges[i].GetT1();
       num2 = _edges[i].GetT2();
       scale = _V[num1][0]*_edg_normal[i][0] + _V[num1][1]*_edg_normal[i][1];

       if (num2 == -1) {
         if (scale > 0.)
           y[num1] = y[num1] - scale * sol[num1];
       }
       else
       {
         scale2= _V[num2][0]*_edg_normal[i][0]+_V[num2][1]*_edg_normal[i][1];
         if (_type_flux == Centered) {
           double flux1 = (scale * sol(num1) + scale2 * sol(num2))/2.;
           y(num1) -= flux1 ;
           y(num2) += flux1 ;
         }
         if (_type_flux == Upwind) {
           double flux1(0.);
           if (scale > 0.)
             flux1 = scale * sol(num1);
           else
             flux1 = scale2 * sol(num2);

           y(num1) =y(num1)- flux1 ;
           y(num2) = y(num2)+flux1 ;
         }
       }
    }
    for (int i = 0; i < y.size(); i++) {
      y[i] = y[i]/_tri_area[i];
    }
  }


// Construit la condition initiale au centre des triangles
VectorXd Advection::InitialCondition()
{
  VectorXd sol0(_triangles.size());

  int ii=_triangles.size();
  for (int i=0; i<ii;i++)
  	{
  		sol0[i]=_function.InitialCondition(_tri_center[i](0),_tri_center[i](1));
  	}
  //  A FAIRE : calculer la condition initiale au centre des triangles

  return sol0;
}


// Solution exacte au centre des triangles
VectorXd Advection::ExactSolution(double t)
{
  VectorXd exact_sol(_triangles.size());
  int ii=_triangles.size();
  for (int i=0; i<ii;i++)
	{
		exact_sol[i]=_function.ExactSolution(_tri_center[i](0),_tri_center[i](1),t);
	}
  return exact_sol;
}


// Sauvegarde la solution
void Advection::SaveSol(const VectorXd& sol, int n)
{
  string name_file = _results + "/solution_" + std::to_string(n) + ".vtk";

  const vector<Matrix<double, 2, 1> >& vertices = _mesh.GetVertices();
  int nb_vert = vertices.size();

  assert((sol.size() == int(_triangles.size())) && "The size of the solution vector is not the same than the number of _triangles !");


  ofstream solution;
  solution.open(name_file, ios::out);
  solution.precision(7);

  if (!solution.is_open())
    {
      cout << "Unable to open file " << name_file << endl;
      abort();
    }

  solution << "# vtk DataFile Version 3.0 " << '\n';
  solution << "2D Unstructured Grid" << '\n';
  solution << "ASCII" << '\n';
  solution << "DATASET UNSTRUCTURED_GRID" << '\n';

  solution << "POINTS " << nb_vert << " float " << '\n';
  for (int i = 0 ; i < nb_vert ; ++i)
    solution << vertices[i][0] << " " << vertices[i][1] << " 0." << '\n';

  solution << '\n';

  int nb_tri = _triangles.size();
  solution << "CELLS " << nb_tri << " " << nb_tri*4 << '\n';
  for (int i = 0 ; i < nb_tri ; ++i)
    solution << 3 << " " << _triangles[i].GetTriangle()[0] << " " << _triangles[i].GetTriangle()[1]
	     << " " << _triangles[i].GetTriangle()[2] << '\n';

  solution << '\n';

  solution << "CELL_TYPES " << nb_tri << '\n';
  for (int i = 0 ; i < nb_tri ; ++i)
    solution << 5 << '\n';

  solution << '\n';

  solution << "CELL_DATA " << nb_tri << '\n';
  solution << "SCALARS sol float 1" << '\n';
  solution << "LOOKUP_TABLE default" << '\n';
  for (int i = 0 ; i < nb_tri ; ++i)
    solution << float(sol[i]) << '\n';

  solution << '\n';

  solution.close();
}

#define FILE_ADVECTION_CPP
#endif
