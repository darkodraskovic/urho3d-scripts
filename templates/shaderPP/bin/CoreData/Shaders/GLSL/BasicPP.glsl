#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"
#include "PostProcess.glsl"

varying vec2 vScreenPos;

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    vScreenPos = GetScreenPosPreDiv(gl_Position);
}

void PS()
{
    vec3 rgb = texture2D(sDiffMap, vScreenPos).rgb;
    gl_FragColor = vec4(rgb, 1.0);

    // gl_FragColor = vec4(vScreenPos.x, vScreenPos.y, 0.0, 1.0);
}
