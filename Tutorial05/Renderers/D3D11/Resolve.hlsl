#ifndef NUM_SAMPLES
 #define NUM_SAMPLES 1
#endif 

float4 QuadVS(in uint id: SV_VertexID): SV_Position
{
    float4 output = 0.0f;

    if(id == 0)
    {
        output = float4(-1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if(id == 1)
    {
        output = float4(3.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        output = float4(-1.0f, -3.0f, 1.0f, 1.0f);
    }

    return output;
}

Texture2DMS<float4, NUM_SAMPLES> t;

float4 ResolvePS(in float4 pos: SV_Position): SV_Target
{
    float4 o = 0.0f;

    [unroll]
    for (int s = 0; s < NUM_SAMPLES; s++)
    {
        o += t.Load(pos.xy, s);
    }

    return o / NUM_SAMPLES;
}

float4 ClearPS(): SV_Target
{
    return float4(0.0f, 0.0f, 0.0f, 0.0f);
}