#ifndef MODEL_H
#define MODEL_H

#include <math.h>
#include <time.h>



#include <fstream>
#include <map>
#include <vector>
#include <glad/glad.h>
#include <string>
#include <gl/GL.h>
#include "VBO.h"
#include "Texture.h"
#include "Mesh.h"

#include <tuple>



class Model {
private:
    static int count_char(std::string& str, char ch) {
        int c = 0;
        int length = str.length() - 1;
        for (int i = 0; i < length; i++) {
            if (str[i] == ch)
                c++;
        }
        return c;
    }

    static bool has_double_slash(std::string& str) {
        int length = str.length() - 2;
        for (int i = 0; i < length; i++) {
            if (str[i] == '/' && str[i + 1] == '/')
                return true;
        }
        return false;
    }
    class Face {
    public:
        int edge;
        int* vertices;
        int* texcoords;
        int normal;

        Face(int edge, int* vertices, int* texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };

    

    void add_face_3v(std::string& line) {
        int v0, v1, v2;
        sscanf_s(line.c_str(), "f %d %d %d", &v0, &v1, &v2);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        faces.push_back(Face(3, v, NULL));
    }

    void add_face_3vt(std::string& line) {
        int v0, v1, v2, t0, t1, t2;
        sscanf_s(line.c_str(), "f %d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        int* t = new int[3]{ t0 - 1, t1 - 1, t2 - 1 };
        faces.push_back(Face(3, v, t));
    }

    void add_face_3vn(std::string& line) {
        int v0, v1, v2, n;
        sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d", &v0, &n, &v1, &n, &v2, &n);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        faces.push_back(Face(3, v, NULL, n - 1));
    }

    void add_face_3vtn(std::string& line) {
        int v0, v1, v2, t0, t1, t2, n;
        sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        int* t = new int[3]{ t0 - 1, t1 - 1, t2 - 1 };
       /* indices.push_back((GLint)(v0 - 1));
        indices.push_back((GLint)(v1 - 1));
        indices.push_back((GLint)(v2 - 1));*/
        faces.push_back(Face(3, v, t, n - 1));
    }

    void add_face_4v(std::string& line) {
        int v0, v1, v2, v3;
        sscanf_s(line.c_str(), "f %d %d %d %d", &v0, &v1, &v2, &v3);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        faces.push_back(Face(4, v, NULL));
    }

    void add_face_4vt(std::string& line) {
        int v0, v1, v2, v3, t0, t1, t2, t3;
        sscanf_s(line.c_str(), "f %d/%d %d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2, &v3, &t3);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        int* t = new int[4]{ t0 - 1, t1 - 1, t2 - 1, t3 - 1 };
        faces.push_back(Face(4, v, t));
    }

    void add_face_4vn(std::string& line) {
        int v0, v1, v2, v3, n;
        sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v0, &n, &v1, &n, &v2, &n, &v3, &n);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        faces.push_back(Face(4, v, NULL, n - 1));
    }

    void add_face_4vtn(std::string& line) {
        int v0, v1, v2, v3, t0, t1, t2, t3, n;
        sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n, &v3,
            &t3, &n);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        int* t = new int[4]{ t0 - 1, t1 - 1, t2 - 1, t3 - 1 };
        faces.push_back(Face(4, v, t, n - 1));
    }

public:
    std::vector<float*> vertices;
    std::vector<float*> texcoords;
    std::vector<float*> normals;
    std::vector<Face> faces;

    
    
    
    
    /*std::tuple<int, int> divide(int dividend, int divisor) {
        return  std::make_tuple(dividend / divisor, dividend % divisor);
    }*/
  
    std::vector<Vertex>  load(const char* filename, std::vector<Vertex> Vert) {

        std::string line;
        std::vector<std::string> lines;
        std::ifstream in(filename);
        if (!in.is_open()) {
            printf("Cannot load model %s\n", filename);
            return  Vert;
        }

        while (!in.eof()) {
            std::getline(in, line);
            lines.push_back(line);
        }
        in.close();

        float a, b, c;

        

        for (std::string& line : lines) {
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    sscanf_s(line.c_str(), "v %f %f %f", &a, &b, &c);
                    vertices.push_back(new float[3]{ a, b, c });
                }
                else if (line[1] == 't') {
                    sscanf_s(line.c_str(), "vt %f %f", &a, &b);
                    texcoords.push_back(new float[2]{ a, b });
                }
                else {
                    sscanf_s(line.c_str(), "vn %f %f %f", &a, &b, &c);
                    normals.push_back(new float[3]{ a, b, c });
                }
            }
            else if (line[0] == 'f') {
                int edge = count_char(line, ' ');
                int count_slash = count_char(line, '/');
                if (count_slash == 0) {
                    if (edge == 3)
                        add_face_3v(line);
                    else
                        add_face_4v(line);
                }
                else if (count_slash == edge) {
                    if (edge == 3)
                        add_face_3vt(line);
                    else
                        add_face_4vt(line);
                }
                else if (count_slash == edge * 2) {
                    if (has_double_slash(line)) {
                        if (edge == 3)
                            add_face_3vn(line);
                        else
                            add_face_4vn(line);
                    }
                    else {
                        if (edge == 3)
                            add_face_3vtn(line);
                        else
                            add_face_4vtn(line);
                    }
                }
            }
           
           
        }

     
        for (int i=0 ;i<faces.size();i++ )
        {
            for (int j = 0; j < 3; j++) {
                glm::vec3 p(vertices.at(faces.at(i).vertices[j])[0], vertices.at(faces.at(i).vertices[j])[1], vertices.at(faces.at(i).vertices[j])[2]);
                glm::vec3 n(normals.at(faces.at(i).normal)[0], normals.at(faces.at(i).normal)[0], normals.at(faces.at(i).normal)[0]);
                glm::vec2 t(texcoords.at(faces.at(i).texcoords[j])[0], texcoords.at(faces.at(i).texcoords[j])[1]);
                Vert.push_back(Vertex{ p,glm::vec3(1.0f, 1.0f, 1.0f),n, t });
            }
        }
 

        for (float* f : vertices)
            delete f;
        vertices.clear();
        for (float* f : texcoords)
            delete f;
        texcoords.clear();
        for (float* f : normals)
            delete f;
        normals.clear();
        faces.clear();
        
        return  Vert;
        
        
    }
   

};

#endif
