#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Lights
#define MAX_LIGHTS 128


struct SceneLight {
   vec3 position;
   float ambient;
   float diffuse;
   float specular;
   vec3 color;
};

struct DirectionalLight {
   float ambient;
   float diffuse;
   float specular;
   vec3 color;
};

uniform int lightSize;
uniform SceneLight lights[MAX_LIGHTS];
uniform DirectionalLight directLight;
uniform bool hasDirectLight = false;

// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 normal;
in vec3 crntPos;
float globalLight = 0.15f;
uniform vec3 camPos;
// Gets the Texture Unit from the main function


uniform sampler2D tex0;
uniform sampler2D tex1;



// Déclaration des functions
vec3 CalcDirectionnalLight(DirectionalLight light);
vec3 CalcSimpleLight(SceneLight light);
bool DrawLine2V(vec2 start, vec2 end, vec4 color);
bool DrawLine2V(vec2 start, vec2 end);
bool DrawLine2V(vec3 start, vec3 end, vec4 color);
bool DrawLine2V(vec3 start, vec3 end);
bool DrawLine(vec3 start, vec3 end, vec4 color);
bool DrawLine(vec3 start, vec3 end);

void main()
{
   

 //  float distanceFactor = clamp(1.0 - distance(camPos, lightPos) / maxSpecDistance, 0.0, 1.0);

   //float specular = pow(specAngle, 16) * specularLight;

   // normalise vec3/sqrt(vec3^2)

   vec4 tex = texture(tex0, texCoord);
   vec4 spec = texture(tex1, texCoord);

   



   vec3 result = vec3(0);
   if(hasDirectLight){
      result += CalcDirectionnalLight(directLight);
   }
   for(int i = 0; i < lightSize; i++){
      result += CalcSimpleLight(lights[i]);

      if(DrawLine2V(lights[i].position,camPos,vec4(1,1,0,0.5))){
         return;
      }
   }

   //FragColor = texture2D(tex0, texCoord) * vec4(color,1) * (lightColor * diffuse);

   FragColor = vec4(result,tex.a) * vec4(color, 1);
}
bool DrawLine2V(vec3 start, vec3 end){
   return DrawLine2V(start,end, vec4(0,1,0,1));
}
bool DrawLine2V(vec3 start, vec3 end, vec4 color){
   return DrawLine(vec3(start.x,0,start.z), vec3(end.x,0,end.z),color);
}
bool DrawLine2V(vec2 start, vec2 end){
   return DrawLine2V(start,end, vec4(0,1,0,1));
}
bool DrawLine2V(vec2 start, vec2 end, vec4 color){
   return DrawLine(vec3(start.x,0,start.y), vec3(end.x,0,end.y));
}
bool DrawLine(vec3 start, vec3 end){
   return DrawLine(start,end,vec4(0,1,0,1));
}
bool DrawLine(vec3 start, vec3 end,vec4 color){
   vec3 nEnd = normalize(end);

   float lineWidth = 0.05f; // Ajustez cette valeur en fonction de l'épaisseur désirée de la ligne

   // Calculer la direction de la ligne
   vec3 lineDirection = normalize(end - start);

   // Calculer le vecteur du point de départ à la position actuelle
   vec3 startToCurrent = crntPos - start;

   // Projetter startToCurrent sur la direction de la ligne
   float projectionLength = dot(startToCurrent, lineDirection);
   vec3 projectedPoint = start + clamp(projectionLength, 0.0, length(end - start)) * lineDirection;

   // Calculer la distance entre le point projeté et la position actuelle
   float distanceToLine = length(crntPos - projectedPoint);

   // Vérifier si la distance est inférieure à l'épaisseur de la ligne
   if (distanceToLine < lineWidth) {
      FragColor = color;  // Couleur verte pour la ligne
      return true;
   }
   return false;
}

vec3 CalcSimpleLight(SceneLight light){
   vec3 tex = vec3(texture(tex0, texCoord));
   vec3 spec = vec3(texture(tex1, texCoord));


   vec3 lightVec = light.position - crntPos;
   float dist = length(lightVec);
   float a = 0.1f;
   float b = 0.04f;
   // 1/a*d^2*b*d+1
   // a = quadratic term
   // b = linear
   float inten = 1.0f / (a*(dist*dist)+b*dist+1.0f);

   float ambient = light.ambient;
   vec3 lightPos = light.position;
   ambient = max(0,ambient-distance(crntPos,lightPos)/50);

   vec3 normal = normalize(normal);
   vec3 lightDirection = normalize(lightVec);
   float diffuseMultiplier = light.diffuse;
   float diffuse = max(dot(normal,lightDirection)*diffuseMultiplier,0.0f);
   diffuse = min(3.0f,diffuse);
   float specularLight = light.specular;
   vec3 viewDirection = normalize(camPos - crntPos);
   vec3 reflectionDirection = reflect(-lightDirection,normal);
   float maxSpecDistance = 100.0f; // modify the code with clamp ?
   // Calcul de l'effet spéculaire
   float specAngle = max(dot(viewDirection, reflectionDirection), 0.0f);
   float distanceFactor = clamp(1.0 - distance(crntPos, lightPos) / maxSpecDistance, 0.0, 1.0);
   float specular = pow(specAngle, 16) * specularLight * distanceFactor;
   tex *= (light.color * (diffuse * inten+ ambient + globalLight + specular));


   tex.r += spec.r * specular * inten;
   tex.g += spec.r * specular * inten;
   tex.b += spec.r * specular * inten;
   return tex;
}

vec3 CalcDirectionnalLight(DirectionalLight light)
{
   vec3 tex = vec3(texture(tex0, texCoord));
   vec3 spec = vec3(texture(tex1, texCoord));
   float ambient = light.ambient;
   vec3 lightPos = vec3(1.0f,1.0f,0.0f);
   vec3 lightDirection = normalize(lightPos);
   float diffuseMultiplier = light.diffuse;
   float diffuse = max(dot(normal,lightDirection)*diffuseMultiplier,0.0f);
   diffuse = min(3.0f,diffuse);
   float specularLight = light.specular;
   vec3 viewDirection = normalize(camPos - crntPos);
   vec3 reflectionDirection = reflect(-lightDirection,normal);
   float maxSpecDistance = 30.0f; // modify the code with clamp ?
   // Calcul de l'effet spéculaire
   float specAngle = max(dot(viewDirection, reflectionDirection), 0.0f);
  // float distanceFactor = clamp(1.0 - distance(crntPos, lightPos) / maxSpecDistance, 0.0, 1.0);
   float specular = pow(specAngle, 16) * specularLight ;//* distanceFactor;
   tex *= (light.color * (diffuse + ambient + globalLight + specular));

   tex.r += spec.r * specular;
   tex.g += spec.r * specular;
   tex.b += spec.r * specular;
   return tex;
}

