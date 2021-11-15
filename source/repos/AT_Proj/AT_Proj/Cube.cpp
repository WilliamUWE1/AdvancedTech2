#include "Cube.h"
#include "BindableBase.h"

Cube::Cube(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		const std::vector<Vertex> vertices =
		{
			{ -1.0f,-1.0f,-1.0f },
			{ 1.0f,-1.0f,-1.0f },
			{ -1.0f,1.0f,-1.0f },
			{ 1.0f,1.0f,-1.0f },
			{ -1.0f,-1.0f,1.0f },
			{ 1.0f,-1.0f,1.0f },
			{ -1.0f,1.0f,1.0f },
			{ 1.0f,1.0f,1.0f },
		};
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

		const std::vector<unsigned short> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		struct ConstantBuffer2
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[6];
		};
		const ConstantBuffer2 cb2 =
		{
			{
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,1.0f,1.0f },
			}
		};
		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuff>(gfx, *this));
}

void Cube::Update(float dt) noexcept
{
	//xPos += 1;
	collider.setBoundingBox(pos);
}

void Cube::setPos(float xpos, float ypos, float zpos)
{
	pos.x = xpos;
	pos.y = ypos;
	pos.z = zpos;
}

DirectX::XMFLOAT3 Cube::GetPos()
{
	return pos;
}

void Cube::setPosX(float xpos)
{
	pos.x = xpos;
}

void Cube::setPosY(float ypos)
{
	pos.y = ypos;
}

void Cube::setPosZ(float zpos)
{
	pos.z = zpos;
}

bool Cube::isColliding(DirectX::XMFLOAT3 pos1)
{
	return collider.checkBoundingBox(pos1);
}


DirectX::XMMATRIX Cube::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}