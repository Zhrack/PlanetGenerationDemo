
bool ConstantBuffer::Generate(ID3D11Device* device, void* data, size_t dataSize, D3D11_USAGE usage)
{
	D3D11_BUFFER_DESC cbDesc;

	cbDesc.ByteWidth = dataSize;
	cbDesc.Usage = usage;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
	initData.pSysMem = data;

	HRESULT hr = device->CreateBuffer(&cbDesc, &initData, &buffer);

	if (FAILED(hr))
		return false;

	return true;	
}

void ConstantBuffer::UpdateValues(ID3D11DeviceContext* con, const void* data)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	memset(&mappedSubResource, 0, sizeof(mappedSubResource));

	con->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
	//TODO trovare altro sistema per astrarre il CB e legarlo alla struct

}