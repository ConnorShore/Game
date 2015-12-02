#pragma once

#include <glm\glm.hpp>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>

class GUI
{
public:
	void init(const std::string& resourceDirectory);
	void render();
	void destroy();

	CEGUI::Window* createWidget(const std::string& scheme, const glm::vec4& destRectPerc, const glm::vec4& destRectPixel, const std::string& name = "");
	static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPixel);

	void loadScheme(const std::string& schemeFile);
	void setFont(const std::string& fontFile);

	//Getters
	static CEGUI::OpenGL3Renderer* getRenderer() { return _renderer; }
	const CEGUI::GUIContext* getContext() { return _context; }

private:
	static CEGUI::OpenGL3Renderer* _renderer;
	CEGUI::GUIContext* _context = nullptr;
	CEGUI::Window* _root = nullptr;
};

