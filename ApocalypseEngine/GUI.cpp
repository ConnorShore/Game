#include "GUI.h"

CEGUI::OpenGL3Renderer* GUI::_renderer = nullptr;

void GUI::init(const std::string& resourceDirectory)
{
	//Check if renderer and system already initialized
	if (_renderer == nullptr) {
		_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
		rp->setResourceGroupDirectory("looknfeel", resourceDirectory + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scprits");
	}

	_context = &CEGUI::System::getSingleton().createGUIContext(_renderer->getDefaultRenderTarget());
	_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	_context->setRootWindow(_root);
}

void GUI::render()
{
	_renderer->beginRendering();
	_context->draw();
	_renderer->endRendering();

	glDisable(GL_SCISSOR_TEST);
}

void GUI::destroy()
{
	CEGUI::System::getSingleton().destroyGUIContext(*_context);
}

CEGUI::Window* GUI::createWidget(const std::string& scheme, const glm::vec4& destRectPerc, const glm::vec4& destRectPixel, const std::string& name /* "" */)
{
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(scheme, name);
	_root->addChild(newWindow);
	setWidgetDestRect(newWindow, destRectPerc, destRectPixel);
	return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPixel)
{
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPixel.x), CEGUI::UDim(destRectPerc.y, destRectPixel.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPixel.z), CEGUI::UDim(destRectPerc.w, destRectPixel.w)));
}

void GUI::loadScheme(const std::string& schemeFile)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GUI::setFont(const std::string& fontFile)
{
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	_context->setDefaultFont(fontFile);
}