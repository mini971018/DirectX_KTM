#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>


#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"

void GameEngineRenderUnit::SetPipeLine(const std::string_view& _Name) 
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}
}

void GameEngineRenderUnit::Render(float _DeltaTime)
{
	Pipe->RenderingPipeLineSetting();
	ShaderResHelper.Setting();
	Pipe->Render();
}

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start()
{
	PushCameraRender(0);
}

void GameEngineRenderer::RenderTransformUpdate(GameEngineCamera* _Camera)
{
	if (nullptr == _Camera)
	{
		assert(false);
		return;
	}

	GetTransform()->SetCameraMatrix(_Camera->GetView(), _Camera->GetProjection());
}

void GameEngineRenderer::Render(float _Delta) 
{
	// GameEngineDevice::GetContext()->VSSetConstantBuffers();
	// GameEngineDevice::GetContext()->PSSetConstantBuffers();

	// 텍스처 세팅 상수버퍼 세팅 이런것들이 전부다 처리 된다.

	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->Pipe->RenderingPipeLineSetting();

		Units[i]->ShaderResHelper.Setting();

		// 이걸하기 전에 각 세팅이 완벽하게 되어있으면 된다.
		Units[i]->Pipe->Render();
	}

}

std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLine(int _index/* = 0*/) 
{
	if (Units.size() <= _index)
	{
		MsgAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	return Units[_index]->Pipe;
}

// 이걸 사용하게되면 이 랜더러의 유니트는 자신만의 클론 파이프라인을 가지게 된다.
std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLineClone(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	if (false == Units[_index]->Pipe->IsClone())
	{
		Units[_index]->Pipe = Units[_index]->Pipe->Clone();
	}

	return Units[_index]->Pipe;
}


void GameEngineRenderer::SetPipeLine(const std::string_view& _Name, int _index)
{
	//if (0 >= Units.size())
	//{
	//	MsgAssert("랜더 유니트가 존재하지 않습니다.");
	//}

	if (Units.size() + 1 <= _index)
	{
		MsgAssert("너무큰 랜더유니트 확장을 하려고 했습니다");
	}

	if (Units.size() <= _index)
	{
		Units.resize(_index + 1);
		Units[_index] = std::make_shared<GameEngineRenderUnit>();
	}

	std::shared_ptr<GameEngineRenderUnit> Unit = Units[_index];

	if (nullptr == Unit)
	{
		MsgAssert("존재하지 않는 랜더유니트를 사용하려고 했습니다.");
	}


	Unit->Pipe = GameEngineRenderingPipeLine::Find(_Name);

	{
		const GameEngineShaderResHelper& Res = Unit->Pipe->GetVertexShader()->GetShaderResHelper();
		Unit->ShaderResHelper.Copy(Res);
	}

	{
		const GameEngineShaderResHelper& Res = Unit->Pipe->GetPixelShader()->GetShaderResHelper();
		Unit->ShaderResHelper.Copy(Res);
	}

	if (true == Unit->ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = GetTransform()->GetTransDataRef();
		Unit->ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}


	GetTransform()->GetWorldMatrix();
}

void GameEngineRenderer::PushCameraRender(int _CameraOrder)
{
	GetLevel()->PushCameraRenderer(DynamicThis<GameEngineRenderer>(), _CameraOrder);
}

void GameEngineRenderer::CalSortZ(GameEngineCamera* _Camera)
{
	// View행렬로 해야 카메라가 원점에 오고 그 원점을 기준으로 카메라가 위치한곳의 z로 처리한다.

	switch (_Camera->ProjectionType)
	{
	case CameraType::Orthogonal:
	{
		// 직교 투영이기 때문에 카메라의 View행렬을 곱해서 원점을 기준으로 
		// 위치를 카메라의 원점을 기준으로한 위치로 바꾸고 그 z를 사용하면 확실한
		// 직교에서의 카메라와의 z거리가 된다.
		float4 View = GetTransform()->GetWorldPosition() * _Camera->View;
		CalZ = View.z;
		break;
	}
	case CameraType::Perspective:
	{
		float4 View = GetTransform()->GetWorldPosition() * _Camera->View;
		CalZ = View.z;
		break;
	}
	default:
		break;
	}

}
