#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

namespace gea
{
	struct RenderComponent
	{
		RenderComponent(short m, short t) : meshIndex(m), textureIndex(t) {};
		short meshIndex;
		short textureIndex;
	};
}

#endif // RENDERCOMPONENT_H
