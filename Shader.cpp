#include "Shader.h"
#include "d3dUtil.h"
using namespace DXFramework;


template<typename T>
Shader<T>::Shader() :
shader(nullptr), RTV(nullptr)
{
	SRVs(nullptr);
	cBuffers(nullptr);
}

template<typename T>
Shader<T>::~Shader()
{

}

template<typename T>
void Shader<T>::UpdateCBuffer(ID3D11DeviceContext* con, int bufferIndex, const void* data, size_t dataSize, int slot)
{
	D3D11_MAPPED_SUBRESOURCE mappedData;
	ZeroMemory(&mappedData, sizeof(D3D11_MAPPED_SUBRESOURCE));

	con->Map(cBuffers[bufferIndex].get(), slot, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	//	Update the vertex buffer here.
	memcpy(mappedData.pData, data, dataSize);
	//	Reenable GPU access to the vertex buffer data.
	con->Unmap(cBuffers[bufferIndex].get(), slot);

}

template<typename T>
void Shader<T>::UpdateSRV(ID3D11DeviceContext* con, int srvIndex, const void* data, size_t dataSize, int slot)
{
	D3D11_MAPPED_SUBRESOURCE mappedData;
	ZeroMemory(&mappedData, sizeof(D3D11_MAPPED_SUBRESOURCE));

	con->Map(SRVs[srvIndex].get(), slot, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	//	Update the vertex buffer here.
	memcpy(mappedData.pData, data, dataSize);
	//	Reenable GPU access to the vertex buffer data.
	con->Unmap(SRVs[srvIndex].get(), slot);

}

template<typename T>
bool Shader<T>::AddCBuffer(ID3D11Device* device, CD3D11_BUFFER_DESC& cbDesc, D3D11_SUBRESOURCE_DATA& initData)
{
	cBuffers.emplace_back(ID3D11Buffer());
	HRESULT hr = device->CreateBuffer(cbDesc, initData, &cBuffers.end());
	if (FAILED(hr))
		return false;
	return true;
}

template<typename T>
bool Shader<T>::AddSRV(ID3D11Device* device, ID3D11Texture2D& texture)
{
	SRVs.emplace_back(ID3D11ShaderResourceView());
	HRESULT hr = device->CreateShaderResourceView(&texture, nullptr, &SRVs.end());
	if (FAILED(hr))
		return false;
	return true;
}

template<typename T>
bool Shader<T>::SetRTV(ID3D11Device* device, ID3D11Texture2D& texture)
{
	HRESULT hr = device->CreateRenderTargetView(&texture, nullptr, RTV.get());
	if (FAILED(hr))
		return false;
	return true;
}