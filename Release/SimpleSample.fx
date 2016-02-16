//--------------------------------------------------------------------------------------
// File: SimpleSample.fx
//
// The effect file for the SimpleSample sample.  
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4 g_MaterialAmbientColor;      // Material's ambient color
float4 g_MaterialDiffuseColor;      // Material's diffuse color
float3 g_LightDir;                  // Light's direction in world space
float4 g_LightDiffuse;              // Light's diffuse color
texture g_MeshTexture;              // Color texture for mesh

float    g_fLighting;
float	 g_fRed = 0.0f;
float    g_fTime;                   // App's time in seconds
float4x4 g_mWorld;                  // World matrix for object
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix


bool	 g_IsRim;
bool	 g_IsLine;
bool	 g_IsEdge;
float4x4 g_mProj;
float3	 g_vCameraPos;
float4x4 g_mInvWorldView;


//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler MeshTextureSampler = 
sampler_state
{
    Texture = <g_MeshTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 Diffuse    : COLOR0;     // vertex diffuse color (note that COLOR0 is clamped from 0..1)
    float2 TextureUV  : TEXCOORD0;  // vertex texture coords 
	float3 Rim		  : TEXCOORD1;
};
struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;  // Pixel color    
};



// PASS 0

VS_OUTPUT RenderSceneVS(    float4 Position : POSITION,
   float3 Normal : NORMAL,
   float2 mTexCoord : TEXCOORD0 )
{
   VS_OUTPUT Output;
   Output.Position = mul( Position, g_mWorldViewProjection );
   
   float3 normal = mul( Normal, (float3x3)g_mInvWorldView);
   normal =  normalize( mul( normal, (float3x3)g_mProj ) );

   float fLen =  ( g_vCameraPos.z ) / Output.Position.z * 0.004f  ;

   Output.Position.xy +=  fLen * Output.Position.z * normal.xy;
   Output.Diffuse = float4( 0.0f, 0.0f, 0.0f, 0.0f );
   Output.TextureUV = mTexCoord;
   Output.Rim = float3( 0.0f, 0.0f, 0.0f );

   return( Output );
}
PS_OUTPUT RenderScenePS( VS_OUTPUT Output)
{   
   PS_OUTPUT Out;
   Out.RGBColor = tex2D( MeshTextureSampler, Output.TextureUV );
   Out.RGBColor.rgb = Output.Diffuse.rgb;

   return Out;
}

///////////////-----------------------------------------------














//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VS_OUTPUT RenderSceneVS_1( float4 vPos : POSITION, 
                         float3 vNormal : NORMAL,
                         float2 vTexCoord0 : TEXCOORD0 )
{
    VS_OUTPUT Output;
    float3 vNormalWorldSpace;
    
    Output.Position = mul(vPos, g_mWorldViewProjection);
    
    vNormalWorldSpace = normalize(mul(vNormal, (float3x3)g_mWorld)); // normal (world space)

	
    Output.Diffuse.rgb = ( dot(vNormalWorldSpace,  g_LightDir.xyz) * 0.5f + 0.5f );
    Output.Diffuse.a = 1.0f;

	float3 vViewDir = normalize( g_vCameraPos  +  Output.Position );
	float Rim = smoothstep( 0.5f, 1.0f,  1.0f -  saturate( dot( vNormalWorldSpace , normalize( vViewDir ) ) ) );

	if( g_IsEdge )
	{
		float result =  dot( vNormalWorldSpace , normalize( vViewDir ) );
		if( result > 0.0f && result < 0.5f )
		{
			Output.Diffuse.rgb += 0.5f;
		}
	}
    
    Output.TextureUV = vTexCoord0; 
	Output.Rim = 0.7f * saturate( dot( vNormalWorldSpace, g_LightDir ) )
		* pow( Rim, 3.0f );
    return Output;    
}


//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// This shader outputs the pixel's color by modulating the texture's
// color with diffuse material color
//--------------------------------------------------------------------------------------
PS_OUTPUT RenderScenePS_1( VS_OUTPUT In )
{ 
    PS_OUTPUT Output;

    // Lookup mesh texture and modulate it with diffuse
//	In.Diffuse = saturate( In.Diffuse );
//	In.Diffuse += float4( 0.2f, 0.2f, 0.2f, 0.0f );





    Output.RGBColor = tex2D( MeshTextureSampler, In.TextureUV );
	if( g_IsRim )
	{
		Output.RGBColor += float4( In.Rim , 0.0f ) ;
	}
	if( g_fRed > 0.0f )
	{
		Output.RGBColor.gb -= g_fRed * 0.1f;
		
		Output.RGBColor.r += g_fRed;
	}
	if( g_IsLine )
	{
		if( Output.RGBColor.a != 1.0f )
		{
			Output.RGBColor.rgb *= Output.RGBColor.rgb  * Output.RGBColor.rgb   * Output.RGBColor.rgb  * 4.5f * In.Diffuse;
			Output.RGBColor.a *= 1.0f;
		}
		else
		{
			In.Diffuse =   (  ceil(In.Diffuse*3) / 3.0f );
			Output.RGBColor.rgb *= Output.RGBColor.rgb * g_fLighting 
				* In.Diffuse;
		}
	}
	else
	{
		Output.RGBColor.rgb *= Output.RGBColor.rgb * Output.RGBColor.rgb  * 2.0f + float4( 0.8f, 0.8f, 0.8f, 0.0f ) ;
	}

    return Output;
}


//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
    pass P0
    {
	CULLMODE = CW;          
        VertexShader = compile vs_3_0 RenderSceneVS();
        PixelShader  = compile ps_3_0 RenderScenePS(); 
    }
    pass P1
    {
	
	CULLMODE = CCW;    
        VertexShader = compile vs_3_0 RenderSceneVS_1();
        PixelShader  = compile ps_3_0 RenderScenePS_1();
    }
}
