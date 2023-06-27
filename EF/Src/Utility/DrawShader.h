#pragma once
#include<DxLib.h>
class Vector2;

class DrawShader
{
public:

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static DrawShader& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);


	//画像描画（定数なし）
	void DrawGraphToShader(
		const Vector2& pos,const int& handle, const int& ps);
	//画像描画（定数付き）
	void DrawGraphToShader(
		const Vector2& pos,const int& handle, const int& ps,
		const COLOR_F& buf,const COLOR_F& subBuf = COLOR_F{});
	//サイズ指定描画
	void DrawExtendGraphToShader(
		const Vector2& pos, const Vector2& size , 
		const int& handle, const int& ps, 
		const COLOR_F& buf, const COLOR_F& subBuf = COLOR_F{});
	
	
	//サブテクスチャ付き描画
	void DrawGraphAndSubToShader(
		const Vector2& pos,
		const int& mHandle, const int& sHandle,
		const int& ps, const COLOR_F& buf, const COLOR_F& subBuf = COLOR_F{});


private:

	// 静的インスタンス
	static DrawShader* instance_;

	//HPシェーダー
	//頂点情報
	VERTEX2DSHADER vertex_[4];
	WORD index_[6];

	//シェーダー定数バッファ
	int psConstBuf_;

	//描画用の四角頂点の作成
	void MakeSquereVertex(Vector2 pos, Vector2 size);





	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	DrawShader(void);

	// デストラクタも同様
	~DrawShader(void);

};

