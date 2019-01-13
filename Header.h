#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4

struct point
{
	float x;
	float y;
	float z;
};

struct face
{
	int vtx[3];
};


struct model
{
	int vertices;
	point obj_points[9122];
	point obj_pointsnormal[9124];
	face obj_faces[18240];
	int faces;
};



//-------- Functions --------------------------------

void ReadFile(model*);
//Function for reading a model file
void DisplayModel(model);
// Function for displaying a model

void MenuSelect(int choice);
void asteroid();