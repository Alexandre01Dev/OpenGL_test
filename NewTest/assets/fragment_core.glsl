#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 normal;
in vec3 crntPos;
// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


void main()
{
   
   float ambient = 0.20f;
   vec3 normal = normalize(normal);
   vec3 lightDirection = normalize(lightPos - crntPos);
   
   float diffuse = max(dot(normal,lightDirection),0.0f);
   
   float specularLight = 0.4f;
   vec3 viewDirection = normalize(camPos - crntPos);
   vec3 reflectionDirection = reflect(-lightDirection,normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f),8); 
   float specular = specAmount * specularLight;
   
   
   vec4 tex = texture(tex0, texCoord);
   vec4 spec = texture(tex1, texCoord);
   
   //FragColor = texture2D(tex0, texCoord) * vec4(color,1) * (lightColor * diffuse);
   tex.r *= (lightColor.r * (diffuse + ambient + specular));
   tex.g *= (lightColor.g * (diffuse + ambient + specular));
   tex.b *= (lightColor.b * (diffuse + ambient + specular));
   
   tex.r += spec.r* specular;
   tex.g += spec.r* specular;
   tex.b += spec.r * specular;
  
   FragColor = tex * vec4(color,1);
}