
#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoord;							//�����2ά��������Ϣ����ʾ�����Ӧ�������е������
layout(location = 3) in vec3 aNormal;							//���뷨����
							//�ͽ����ı任����
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;
out vec2 TexCoord;

//�߶��в�����Position�;����任�ķ�����
out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0);
	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz;		//֮ǰû��������൱��ֻ�й�Դ����û�б���������꣬���еط��õ��Ķ���ƽ�й�
	TexCoord = aTexCoord;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;	//�������Ķ��������Ϊ�˱��ⳤ��ȸı䵼�·����������Ƿ����������
}
