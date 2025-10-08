#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

namespace gea
{
	struct RenderComponent
	{
		RenderComponent(short m, short t, short id) : meshIndex(m), textureIndex(t), entityID(id){};
		short meshIndex;
		short textureIndex;
		short entityID;
	};
}

#endif // RENDERCOMPONENT_H
