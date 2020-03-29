#include <exception>
#include <stdexcept>
#include <chrono>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
	#define WINDOWS_LEAN_AND_MEAN
	#include <windows.h>
#else
	#include <iostream>
#endif
#include "Device.h"

namespace sgl {

	Device::Device(SDL_Window* sdl_window) 
	{
		sdl_gl_context_ = SDL_GL_CreateContext(sdl_window);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

		if (GLEW_OK != glewInit())
		{
			throw std::runtime_error("erreorinit gleew");
		}

		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version_);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version_);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void Device::Startup(std::pair<int, int> size)
	{
		program_ = std::make_shared<Program>();

		Shader vertex_shader(ShaderType::VERTEX_SHADER);
		if (!vertex_shader.LoadFromFile("../Asset/SimpleVertex.glsl"))
		{
			std::cout << "can't read vertex sahder" << std::endl;
			exit(-1);
		}
		program_->AddShader(vertex_shader);

		Shader fragement_shader(ShaderType::FRAGMENT_SHADER);
		if (!fragement_shader.LoadFromFile("../Asset/SimpleFragment.glsl"))
		{
			std::cout << "can't read vertex sahder" << std::endl;
			exit(-1);
		}
		program_->AddShader(fragement_shader);

		program_->LinkShader();
		program_->Use();

		double aspect_ratio = size.second / size.first;
		sgl::matrix projection(
			aspect_ratio * 1 / std::tan((90 * M_PI / 180) / 2), 0, 0, 0,
			0, 1 / std::tan((90 * M_PI / 180) / 2), 0, 0,
			0, 0, -(1000 + 0.1) / (1000 - 0.1), -1,
			0, 0, -(2 * 1000 * 0.1) / (1000 - 0.1), 0);

		program_->UniformMatrix("projection", projection);
		program_->UniformMatrix("view", camera_.LookAt());
		program_->UniformMatrix("model", sgl::matrix());

	}

	void Device::Draw(const double dt)
	{
		glClearColor(0.2, 0, 0.2, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (const auto& node : scene_tree_)
		{
		
			if (node->GetLocalMesh())
			{
				node->GetLocalMesh()->Draw(*program_, texture_manager_, node->GetLocalModel(dt));
			}
		}
	}

} // End namespace sgl.
