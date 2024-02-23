#include <Object.hpp>
#include <Window.h>
#include <iostream>
#include <Vector3.h>


//this is suppose to be a hpp?
class Camera :public Object{

	Vector3 CameraPos = Vector3(0, 0, 3);
	Vector3 CameraTarget = Vector3(0, 0, 0);

	Vector3 CameraDirection = Vector3(0, 0, 0);

};

