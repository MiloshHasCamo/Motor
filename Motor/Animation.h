#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Texture.h"
#include <iostream>
#include "Vertex.h"
#include "FileUtillities.h"
#include "OpenGLUtils.h"

using namespace std;

namespace Animation
{
	class Animation
	{
	protected:
		unsigned int index;
		Log* log;
	
	public:
		Animation ( );
		virtual ~Animation ( );

		void operator++ ( void );
	};

class Animation2D: public Animation
			 {
			 protected:
				 Texture** frames;
				 Entity* FramesEntity;
				 long int frameCounter;

			 public:
				 Animation2D ( string files [ ], Vectorf::Vector2f pos, Vectorf::Vector2f dim );
				 Animation2D ( string files [ ], float x, float y, int width, int height );
				 virtual ~Animation2D ( );

				 void Render (  );
			 };
	
class Animation3D: public Animation
			 {
			 private:
				 unsigned int* DisplayIDs;
				 Vectorf::Vector3f* pos;
				 Vectorf::Vector3f* dim;
				 objloader* loader;
				 long int frameCounter;

			 public:
				 Animation3D ( string files [ ], Vectorf::Vector3f* pos, Vectorf::Vector3f* dim );
				 Animation3D ( string files [ ], float x, float y, float z, float w, float h, float d );
				 virtual ~Animation3D ( );

				 void Render (  );
			 };
};

#endif//ANIMATION_H_