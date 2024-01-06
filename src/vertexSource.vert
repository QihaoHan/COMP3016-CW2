
#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoord;							//再添加2维的纹理信息，表示顶点对应的纹理中点的坐标
layout(location = 3) in vec3 aNormal;							//输入法向量
							//送进来的变换矩阵
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;
out vec2 TexCoord;

//线段中插入点的Position和经过变换的法向量
out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;		//之前没有这个，相当于只有光源坐标没有被照射点坐标，所有地方得到的都是平行光
	TexCoord = aTexCoord;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;	//做这样的额外操作是为了避免长宽比改变导致法向量不再是法向量的情况
}
