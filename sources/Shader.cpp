#include "../headers/Shader.h"
#include "../headers/Constants.h"
#include "../headers/File_not_found.h"


std::mutex file_mutex; 
static const char* shader_uniforms_texture_names[] = { "diffuse", "normal", "opacity", "blendMap", "specular", "ambiant", "height", "dudv", "data", "optional","shadowmap" };
static const char* shader_uniforms_specular_names[] = { "spec_power", "spec_exponent" };
void Shader::set_textures_uni(GLuint program){
	using namespace Echeyde;
	for (unsigned int i = 0; i < TEX_SIZE; i++)
		uniform_textures[i] = glGetUniformLocation(program, shader_uniforms_texture_names[i]);
	

	
}

Shader::Shader() {
	

}

Shader::Shader(std::string& v, std::string &f) {
	vertex_shader_name = SHADER_LOCATION + v;
	fragment_shader_name = SHADER_LOCATION + f;
	geometry_shader_name = " "; 
	tesselation_shader_name = " ";
	create_shaders();
	compile_shaders();
	uniform_model = glGetUniformLocation(getProgram(), M_MODEL.c_str());
	uniform_projection = glGetUniformLocation(getProgram(), M_PROJECTION.c_str());
	uniform_view = glGetUniformLocation(getProgram(), M_VIEW.c_str());
	set_textures_uni(programID); 

}

Shader::Shader(std::string &v, std::string &f, std::string &g) {
	vertex_shader_name = SHADER_LOCATION + v;
	fragment_shader_name = SHADER_LOCATION + f;
	geometry_shader_name = SHADER_LOCATION + g;
	tesselation_shader_name = " ";
	create_shaders();
	compile_shaders();
	uniform_model = glGetUniformLocation(getProgram(), M_MODEL.c_str());
	uniform_projection = glGetUniformLocation(getProgram(), M_PROJECTION.c_str());
	uniform_view = glGetUniformLocation(getProgram(), M_VIEW.c_str());
	set_textures_uni(programID);

}
Shader::Shader(std::string &v, std::string &f, std::string &g, std::string &t)
{
	vertex_shader_name = SHADER_LOCATION+v;
	fragment_shader_name = SHADER_LOCATION + f;
	geometry_shader_name = SHADER_LOCATION + g;
	tesselation_shader_name = SHADER_LOCATION + t;
	create_shaders(); 
	compile_shaders(); 
	uniform_model = glGetUniformLocation(getProgram(), M_MODEL.c_str());
	uniform_projection = glGetUniformLocation(getProgram(), M_PROJECTION.c_str());
	uniform_view = glGetUniformLocation(getProgram(), M_VIEW.c_str());
	set_textures_uni(programID);




}


Shader::~Shader()
{

	

	
	
}

void Shader::clean(){
	if (DEBUG_DESTRUCTOR)
		std::cout << "Shader Deleted" << std::endl;
	glDetachShader(programID, vertex_shader);
	glDetachShader(programID, fragment_shader);
	if (geometry_shader_name.compare(" ") != 0)
	{
		glDetachShader(programID, geometry_shader);
		glDeleteShader(geometry_shader);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteProgram(programID);
}

/*****************************************************************************************************************************************/
struct thread_data {
	std::string shader_location; 
	GLuint id; 
	uint16_t type;
};


/*retrieve text from a file as string*/
static std::string get_text(std::string &file) {
	std::string ret; 
	std::ifstream file_stream; 
	file_stream.open(file.c_str(), std::ios::in); 
	if (file_stream.is_open()) {
		std::string buf;
		while (std::getline(file_stream, buf)) {
			ret += buf + "\n";
		}
		file_stream.close();
	}
	else
		throw File_not_found(file);
	return ret; 
}




/*retrieve multiple source codes using threads*/
static std::string threaded_read(thread_data* data_t) {
			std::string error_message = ""; 
			 
			try {
				file_mutex.lock();
				std::string shader_code = get_text(data_t->shader_location);
				file_mutex.unlock();
				return shader_code;
			}
			catch (File_not_found &e) {
				std::cout << e.what() << std::endl;
				return " "; 
			}
			
			
		
}


/*compile shader*/

static std::string compile_shader(std::string &source_code,thread_data *data_t) {
	GLint size = source_code.size() + 1;
	const GLchar* code_c_style =(const GLchar*)(source_code.c_str());
	glShaderSource(data_t->id, 1, &(code_c_style),NULL);
	glCompileShader(data_t->id);
	GLint ok = 0;
	glGetShaderiv(data_t->id, GL_COMPILE_STATUS, &ok);
	if (ok == GL_FALSE) {
	std::string error_message = "Shader : " + data_t->shader_location + "\ncompilation problem !\n";
	int length = 0;
	glGetShaderiv(data_t->id, GL_INFO_LOG_LENGTH, &length);
	std::string infoLog;
	infoLog.reserve(size);
	glGetShaderInfoLog(data_t->id, size, NULL, &infoLog[0]);
	std::string err = error_message.append(infoLog.c_str()); 
	return err; 
	}
	else {
	return data_t->shader_location + " compiled successfully!";
	}
}

void Shader::compile_shaders() {
	thread_data vert, frag, geo; 
	vert.shader_location = vertex_shader_name; 
	vert.id = vertex_shader;
	vert.type = GL_VERTEX_SHADER; 

	frag.shader_location = fragment_shader_name;
	frag.id = fragment_shader; 
	frag.type = GL_FRAGMENT_SHADER;
	std::future<std::string> g_thread;
	if (geometry_shader_name.compare(" ")!=0) {
		geo.shader_location = geometry_shader_name;
		geo.id = geometry_shader;
		geo.type = GL_GEOMETRY_SHADER;
		g_thread = std::async(std::launch::async,threaded_read, &geo);
	} 
	auto v_thread = std::async(std::launch::async,threaded_read, &vert);
	auto f_thread = std::async(std::launch::async,threaded_read, &frag);

	std::string v_code = v_thread.get(); 
	std::string f_code = f_thread.get(); 
	std::string g_code = (geometry_shader_name.compare(" ") != 0) ? g_thread.get() : " "; 

	std::cout << compile_shader(v_code,&vert) << "\n"; 
	std::cout << compile_shader(f_code,&frag) << "\n";
	if (g_code.compare(" ") != 0) 
		std::cout << compile_shader(g_code, &geo) << "\n"; 
	
	
	glAttachShader(programID, vertex_shader); 
	glAttachShader(programID, fragment_shader); 
	if (geometry_shader_name.compare(" ") != 0)
		glAttachShader(programID, geometry_shader); 

	glLinkProgram(programID); 
	GLint link = 0; 
	glGetProgramiv(programID, GL_LINK_STATUS, &link); 
	if (link == GL_FALSE) {
		link = 0; 
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &link); 
		std::string link_error;
		link_error.reserve(link); 
		glGetProgramInfoLog(programID, link, NULL, &(link_error[0])); 
		std::cout << "Linkage problem : \n" << link_error.c_str() << std::endl; 
	}
	else {
		std::cout << "Program compiled!" << std::endl; 
	}
	


}




