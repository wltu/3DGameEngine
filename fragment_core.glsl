#version 440

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTexture;
	sampler2D specularTexture;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

// Uniforms
uniform Material material;
uniform vec3 lightPos0;
uniform vec3 camPosition;

// Functions
vec3 calculateAmbient(Material material){
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 lightPos0, vec3 vs_normal){
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	vec3 diffusedColor = vec3(1.f, 1.f, 1.f);
	float diffused = clamp(dot(posToLightDirVec, vs_normal), 0, 1);

	return material.diffuse * diffused;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 lightPos0, vec3 vs_normal, vec3 camPosition){
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(camPosition - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	
	
	return 2* material.specular * specularConstant * texture(material.specularTexture, vs_texcoord).rgb;
}

void main(){
	// fs_color = vec4(vs_color, 1.f);
	//fs_color = texture(texture0, vs_texcoord) * vec4(vs_color, 1.f) + texture(texture1, vs_texcoord);

	// Ambient Light
	vec3 ambientLight = calculateAmbient(material);

	// Diffuse Light
	vec3 diffusedLight = calculateDiffuse(material, vs_position, lightPos0, vs_normal);

	// Specular Light
	vec3 specularLight = calculateSpecular(material, vs_position, lightPos0, vs_normal, camPosition);

	// Attenuation

	// Final Light
	//fs_color = texture(material.diffuseTexture, vs_texcoord) * vec4(vs_color, 1.f) 
	//		* (vec4(ambientLight, 1.f) + vec4(diffusedLight, 1.f) + vec4(specularLight, 1.f));

	fs_color = texture(material.diffuseTexture, vs_texcoord)
			* (vec4(ambientLight, 1.f) + vec4(diffusedLight, 1.f) + vec4(specularLight, 1.f));
}