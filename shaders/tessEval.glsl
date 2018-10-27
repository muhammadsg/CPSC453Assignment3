#version 410

layout(isolines) in;

in vec3 teColour[];
uniform int curveType;
vec2 position;

out vec3 color; //Color going forward to Fragment shader


void main()
{
	float t = gl_TessCoord.x; // X TessCoord is u value in the spiral or given formula (for spiral was simply the angle around spiral)

	vec3 startColour = teColour[2]; //Start color is green
	vec3 endColour = teColour[1]; //End color is red

	if (curveType == 0)
	{
		vec2 p0 = gl_in[0].gl_Position.xy;
		vec2 p1 = gl_in[1].gl_Position.xy;
		vec2 p2 = gl_in[2].gl_Position.xy;
	
		float b0 = (1-t) * (1-t);
		float b1 = 2 * (1-t) * t;
		float b2 = t * t;

		position = b0*p0 + b1*p1 + b2*p2; 
	}

	if (curveType == 1)
	{
		vec2 p0 = gl_in[0].gl_Position.xy;
		vec2 p1 = gl_in[1].gl_Position.xy;
		vec2 p2 = gl_in[2].gl_Position.xy;
		vec2 p3 = gl_in[3].gl_Position.xy;

		float b0 = (1-t) * (1-t) * (1-t);
		float b1 = 3 * t * (1-t) * (1-t); 
		float b2 = 3 * t * t * (1-t);
		float b3 = t * t * t;

		position = b0*p0 + b1*p1 + b2*p2 + b3*p3; 
	}

	gl_Position = vec4(position, 0, 1);

	color = startColour;

}