/*****************************************************************************************************************************************/



void Shader::create_shaders() {
	vertex_shader = glCreateShader(GL_VERTEX_SHADER); 
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); 
	programID = glCreateProgram(); 
	if (geometry_shader_name.compare(" " )!=0)
		geometry_shader = glCreateShader(GL_GEOMETRY_SHADER); 
	

}


/*****************************************************************************************************************************************/

bool Shader::operator==(const Shader A) const{
	if (vertex_shader_name.compare(A.getVertexShader()) == 0 && fragment_shader_name.compare(A.getFragmentShader()) == 0
		&& geometry_shader_name.compare(A.getGeometryShader()) == 0 && tesselation_shader_name.compare(A.getTesselationShader()) == 0)
		return true;
	else
		return false; 
}


/*****************************************************************************************************************************************/
void Shader::BindMatrices(glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model) const{
	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));


}

void Shader::BindTextures( Echeyde::TEX tex_name){
	glUniform1i(uniform_textures[tex_name], tex_name);
}



















/*****************************************************************************************************************************************/
//TODO : Use that later !
/*search the variable MAX_LIGHTS in fragment shaders and returns it*/
static unsigned int search_light_number(std::string& text){
	std::regex pattern("#define MAX_LIGHTS [0-9]+"); 
	std::vector<char> arr(text.begin(), text.end()); 
	char *c = strtok(arr.data(), "\n"); 

}
struct uni_lights_array{
	ShaderPLightUni PLight_uni;
	ShaderDLightUni DLight_uni;
	ShaderSLightUni SLight_uni;
};

