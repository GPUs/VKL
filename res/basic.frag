#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (location = 0) out vec4 uFragColor;

layout ( location = 0 ) in struct fragment_in {
    vec2 uv;
} IN;

void main() {
	uFragColor = vec4(IN.uv.x, IN.uv.y, 0.5, 1.0);
}