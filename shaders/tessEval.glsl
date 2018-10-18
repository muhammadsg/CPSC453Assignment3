#version 410

layout(isolines) in;

in vec3 teColour[];

out vec3 color; //Color going forward to Fragment shader

#define PI 3.14159265359

void main()
{
	float t = gl_TessCoord.x; // X TessCoord is u value in the spiral or given formula (for spiral was simply the angle around spiral)

	vec3 startColour = teColour[0]; //Start color is red
	vec3 endColour = teColour[1]; //End color is blue

	//vec2 p0 = vec2(0, 0);
	//vec2 p1 = vec2(1, 0);

	//For example linear
	//vec2 p0 = gl_in[0].gl_Position.xy;
	//vec2 p1 = gl_in[1].gl_Position.xy;

	//vec2 bx = p1-p0; //Direction of spiral if p0 (0,0) and p1 = (1,0) then bx = (1,0)
	//vec2 by = vec2(bx.y, bx.x); //Then by = (0, 1) 
	//float cycles = 3.0;

	//vec2 position = t*cos(t*cycles*2.0*PI)*bx + t*sin(t*cycles*2.0*PI)*by + p0;

	//For example quadratic
	vec2 p0 = gl_in[0].gl_Position.xy;
	vec2 p1 = gl_in[1].gl_Position.xy;
	vec2 p2 = gl_in[2].gl_Position.xy;
	
	float b0 = (1-t) * (1-t);
	float b1 = 2 * (1-t) * t;
	float b2 = t * t;

	vec2 position = b0*p0 + b1*p1 + b2*p2;

	gl_Position = vec4(position, 0, 1);

	color = (1-t)*startColour + t*endColour;

}
