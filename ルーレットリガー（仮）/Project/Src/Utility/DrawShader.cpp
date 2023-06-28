#include "../Common/Vector2.h"
#include "DrawShader.h"

DrawShader* DrawShader::instance_ = nullptr;

void DrawShader::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new DrawShader();
	}
	instance_->Init();
}

DrawShader& DrawShader::GetInstance(void)
{
	return *instance_;
}

void DrawShader::Init(void)
{
	psConstBuf_= CreateShaderConstantBuffer(sizeof(float) * 8);
}

void DrawShader::Release(void)
{
	DeleteShaderConstantBuffer(psConstBuf_);

	delete[] index_;
	delete[] vertex_;
}

void DrawShader::DrawGraphToShader(const Vector2& pos, const int& handle, const int& ps)
{
	//シェーダーの設定
	SetUsePixelShader(ps);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, handle);

	//サイズ
	int x, y;
	GetGraphSize(handle, &x, &y);

	//描画座標
	MakeSquereVertex(pos, { x,y });


	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void DrawShader::DrawGraphToShader(
	const Vector2& pos, const int& handle, const int& ps,
	const COLOR_F& buf, const COLOR_F& subBuf)
{
	//シェーダーの設定
	SetUsePixelShader(ps);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, handle);

	//シェーダー用の定数バッファ
	auto& cBuf = psConstBuf_;

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = buf;

	//サイズ
	int x, y;
	GetGraphSize(handle, &x, &y);

	//描画座標
	MakeSquereVertex(pos, {x,y});


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawShader::DrawExtendGraphToShader(
	const Vector2& pos, const Vector2& size, 
	const int& handle, const int& ps, 
	const COLOR_F& buf, const COLOR_F& subBuf)
{
	//シェーダーの設定
	SetUsePixelShader(ps);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, handle);

	//シェーダー用の定数バッファ
	auto& cBuf = psConstBuf_;

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = subBuf;

	//描画座標
	MakeSquereVertex(pos,size);


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//バイリニア補間モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ネアレストネイバー法
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void DrawShader::DrawGraphAndSubToShader(
	const Vector2& pos,
	const int& mHandle, const int& sHandle, const int& ps, 
	const COLOR_F& buf, const COLOR_F& subBuf)
{
	//シェーダーの設定
	SetUsePixelShader(ps);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, mHandle);
	SetUseTextureToShader(1, sHandle);

	//シェーダー用の定数バッファ
	auto& cBuf = psConstBuf_;

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = subBuf;

	//サイズ
	int x, y;
	GetGraphSize(mHandle, &x, &y);
	//描画座標
	MakeSquereVertex(pos, {x,y});


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void DrawShader::MakeSquereVertex(Vector2 pos, Vector2 size)
{

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + size.x);
	float eY = static_cast<float>(pos.y + size.y);

	// ４頂点の初期化
	for (int i = 0; i < 4; i++)
	{
		vertex_[i].rhw = 1.0f;
		vertex_[i].dif = GetColorU8(255, 255, 255, 255);
		vertex_[i].spc = GetColorU8(255, 255, 255, 255);
		vertex_[i].su = 0.0f;
		vertex_[i].sv = 0.0f;
	}

	// 左上
	vertex_[cnt].pos = VGet(sX, sY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// 右上
	vertex_[cnt].pos = VGet(eX, sY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// 右下
	vertex_[cnt].pos = VGet(eX, eY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 1.0f;
	cnt++;

	// 左下
	vertex_[cnt].pos = VGet(sX, eY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 1.0f;

	// 頂点インデックス
	cnt = 0;
	index_[cnt++] = 0;
	index_[cnt++] = 1;
	index_[cnt++] = 3;

	index_[cnt++] = 1;
	index_[cnt++] = 2;
	index_[cnt++] = 3;
}

DrawShader::DrawShader(void)
{
}

DrawShader::~DrawShader(void)
{
	delete instance_;
}