static uni_lights_array get_lights_uni(GLuint program){
	uni_lights_array uni;
	for (int i = 0; i < LIGHTS_COUNT_SHADER; i++){
		GLuint p_uni_pos = glGetUniformLocation(program, ("pointLights[" + std::to_string(i) + "].position").c_str());
		GLuint p_uni_col = glGetUniformLocation(program, ("pointLights[" + std::to_string(i) + "].color").c_str());
		GLuint p_uni_att = glGetUniformLocation(program, ("pointLights[" + std::to_string(i) + "].attenuation").c_str());
		GLuint p_uni_rad = glGetUniformLocation(program, ("pointLights[" + std::to_string(i) + "].radius").c_str());
		GLuint p_uni_pow = glGetUniformLocation(program, ("pointLights[" + std::to_string(i) + "].power").c_str());
		uni.PLight_uni.uni_positions.push_back(p_uni_pos);
		uni.PLight_uni.uni_colors.push_back(p_uni_col);
		uni.PLight_uni.uni_attenuation.push_back(p_uni_att);
		uni.PLight_uni.uni_radius.push_back(p_uni_rad);
		uni.PLight_uni.uni_power.push_back(p_uni_pow);

		GLuint s_uni_pos = glGetUniformLocation(program, ("spotLights[" + std::to_string(i) + "].position").c_str());
		GLuint s_uni_col = glGetUniformLocation(program, ("spotLights[" + std::to_string(i) + "].color").c_str());
		GLuint s_uni_att = glGetUniformLocation(program, ("spotLights[" + std::to_string(i) + "].attenuation").c_str());
		GLuint s_uni_rad = glGetUniformLocation(program, ("spotLights[" + std::to_string(i) + "].radius").c_str());
		GLuint s_uni_pow = glGetUniformLocation(program, ("spotLights[" + std::to_string(i) + "].power").c_str());
		uni.SLight_uni.uni_positions.push_back(s_uni_pos);
		uni.SLight_uni.uni_colors.push_back(s_uni_col);
		uni.SLight_uni.uni_attenuation.push_back(s_uni_att);
		uni.SLight_uni.uni_radius.push_back(s_uni_rad);
		uni.SLight_uni.uni_power.push_back(s_uni_pow);


		GLuint d_uni_pos = glGetUniformLocation(program, ("directLights[" + std::to_string(i) + "].position").c_str());
		GLuint d_uni_col = glGetUniformLocation(program, ("directLights[" + std::to_string(i) + "].color").c_str());
		GLuint d_uni_pow = glGetUniformLocation(program, ("directLights[" + std::to_string(i) + "].power").c_str());
		uni.DLight_uni.uni_positions.push_back(d_uni_pos);
		uni.DLight_uni.uni_colors.push_back(d_uni_col);
		uni.DLight_uni.uni_power.push_back(d_uni_pow);

	}
	return uni;
}




BaseShader::BaseShader(std::string &vertex_shader, std::string &fragment_shader, std::string &geometry_shader) : Shader(vertex_shader, fragment_shader, geometry_shader){
	uni_lights_array uni = get_lights_uni(getProgram()); 
	SLight_uni = uni.SLight_uni;
	DLight_uni = uni.DLight_uni;
	PLight_uni = uni.PLight_uni;
	material_uni.specular_expo = glGetUniformLocation(getProgram(), shader_uniforms_specular_names[1]); 
	material_uni.specular_pow = glGetUniformLocation(getProgram(), shader_uniforms_specular_names[0]); 
	material_uni.textured = glGetUniformLocation(getProgram(), "isTextured"); 

}

BaseShader::~BaseShader(){

}

void BaseShader::BindLights(){
	lightArray = LightArray::getInstance();
	if (lightArray->getLightArray().empty())
		std::cout << "Light array is empty !\n";
	else{
		int directional = 0, point = 0, spot = 0;
		for (Light* light : lightArray->getLightArray()){
			shader_light_data shader_data = light->getLightInfo();
			base_light_data base_data = shader_data.base;
			glm::vec3 position = base_data.position;
			glm::vec3 attenuation = shader_data.attenuation;
			glm::vec3 color = base_data.colour;
			float power = base_data.power;
			float radius = shader_data.radius;

			switch (shader_data.type){
				assert(shader_data.type == Echeyde::DIRECTIONAL || shader_data.type == Echeyde::POINT || shader_data.type == Echeyde::SPOT);
			case Echeyde::DIRECTIONAL:
				glUniform3f(DLight_uni.uni_positions[directional], position.x, position.y, position.z);
				glUniform3f(DLight_uni.uni_colors[directional], color.x, color.y, color.z);
				glUniform1f(DLight_uni.uni_power[directional], power);
				directional++;
				break;
			case Echeyde::POINT:
				glUniform3f(PLight_uni.uni_positions[point], position.x, position.y, position.z);
				glUniform3f(PLight_uni.uni_colors[point], color.x, color.y, color.z);
				glUniform3f(PLight_uni.uni_attenuation[point], attenuation.x, attenuation.y, attenuation.z);
				glUniform1f(PLight_uni.uni_power[point], power);
				glUniform1f(PLight_uni.uni_radius[point], radius);
				point++;
				break;
			case Echeyde::SPOT:
				glUniform3f(SLight_uni.uni_positions[spot], position.x, position.y, position.z);
				glUniform3f(SLight_uni.uni_colors[spot], color.x, color.y, color.z);
				glUniform3f(SLight_uni.uni_attenuation[spot], attenuation.x, attenuation.y, attenuation.z);
				glUniform1f(SLight_uni.uni_power[spot], power);
				glUniform1f(SLight_uni.uni_radius[spot], radius);
				spot++;
				break;

			}

		}

		glUniform1ui(glGetUniformLocation(getProgram(), "directional_lights_size"), directional);
		glUniform1ui(glGetUniformLocation(getProgram(), "point_lights_size"), point);
		glUniform1ui(glGetUniformLocation(getProgram(), "spot_lights_size"), spot);


	}
}
/*****************************************************************************************************************************************/

void BaseShader::BindMaterials(float pow, float exp,bool textured){
	glUniform1f(material_uni.specular_expo, exp);
	glUniform1f(material_uni.specular_pow, pow); 
	glUniform1i(material_uni.textured, (textured == true) ? 1 : 0);

}




/*****************************************************************************************************************************************/








/*****************************************************************************************************************************************/







/*****************************************************************************************************************************************/







/*****************************************************************************************************************************************/



