
#include"../Mesh.h"
#include"../Model.h"

Model mod;

const unsigned int width = 1080;
const unsigned int height = 720;


std::vector<Vertex> VER_Goal;
std::vector<Texture> TEX_Goal;

std::vector<Vertex> VER_Plan;
std::vector<Texture> TEX_Plan;

std::vector<Vertex> VER_Lim1;
std::vector<Texture> TEX_Lim1;

std::vector<Vertex> VER_Player1;
std::vector<Texture> TEX_Player1;

std::vector<Vertex> VER_Player2;
std::vector<Texture> TEX_Player2;

std::vector<Vertex> VER_Ball;
std::vector<Texture> TEX_Ball;


Vertex lightVertices[] =
{ //     COORDINATES     //
	/// <summary> bottom
	Vertex{glm::vec3(-1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(-1.0f, 3.0f, 1.0f)},
	Vertex{glm::vec3(1.0f,  3.0f, -1.0f)},

	Vertex{glm::vec3(-1.0f,  3.0f,  1.0f)},
	Vertex{glm::vec3(1.0f,  3.0f, -1.0f)},
	Vertex{glm::vec3(1.0f,  3.0f,  1.0f)},
	/// </summary>
	

	/// <summary> top
	Vertex{glm::vec3(-1.0f, 4.0f,  -1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, 1.0f)},
	Vertex{glm::vec3(1.0f,  4.0f, -1.0f)},

	Vertex{glm::vec3(-1.0f,  4.0f,  1.0f)},
	Vertex{glm::vec3(1.0f,  4.0f, -1.0f)},
	Vertex{glm::vec3(1.0f,  4.0f,  1.0f)},
	/// </summary>
	
	/// <summary> Left
	Vertex{glm::vec3(-1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(-1.0f, 3.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, 1.0f)},

	Vertex{glm::vec3(-1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, -1.0f)},
	/// </summary>
	
	/// <summary> Right
	Vertex{glm::vec3(1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(1.0f, 3.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 4.0f, -1.0f)},

	Vertex{glm::vec3(1.0f, 3.0f,  1.0f)},
	Vertex{glm::vec3(1.0f, 4.0f, -1.0f)},
	Vertex{glm::vec3(1.0f, 4.0f, 1.0f)},
	/// </summary>

	/// <summary> Front
	Vertex{glm::vec3(-1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(1.0f, 3.0f, -1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, -1.0f)},

	Vertex{glm::vec3(1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, -1.0f)},
	Vertex{glm::vec3(1.0f, 4.0f, -1.0f)},
	/// </summary>

	/// <summary> Beck
	Vertex{glm::vec3(-1.0f, 3.0f,  1.0f)},
	Vertex{glm::vec3(1.0f, 3.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, 1.0f)},

	Vertex{glm::vec3(1.0f, 3.0f,  -1.0f)},
	Vertex{glm::vec3(-1.0f, 4.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 4.0f, 1.0f)},
	/// </summary>

};


float minVert(std::vector<Vertex> VER, int j) {

	float min = VER.at(0).position[j];

	for (int i = 0; i < VER.size(); i++)
	{
		if (min > VER.at(i).position[j]) {
			min = VER.at(i).position[j];
		}


	}
	return  min;

}
float maxVert(std::vector<Vertex> VER, int j) {

	float max = VER.at(0).position[j];

	for (int i = 0; i < VER.size(); i++)
	{
		if (max < VER.at(i).position[j]) {
			max = VER.at(i).position[j];
		}


	}
	return  max;

}
bool ballCollusionUp(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMinX <= BvertMaxX && AvertMaxX >= BvertMinX);
		
}

bool collusion(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMinY = minVert(VER1, 1);
	float AvertMinZ = minVert(VER1, 2);

	float AvertMaxX = maxVert(VER1, 0);
	float AvertMaxY = maxVert(VER1, 1);
	float AvertMaxZ = maxVert(VER1, 2);

	float BvertMinX = minVert(VER2, 0);
	float BvertMinY = minVert(VER2, 1);
	float BvertMinZ = minVert(VER2, 2);

	float BvertMaxX = maxVert(VER2, 0);
	float BvertMaxY = maxVert(VER2, 1);
	float BvertMaxZ = maxVert(VER2, 2);



	return (AvertMinX + 0.1 <= BvertMaxX && AvertMaxX >= BvertMinX)
		&& (AvertMinY + 0.1 <= BvertMaxY && AvertMaxY >= BvertMinY)
		&& (AvertMinZ + 0.1 <= BvertMaxZ && AvertMaxZ >= BvertMinZ);
}
bool collusionXPlayer1(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMinX <= BvertMaxX && AvertMaxX >= BvertMinX);
}
bool collusionXupPlayer1(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMaxX-0.5 >= BvertMinX);

}
bool collusionXdownPlayer1(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMinX+0.5 <= BvertMaxX );
	
}

