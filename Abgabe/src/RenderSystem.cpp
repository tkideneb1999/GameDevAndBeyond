#include "RenderSystem.h"

//GLuint VBO;
	//Handle to reach Buffer later on

	//glGenBuffers(1, &VBO);
	//Generates generic Buffers based on first argument (amount of Buffers to generate) and a pointer to the array (GLuint)

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Binds the Buffer so that it can be modified until another Buffer is bound or handle is 0, also defines type of Buffer
	//GL_ARRAY_BUFFER = buffer contains array of vertices
	//GL_ELEMENT_ARRAY_BUFFER = buffer contains indices of vertices in another buffer

	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	//Fill object/buffer with data
	//Arguments: 1. Target name: same as in Binding Buffer, 2. size: size of data in bytes, 3. adress of data
	//			 4. How to use data: GL_STATIC_DRAW = data in Buffer not changing
	//							     GL_DYNAMIC_DRAW = data in Buffer changes
	//							     For optimization purposes

	//--Later important
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//Tells pipeline how to interpret data
	//1. index of attribute, 2. number of components in Attribute, 3. Data type of Component, 4. Normalize data?, 5. stride: number of bytes between two instances of the attribute
	//6. Offset useful for more than one attribute -> tells starting point of other attributes in bytes

	//glDrawArrays(GL_POINTS, 0, 1);
	//Call to draw geometry
	//1. How to draw: GL_POINTS, GL_TRIANGLES, GL_LINE, 2. where to start, 3. how many elements to draw
	//Can be separated into ORDERED DRAWS -> GPU goes array through one by one (if one vertex is to be used twice, has to be specified twice)
	//					and INDEXED DRAWS -> GPU goes through array based on Index Buffer

	//glDisableVertexAttribArray(0);
	//Disables vertex attribute

	//GLuint ShaderProgram = glCreateProgram();
	//Creates shader object with handle
	//Shaders will be linked to this

	//GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	//GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Create vertex and fragment shader objects + handles

	//glShaderSource(VertexShader, 1, pShaderCodeString, length)
	//provide Shader object with source code as string (code can be divided over many arrays)

	//glCompileShader(VertexShader);
	//Compile shader

	//GLint success;
	//glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	GLchar InfoLog[1024];
	//	glGetShaderInfoLog(VertexShader, sizeof(InfoLog), nullptr, InfoLog);
	//}
	//get compiler errors of shader

	//glAttachShader(ShaderProgram, VertexShader);
	//Attach compiled shader to shader program

	//glLinkProgram(ShaderProgram);
	//Link shader Program -> Vertex outputs to Fragment inputs etc.
	//After that intermediate shader objects can be deleted with glDetachShader and glDeleteShader
	//glDeleteShader will only mark it for deletion, only if shader object detached it will get deleted as no more references there

	//glGetProgramiv(ShaderProgramm, GL_LINK_STATUS, &success);
	//if (success == 0)
	//{
	//	GLchar ErrorLog[1024];
	//	glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), nullptr, ErrorLog);
	//}
	//get linking errors

	//glValidateProgram(ShaderProgram);
	//Checks if program can execute in the current pipeline state
	//Should be used only during developement -> creates overhead

	//glUseProgram(ShaderProgram);
	//mark shader program to be used from now on for all draws until it is replaced

	//--SHADER
	//#version 330
	//Tells compiler which version of GLSL to use
	//layout(location = 0) in vec3 Position;
	//declares "Position" Attribute

	//only one main function per shader which is used as entry point for shader
	//used function is called main()
	//--END SHADER