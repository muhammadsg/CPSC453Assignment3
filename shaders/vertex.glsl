// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;

uniform int curveType;
double s;

// output to be interpolated between vertices and passed to the fragment stage
out vec3 color; //Color goes to tesselation control shader

void main()
{
    if (curveType == 1)
    {
        s = 0.1;
    }

    else
        s = 0.5;

    mat3x3 scalingMatrix = mat3x3(s, 0.0, 0.0, 
                                  0.0, s, 0.0, 
                                  0.0, 0.0, s);
                                  
    vec3 scaledPoint = scalingMatrix * VertexPosition;

    //vec4 translate = vec4(0.25, 0.25, 0.25, 0.25);
    // assign vertex position without modification
    gl_Position = vec4(scaledPoint.xy, 0.0, 1.0);

    // assign output colour to be interpolated
    color = VertexColor;
}