bool collusionXPlayer2(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMinX <= BvertMaxX && AvertMaxX >= BvertMinX);

}
bool collusionXupPlayer2(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMaxX - 0.5 >= BvertMinX);

}
bool collusionXdownPlayer2(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinX = minVert(VER1, 0);
	float AvertMaxX = maxVert(VER1, 0);
	float BvertMinX = minVert(VER2, 0);
	float BvertMaxX = maxVert(VER2, 0);

	return (AvertMinX + 0.5 <= BvertMaxX);
	
}

bool collusionZPlayer1(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinZ = minVert(VER1, 2);
	float AvertMaxZ = maxVert(VER1, 2);
	float BvertMinZ = minVert(VER2, 2);
	float BvertMaxZ = maxVert(VER2, 2);

	return (AvertMinZ <= BvertMaxZ && AvertMaxZ >= BvertMinZ);
}
bool collusionZleftPlayer1(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinZ = minVert(VER1, 2);
	float AvertMaxZ = maxVert(VER1, 2);
	float BvertMinZ = minVert(VER2, 2);
	float BvertMaxZ = maxVert(VER2, 2);

	return (AvertMinZ+5.8 <= BvertMaxZ);
}
bool collusionZrightPlayer1(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinZ = minVert(VER1, 2);
	float AvertMaxZ = maxVert(VER1, 2);
	float BvertMinZ = minVert(VER2, 2);
	float BvertMaxZ = maxVert(VER2, 2);

	return ( AvertMaxZ-0.4 >= BvertMinZ);
}
bool collusionZPlayer2(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinZ = minVert(VER1, 2);
	float AvertMaxZ = maxVert(VER1, 2);
	float BvertMinZ = minVert(VER2, 2);
	float BvertMaxZ = maxVert(VER2, 2);

	return (AvertMinZ <= BvertMaxZ && AvertMaxZ >= BvertMinZ);
}
bool collusionZleftPlayer2(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinZ = minVert(VER1, 2);
	float AvertMaxZ = maxVert(VER1, 2);
	float BvertMinZ = minVert(VER2, 2);
	float BvertMaxZ = maxVert(VER2, 2);

	return (AvertMinZ +0.4 <= BvertMaxZ);
}
bool collusionZrightPlayer2(std::vector<Vertex> VER1, std::vector<Vertex> VER2) {

	float AvertMinZ = minVert(VER1, 2);
	float AvertMaxZ = maxVert(VER1, 2);
	float BvertMinZ = minVert(VER2, 2);
	float BvertMaxZ = maxVert(VER2, 2);

	return (AvertMaxZ - 5.4 >= BvertMinZ);
}
bool C_UP = false;
bool C_RIGHT = false;
bool C_DOWN = false;
bool C_LEFT = false;
bool Dir_Right = true;
bool Dir_UP = true;
bool Dir_Left = false;
bool Dir_Down= false;
std::tuple< std::vector<Vertex>, bool,bool,bool,bool,bool,bool,bool,bool> controleBall(GLFWwindow* window,bool CUP, bool CRIGHT, bool CDOWN, bool CLEFT,bool DIRRIGHT,bool DIRUP,bool DIRLEFT,bool DIRDOWN, std::vector<Vertex> VER, std::vector<Vertex> VER2, std::vector<Vertex> VER3, std::vector<Vertex> VER4, std::vector <Texture> tex2) {
	
	if (!collusionXupPlayer1(VER, VER2) && DIRRIGHT==true && DIRLEFT == false) {
		 CUP = true;
		 CRIGHT = false;
		 CDOWN = false;
		 CLEFT = false;
		 //////
		 DIRUP = false;
		 DIRRIGHT = true;
		 DIRLEFT = false;
		 DIRDOWN = true;
	}
	if (!collusionXupPlayer1(VER, VER2) && DIRRIGHT == false && DIRLEFT == true) {
		CUP = true;
		CRIGHT = false;
		CDOWN = false;
		CLEFT = false;
		//////
		DIRUP = false;
		DIRRIGHT = false;
		DIRLEFT = true;
		DIRDOWN = true;
	}
	/////////////////////////////////////////////////////////
	if (!collusionZrightPlayer1(VER, VER2) && DIRUP == false && DIRDOWN == true) {
		CUP = false;
		CRIGHT = true;
		CDOWN = false;
		CLEFT = false;
		/////
		DIRUP = false;
		DIRRIGHT = false;
		DIRLEFT = true;
		DIRDOWN = true;

	}
	if (!collusionZrightPlayer1(VER, VER2) && DIRUP == true && DIRDOWN == false) {
		CUP = false;
		CRIGHT = true;
		CDOWN = false;
		CLEFT = false;
		/////
		DIRUP = true;
		DIRRIGHT = false;
		DIRLEFT = true;
		DIRDOWN = false;

	}
	///////////////////////////////////////////////////
	if (!collusionXdownPlayer1(VER, VER2) && DIRRIGHT == false && DIRLEFT == true) {
		CUP = false;
		CRIGHT = false;
		CDOWN = true;
		CLEFT = false;
		///////
		DIRRIGHT = false;
		DIRUP = true;
		DIRLEFT = true;
		DIRDOWN = false;
	}
	if (!collusionXdownPlayer1(VER, VER2) && DIRRIGHT == true && DIRLEFT == false) {
		CUP = false;
		CRIGHT = false;
		CDOWN = true;
		CLEFT = false;
		///////
		DIRRIGHT = true;
		DIRUP = true;
		DIRLEFT = false;
		DIRDOWN = false;
	}
	////////////////////////////////////////////////
	if (!collusionZleftPlayer2(VER, VER2) && DIRUP == false && DIRDOWN == true) {
		CUP = false;
		CRIGHT = false;
		CDOWN = false;
		CLEFT = true;
		//////
		DIRRIGHT = true;
		DIRUP = false;
		DIRLEFT = false;
		DIRDOWN = true;
	}
	if (!collusionZleftPlayer2(VER, VER2) && DIRUP == true && DIRDOWN == false) {
		CUP = false;
		CRIGHT = false;
		CDOWN = false;
		CLEFT = true;
		/////////
		DIRRIGHT = true;
		DIRUP = true;
		DIRLEFT = false;
		DIRDOWN = false;
	}
	/////////////////////////////////////////////// 1
	if ( CUP == true && DIRRIGHT == true && DIRUP== false && DIRLEFT==false && DIRDOWN==true) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] -= 0.3;
			}
			CUP = false;
			CRIGHT = false;
			CDOWN = true;
			CLEFT = false;
			//////
			DIRRIGHT = true;
			DIRUP = true;
			DIRLEFT = false;
			DIRDOWN = false;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] += 0.1;
				VER.at(i).position[2] -= 0.05;
			}
			DIRUP = false;
			DIRRIGHT = true;
			DIRLEFT = false;
			DIRDOWN = true;
		}
	}
	///////////////////////////////////////2
	if (CUP == true && DIRRIGHT == false && DIRUP==false && DIRLEFT == true && DIRDOWN == true) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] -= 0.3;
			}
			CUP = false;
			CRIGHT = false;
			CDOWN = true;
			CLEFT = false;
			////////////
			DIRRIGHT = false;
			DIRUP = true;
			DIRLEFT = true;
			DIRDOWN = false;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] += 0.1;
				VER.at(i).position[2] += 0.05;
			}
			DIRUP = false;
			DIRRIGHT = false;
			DIRLEFT = true;
			DIRDOWN = true;
		}
	}
	////////////////////////////////////////////////// 3
	if (CRIGHT == true && DIRUP == true && DIRRIGHT== false && DIRLEFT == true && DIRDOWN == false) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[2] -= 0.3;
			}
			CUP = false;
			CRIGHT = false;
			CDOWN = false;
			CLEFT = true;
			/////////
			DIRRIGHT = true;
			DIRUP = true;
			DIRLEFT = false;
			DIRDOWN = false;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] -= 0.1;
				VER.at(i).position[2] += 0.05;
			}
			DIRUP = true;
			DIRRIGHT = false;
			DIRLEFT = true;
			DIRDOWN = false;
		}
	}
	///////////////////////////////////////////////////////4
	if (CRIGHT == true && DIRUP == false && DIRRIGHT == false && DIRLEFT == true && DIRDOWN == true) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[2] -= 0.3;
			}
			CUP = false;
			CRIGHT = false;
			CDOWN = false;
			CLEFT = true;
			//////
			DIRRIGHT = true;
			DIRUP = false;
			DIRLEFT = false;
			DIRDOWN = true;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] += 0.1;
				VER.at(i).position[2] += 0.05;
			}
			DIRUP = false;
			DIRRIGHT = false;
			DIRLEFT = true;
			DIRDOWN = true;
		}
	}
	////////////////////////////////////////////// 5
	if (CDOWN == true && DIRRIGHT == true && DIRUP == true  && DIRLEFT == false && DIRDOWN == false) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] += 0.3;
			}
			CUP = true;
			CRIGHT = false;
			CDOWN = false;
			CLEFT = false;
			//////
			DIRUP = false;
			DIRRIGHT = true;
			DIRLEFT = false;
			DIRDOWN = true;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] -= 0.1;
				VER.at(i).position[2] -= 0.05;
			}
			DIRRIGHT == true;
			DIRUP = true;
			DIRLEFT = false;
			DIRDOWN = false;
		}
	}
	////////////////////////////////////////// 6
	if (CDOWN == true && DIRRIGHT == false && DIRUP == true && DIRLEFT == true && DIRDOWN == false) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] += 0.3;
			}
			CUP = true;
			CRIGHT = false;
			CDOWN = false;
			CLEFT = false;
			//////
			DIRUP = false;
			DIRRIGHT = false;
			DIRLEFT = true;
			DIRDOWN = true;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] -= 0.1;
				VER.at(i).position[2] += 0.05;
			}
			DIRRIGHT == false;
			DIRUP = true;
			DIRLEFT = true;
			DIRDOWN = false;
		}
	}
	/////////////////////////////////////////////////// 7
	if (CLEFT == true && DIRUP == true && DIRRIGHT == true && DIRLEFT == false && DIRDOWN == false) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[2] += 0.3;
			}
			CUP = false;
			CRIGHT = true;
			CDOWN = false;
			CLEFT = false;
			/////
			DIRUP = true;
			DIRRIGHT = false;
			DIRLEFT = true;
			DIRDOWN = false;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] -= 0.1;
				VER.at(i).position[2] -= 0.05;
			}
			////////
			DIRRIGHT == true;
			DIRUP = true;
			DIRLEFT = false;
			DIRDOWN = false;
		}
	}
	///////////////////////////////////////////////////////// 8
	if (CLEFT == true && DIRUP == false && DIRRIGHT == true && DIRLEFT == false && DIRDOWN == true) {
		if (collusion(VER, VER3) || collusion(VER, VER4)) {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[2] += 0.3;
			}
			CUP = false;
			CRIGHT = true;
			CDOWN = false;
			CLEFT = false;
			/////
			DIRUP = false;
			DIRRIGHT = false;
			DIRLEFT = true;
			DIRDOWN = true;
		}
		else {
			for (int i = 0; i < VER.size(); i++)
			{
				VER.at(i).position[0] += 0.1;
				VER.at(i).position[2] -= 0.05;
			}
			////////////////
			DIRRIGHT == true;
			DIRUP = false;
			DIRLEFT = false;
			DIRDOWN = true;
		}
	}

	if(CUP==false && CRIGHT== false && CDOWN==false && CLEFT == false) {
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[0] -= 0.1;
			VER.at(i).position[2] -= 0.05;
		}
	}
	
	return  std::make_tuple(VER, CUP,CRIGHT,CDOWN,CLEFT,DIRRIGHT,DIRUP,DIRLEFT,DIRDOWN);
}

