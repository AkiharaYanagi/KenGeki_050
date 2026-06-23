//=================================================================================================
//
// LoadChara_Utl ソースファイル
//
//=================================================================================================
#include "10_CharaData/LoadChara_Utl.h"
#include <codecvt>


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	LoadChara_Utl::LoadChara_Utl ()
	{
		::setlocale ( LC_ALL, "japanese" );
	}

	//-----------------------------------------------------------------------
	s3d::String LoadChara_Utl::LoadS3dString ( CUPR_BYTE buf, UINT32 & pos )
	{
		//名前のサイズ
		byte length = buf [ pos ++ ];	//Encoding.UTF8

		std::string str ( (char*)buf.get() + pos, length );
		s3d::String s3dStr = Unicode::FromUTF8 ( str );

		//位置を更新
		pos += length;

		//取得した名前を返す
		return s3dStr;
	}


	bool LoadChara_Utl::LoadBool ( CUPR_BYTE buf, UINT32 & pos )
	{
		//bool値も1バイト読み込んでポインタを進め、値を返す
		byte b = buf [ pos ++ ];	//1  or 0
		return (bool)b;
	}

	byte LoadChara_Utl::LoadByte ( CUPR_BYTE buf, UINT32 & pos )
	{
		//1バイト読み込んでポインタを進め、値を返す
		byte b = buf [ pos ++ ];
		return b;
	}

	int LoadChara_Utl::LoadInt ( CUPR_BYTE buf, UINT32 & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (int)0x01234567
		int i = 0;
		rsize_t size = sizeof ( int );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		pos += (UINT32)size;
		return i;
	}

	UINT32 LoadChara_Utl::LoadUInt ( CUPR_BYTE buf, UINT32 & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (UINT32)0x01234567
		UINT32 i = 0;
		rsize_t size = sizeof ( UINT32 );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		pos += (UINT32)size;
		return i;
	}

	float LoadChara_Utl::LoadFloat ( CUPR_BYTE buf, UINT32 & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (UINT32)0x01234567
		float f = 0;
		rsize_t size = sizeof ( float );
		::memcpy_s ( &f, size, buf.get () + pos, size );
		pos += (UINT32)size;
		return f;
	}


	VEC2 LoadChara_Utl::LoadVec2 ( CUPR_BYTE buf, UINT32 & pos )
	{
		int pos_x = LoadInt ( std::move ( buf ), pos );
		int pos_y = LoadInt ( std::move ( buf ), pos );
		return VEC2 ( (float)pos_x, (float)pos_y );
	}

	//intで読んだ値を10.fで割る(0.1f掛ける)
	VEC2 LoadChara_Utl::LoadVec2_Dev10F ( CUPR_BYTE buf, UINT32 & pos )
	{
		int pos_x = LoadInt ( std::move ( buf ), pos );
		int pos_y = LoadInt ( std::move ( buf ), pos );
		return VEC2 ( 0.1f * pos_x, 0.1f * pos_y );
	}


	RECT LoadChara_Utl::LoadRect ( CUPR_BYTE buf, UINT32 & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (UINT32)0x01234567
		RECT rect = { 0 };
		rsize_t size = sizeof ( RECT );
		::memcpy_s ( &rect, size, buf.get () + pos, size );
		pos += (UINT32)size;
		return rect;
	}
	
	void LoadChara_Utl::LoadListRect ( CUPR_BYTE buf, UINT32 & pos, PV_RECT pvRect )
	{
		UINT32 n = buf [ pos ++ ];
		pvRect->clear ();
		pvRect->resize ( n );
		for ( UINT32 i = 0; i < n; ++ i )
		{
			( *pvRect ) [ i ] = LoadRect ( std::move ( buf ), pos );
		}
	}


	L_UINT LoadChara_Utl::LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, UINT32 & refLength )
	{
		refLength = buf [ pos ++ ];

		std::unique_ptr < UINT32 [] > ary_uint = std::make_unique < UINT32 [] > ( refLength );
		for ( UINT32 i = 0; i < refLength; ++ i )
		{
			ary_uint [ i ] = (UINT32)buf [ pos ++ ];
		}

		return std::move ( ary_uint );
	}


	void LoadChara_Utl::LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, V_UINT32 & refAryUint )
	{
		UINT32 size = LoadUInt ( std::move ( buf ), pos );
		refAryUint.resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			refAryUint [ i ] = LoadUInt ( std::move ( buf ), pos );
		}
	}


	void LoadChara_Utl::LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, A_UINT32 & refAryUint )
	{
		UINT32 size = LoadUInt ( std::move ( buf ), pos );
		refAryUint.resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			refAryUint [ i ] = LoadUInt ( std::move ( buf ), pos );
		}
	}

	void LoadChara_Utl::LoadAryInt ( CUPR_BYTE buf, UINT32 & pos, A_INT32 & refAryInt )
	{
		UINT32 size = LoadInt ( std::move ( buf ), pos );
		refAryInt.resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			refAryInt [ i ] = LoadInt ( std::move ( buf ), pos );
		}
	}


}	//namespace CHARA

