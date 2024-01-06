
#version 410 core
struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct LightDirectional {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
	float cosPhyInner;
	float cosPhyOuter;
};

uniform LightDirectional lightD;	//ƽ�й�Դ

uniform LightPoint lightP0;		//�������Դ˥��
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;

uniform LightSpot lightS;		//�۹�Դ����Ҫ�����ж��Ƿ������䷶Χ��

uniform Material material;		//���տ��Ե�����ɫֵ

in vec2 TexCoord;		//��Ӧ��ͼ�е�uv����
in vec3 FragPos;		//��ǰ������
in vec3 Normal;			//������


uniform vec3 objColor;

uniform vec3 ambientColor;

uniform vec3 lightDirUniform;
uniform vec3 cameraPos;


out vec4 FragColor;

//��װƽ�й�Դ
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera) {
	
	float diffuseIntensity = max(dot(light.dirToLight, uNormal), 0);
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	
	vec3 R = normalize(reflect(-light.dirToLight, uNormal));	// ��������������Ϊ����������������
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//��װ���Դ
vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//����ǹ����յ��õ�ķ���ĵ�λ����
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//���Դʵ�ʹ���˥��
	
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// ��������������Ϊ����������������
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//��װ�۹�Դ
vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//����ǹ����յ��õ�ķ���ĵ�λ����
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//���Դʵ�ʹ���˥��
	float spotRatio = 0;
	float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);		//��Դ����ķ����� ��� ��Դ����Ƭ�εķ���
	
	//cosTheta > light.cosPhyInner��cosTheta < light.cosPhyOuter
	spotRatio = (light.cosPhyOuter - cosTheta) / (light.cosPhyOuter - light.cosPhyInner);	
	spotRatio = max(0.0f, min(1.0f, spotRatio));	//���ñ�Ե����

	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation * spotRatio;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// ��������������Ϊ����������������
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation * spotRatio;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

void main() {
	vec3 finalResult = vec3(0.0f, 0.0f, 0.0f);
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);		//�Ӹõ㵽���������
//	vec3 ambient = texture(material.diffuse, TexCoord).rgb * material.ambient * ambientColor;	//Ϊ������Ӱ��Ҳ��������������ҲҪ��������

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);
	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0f);
}
