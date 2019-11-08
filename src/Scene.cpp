#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 


void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;


		 std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 0.5f, 0));

		std::vector<Vec3f> vVertexes;
		std::vector<Vec3f> nVertexes;
		std::vector<Vec2f> tVertexes;
		
		std::string line;

		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];

				vVertexes.emplace_back(v);
			}
			else if (line == "f") {

				int indices[3][3];

				std::stringstream v_vt_vn;
				std::string lookup;

				for(int i=0; i<3; i++) {

					ss >> lookup;
					v_vt_vn = std::stringstream(lookup);
					for(int j=0; j<3; j++) {
						getline(v_vt_vn, lookup, '/');
						indices[i][j] = stoi(lookup) - 1;
					}
				}

				// SMOOTH
				Add(std::make_shared<CPrimTriangleSmoothTextured>(
					vVertexes[indices[0][0]], vVertexes[indices[1][0]], vVertexes[indices[2][0]],
					nVertexes[indices[0][2]], nVertexes[indices[1][2]], nVertexes[indices[2][2]],
					tVertexes[indices[0][1]], tVertexes[indices[1][1]], tVertexes[indices[2][1]],
					pShader));

				// NOT SMOOTH
				 //Add(std::make_shared<CPrimTriangle>(
				 //	vVertexes[indices[0][0]], vVertexes[indices[1][0]], vVertexes[indices[2][0]],
				 //	pShader));

			}
			else if(line == "vt") 
			{

				Vec2f v;
				for(int i=0; i<2; i++) ss >> v.val[i];
				tVertexes.emplace_back(v);
			}
			else if(line == "vn") 
			{

				Vec3f v;
				for(int i=0; i < 3; i++) ss >> v.val[i];
				nVertexes.emplace_back(v);
			} 

			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	} else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}


