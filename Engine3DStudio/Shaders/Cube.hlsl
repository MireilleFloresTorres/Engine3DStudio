/**
 * @brief Matriz utilizada para transformar las posiciones de los vértices
 */
cbuffer TransformBuffer : register(b0)
{
    float4x4 worldViewProjection;
};

/**
 * @brief Datos de entrada del vertex shader
 */
struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
};

/**
 * @brief Datos enviados desde el vertex shader al pixel shader
 */
struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

/**
 * @brief Transforma la posición del vértice y conserva su color
 */
PSInput VSMain(VSInput input)
{
    PSInput output;
    output.position = mul(float4(input.position, 1.0f), worldViewProjection);
    output.color = input.color;
    return output;
}

/**
 * @brief Devuelve el color del píxel
 */
float4 PSMain(PSInput input) : SV_TARGET
{
    return input.color;
}