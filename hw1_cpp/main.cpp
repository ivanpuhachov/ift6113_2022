#include <igl/opengl/glfw/Viewer.h>
#include <igl/read_triangle_mesh.h>
#include "trimesh.h"

int main(int argc, char *argv[])
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::read_triangle_mesh("../../input/cube.obj", V,F);

    // half-edges example
    std::vector< trimesh::triangle_t > triangles;

    int kNumVertices = V.rows();
    int kNumFaces = F.rows();
    triangles.resize( kNumFaces );
    for (int i=0; i<kNumFaces; ++i){
        triangles[i].v[0] = F(i,0);
        triangles[i].v[1] = F(i,1);
        triangles[i].v[2] = F(i,2);
    }

    std::vector< trimesh::edge_t > edges;
    trimesh::unordered_edges_from_triangles( triangles.size(), &triangles[0], edges );

    trimesh::trimesh_t mesh;
    mesh.build( kNumVertices, triangles.size(), &triangles[0], edges.size(), &edges[0] );

    std::vector< trimesh::index_t > neighs;
    for( int vi = 0; vi < kNumVertices; ++vi )
    {
        mesh.vertex_vertex_neighbors( vi, neighs );

        std::cout << "neighbors of vertex " << vi << ": ";
        for( int i = 0; i < neighs.size(); ++i )
        {
            std::cout << ' ' << neighs.at(i);
        }
        std::cout << '\n';
    }
    std::vector< int > a = mesh.get_face_from_he_index(0);
    std::cout << a[0] << a[1] << a[2] << std::endl;
    Eigen::MatrixXi newF;
    newF = mesh.get_faces();
    std::cout<< "\n" << newF << "\n";
    // output the mesh
    igl::writeOBJ("../output/cube.obj", V, F);

    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, newF);
    viewer.data().set_face_based(true);
    const Eigen::RowVector3d red = Eigen::RowVector3d(1,0,0);
    // add vertices highlights
    viewer.data().point_size = 20;
    viewer.data().add_points(V, red);
    // add vertices index
    for (int i=0; i<V.rows(); ++i){
        viewer.data().add_label(V.row(i)+Eigen::RowVector3d(0.005, 0.005, 0),std::to_string(i));
    }
    viewer.data().show_custom_labels = true;
    // launch viewer
    viewer.launch();
}