Mesh updateBall(GLFWwindow* window, Mesh BALL, std::vector<Vertex> VER, std::vector <Texture> tex2) {
	
	Mesh BALL1(VER, tex2);
	return BALL1;
}
std::vector<Vertex> controleObj1(GLFWwindow* window, std::vector<Vertex> VER, std::vector<Vertex> VER2 , std::vector <Texture> tex2, float speed) {
	
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && collusionXupPlayer1(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[0] -= speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && collusionZleftPlayer1(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[2] += speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && collusionXdownPlayer1(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[0] += speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && collusionZrightPlayer1(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[2] -= speed;
		}
	}
	return VER;
}
std::vector<Vertex> controleObj2(GLFWwindow* window, std::vector<Vertex> VER, std::vector<Vertex> VER2, std::vector <Texture> tex2, float speed) {

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && collusionXupPlayer2(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[0] -= speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && collusionZleftPlayer2(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[2] += speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && collusionXdownPlayer2(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[0] += speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && collusionZrightPlayer2(VER, VER2))
	{
		for (int i = 0; i < VER.size(); i++)
		{
			VER.at(i).position[2] -= speed;
		}
	}
	return VER;
}


Mesh updatePlayer1(GLFWwindow* window,Mesh PLAYER,std::vector<Vertex> VER, std::vector <Texture> tex2) {
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		Mesh PLAYER1(VER, tex2);
		return PLAYER1;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		Mesh PLAYER1(VER, tex2);
		return PLAYER1;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		Mesh PLAYER1(VER, tex2);
		return PLAYER1;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		Mesh PLAYER1(VER, tex2);
		return PLAYER1;
	}
	return PLAYER;
}

Mesh updatePlayer2(GLFWwindow* window, Mesh PLAYER, std::vector<Vertex> VER, std::vector <Texture> tex2) {
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		Mesh PLAYER2(VER, tex2);
		return PLAYER2;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		Mesh PLAYER2(VER, tex2);
		return PLAYER2;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		Mesh PLAYER2(VER, tex2);
		return PLAYER2;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		Mesh PLAYER2(VER, tex2);
		return PLAYER2;
	}
	return PLAYER;
}





int main(int argc, char* argv[]) {
	
	VER_Player1 = mod.load("models/player1.obj", VER_Player1);
	VER_Player2 = mod.load("models/player2.obj", VER_Player2);
	VER_Goal =  mod.load("models/GoalLeft.obj", VER_Goal);
	VER_Plan = mod.load("models/plan.obj", VER_Plan);
	VER_Lim1 = mod.load("models/limites1.obj", VER_Lim1);
	VER_Ball = mod.load("models/Ball.obj", VER_Ball);
	
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Air Hockey", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	Texture textures1[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Texture textures2[]
	{
		Texture("brick.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
		
	};
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Store mesh data in vectors for the mesh
	//std::vector <Vertex> verts = vertices;
	std::vector <Texture> tex1(textures1, textures1 + sizeof(textures1) / sizeof(Texture));
	std::vector <Texture> tex2(textures2, textures2 + sizeof(textures2) / sizeof(Texture));
	// Create floor mesh
	Mesh GOAL(VER_Goal, tex1);
	Mesh PLAN(VER_Plan, tex1);
	Mesh PLAYER1(VER_Player1, tex2);
	Mesh PLAYER2(VER_Player2, tex2);
	Mesh LIM1(VER_Lim1, tex1);
	Mesh BALL(VER_Ball, tex2);
	
	
	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	// Crate light mesh
	Mesh light(lightVerts, tex1);


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(15.0f, 5.0f, 0.0f));
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);

		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		VER_Player1  = controleObj1(window, VER_Player1,VER_Lim1, tex2, 0.3);
		PLAYER1 = updatePlayer1(window,PLAYER1 , VER_Player1, tex2);

		VER_Player2 = controleObj2(window, VER_Player2,VER_Lim1, tex2, 0.3);
		PLAYER2 = updatePlayer2(window, PLAYER2, VER_Player2, tex2);

		tie(VER_Ball, C_UP,C_RIGHT,C_DOWN,C_LEFT,Dir_Right,Dir_UP,Dir_Left,Dir_Down) = controleBall(window, C_UP,C_RIGHT,C_DOWN,C_LEFT,Dir_Right,Dir_UP,Dir_Left,Dir_Down, VER_Ball, VER_Lim1,VER_Player1,VER_Player2, tex2);
		
		BALL = updateBall(window, BALL, VER_Ball, tex2);

		
		// Draws different meshes
		light.Draw(lightShader, camera);
		GOAL.Draw(shaderProgram, camera);
		PLAN.Draw(shaderProgram, camera);
		PLAYER1.Draw(shaderProgram, camera);
		PLAYER2.Draw(shaderProgram, camera);
		LIM1.Draw(shaderProgram, camera);
		BALL.Draw(shaderProgram, camera);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	
	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}