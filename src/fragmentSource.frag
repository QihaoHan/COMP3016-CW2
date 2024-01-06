
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

uniform LightDirectional lightD;	//平行光源

uniform LightPoint lightP0;		//调整点光源衰减
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;

uniform LightSpot lightS;		//聚光源，主要用来判断是否在照射范围内

uniform Material material;		//最终可以调整颜色值

in vec2 TexCoord;		//对应贴图中的uv坐标
in vec3 FragPos;		//当前点坐标
in vec3 Normal;			//法向量


uniform vec3 objColor;

uniform vec3 ambientColor;

uniform vec3 lightDirUniform;
uniform vec3 cameraPos;


out vec4 FragColor;

//封装平行光源
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera) {
	
	float diffuseIntensity = max(dot(light.dirToLight, uNormal), 0);
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	
	vec3 R = normalize(reflect(-light.dirToLight, uNormal));	// 反射向量，参数为入射向量、法向量
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//封装点光源
vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//这个是光线照到该点的方向的单位向量
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//点光源实际光照衰减
	
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// 反射向量，参数为入射向量、法向量
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

//封装聚光源
vec3 CalcLightSpot(LightSpot light, vec3 uNormal, vec3 dirToCamera) {
	//attenuation
	float dist = length(light.pos - FragPos);		//这个是光线照到该点的方向的单位向量
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));		//点光源实际光照衰减
	float spotRatio = 0;
	float cosTheta = dot(normalize(FragPos - light.pos), -light.dirToLight);		//光源方向的反方向 点乘 光源到该片段的方向
	
	//cosTheta > light.cosPhyInner、cosTheta < light.cosPhyOuter
	spotRatio = (light.cosPhyOuter - cosTheta) / (light.cosPhyOuter - light.cosPhyInner);	
	spotRatio = max(0.0f, min(1.0f, spotRatio));	//设置边缘渐变

	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0) * attenuation * spotRatio;
	vec3 diffColor = diffuseIntensity * light.color * texture(material.diffuse, TexCoord).rgb;
	
	// specular		pow(max(dot(R, Cam), 0), shininess)
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal));	// 反射向量，参数为入射向量、法向量
	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess) * attenuation * spotRatio;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

void main() {
	vec3 finalResult = vec3(0.0f, 0.0f, 0.0f);
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);		//从该点到相机的向量
//	vec3 ambient = texture(material.diffuse, TexCoord).rgb * material.ambient * ambientColor;	//为了让阴影面也具有纹理，环境光也要乘上纹理

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);
	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0f);
}
