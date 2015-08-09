//***************************************************************************************
// Effects.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Defines lightweight effect wrappers to group an effect and its variables.
// Also defines a static Effects class from which we can access all of our effects.
//***************************************************************************************

#ifndef EFFECTS_H
#define EFFECTS_H

#include "d3dUtil.h"
#include "Shader.h"

namespace DXFramework
{

	template<typename T>
	class Shader;
	//forward declare templates
	typedef Shader<ID3D11VertexShader> VertexShader;
	typedef Shader<ID3D11GeometryShader> GeometryShader;
	typedef Shader<ID3D11DomainShader> DomainShader;
	typedef Shader<ID3D11HullShader> HullShader;
	typedef Shader<ID3D11PixelShader> PixelShader;

	class Effect
	{
	public:
		Effect(ID3D11Device* device);
		virtual ~Effect();

	protected:
		virtual void Draw(ID3D11DeviceContext* context) = 0;

	protected:
		D3D_PRIMITIVE_TOPOLOGY topology;

		VertexShader* vertexShader;
		GeometryShader* geoShader;
		DomainShader* domainShader;
		HullShader* hullShader;
		PixelShader* pixelShader;
	private:
		Effect(const Effect& rhs);
		Effect& operator=(const Effect& rhs);
	};
#pragma endregion

#pragma region Effects
	class Effects
	{
	public:
		static void InitAll(ID3D11Device* device);
		static void DestroyAll();

		//static BasicEffect* BasicFX;
		//static SkyEffect* SkyFX;
		//static TerrainEffect* TerrainFX;
	};

}

#endif // EFFECTS_H