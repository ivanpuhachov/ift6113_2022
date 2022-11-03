#include <igl/eigs.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/read_triangle_mesh.h>
#include <igl/decimate.h>
#include <Eigen/Sparse>
#include <iostream>

Eigen::MatrixXd eigenvectors;
int selectedcolumn=0;

// This function is called every time a keyboard button is pressed
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
  std::cout<<"Key: "<<key<<" "<<(unsigned int)key<<std::endl;
  if (key == '1')
  {
    selectedcolumn = 1;
    viewer.data().set_data(eigenvectors.col(selectedcolumn));
  }
  else if (key == '2')
  {
    selectedcolumn = 2;
    viewer.data().set_data(eigenvectors.col(selectedcolumn));
  }
  else if (key == ' ')
  {
    selectedcolumn = (selectedcolumn + 1) % eigenvectors.cols();
    viewer.data().set_data(eigenvectors.col(selectedcolumn));
  }

  return false;
}

int main(int argc, char * argv[])
{
    Eigen::MatrixXd V, U;
    Eigen::MatrixXi F;
    if(!igl::read_triangle_mesh(
            argc>1?argv[1]: "../../input/bunny.obj",V,F))
    {
        std::cout<<"failed to load mesh"<<std::endl;
    }
    
    Eigen::SparseMatrix<double> L, M;
    igl::cotmatrix(V,F,L);
    L = (-L).eval();
    igl::massmatrix(V,F,igl::MASSMATRIX_TYPE_DEFAULT,M);
    
    Eigen::VectorXd D;
    const size_t k = 5;
    if(!eigs(L,M,k+1,igl::EIGS_TYPE_SM,U,D))
        {
            std::cout<<"failed."<<std::endl;
        }
    // Normalize
    U = ((U.array()-U.minCoeff())/(U.maxCoeff()-U.minCoeff())).eval();

    eigenvectors = U.block(0,0,U.rows(), 3);

    igl::opengl::glfw::Viewer viewer;
    igl::opengl::glfw::imgui::ImGuiPlugin plugin;
    viewer.plugins.push_back(&plugin);
    igl::opengl::glfw::imgui::ImGuiMenu menu;
    plugin.widgets.push_back(&menu);
    
    viewer.data().set_mesh(V,F);
    viewer.callback_key_down = &key_down; // setting the callback
    viewer.data().show_lines = true;
    viewer.launch();
}
