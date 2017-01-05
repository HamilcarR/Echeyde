#include "Shader.h"
#include "Constants.h"
#include "File_not_found.h"

std::mutex file_mutex; 


Shader::Shader() {
	

}

Shader::Shader(std::string& v, std::string &f) {
	vertex_shader_name = SHADER_LOCATION + v;
	fragment_shader_name = SHADER_LOCATION + f;
	geometry_shader_name = " "; 
	tesselation_shader_name = " ";
	create_shaders();
	compile_shaders();
}

Shader::Shader(std::string &v, std::string &f, std::string &g) {
	vertex_shader_name = SHADER_LOCATION + v;
	fragment_shader_name = SHADER_LOCATION + f;
	geometry_shader_name = SHADER_LOCATION + g;
	tesselation_shader_name = " ";
	create_shaders();
	compile_shaders();

}
Shader::Shader(std::string &v, std::string &f, std::string &g, std::string &t)
{
	vertex_shader_name = SHADER_LOCATION+v;
	fragment_shader_name = SHADER_LOCATION + f;
	geometry_shader_name = SHADER_LOCATION + g;
	tesselation_shader_name = SHADER_LOCATION + t;
	create_shaders(); 
	compile_shaders(); 
	




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


/*retrieve text from a file*/
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